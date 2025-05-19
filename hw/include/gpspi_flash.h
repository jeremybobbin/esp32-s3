#include <stdlib.h>
#include <sys/param.h> // For MIN/MAX
#include <stdbool.h>
#include <string.h>

#define gpspi_flash_ll_get_hw(host_id)  (((host_id)==SPI2_HOST ? &GPSPI2 \
												: ((host_id)==SPI3_HOST ? &GPSPI3 \
												: ({abort();(spi_dev_t*)0;}))))

#define gpspi_flash_ll_hw_get_id(dev)   ( ((dev) == (void*)&GPSPI2) ? SPI2_HOST : (\
										  ((dev) == (void*)&GPSPI3) ? SPI3_HOST : (\
										  -1 \
										)) )

typedef typeof(GPSPI2.clock) gpspi_flash_ll_clock_reg_t;

#define GPSPI_FLASH_LL_CLKREG_VAL_5MHZ   ((gpspi_flash_ll_clock_reg_t){.val=0x0000F1CF})   ///< Clock set to 5 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_10MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x000070C7})   ///< Clock set to 10 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_20MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x00003043})   ///< Clock set to 20 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_26MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x00002002})   ///< Clock set to 26 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_40MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x00001001})   ///< Clock set to 40 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_80MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x80000000})   ///< Clock set to 80 MHz

void gpspi_flash_ll_reset(spi_dev_t *dev);
bool gpspi_flash_ll_cmd_is_done(const spi_dev_t *dev);
void gpspi_flash_ll_get_buffer_data(spi_dev_t *dev, void *buffer, uint32_t read_len);
void gpspi_flash_ll_write_word(spi_dev_t *dev, uint32_t word);
void gpspi_flash_ll_set_buffer_data(spi_dev_t *dev, const void *buffer, uint32_t length);
void gpspi_flash_ll_user_start(spi_dev_t *dev);
void gpspi_flash_ll_set_hold_pol(spi_dev_t *dev, uint32_t pol_val);
bool gpspi_flash_ll_host_idle(const spi_dev_t *dev);
void gpspi_flash_ll_read_phase(spi_dev_t *dev);
void gpspi_flash_ll_set_cs_pin(spi_dev_t *dev, int pin);
void gpspi_flash_ll_set_read_mode(spi_dev_t *dev, esp_flash_io_mode_t read_mode);
void gpspi_flash_ll_set_clock(spi_dev_t *dev, gpspi_flash_ll_clock_reg_t *clock_val);
void gpspi_flash_ll_set_miso_bitlen(spi_dev_t *dev, uint32_t bitlen);
void gpspi_flash_ll_set_mosi_bitlen(spi_dev_t *dev, uint32_t bitlen);
void gpspi_flash_ll_set_command(spi_dev_t *dev, uint8_t command, uint32_t bitlen);
int gpspi_flash_ll_get_addr_bitlen(spi_dev_t *dev);
void gpspi_flash_ll_set_addr_bitlen(spi_dev_t *dev, uint32_t bitlen);
void gpspi_flash_ll_set_usr_address(spi_dev_t *dev, uint32_t addr, uint32_t bitlen);
void gpspi_flash_ll_set_address(spi_dev_t *dev, uint32_t addr);
void gpspi_flash_ll_set_dummy(spi_dev_t *dev, uint32_t dummy_n);
void gpspi_flash_ll_set_dummy_out(spi_dev_t *dev, uint32_t out_en, uint32_t out_lev);
void gpspi_flash_ll_set_hold(spi_dev_t *dev, uint32_t hold_n);
void gpspi_flash_ll_set_cs_setup(spi_dev_t *dev, uint32_t cs_setup_time);
