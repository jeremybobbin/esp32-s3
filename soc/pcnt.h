#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
//#include "freertos/FreeRTOS.h"
#include "soc/intr-alloc.h"
//#include "driver/gpio.h"
//#include "soc/soc_caps.h"
//#include "hal/pcnt_types.h"






#define PCNT_PIN_NOT_USED	  (-1)

typedef intr_handle_t pcnt_isr_handle_t;

typedef enum {
	PCNT_PORT_0,
	PCNT_PORT_MAX,
} pcnt_port_t;

typedef enum {
	PCNT_UNIT_0,
	PCNT_UNIT_1,
	PCNT_UNIT_2,
	PCNT_UNIT_3,
	PCNT_UNIT_MAX,
} pcnt_unit_t;

typedef enum {
	PCNT_CHANNEL_0,
	PCNT_CHANNEL_1,
	PCNT_CHANNEL_MAX,
} pcnt_channel_t;


typedef enum {
	PCNT_EVT_THRES_1 = 1 << 2,
	PCNT_EVT_THRES_0 = 1 << 3,
	PCNT_EVT_L_LIM = 1 << 4,
	PCNT_EVT_H_LIM = 1 << 5,
	PCNT_EVT_ZERO = 1 << 6,
	PCNT_EVT_MAX
} pcnt_evt_type_t;

typedef enum {
	PCNT_CHANNEL_EDGE_ACTION_HOLD,     /*!< Hold current count value */
	PCNT_CHANNEL_EDGE_ACTION_INCREASE, /*!< Increase count value */
	PCNT_CHANNEL_EDGE_ACTION_DECREASE, /*!< Decrease count value */
} pcnt_channel_edge_action_t;

typedef enum {
	PCNT_CHANNEL_LEVEL_ACTION_KEEP,    /*!< Keep current count mode */
	PCNT_CHANNEL_LEVEL_ACTION_INVERSE, /*!< Invert current count mode (increase -> decrease, decrease -> increase) */
	PCNT_CHANNEL_LEVEL_ACTION_HOLD,    /*!< Hold current count value */
} pcnt_channel_level_action_t;

typedef enum {
	PCNT_UNIT_COUNT_SIGN_ZERO_POS, /*!< positive value to zero */
	PCNT_UNIT_COUNT_SIGN_ZERO_NEG, /*!< negative value to zero */
	PCNT_UNIT_COUNT_SIGN_NEG,      /*!< counter value negative */
	PCNT_UNIT_COUNT_SIGN_POS,      /*!< counter value positive */
} pcnt_unit_count_sign_t;


typedef pcnt_channel_level_action_t pcnt_ctrl_mode_t;
#define PCNT_MODE_KEEP	  PCNT_CHANNEL_LEVEL_ACTION_KEEP
#define PCNT_MODE_REVERSE PCNT_CHANNEL_LEVEL_ACTION_INVERSE
#define PCNT_MODE_DISABLE PCNT_CHANNEL_LEVEL_ACTION_HOLD
#define PCNT_MODE_MAX	  3


typedef pcnt_channel_edge_action_t pcnt_count_mode_t;
#define PCNT_COUNT_DIS PCNT_CHANNEL_EDGE_ACTION_HOLD
#define PCNT_COUNT_INC PCNT_CHANNEL_EDGE_ACTION_INCREASE
#define PCNT_COUNT_DEC PCNT_CHANNEL_EDGE_ACTION_DECREASE
#define PCNT_COUNT_MAX 3


typedef struct {
	int pulse_gpio_num;
	int ctrl_gpio_num;
	pcnt_ctrl_mode_t lctrl_mode;
	pcnt_ctrl_mode_t hctrl_mode;
	pcnt_count_mode_t pos_mode;
	pcnt_count_mode_t neg_mode;
	int16_t counter_h_lim;
	int16_t counter_l_lim;
	pcnt_unit_t unit;
	pcnt_channel_t channel;
} pcnt_config_t;


int pcnt_unit_config(const pcnt_config_t *pcnt_config);
int pcnt_get_counter_value(pcnt_unit_t pcnt_unit, int16_t *count);
int pcnt_counter_pause(pcnt_unit_t pcnt_unit);
int pcnt_counter_resume(pcnt_unit_t pcnt_unit);
int pcnt_counter_clear(pcnt_unit_t pcnt_unit);
int pcnt_intr_enable(pcnt_unit_t pcnt_unit);
int pcnt_intr_disable(pcnt_unit_t pcnt_unit);
int pcnt_event_enable(pcnt_unit_t unit, pcnt_evt_type_t evt_type);
int pcnt_event_disable(pcnt_unit_t unit, pcnt_evt_type_t evt_type);
int pcnt_set_event_value(pcnt_unit_t unit, pcnt_evt_type_t evt_type, int16_t value);
int pcnt_get_event_value(pcnt_unit_t unit, pcnt_evt_type_t evt_type, int16_t *value);
int pcnt_get_event_status(pcnt_unit_t unit, uint32_t *status);
int pcnt_isr_unregister(pcnt_isr_handle_t handle);
int pcnt_isr_register(void (*fn)(void *), void *arg, int intr_alloc_flags, pcnt_isr_handle_t *handle);
int pcnt_set_pin(pcnt_unit_t unit, pcnt_channel_t channel, int pulse_io, int ctrl_io);
int pcnt_filter_enable(pcnt_unit_t unit);
int pcnt_filter_disable(pcnt_unit_t unit);
int pcnt_set_filter_value(pcnt_unit_t unit, uint16_t filter_val);
int pcnt_get_filter_value(pcnt_unit_t unit, uint16_t *filter_val);
int pcnt_set_mode(pcnt_unit_t unit, pcnt_channel_t channel, pcnt_count_mode_t pos_mode, pcnt_count_mode_t neg_mode, pcnt_ctrl_mode_t hctrl_mode, pcnt_ctrl_mode_t lctrl_mode);
int pcnt_isr_handler_add(pcnt_unit_t unit, void(*isr_handler)(void *), void *args);
int pcnt_isr_service_install(int intr_alloc_flags);
void pcnt_isr_service_uninstall(void);
int pcnt_isr_handler_remove(pcnt_unit_t unit);







#define PCNT_LL_GET_HW(num) (((num) == 0) ? (&PCNT) : NULL)
#define PCNT_LL_MAX_GLITCH_WIDTH 1023

typedef enum {
	PCNT_LL_EVENT_THRES1,
	PCNT_LL_EVENT_THRES0,
	PCNT_LL_EVENT_LOW_LIMIT,
	PCNT_LL_EVENT_HIGH_LIMIT,
	PCNT_LL_EVENT_ZERO_CROSS,
	PCNT_LL_EVENT_MAX
} pcnt_ll_event_id_t;

#define PCNT_LL_EVENT_MASK ((1 << PCNT_LL_EVENT_MAX) - 1)

typedef union {
	struct {
		uint32_t filter_thres_un: 10;
		uint32_t filter_en_un: 1;
		uint32_t thr_zero_en_un: 1;
		uint32_t thr_h_lim_en_un: 1;
		uint32_t thr_l_lim_en_un: 1;
		uint32_t thr_thres0_en_un: 1;
		uint32_t thr_thres1_en_un: 1;
		uint32_t ch0_neg_mode_un: 2;
		uint32_t ch0_pos_mode_un: 2;
		uint32_t ch0_hctrl_mode_un: 2;
		uint32_t ch0_lctrl_mode_un: 2;
		uint32_t ch1_neg_mode_un: 2;
		uint32_t ch1_pos_mode_un: 2;
		uint32_t ch1_hctrl_mode_un: 2;
		uint32_t ch1_lctrl_mode_un: 2;
	};
	uint32_t val;
} pcnt_un_conf0_reg_t;

typedef union {
	struct {
		uint32_t cnt_thres0_un: 16;
		uint32_t cnt_thres1_un: 16;
	};
	uint32_t val;
} pcnt_un_conf1_reg_t;

typedef union {
	struct {
		uint32_t cnt_h_lim_un: 16;
		uint32_t cnt_l_lim_un: 16;
	};
	uint32_t val;
} pcnt_un_conf2_reg_t;


typedef union {
	struct {
		uint32_t pulse_cnt_rst_u0: 1;
		uint32_t cnt_pause_u0: 1;
		uint32_t pulse_cnt_rst_u1: 1;
		uint32_t cnt_pause_u1: 1;
		uint32_t pulse_cnt_rst_u2: 1;
		uint32_t cnt_pause_u2: 1;
		uint32_t pulse_cnt_rst_u3: 1;
		uint32_t cnt_pause_u3: 1;
		uint32_t reserved_8: 8;
		uint32_t clk_en: 1;
		uint32_t reserved_17: 15;
	};
	uint32_t val;
} pcnt_ctrl_reg_t;


typedef union {
	struct {
		uint32_t pulse_cnt_un: 16;
		uint32_t reserved_16: 16;
	};
	uint32_t val;
} pcnt_un_cnt_reg_t;

typedef union {
	struct {
		uint32_t cnt_thr_zero_mode_un: 2;
		uint32_t cnt_thr_thres1_lat_un: 1;
		uint32_t cnt_thr_thres0_lat_un: 1;
		uint32_t cnt_thr_l_lim_lat_un: 1;
		uint32_t cnt_thr_h_lim_lat_un: 1;
		uint32_t cnt_thr_zero_lat_un: 1;
		uint32_t reserved_7: 25;
	};
	uint32_t val;
} pcnt_un_status_reg_t;


typedef union {
	struct {
		uint32_t cnt_thr_event_u0_int_raw: 1;
		uint32_t cnt_thr_event_u1_int_raw: 1;
		uint32_t cnt_thr_event_u2_int_raw: 1;
		uint32_t cnt_thr_event_u3_int_raw: 1;
		uint32_t reserved_4: 28;
	};
	uint32_t val;
} pcnt_int_raw_reg_t;

typedef union {
	struct {
		uint32_t cnt_thr_event_u0_int_st: 1;
		uint32_t cnt_thr_event_u1_int_st: 1;
		uint32_t cnt_thr_event_u2_int_st: 1;
		uint32_t cnt_thr_event_u3_int_st: 1;
		uint32_t reserved_4: 28;
	};
	uint32_t val;
} pcnt_int_st_reg_t;

typedef union {
	struct {
		uint32_t cnt_thr_event_u0_int_ena: 1;
		uint32_t cnt_thr_event_u1_int_ena: 1;
		uint32_t cnt_thr_event_u2_int_ena: 1;
		uint32_t cnt_thr_event_u3_int_ena: 1;
		uint32_t reserved_4: 28;
	};
	uint32_t val;
} pcnt_int_ena_reg_t;

typedef union {
	struct {
		uint32_t cnt_thr_event_u0_int_clr: 1;
		uint32_t cnt_thr_event_u1_int_clr: 1;
		uint32_t cnt_thr_event_u2_int_clr: 1;
		uint32_t cnt_thr_event_u3_int_clr: 1;
		uint32_t reserved_4: 28;
	};
	uint32_t val;
} pcnt_int_clr_reg_t;


typedef union {
	struct {
		uint32_t date: 32;
	};
	uint32_t val;
} pcnt_date_reg_t;


typedef struct {
	volatile struct {
		pcnt_un_conf0_reg_t conf0;
		pcnt_un_conf1_reg_t conf1;
		pcnt_un_conf2_reg_t conf2;
	} conf_unit[4];
	volatile pcnt_un_cnt_reg_t cnt_unit[4];
	volatile pcnt_int_raw_reg_t int_raw;
	volatile pcnt_int_st_reg_t int_st;
	volatile pcnt_int_ena_reg_t int_ena;
	volatile pcnt_int_clr_reg_t int_clr;
	volatile pcnt_un_status_reg_t status_unit[4];
	volatile pcnt_ctrl_reg_t ctrl;
	uint32_t reserved_064[38];
	volatile pcnt_date_reg_t date;
} pcnt_dev_t;

extern pcnt_dev_t PCNT;

void pcnt_ll_set_edge_action(pcnt_dev_t *hw, uint32_t unit, uint32_t channel, pcnt_channel_edge_action_t pos_act, pcnt_channel_edge_action_t neg_act);
void pcnt_ll_set_level_action(pcnt_dev_t *hw, uint32_t unit, uint32_t channel, pcnt_channel_level_action_t high_act, pcnt_channel_level_action_t low_act);
int pcnt_ll_get_count(pcnt_dev_t *hw, uint32_t unit);
void pcnt_ll_stop_count(pcnt_dev_t *hw, uint32_t unit);
void pcnt_ll_start_count(pcnt_dev_t *hw, uint32_t unit);
void pcnt_ll_clear_count(pcnt_dev_t *hw, uint32_t unit);
void pcnt_ll_enable_intr(pcnt_dev_t *hw, uint32_t unit_mask, bool enable);
uint32_t pcnt_ll_get_intr_status(pcnt_dev_t *hw);
void pcnt_ll_clear_intr_status(pcnt_dev_t *hw, uint32_t status);
void pcnt_ll_enable_high_limit_event(pcnt_dev_t *hw, uint32_t unit, bool enable);
void pcnt_ll_enable_low_limit_event(pcnt_dev_t *hw, uint32_t unit, bool enable);
void pcnt_ll_enable_zero_cross_event(pcnt_dev_t *hw, uint32_t unit, bool enable);
void pcnt_ll_enable_thres_event(pcnt_dev_t *hw, uint32_t unit, uint32_t thres, bool enable);
void pcnt_ll_disable_all_events(pcnt_dev_t *hw, uint32_t unit);
void pcnt_ll_set_high_limit_value(pcnt_dev_t *hw, uint32_t unit, int value);
void pcnt_ll_set_low_limit_value(pcnt_dev_t *hw, uint32_t unit, int value);
void pcnt_ll_set_thres_value(pcnt_dev_t *hw, uint32_t unit, uint32_t thres, int value);
int pcnt_ll_get_high_limit_value(pcnt_dev_t *hw, uint32_t unit);
int pcnt_ll_get_low_limit_value(pcnt_dev_t *hw, uint32_t unit);
int pcnt_ll_get_thres_value(pcnt_dev_t *hw, uint32_t unit, uint32_t thres);
uint32_t pcnt_ll_get_unit_status(pcnt_dev_t *hw, uint32_t unit);
pcnt_unit_count_sign_t pcnt_ll_get_count_sign(pcnt_dev_t *hw, uint32_t unit);
uint32_t pcnt_ll_get_event_status(pcnt_dev_t *hw, uint32_t unit);
void pcnt_ll_set_glitch_filter_thres(pcnt_dev_t *hw, uint32_t unit, uint32_t filter_val);
uint32_t pcnt_ll_get_glitch_filter_thres(pcnt_dev_t *hw, uint32_t unit);
void pcnt_ll_enable_glitch_filter(pcnt_dev_t *hw, uint32_t unit, bool enable);
