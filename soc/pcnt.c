

// The LL layer for ESP32-S3 PCNT register operations


#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "soc/pcnt.h"


#define PCNT_LL_GET_HW(num) (((num) == 0) ? (&PCNT) : NULL)
#define PCNT_LL_MAX_GLITCH_WIDTH 1023

/*
typedef enum {
	PCNT_LL_EVENT_THRES1,
	PCNT_LL_EVENT_THRES0,
	PCNT_LL_EVENT_LOW_LIMIT,
	PCNT_LL_EVENT_HIGH_LIMIT,
	PCNT_LL_EVENT_ZERO_CROSS,
	PCNT_LL_EVENT_MAX
} pcnt_ll_event_id_t;
*/

#define PCNT_LL_EVENT_MASK ((1 << PCNT_LL_EVENT_MAX) - 1)

void pcnt_ll_set_edge_action(pcnt_dev_t *hw, uint32_t unit, uint32_t channel, pcnt_channel_edge_action_t pos_act, pcnt_channel_edge_action_t neg_act)
{
	if (channel == 0) {
		hw->conf_unit[unit].conf0.ch0_pos_mode_un = pos_act;
		hw->conf_unit[unit].conf0.ch0_neg_mode_un = neg_act;
	} else {
		hw->conf_unit[unit].conf0.ch1_pos_mode_un = pos_act;
		hw->conf_unit[unit].conf0.ch1_neg_mode_un = neg_act;
	}
}

void pcnt_ll_set_level_action(pcnt_dev_t *hw, uint32_t unit, uint32_t channel, pcnt_channel_level_action_t high_act, pcnt_channel_level_action_t low_act)
{
	if (channel == 0) {
		hw->conf_unit[unit].conf0.ch0_hctrl_mode_un = high_act;
		hw->conf_unit[unit].conf0.ch0_lctrl_mode_un = low_act;
	} else {
		hw->conf_unit[unit].conf0.ch1_hctrl_mode_un = high_act;
		hw->conf_unit[unit].conf0.ch1_lctrl_mode_un = low_act;
	}
}

int pcnt_ll_get_count(pcnt_dev_t *hw, uint32_t unit)
{
	pcnt_un_cnt_reg_t cnt_reg = hw->cnt_unit[unit];
	int16_t value = cnt_reg.pulse_cnt_un;
	return value;
}

void pcnt_ll_stop_count(pcnt_dev_t *hw, uint32_t unit)
{
	hw->ctrl.val |= 1 << (2 * unit + 1);
}

void pcnt_ll_start_count(pcnt_dev_t *hw, uint32_t unit)
{
	hw->ctrl.val &= ~(1 << (2 * unit + 1));
}

void pcnt_ll_clear_count(pcnt_dev_t *hw, uint32_t unit)
{
	hw->ctrl.val |= 1 << (2 * unit);
	hw->ctrl.val &= ~(1 << (2 * unit));
}

void pcnt_ll_enable_intr(pcnt_dev_t *hw, uint32_t unit_mask, bool enable)
{
	if (enable) {
		hw->int_ena.val |= unit_mask;
	} else {
		hw->int_ena.val &= ~unit_mask;
	}
}

uint32_t pcnt_ll_get_intr_status(pcnt_dev_t *hw)
{
	return hw->int_st.val;
}

void pcnt_ll_clear_intr_status(pcnt_dev_t *hw, uint32_t status)
{
	hw->int_clr.val = status;
}

void pcnt_ll_enable_high_limit_event(pcnt_dev_t *hw, uint32_t unit, bool enable)
{
	hw->conf_unit[unit].conf0.thr_h_lim_en_un = enable;
}

void pcnt_ll_enable_low_limit_event(pcnt_dev_t *hw, uint32_t unit, bool enable)
{
	hw->conf_unit[unit].conf0.thr_l_lim_en_un = enable;
}

void pcnt_ll_enable_zero_cross_event(pcnt_dev_t *hw, uint32_t unit, bool enable)
{
	hw->conf_unit[unit].conf0.thr_zero_en_un = enable;
}

void pcnt_ll_enable_thres_event(pcnt_dev_t *hw, uint32_t unit, uint32_t thres, bool enable)
{
	if (thres == 0) {
		hw->conf_unit[unit].conf0.thr_thres0_en_un = enable;
	} else {
		hw->conf_unit[unit].conf0.thr_thres1_en_un = enable;
	}
}

void pcnt_ll_disable_all_events(pcnt_dev_t *hw, uint32_t unit)
{
	hw->conf_unit[unit].conf0.val &= ~(PCNT_LL_EVENT_MASK << 11);
}

void pcnt_ll_set_high_limit_value(pcnt_dev_t *hw, uint32_t unit, int value)
{
	pcnt_un_conf2_reg_t conf2_reg = hw->conf_unit[unit].conf2;
	conf2_reg.cnt_h_lim_un = value;
	hw->conf_unit[unit].conf2 = conf2_reg;
}

void pcnt_ll_set_low_limit_value(pcnt_dev_t *hw, uint32_t unit, int value)
{
	pcnt_un_conf2_reg_t conf2_reg = hw->conf_unit[unit].conf2;
	conf2_reg.cnt_l_lim_un = value;
	hw->conf_unit[unit].conf2 = conf2_reg;
}

void pcnt_ll_set_thres_value(pcnt_dev_t *hw, uint32_t unit, uint32_t thres, int value)
{
	pcnt_un_conf1_reg_t conf1_reg = hw->conf_unit[unit].conf1;
	if (thres == 0) {
		conf1_reg.cnt_thres0_un = value;
	} else {
		conf1_reg.cnt_thres1_un = value;
	}
	hw->conf_unit[unit].conf1 = conf1_reg;
}

int pcnt_ll_get_high_limit_value(pcnt_dev_t *hw, uint32_t unit)
{
	pcnt_un_conf2_reg_t conf2_reg = hw->conf_unit[unit].conf2;
	int16_t value = conf2_reg.cnt_h_lim_un;
	return value;
}

int pcnt_ll_get_low_limit_value(pcnt_dev_t *hw, uint32_t unit)
{
	pcnt_un_conf2_reg_t conf2_reg = hw->conf_unit[unit].conf2;
	int16_t value = conf2_reg.cnt_l_lim_un;
	return value;
}

int pcnt_ll_get_thres_value(pcnt_dev_t *hw, uint32_t unit, uint32_t thres)
{
	int16_t value;
	pcnt_un_conf1_reg_t conf1_reg = hw->conf_unit[unit].conf1;
	if (thres == 0) {
		value = conf1_reg.cnt_thres0_un;
	} else {
		value = conf1_reg.cnt_thres1_un;
	}
	return value;
}

uint32_t pcnt_ll_get_unit_status(pcnt_dev_t *hw, uint32_t unit)
{
	return hw->status_unit[unit].val;
}

pcnt_unit_count_sign_t pcnt_ll_get_count_sign(pcnt_dev_t *hw, uint32_t unit)
{
	return hw->status_unit[unit].val & 0x03;
}

uint32_t pcnt_ll_get_event_status(pcnt_dev_t *hw, uint32_t unit)
{
	return hw->status_unit[unit].val >> 2;
}

void pcnt_ll_set_glitch_filter_thres(pcnt_dev_t *hw, uint32_t unit, uint32_t filter_val)
{
	hw->conf_unit[unit].conf0.filter_thres_un = filter_val;
}

uint32_t pcnt_ll_get_glitch_filter_thres(pcnt_dev_t *hw, uint32_t unit)
{
	return hw->conf_unit[unit].conf0.filter_thres_un;
}

void pcnt_ll_enable_glitch_filter(pcnt_dev_t *hw, uint32_t unit, bool enable)
{
	hw->conf_unit[unit].conf0.filter_en_un = enable;
}

