#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
	TIMER_GROUP_0 = 0, /*!<Hw timer group 0*/
	TIMER_GROUP_1 = 1, /*!<Hw timer group 1*/
	TIMER_GROUP_MAX,
} timer_group_t;

typedef union {
	struct {
		uint32_t reserved_0:9;
		uint32_t tn_use_xtal:1;
		uint32_t tn_alarm_en:1;
		uint32_t reserved_11:2;
		uint32_t tn_divider:16;
		uint32_t tn_autoreload:1;
		uint32_t tn_increase:1;
		uint32_t tn_en:1;
	};
	uint32_t val;
} timg_tnconfig_reg_t;

typedef union {
	struct {
		uint32_t tn_lo:32;
	};
	uint32_t val;
} timg_tnlo_reg_t;

typedef union {
	struct {
		uint32_t tn_hi:22;
		uint32_t reserved_22:10;
	};
	uint32_t val;
} timg_tnhi_reg_t;

typedef union {
	struct {
		uint32_t reserved_0:31;
		uint32_t tn_update:1;
	};
	uint32_t val;
} timg_tnupdate_reg_t;

typedef union {
	struct {
		uint32_t tn_alarm_lo:32;
	};
	uint32_t val;
} timg_tnalarmlo_reg_t;

typedef union {
	struct {
		uint32_t tn_alarm_hi:22;
		uint32_t reserved_22:10;
	};
	uint32_t val;
} timg_tnalarmhi_reg_t;

typedef union {
	struct {
		uint32_t tn_load_lo:32;
	};
	uint32_t val;
} timg_tnloadlo_reg_t;

typedef union {
	struct {
		uint32_t tn_load_hi:22;
		uint32_t reserved_22:10;
	};
	uint32_t val;
} timg_tnloadhi_reg_t;

typedef union {
	struct {
		uint32_t tn_load:32;
	};
	uint32_t val;
} timg_tnload_reg_t;


typedef union {
	struct {
		uint32_t reserved_0:12;
		uint32_t wdt_appcpu_reset_en:1;
		uint32_t wdt_procpu_reset_en:1;
		uint32_t wdt_flashboot_mod_en:1;
		uint32_t wdt_sys_reset_length:3;
		uint32_t wdt_cpu_reset_length:3;
		uint32_t reserved_21:2;
		uint32_t wdt_stg3:2;
		uint32_t wdt_stg2:2;
		uint32_t wdt_stg1:2;
		uint32_t wdt_stg0:2;
		uint32_t wdt_en:1;
	};
	uint32_t val;
} timg_wdtconfig0_reg_t;

typedef union {
	struct {
		uint32_t reserved_0:16;
		uint32_t wdt_clk_prescale:16;
	};
	uint32_t val;
} timg_wdtconfig1_reg_t;

typedef union {
	struct {
		uint32_t wdt_stg0_hold:32;
	};
	uint32_t val;
} timg_wdtconfig2_reg_t;

typedef union {
	struct {
		uint32_t wdt_stg1_hold:32;
	};
	uint32_t val;
} timg_wdtconfig3_reg_t;

typedef union {
	struct {
		uint32_t wdt_stg2_hold:32;
	};
	uint32_t val;
} timg_wdtconfig4_reg_t;

typedef union {
	struct {
		uint32_t wdt_stg3_hold:32;
	};
	uint32_t val;
} timg_wdtconfig5_reg_t;

typedef union {
	struct {
		uint32_t wdt_feed:32;
	};
	uint32_t val;
} timg_wdtfeed_reg_t;

typedef union {
	struct {
		uint32_t wdt_wkey:32;
	};
	uint32_t val;
} timg_wdtwprotect_reg_t;


typedef union {
	struct {
		uint32_t reserved_0:12;
		uint32_t rtc_cali_start_cycling:1;
		uint32_t rtc_cali_clk_sel:2;
		uint32_t rtc_cali_rdy:1;
		uint32_t rtc_cali_max:15;
		uint32_t rtc_cali_start:1;
	};
	uint32_t val;
} timg_rtccalicfg_reg_t;

typedef union {
	struct {
		uint32_t rtc_cali_cycling_data_vld:1;
		uint32_t reserved_1:6;
		uint32_t rtc_cali_value:25;
	};
	uint32_t val;
} timg_rtccalicfg1_reg_t;

typedef union {
	struct {
		uint32_t rtc_cali_timeout:1;
		uint32_t reserved_1:2;
		uint32_t rtc_cali_timeout_rst_cnt:4;
		uint32_t rtc_cali_timeout_thres:25;
	};
	uint32_t val;
} timg_rtccalicfg2_reg_t;


typedef union {
	struct {
		uint32_t t0_int_ena:1;
		uint32_t t1_int_ena:1;
		uint32_t wdt_int_ena:1;
		uint32_t reserved_3:29;
	};
	uint32_t val;
} timg_int_ena_timers_reg_t;

typedef union {
	struct {
		uint32_t t0_int_raw:1;
		uint32_t t1_int_raw:1;
		uint32_t wdt_int_raw:1;
		uint32_t reserved_3:29;
	};
	uint32_t val;
} timg_int_raw_timers_reg_t;

typedef union {
	struct {
		uint32_t t0_int_st:1;
		uint32_t t1_int_st:1;
		uint32_t wdt_int_st:1;
		uint32_t reserved_3:29;
	};
	uint32_t val;
} timg_int_st_timers_reg_t;

typedef union {
	struct {
		uint32_t t0_int_clr:1;
		uint32_t t1_int_clr:1;
		uint32_t wdt_int_clr:1;
		uint32_t reserved_3:29;
	};
	uint32_t val;
} timg_int_clr_timers_reg_t;


typedef union {
	struct {
		uint32_t ntimers_date:28;
		uint32_t reserved_28:4;
	};
	uint32_t val;
} timg_ntimers_date_reg_t;

typedef union {
	struct {
		uint32_t reserved_0:31;
		uint32_t clk_en:1;
	};
	uint32_t val;
} timg_regclk_reg_t;

typedef struct {
	volatile timg_tnconfig_reg_t config;
	volatile timg_tnlo_reg_t lo;
	volatile timg_tnhi_reg_t hi;
	volatile timg_tnupdate_reg_t update;
	volatile timg_tnalarmlo_reg_t alarmlo;
	volatile timg_tnalarmhi_reg_t alarmhi;
	volatile timg_tnloadlo_reg_t loadlo;
	volatile timg_tnloadhi_reg_t loadhi;
	volatile timg_tnload_reg_t load;
} timg_hwtimer_reg_t;

typedef struct {
	volatile timg_hwtimer_reg_t hw_timer[2];
	volatile timg_wdtconfig0_reg_t wdtconfig0;
	volatile timg_wdtconfig1_reg_t wdtconfig1;
	volatile timg_wdtconfig2_reg_t wdtconfig2;
	volatile timg_wdtconfig3_reg_t wdtconfig3;
	volatile timg_wdtconfig4_reg_t wdtconfig4;
	volatile timg_wdtconfig5_reg_t wdtconfig5;
	volatile timg_wdtfeed_reg_t wdtfeed;
	volatile timg_wdtwprotect_reg_t wdtwprotect;
	volatile timg_rtccalicfg_reg_t rtccalicfg;
	volatile timg_rtccalicfg1_reg_t rtccalicfg1;
	volatile timg_int_ena_timers_reg_t int_ena_timers;
	volatile timg_int_raw_timers_reg_t int_raw_timers;
	volatile timg_int_st_timers_reg_t int_st_timers;
	volatile timg_int_clr_timers_reg_t int_clr_timers;
	volatile timg_rtccalicfg2_reg_t rtccalicfg2;
	uint32_t reserved_084[29];
	volatile timg_ntimers_date_reg_t ntimers_date;
	volatile timg_regclk_reg_t regclk;
} timg_dev_t;

typedef enum {
	TIMER_0 = 0, /*!<Select timer0 of GROUPx*/
	TIMER_1 = 1, /*!<Select timer1 of GROUPx*/
	TIMER_MAX,
} timer_idx_t;

typedef struct {
	timg_dev_t *dev;
	timer_idx_t idx;
} timer_ll_context_t;

extern timg_dev_t TIMERG0;
extern timg_dev_t TIMERG1;


#define TIMER_LL_GET_HW(num) ((num == 0) ? (&TIMERG0) : (&TIMERG1))

void timer_ll_set_divider(timg_dev_t *hw, timer_idx_t timer_num, uint32_t divider);
void timer_ll_get_divider(timg_dev_t *hw, timer_idx_t timer_num, uint32_t *divider);
void timer_ll_set_counter_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t load_val);
void timer_ll_get_counter_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t *timer_val);
void timer_ll_set_counter_increase(timg_dev_t *hw, timer_idx_t timer_num, bool increase_en);
bool timer_ll_get_counter_increase(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_set_counter_enable(timg_dev_t *hw, timer_idx_t timer_num, bool counter_en);
bool timer_ll_get_counter_enable(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_set_auto_reload(timg_dev_t *hw, timer_idx_t timer_num, bool auto_reload_en);
bool timer_ll_get_auto_reload(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_set_alarm_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t alarm_value);
void timer_ll_get_alarm_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t *alarm_value);
void timer_ll_set_alarm_enable(timg_dev_t *hw, timer_idx_t timer_num, bool alarm_en);
bool timer_ll_get_alarm_enable(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_intr_enable(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_intr_disable(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_clear_intr_status(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_get_intr_status(timg_dev_t *hw, uint32_t *intr_status);
void timer_ll_get_intr_raw_status(timer_group_t group_num, uint32_t *intr_raw_status);
void timer_ll_set_level_int_enable(timg_dev_t *hw, timer_idx_t timer_num, bool level_int_en);
bool timer_ll_get_level_int_enable(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_set_edge_int_enable(timg_dev_t *hw, timer_idx_t timer_num, bool edge_int_en);
bool timer_ll_get_edge_int_enable(timg_dev_t *hw, timer_idx_t timer_num);
uint32_t timer_ll_get_intr_status_reg(timg_dev_t *hw);
uint32_t timer_ll_get_intr_mask_bit(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_set_use_xtal(timg_dev_t *hw, timer_idx_t timer_num, bool use_xtal_en);
bool timer_ll_get_use_xtal(timg_dev_t *hw, timer_idx_t timer_num);
