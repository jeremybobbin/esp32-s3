

// The Lowlevel layer for Touch Sensor


#include <stdlib.h>
#include <stdbool.h>
#include "hal/misc.h"
#include "soc/touch_sensor_periph.h"
#include "soc/rtc_cntl_struct.h"
#include "soc/rtc_io_struct.h"
#include "soc/sens_struct.h"
#include "soc/soc_caps.h"
#include "hal/touch_sensor_types.h"


#define TOUCH_LL_READ_RAW           0x0
#define TOUCH_LL_READ_BENCHMARK     0x2
#define TOUCH_LL_READ_SMOOTH        0x3
#define TOUCH_LL_TIMER_FORCE_DONE   0x3
#define TOUCH_LL_TIMER_DONE         0x0

void touch_ll_set_meas_times(uint16_t meas_time)
{
	//The times of charge and discharge in each measure process of touch channels.
	HAL_FORCE_MODIFY_U32_REG_FIELD(RTCCNTL.touch_ctrl1, touch_meas_num, meas_time);
	//the waiting cycles (in 8MHz) between TOUCH_START and TOUCH_XPD
	HAL_FORCE_MODIFY_U32_REG_FIELD(RTCCNTL.touch_ctrl2, touch_xpd_wait, SOC_TOUCH_PAD_MEASURE_WAIT_MAX); //wait volt stable
}

void touch_ll_get_measure_times(uint16_t *meas_time)
{
	*meas_time = HAL_FORCE_READ_U32_REG_FIELD(RTCCNTL.touch_ctrl1, touch_meas_num);
}

void touch_ll_set_sleep_time(uint16_t sleep_time)
{
	// touch sensor sleep cycle Time = sleep_cycle / RTC_SLOW_CLK(150k)
	HAL_FORCE_MODIFY_U32_REG_FIELD(RTCCNTL.touch_ctrl1, touch_sleep_cycles, sleep_time);
}

void touch_ll_get_sleep_time(uint16_t *sleep_time)
{
	*sleep_time = HAL_FORCE_READ_U32_REG_FIELD(RTCCNTL.touch_ctrl1, touch_sleep_cycles);
}

void touch_ll_set_voltage_high(touch_high_volt_t refh)
{
	RTCCNTL.touch_ctrl2.touch_drefh = refh;
}

void touch_ll_get_voltage_high(touch_high_volt_t *refh)
{
	*refh = (touch_high_volt_t)RTCCNTL.touch_ctrl2.touch_drefh;
}

void touch_ll_set_voltage_low(touch_low_volt_t refl)
{
	RTCCNTL.touch_ctrl2.touch_drefl = refl;
}

void touch_ll_get_voltage_low(touch_low_volt_t *refl)
{
	*refl = (touch_low_volt_t)RTCCNTL.touch_ctrl2.touch_drefl;
}

void touch_ll_set_voltage_attenuation(touch_volt_atten_t atten)
{
	RTCCNTL.touch_ctrl2.touch_drange = atten;
}

void touch_ll_get_voltage_attenuation(touch_volt_atten_t *atten)
{
	*atten = (touch_volt_atten_t)RTCCNTL.touch_ctrl2.touch_drange;
}

void touch_ll_set_slope(touch_pad_t touch_num, touch_cnt_slope_t slope)
{
	if (touch_num < TOUCH_PAD_NUM10) {
		SET_PERI_REG_BITS(RTC_CNTL_TOUCH_DAC_REG, RTC_CNTL_TOUCH_PAD0_DAC_V, slope, (RTC_CNTL_TOUCH_PAD0_DAC_S - touch_num * 3));
	} else {
		SET_PERI_REG_BITS(RTC_CNTL_TOUCH_DAC1_REG, RTC_CNTL_TOUCH_PAD10_DAC_V, slope, (RTC_CNTL_TOUCH_PAD10_DAC_S - (touch_num - TOUCH_PAD_NUM10) * 3));
	}
}

void touch_ll_get_slope(touch_pad_t touch_num, touch_cnt_slope_t *slope)
{
	if (touch_num < TOUCH_PAD_NUM10) {
		*slope = GET_PERI_REG_BITS2(RTC_CNTL_TOUCH_DAC_REG, RTC_CNTL_TOUCH_PAD0_DAC_V, (RTC_CNTL_TOUCH_PAD0_DAC_S - touch_num * 3));
	} else {
		*slope = GET_PERI_REG_BITS2(RTC_CNTL_TOUCH_DAC1_REG, RTC_CNTL_TOUCH_PAD10_DAC_V, (RTC_CNTL_TOUCH_PAD10_DAC_S - (touch_num - TOUCH_PAD_NUM10) * 3));
	}
}

void touch_ll_set_tie_option(touch_pad_t touch_num, touch_tie_opt_t opt)
{
	RTCIO.touch_pad[touch_num].tie_opt = opt;
}

void touch_ll_get_tie_option(touch_pad_t touch_num, touch_tie_opt_t *opt)
{
	*opt = (touch_tie_opt_t)RTCIO.touch_pad[touch_num].tie_opt;
}

void touch_ll_set_fsm_mode(touch_fsm_mode_t mode)
{
	RTCCNTL.touch_ctrl2.touch_start_force = mode;
}

void touch_ll_get_fsm_mode(touch_fsm_mode_t *mode)
{
	*mode = (touch_fsm_mode_t)RTCCNTL.touch_ctrl2.touch_start_force;
}

void touch_ll_clkgate(bool enable)
{
	RTCCNTL.touch_ctrl2.touch_clkgate_en = enable; //enable touch clock for FSM. or force enable.
}

bool touch_ll_clkgate_get_state(void)
{
	return RTCCNTL.touch_ctrl2.touch_clkgate_en;
}

void touch_ll_timer_force_done(void)
{
	RTCCNTL.touch_ctrl2.touch_timer_force_done = TOUCH_LL_TIMER_FORCE_DONE;
	RTCCNTL.touch_ctrl2.touch_timer_force_done = TOUCH_LL_TIMER_DONE;
}

void touch_ll_start_fsm(void)
{
	/**
	 * Touch timer trigger measurement and always wait measurement done.
	 * Force done for touch timer ensures that the timer always can get the measurement done signal.
	 */
	RTCCNTL.touch_ctrl2.touch_timer_force_done = TOUCH_LL_TIMER_FORCE_DONE;
	RTCCNTL.touch_ctrl2.touch_timer_force_done = TOUCH_LL_TIMER_DONE;
	RTCCNTL.touch_ctrl2.touch_slp_timer_en = (RTCCNTL.touch_ctrl2.touch_start_force == TOUCH_FSM_MODE_TIMER ? 1 : 0);
}

void touch_ll_stop_fsm(void)
{
	RTCCNTL.touch_ctrl2.touch_start_en = 0; //stop touch fsm
	RTCCNTL.touch_ctrl2.touch_slp_timer_en = 0;
	RTCCNTL.touch_ctrl2.touch_timer_force_done = TOUCH_LL_TIMER_FORCE_DONE;
	RTCCNTL.touch_ctrl2.touch_timer_force_done = TOUCH_LL_TIMER_DONE;
}

bool touch_ll_get_fsm_state(void)
{
	return (bool)RTCCNTL.touch_ctrl2.touch_slp_timer_en;
}

void touch_ll_start_sw_meas(void)
{
	RTCCNTL.touch_ctrl2.touch_start_en = 0;
	RTCCNTL.touch_ctrl2.touch_start_en = 1;
}

void touch_ll_set_threshold(touch_pad_t touch_num, uint32_t threshold)
{
	SENS.touch_thresh[touch_num - 1].thresh = threshold;
}

void touch_ll_get_threshold(touch_pad_t touch_num, uint32_t *threshold)
{
	*threshold = SENS.touch_thresh[touch_num - 1].thresh;
}

void touch_ll_set_channel_mask(uint16_t enable_mask)
{
	RTCCNTL.touch_scan_ctrl.touch_scan_pad_map  |= (enable_mask & TOUCH_PAD_BIT_MASK_ALL);
	SENS.sar_touch_conf.touch_outen |= (enable_mask & TOUCH_PAD_BIT_MASK_ALL);
}

void touch_ll_get_channel_mask(uint16_t *enable_mask)
{
	*enable_mask = SENS.sar_touch_conf.touch_outen \
				   & RTCCNTL.touch_scan_ctrl.touch_scan_pad_map \
				   & TOUCH_PAD_BIT_MASK_ALL;
}

void touch_ll_clear_channel_mask(uint16_t disable_mask)
{
	SENS.sar_touch_conf.touch_outen &= ~(disable_mask & TOUCH_PAD_BIT_MASK_ALL);
	RTCCNTL.touch_scan_ctrl.touch_scan_pad_map  &= ~(disable_mask & TOUCH_PAD_BIT_MASK_ALL);
}

void touch_ll_read_trigger_status_mask(uint32_t *status_mask)
{
	*status_mask = SENS.sar_touch_chn_st.touch_pad_active;
}

void touch_ll_clear_trigger_status_mask(void)
{
	SENS.sar_touch_conf.touch_status_clr = 1;
}

uint32_t IRAM_ATTR touch_ll_read_raw_data(touch_pad_t touch_num)
{
	SENS.sar_touch_conf.touch_data_sel = TOUCH_LL_READ_RAW;
	return SENS.sar_touch_status[touch_num - 1].touch_pad_data;
}

bool touch_ll_meas_is_done(void)
{
	return (bool)SENS.sar_touch_chn_st.touch_meas_done;
}

void touch_ll_reset(void)
{
	RTCCNTL.touch_ctrl2.touch_reset = 0;
	RTCCNTL.touch_ctrl2.touch_reset = 1;
	RTCCNTL.touch_ctrl2.touch_reset = 0;    // Should be set 0.
}

void touch_ll_set_idle_channel_connect(touch_pad_conn_type_t type)
{
	RTCCNTL.touch_scan_ctrl.touch_inactive_connection = type;
}

void touch_ll_get_idle_channel_connect(touch_pad_conn_type_t *type)
{
	*type = RTCCNTL.touch_scan_ctrl.touch_inactive_connection;
}

touch_pad_t IRAM_ATTR touch_ll_get_current_meas_channel(void)
{
	return (touch_pad_t)(SENS.sar_touch_status0.touch_scan_curr);
}

void touch_ll_intr_enable(touch_pad_intr_mask_t int_mask)
{
	if (int_mask & TOUCH_PAD_INTR_MASK_DONE) {
		RTCCNTL.int_ena_w1ts.rtc_touch_done_w1ts = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_ACTIVE) {
		RTCCNTL.int_ena_w1ts.rtc_touch_active_w1ts = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_INACTIVE) {
		RTCCNTL.int_ena_w1ts.rtc_touch_inactive_w1ts = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_SCAN_DONE) {
		RTCCNTL.int_ena_w1ts.rtc_touch_scan_done_w1ts = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_TIMEOUT) {
		RTCCNTL.int_ena_w1ts.rtc_touch_timeout_w1ts = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_PROXI_MEAS_DONE) {
		RTCCNTL.int_ena_w1ts.rtc_touch_approach_loop_done_w1ts = 1;
	}
}

void touch_ll_intr_disable(touch_pad_intr_mask_t int_mask)
{
	if (int_mask & TOUCH_PAD_INTR_MASK_DONE) {
		RTCCNTL.int_ena_w1tc.rtc_touch_done_w1tc = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_ACTIVE) {
		RTCCNTL.int_ena_w1tc.rtc_touch_active_w1tc = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_INACTIVE) {
		RTCCNTL.int_ena_w1tc.rtc_touch_inactive_w1tc = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_SCAN_DONE) {
		RTCCNTL.int_ena_w1tc.rtc_touch_scan_done_w1tc = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_TIMEOUT) {
		RTCCNTL.int_ena_w1tc.rtc_touch_timeout_w1tc = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_PROXI_MEAS_DONE) {
		RTCCNTL.int_ena_w1tc.rtc_touch_approach_loop_done_w1tc = 1;
	}
}

void touch_ll_intr_clear(touch_pad_intr_mask_t int_mask)
{
	if (int_mask & TOUCH_PAD_INTR_MASK_DONE) {
		RTCCNTL.int_clr.rtc_touch_done = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_ACTIVE) {
		RTCCNTL.int_clr.rtc_touch_active = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_INACTIVE) {
		RTCCNTL.int_clr.rtc_touch_inactive = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_SCAN_DONE) {
		RTCCNTL.int_clr.rtc_touch_scan_done = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_TIMEOUT) {
		RTCCNTL.int_clr.rtc_touch_timeout = 1;
	}
	if (int_mask & TOUCH_PAD_INTR_MASK_PROXI_MEAS_DONE) {
		RTCCNTL.int_clr.rtc_touch_approach_loop_done = 1;
	}
}

uint32_t touch_ll_read_intr_status_mask(void)
{
	uint32_t intr_st = RTCCNTL.int_st.val;
	uint32_t intr_msk = 0;

	if (intr_st & RTC_CNTL_TOUCH_DONE_INT_ST_M) {
		intr_msk |= TOUCH_PAD_INTR_MASK_DONE;
	}
	if (intr_st & RTC_CNTL_TOUCH_ACTIVE_INT_ST_M) {
		intr_msk |= TOUCH_PAD_INTR_MASK_ACTIVE;
	}
	if (intr_st & RTC_CNTL_TOUCH_INACTIVE_INT_ST_M) {
		intr_msk |= TOUCH_PAD_INTR_MASK_INACTIVE;
	}
	if (intr_st & RTC_CNTL_TOUCH_SCAN_DONE_INT_ST_M) {
		intr_msk |= TOUCH_PAD_INTR_MASK_SCAN_DONE;
	}
	if (intr_st & RTC_CNTL_TOUCH_TIMEOUT_INT_ST_M) {
		intr_msk |= TOUCH_PAD_INTR_MASK_TIMEOUT;
	}
	if (intr_st & RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ST_M) {
		intr_msk |= TOUCH_PAD_INTR_MASK_PROXI_MEAS_DONE;
	}
	return (intr_msk & TOUCH_PAD_INTR_MASK_ALL);
}

void touch_ll_timeout_enable(void)
{
	RTCCNTL.touch_timeout_ctrl.touch_timeout_en = 1;
}

void touch_ll_timeout_disable(void)
{
	RTCCNTL.touch_timeout_ctrl.touch_timeout_en = 0;
}

void touch_ll_timeout_set_threshold(uint32_t threshold)
{
	RTCCNTL.touch_timeout_ctrl.touch_timeout_num = threshold;
}

void touch_ll_timeout_get_threshold(uint32_t *threshold)
{
	*threshold = RTCCNTL.touch_timeout_ctrl.touch_timeout_num;
}

void IRAM_ATTR touch_ll_filter_read_smooth(touch_pad_t touch_num, uint32_t *smooth_data)
{
	SENS.sar_touch_conf.touch_data_sel = TOUCH_LL_READ_SMOOTH;
	*smooth_data = SENS.sar_touch_status[touch_num - 1].touch_pad_data;
}

void IRAM_ATTR touch_ll_read_benchmark(touch_pad_t touch_num, uint32_t *benchmark)
{
	SENS.sar_touch_conf.touch_data_sel = TOUCH_LL_READ_BENCHMARK;
	*benchmark = SENS.sar_touch_status[touch_num - 1].touch_pad_data;
}

void touch_ll_reset_benchmark(touch_pad_t touch_num)
{
	/* Clear touch channels to initialize the channel value (benchmark, raw_data).
	 */
	if (touch_num == TOUCH_PAD_MAX) {
		SENS.sar_touch_chn_st.touch_channel_clr = TOUCH_PAD_BIT_MASK_ALL;
	} else {
		SENS.sar_touch_chn_st.touch_channel_clr = (1U << touch_num);
	}
}

void touch_ll_filter_set_filter_mode(touch_filter_mode_t mode)
{
	RTCCNTL.touch_filter_ctrl.touch_filter_mode = mode;
}

void touch_ll_filter_get_filter_mode(touch_filter_mode_t *mode)
{
	*mode = (touch_filter_mode_t)RTCCNTL.touch_filter_ctrl.touch_filter_mode;
}

void touch_ll_filter_set_smooth_mode(touch_smooth_mode_t mode)
{
	RTCCNTL.touch_filter_ctrl.touch_smooth_lvl = mode;
}

void touch_ll_filter_get_smooth_mode(touch_smooth_mode_t *mode)
{
	*mode = RTCCNTL.touch_filter_ctrl.touch_smooth_lvl;
}

void touch_ll_filter_set_debounce(uint32_t dbc_cnt)
{
	RTCCNTL.touch_filter_ctrl.touch_debounce = dbc_cnt;
}

void touch_ll_filter_get_debounce(uint32_t *dbc_cnt)
{
	*dbc_cnt = RTCCNTL.touch_filter_ctrl.touch_debounce;
}

void touch_ll_filter_set_noise_thres(uint32_t noise_thr)
{
	RTCCNTL.touch_filter_ctrl.touch_noise_thres = noise_thr;
	RTCCNTL.touch_filter_ctrl.config2 = noise_thr;
	RTCCNTL.touch_filter_ctrl.config1 = 0xF;
	RTCCNTL.touch_filter_ctrl.config3 = 2;
}

void touch_ll_filter_get_noise_thres(uint32_t *noise_thr)
{
	*noise_thr = RTCCNTL.touch_filter_ctrl.touch_noise_thres;
}

void touch_ll_filter_set_jitter_step(uint32_t step)
{
	RTCCNTL.touch_filter_ctrl.touch_jitter_step = step;
}

void touch_ll_filter_get_jitter_step(uint32_t *step)
{
	*step = RTCCNTL.touch_filter_ctrl.touch_jitter_step;
}

void touch_ll_filter_enable(void)
{
	RTCCNTL.touch_filter_ctrl.touch_filter_en = 1;
}

void touch_ll_filter_disable(void)
{
	RTCCNTL.touch_filter_ctrl.touch_filter_en = 0;
}

void touch_ll_denoise_enable(void)
{
	RTCCNTL.touch_scan_ctrl.touch_denoise_en = 1;
}

void touch_ll_denoise_disable(void)
{
	RTCCNTL.touch_scan_ctrl.touch_denoise_en = 0;
}

void touch_ll_denoise_set_cap_level(touch_pad_denoise_cap_t cap_level)
{
	RTCCNTL.touch_ctrl2.touch_refc = cap_level;
}

void touch_ll_denoise_get_cap_level(touch_pad_denoise_cap_t *cap_level)
{
	*cap_level = RTCCNTL.touch_ctrl2.touch_refc;
}

void touch_ll_denoise_set_grade(touch_pad_denoise_grade_t grade)
{
	RTCCNTL.touch_scan_ctrl.touch_denoise_res = grade;
}

void touch_ll_denoise_get_grade(touch_pad_denoise_grade_t *grade)
{
	*grade = RTCCNTL.touch_scan_ctrl.touch_denoise_res;
}

void touch_ll_denoise_read_data(uint32_t *data)
{
	*data =  SENS.sar_touch_denoise.touch_denoise_data;
}

void touch_ll_waterproof_set_guard_pad(touch_pad_t pad_num)
{
	RTCCNTL.touch_scan_ctrl.touch_out_ring = pad_num;
}

void touch_ll_waterproof_get_guard_pad(touch_pad_t *pad_num)
{
	*pad_num = RTCCNTL.touch_scan_ctrl.touch_out_ring;
}

void touch_ll_waterproof_set_sheild_driver(touch_pad_shield_driver_t driver_level)
{
	RTCCNTL.touch_scan_ctrl.touch_bufdrv = driver_level;
}

void touch_ll_waterproof_get_sheild_driver(touch_pad_shield_driver_t *driver_level)
{
	*driver_level = RTCCNTL.touch_scan_ctrl.touch_bufdrv;
}

void touch_ll_waterproof_enable(void)
{
	RTCCNTL.touch_scan_ctrl.touch_shield_pad_en = 1;
}

void touch_ll_waterproof_disable(void)
{
	RTCCNTL.touch_scan_ctrl.touch_shield_pad_en = 0;
}

void touch_ll_proximity_set_channel_num(const touch_pad_t prox_pad[])
{
	SENS.sar_touch_conf.touch_approach_pad0 = prox_pad[0];
	SENS.sar_touch_conf.touch_approach_pad1 = prox_pad[1];
	SENS.sar_touch_conf.touch_approach_pad2 = prox_pad[2];
}

void touch_ll_proximity_get_channel_num(touch_pad_t prox_pad[])
{
	prox_pad[0] = SENS.sar_touch_conf.touch_approach_pad0;
	prox_pad[1] = SENS.sar_touch_conf.touch_approach_pad1;
	prox_pad[2] = SENS.sar_touch_conf.touch_approach_pad2;
}

void touch_ll_proximity_set_meas_times(uint32_t times)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(RTCCNTL.touch_approach, touch_approach_meas_time, times);
}

void touch_ll_proximity_get_meas_times(uint32_t *times)
{
	*times = HAL_FORCE_READ_U32_REG_FIELD(RTCCNTL.touch_approach, touch_approach_meas_time);
}

void touch_ll_proximity_read_meas_cnt(touch_pad_t touch_num, uint32_t *cnt)
{
	if (SENS.sar_touch_conf.touch_approach_pad0 == touch_num) {
		*cnt = SENS.sar_touch_appr_status.touch_approach_pad0_cnt;
	} else if (SENS.sar_touch_conf.touch_approach_pad1 == touch_num) {
		*cnt = SENS.sar_touch_appr_status.touch_approach_pad1_cnt;
	} else if (SENS.sar_touch_conf.touch_approach_pad2 == touch_num) {
		*cnt = SENS.sar_touch_appr_status.touch_approach_pad2_cnt;
	}
}

bool touch_ll_proximity_pad_check(touch_pad_t touch_num)
{
	if ((SENS.sar_touch_conf.touch_approach_pad0 != touch_num)
			&& (SENS.sar_touch_conf.touch_approach_pad1 != touch_num)
			&& (SENS.sar_touch_conf.touch_approach_pad2 != touch_num)) {
		return false;
	} else {
		return true;
	}
}

void touch_ll_sleep_set_channel_num(touch_pad_t touch_num)
{
	RTCCNTL.touch_slp_thres.touch_slp_pad = touch_num;
}

void touch_ll_sleep_get_channel_num(touch_pad_t *touch_num)
{
	*touch_num = RTCCNTL.touch_slp_thres.touch_slp_pad;
}

void touch_ll_sleep_set_threshold(uint32_t touch_thres)
{
	RTCCNTL.touch_slp_thres.touch_slp_th = touch_thres;
}

void touch_ll_sleep_get_threshold(uint32_t *touch_thres)
{
	*touch_thres = RTCCNTL.touch_slp_thres.touch_slp_th;
}

void touch_ll_sleep_enable_approach(void)
{
	RTCCNTL.touch_slp_thres.touch_slp_approach_en = 1;
}

void touch_ll_sleep_disable_approach(void)
{
	RTCCNTL.touch_slp_thres.touch_slp_approach_en = 0;
}

bool touch_ll_sleep_get_approach_status(void)
{
	return (bool)RTCCNTL.touch_slp_thres.touch_slp_approach_en;
}

void touch_ll_sleep_read_benchmark(uint32_t *benchmark)
{
	SENS.sar_touch_conf.touch_data_sel = TOUCH_LL_READ_BENCHMARK;
	*benchmark = SENS.sar_touch_slp_status.touch_slp_data;
}

void touch_ll_sleep_read_smooth(uint32_t *smooth_data)
{
	SENS.sar_touch_conf.touch_data_sel = TOUCH_LL_READ_SMOOTH;
	*smooth_data = SENS.sar_touch_slp_status.touch_slp_data;
}

void touch_ll_sleep_low_power(bool is_low_power)
{
	RTCCNTL.touch_ctrl2.touch_dbias = is_low_power;
}

void touch_ll_sleep_read_debounce(uint32_t *debounce)
{
	*debounce = SENS.sar_touch_slp_status.touch_slp_debounce;
}

void touch_ll_sleep_read_proximity_cnt(uint32_t *approach_cnt)
{
	*approach_cnt = SENS.sar_touch_appr_status.touch_slp_approach_cnt;
}

void touch_ll_get_wakeup_status(touch_pad_t *pad_num)
{
	*pad_num = (touch_pad_t)RTCCNTL.touch_slp_thres.touch_slp_pad;
}

