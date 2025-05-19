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

#define SPIMEM_FLASH_LL_CLKREG_VAL_5MHZ   ((spimem_flash_ll_clock_reg_t){.val=0x000F070F})   ///< Clock set to 5 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_10MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00070307})   ///< Clock set to 10 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_20MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00030103})   ///< Clock set to 20 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_26MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00020002})   ///< Clock set to 26 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_40MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00010001})   ///< Clock set to 40 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_80MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x80000000})   ///< Clock set to 80 MHz

void spimem_flash_ll_reset(spi_mem_dev_t *dev);
bool spimem_flash_ll_cmd_is_done(const spi_mem_dev_t *dev);
void spimem_flash_ll_erase_chip(spi_mem_dev_t *dev);
void spimem_flash_ll_erase_sector(spi_mem_dev_t *dev);
void spimem_flash_ll_erase_block(spi_mem_dev_t *dev);
void spimem_flash_ll_suspend(spi_mem_dev_t *dev);
void spimem_flash_ll_resume(spi_mem_dev_t *dev);
void spimem_flash_ll_auto_suspend_init(spi_mem_dev_t *dev, bool auto_sus);
void spimem_flash_ll_auto_resume_init(spi_mem_dev_t *dev, bool auto_res);
void spimem_flash_ll_suspend_cmd_setup(spi_mem_dev_t *dev, uint32_t sus_cmd);
void spimem_flash_ll_resume_cmd_setup(spi_mem_dev_t *dev, uint32_t res_cmd);
void spimem_flash_ll_rd_sus_cmd_setup(spi_mem_dev_t *dev, uint32_t pesr_cmd);
void spimem_flash_ll_sus_check_sus_setup(spi_mem_dev_t *dev, bool sus_check_sus_en);
void spimem_flash_ll_res_check_sus_setup(spi_mem_dev_t *dev, bool res_check_sus_en);
void spimem_flash_ll_set_read_sus_status(spi_mem_dev_t *dev, uint32_t sus_mask);
void spimem_flash_ll_auto_wait_idle_init(spi_mem_dev_t *dev, bool auto_waiti);
bool spimem_flash_ll_sus_status(spi_mem_dev_t *dev);
void spimem_flash_ll_set_write_protect(spi_mem_dev_t *dev, bool wp);
void spimem_flash_ll_get_buffer_data(spi_mem_dev_t *dev, void *buffer, uint32_t read_len);
void spimem_flash_ll_set_buffer_data(spi_mem_dev_t *dev, const void *buffer, uint32_t length);
void spimem_flash_ll_program_page(spi_mem_dev_t *dev, const void *buffer, uint32_t length);
void spimem_flash_ll_user_start(spi_mem_dev_t *dev);
bool spimem_flash_ll_host_idle(const spi_mem_dev_t *dev);
void spimem_flash_ll_read_phase(spi_mem_dev_t *dev);
void spimem_flash_ll_set_cs_pin(spi_mem_dev_t *dev, int pin);
void spimem_flash_ll_set_read_mode(spi_mem_dev_t *dev, esp_flash_io_mode_t read_mode);
void spimem_flash_ll_set_clock(spi_mem_dev_t *dev, spimem_flash_ll_clock_reg_t *clock_val);
void spimem_flash_ll_set_miso_bitlen(spi_mem_dev_t *dev, uint32_t bitlen);
void spimem_flash_ll_set_mosi_bitlen(spi_mem_dev_t *dev, uint32_t bitlen);
void spimem_flash_ll_set_command(spi_mem_dev_t *dev, uint32_t command, uint32_t bitlen);
int spimem_flash_ll_get_addr_bitlen(spi_mem_dev_t *dev);
void spimem_flash_ll_set_addr_bitlen(spi_mem_dev_t *dev, uint32_t bitlen);
void spimem_flash_ll_set_address(spi_mem_dev_t *dev, uint32_t addr);
void spimem_flash_ll_set_usr_address(spi_mem_dev_t *dev, uint32_t addr, uint32_t bitlen);
void spimem_flash_ll_set_dummy(spi_mem_dev_t *dev, uint32_t dummy_n);
void spimem_flash_ll_set_dummy_out(spi_mem_dev_t *dev, uint32_t out_en, uint32_t out_lev);
void spimem_flash_ll_set_hold(spi_mem_dev_t *dev, uint32_t hold_n);
void spimem_flash_ll_set_cs_setup(spi_mem_dev_t *dev, uint32_t cs_setup_time);
void spimem_flash_ll_set_extra_dummy(spi_mem_dev_t *dev, uint32_t extra_dummy);
