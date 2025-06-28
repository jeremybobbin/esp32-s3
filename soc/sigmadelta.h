#include <stdbool.h>
#include <stdint.h>

typedef enum {
	SIGMADELTA_PORT_0,      /*!< SIGMADELTA port 0 */
	SIGMADELTA_PORT_MAX,    /*!< SIGMADELTA port max */
} sigmadelta_port_t;

typedef enum {
	SIGMADELTA_CHANNEL_0,   /*!< Sigma-delta channel 0 */
	SIGMADELTA_CHANNEL_1,   /*!< Sigma-delta channel 1 */
	SIGMADELTA_CHANNEL_2,   /*!< Sigma-delta channel 2 */
	SIGMADELTA_CHANNEL_3,   /*!< Sigma-delta channel 3 */
	SIGMADELTA_CHANNEL_4,   /*!< Sigma-delta channel 4 */
	SIGMADELTA_CHANNEL_5,   /*!< Sigma-delta channel 5 */
	SIGMADELTA_CHANNEL_6,   /*!< Sigma-delta channel 6 */
	SIGMADELTA_CHANNEL_7,   /*!< Sigma-delta channel 7 */
	SIGMADELTA_CHANNEL_MAX, /*!< Sigma-delta channel max */
} sigmadelta_channel_t;

typedef struct {
	sigmadelta_channel_t channel;    /*!< Sigma-delta channel number */
	int8_t sigmadelta_duty;          /*!< Sigma-delta duty, duty ranges from -128 to 127. */
	uint8_t sigmadelta_prescale;     /*!< Sigma-delta prescale, prescale ranges from 0 to 255. */
	uint8_t  sigmadelta_gpio;        /*!< Sigma-delta output io number, refer to gpio.h for more details. */
} sigmadelta_config_t;


typedef volatile struct gpio_sd_dev_s {
	union {
		struct {
			uint32_t duty                          :    8;
			uint32_t prescale                      :    8;
			uint32_t reserved16                    :    16;
		};
		uint32_t val;
	} channel[8];
	union {
		struct {
			uint32_t reserved0                     :    31;
			uint32_t clk_en                        :    1;
		};
		uint32_t val;
	} cg;
	union {
		struct {
			uint32_t reserved0                     :    30;
			uint32_t function_clk_en               :    1;
			uint32_t spi_swap                      :    1;
		};
		uint32_t val;
	} misc;
	union {
		struct {
			uint32_t date                          :    28;
			uint32_t reserved28                    :    4;
		};
		uint32_t val;
	} version;
} gpio_sd_dev_t;
extern gpio_sd_dev_t SIGMADELTA;


#define SIGMADELTA_LL_GET_HW(num) (((num) == 0) ? (&SIGMADELTA) : NULL)

void sigmadelta_ll_set_en(gpio_sd_dev_t *hw, bool en);
void sigmadelta_ll_set_duty(gpio_sd_dev_t *hw, sigmadelta_channel_t channel, int8_t duty);
void sigmadelta_ll_set_prescale(gpio_sd_dev_t *hw, sigmadelta_channel_t channel, uint8_t prescale);
