#include <stdlib.h>
#include <stdbool.h>

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
