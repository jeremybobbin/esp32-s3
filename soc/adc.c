#include <stdlib.h>

#include "soc/i2c.h"
#include "rom/i2c.h"
#include "soc/adc.h"
#include "soc/rtc_cntl.h"
#include "soc/sens.h"

#define I2C_SAR_ADC            0X69
#define I2C_SAR_ADC_HOSTID     1

#define ADC_SAR1_ENCAL_GND_ADDR 0x7
#define ADC_SAR1_ENCAL_GND_ADDR_MSB 5
#define ADC_SAR1_ENCAL_GND_ADDR_LSB 5

#define ADC_SAR2_ENCAL_GND_ADDR 0x7
#define ADC_SAR2_ENCAL_GND_ADDR_MSB 7
#define ADC_SAR2_ENCAL_GND_ADDR_LSB 7

#define ADC_SAR1_INITIAL_CODE_HIGH_ADDR 0x1
#define ADC_SAR1_INITIAL_CODE_HIGH_ADDR_MSB 0x3
#define ADC_SAR1_INITIAL_CODE_HIGH_ADDR_LSB 0x0

#define ADC_SAR1_INITIAL_CODE_LOW_ADDR  0x0
#define ADC_SAR1_INITIAL_CODE_LOW_ADDR_MSB  0x7
#define ADC_SAR1_INITIAL_CODE_LOW_ADDR_LSB  0x0

#define ADC_SAR2_INITIAL_CODE_HIGH_ADDR 0x4
#define ADC_SAR2_INITIAL_CODE_HIGH_ADDR_MSB 0x3
#define ADC_SAR2_INITIAL_CODE_HIGH_ADDR_LSB 0x0

#define ADC_SAR2_INITIAL_CODE_LOW_ADDR  0x3
#define ADC_SAR2_INITIAL_CODE_LOW_ADDR_MSB  0x7
#define ADC_SAR2_INITIAL_CODE_LOW_ADDR_LSB  0x0

#define ADC_SAR1_DREF_ADDR  0x2
#define ADC_SAR1_DREF_ADDR_MSB  0x6
#define ADC_SAR1_DREF_ADDR_LSB  0x4

#define ADC_SAR2_DREF_ADDR  0x5
#define ADC_SAR2_DREF_ADDR_MSB  0x6
#define ADC_SAR2_DREF_ADDR_LSB  0x4

#define ADC_SAR1_SAMPLE_CYCLE_ADDR 0x2
#define ADC_SAR1_SAMPLE_CYCLE_ADDR_MSB 0x2
#define ADC_SAR1_SAMPLE_CYCLE_ADDR_LSB 0x0

#define ADC_SARADC_DTEST_RTC_ADDR 0x7
#define ADC_SARADC_DTEST_RTC_ADDR_MSB 1
#define ADC_SARADC_DTEST_RTC_ADDR_LSB 0

#define ADC_SARADC_ENT_TSENS_ADDR 0x7
#define ADC_SARADC_ENT_TSENS_ADDR_MSB 2
#define ADC_SARADC_ENT_TSENS_ADDR_LSB 2

#define ADC_SARADC_ENT_RTC_ADDR 0x7
#define ADC_SARADC_ENT_RTC_ADDR_MSB 3
#define ADC_SARADC_ENT_RTC_ADDR_LSB 3

#define ADC_SARADC_ENCAL_REF_ADDR 0x7
#define ADC_SARADC_ENCAL_REF_ADDR_MSB 4
#define ADC_SARADC_ENCAL_REF_ADDR_LSB 4

#define I2C_SARADC_TSENS_DAC 0x6
#define I2C_SARADC_TSENS_DAC_MSB 3
#define I2C_SARADC_TSENS_DAC_LSB 0


#define I2C_MST_ANA_CONF0_REG  0x6000E040
#define I2C_MST_BBPLL_STOP_FORCE_HIGH  (1<<2)
#define I2C_MST_BBPLL_STOP_FORCE_LOW   (1<<3)
#define I2C_MST_BBPLL_CAL_DONE  (1<<24)
#define ANA_CONFIG_REG  0x6000E044
#define ANA_CONFIG_S    (8)
#define ANA_CONFIG_M    (0x3FF)
#define I2C_APLL_M      (1<<14)
#define I2C_BBPLL_M     (1<<17)
#define I2C_SAR_M       (1<<18)

#define ANA_CONFIG2_REG 0x6000E048
#define ANA_SAR_CFG2_M  (1<<16)
#define REGI2C_WRITE_MASK(block, reg_add, indata) \
      rom_i2c_writeReg_Mask(block, block##_HOSTID,  reg_add,  reg_add##_MSB,  reg_add##_LSB,  indata)

#define REGI2C_READ_MASK(block, reg_add) \
      rom_i2c_readReg_Mask(block, block##_HOSTID,  reg_add,  reg_add##_MSB,  reg_add##_LSB)

#define REGI2C_WRITE(block, reg_add, indata) \
      rom_i2c_writeReg(block, block##_HOSTID,  reg_add, indata)

#define REGI2C_READ(block, reg_add) \
      rom_i2c_readReg(block, block##_HOSTID,  reg_add)



#define HAL_FORCE_MODIFY_U32_REG_FIELD(base_reg, reg_field, field_val)    \
{                                                           \
	uint32_t temp_val = base_reg.val;                       \
	typeof(base_reg) temp_reg;                              \
	temp_reg.val = temp_val;                                \
	temp_reg.reg_field = (field_val);                       \
	(base_reg).val = temp_reg.val;                          \
}

#define HAL_FORCE_READ_U32_REG_FIELD(base_reg, reg_field) ({    \
	uint32_t temp_val = base_reg.val;                       \
	typeof(base_reg) temp_reg;                              \
	temp_reg.val = temp_val;                                \
	temp_reg.reg_field;                                     \
})

apb_saradc_dev_t *APB_SARADC = (void*)0x60040000;

void adc_ll_digi_set_fsm_time(uint32_t rst_wait, uint32_t start_wait, uint32_t standby_wait)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC->fsm_wait, rstb_wait, rst_wait);
	HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC->fsm_wait, xpd_wait, start_wait);
	HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC->fsm_wait, standby_wait, standby_wait);
}

void adc_ll_set_sample_cycle(uint32_t sample_cycle) {
	*((volatile int*)RTC_CNTL_ANA_CONF_REG) |= RTC_CNTL_SAR_I2C_PU_M;
	*((volatile int*)ANA_CONFIG_REG) ^= I2C_SAR_M;
	*((volatile int*)ANA_CONFIG2_REG) |= ANA_SAR_CFG2_M;

	REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_SAMPLE_CYCLE_ADDR, sample_cycle);
}

void adc_ll_digi_set_clk_div(uint32_t div) {
	/* ADC clock divided from digital controller clock clk */
	HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC->ctrl, sar_clk_div, div);
}

void adc_ll_digi_set_convert_limit_num(uint32_t meas_num) {
	HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC->ctrl2, max_meas_num, meas_num);
}

void adc_ll_digi_convert_limit_enable(void) {
	APB_SARADC->ctrl2.meas_num_limit = 1;
}

void adc_ll_digi_convert_limit_disable(void) {
	APB_SARADC->ctrl2.meas_num_limit = 0;
}

void adc_ll_digi_set_convert_mode(adc_ll_digi_convert_mode_t mode) {
	if (mode == ADC_LL_DIGI_CONV_ONLY_ADC1) {
		APB_SARADC->ctrl.work_mode = 0;
		APB_SARADC->ctrl.sar_sel = 0;
	} else if (mode == ADC_LL_DIGI_CONV_ONLY_ADC2) {
		APB_SARADC->ctrl.work_mode = 0;
		APB_SARADC->ctrl.sar_sel = 1;
	} else if (mode == ADC_LL_DIGI_CONV_BOTH_UNIT) {
		APB_SARADC->ctrl.work_mode = 1;
	} else if (mode == ADC_LL_DIGI_CONV_ALTER_UNIT) {
		APB_SARADC->ctrl.work_mode = 2;
	}
	APB_SARADC->ctrl.data_sar_sel = 1;
}

void adc_ll_digi_set_pattern_table_len(adc_ll_num_t adc_n, uint32_t patt_len) {
	if (adc_n == ADC_NUM_1) {
		APB_SARADC->ctrl.sar1_patt_len = patt_len - 1;
	} else { // adc_n == ADC_NUM_2
		APB_SARADC->ctrl.sar2_patt_len = patt_len - 1;
	}
}

void adc_ll_digi_set_pattern_table(adc_ll_num_t adc_n, uint32_t pattern_index, adc_digi_pattern_config_t table) {
	uint32_t tab;
	uint8_t index = pattern_index / 4;
	uint8_t offset = (pattern_index % 4) * 6;
	adc_ll_digi_pattern_table_t pattern = {0};

	pattern.val = (table.atten & 0x3) | ((table.channel & 0xF) << 2);
	if (table.unit == ADC_NUM_1){
		tab = APB_SARADC->sar1_patt_tab[index].sar1_patt_tab;            //Read old register value
		tab &= (~(0xFC0000 >> offset));                 //Clear old data
		tab |= ((uint32_t)(pattern.val & 0x3F) << 18) >> offset;   //Fill in the new data
		APB_SARADC->sar1_patt_tab[index].sar1_patt_tab = tab;            //Write back
	} else {
		tab = APB_SARADC->sar2_patt_tab[index].sar2_patt_tab;        //Read old register value
		tab &= (~(0xFC0000 >> offset));                             //clear old data
		tab |= ((uint32_t)(pattern.val & 0x3F) << 18) >> offset;    //Fill in the new data
		APB_SARADC->sar2_patt_tab[index].sar2_patt_tab = tab;        //Write back
	}
}

void adc_ll_digi_clear_pattern_table(adc_ll_num_t adc_n) {
	if (adc_n == ADC_NUM_1) {
		APB_SARADC->ctrl.sar1_patt_p_clear = 1;
		APB_SARADC->ctrl.sar1_patt_p_clear = 0;
	} else { // adc_n == ADC_NUM_2
		APB_SARADC->ctrl.sar2_patt_p_clear = 1;
		APB_SARADC->ctrl.sar2_patt_p_clear = 0;
	}
}

void adc_ll_digi_set_arbiter_stable_cycle(uint32_t cycle) {
	APB_SARADC->ctrl.wait_arb_cycle = cycle;
}

void adc_ll_digi_output_invert(adc_ll_num_t adc_n, bool inv_en) {
	if (adc_n == ADC_NUM_1) {
		APB_SARADC->ctrl2.sar1_inv = inv_en;   // Enable / Disable ADC data invert
	} else { // adc_n == ADC_NUM_2
		APB_SARADC->ctrl2.sar2_inv = inv_en;   // Enable / Disable ADC data invert
	}
}

void adc_ll_digi_set_trigger_interval(uint32_t cycle) {
	APB_SARADC->ctrl2.timer_target = cycle;
}

void adc_ll_digi_trigger_enable(void) {
	APB_SARADC->ctrl2.timer_sel = 1;
	APB_SARADC->ctrl2.timer_en = 1;
}

void adc_ll_digi_trigger_disable(void) {
	APB_SARADC->ctrl2.timer_en = 0;
}

void adc_ll_digi_controller_clk_div(uint32_t div_num, uint32_t div_b, uint32_t div_a) {
	HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC->apb_adc_clkm_conf, clkm_div_num, div_num);
	APB_SARADC->apb_adc_clkm_conf.clkm_div_b = div_b;
	APB_SARADC->apb_adc_clkm_conf.clkm_div_a = div_a;
}

void adc_ll_digi_clk_sel(bool use_apll) {
	if (use_apll) {
		APB_SARADC->apb_adc_clkm_conf.clk_sel = 1;   // APLL clock
	} else {
		APB_SARADC->apb_adc_clkm_conf.clk_sel = 2;   // APB clock
	}
	APB_SARADC->ctrl.sar_clk_gated = 1;
}

void adc_ll_digi_controller_clk_disable(void) {
	APB_SARADC->ctrl.sar_clk_gated = 0;
	APB_SARADC->apb_adc_clkm_conf.clk_sel = 0;
}

void adc_ll_digi_dma_set_eof_num(uint32_t num) {
	HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC->dma_conf, apb_adc_eof_num, num);
}

void adc_ll_digi_dma_enable(void) {
	APB_SARADC->dma_conf.apb_adc_trans = 1;
}

void adc_ll_digi_dma_disable(void) {
	APB_SARADC->dma_conf.apb_adc_trans = 0;
}

void adc_ll_digi_reset(void) {
	APB_SARADC->dma_conf.apb_adc_reset_fsm = 1;
	APB_SARADC->dma_conf.apb_adc_reset_fsm = 0;
}

void adc_ll_pwdet_set_cct(uint32_t cct) {
	/* Capacitor tuning of the PA power monitor. cct set to the same value with PHY. */
	SENS->sar_meas2_mux.sar2_pwdet_cct = cct;
}

uint32_t adc_ll_pwdet_get_cct(void) {
	/* Capacitor tuning of the PA power monitor. cct set to the same value with PHY. */
	return SENS->sar_meas2_mux.sar2_pwdet_cct;
}

void adc_ll_set_power_manage(adc_ll_power_t manage) {
	/* Bit1  0:Fsm  1: SW mode
	   Bit0  0:SW mode power down  1: SW mode power on */
	if (manage == ADC_POWER_SW_ON) {
		SENS->sar_peri_clk_gate_conf.saradc_clk_en = 1;
		SENS->sar_power_xpd_sar.force_xpd_sar = 3; //SENS_FORCE_XPD_SAR_PU;
	} else if (manage == ADC_POWER_BY_FSM) {
		SENS->sar_peri_clk_gate_conf.saradc_clk_en = 1;
		SENS->sar_power_xpd_sar.force_xpd_sar = 0; //SENS_FORCE_XPD_SAR_FSM;
	} else if (manage == ADC_POWER_SW_OFF) {
		SENS->sar_power_xpd_sar.force_xpd_sar = 2; //SENS_FORCE_XPD_SAR_PD;
		SENS->sar_peri_clk_gate_conf.saradc_clk_en = 0;
	}
}

void adc_ll_set_controller(adc_ll_num_t adc_n, adc_ll_controller_t ctrl) {
	if (adc_n == ADC_NUM_1) {
		switch (ctrl) {
			case ADC_LL_CTRL_RTC:
				SENS->sar_meas1_mux.sar1_dig_force       = 0;    // 1: Select digital control;       0: Select RTC control.
				SENS->sar_meas1_ctrl2.meas1_start_force  = 1;    // 1: SW control RTC ADC start;     0: ULP control RTC ADC start.
				SENS->sar_meas1_ctrl2.sar1_en_pad_force  = 1;    // 1: SW control RTC ADC bit map;   0: ULP control RTC ADC bit map;
				break;
			case ADC_LL_CTRL_ULP:
				SENS->sar_meas1_mux.sar1_dig_force       = 0;    // 1: Select digital control;       0: Select RTC control.
				SENS->sar_meas1_ctrl2.meas1_start_force  = 0;    // 1: SW control RTC ADC start;     0: ULP control RTC ADC start.
				SENS->sar_meas1_ctrl2.sar1_en_pad_force  = 0;    // 1: SW control RTC ADC bit map;   0: ULP control RTC ADC bit map;
				break;
			case ADC_LL_CTRL_DIG:
				SENS->sar_meas1_mux.sar1_dig_force       = 1;    // 1: Select digital control;       0: Select RTC control.
				SENS->sar_meas1_ctrl2.meas1_start_force  = 1;    // 1: SW control RTC ADC start;     0: ULP control RTC ADC start.
				SENS->sar_meas1_ctrl2.sar1_en_pad_force  = 1;    // 1: SW control RTC ADC bit map;   0: ULP control RTC ADC bit map;
				break;
			default:
				break;
		}
	} else { // adc_n == ADC_NUM_2
		//If ADC2 is not controlled by ULP, the arbiter will decide which controller to use ADC2.
		switch (ctrl) {
			case ADC_LL_CTRL_ARB:
				SENS->sar_meas2_ctrl2.meas2_start_force  = 1;    // 1: SW control RTC ADC start;     0: ULP control RTC ADC start.
				SENS->sar_meas2_ctrl2.sar2_en_pad_force  = 1;    // 1: SW control RTC ADC bit map;   0: ULP control RTC ADC bit map;
				break;
			case ADC_LL_CTRL_ULP:
				SENS->sar_meas2_ctrl2.meas2_start_force  = 0;    // 1: SW control RTC ADC start;     0: ULP control RTC ADC start.
				SENS->sar_meas2_ctrl2.sar2_en_pad_force  = 0;    // 1: SW control RTC ADC bit map;   0: ULP control RTC ADC bit map;
				break;
			default:
				break;
		}
	}
}

void adc_ll_set_arbiter_work_mode(adc_arbiter_mode_t mode) {
	if (mode == ADC_ARB_MODE_FIX) {
		APB_SARADC->apb_adc_arb_ctrl.adc_arb_grant_force = 0;
		APB_SARADC->apb_adc_arb_ctrl.adc_arb_fix_priority = 1;
	} else if (mode == ADC_ARB_MODE_LOOP) {
		APB_SARADC->apb_adc_arb_ctrl.adc_arb_grant_force = 0;
		APB_SARADC->apb_adc_arb_ctrl.adc_arb_fix_priority = 0;
	} else {  // Shield arbiter.
		APB_SARADC->apb_adc_arb_ctrl.adc_arb_grant_force = 1;
	}
}

void adc_ll_set_arbiter_priority(uint8_t pri_rtc, uint8_t pri_dig, uint8_t pri_pwdet) {
	if (pri_rtc != pri_dig && pri_rtc != pri_pwdet && pri_dig != pri_pwdet) {
		APB_SARADC->apb_adc_arb_ctrl.adc_arb_rtc_priority = pri_rtc;
		APB_SARADC->apb_adc_arb_ctrl.adc_arb_apb_priority = pri_dig;
		APB_SARADC->apb_adc_arb_ctrl.adc_arb_wifi_priority = pri_pwdet;
	}
	/* Should select highest priority controller. */
	if (pri_rtc > pri_dig) {
		if (pri_rtc > pri_pwdet) {
			APB_SARADC->apb_adc_arb_ctrl.adc_arb_apb_force = 0;
			APB_SARADC->apb_adc_arb_ctrl.adc_arb_rtc_force = 1;
			APB_SARADC->apb_adc_arb_ctrl.adc_arb_wifi_force = 0;
		} else {
			APB_SARADC->apb_adc_arb_ctrl.adc_arb_apb_force = 0;
			APB_SARADC->apb_adc_arb_ctrl.adc_arb_rtc_force = 0;
			APB_SARADC->apb_adc_arb_ctrl.adc_arb_wifi_force = 1;
		}
	} else {
		if (pri_dig > pri_pwdet) {
			APB_SARADC->apb_adc_arb_ctrl.adc_arb_apb_force = 1;
			APB_SARADC->apb_adc_arb_ctrl.adc_arb_rtc_force = 0;
			APB_SARADC->apb_adc_arb_ctrl.adc_arb_wifi_force = 0;
		} else {
			APB_SARADC->apb_adc_arb_ctrl.adc_arb_apb_force = 0;
			APB_SARADC->apb_adc_arb_ctrl.adc_arb_rtc_force = 0;
			APB_SARADC->apb_adc_arb_ctrl.adc_arb_wifi_force = 1;
		}
	}
}

void adc_ll_enable_sleep_controller(void) {
	SENS->sar_meas2_mux.sar2_rtc_force = 1;
}

void adc_ll_disable_sleep_controller(void) {
	SENS->sar_meas2_mux.sar2_rtc_force = 0;
}

void adc_ll_calibration_init(adc_ll_num_t adc_n) {
	if (adc_n == ADC_NUM_1) {
		REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_DREF_ADDR, 4);
	} else {
		REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_DREF_ADDR, 4);
	}
}

void adc_ll_calibration_prepare(adc_ll_num_t adc_n, adc_channel_t channel, bool internal_gnd) {
	/* Should be called before writing I2C registers. */
	*((volatile int*)RTC_CNTL_ANA_CONF_REG) |= RTC_CNTL_SAR_I2C_PU_M;
	*((volatile int*)ANA_CONFIG_REG) ^= I2C_SAR_M;
	*((volatile int*)ANA_CONFIG2_REG) |= ANA_SAR_CFG2_M;

	/* Enable/disable internal connect GND (for calibration). */
	if (adc_n == ADC_NUM_1) {
		if (internal_gnd) {
			REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_ENCAL_GND_ADDR, 1);
		} else {
			REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_ENCAL_GND_ADDR, 0);
		}
	} else {    //adc_n == ADC_NUM_2
		if (internal_gnd) {
			REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_ENCAL_GND_ADDR, 1);
		} else {
			REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_ENCAL_GND_ADDR, 0);
		}
	}
}

void adc_ll_calibration_finish(adc_ll_num_t adc_n) {
	if (adc_n == ADC_NUM_1) {
		REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_ENCAL_GND_ADDR, 0);
	} else {    //adc_n == ADC_NUM_2
		REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_ENCAL_GND_ADDR, 0);
	}
}

void adc_ll_set_calibration_param(adc_ll_num_t adc_n, uint32_t param) {
	uint8_t msb = param >> 8;
	uint8_t lsb = param & 0xFF;
	if (adc_n == ADC_NUM_1) {
		REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_INITIAL_CODE_HIGH_ADDR, msb);
		REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_INITIAL_CODE_LOW_ADDR, lsb);
	} else {
		REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_INITIAL_CODE_HIGH_ADDR, msb);
		REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_INITIAL_CODE_LOW_ADDR, lsb);
	}
}

void adc_ll_vref_output(adc_ll_num_t adc, adc_channel_t channel, bool en) {
	abort();
}

void adc_ll_set_sar_clk_div(adc_ll_num_t adc_n, uint32_t div) {
	if (adc_n == ADC_NUM_1) {
		HAL_FORCE_MODIFY_U32_REG_FIELD(SENS->sar_reader1_ctrl, sar1_clk_div, div);
	} else { // adc_n == ADC_NUM_2
		HAL_FORCE_MODIFY_U32_REG_FIELD(SENS->sar_reader2_ctrl, sar2_clk_div, div);
	}
}

void adc_ll_rtc_set_output_format(adc_ll_num_t adc_n, adc_bits_width_t bits) {

}

void adc_ll_rtc_enable_channel(adc_ll_num_t adc_n, int channel) {
	if (adc_n == ADC_NUM_1) {
		SENS->sar_meas1_ctrl2.sar1_en_pad = (1 << channel); //only one channel is selected.
	} else { // adc_n == ADC_NUM_2
		SENS->sar_meas2_ctrl2.sar2_en_pad = (1 << channel); //only one channel is selected.
	}
}

void adc_ll_rtc_disable_channel(adc_ll_num_t adc_n) {
	if (adc_n == ADC_NUM_1) {
		SENS->sar_meas1_ctrl2.sar1_en_pad = 0; //only one channel is selected.
	} else { // adc_n == ADC_NUM_2
		SENS->sar_meas2_ctrl2.sar2_en_pad = 0; //only one channel is selected.
	}
}

void adc_ll_rtc_start_convert(adc_ll_num_t adc_n, int channel) {
	if (adc_n == ADC_NUM_1) {
		while (HAL_FORCE_READ_U32_REG_FIELD(SENS->sar_slave_addr1, meas_status) != 0) {}
		SENS->sar_meas1_ctrl2.meas1_start_sar = 0;
		SENS->sar_meas1_ctrl2.meas1_start_sar = 1;
	} else { // adc_n == ADC_NUM_2
		SENS->sar_meas2_ctrl2.meas2_start_sar = 0; //start force 0
		SENS->sar_meas2_ctrl2.meas2_start_sar = 1; //start force 1
	}
}

bool adc_ll_rtc_convert_is_done(adc_ll_num_t adc_n) {
	bool ret = true;
	if (adc_n == ADC_NUM_1) {
		ret = (bool)SENS->sar_meas1_ctrl2.meas1_done_sar;
	} else { // adc_n == ADC_NUM_2
		ret = (bool)SENS->sar_meas2_ctrl2.meas2_done_sar;
	}
	return ret;
}

int adc_ll_rtc_get_convert_value(adc_ll_num_t adc_n) {
	int ret_val = 0;
	if (adc_n == ADC_NUM_1) {
		ret_val = HAL_FORCE_READ_U32_REG_FIELD(SENS->sar_meas1_ctrl2, meas1_data_sar);
	} else { // adc_n == ADC_NUM_2
		ret_val = HAL_FORCE_READ_U32_REG_FIELD(SENS->sar_meas2_ctrl2, meas2_data_sar);
	}
	return ret_val;
}

void adc_ll_rtc_output_invert(adc_ll_num_t adc_n, bool inv_en) {
	if (adc_n == ADC_NUM_1) {
		SENS->sar_reader1_ctrl.sar1_data_inv = inv_en;   // Enable / Disable ADC data invert
	} else { // adc_n == ADC_NUM_2
		SENS->sar_reader2_ctrl.sar2_data_inv = inv_en;  // Enable / Disable ADC data invert
	}
}

void adc_ll_rtc_intr_enable(adc_ll_num_t adc_n) {
	if (adc_n == ADC_NUM_1) {
		SENS->sar_reader1_ctrl.sar1_int_en = 1;
		RTCCNTL->int_ena.rtc_saradc1 = 1;
	} else { // adc_n == ADC_NUM_2
		SENS->sar_reader2_ctrl.sar2_int_en = 1;
		RTCCNTL->int_ena.rtc_saradc2 = 1;
	}
}

void adc_ll_rtc_intr_disable(adc_ll_num_t adc_n) {
	if (adc_n == ADC_NUM_1) {
		SENS->sar_reader1_ctrl.sar1_int_en = 0;
		RTCCNTL->int_ena.rtc_saradc1 = 0;
	} else { // adc_n == ADC_NUM_2
		SENS->sar_reader2_ctrl.sar2_int_en = 0;
		RTCCNTL->int_ena.rtc_saradc2 = 0;
	}
}

void adc_ll_rtc_reset(void) {
	SENS->sar_peri_reset_conf.saradc_reset = 1;
	SENS->sar_peri_reset_conf.saradc_reset = 0;
}

void adc_ll_rtc_set_arbiter_stable_cycle(uint32_t cycle) {
	SENS->sar_reader2_ctrl.sar2_wait_arb_cycle = cycle;
}

adc_ll_rtc_raw_data_t adc_ll_rtc_analysis_raw_data(adc_ll_num_t adc_n, uint16_t raw_data) {
	/* ADC1 don't need check data */
	if (adc_n == ADC_NUM_1) {
		return ADC_RTC_DATA_OK;
	}
	adc_ll_rtc_output_data_t *temp = (adc_ll_rtc_output_data_t *)&raw_data;
	if (temp->flag == 0) {
		return ADC_RTC_DATA_OK;
	} else if (temp->flag == 1) {
		return ADC_RTC_CTRL_UNSELECTED;
	} else if (temp->flag == 2) {
		return ADC_RTC_CTRL_BREAK;
	} else {
		return ADC_RTC_DATA_FAIL;
	}
}

void adc_ll_set_atten(adc_ll_num_t adc_n, adc_channel_t channel, adc_atten_t atten) {
	if (adc_n == ADC_NUM_1) {
		SENS->sar_atten1 = ( SENS->sar_atten1 & ~(0x3 << (channel * 2)) ) | ((atten & 0x3) << (channel * 2));
	} else { // adc_n == ADC_NUM_2
		SENS->sar_atten2 = ( SENS->sar_atten2 & ~(0x3 << (channel * 2)) ) | ((atten & 0x3) << (channel * 2));
	}
}

adc_atten_t adc_ll_get_atten(adc_ll_num_t adc_n, adc_channel_t channel) {
	if (adc_n == ADC_NUM_1) {
		return (adc_atten_t)((SENS->sar_atten1 >> (channel * 2)) & 0x3);
	} else {
		return (adc_atten_t)((SENS->sar_atten2 >> (channel * 2)) & 0x3);
	}
}

uint32_t adc_ll_adc1_read(void)
{
	//On ESP32S3, valid data width is 12-bit
	return (APB_SARADC->apb_saradc1_data_status.adc1_data & 0xfff);
}

uint32_t adc_ll_adc2_read(void)
{
	//On ESP32S3, valid data width is 12-bit
	return (APB_SARADC->apb_saradc2_data_status.adc2_data & 0xfff);
}
