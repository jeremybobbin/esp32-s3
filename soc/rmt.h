#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define RMT_LL_MAX_LOOP_COUNT           (1023)/*!< Max loop count that hardware is supported */
#define RMT_LL_HW_BASE  (&RMT)
#define RMT_LL_MEM_BASE (&RMTMEM)

typedef union {
	struct {
		uint32_t chndata: 32;
	};
	uint32_t val;
} rmt_chndata_reg_t;

typedef union {
	struct {
		uint32_t chmdata: 32;
	};
	uint32_t val;
} rmt_chmdata_reg_t;


typedef union {
	struct {
		uint32_t tx_start_n: 1;
		uint32_t mem_rd_rst_n: 1;
		uint32_t apb_mem_rst_n: 1;
		uint32_t tx_conti_mode_n: 1;
		uint32_t mem_tx_wrap_en_n: 1;
		uint32_t idle_out_lv_n: 1;
		uint32_t idle_out_en_n: 1;
		uint32_t tx_stop_n: 1;
		uint32_t div_cnt_n: 8;
		uint32_t mem_size_n: 4;
		uint32_t carrier_eff_en_n: 1;
		uint32_t carrier_en_n: 1;
		uint32_t carrier_out_lv_n: 1;
		uint32_t afifo_rst_n: 1;
		uint32_t conf_update_n: 1;
		uint32_t reserved_25: 7;
	};
	uint32_t val;
} rmt_chnconf0_reg_t;

typedef struct {
	union {
		struct {
			uint32_t div_cnt_m: 8;
			uint32_t idle_thres_m: 15;
			uint32_t reserved_23: 1;
			uint32_t mem_size_m: 4;
			uint32_t carrier_en_m: 1;
			uint32_t carrier_out_lv_m: 1;
			uint32_t reserved_30: 2;
		};
		uint32_t val;
	} conf0;

	union {
		struct {
			uint32_t rx_en_m: 1;
			uint32_t mem_wr_rst_m: 1;
			uint32_t apb_mem_rst_m: 1;
			uint32_t mem_owner_m: 1;
			uint32_t rx_filter_en_m: 1;
			uint32_t rx_filter_thres_m: 8;
			uint32_t mem_rx_wrap_en_m: 1;
			uint32_t afifo_rst_m: 1;
			uint32_t conf_update_m: 1;
			uint32_t reserved_16: 16;
		};
		uint32_t val;
	} conf1;
} rmt_chmconf_reg_t;

typedef union {
	struct {
		uint32_t carrier_low_thres_chm: 16;
		uint32_t carrier_high_thres_chm: 16;
	};
	uint32_t val;
} rmt_chm_rx_carrier_rm_reg_t;

typedef union {
	struct {
		uint32_t apb_fifo_mask: 1;
		uint32_t mem_clk_force_on: 1;
		uint32_t mem_force_pd: 1;
		uint32_t mem_force_pu: 1;
		uint32_t sclk_div_num: 8;
		uint32_t sclk_div_a: 6;
		uint32_t sclk_div_b: 6;
		uint32_t sclk_sel: 2;
		uint32_t sclk_active: 1;
		uint32_t reserved_27: 4;
		uint32_t clk_en: 1;
	};
	uint32_t val;
} rmt_sys_conf_reg_t;

typedef union {
	struct {
		uint32_t ref_cnt_rst_ch0: 1;
		uint32_t ref_cnt_rst_ch1: 1;
		uint32_t ref_cnt_rst_ch2: 1;
		uint32_t ref_cnt_rst_ch3: 1;
		uint32_t ref_cnt_rst_ch4: 1;
		uint32_t ref_cnt_rst_ch5: 1;
		uint32_t ref_cnt_rst_ch6: 1;
		uint32_t ref_cnt_rst_ch7: 1;
		uint32_t reserved_8: 24;
	};
	uint32_t val;
} rmt_ref_cnt_rst_reg_t;


typedef union {
	struct {
		uint32_t mem_raddr_ex_n: 10;
		uint32_t reserved_10: 1;
		uint32_t apb_mem_waddr_n: 10;
		uint32_t reserved_21: 1;
		uint32_t state_n: 3;
		uint32_t mem_empty_n: 1;
		uint32_t apb_mem_wr_err_n: 1;
		uint32_t reserved_27: 5;
	};
	uint32_t val;
} rmt_chnstatus_reg_t;

typedef union {
	struct {
		uint32_t mem_waddr_ex_m: 10;
		uint32_t reserved_10: 1;
		uint32_t apb_mem_raddr_m: 10;
		uint32_t reserved_21: 1;
		uint32_t state_m: 3;
		uint32_t mem_owner_err_m: 1;
		uint32_t mem_full_m: 1;
		uint32_t apb_mem_rd_err_m: 1;
		uint32_t reserved_28: 4;
	};
	uint32_t val;
} rmt_chmstatus_reg_t;


typedef union {
	struct {
		uint32_t ch0_tx_end_int_raw: 1;
		uint32_t ch1_tx_end_int_raw: 1;
		uint32_t ch2_tx_end_int_raw: 1;
		uint32_t ch3_tx_end_int_raw: 1;
		uint32_t ch0_err_int_raw: 1;
		uint32_t ch1_err_int_raw: 1;
		uint32_t ch2_err_int_raw: 1;
		uint32_t ch3_err_int_raw: 1;
		uint32_t ch0_tx_thr_event_int_raw: 1;
		uint32_t ch1_tx_thr_event_int_raw: 1;
		uint32_t ch2_tx_thr_event_int_raw: 1;
		uint32_t ch3_tx_thr_event_int_raw: 1;
		uint32_t ch0_tx_loop_int_raw: 1;
		uint32_t ch1_tx_loop_int_raw: 1;
		uint32_t ch2_tx_loop_int_raw: 1;
		uint32_t ch3_tx_loop_int_raw: 1;
		uint32_t ch4_rx_end_int_raw: 1;
		uint32_t ch5_rx_end_int_raw: 1;
		uint32_t ch6_rx_end_int_raw: 1;
		uint32_t ch7_rx_end_int_raw: 1;
		uint32_t ch4_err_int_raw: 1;
		uint32_t ch5_err_int_raw: 1;
		uint32_t ch6_err_int_raw: 1;
		uint32_t ch7_err_int_raw: 1;
		uint32_t ch4_rx_thr_event_int_raw: 1;
		uint32_t ch5_rx_thr_event_int_raw: 1;
		uint32_t ch6_rx_thr_event_int_raw: 1;
		uint32_t ch7_rx_thr_event_int_raw: 1;
		uint32_t ch3_dma_access_fail_int_raw: 1;
		uint32_t ch7_dma_access_fail_int_raw: 1;
		uint32_t reserved_30: 2;
	};
	uint32_t val;
} rmt_int_raw_reg_t;

typedef union {
	struct {
		uint32_t ch0_tx_end_int_st: 1;
		uint32_t ch1_tx_end_int_st: 1;
		uint32_t ch2_tx_end_int_st: 1;
		uint32_t ch3_tx_end_int_st: 1;
		uint32_t ch0_err_int_st: 1;
		uint32_t ch1_err_int_st: 1;
		uint32_t ch2_err_int_st: 1;
		uint32_t ch3_err_int_st: 1;
		uint32_t ch0_tx_thr_event_int_st: 1;
		uint32_t ch1_tx_thr_event_int_st: 1;
		uint32_t ch2_tx_thr_event_int_st: 1;
		uint32_t ch3_tx_thr_event_int_st: 1;
		uint32_t ch0_tx_loop_int_st: 1;
		uint32_t ch1_tx_loop_int_st: 1;
		uint32_t ch2_tx_loop_int_st: 1;
		uint32_t ch3_tx_loop_int_st: 1;
		uint32_t ch4_rx_end_int_st: 1;
		uint32_t ch5_rx_end_int_st: 1;
		uint32_t ch6_rx_end_int_st: 1;
		uint32_t ch7_rx_end_int_st: 1;
		uint32_t ch4_err_int_st: 1;
		uint32_t ch5_err_int_st: 1;
		uint32_t ch6_err_int_st: 1;
		uint32_t ch7_err_int_st: 1;
		uint32_t ch4_rx_thr_event_int_st: 1;
		uint32_t ch5_rx_thr_event_int_st: 1;
		uint32_t ch6_rx_thr_event_int_st: 1;
		uint32_t ch7_rx_thr_event_int_st: 1;
		uint32_t ch3_dma_access_fail_int_st: 1;
		uint32_t ch7_dma_access_fail_int_st: 1;
		uint32_t reserved_30: 2;
	};
	uint32_t val;
} rmt_int_st_reg_t;

typedef union {
	struct {
		uint32_t ch0_tx_end_int_ena: 1;
		uint32_t ch1_tx_end_int_ena: 1;
		uint32_t ch2_tx_end_int_ena: 1;
		uint32_t ch3_tx_end_int_ena: 1;
		uint32_t ch0_err_int_ena: 1;
		uint32_t ch1_err_int_ena: 1;
		uint32_t ch2_err_int_ena: 1;
		uint32_t ch3_err_int_ena: 1;
		uint32_t ch0_tx_thr_event_int_ena: 1;
		uint32_t ch1_tx_thr_event_int_ena: 1;
		uint32_t ch2_tx_thr_event_int_ena: 1;
		uint32_t ch3_tx_thr_event_int_ena: 1;
		uint32_t ch0_tx_loop_int_ena: 1;
		uint32_t ch1_tx_loop_int_ena: 1;
		uint32_t ch2_tx_loop_int_ena: 1;
		uint32_t ch3_tx_loop_int_ena: 1;
		uint32_t ch4_rx_end_int_ena: 1;
		uint32_t ch5_rx_end_int_ena: 1;
		uint32_t ch6_rx_end_int_ena: 1;
		uint32_t ch7_rx_end_int_ena: 1;
		uint32_t ch4_err_int_ena: 1;
		uint32_t ch5_err_int_ena: 1;
		uint32_t ch6_err_int_ena: 1;
		uint32_t ch7_err_int_ena: 1;
		uint32_t ch4_rx_thr_event_int_ena: 1;
		uint32_t ch5_rx_thr_event_int_ena: 1;
		uint32_t ch6_rx_thr_event_int_ena: 1;
		uint32_t ch7_rx_thr_event_int_ena: 1;
		uint32_t ch3_dma_access_fail_int_ena: 1;
		uint32_t ch7_dma_access_fail_int_ena: 1;
		uint32_t reserved_30: 2;
	};
	uint32_t val;
} rmt_int_ena_reg_t;

typedef union {
	struct {
		uint32_t ch0_tx_end_int_clr: 1;
		uint32_t ch1_tx_end_int_clr: 1;
		uint32_t ch2_tx_end_int_clr: 1;
		uint32_t ch3_tx_end_int_clr: 1;
		uint32_t ch0_err_int_clr: 1;
		uint32_t ch1_err_int_clr: 1;
		uint32_t ch2_err_int_clr: 1;
		uint32_t ch3_err_int_clr: 1;
		uint32_t ch0_tx_thr_event_int_clr: 1;
		uint32_t ch1_tx_thr_event_int_clr: 1;
		uint32_t ch2_tx_thr_event_int_clr: 1;
		uint32_t ch3_tx_thr_event_int_clr: 1;
		uint32_t ch0_tx_loop_int_clr: 1;
		uint32_t ch1_tx_loop_int_clr: 1;
		uint32_t ch2_tx_loop_int_clr: 1;
		uint32_t ch3_tx_loop_int_clr: 1;
		uint32_t ch4_rx_end_int_clr: 1;
		uint32_t ch5_rx_end_int_clr: 1;
		uint32_t ch6_rx_end_int_clr: 1;
		uint32_t ch7_rx_end_int_clr: 1;
		uint32_t ch4_err_int_clr: 1;
		uint32_t ch5_err_int_clr: 1;
		uint32_t ch6_err_int_clr: 1;
		uint32_t ch7_err_int_clr: 1;
		uint32_t ch4_rx_thr_event_int_clr: 1;
		uint32_t ch5_rx_thr_event_int_clr: 1;
		uint32_t ch6_rx_thr_event_int_clr: 1;
		uint32_t ch7_rx_thr_event_int_clr: 1;
		uint32_t ch3_dma_access_fail_int_clr: 1;
		uint32_t ch7_dma_access_fail_int_clr: 1;
		uint32_t reserved_30: 2;
	};
	uint32_t val;
} rmt_int_clr_reg_t;


typedef union {
	struct {
		uint32_t carrier_low_chn: 16;
		uint32_t carrier_high_chn: 16;
	};
	uint32_t val;
} rmt_chncarrier_duty_reg_t;


typedef union {
	struct {
		uint32_t tx_lim_chn: 9;
		uint32_t tx_loop_num_chn: 10;
		uint32_t tx_loop_cnt_en_chn: 1;
		uint32_t loop_count_reset_chn: 1;
		uint32_t loop_stop_en_chn: 1;
		uint32_t reserved_22: 10;
	};
	uint32_t val;
} rmt_chn_tx_lim_reg_t;

typedef union {
	struct {
		uint32_t tx_sim_ch0: 1;
		uint32_t tx_sim_ch1: 1;
		uint32_t tx_sim_ch2: 1;
		uint32_t tx_sim_ch3: 1;
		uint32_t tx_sim_en: 1;
		uint32_t reserved_5: 27;
	};
	uint32_t val;
} rmt_tx_sim_reg_t;


typedef union {
	struct {
		uint32_t chm_rx_lim_reg: 9;
		uint32_t reserved_9: 23;
	};
	uint32_t val;
} rmt_chm_rx_lim_reg_t;


typedef union {
	struct {
		uint32_t date: 28;
		uint32_t reserved_28: 4;
	};
	uint32_t val;
} rmt_date_reg_t;


typedef struct {
	volatile rmt_chndata_reg_t chndata[4];
	volatile rmt_chmdata_reg_t chmdata[4];
	volatile rmt_chnconf0_reg_t chnconf0[4];
	volatile rmt_chmconf_reg_t chmconf[4];
	volatile rmt_chnstatus_reg_t chnstatus[4];
	volatile rmt_chmstatus_reg_t chmstatus[4];
	volatile rmt_int_raw_reg_t int_raw;
	volatile rmt_int_st_reg_t int_st;
	volatile rmt_int_ena_reg_t int_ena;
	volatile rmt_int_clr_reg_t int_clr;
	volatile rmt_chncarrier_duty_reg_t chncarrier_duty[4];
	volatile rmt_chm_rx_carrier_rm_reg_t chm_rx_carrier_rm[4];
	volatile rmt_chn_tx_lim_reg_t chn_tx_lim[4];
	volatile rmt_chm_rx_lim_reg_t chm_rx_lim[4];
	volatile rmt_sys_conf_reg_t sys_conf;
	volatile rmt_tx_sim_reg_t tx_sim;
	volatile rmt_ref_cnt_rst_reg_t ref_cnt_rst;
	volatile rmt_date_reg_t date;
} rmt_dev_t;

typedef struct {
	union {
		struct {
			uint32_t duration0 : 15;
			uint32_t level0 : 1;
			uint32_t duration1 : 15;
			uint32_t level1 : 1;
		};
		uint32_t val;
	};
} rmt_item32_t;

typedef struct {
	struct {
		volatile rmt_item32_t data32[48];
	} chan[8];
} rmt_mem_t;

extern rmt_dev_t RMT;
extern rmt_mem_t RMTMEM;


void rmt_ll_enable_drive_clock(rmt_dev_t *dev, bool enable);
void rmt_ll_power_down_mem(rmt_dev_t *dev, bool enable);
bool rmt_ll_is_mem_power_down(rmt_dev_t *dev);
void rmt_ll_enable_mem_access(rmt_dev_t *dev, bool enable);
void rmt_ll_set_group_clock_src(rmt_dev_t *dev, uint32_t channel, uint8_t src, uint8_t div_num, uint8_t div_a, uint8_t div_b);
uint32_t rmt_ll_get_group_clock_src(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_reset_channel_clock_div(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_reset_channels_clock_div(rmt_dev_t *dev, uint32_t channel_mask);
void rmt_ll_rx_reset_channel_clock_div(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_reset_pointer(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_rx_reset_pointer(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_start(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_stop(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_rx_enable(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_tx_set_mem_blocks(rmt_dev_t *dev, uint32_t channel, uint8_t block_num);
void rmt_ll_rx_set_mem_blocks(rmt_dev_t *dev, uint32_t channel, uint8_t block_num);
uint32_t rmt_ll_tx_get_mem_blocks(rmt_dev_t *dev, uint32_t channel);
uint32_t rmt_ll_rx_get_mem_blocks(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_set_channel_clock_div(rmt_dev_t *dev, uint32_t channel, uint32_t div);
void rmt_ll_rx_set_channel_clock_div(rmt_dev_t *dev, uint32_t channel, uint32_t div);
uint32_t rmt_ll_tx_get_channel_clock_div(rmt_dev_t *dev, uint32_t channel);
uint32_t rmt_ll_rx_get_channel_clock_div(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_enable_pingpong(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_rx_set_idle_thres(rmt_dev_t *dev, uint32_t channel, uint32_t thres);
uint32_t rmt_ll_rx_get_idle_thres(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_rx_set_mem_owner(rmt_dev_t *dev, uint32_t channel, uint8_t owner);
uint32_t rmt_ll_rx_get_mem_owner(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_enable_loop(rmt_dev_t *dev, uint32_t channel, bool enable);
bool rmt_ll_is_tx_loop_enabled(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_enable_loop_autostop(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_tx_set_loop_count(rmt_dev_t *dev, uint32_t channel, uint32_t count);
void rmt_ll_tx_reset_loop(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_enable_loop_count(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_tx_enable_sync(rmt_dev_t *dev, bool enable);
void rmt_ll_tx_add_to_sync_group(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_remove_from_sync_group(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_rx_enable_filter(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_rx_set_filter_thres(rmt_dev_t *dev, uint32_t channel, uint32_t thres);
void rmt_ll_tx_enable_idle(rmt_dev_t *dev, uint32_t channel, bool enable);
bool rmt_ll_is_tx_idle_enabled(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_set_idle_level(rmt_dev_t *dev, uint32_t channel, uint8_t level);
uint32_t rmt_ll_tx_get_idle_level(rmt_dev_t *dev, uint32_t channel);
uint32_t rmt_ll_rx_get_channel_status(rmt_dev_t *dev, uint32_t channel);
uint32_t rmt_ll_tx_get_channel_status(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_tx_set_limit(rmt_dev_t *dev, uint32_t channel, uint32_t limit);
void rmt_ll_rx_set_limit(rmt_dev_t *dev, uint32_t channel, uint32_t limit);
uint32_t rmt_ll_rx_get_limit(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_enable_interrupt(rmt_dev_t *dev, uint32_t mask, bool enable);
void rmt_ll_enable_tx_end_interrupt(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_enable_tx_err_interrupt(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_enable_rx_end_interrupt(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_enable_rx_err_interrupt(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_enable_tx_thres_interrupt(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_enable_tx_loop_interrupt(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_enable_rx_thres_interrupt(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_clear_tx_end_interrupt(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_clear_rx_end_interrupt(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_clear_tx_err_interrupt(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_clear_rx_err_interrupt(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_clear_tx_thres_interrupt(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_clear_tx_loop_interrupt(rmt_dev_t *dev, uint32_t channel);
void rmt_ll_clear_rx_thres_interrupt(rmt_dev_t *dev, uint32_t channel);
uint32_t rmt_ll_get_tx_end_interrupt_status(rmt_dev_t *dev);
uint32_t rmt_ll_get_rx_end_interrupt_status(rmt_dev_t *dev);
uint32_t rmt_ll_get_tx_err_interrupt_status(rmt_dev_t *dev);
uint32_t rmt_ll_get_rx_err_interrupt_status(rmt_dev_t *dev);
uint32_t rmt_ll_get_tx_thres_interrupt_status(rmt_dev_t *dev);
uint32_t rmt_ll_get_rx_thres_interrupt_status(rmt_dev_t *dev);
uint32_t rmt_ll_get_tx_loop_interrupt_status(rmt_dev_t *dev);
void rmt_ll_tx_set_carrier_high_low_ticks(rmt_dev_t *dev, uint32_t channel, uint32_t high_ticks, uint32_t low_ticks);
void rmt_ll_rx_set_carrier_high_low_ticks(rmt_dev_t *dev, uint32_t channel, uint32_t high_ticks, uint32_t low_ticks);
void rmt_ll_tx_get_carrier_high_low_ticks(rmt_dev_t *dev, uint32_t channel, uint32_t *high_ticks, uint32_t *low_ticks );
void rmt_ll_rx_get_carrier_high_low_ticks(rmt_dev_t *dev, uint32_t channel, uint32_t *high_ticks, uint32_t *low_ticks);
void rmt_ll_tx_enable_carrier_modulation(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_rx_enable_carrier_demodulation(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_tx_set_carrier_level(rmt_dev_t *dev, uint32_t channel, uint8_t level);
void rmt_ll_rx_set_carrier_level(rmt_dev_t *dev, uint32_t channel, uint8_t level);
void rmt_ll_tx_set_carrier_always_on(rmt_dev_t *dev, uint32_t channel, bool enable);
void rmt_ll_write_memory(rmt_mem_t *mem, uint32_t channel, const void *data, size_t length_in_words, size_t off);
void rmt_ll_rx_enable_pingpong(rmt_dev_t *dev, uint32_t channel, bool enable);
