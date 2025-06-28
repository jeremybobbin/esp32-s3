

// The LL layer for ESP32 SIGMADELTA register operations


#include <stdbool.h>
#include "soc/sigmadelta.h"
#include "soc/i2c.h"


// Get SIGMADELTA hardware instance with giving sigmadelta num
#define SIGMADELTA_LL_GET_HW(num) (((num) == 0) ? (&SIGMADELTA) : NULL)

void sigmadelta_ll_set_en(gpio_sd_dev_t *hw, bool en)
{
	hw->misc.function_clk_en = en;
}

void sigmadelta_ll_set_duty(gpio_sd_dev_t *hw, sigmadelta_channel_t channel, int8_t duty)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->channel[channel], duty, (uint8_t)duty);
}

void sigmadelta_ll_set_prescale(gpio_sd_dev_t *hw, sigmadelta_channel_t channel, uint8_t prescale)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->channel[channel], prescale, prescale);
}

