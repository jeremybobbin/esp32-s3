#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define TOUCH_LL_READ_RAW           0x0
#define TOUCH_LL_READ_BENCHMARK     0x2
#define TOUCH_LL_READ_SMOOTH        0x3
#define TOUCH_LL_TIMER_FORCE_DONE   0x3
#define TOUCH_LL_TIMER_DONE         0x0

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

typedef enum {
	TOUCH_PAD_NUM0 = 0,
	TOUCH_PAD_NUM1,
	TOUCH_PAD_NUM2,
	TOUCH_PAD_NUM3,
	TOUCH_PAD_NUM4,
	TOUCH_PAD_NUM5,
	TOUCH_PAD_NUM6,
	TOUCH_PAD_NUM7,
	TOUCH_PAD_NUM8,
	TOUCH_PAD_NUM9,
	TOUCH_PAD_NUM10,
	TOUCH_PAD_NUM11,
	TOUCH_PAD_NUM12,
	TOUCH_PAD_NUM13,
	TOUCH_PAD_NUM14,
	TOUCH_PAD_MAX,
} touch_pad_t;

typedef enum {
	TOUCH_HVOLT_KEEP = -1,
	TOUCH_HVOLT_2V4 = 0,
	TOUCH_HVOLT_2V5,
	TOUCH_HVOLT_2V6,
	TOUCH_HVOLT_2V7,
	TOUCH_HVOLT_MAX,
} touch_high_volt_t;

typedef enum {
	TOUCH_LVOLT_KEEP = -1,
	TOUCH_LVOLT_0V5 = 0,
	TOUCH_LVOLT_0V6,
	TOUCH_LVOLT_0V7,
	TOUCH_LVOLT_0V8,
	TOUCH_LVOLT_MAX,
} touch_low_volt_t;

typedef enum {
	TOUCH_HVOLT_ATTEN_KEEP = -1,
	TOUCH_HVOLT_ATTEN_1V5 = 0,
	TOUCH_HVOLT_ATTEN_1V,
	TOUCH_HVOLT_ATTEN_0V5,
	TOUCH_HVOLT_ATTEN_0V,
	TOUCH_HVOLT_ATTEN_MAX,
} touch_volt_atten_t;

typedef enum {
	TOUCH_PAD_SLOPE_0 = 0,
	TOUCH_PAD_SLOPE_1 = 1,
	TOUCH_PAD_SLOPE_2 = 2,
	TOUCH_PAD_SLOPE_3 = 3,
	TOUCH_PAD_SLOPE_4 = 4,
	TOUCH_PAD_SLOPE_5 = 5,
	TOUCH_PAD_SLOPE_6 = 6,
	TOUCH_PAD_SLOPE_7 = 7,
	TOUCH_PAD_SLOPE_MAX,
} touch_cnt_slope_t;

typedef enum {
	TOUCH_PAD_TIE_OPT_LOW = 0,
	TOUCH_PAD_TIE_OPT_HIGH = 1,
	TOUCH_PAD_TIE_OPT_MAX,
} touch_tie_opt_t;

typedef enum {
	TOUCH_FSM_MODE_TIMER = 0,
	TOUCH_FSM_MODE_SW,
	TOUCH_FSM_MODE_MAX,
} touch_fsm_mode_t;

typedef enum {
	TOUCH_TRIGGER_BELOW = 0,
	TOUCH_TRIGGER_ABOVE = 1,
	TOUCH_TRIGGER_MAX,
} touch_trigger_mode_t;

typedef enum {
	TOUCH_TRIGGER_SOURCE_BOTH = 0,
	TOUCH_TRIGGER_SOURCE_SET1 = 1,
	TOUCH_TRIGGER_SOURCE_MAX,
} touch_trigger_src_t;

#define TOUCH_PAD_BIT_MASK_ALL              ((1<<SOC_TOUCH_SENSOR_NUM)-1)
#define TOUCH_PAD_SLOPE_DEFAULT             (TOUCH_PAD_SLOPE_7)
#define TOUCH_PAD_TIE_OPT_DEFAULT           (TOUCH_PAD_TIE_OPT_LOW)
#define TOUCH_PAD_BIT_MASK_MAX              (TOUCH_PAD_BIT_MASK_ALL)
#define TOUCH_PAD_HIGH_VOLTAGE_THRESHOLD    (TOUCH_HVOLT_2V7)
#define TOUCH_PAD_LOW_VOLTAGE_THRESHOLD     (TOUCH_LVOLT_0V5)
#define TOUCH_PAD_ATTEN_VOLTAGE_THRESHOLD   (TOUCH_HVOLT_ATTEN_0V5)
#define TOUCH_PAD_IDLE_CH_CONNECT_DEFAULT   (TOUCH_PAD_CONN_GND)
#define TOUCH_PAD_THRESHOLD_MAX             (SOC_TOUCH_PAD_THRESHOLD_MAX)

#define TOUCH_PAD_SLEEP_CYCLE_DEFAULT   (0xf)
#define TOUCH_PAD_MEASURE_CYCLE_DEFAULT (500)
#define SOC_TOUCH_PAD_MEASURE_WAIT_MAX      (0xFF)

typedef enum {
	TOUCH_PAD_INTR_MASK_DONE = 1<<(0),
	TOUCH_PAD_INTR_MASK_ACTIVE = 1<<(1),
	TOUCH_PAD_INTR_MASK_INACTIVE = 1<<(2),
	TOUCH_PAD_INTR_MASK_SCAN_DONE = 1<<(3),
	TOUCH_PAD_INTR_MASK_TIMEOUT = 1<<(4),
	TOUCH_PAD_INTR_MASK_PROXI_MEAS_DONE = 1<<(5),
	TOUCH_PAD_INTR_MASK_MAX
#define TOUCH_PAD_INTR_MASK_ALL (TOUCH_PAD_INTR_MASK_TIMEOUT    \
								| TOUCH_PAD_INTR_MASK_SCAN_DONE \
								| TOUCH_PAD_INTR_MASK_INACTIVE  \
								| TOUCH_PAD_INTR_MASK_ACTIVE    \
								| TOUCH_PAD_INTR_MASK_DONE      \
								| TOUCH_PAD_INTR_MASK_PROXI_MEAS_DONE)
} touch_pad_intr_mask_t;

typedef enum {
	TOUCH_PAD_DENOISE_BIT12 = 0,
	TOUCH_PAD_DENOISE_BIT10 = 1,
	TOUCH_PAD_DENOISE_BIT8 = 2,
	TOUCH_PAD_DENOISE_BIT4 = 3,
	TOUCH_PAD_DENOISE_MAX
} touch_pad_denoise_grade_t;

typedef enum {
	TOUCH_PAD_DENOISE_CAP_L0 = 0,
	TOUCH_PAD_DENOISE_CAP_L1 = 1,
	TOUCH_PAD_DENOISE_CAP_L2 = 2,
	TOUCH_PAD_DENOISE_CAP_L3 = 3,
	TOUCH_PAD_DENOISE_CAP_L4 = 4,
	TOUCH_PAD_DENOISE_CAP_L5 = 5,
	TOUCH_PAD_DENOISE_CAP_L6 = 6,
	TOUCH_PAD_DENOISE_CAP_L7 = 7,
	TOUCH_PAD_DENOISE_CAP_MAX = 8
} touch_pad_denoise_cap_t;


typedef struct touch_pad_denoise {
	touch_pad_denoise_grade_t grade;
	touch_pad_denoise_cap_t cap_level;
} touch_pad_denoise_t;


typedef enum {
	TOUCH_PAD_SHIELD_DRV_L0 = 0,
	TOUCH_PAD_SHIELD_DRV_L1,
	TOUCH_PAD_SHIELD_DRV_L2,
	TOUCH_PAD_SHIELD_DRV_L3,
	TOUCH_PAD_SHIELD_DRV_L4,
	TOUCH_PAD_SHIELD_DRV_L5,
	TOUCH_PAD_SHIELD_DRV_L6,
	TOUCH_PAD_SHIELD_DRV_L7,
	TOUCH_PAD_SHIELD_DRV_MAX
} touch_pad_shield_driver_t;


typedef struct touch_pad_waterproof {
	touch_pad_t guard_ring_pad;
	touch_pad_shield_driver_t shield_driver;
} touch_pad_waterproof_t;


#define TOUCH_PROXIMITY_MEAS_NUM_MAX (0xFF)


typedef enum {
	TOUCH_PAD_CONN_HIGHZ = 0,
	TOUCH_PAD_CONN_GND = 1,
	TOUCH_PAD_CONN_MAX
} touch_pad_conn_type_t;


typedef enum {
	TOUCH_PAD_FILTER_IIR_4 = 0,
	TOUCH_PAD_FILTER_IIR_8,
	TOUCH_PAD_FILTER_IIR_16,
	TOUCH_PAD_FILTER_IIR_32,
	TOUCH_PAD_FILTER_IIR_64,
	TOUCH_PAD_FILTER_IIR_128,
	TOUCH_PAD_FILTER_IIR_256,
	TOUCH_PAD_FILTER_JITTER,
	TOUCH_PAD_FILTER_MAX
} touch_filter_mode_t;


typedef enum {
	TOUCH_PAD_SMOOTH_OFF   = 0,
	TOUCH_PAD_SMOOTH_IIR_2 = 1,
	TOUCH_PAD_SMOOTH_IIR_4 = 2,
	TOUCH_PAD_SMOOTH_IIR_8 = 3,
	TOUCH_PAD_SMOOTH_MAX,
} touch_smooth_mode_t;


typedef struct touch_filter_config {
	touch_filter_mode_t mode;
	uint32_t debounce_cnt;
	uint32_t noise_thr;
	uint32_t jitter_step;
	touch_smooth_mode_t smh_lvl;
#define TOUCH_DEBOUNCE_CNT_MAX      (7)
#define TOUCH_NOISE_THR_MAX         (3)
#define TOUCH_JITTER_STEP_MAX       (15)
} touch_filter_config_t;


typedef struct {
	touch_pad_t touch_num;
	bool en_proximity;
} touch_pad_sleep_channel_t;

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
uint32_t touch_ll_read_raw_data(touch_pad_t touch_num);
bool touch_ll_meas_is_done(void);
void touch_ll_reset(void);
void touch_ll_set_idle_channel_connect(touch_pad_conn_type_t type);
void touch_ll_get_idle_channel_connect(touch_pad_conn_type_t *type);
touch_pad_t touch_ll_get_current_meas_channel(void);
void touch_ll_intr_enable(touch_pad_intr_mask_t int_mask);
void touch_ll_intr_disable(touch_pad_intr_mask_t int_mask);
void touch_ll_intr_clear(touch_pad_intr_mask_t int_mask);
uint32_t touch_ll_read_intr_status_mask(void);
void touch_ll_timeout_enable(void);
void touch_ll_timeout_disable(void);
void touch_ll_timeout_set_threshold(uint32_t threshold);
void touch_ll_timeout_get_threshold(uint32_t *threshold);
void touch_ll_filter_read_smooth(touch_pad_t touch_num, uint32_t *smooth_data);
void touch_ll_read_benchmark(touch_pad_t touch_num, uint32_t *benchmark);
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
