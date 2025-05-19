#include "hal/touch_sensor_ll.h"
#include "hal/touch_sensor_types.h"

#define touch_hal_reset()                                    touch_ll_reset()
#define touch_hal_set_meas_times(meas_time)                  touch_ll_set_meas_times(meas_time)
#define touch_hal_get_measure_times(meas_time)               touch_ll_get_measure_times(meas_time)
#define touch_hal_set_idle_channel_connect(type)             touch_ll_set_idle_channel_connect(type)
#define touch_hal_get_idle_channel_connect(type)             touch_ll_get_idle_channel_connect(type)
#define touch_hal_get_current_meas_channel()                 touch_ll_get_current_meas_channel()
#define touch_hal_intr_enable(int_mask)                      touch_ll_intr_enable(int_mask)
#define touch_hal_intr_disable(int_mask)                     touch_ll_intr_disable(int_mask)
#define touch_hal_intr_clear(int_mask)                       touch_ll_intr_clear(int_mask)
#define touch_hal_read_intr_status_mask()                    touch_ll_read_intr_status_mask()
#define touch_hal_timeout_enable()                           touch_ll_timeout_enable()
#define touch_hal_timeout_disable()                          touch_ll_timeout_disable()
#define touch_hal_timeout_set_threshold(threshold)           touch_ll_timeout_set_threshold(threshold)
#define touch_hal_timeout_get_threshold(threshold)           touch_ll_timeout_get_threshold(threshold)
#define touch_hal_timer_force_done()                         touch_ll_timer_force_done()
#define touch_hal_filter_read_smooth(touch_num, smooth_data) touch_ll_filter_read_smooth(touch_num, smooth_data)
#define touch_hal_read_benchmark(touch_num, benchmark)       touch_ll_read_benchmark(touch_num, benchmark)
#define touch_hal_reset_benchmark(touch_num)                 touch_ll_reset_benchmark(touch_num)
#define touch_hal_filter_set_filter_mode(mode)               touch_ll_filter_set_filter_mode(mode)
#define touch_hal_filter_get_filter_mode(mode)               touch_ll_filter_get_filter_mode(mode)
#define touch_hal_filter_set_debounce(dbc_cnt)               touch_ll_filter_set_debounce(dbc_cnt)
#define touch_hal_filter_get_debounce(dbc_cnt)               touch_ll_filter_get_debounce(dbc_cnt)
#define touch_hal_filter_set_noise_thres(noise_thr)          touch_ll_filter_set_noise_thres(noise_thr)
#define touch_hal_filter_get_noise_thres(noise_thr)          touch_ll_filter_get_noise_thres(noise_thr)
#define touch_hal_filter_set_benchmark_reset(reset_cnt)      touch_ll_filter_set_benchmark_reset(reset_cnt)
#define touch_hal_filter_get_benchmark_reset(reset_cnt)      touch_ll_filter_get_benchmark_reset(reset_cnt)
#define touch_hal_filter_set_jitter_step(step)               touch_ll_filter_set_jitter_step(step)
#define touch_hal_filter_get_jitter_step(step)               touch_ll_filter_get_jitter_step(step)
#define touch_hal_filter_enable()                            touch_ll_filter_enable()
#define touch_hal_filter_disable()                           touch_ll_filter_disable()
#define touch_hal_denoise_disable()                          touch_ll_denoise_disable()
#define touch_hal_denoise_set_cap_level(cap_level)           touch_ll_denoise_set_cap_level(cap_level)
#define touch_hal_denoise_get_cap_level(cap_level)           touch_ll_denoise_get_cap_level(cap_level)
#define touch_hal_denoise_set_grade(grade)                   touch_ll_denoise_set_grade(grade)
#define touch_hal_denoise_get_grade(grade)                   touch_ll_denoise_get_grade(grade)
#define touch_hal_denoise_read_data(data)                    touch_ll_denoise_read_data(data)
#define touch_hal_waterproof_set_guard_pad(pad_num)          touch_ll_waterproof_set_guard_pad(pad_num)
#define touch_hal_waterproof_get_guard_pad(pad_num)          touch_ll_waterproof_get_guard_pad(pad_num)
#define touch_hal_waterproof_set_sheild_driver(driver_level) touch_ll_waterproof_set_sheild_driver(driver_level)
#define touch_hal_waterproof_get_sheild_driver(driver_level) touch_ll_waterproof_get_sheild_driver(driver_level)
#define touch_hal_waterproof_disable()                       touch_ll_waterproof_disable()
#define touch_hal_proximity_set_channel_num(prox_pad)        touch_ll_proximity_set_channel_num(prox_pad)
#define touch_hal_proximity_get_channel_num(prox_pad)        touch_ll_proximity_get_channel_num(prox_pad)
#define touch_hal_proximity_set_meas_times(times)            touch_ll_proximity_set_meas_times(times)
#define touch_hal_proximity_get_meas_times(times)            touch_ll_proximity_get_meas_times(times)
#define touch_hal_proximity_read_meas_cnt(touch_num, cnt)    touch_ll_proximity_read_meas_cnt(touch_num, cnt)
#define touch_hal_proximity_pad_check(touch_num)             touch_ll_proximity_pad_check(touch_num)
#define touch_hal_sleep_set_channel_num(touch_num)           touch_ll_sleep_set_channel_num(touch_num)
#define touch_hal_sleep_get_channel_num(touch_num)           touch_ll_sleep_get_channel_num(touch_num)
#define touch_hal_sleep_set_threshold(touch_thres)           touch_ll_sleep_set_threshold(touch_thres)
#define touch_hal_sleep_get_threshold(touch_thres)           touch_ll_sleep_get_threshold(touch_thres)
#define touch_hal_sleep_enable_approach()                    touch_ll_sleep_enable_approach()
#define touch_hal_sleep_disable_approach()                   touch_ll_sleep_disable_approach()
#define touch_hal_sleep_read_benchmark(benchmark)            touch_ll_sleep_read_benchmark(benchmark)
#define touch_hal_sleep_read_smooth(smooth_data)             touch_ll_sleep_read_smooth(smooth_data)
#define touch_hal_sleep_read_data(raw_data)                  touch_ll_sleep_read_data(raw_data)
#define touch_hal_sleep_reset_benchmark()                    touch_ll_sleep_reset_benchmark()
#define touch_hal_sleep_read_debounce(debounce)              touch_ll_sleep_read_debounce(debounce)
#define touch_hal_sleep_read_proximity_cnt(approach_cnt)     touch_ll_sleep_read_proximity_cnt(approach_cnt)
#define touch_hal_get_wakeup_status(pad_num)                 touch_ll_get_wakeup_status(pad_num)

void touch_hal_filter_set_config(const touch_filter_config_t *filter_info);
void touch_hal_filter_get_config(touch_filter_config_t *filter_info);
void touch_hal_denoise_set_config(const touch_pad_denoise_t *denoise);
void touch_hal_denoise_get_config(touch_pad_denoise_t *denoise);
void touch_hal_denoise_enable(void);
void touch_hal_waterproof_set_config(const touch_pad_waterproof_t *waterproof);
void touch_hal_waterproof_get_config(touch_pad_waterproof_t *waterproof);
void touch_hal_waterproof_enable(void);
bool touch_hal_enable_proximity(touch_pad_t touch_num, bool enabled);
void touch_hal_sleep_channel_get_config(touch_pad_sleep_channel_t *slp_config);
void touch_hal_sleep_channel_enable(touch_pad_t pad_num, bool enable);
void touch_hal_sleep_channel_set_work_time(uint16_t sleep_cycle, uint16_t meas_times);
void touch_hal_sleep_channel_get_work_time(uint16_t *sleep_cycle, uint16_t *meas_times);
