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

void touch_ll_set_meas_times(uint16_t meas_time);
void touch_ll_get_measure_times(uint16_t *meas_time);
void touch_ll_set_sleep_time(uint16_t sleep_time);
void touch_ll_get_sleep_time(uint16_t *sleep_time);
void touch_ll_set_voltage_high(touch_high_volt_t refh);
void touch_ll_get_voltage_high(touch_high_volt_t *refh);
void touch_ll_set_voltage_low(touch_low_volt_t refl);
void touch_ll_get_voltage_low(touch_low_volt_t *refl);
void touch_ll_set_voltage_attenuation(touch_volt_atten_t atten);
void touch_ll_get_voltage_attenuation(touch_volt_atten_t *atten);
void touch_ll_set_slope(touch_pad_t touch_num, touch_cnt_slope_t slope);
void touch_ll_get_slope(touch_pad_t touch_num, touch_cnt_slope_t *slope);
void touch_ll_set_tie_option(touch_pad_t touch_num, touch_tie_opt_t opt);
void touch_ll_get_tie_option(touch_pad_t touch_num, touch_tie_opt_t *opt);
void touch_ll_set_fsm_mode(touch_fsm_mode_t mode);
void touch_ll_get_fsm_mode(touch_fsm_mode_t *mode);
void touch_ll_clkgate(bool enable);
bool touch_ll_clkgate_get_state(void);
void touch_ll_timer_force_done(void);
void touch_ll_start_fsm(void);
void touch_ll_stop_fsm(void);
bool touch_ll_get_fsm_state(void);
void touch_ll_start_sw_meas(void);
void touch_ll_set_threshold(touch_pad_t touch_num, uint32_t threshold);
void touch_ll_get_threshold(touch_pad_t touch_num, uint32_t *threshold);
void touch_ll_set_channel_mask(uint16_t enable_mask);
void touch_ll_get_channel_mask(uint16_t *enable_mask);
void touch_ll_clear_channel_mask(uint16_t disable_mask);
void touch_ll_read_trigger_status_mask(uint32_t *status_mask);
void touch_ll_clear_trigger_status_mask(void);
uint32_t IRAM_ATTR touch_ll_read_raw_data(touch_pad_t touch_num);
bool touch_ll_meas_is_done(void);
void touch_ll_reset(void);
void touch_ll_set_idle_channel_connect(touch_pad_conn_type_t type);
void touch_ll_get_idle_channel_connect(touch_pad_conn_type_t *type);
touch_pad_t IRAM_ATTR touch_ll_get_current_meas_channel(void);
void touch_ll_intr_enable(touch_pad_intr_mask_t int_mask);
void touch_ll_intr_disable(touch_pad_intr_mask_t int_mask);
void touch_ll_intr_clear(touch_pad_intr_mask_t int_mask);
uint32_t touch_ll_read_intr_status_mask(void);
void touch_ll_timeout_enable(void);
void touch_ll_timeout_disable(void);
void touch_ll_timeout_set_threshold(uint32_t threshold);
void touch_ll_timeout_get_threshold(uint32_t *threshold);
void IRAM_ATTR touch_ll_filter_read_smooth(touch_pad_t touch_num, uint32_t *smooth_data);
void IRAM_ATTR touch_ll_read_benchmark(touch_pad_t touch_num, uint32_t *benchmark);
void touch_ll_reset_benchmark(touch_pad_t touch_num);
void touch_ll_filter_set_filter_mode(touch_filter_mode_t mode);
void touch_ll_filter_get_filter_mode(touch_filter_mode_t *mode);
void touch_ll_filter_set_smooth_mode(touch_smooth_mode_t mode);
void touch_ll_filter_get_smooth_mode(touch_smooth_mode_t *mode);
void touch_ll_filter_set_debounce(uint32_t dbc_cnt);
void touch_ll_filter_get_debounce(uint32_t *dbc_cnt);
void touch_ll_filter_set_noise_thres(uint32_t noise_thr);
void touch_ll_filter_get_noise_thres(uint32_t *noise_thr);
void touch_ll_filter_set_jitter_step(uint32_t step);
void touch_ll_filter_get_jitter_step(uint32_t *step);
void touch_ll_filter_enable(void);
void touch_ll_filter_disable(void);
void touch_ll_denoise_enable(void);
void touch_ll_denoise_disable(void);
void touch_ll_denoise_set_cap_level(touch_pad_denoise_cap_t cap_level);
void touch_ll_denoise_get_cap_level(touch_pad_denoise_cap_t *cap_level);
void touch_ll_denoise_set_grade(touch_pad_denoise_grade_t grade);
void touch_ll_denoise_get_grade(touch_pad_denoise_grade_t *grade);
void touch_ll_denoise_read_data(uint32_t *data);
void touch_ll_waterproof_set_guard_pad(touch_pad_t pad_num);
void touch_ll_waterproof_get_guard_pad(touch_pad_t *pad_num);
void touch_ll_waterproof_set_sheild_driver(touch_pad_shield_driver_t driver_level);
void touch_ll_waterproof_get_sheild_driver(touch_pad_shield_driver_t *driver_level);
void touch_ll_waterproof_enable(void);
void touch_ll_waterproof_disable(void);
void touch_ll_proximity_set_channel_num(const touch_pad_t prox_pad[]);
void touch_ll_proximity_get_channel_num(touch_pad_t prox_pad[]);
void touch_ll_proximity_set_meas_times(uint32_t times);
void touch_ll_proximity_get_meas_times(uint32_t *times);
void touch_ll_proximity_read_meas_cnt(touch_pad_t touch_num, uint32_t *cnt);
bool touch_ll_proximity_pad_check(touch_pad_t touch_num);
void touch_ll_sleep_set_channel_num(touch_pad_t touch_num);
void touch_ll_sleep_get_channel_num(touch_pad_t *touch_num);
void touch_ll_sleep_set_threshold(uint32_t touch_thres);
void touch_ll_sleep_get_threshold(uint32_t *touch_thres);
void touch_ll_sleep_enable_approach(void);
void touch_ll_sleep_disable_approach(void);
bool touch_ll_sleep_get_approach_status(void);
void touch_ll_sleep_read_benchmark(uint32_t *benchmark);
void touch_ll_sleep_read_smooth(uint32_t *smooth_data);
void touch_ll_sleep_read_data(uint32_t *raw_data);
void touch_ll_sleep_reset_benchmark(void);
void touch_ll_sleep_low_power(bool is_low_power);
void touch_ll_sleep_read_debounce(uint32_t *debounce);
void touch_ll_sleep_read_proximity_cnt(uint32_t *approach_cnt);
void touch_ll_get_wakeup_status(touch_pad_t *pad_num);
