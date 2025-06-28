#include <stdint.h>
#include <stdbool.h>

#define SYSTIMER_LL_COUNTER_CLOCK       (0) // Counter used for "wallclock" time
#define SYSTIMER_LL_COUNTER_OS_TICK     (1) // Counter used for OS tick
#define SYSTIMER_LL_ALARM_OS_TICK_CORE0 (0) // Alarm used for OS tick of CPU core 0
#define SYSTIMER_LL_ALARM_OS_TICK_CORE1 (1) // Alarm used for OS tick of CPU core 1
#define SYSTIMER_LL_ALARM_CLOCK         (2) // Alarm used for "wallclock" time

#define SYSTIMER_LL_TICKS_PER_US        (16) // 16 systimer ticks == 1us

typedef union {
	struct {
		uint32_t systimer_clk_fo: 1;
		uint32_t reserved_1: 21;
		uint32_t target2_work_en: 1;
		uint32_t target1_work_en: 1;
		uint32_t target0_work_en: 1;
		uint32_t timer_unit1_core1_stall_en: 1;
		uint32_t timer_unit1_core0_stall_en: 1;
		uint32_t timer_unit0_core1_stall_en: 1;
		uint32_t timer_unit0_core0_stall_en: 1;
		uint32_t timer_unit1_work_en: 1;
		uint32_t timer_unit0_work_en: 1;
		uint32_t clk_en: 1;
	};
	uint32_t val;
} systimer_conf_reg_t;

typedef union {
	struct {
		uint32_t reserved_0: 29;
		uint32_t timer_unit_value_valid: 1;
		uint32_t timer_unit_update: 1;
		uint32_t reserved_32: 1;
	};
	uint32_t val;
} systimer_unit_op_reg_t;

typedef struct {
	union {
		struct {
			uint32_t timer_unit_load_hi: 20;
			uint32_t reserved_20: 12;
		};
		uint32_t val;
	} hi;
	union {
		struct {
			uint32_t timer_unit_load_lo: 32;
		};
		uint32_t val;
	} lo;
} systimer_unit_load_val_reg_t;

typedef struct {
	union {
		struct {
			uint32_t timer_target_hi: 20;
			uint32_t reserved_20: 12;
		};
		uint32_t val;
	} hi;
	union {
		struct {
			uint32_t timer_target_lo: 32;
		};
		uint32_t val;
	} lo;
} systimer_target_val_reg_t;

typedef union {
	struct {
		uint32_t target_period: 26;
		uint32_t reserved_26: 4;
		uint32_t target_period_mode: 1;
		uint32_t target_timer_unit_sel: 1;
	};
	uint32_t val;
} systimer_target_conf_reg_t;

typedef struct {
	union {
		struct {
			uint32_t timer_unit_value_hi: 20;
			uint32_t reserved_20: 12;
		};
		uint32_t val;
	} hi;
	union {
		struct {
			uint32_t timer_unit_value_lo: 32;
		};
		uint32_t val;
	} lo;
} systimer_unit_value_reg_t;

typedef union {
	struct {
		uint32_t timer_comp_load: 1;
		uint32_t reserved_1: 31;
	};
	uint32_t val;
} systimer_comp_load_reg_t;

typedef union {
	struct {
		uint32_t timer_unit_load: 1;
		uint32_t reserved_1: 31;
	};
	uint32_t val;
} systimer_unit_load_reg_t;

typedef union {
	struct {
		uint32_t target0_int_ena: 1;
		uint32_t target1_int_ena: 1;
		uint32_t target2_int_ena: 1;
		uint32_t reserved_3: 29;
	};
	uint32_t val;
} systimer_int_ena_reg_t;

typedef union {
	struct {
		uint32_t target0_int_raw: 1;
		uint32_t target1_int_raw: 1;
		uint32_t target2_int_raw: 1;
		uint32_t reserved_3: 29;
	};
	uint32_t val;
} systimer_int_raw_reg_t;

typedef union {
	struct {
		uint32_t target0_int_clr: 1;
		uint32_t target1_int_clr: 1;
		uint32_t target2_int_clr: 1;
		uint32_t reserved_3: 29;
	};
	uint32_t val;
} systimer_int_clr_reg_t;

typedef union {
	struct {
		uint32_t target0_int_st: 1;
		uint32_t target1_int_st: 1;
		uint32_t target2_int_st: 1;
		uint32_t reserved_3: 29;
	};
	uint32_t val;
} systimer_int_st_reg_t;

typedef struct {
	union {
		struct {
			uint32_t target_lo_ro: 32;
		};
		uint32_t val;
	} lo;
	union {
		struct {
			uint32_t target_hi_ro: 20;
			uint32_t reserved_20: 12;
		};
		uint32_t val;
	} hi;
} systimer_real_target_val_reg_t;

typedef union {
	struct {
		uint32_t date: 32;
	};
	uint32_t val;
} systimer_date_reg_t;

typedef struct {
	volatile systimer_conf_reg_t conf;
	volatile systimer_unit_op_reg_t unit_op[2];
	volatile systimer_unit_load_val_reg_t unit_load_val[2];
	volatile systimer_target_val_reg_t target_val[3];
	volatile systimer_target_conf_reg_t target_conf[3];
	volatile systimer_unit_value_reg_t unit_val[2];
	volatile systimer_comp_load_reg_t comp_load[3];
	volatile systimer_unit_load_reg_t unit_load[2];
	volatile systimer_int_ena_reg_t int_ena;
	volatile systimer_int_raw_reg_t int_raw;
	volatile systimer_int_clr_reg_t int_clr;
	volatile systimer_int_st_reg_t int_st;
	volatile systimer_real_target_val_reg_t real_target_val[3];
	uint32_t reserved_08c;
	uint32_t reserved_090;
	uint32_t reserved_094;
	uint32_t reserved_098;
	uint32_t reserved_09c;
	uint32_t reserved_0a0;
	uint32_t reserved_0a4;
	uint32_t reserved_0a8;
	uint32_t reserved_0ac;
	uint32_t reserved_0b0;
	uint32_t reserved_0b4;
	uint32_t reserved_0b8;
	uint32_t reserved_0bc;
	uint32_t reserved_0c0;
	uint32_t reserved_0c4;
	uint32_t reserved_0c8;
	uint32_t reserved_0cc;
	uint32_t reserved_0d0;
	uint32_t reserved_0d4;
	uint32_t reserved_0d8;
	uint32_t reserved_0dc;
	uint32_t reserved_0e0;
	uint32_t reserved_0e4;
	uint32_t reserved_0e8;
	uint32_t reserved_0ec;
	uint32_t reserved_0f0;
	uint32_t reserved_0f4;
	uint32_t reserved_0f8;
	volatile systimer_date_reg_t date;
} systimer_dev_t;

extern systimer_dev_t *SYSTIMER;


void systimer_ll_enable_clock(systimer_dev_t *dev, bool en);
void systimer_ll_enable_counter(systimer_dev_t *dev, uint32_t counter_id, bool en);
void systimer_ll_counter_can_stall_by_cpu(systimer_dev_t *dev, uint32_t counter_id, uint32_t cpu_id, bool can);
void systimer_ll_counter_snapshot(systimer_dev_t *dev, uint32_t counter_id);
bool systimer_ll_is_counter_value_valid(systimer_dev_t *dev, uint32_t counter_id);
void systimer_ll_set_counter_value(systimer_dev_t *dev, uint32_t counter_id, uint64_t value);
uint32_t systimer_ll_get_counter_value_low(systimer_dev_t *dev, uint32_t counter_id);
uint32_t systimer_ll_get_counter_value_high(systimer_dev_t *dev, uint32_t counter_id);
void systimer_ll_apply_counter_value(systimer_dev_t *dev, uint32_t counter_id);
void systimer_ll_set_alarm_target(systimer_dev_t *dev, uint32_t alarm_id, uint64_t value);
uint64_t systimer_ll_get_alarm_target(systimer_dev_t *dev, uint32_t alarm_id);
void systimer_ll_connect_alarm_counter(systimer_dev_t *dev, uint32_t alarm_id, uint32_t counter_id);
void systimer_ll_enable_alarm_oneshot(systimer_dev_t *dev, uint32_t alarm_id);
void systimer_ll_enable_alarm_period(systimer_dev_t *dev, uint32_t alarm_id);
void systimer_ll_set_alarm_period(systimer_dev_t *dev, uint32_t alarm_id, uint32_t period);
uint32_t systimer_ll_get_alarm_period(systimer_dev_t *dev, uint32_t alarm_id);
void systimer_ll_apply_alarm_value(systimer_dev_t *dev, uint32_t alarm_id);
void systimer_ll_enable_alarm(systimer_dev_t *dev, uint32_t alarm_id, bool en);
void systimer_ll_enable_alarm_int(systimer_dev_t *dev, uint32_t alarm_id, bool en);
bool systimer_ll_is_alarm_int_fired(systimer_dev_t *dev, uint32_t alarm_id);
void systimer_ll_clear_alarm_int(systimer_dev_t *dev, uint32_t alarm_id);

