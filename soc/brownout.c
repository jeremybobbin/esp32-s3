#include "soc/rtc_cntl.h"
#include "soc/i2c.h"
#include <stdbool.h>

#define I2C_BOD            0x61
#define I2C_BOD_HOSTID     1

#define I2C_BOD_THRESHOLD           0x5
#define I2C_BOD_THRESHOLD_MSB       2
#define I2C_BOD_THRESHOLD_LSB       0

typedef struct {
	uint8_t threshold;
	bool enabled;
	bool reset_enabled;
	bool flash_power_down;
	bool rf_power_down;
} brownout_hal_config_t;


#define REGI2C_WRITE_MASK(block, reg_add, indata) \
      rom_i2c_writeReg_Mask(block, block##_HOSTID,  reg_add,  reg_add##_MSB,  reg_add##_LSB,  indata)

void brownout_hal_config(const brownout_hal_config_t *cfg)
{
	REGI2C_WRITE_MASK(I2C_BOD, I2C_BOD_THRESHOLD, cfg->threshold);
	typeof(RTCCNTL->brown_out) brown_out_reg = {
		.int_wait = 0x002,
		.close_flash_ena = cfg->flash_power_down,
		.pd_rf_ena = cfg->rf_power_down,
		.rst_wait = 0x3ff,
		.rst_ena = cfg->reset_enabled,
		.ena = cfg->enabled,
		.rst_sel = 1,
	};
	RTCCNTL->brown_out = brown_out_reg;
}

void brownout_hal_intr_enable(bool enable)
{
	RTCCNTL->int_ena.rtc_brown_out = enable;
}

void brownout_hal_intr_clear(void)
{
	RTCCNTL->int_clr.rtc_brown_out = 1;
}
