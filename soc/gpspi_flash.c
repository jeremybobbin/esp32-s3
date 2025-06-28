#include <stdlib.h>
#include <sys/param.h> // For MIN/MAX
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "soc/gpspi_flash.h"
#include "soc/i2c.h"

/*
#define SPI_FCMD_QUAD_M  (1<<9)
#define SPI_FREAD_QUAD_M  (1<<15)
#define SPI_FADDR_QUAD    (1<<6)
#define SPI_FADDR_QUAD_M  (1<<6)
#define SPI_FADDR_DUAL_M  (1<<5)
#define SPI_FCMD_DUAL_M  (1<<8)
#define SPI_FREAD_DUAL_M  (1<<14)
#define SPI_FWRITE_QUAD_M  (1<<13)
#define SPI_FWRITE_DUAL_M  (1<<12)
*/

spi_dev_t *GPSPI2  = (void*)0x60024000;



/*
#define gpspi_flash_ll_get_hw(host_id)  (((host_id)==SPI2_HOST ? GPSPI2 \
												: ((host_id)==SPI3_HOST ? &GPSPI3 \
												: ({abort();(spi_dev_t*)0;}))))

#define gpspi_flash_ll_hw_get_id(dev)   ( ((dev) == (void*)GPSPI2) ? SPI2_HOST : (\
										  ((dev) == (void*)&GPSPI3) ? SPI3_HOST : (\
										  -1 \
										)) )

												*/


//Supported clock register values
#define GPSPI_FLASH_LL_CLKREG_VAL_5MHZ   ((gpspi_flash_ll_clock_reg_t){.val=0x0000F1CF})   ///< Clock set to 5 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_10MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x000070C7})   ///< Clock set to 10 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_20MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x00003043})   ///< Clock set to 20 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_26MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x00002002})   ///< Clock set to 26 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_40MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x00001001})   ///< Clock set to 40 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_80MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x80000000})   ///< Clock set to 80 MHz

void gpspi_flash_ll_reset(spi_dev_t *dev)
{
	dev->user.val = 0;
	dev->ctrl.val = 0;

	dev->clk_gate.clk_en = 1;
	dev->clk_gate.mst_clk_active = 1;
	dev->clk_gate.mst_clk_sel = 1;

	dev->dma_conf.val = 0;
	dev->dma_conf.tx_seg_trans_clr_en = 1;
	dev->dma_conf.rx_seg_trans_clr_en = 1;
	dev->dma_conf.dma_seg_trans_en = 0;
}

bool gpspi_flash_ll_cmd_is_done(const spi_dev_t *dev)
{
	return (dev->cmd.usr == 0);
}

void gpspi_flash_ll_get_buffer_data(spi_dev_t *dev, void *buffer, uint32_t read_len)
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

void gpspi_flash_ll_write_word(spi_dev_t *dev, uint32_t word)
{
	dev->data_buf[0] = word;
}

void gpspi_flash_ll_set_buffer_data(spi_dev_t *dev, const void *buffer, uint32_t length)
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

void gpspi_flash_ll_user_start(spi_dev_t *dev)
{
	dev->cmd.update = 1;
	while (dev->cmd.update);
	dev->cmd.usr = 1;
}

void gpspi_flash_ll_set_hold_pol(spi_dev_t *dev, uint32_t pol_val)
{
	dev->ctrl.hold_pol = pol_val;
}

bool gpspi_flash_ll_host_idle(const spi_dev_t *dev)
{
	return dev->cmd.usr == 0;
}

void gpspi_flash_ll_read_phase(spi_dev_t *dev)
{
	typeof (dev->user) user = {
		.usr_command = 1,
		.usr_mosi = 0,
		.usr_miso = 1,
		.usr_addr = 1,
	};
	dev->user = user;
}
void gpspi_flash_ll_set_cs_pin(spi_dev_t *dev, int pin)
{
	dev->misc.cs0_dis = (pin == 0) ? 0 : 1;
	dev->misc.cs1_dis = (pin == 1) ? 0 : 1;
}

void gpspi_flash_ll_set_read_mode(spi_dev_t *dev, esp_flash_io_mode_t read_mode)
{
	typeof (dev->ctrl) ctrl = dev->ctrl;
	typeof (dev->user) user = dev->user;

	ctrl.val &= ~(SPI_FCMD_QUAD_M | SPI_FADDR_QUAD_M | SPI_FREAD_QUAD_M | SPI_FCMD_DUAL_M | SPI_FADDR_DUAL_M | SPI_FREAD_DUAL_M);
	user.val &= ~(SPI_FWRITE_QUAD_M | SPI_FWRITE_DUAL_M);

	switch (read_mode) {
	case SPI_FLASH_FASTRD:
		//the default option
	case SPI_FLASH_SLOWRD:
		break;
	case SPI_FLASH_QIO:
		ctrl.fread_quad = 1;
		ctrl.faddr_quad = 1;
		user.fwrite_quad = 1;
		break;
	case SPI_FLASH_QOUT:
		ctrl.fread_quad = 1;
		user.fwrite_quad = 1;
		break;
	case SPI_FLASH_DIO:
		ctrl.fread_dual = 1;
		ctrl.faddr_dual = 1;
		user.fwrite_dual = 1;
		break;
	case SPI_FLASH_DOUT:
		ctrl.fread_dual = 1;
		user.fwrite_dual = 1;
		break;
	default:
		abort();
	}

	dev->ctrl = ctrl;
	dev->user = user;
}

void gpspi_flash_ll_set_clock(spi_dev_t *dev, gpspi_flash_ll_clock_reg_t *clock_val)
{
	dev->clock = *clock_val;
}

void gpspi_flash_ll_set_miso_bitlen(spi_dev_t *dev, uint32_t bitlen)
{
	dev->user.usr_miso = bitlen > 0;
	if (bitlen) {
		dev->ms_dlen.ms_data_bitlen = bitlen - 1;
	}
}

void gpspi_flash_ll_set_mosi_bitlen(spi_dev_t *dev, uint32_t bitlen)
{
	dev->user.usr_mosi = bitlen > 0;
	if (bitlen) {
		dev->ms_dlen.ms_data_bitlen = bitlen - 1;
	}
}

void gpspi_flash_ll_set_command(spi_dev_t *dev, uint8_t command, uint32_t bitlen)
{
	dev->user.usr_command = 1;
	typeof(dev->user2) user2 = {
		.usr_command_value = command,
		.usr_command_bitlen = (bitlen - 1),
	};
	dev->user2 = user2;
}

int gpspi_flash_ll_get_addr_bitlen(spi_dev_t *dev)
{
	return dev->user.usr_addr ? dev->user1.usr_addr_bitlen + 1 : 0;
}

void gpspi_flash_ll_set_addr_bitlen(spi_dev_t *dev, uint32_t bitlen)
{
	dev->user1.usr_addr_bitlen = (bitlen - 1);
	dev->user.usr_addr = bitlen ? 1 : 0;
}

void gpspi_flash_ll_set_usr_address(spi_dev_t *dev, uint32_t addr, uint32_t bitlen)
{
	// The blank region should be all ones
	uint32_t padding_ones = (bitlen == 32? 0 : UINT32_MAX >> bitlen);
	dev->addr = (addr << (32 - bitlen)) | padding_ones;
}


void gpspi_flash_ll_set_address(spi_dev_t *dev, uint32_t addr)
{
	dev->addr = addr;
}

void gpspi_flash_ll_set_dummy(spi_dev_t *dev, uint32_t dummy_n)
{
	dev->user.usr_dummy = dummy_n ? 1 : 0;
	//HAL_FORCE_MODIFY_U32_REG_FIELD(dev->user1, dev->user1.usr_dummy_cyclelen, dummy_n - 1);
	HAL_FORCE_MODIFY_U32_REG_FIELD(dev->user1, usr_dummy_cyclelen, dummy_n - 1);
}

void gpspi_flash_ll_set_dummy_out(spi_dev_t *dev, uint32_t out_en, uint32_t out_lev)
{
	dev->ctrl.dummy_out = out_en;
	dev->ctrl.q_pol = out_lev;
	dev->ctrl.d_pol = out_lev;
}

void gpspi_flash_ll_set_hold(spi_dev_t *dev, uint32_t hold_n)
{
	dev->user1.cs_hold_time = hold_n - 1;
	dev->user.cs_hold = (hold_n > 0? 1: 0);
}

void gpspi_flash_ll_set_cs_setup(spi_dev_t *dev, uint32_t cs_setup_time)
{
	dev->user.cs_setup = (cs_setup_time > 0 ? 1 : 0);
	dev->user1.cs_setup_time = cs_setup_time - 1;
}

