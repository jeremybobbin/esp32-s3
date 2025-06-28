#include <stdbool.h>
#include "soc/clk_tree_defs.h"
#include "soc/i2c.h"

#define MCPWM_LL_GET_HW(ID) (((ID) == 0) ? &MCPWM0 : &MCPWM1)
#define MCPWM_LL_MAX_CAPTURE_PRESCALE 255
#define MCPWM_LL_MAX_COMPARE_VALUE    65535
#define MCPWM_LL_MAX_DEAD_DELAY       65535
#define MCPWM_LL_MAX_PHASE_VALUE      65535
typedef soc_periph_mcpwm_timer_clk_src_t mcpwm_timer_clock_source_t;
typedef soc_periph_mcpwm_capture_clk_src_t mcpwm_capture_clock_source_t;
typedef soc_periph_mcpwm_carrier_clk_src_t mcpwm_carrier_clock_source_t;

typedef enum {
	MCPWM_TIMER_DIRECTION_UP,	
	MCPWM_TIMER_DIRECTION_DOWN,
} mcpwm_timer_direction_t;


typedef enum {
	MCPWM_TIMER_EVENT_EMPTY,
	MCPWM_TIMER_EVENT_FULL,	
	MCPWM_TIMER_EVENT_INVALID,
} mcpwm_timer_event_t;

typedef enum {
	MCPWM_TRIP_TYPE_CBC, /*!< CBC trip type, shut down the operator cycle by cycle*/
	MCPWM_TRIP_TYPE_OST, /*!< OST trip type, shut down the operator in one shot */
} mcpwm_trip_type_t;



/*
typedef enum {
	MCPWM_TIMER_STOP_EMPTY,		
	MCPWM_TIMER_STOP_FULL,		
	MCPWM_TIMER_START_NO_STOP,	
	MCPWM_TIMER_START_STOP_EMPTY,
	MCPWM_TIMER_START_STOP_FULL,
} mcpwm_timer_start_stop_cmd_t;
*/

typedef enum {
	MCPWM_GEN_ACTION_KEEP,	
	MCPWM_GEN_ACTION_LOW,	
	MCPWM_GEN_ACTION_HIGH,	
	MCPWM_GEN_ACTION_TOGGLE,
} mcpwm_generator_action_t;


typedef enum {
	MCPWM_OPER_BRAKE_MODE_CBC,	
	MCPWM_OPER_BRAKE_MODE_OST,	
	MCPWM_OPER_BRAKE_MODE_INVALID,
} mcpwm_operator_brake_mode_t;


typedef enum {
	MCPWM_CAP_EDGE_POS,
	MCPWM_CAP_EDGE_NEG,
} mcpwm_capture_edge_t;


typedef enum {
	MCPWM_CMPR_ETM_EVENT_EQUAL,
	MCPWM_CMPR_ETM_EVENT_MAX,	
} mcpwm_comparator_etm_event_type_t;


typedef enum {
	MCPWM_TIMER_COUNT_MODE_PAUSE,
	MCPWM_TIMER_COUNT_MODE_UP,
	MCPWM_TIMER_COUNT_MODE_DOWN,
	MCPWM_TIMER_COUNT_MODE_UP_DOWN,
} mcpwm_timer_count_mode_t;

typedef union {
	struct {
		
		uint32_t clk_prescale: 8;
		uint32_t reserved_8: 24;
	};
	uint32_t val;
} mcpwm_clk_cfg_reg_t;

typedef union {
	struct {
		uint32_t timer_prescale: 8;
		uint32_t timer_period: 16;
		uint32_t timer_period_upmethod: 2;
		uint32_t reserved_26: 6;
	};
	uint32_t val;
} mcpwm_timer_cfg0_reg_t;

typedef union {
	struct {
		uint32_t timer_start: 3;
		uint32_t timer_mod: 2;
		uint32_t reserved_5: 27;
	};
	uint32_t val;
} mcpwm_timer_cfg1_reg_t;

typedef union {
	struct {
		uint32_t timer_synci_en: 1;
		uint32_t timer_sync_sw: 1;
		uint32_t timer_synco_sel: 2;
		uint32_t timer_phase: 16;
		uint32_t timer_phase_direction: 1;
		uint32_t reserved_21: 11;
	};
	uint32_t val;
} mcpwm_timer_sync_reg_t;

typedef union {
	struct {
		uint32_t timer_value: 16;
		uint32_t timer_direction: 1;
		uint32_t reserved_17: 15;
	};
	uint32_t val;
} mcpwm_timer_status_reg_t;

typedef union {
	struct {
		uint32_t timer0_syncisel: 3;
		uint32_t timer1_syncisel: 3;
		uint32_t timer2_syncisel: 3;
		uint32_t external_synci0_invert: 1;
		uint32_t external_synci1_invert: 1;
		uint32_t external_synci2_invert: 1;
		uint32_t reserved_12: 20;
	};
	uint32_t val;
} mcpwm_timer_synci_cfg_reg_t;

typedef union {
	struct {
		uint32_t operator0_timersel: 2;
		uint32_t operator1_timersel: 2;
		uint32_t operator2_timersel: 2;
		uint32_t reserved_6: 26;
	};
	uint32_t val;
} mcpwm_operator_timersel_reg_t;

typedef union {
	struct {
		uint32_t gen_a_upmethod: 4;
		uint32_t gen_b_upmethod: 4;
		uint32_t gen_a_shdw_full: 1;
		uint32_t gen_b_shdw_full: 1;
		uint32_t reserved_10: 22;
	};
	uint32_t val;
} mcpwm_gen_stmp_cfg_reg_t;

typedef union {
	struct {
		uint32_t gen: 16;
		uint32_t reserved_16: 16;
	};
	uint32_t val;
} mcpwm_gen_tstmp_reg_t;

typedef union {
	struct {
		uint32_t gen_cfg_upmethod: 4;
		uint32_t gen_t0_sel: 3;
		uint32_t gen_t1_sel: 3;
		uint32_t reserved_10: 22;
	};
	uint32_t val;
} mcpwm_gen_cfg0_reg_t;

typedef union {
	struct {
		uint32_t gen_cntuforce_upmethod: 6;
		uint32_t gen_a_cntuforce_mode: 2;
		uint32_t gen_b_cntuforce_mode: 2;
		uint32_t gen_a_nciforce: 1;
		uint32_t gen_a_nciforce_mode: 2;
		uint32_t gen_b_nciforce: 1;
		uint32_t gen_b_nciforce_mode: 2;
		uint32_t reserved_16: 16;
	};
	uint32_t val;
} mcpwm_gen_force_reg_t;

typedef union {
	struct {
		uint32_t gen_utez: 2;
		uint32_t gen_utep: 2;
		uint32_t gen_utea: 2;
		uint32_t gen_uteb: 2;
		uint32_t gen_ut0: 2;
		uint32_t gen_ut1: 2;
		uint32_t gen_dtez: 2;
		uint32_t gen_dtep: 2;
		uint32_t gen_dtea: 2;
		uint32_t gen_dteb: 2;
		uint32_t gen_dt0: 2;
		uint32_t gen_dt1: 2;
		uint32_t reserved_24: 8;
	};
	uint32_t val;
} mcpwm_gen_reg_t;

typedef union {
	struct {
		uint32_t dt_fed_upmethod: 4;
		uint32_t dt_red_upmethod: 4;
		uint32_t dt_deb_mode: 1;
		uint32_t dt_a_outswap: 1;
		uint32_t dt_b_outswap: 1;
		uint32_t dt_red_insel: 1;
		uint32_t dt_fed_insel: 1;
		uint32_t dt_red_outinvert: 1;
		uint32_t dt_fed_outinvert: 1;
		uint32_t dt_a_outbypass: 1;
		uint32_t dt_b_outbypass: 1;
		uint32_t dt_clk_sel: 1;
		uint32_t reserved_18: 14;
	};
	uint32_t val;
} mcpwm_dt_cfg_reg_t;

typedef union {
	struct {
		uint32_t dt_fed: 16;
		uint32_t reserved_16: 16;
	};
	uint32_t val;
} mcpwm_dt_fed_cfg_reg_t;

typedef union {
	struct {
		uint32_t dt_red: 16;
		uint32_t reserved_16: 16;
	};
	uint32_t val;
} mcpwm_dt_red_cfg_reg_t;

typedef union {
	struct {
		uint32_t carrier_en: 1;
		uint32_t carrier_prescale: 4;
		uint32_t carrier_duty: 3;
		uint32_t carrier_oshtwth: 4;
		uint32_t carrier_out_invert: 1;
		uint32_t carrier_in_invert: 1;
		uint32_t reserved_14: 18;
	};
	uint32_t val;
} mcpwm_carrier_cfg_reg_t;

typedef union {
	struct {
		uint32_t fh_sw_cbc: 1;
		uint32_t fh_f2_cbc: 1;
		uint32_t fh_f1_cbc: 1;
		uint32_t fh_f0_cbc: 1;
		uint32_t fh_sw_ost: 1;
		uint32_t fh_f2_ost: 1;
		uint32_t fh_f1_ost: 1;
		uint32_t fh_f0_ost: 1;
		uint32_t fh_a_cbc_d: 2;
		uint32_t fh_a_cbc_u: 2;
		uint32_t fh_a_ost_d: 2;
		uint32_t fh_a_ost_u: 2;
		uint32_t fh_b_cbc_d: 2;
		uint32_t fh_b_cbc_u: 2;
		uint32_t fh_b_ost_d: 2;
		uint32_t fh_b_ost_u: 2;
		uint32_t reserved_24: 8;
	};
	uint32_t val;
} mcpwm_fh_cfg0_reg_t;

typedef union {
	struct {
		uint32_t fh_clr_ost: 1;
		uint32_t fh_cbcpulse: 2;
		uint32_t fh_force_cbc: 1;
		uint32_t fh_force_ost: 1;
		uint32_t reserved_5: 27;
	};
	uint32_t val;
} mcpwm_fh_cfg1_reg_t;

typedef union {
	struct {
		uint32_t fh_cbc_on: 1;
		uint32_t fh_ost_on: 1;
		uint32_t reserved_2: 30;
	};
	uint32_t val;
} mcpwm_fh_status_reg_t;

typedef union {
	struct {
		uint32_t f0_en: 1;
		uint32_t f1_en: 1;
		uint32_t f2_en: 1;
		uint32_t f0_pole: 1;
		uint32_t f1_pole: 1;
		uint32_t f2_pole: 1;
		uint32_t event_f0: 1;
		uint32_t event_f1: 1;
		uint32_t event_f2: 1;
		uint32_t reserved_9: 23;
	};
	uint32_t val;
} mcpwm_fault_detect_reg_t;

typedef union {
	struct {
		uint32_t cap_timer_en: 1;
		uint32_t cap_synci_en: 1;
		uint32_t cap_synci_sel: 3;
		uint32_t cap_sync_sw: 1;
		uint32_t reserved_6: 26;
	};
	uint32_t val;
} mcpwm_cap_timer_cfg_reg_t;

typedef union {
	struct {
		uint32_t cap_timer_phase: 32;
	};
	uint32_t val;
} mcpwm_cap_timer_phase_reg_t;

typedef union {
	struct {
		uint32_t capn_en: 1;
		uint32_t capn_mode: 2;
		uint32_t capn_prescale: 8;
		uint32_t capn_in_invert: 1;
		uint32_t capn_sw: 1;
		uint32_t reserved_13: 19;
	};
	uint32_t val;
} mcpwm_cap_chn_cfg_reg_t;

typedef union {
	struct {
		uint32_t capn_value: 32;
	};
	uint32_t val;
} mcpwm_cap_chn_reg_t;

typedef union {
	struct {
		uint32_t cap0_edge: 1;
		uint32_t cap1_edge: 1;
		uint32_t cap2_edge: 1;
		uint32_t reserved_3: 29;
	};
	uint32_t val;
} mcpwm_cap_status_reg_t;

typedef union {
	struct {
		uint32_t global_up_en: 1;
		uint32_t global_force_up: 1;
		uint32_t op0_up_en: 1;
		uint32_t op0_force_up: 1;
		uint32_t op1_up_en: 1;
		uint32_t op1_force_up: 1;
		uint32_t op2_up_en: 1;
		uint32_t op2_force_up: 1;
		uint32_t reserved_8: 24;
	};
	uint32_t val;
} mcpwm_update_cfg_reg_t;

typedef union {
	struct {
		uint32_t timer0_stop_int_ena: 1;
		uint32_t timer1_stop_int_ena: 1;
		uint32_t timer2_stop_int_ena: 1;
		uint32_t timer0_tez_int_ena: 1;
		uint32_t timer1_tez_int_ena: 1;
		uint32_t timer2_tez_int_ena: 1;
		uint32_t timer0_tep_int_ena: 1;
		uint32_t timer1_tep_int_ena: 1;
		uint32_t timer2_tep_int_ena: 1;
		uint32_t fault0_int_ena: 1;
		uint32_t fault1_int_ena: 1;
		uint32_t fault2_int_ena: 1;
		uint32_t fault0_clr_int_ena: 1;
		uint32_t fault1_clr_int_ena: 1;
		uint32_t fault2_clr_int_ena: 1;
		uint32_t op0_tea_int_ena: 1;
		uint32_t op1_tea_int_ena: 1;
		uint32_t op2_tea_int_ena: 1;
		uint32_t op0_teb_int_ena: 1;
		uint32_t op1_teb_int_ena: 1;
		uint32_t op2_teb_int_ena: 1;
		uint32_t fh0_cbc_int_ena: 1;
		uint32_t fh1_cbc_int_ena: 1;
		uint32_t fh2_cbc_int_ena: 1;
		uint32_t fh0_ost_int_ena: 1;
		uint32_t fh1_ost_int_ena: 1;
		uint32_t fh2_ost_int_ena: 1;
		uint32_t cap0_int_ena: 1;
		uint32_t cap1_int_ena: 1;
		uint32_t cap2_int_ena: 1;
		uint32_t reserved_30: 2;
	};
	uint32_t val;
} mcpwm_int_ena_reg_t;

typedef union {
	struct {
		uint32_t timer0_stop_int_raw: 1;
		uint32_t timer1_stop_int_raw: 1;
		uint32_t timer2_stop_int_raw: 1;
		uint32_t timer0_tez_int_raw: 1;
		uint32_t timer1_tez_int_raw: 1;
		uint32_t timer2_tez_int_raw: 1;
		uint32_t timer0_tep_int_raw: 1;
		uint32_t timer1_tep_int_raw: 1;
		uint32_t timer2_tep_int_raw: 1;
		uint32_t fault0_int_raw: 1;
		uint32_t fault1_int_raw: 1;
		uint32_t fault2_int_raw: 1;
		uint32_t fault0_clr_int_raw: 1;
		uint32_t fault1_clr_int_raw: 1;
		uint32_t fault2_clr_int_raw: 1;
		uint32_t op0_tea_int_raw: 1;
		uint32_t op1_tea_int_raw: 1;
		uint32_t op2_tea_int_raw: 1;
		uint32_t op0_teb_int_raw: 1;
		uint32_t op1_teb_int_raw: 1;
		uint32_t op2_teb_int_raw: 1;
		uint32_t fh0_cbc_int_raw: 1;
		uint32_t fh1_cbc_int_raw: 1;
		uint32_t fh2_cbc_int_raw: 1;
		uint32_t fh0_ost_int_raw: 1;
		uint32_t fh1_ost_int_raw: 1;
		uint32_t fh2_ost_int_raw: 1;
		uint32_t cap0_int_raw: 1;
		uint32_t cap1_int_raw: 1;
		uint32_t cap2_int_raw: 1;
		uint32_t reserved_30: 2;
	};
	uint32_t val;
} mcpwm_int_raw_reg_t;

typedef union {
	struct {
		uint32_t timer0_stop_int_st: 1;
		uint32_t timer1_stop_int_st: 1;
		uint32_t timer2_stop_int_st: 1;
		uint32_t timer0_tez_int_st: 1;
		uint32_t timer1_tez_int_st: 1;
		uint32_t timer2_tez_int_st: 1;
		uint32_t timer0_tep_int_st: 1;
		uint32_t timer1_tep_int_st: 1;
		uint32_t timer2_tep_int_st: 1;
		uint32_t fault0_int_st: 1;
		uint32_t fault1_int_st: 1;
		uint32_t fault2_int_st: 1;
		uint32_t fault0_clr_int_st: 1;
		uint32_t fault1_clr_int_st: 1;
		uint32_t fault2_clr_int_st: 1;
		uint32_t op0_tea_int_st: 1;
		uint32_t op1_tea_int_st: 1;
		uint32_t op2_tea_int_st: 1;
		uint32_t op0_teb_int_st: 1;
		uint32_t op1_teb_int_st: 1;
		uint32_t op2_teb_int_st: 1;
		uint32_t fh0_cbc_int_st: 1;
		uint32_t fh1_cbc_int_st: 1;
		uint32_t fh2_cbc_int_st: 1;
		uint32_t fh0_ost_int_st: 1;
		uint32_t fh1_ost_int_st: 1;
		uint32_t fh2_ost_int_st: 1;
		uint32_t cap0_int_st: 1;
		uint32_t cap1_int_st: 1;
		uint32_t cap2_int_st: 1;
		uint32_t reserved_30: 2;
	};
	uint32_t val;
} mcpwm_int_st_reg_t;

typedef union {
	struct {
		uint32_t timer0_stop_int_clr: 1;
		uint32_t timer1_stop_int_clr: 1;
		uint32_t timer2_stop_int_clr: 1;
		uint32_t timer0_tez_int_clr: 1;
		uint32_t timer1_tez_int_clr: 1;
		uint32_t timer2_tez_int_clr: 1;
		uint32_t timer0_tep_int_clr: 1;
		uint32_t timer1_tep_int_clr: 1;
		uint32_t timer2_tep_int_clr: 1;
		uint32_t fault0_int_clr: 1;
		uint32_t fault1_int_clr: 1;
		uint32_t fault2_int_clr: 1;
		uint32_t fault0_clr_int_clr: 1;
		uint32_t fault1_clr_int_clr: 1;
		uint32_t fault2_clr_int_clr: 1;
		uint32_t op0_tea_int_clr: 1;
		uint32_t op1_tea_int_clr: 1;
		uint32_t op2_tea_int_clr: 1;
		uint32_t op0_teb_int_clr: 1;
		uint32_t op1_teb_int_clr: 1;
		uint32_t op2_teb_int_clr: 1;
		uint32_t fh0_cbc_int_clr: 1;
		uint32_t fh1_cbc_int_clr: 1;
		uint32_t fh2_cbc_int_clr: 1;
		uint32_t fh0_ost_int_clr: 1;
		uint32_t fh1_ost_int_clr: 1;
		uint32_t fh2_ost_int_clr: 1;
		uint32_t cap0_int_clr: 1;
		uint32_t cap1_int_clr: 1;
		uint32_t cap2_int_clr: 1;
		uint32_t reserved_30: 2;
	};
	uint32_t val;
} mcpwm_int_clr_reg_t;

typedef union {
	struct {
		uint32_t clk_en: 1;
		uint32_t reserved_1: 31;
	};
	uint32_t val;
} mcpwm_clk_reg_t;

typedef union {
	struct {
		uint32_t date: 28;
		uint32_t reserved_28: 4;
	};
	uint32_t val;
} mcpwm_version_reg_t;

typedef struct {
	mcpwm_timer_cfg0_reg_t timer_cfg0;
	mcpwm_timer_cfg1_reg_t timer_cfg1;
	mcpwm_timer_sync_reg_t timer_sync;
	mcpwm_timer_status_reg_t timer_status;
} mcpwm_timer_regs_t;

typedef struct {
	mcpwm_gen_stmp_cfg_reg_t gen_stmp_cfg;
	mcpwm_gen_tstmp_reg_t timestamp[2];
	mcpwm_gen_cfg0_reg_t gen_cfg0;
	mcpwm_gen_force_reg_t gen_force;
	mcpwm_gen_reg_t generator[2];
	mcpwm_dt_cfg_reg_t dt_cfg;
	mcpwm_dt_fed_cfg_reg_t dt_fed_cfg;
	mcpwm_dt_red_cfg_reg_t dt_red_cfg;
	mcpwm_carrier_cfg_reg_t carrier_cfg;
	mcpwm_fh_cfg0_reg_t fh_cfg0;
	mcpwm_fh_cfg1_reg_t fh_cfg1;
	mcpwm_fh_status_reg_t fh_status;
} mcpwm_operator_reg_t;

typedef enum {
	MCPWM_TIMER_STOP_AT_ZERO,       /*!< MCPWM timer stops when couting to zero */
	MCPWM_TIMER_STOP_AT_PEAK,       /*!< MCPWM timer stops when counting to peak */
	MCPWM_TIMER_START_NO_STOP,      /*!< MCPWM timer starts couting */
	MCPWM_TIMER_START_STOP_AT_ZERO, /*!< MCPWM timer starts counting and stops when couting to zero */
	MCPWM_TIMER_START_STOP_AT_PEAK, /*!< MCPWM timer starts counting and stops when counting to peak */
} mcpwm_timer_execute_cmd_t;


typedef struct mcpwm_dev_t {
	volatile mcpwm_clk_cfg_reg_t clk_cfg;
	volatile mcpwm_timer_regs_t timer[3];
	volatile mcpwm_timer_synci_cfg_reg_t timer_synci_cfg;
	volatile mcpwm_operator_timersel_reg_t operator_timersel;
	volatile mcpwm_operator_reg_t operators[3];
	volatile mcpwm_fault_detect_reg_t fault_detect;
	volatile mcpwm_cap_timer_cfg_reg_t cap_timer_cfg;
	volatile mcpwm_cap_timer_phase_reg_t cap_timer_phase;
	volatile mcpwm_cap_chn_cfg_reg_t cap_chn_cfg[3];
	volatile mcpwm_cap_chn_reg_t cap_chn[3];
	volatile mcpwm_cap_status_reg_t cap_status;
	volatile mcpwm_update_cfg_reg_t update_cfg;
	volatile mcpwm_int_ena_reg_t int_ena;
	volatile mcpwm_int_raw_reg_t int_raw;
	volatile mcpwm_int_st_reg_t int_st;
	volatile mcpwm_int_clr_reg_t int_clr;
	volatile mcpwm_clk_reg_t clk;
	volatile mcpwm_version_reg_t version;
} mcpwm_dev_t;

extern mcpwm_dev_t MCPWM0;
extern mcpwm_dev_t MCPWM1;

void mcpwm_ll_group_set_clock_prescale(mcpwm_dev_t *mcpwm, int pre_scale);
uint32_t mcpwm_ll_group_get_clock_prescale(mcpwm_dev_t *mcpwm);
void mcpwm_ll_group_enable_shadow_mode(mcpwm_dev_t *mcpwm);
void mcpwm_ll_group_flush_shadow(mcpwm_dev_t *mcpwm);
uint32_t mcpwm_ll_intr_get_status(mcpwm_dev_t *mcpwm);
void mcpwm_ll_intr_clear_status(mcpwm_dev_t *mcpwm, uint32_t intr_mask);
void mcpwm_ll_intr_disable_all(mcpwm_dev_t *mcpwm);
uint32_t mcpwm_ll_intr_get_timer_stop_status(mcpwm_dev_t *mcpwm);
uint32_t mcpwm_ll_intr_get_timer_tez_status(mcpwm_dev_t *mcpwm);
uint32_t mcpwm_ll_intr_get_timer_tep_status(mcpwm_dev_t *mcpwm);
uint32_t mcpwm_ll_intr_get_fault_enter_status(mcpwm_dev_t *mcpwm);
uint32_t mcpwm_ll_intr_get_fault_exit_status(mcpwm_dev_t *mcpwm);
uint32_t mcpwm_ll_intr_get_compare_status(mcpwm_dev_t *mcpwm, uint32_t cmp_id);
uint32_t mcpwm_ll_intr_get_trip_cbc_status(mcpwm_dev_t *mcpwm);
uint32_t mcpwm_ll_intr_get_trip_ost_status(mcpwm_dev_t *mcpwm);
uint32_t mcpwm_ll_intr_get_capture_status(mcpwm_dev_t *mcpwm);
void mcpwm_ll_intr_clear_timer_stop_status(mcpwm_dev_t *mcpwm, uint32_t timer_mask);
void mcpwm_ll_intr_clear_timer_tez_status(mcpwm_dev_t *mcpwm, uint32_t timer_mask);
void mcpwm_ll_intr_clear_timer_tep_status(mcpwm_dev_t *mcpwm, uint32_t timer_mask);
void mcpwm_ll_intr_clear_fault_enter_status(mcpwm_dev_t *mcpwm, uint32_t fault_mask);
void mcpwm_ll_intr_clear_fault_exit_status(mcpwm_dev_t *mcpwm, uint32_t fault_mask);
void mcpwm_ll_intr_clear_compare_status(mcpwm_dev_t *mcpwm, uint32_t operator_mask, uint32_t cmp_id);
void mcpwm_ll_intr_clear_trip_cbc_status(mcpwm_dev_t *mcpwm, uint32_t cbc_mask);
void mcpwm_ll_intr_clear_trip_ost_status(mcpwm_dev_t *mcpwm, uint32_t ost_mask);
void mcpwm_ll_intr_clear_capture_status(mcpwm_dev_t *mcpwm, uint32_t capture_mask);
void mcpwm_ll_intr_enable_timer_stop(mcpwm_dev_t *mcpwm, uint32_t timer_id, bool enable);
void mcpwm_ll_intr_enable_timer_tez(mcpwm_dev_t *mcpwm, uint32_t timer_id, bool enable);
void mcpwm_ll_intr_enable_timer_tep(mcpwm_dev_t *mcpwm, uint32_t timer_id, bool enable);
void mcpwm_ll_intr_enable_fault_enter(mcpwm_dev_t *mcpwm, uint32_t fault_id, bool enable);
void mcpwm_ll_intr_enable_fault_exit(mcpwm_dev_t *mcpwm, uint32_t fault_id, bool enable);
void mcpwm_ll_intr_enable_compare(mcpwm_dev_t *mcpwm, uint32_t operator_id, uint32_t cmp_id, bool enable);
void mcpwm_ll_intr_enable_trip_cbc(mcpwm_dev_t *mcpwm, uint32_t operator_id, bool enable);
void mcpwm_ll_intr_enable_trip_ost(mcpwm_dev_t *mcpwm, uint32_t operator_id, bool enable);
void mcpwm_ll_intr_enable_capture(mcpwm_dev_t *mcpwm, uint32_t capture_id, bool enable);
void mcpwm_ll_timer_set_clock_prescale(mcpwm_dev_t *mcpwm, int timer_id, uint32_t prescale);
uint32_t mcpwm_ll_timer_get_clock_prescale(mcpwm_dev_t *mcpwm, int timer_id);
void mcpwm_ll_timer_set_peak(mcpwm_dev_t *mcpwm, int timer_id, uint32_t peak, bool symmetric);
uint32_t mcpwm_ll_timer_get_peak(mcpwm_dev_t *mcpwm, int timer_id, bool symmetric);
void mcpwm_ll_timer_update_period_at_once(mcpwm_dev_t *mcpwm, int timer_id);
void mcpwm_ll_timer_enable_update_period_on_tez(mcpwm_dev_t *mcpwm, int timer_id, bool enable);
void mcpwm_ll_timer_enable_update_period_on_sync(mcpwm_dev_t *mcpwm, int timer_id, bool enable);
void mcpwm_ll_timer_set_count_mode(mcpwm_dev_t *mcpwm, int timer_id, mcpwm_timer_count_mode_t mode);
mcpwm_timer_count_mode_t mcpwm_ll_timer_get_count_mode(mcpwm_dev_t *mcpwm, int timer_id);
void mcpwm_ll_timer_set_execute_command(mcpwm_dev_t *mcpwm, int timer_id, mcpwm_timer_execute_cmd_t cmd);
uint32_t mcpwm_ll_timer_get_count_value(mcpwm_dev_t *mcpwm, int timer_id);
mcpwm_timer_direction_t mcpwm_ll_timer_get_count_direction(mcpwm_dev_t *mcpwm, int timer_id);
void mcpwm_ll_timer_enable_sync_input(mcpwm_dev_t *mcpwm, int timer_id, bool enable);
void mcpwm_ll_timer_sync_out_penetrate(mcpwm_dev_t *mcpwm, int timer_id);
void mcpwm_ll_timer_sync_out_on_timer_event(mcpwm_dev_t *mcpwm, int timer_id, mcpwm_timer_event_t event);
void mcpwm_ll_timer_disable_sync_out(mcpwm_dev_t *mcpwm, int timer_id);
void mcpwm_ll_timer_trigger_soft_sync(mcpwm_dev_t *mcpwm, int timer_id);
void mcpwm_ll_timer_set_sync_phase_value(mcpwm_dev_t *mcpwm, int timer_id, uint32_t phase_value);
void mcpwm_ll_timer_set_sync_phase_direction(mcpwm_dev_t *mcpwm, int timer_id, mcpwm_timer_direction_t direction);
void mcpwm_ll_timer_set_gpio_synchro(mcpwm_dev_t *mcpwm, int timer, int gpio_sync_id);
void mcpwm_ll_timer_set_timer_synchro(mcpwm_dev_t *mcpwm, int timer, int timer_sync_id);
void mcpwm_ll_timer_set_soft_synchro(mcpwm_dev_t *mcpwm, int timer);
void mcpwm_ll_invert_gpio_synchro(mcpwm_dev_t *mcpwm, int sync_id, bool invert);
void mcpwm_ll_operator_flush_shadow(mcpwm_dev_t *mcpwm, int operator_id);
void mcpwm_ll_operator_select_timer(mcpwm_dev_t *mcpwm, int operator_id, int timer_id);
void mcpwm_ll_operator_update_compare_at_once(mcpwm_dev_t *mcpwm, int operator_id, int compare_id);
void mcpwm_ll_operator_enable_update_compare_on_tez(mcpwm_dev_t *mcpwm, int operator_id, int compare_id, bool enable);
void mcpwm_ll_operator_enable_update_compare_on_tep(mcpwm_dev_t *mcpwm, int operator_id, int compare_id, bool enable);
void mcpwm_ll_operator_enable_update_compare_on_sync(mcpwm_dev_t *mcpwm, int operator_id, int compare_id, bool enable);
void mcpwm_ll_operator_set_compare_value(mcpwm_dev_t *mcpwm, int operator_id, int compare_id, uint32_t compare_value);
uint32_t mcpwm_ll_operator_get_compare_value(mcpwm_dev_t *mcpwm, int operator_id, int compare_id);
void mcpwm_ll_operator_update_action_at_once(mcpwm_dev_t *mcpwm, int operator_id);
void mcpwm_ll_operator_enable_update_action_on_tez(mcpwm_dev_t *mcpwm, int operator_id, bool enable);
void mcpwm_ll_operator_enable_update_action_on_tep(mcpwm_dev_t *mcpwm, int operator_id, bool enable);
void mcpwm_ll_operator_enable_update_action_on_sync(mcpwm_dev_t *mcpwm, int operator_id, bool enable);
void mcpwm_ll_operator_set_trigger_gpio_fault(mcpwm_dev_t *mcpwm, int operator_id, int trig_id, int fault_id);
void mcpwm_ll_operator_set_trigger_timer_sync(mcpwm_dev_t *mcpwm, int operator_id, int trig_id);
void mcpwm_ll_generator_reset_actions(mcpwm_dev_t *mcpwm, int operator_id, int generator_id);
void mcpwm_ll_generator_set_action_on_timer_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id, mcpwm_timer_direction_t direction, mcpwm_timer_event_t event, mcpwm_generator_action_t action);
void mcpwm_ll_generator_set_action_on_compare_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id, mcpwm_timer_direction_t direction, int cmp_id, int action);
void mcpwm_ll_generator_set_action_on_trigger_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id, mcpwm_timer_direction_t direction, int trig_id, int action);
void mcpwm_ll_gen_trigger_noncontinue_force_action(mcpwm_dev_t *mcpwm, int operator_id, int generator_id);
void mcpwm_ll_gen_disable_continue_force_action(mcpwm_dev_t *mcpwm, int operator_id, int generator_id);
void mcpwm_ll_gen_disable_noncontinue_force_action(mcpwm_dev_t *mcpwm, int operator_id, int generator_id);
void mcpwm_ll_gen_set_continue_force_level(mcpwm_dev_t *mcpwm, int operator_id, int generator_id, int level);
void mcpwm_ll_gen_set_noncontinue_force_level(mcpwm_dev_t *mcpwm, int operator_id, int generator_id, int level);
void mcpwm_ll_deadtime_resolution_to_timer(mcpwm_dev_t *mcpwm, int operator_id, bool same);
void mcpwm_ll_deadtime_red_select_generator(mcpwm_dev_t *mcpwm, int operator_id, int generator);
void mcpwm_ll_deadtime_fed_select_generator(mcpwm_dev_t *mcpwm, int operator_id, int generator);
void mcpwm_ll_deadtime_bypass_path(mcpwm_dev_t *mcpwm, int operator_id, int path, bool bypass);
void mcpwm_ll_deadtime_invert_outpath(mcpwm_dev_t *mcpwm, int operator_id, int path, bool invert);
void mcpwm_ll_deadtime_swap_out_path(mcpwm_dev_t *mcpwm, int operator_id, int path, bool swap);
void mcpwm_ll_deadtime_enable_deb(mcpwm_dev_t *mcpwm, int operator_id, bool enable);
uint32_t mcpwm_ll_deadtime_get_switch_topology(mcpwm_dev_t *mcpwm, int operator_id);
void mcpwm_ll_deadtime_set_falling_delay(mcpwm_dev_t *mcpwm, int operator_id, uint32_t fed);
uint32_t mcpwm_ll_deadtime_get_falling_delay(mcpwm_dev_t *mcpwm, int operator_id);
void mcpwm_ll_deadtime_set_rising_delay(mcpwm_dev_t *mcpwm, int operator_id, uint32_t red);
uint32_t mcpwm_ll_deadtime_get_rising_delay(mcpwm_dev_t *mcpwm, int operator_id);
void mcpwm_ll_deadtime_update_delay_at_once(mcpwm_dev_t *mcpwm, int operator_id);
void mcpwm_ll_deadtime_enable_update_delay_on_tez(mcpwm_dev_t *mcpwm, int operator_id, bool enable);
void mcpwm_ll_deadtime_enable_update_delay_on_tep(mcpwm_dev_t *mcpwm, int operator_id, bool enable);
void mcpwm_ll_deadtime_enable_update_delay_on_sync(mcpwm_dev_t *mcpwm, int operator_id, bool enable);
void mcpwm_ll_carrier_enable(mcpwm_dev_t *mcpwm, int operator_id, bool enable);
void mcpwm_ll_carrier_set_prescale(mcpwm_dev_t *mcpwm, int operator_id, uint8_t prescale);
uint8_t mcpwm_ll_carrier_get_prescale(mcpwm_dev_t *mcpwm, int operator_id);
void mcpwm_ll_carrier_set_duty(mcpwm_dev_t *mcpwm, int operator_id, uint8_t carrier_duty);
uint8_t mcpwm_ll_carrier_get_duty(mcpwm_dev_t *mcpwm, int operator_id);
void mcpwm_ll_carrier_out_invert(mcpwm_dev_t *mcpwm, int operator_id, bool invert);
void mcpwm_ll_carrier_in_invert(mcpwm_dev_t *mcpwm, int operator_id, bool invert);
void mcpwm_ll_carrier_set_oneshot_width(mcpwm_dev_t *mcpwm, int operator_id, uint8_t pulse_width);
uint8_t mcpwm_ll_carrier_get_oneshot_width(mcpwm_dev_t *mcpwm, int operator_id);
void mcpwm_ll_fault_enable_detection(mcpwm_dev_t *mcpwm, int fault_sig, bool enable);
void mcpwm_ll_fault_set_active_level(mcpwm_dev_t *mcpwm, int fault_sig, bool level);
void mcpwm_ll_fault_clear_ost(mcpwm_dev_t *mcpwm, int operator_id);
void mcpwm_ll_fault_enable_oneshot_mode(mcpwm_dev_t *mcpwm, int operator_id, int fault_sig, bool enable);
void mcpwm_ll_fault_enable_cbc_mode(mcpwm_dev_t *mcpwm, int operator_id, int fault_sig, bool enable);
void mcpwm_ll_fault_enable_cbc_refresh_on_tez(mcpwm_dev_t *mcpwm, int operator_id, bool enable);
void mcpwm_ll_fault_enable_cbc_refresh_on_tep(mcpwm_dev_t *mcpwm, int operator_id, bool enable);
void mcpwm_ll_fault_enable_sw_cbc(mcpwm_dev_t *mcpwm, int operator_id, bool enable);
void mcpwm_ll_fault_enable_sw_oneshot(mcpwm_dev_t *mcpwm, int operator_id, bool enable);
void mcpwm_ll_fault_trigger_sw_cbc(mcpwm_dev_t *mcpwm, int operator_id);
void mcpwm_ll_fault_trigger_sw_ost(mcpwm_dev_t *mcpwm, int operator_id);
void mcpwm_ll_generator_set_action_on_trip_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id, mcpwm_timer_direction_t direction, mcpwm_trip_type_t trip, int action);
bool mcpwm_ll_fault_is_ost_on(mcpwm_dev_t *mcpwm, int op);
bool mcpwm_ll_fault_is_cbc_on(mcpwm_dev_t *mcpwm, int op);
void mcpwm_ll_capture_enable_timer(mcpwm_dev_t *mcpwm, bool enable);
void mcpwm_ll_capture_enable_channel(mcpwm_dev_t *mcpwm, int channel, bool enable);
void mcpwm_ll_capture_set_sync_phase_value(mcpwm_dev_t *mcpwm, uint32_t phase_value);
uint32_t mcpwm_ll_capture_get_sync_phase_value(mcpwm_dev_t *mcpwm);
void mcpwm_ll_capture_enable_timer_sync(mcpwm_dev_t *mcpwm, bool enable);
void mcpwm_ll_capture_set_internal_timer_synchro(mcpwm_dev_t *mcpwm, int sync_out_timer);
void mcpwm_ll_capture_set_external_synchro(mcpwm_dev_t *mcpwm, int extern_synchro);
void mcpwm_ll_capture_trigger_sw_sync(mcpwm_dev_t *mcpwm);
void mcpwm_ll_capture_enable_posedge(mcpwm_dev_t *mcpwm, int channel, bool enable);
void mcpwm_ll_capture_enable_negedge(mcpwm_dev_t *mcpwm, int channel, bool enable);
void mcpwm_ll_invert_input(mcpwm_dev_t *mcpwm, int channel, bool invert);
void mcpwm_ll_trigger_soft_capture(mcpwm_dev_t *mcpwm, int channel);
uint32_t mcpwm_ll_capture_get_value(mcpwm_dev_t *mcpwm, int channel);
bool mcpwm_ll_capture_is_negedge(mcpwm_dev_t *mcpwm, int channel);
void mcpwm_ll_capture_set_prescale(mcpwm_dev_t *mcpwm, int channel, uint32_t prescale);
uint32_t mcpwm_ll_capture_get_prescale(mcpwm_dev_t *mcpwm, int channel);

void mcpwm_ll_timer_set_execute_command(mcpwm_dev_t *mcpwm, int timer_id, mcpwm_timer_execute_cmd_t cmd);
