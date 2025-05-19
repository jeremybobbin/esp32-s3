#include <stdbool.h>
#include "soc/sigmadelta_periph.h"
#include "soc/gpio_sd_struct.h"
#include "hal/sigmadelta_types.h"
#include "hal/misc.h"

#define SIGMADELTA_LL_GET_HW(num) (((num) == 0) ? (&SIGMADELTA) : NULL)

void sigmadelta_ll_set_en(gpio_sd_dev_t *hw, bool en);
void sigmadelta_ll_set_duty(gpio_sd_dev_t *hw, sigmadelta_channel_t channel, int8_t duty);
void sigmadelta_ll_set_prescale(gpio_sd_dev_t *hw, sigmadelta_channel_t channel, uint8_t prescale);
