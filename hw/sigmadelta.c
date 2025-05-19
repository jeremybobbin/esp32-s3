
/*******************************************************************************
 * NOTICE
 * The hal is not public api, don't use in application code.
 * See readme.md in hal/include/hal/readme.md
 ******************************************************************************/

// The LL layer for ESP32 SIGMADELTA register operations

#pragma once

#include <stdbool.h>
#include "soc/sigmadelta_periph.h"
#include "soc/gpio_sd_struct.h"
#include "hal/sigmadelta_types.h"
#include "hal/misc.h"

#ifdef __cplusplus
extern "C" {
#endif

// Get SIGMADELTA hardware instance with giving sigmadelta num
#define SIGMADELTA_LL_GET_HW(num) (((num) == 0) ? (&SIGMADELTA) : NULL)

/**
 * @brief Set Sigma-delta enable
 *
 * @param hw Peripheral SIGMADELTA hardware instance address.
 * @param en Sigma-delta enable value
 */
static inline void sigmadelta_ll_set_en(gpio_sd_dev_t *hw, bool en)
{
	hw->misc.function_clk_en = en;
}

/**
 * @brief Set Sigma-delta channel duty.
 *
 * @param hw Peripheral SIGMADELTA hardware instance address.
 * @param channel Sigma-delta channel number
 * @param duty Sigma-delta duty of one channel, the value ranges from -128 to 127, recommended range is -90 ~ 90.
 *             The waveform is more like a random one in this range.
 */
static inline void sigmadelta_ll_set_duty(gpio_sd_dev_t *hw, sigmadelta_channel_t channel, int8_t duty)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->channel[channel], duty, (uint8_t)duty);
}

/**
 * @brief Set Sigma-delta channel's clock pre-scale value.
 *
 * @param hw Peripheral SIGMADELTA hardware instance address.
 * @param channel Sigma-delta channel number
 * @param val The divider of source clock, ranges from 0 to 255
 */
static inline void sigmadelta_ll_set_prescale(gpio_sd_dev_t *hw, sigmadelta_channel_t channel, uint8_t prescale)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->channel[channel], prescale, prescale);
}

#ifdef __cplusplus
}
#endif
