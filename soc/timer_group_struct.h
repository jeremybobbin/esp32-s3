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

extern timg_dev_t TIMERG0;
extern timg_dev_t TIMERG1;
