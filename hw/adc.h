#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define SOC_ADC_FSM_RSTB_WAIT_DEFAULT       (8)
#define SOC_ADC_FSM_START_WAIT_DEFAULT      (5)
#define SOC_ADC_FSM_STANDBY_WAIT_DEFAULT    (100)
#define ADC_FSM_SAMPLE_CYCLE_DEFAULT        (2)
#define SOC_ADC_PWDET_CCT_DEFAULT           (4)
#define SOC_ADC_SAR_CLK_DIV_DEFAULT(PERIPH_NUM) ((PERIPH_NUM==0)? 2 : 1)
#define SOC_ADC_DIGI_SAR_CLK_DIV_DEFAULT     (1)

#define ADC_LL_CLKM_DIV_NUM_DEFAULT 15
#define ADC_LL_CLKM_DIV_B_DEFAULT   1
#define ADC_LL_CLKM_DIV_A_DEFAULT   0

typedef enum {
	ADC_UNIT_1 = 1,          /*!< SAR ADC 1. */
	ADC_UNIT_2 = 2,          /*!< SAR ADC 2. */
	ADC_UNIT_BOTH = 3,       /*!< SAR ADC 1 and 2. */
	ADC_UNIT_ALTER = 7,      /*!< SAR ADC 1 and 2 alternative mode. */
	ADC_UNIT_MAX,
} adc_unit_t;

typedef enum {
	ADC_CHANNEL_0 = 0, /*!< ADC channel */
	ADC_CHANNEL_1,     /*!< ADC channel */
	ADC_CHANNEL_2,     /*!< ADC channel */
	ADC_CHANNEL_3,     /*!< ADC channel */
	ADC_CHANNEL_4,     /*!< ADC channel */
	ADC_CHANNEL_5,     /*!< ADC channel */
	ADC_CHANNEL_6,     /*!< ADC channel */
	ADC_CHANNEL_7,     /*!< ADC channel */
	ADC_CHANNEL_8,     /*!< ADC channel */
	ADC_CHANNEL_9,     /*!< ADC channel */
	ADC_CHANNEL_MAX,
} adc_channel_t;

typedef enum {
	ADC_ATTEN_DB_0   = 0,  /*!<No input attenumation, ADC can measure up to approx. 800 mV. */
	ADC_ATTEN_DB_2_5 = 1,  /*!<The input voltage of ADC will be attenuated extending the range of measurement by about 2.5 dB (1.33 x) */
	ADC_ATTEN_DB_6   = 2,  /*!<The input voltage of ADC will be attenuated extending the range of measurement by about 6 dB (2 x) */
	ADC_ATTEN_DB_11  = 3,  /*!<The input voltage of ADC will be attenuated extending the range of measurement by about 11 dB (3.55 x) */
	ADC_ATTEN_MAX,
} adc_atten_t;

typedef enum {
	ADC_WIDTH_BIT_12 = 3, /*!< ADC capture width is 12Bit. */
	ADC_WIDTH_MAX,
} adc_bits_width_t;

typedef enum {
	ADC_CONV_SINGLE_UNIT_1 = 1,  ///< Only use ADC1 for conversion
	ADC_CONV_SINGLE_UNIT_2 = 2,  ///< Only use ADC2 for conversion
	ADC_CONV_BOTH_UNIT     = 3,  ///< Use Both ADC1 and ADC2 for conversion simultaneously
	ADC_CONV_ALTER_UNIT    = 7,  ///< Use both ADC1 and ADC2 for conversion by turn. e.g. ADC1 -> ADC2 -> ADC1 -> ADC2 .....
	ADC_CONV_UNIT_MAX,
} adc_digi_convert_mode_t;

typedef enum {
	ADC_DIGI_FORMAT_12BIT __attribute__((deprecated)),  /*!<ADC to DMA data format,                [15:12]-channel, [11: 0]-12 bits ADC data (`adc_digi_output_data_t`). Note: For single convert mode. */
	ADC_DIGI_FORMAT_11BIT __attribute__((deprecated)),  /*!<ADC to DMA data format, [15]-adc unit, [14:11]-channel, [10: 0]-11 bits ADC data (`adc_digi_output_data_t`). Note: For multi or alter convert mode. */
	ADC_DIGI_FORMAT_MAX   __attribute__((deprecated)),

	ADC_DIGI_OUTPUT_FORMAT_TYPE1,   ///< See `adc_digi_output_data_t.type1`
	ADC_DIGI_OUTPUT_FORMAT_TYPE2,   ///< See `adc_digi_output_data_t.type2`
} adc_digi_output_format_t;

typedef struct {
	uint8_t atten;      ///< Attenuation of this ADC channel
	uint8_t channel;    ///< ADC channel
	uint8_t unit;       ///< ADC unit
	uint8_t bit_width;  ///< ADC output bit width
} adc_digi_pattern_config_t;

typedef struct {
	union {
		struct {
			uint16_t data:     12;  /*!<ADC real output data info. Resolution: 12 bit. */
			uint16_t channel:   4;  /*!<ADC channel index info. */
		} type1;                    /*!<ADC type1 */
		struct {
			uint16_t data:     11;  /*!<ADC real output data info. Resolution: 11 bit. */
			uint16_t channel:   4;  /*!<ADC channel index info. For ESP32-S2:
										If (channel < ADC_CHANNEL_MAX), The data is valid.
										If (channel > ADC_CHANNEL_MAX), The data is invalid. */
			uint16_t unit:      1;  /*!<ADC unit index info. 0: ADC1; 1: ADC2.  */
		} type2;                    /*!<When the configured output format is 11bit. `ADC_DIGI_FORMAT_11BIT` */
		uint16_t val;               /*!<Raw data value */
	};
} adc_digi_output_data_t;

typedef enum {
	ADC_NUM_1 = 0,          /*!< SAR ADC 1 */
	ADC_NUM_2 = 1,          /*!< SAR ADC 2 */
	ADC_NUM_MAX,
} adc_ll_num_t;

typedef enum {
	ADC_POWER_BY_FSM,   /*!< ADC XPD controled by FSM. Used for polling mode */
	ADC_POWER_SW_ON,    /*!< ADC XPD controled by SW. power on. Used for DMA mode */
	ADC_POWER_SW_OFF,   /*!< ADC XPD controled by SW. power off. */
	ADC_POWER_MAX,      /*!< For parameter check. */
} adc_ll_power_t;

typedef enum {
	ADC_RTC_DATA_OK = 0,
	ADC_RTC_CTRL_UNSELECTED = 1,
	ADC_RTC_CTRL_BREAK = 2,
	ADC_RTC_DATA_FAIL = -1,
} adc_ll_rtc_raw_data_t;

typedef enum {
	ADC_LL_CTRL_RTC = 0,    ///< For ADC1. Select RTC controller.
	ADC_LL_CTRL_ULP = 1,    ///< For ADC1 and ADC2. Select ULP controller.
	ADC_LL_CTRL_DIG = 2,    ///< For ADC1. Select DIG controller.
	ADC_LL_CTRL_ARB = 3,    ///< For ADC2. The controller is selected by the arbiter.
} adc_ll_controller_t;

typedef enum {
	ADC_LL_DIGI_CONV_ONLY_ADC1  = 0,    // Only use ADC1 for conversion
	ADC_LL_DIGI_CONV_ONLY_ADC2  = 1,    // Only use ADC2 for conversion
	ADC_LL_DIGI_CONV_BOTH_UNIT  = 2,    // Use Both ADC1 and ADC2 for conversion simultaneously
	ADC_LL_DIGI_CONV_ALTER_UNIT = 3     // Use both ADC1 and ADC2 for conversion by turn. e.g. ADC1 -> ADC2 -> ADC1 -> ADC2 .....
} adc_ll_digi_convert_mode_t;

typedef struct {
	union {
		struct {
			uint8_t atten:       2;
			uint8_t channel:     4;
			uint8_t reserved:    2;
		};
		uint8_t val;
	};
} __attribute__((packed)) adc_ll_digi_pattern_table_t;


typedef struct {
	union {
		struct {
			uint16_t data:     13;  /*!<ADC real output data info. Resolution: 13 bit. */
			uint16_t reserved:  1;  /*!<reserved */
			uint16_t flag:      2;  /*!<ADC data flag info.
										If (flag == 0), The data is valid.
										If (flag > 0), The data is invalid. */
		};
		uint16_t val;
	};
} adc_ll_rtc_output_data_t;

typedef volatile struct apb_saradc_dev_s {
	union {
		struct {
			uint32_t start_force                   :    1;
			uint32_t start                         :    1;
			uint32_t reserved2                     :    1;
			uint32_t work_mode                     :    2;  /* 0: single mode, 1: double mode, 2: alternate mode*/
			uint32_t sar_sel                       :    1;  /* 0: SAR1, 1: SAR2, only work for single SAR mode*/
			uint32_t sar_clk_gated                 :    1;
			uint32_t sar_clk_div                   :    8;  /*SAR clock divider*/
			uint32_t sar1_patt_len                 :    4;  /* 0 ~ 15 means length 1 ~ 16*/
			uint32_t sar2_patt_len                 :    4;  /* 0 ~ 15 means length 1 ~ 16*/
			uint32_t sar1_patt_p_clear             :    1;  /*clear the pointer of pattern table for DIG ADC1 CTRL*/
			uint32_t sar2_patt_p_clear             :    1;  /*clear the pointer of pattern table for DIG ADC2 CTRL*/
			uint32_t data_sar_sel                  :    1;  /*1: sar_sel will be coded by the MSB of the 16-bit output data, in this case the resolution should not be larger than 11 bits.*/
			uint32_t data_to_i2s                   :    1;  /*1: I2S input data is from SAR ADC (for DMA), 0: I2S input data is from GPIO matrix*/
			uint32_t xpd_sar_force                 :    2;  /*force option to xpd sar blocks*/
			uint32_t reserved29                    :    1;
			uint32_t wait_arb_cycle                :    2;  /*wait arbit signal stable after sar_done*/
		};
		uint32_t val;
	} ctrl;
	union {
		struct {
			uint32_t meas_num_limit                :    1;
			uint32_t max_meas_num                  :    8;  /*max conversion number*/
			uint32_t sar1_inv                      :    1;  /*1: data to DIG ADC1 CTRL is inverted, otherwise not*/
			uint32_t sar2_inv                      :    1;  /*1: data to DIG ADC2 CTRL is inverted, otherwise not*/
			uint32_t timer_sel                     :    1;  /*1: select saradc timer 0: i2s_ws trigger*/
			uint32_t timer_target                  :    12;  /*to set saradc timer target*/
			uint32_t timer_en                      :    1;  /*to enable saradc timer trigger*/
			uint32_t reserved25                    :    7;
		};
		uint32_t val;
	} ctrl2;
	union {
		struct {
			uint32_t reserved0                     :    26;
			uint32_t filter_factor1                :    3;
			uint32_t filter_factor0                :    3;
		};
		uint32_t val;
	} filter_ctrl1;
	union {
		struct {
			uint32_t xpd_wait                      :    8;
			uint32_t rstb_wait                     :    8;
			uint32_t standby_wait                  :    8;
			uint32_t reserved24                    :    8;
		};
		uint32_t val;
	} fsm_wait;
	uint32_t sar1_status;
	uint32_t sar2_status;
	union {
		struct {
			uint32_t sar1_patt_tab                 :    24;  /*item 0 ~ 3 for pattern table 1 (each item one byte)*/
			uint32_t reserved24                    :    8;
		};
		uint32_t val;
	} sar1_patt_tab[4];
	union {
		struct {
			uint32_t sar2_patt_tab                 :    24;  /*item 0 ~ 3 for pattern table 2 (each item one byte)*/
			uint32_t reserved24                    :    8;
		};
		uint32_t val;
	} sar2_patt_tab[4];
	union {
		struct {
			uint32_t reserved0                     :    2;
			uint32_t adc_arb_apb_force             :    1;  /*adc2 arbiter force to enableapb controller*/
			uint32_t adc_arb_rtc_force             :    1;  /*adc2 arbiter force to enable rtc controller*/
			uint32_t adc_arb_wifi_force            :    1;  /*adc2 arbiter force to enable wifi controller*/
			uint32_t adc_arb_grant_force           :    1;  /*adc2 arbiter force grant*/
			uint32_t adc_arb_apb_priority          :    2;  /*Set adc2 arbiterapb priority*/
			uint32_t adc_arb_rtc_priority          :    2;  /*Set adc2 arbiter rtc priority*/
			uint32_t adc_arb_wifi_priority         :    2;  /*Set adc2 arbiter wifi priority*/
			uint32_t adc_arb_fix_priority          :    1;  /*adc2 arbiter uses fixed priority*/
			uint32_t reserved13                    :    19;
		};
		uint32_t val;
	} apb_adc_arb_ctrl;
	union {
		struct {
			uint32_t reserved0                     :    14;
			uint32_t filter_channel1               :    5;
			uint32_t filter_channel0               :    5;  /*apb_adc1_filter_factor*/
			uint32_t reserved24                    :    7;
			uint32_t filter_reset                  :    1;  /*enable apb_adc1_filter*/
		};
		uint32_t val;
	} filter_ctrl0;
	union {
		struct {
			uint32_t adc1_data                     :    17;
			uint32_t reserved17                    :    15;
		};
		uint32_t val;
	} apb_saradc1_data_status;
	union {
		struct {
			uint32_t thres0_channel                :    5;
			uint32_t thres0_high                   :    13;  /*saradc1's thres0 monitor thres*/
			uint32_t thres0_low                    :    13;  /*saradc1's thres0 monitor thres*/
			uint32_t reserved31                    :    1;
		};
		uint32_t val;
	} thres0_ctrl;
	union {
		struct {
			uint32_t thres1_channel                :    5;
			uint32_t thres1_high                   :    13;  /*saradc1's thres0 monitor thres*/
			uint32_t thres1_low                    :    13;  /*saradc1's thres0 monitor thres*/
			uint32_t reserved31                    :    1;
		};
		uint32_t val;
	} thres1_ctrl;
	uint32_t reserved_4c;
	uint32_t reserved_50;
	uint32_t reserved_54;
	union {
		struct {
			uint32_t reserved0                     :    27;
			uint32_t thres_all_en                  :    1;
			uint32_t thres3_en                     :    1;
			uint32_t thres2_en                     :    1;
			uint32_t thres1_en                     :    1;
			uint32_t thres0_en                     :    1;
		};
		uint32_t val;
	} thres_ctrl;
	union {
		struct {
			uint32_t reserved0                     :    26;
			uint32_t thres1_low                    :    1;
			uint32_t thres0_low                    :    1;
			uint32_t thres1_high                   :    1;
			uint32_t thres0_high                   :    1;
			uint32_t adc2_done                     :    1;
			uint32_t adc1_done                     :    1;
		};
		uint32_t val;
	} int_ena;
	union {
		struct {
			uint32_t reserved0                     :    26;
			uint32_t thres1_low                    :    1;
			uint32_t thres0_low                    :    1;
			uint32_t thres1_high                   :    1;
			uint32_t thres0_high                   :    1;
			uint32_t adc2_done                     :    1;
			uint32_t adc1_done                     :    1;
		};
		uint32_t val;
	} int_raw;
	union {
		struct {
			uint32_t reserved0                     :    26;
			uint32_t thres1_low                    :    1;
			uint32_t thres0_low                    :    1;
			uint32_t thres1_high                   :    1;
			uint32_t thres0_high                   :    1;
			uint32_t adc2_done                     :    1;
			uint32_t adc1_done                     :    1;
		};
		uint32_t val;
	} int_st;
	union {
		struct {
			uint32_t reserved0                     :    26;
			uint32_t thres1_low                    :    1;
			uint32_t thres0_low                    :    1;
			uint32_t thres1_high                   :    1;
			uint32_t thres0_high                   :    1;
			uint32_t adc2_done                     :    1;
			uint32_t adc1_done                     :    1;
		};
		uint32_t val;
	} int_clr;
	union {
		struct {
			uint32_t apb_adc_eof_num               :    16;  /*the dma_in_suc_eof gen when sample cnt = spi_eof_num*/
			uint32_t reserved16                    :    14;
			uint32_t apb_adc_reset_fsm             :    1;  /*reset_apb_adc_state*/
			uint32_t apb_adc_trans                 :    1;  /*enable apb_adc use spi_dma*/
		};
		uint32_t val;
	} dma_conf;
	union {
		struct {
			uint32_t clkm_div_num                  :    8;  /*Integral I2S clock divider value*/
			uint32_t clkm_div_b                    :    6;  /*Fractional clock divider numerator value*/
			uint32_t clkm_div_a                    :    6;  /*Fractional clock divider denominator value*/
			uint32_t clk_en                        :    1;
			uint32_t clk_sel                       :    2;  /*Set this bit to enable clk_apll*/
			uint32_t reserved23                    :    9;
		};
		uint32_t val;
	} apb_adc_clkm_conf;
	uint32_t reserved_74;
	union {
		struct {
			uint32_t adc2_data                     :    17;
			uint32_t reserved17                    :    15;
		};
		uint32_t val;
	} apb_saradc2_data_status;
	uint32_t reserved[224];
	uint32_t apb_ctrl_date;
} apb_saradc_dev_t;

extern apb_saradc_dev_t APB_SARADC;

void adc_ll_digi_set_fsm_time(uint32_t rst_wait, uint32_t start_wait, uint32_t standby_wait);
void adc_ll_set_sample_cycle(uint32_t sample_cycle);
void adc_ll_digi_set_clk_div(uint32_t div);
void adc_ll_digi_set_convert_limit_num(uint32_t meas_num);
void adc_ll_digi_convert_limit_enable(void);
void adc_ll_digi_convert_limit_disable(void);
void adc_ll_digi_set_convert_mode(adc_ll_digi_convert_mode_t mode);
void adc_ll_digi_set_pattern_table_len(adc_ll_num_t adc_n, uint32_t patt_len);
void adc_ll_digi_set_pattern_table(adc_ll_num_t adc_n, uint32_t pattern_index, adc_digi_pattern_config_t table);
void adc_ll_digi_clear_pattern_table(adc_ll_num_t adc_n);
void adc_ll_digi_set_arbiter_stable_cycle(uint32_t cycle);
void adc_ll_digi_output_invert(adc_ll_num_t adc_n, bool inv_en);
void adc_ll_digi_set_trigger_interval(uint32_t cycle);
void adc_ll_digi_trigger_enable(void);
void adc_ll_digi_trigger_disable(void);
void adc_ll_digi_controller_clk_div(uint32_t div_num, uint32_t div_b, uint32_t div_a);
void adc_ll_digi_clk_sel(bool use_apll);
void adc_ll_digi_controller_clk_disable(void);
void adc_ll_digi_dma_set_eof_num(uint32_t num);
void adc_ll_digi_dma_enable(void);
void adc_ll_digi_dma_disable(void);
void adc_ll_digi_reset(void);
void adc_ll_pwdet_set_cct(uint32_t cct);
uint32_t adc_ll_pwdet_get_cct(void);
void adc_ll_set_power_manage(adc_ll_power_t manage);
void adc_ll_set_controller(adc_ll_num_t adc_n, adc_ll_controller_t ctrl);
void adc_ll_set_arbiter_work_mode(adc_arbiter_mode_t mode);
void adc_ll_set_arbiter_priority(uint8_t pri_rtc, uint8_t pri_dig, uint8_t pri_pwdet);
void adc_ll_enable_sleep_controller(void);
void adc_ll_disable_sleep_controller(void);
void adc_ll_calibration_init(adc_ll_num_t adc_n);
void adc_ll_calibration_prepare(adc_ll_num_t adc_n, adc_channel_t channel, bool internal_gnd);
void adc_ll_calibration_finish(adc_ll_num_t adc_n);
void adc_ll_set_calibration_param(adc_ll_num_t adc_n, uint32_t param);
void adc_ll_vref_output(adc_ll_num_t adc, adc_channel_t channel, bool en);
void adc_ll_set_sar_clk_div(adc_ll_num_t adc_n, uint32_t div);
void adc_ll_rtc_set_output_format(adc_ll_num_t adc_n, adc_bits_width_t bits);
void adc_ll_rtc_enable_channel(adc_ll_num_t adc_n, int channel);
void adc_ll_rtc_disable_channel(adc_ll_num_t adc_n);
void adc_ll_rtc_start_convert(adc_ll_num_t adc_n, int channel);
bool adc_ll_rtc_convert_is_done(adc_ll_num_t adc_n);
int adc_ll_rtc_get_convert_value(adc_ll_num_t adc_n);
void adc_ll_rtc_output_invert(adc_ll_num_t adc_n, bool inv_en);
void adc_ll_rtc_intr_enable(adc_ll_num_t adc_n);
void adc_ll_rtc_intr_disable(adc_ll_num_t adc_n);
void adc_ll_rtc_reset(void);
void adc_ll_rtc_set_arbiter_stable_cycle(uint32_t cycle);
adc_ll_rtc_raw_data_t adc_ll_rtc_analysis_raw_data(adc_ll_num_t adc_n, uint16_t raw_data);
void adc_ll_set_atten(adc_ll_num_t adc_n, adc_channel_t channel, adc_atten_t atten);
adc_atten_t adc_ll_get_atten(adc_ll_num_t adc_n, adc_channel_t channel);
uint32_t adc_ll_adc1_read(void);
uint32_t adc_ll_adc2_read(void);
