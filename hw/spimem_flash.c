

// The Lowlevel layer for SPI Flash


#include <stdlib.h>
#include <sys/param.h> // For MIN/MAX
#include <stdbool.h>
#include <string.h>

#include "soc/spi_periph.h"
#include "soc/spi_mem_struct.h"
#include "hal/spi_types.h"
#include "hal/spi_flash_types.h"


#define spimem_flash_ll_get_hw(host_id)  (((host_id)==SPI1_HOST ?  &SPIMEM1 : NULL ))
#define spimem_flash_ll_hw_get_id(dev)  ((dev) == (void*)&SPIMEM1? SPI1_HOST: -1)

typedef typeof(SPIMEM1.clock) spimem_flash_ll_clock_reg_t;

//Supported clock register values
#define SPIMEM_FLASH_LL_CLKREG_VAL_5MHZ   ((spimem_flash_ll_clock_reg_t){.val=0x000F070F})   ///< Clock set to 5 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_10MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00070307})   ///< Clock set to 10 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_20MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00030103})   ///< Clock set to 20 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_26MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00020002})   ///< Clock set to 26 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_40MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00010001})   ///< Clock set to 40 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_80MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x80000000})   ///< Clock set to 80 MHz

void spimem_flash_ll_reset(spi_mem_dev_t *dev)
{
	dev->user.val = 0;
	dev->ctrl.val = 0;
}

bool spimem_flash_ll_cmd_is_done(const spi_mem_dev_t *dev)
{
	return (dev->cmd.val == 0);
}

void spimem_flash_ll_erase_chip(spi_mem_dev_t *dev)
{
	dev->cmd.flash_ce = 1;
}

void spimem_flash_ll_erase_sector(spi_mem_dev_t *dev)
{
	dev->ctrl.val = 0;
	dev->cmd.flash_se = 1;
}

void spimem_flash_ll_erase_block(spi_mem_dev_t *dev)
{
	dev->cmd.flash_be = 1;
}

void spimem_flash_ll_suspend(spi_mem_dev_t *dev)
{
	dev->flash_sus_cmd.flash_pes = 1;
}

void spimem_flash_ll_resume(spi_mem_dev_t *dev)
{
	dev->flash_sus_cmd.flash_per = 1;
}

void spimem_flash_ll_auto_suspend_init(spi_mem_dev_t *dev, bool auto_sus)
{
	dev->flash_sus_ctrl.flash_pes_en = auto_sus; // enable Flash Auto-Suspend.
}

void spimem_flash_ll_auto_resume_init(spi_mem_dev_t *dev, bool auto_res)
{
	dev->misc.auto_per = auto_res;
}

void spimem_flash_ll_suspend_cmd_setup(spi_mem_dev_t *dev, uint32_t sus_cmd)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(dev->flash_sus_ctrl, flash_pes_command, sus_cmd);
}

void spimem_flash_ll_resume_cmd_setup(spi_mem_dev_t *dev, uint32_t res_cmd)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(dev->flash_sus_ctrl, flash_per_command, res_cmd);
}

void spimem_flash_ll_rd_sus_cmd_setup(spi_mem_dev_t *dev, uint32_t pesr_cmd)
{
	abort(); //Not support on esp32s3
}

void spimem_flash_ll_sus_check_sus_setup(spi_mem_dev_t *dev, bool sus_check_sus_en)
{
	abort(); //Not support on esp32s3
}

void spimem_flash_ll_res_check_sus_setup(spi_mem_dev_t *dev, bool res_check_sus_en)
{
	abort(); //Not support ont esp32s3
}

void spimem_flash_ll_set_read_sus_status(spi_mem_dev_t *dev, uint32_t sus_mask)
{
	abort();// Not supported on esp32s3
}

void spimem_flash_ll_auto_wait_idle_init(spi_mem_dev_t *dev, bool auto_waiti)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(dev->flash_waiti_ctrl, waiti_cmd, 0x05); // Set the command to send, to fetch flash status reg value.
	dev->flash_waiti_ctrl.waiti_en = auto_waiti;  // enable auto wait-idle function.
}

bool spimem_flash_ll_sus_status(spi_mem_dev_t *dev)
{
	return dev->sus_status.flash_sus;
}

void spimem_flash_ll_set_write_protect(spi_mem_dev_t *dev, bool wp)
{
	if (wp) {
		dev->cmd.flash_wrdi = 1;
	} else {
		dev->cmd.flash_wren = 1;
	}
}

void spimem_flash_ll_get_buffer_data(spi_mem_dev_t *dev, void *buffer, uint32_t read_len)
{
	if (((intptr_t)buffer % 4 == 0) && (read_len % 4 == 0)) {
		// If everything is word-aligned, do a faster memcpy
		memcpy(buffer, (void *)dev->data_buf, read_len);
	} else {
		// Otherwise, slow(er) path copies word by word
		int copy_len = read_len;
		for (uint32_t i = 0; i < (read_len + 3) / 4; i++) {
			int word_len = MIN(sizeof(uint32_t), copy_len);
			uint32_t word = dev->data_buf[i];
			memcpy(buffer, &word, word_len);
			buffer = (void *)((intptr_t)buffer + word_len);
			copy_len -= word_len;
		}
	}
}

void spimem_flash_ll_set_buffer_data(spi_mem_dev_t *dev, const void *buffer, uint32_t length)
{
	// Load data registers, word at a time
	int num_words = (length + 3) / 4;
	for (int i = 0; i < num_words; i++) {
		uint32_t word = 0;
		uint32_t word_len = MIN(length, sizeof(word));
		memcpy(&word, buffer, word_len);
		dev->data_buf[i] = word;
		length -= word_len;
		buffer = (void *)((intptr_t)buffer + word_len);
	}
}


void spimem_flash_ll_program_page(spi_mem_dev_t *dev, const void *buffer, uint32_t length)
{
	dev->user.usr_dummy = 0;
	spimem_flash_ll_set_buffer_data(dev, buffer, length);
	dev->cmd.flash_pp = 1;
}

void spimem_flash_ll_user_start(spi_mem_dev_t *dev)
{
	dev->cmd.usr = 1;
}

bool spimem_flash_ll_host_idle(const spi_mem_dev_t *dev)
{
	return dev->fsm.st == 0;
}

void spimem_flash_ll_read_phase(spi_mem_dev_t *dev)
{
	typeof (dev->user) user = {
		.usr_command = 1,
		.usr_mosi = 0,
		.usr_miso = 1,
		.usr_addr = 1,
	};
	dev->user = user;
}
void spimem_flash_ll_set_cs_pin(spi_mem_dev_t *dev, int pin)
{
	dev->misc.cs0_dis = (pin == 0) ? 0 : 1;
	dev->misc.cs1_dis = (pin == 1) ? 0 : 1;
}

void spimem_flash_ll_set_read_mode(spi_mem_dev_t *dev, esp_flash_io_mode_t read_mode)
{
	typeof (dev->ctrl) ctrl = dev->ctrl;
	ctrl.val &= ~(SPI_MEM_FREAD_QIO_M | SPI_MEM_FREAD_QUAD_M | SPI_MEM_FREAD_DIO_M | SPI_MEM_FREAD_DUAL_M | SPI_MEM_FCMD_OCT | SPI_MEM_FADDR_OCT | SPI_MEM_FDIN_OCT | SPI_MEM_FDOUT_OCT);
	dev->ddr.fmem_ddr_en = 0;
	ctrl.val |= SPI_MEM_FASTRD_MODE_M;
	switch (read_mode) {
	case SPI_FLASH_FASTRD:
		//the default option
		break;
	case SPI_FLASH_QIO:
		ctrl.fread_qio = 1;
		break;
	case SPI_FLASH_QOUT:
		ctrl.fread_quad = 1;
		break;
	case SPI_FLASH_DIO:
		ctrl.fread_dio = 1;
		break;
	case SPI_FLASH_DOUT:
		ctrl.fread_dual = 1;
		break;
	case SPI_FLASH_SLOWRD:
		ctrl.fastrd_mode = 0;
		break;
	case SPI_FLASH_OPI_STR:
		ctrl.faddr_oct = 1;
		ctrl.fcmd_oct = 1;
		ctrl.fdin_oct = 1;
		ctrl.fdout_oct = 1;
		break;
	case SPI_FLASH_OPI_DTR:
		ctrl.faddr_oct = 1;
		ctrl.fcmd_oct = 1;
		ctrl.fdin_oct = 1;
		ctrl.fdout_oct = 1;
		dev->ddr.fmem_ddr_en = 1;
		break;
	default:
		abort();
	}
	dev->ctrl = ctrl;
}

void spimem_flash_ll_set_clock(spi_mem_dev_t *dev, spimem_flash_ll_clock_reg_t *clock_val)
{
	dev->clock = *clock_val;
}

void spimem_flash_ll_set_miso_bitlen(spi_mem_dev_t *dev, uint32_t bitlen)
{
	dev->user.usr_miso = bitlen > 0;
	dev->miso_dlen.usr_miso_bit_len = bitlen ? (bitlen - 1) : 0;
}

void spimem_flash_ll_set_mosi_bitlen(spi_mem_dev_t *dev, uint32_t bitlen)
{
	dev->user.usr_mosi = bitlen > 0;
	dev->mosi_dlen.usr_mosi_bit_len = bitlen ? (bitlen - 1) : 0;
}

void spimem_flash_ll_set_command(spi_mem_dev_t *dev, uint32_t command, uint32_t bitlen)
{
	dev->user.usr_command = 1;
	typeof(dev->user2) user2 = {
		.usr_command_value = command,
		.usr_command_bitlen = (bitlen - 1),
	};
	dev->user2 = user2;
}

int spimem_flash_ll_get_addr_bitlen(spi_mem_dev_t *dev)
{
	return dev->user.usr_addr ? dev->user1.usr_addr_bitlen + 1 : 0;
}

void spimem_flash_ll_set_addr_bitlen(spi_mem_dev_t *dev, uint32_t bitlen)
{
	// set the correct address length here (24-length or 32-length address),
	dev->cache_fctrl.usr_cmd_4byte = (bitlen == 32) ? 1 : 0 ;
	dev->user1.usr_addr_bitlen = (bitlen - 1);
	dev->user.usr_addr = bitlen ? 1 : 0;
}

void spimem_flash_ll_set_address(spi_mem_dev_t *dev, uint32_t addr)
{
	dev->addr = addr;
}

void spimem_flash_ll_set_usr_address(spi_mem_dev_t *dev, uint32_t addr, uint32_t bitlen)
{
	(void)bitlen;
	spimem_flash_ll_set_address(dev, addr);
}

void spimem_flash_ll_set_dummy(spi_mem_dev_t *dev, uint32_t dummy_n)
{
	dev->user.usr_dummy = dummy_n ? 1 : 0;
	dev->user1.usr_dummy_cyclelen = dummy_n - 1;
}

void spimem_flash_ll_set_dummy_out(spi_mem_dev_t *dev, uint32_t out_en, uint32_t out_lev)
{
	dev->ctrl.fdummy_out = out_en;
	dev->ctrl.q_pol = out_lev;
	dev->ctrl.d_pol = out_lev;
}

void spimem_flash_ll_set_hold(spi_mem_dev_t *dev, uint32_t hold_n)
{
	dev->ctrl2.cs_hold_time = hold_n - 1;
	dev->user.cs_hold = (hold_n > 0? 1: 0);
}

void spimem_flash_ll_set_cs_setup(spi_mem_dev_t *dev, uint32_t cs_setup_time)
{
	dev->user.cs_setup = (cs_setup_time > 0 ? 1 : 0);
	dev->ctrl2.cs_setup_time = cs_setup_time - 1;
}

void spimem_flash_ll_set_extra_dummy(spi_mem_dev_t *dev, uint32_t extra_dummy)
{
	dev->timing_cali.extra_dummy_cyclelen = extra_dummy;
}

