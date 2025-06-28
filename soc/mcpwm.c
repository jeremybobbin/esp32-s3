

// The LL layer for ESP32-S3 MCPWM register operations


#include <stdbool.h>
#include <stdint.h>
#include "soc/mcpwm.h"


/// Get the address of peripheral registers
#define MCPWM_LL_GET_HW(ID) (((ID) == 0) ? &MCPWM0 : &MCPWM1)
#define MCPWM_LL_MAX_CAPTURE_PRESCALE 255
#define MCPWM_LL_MAX_COMPARE_VALUE    65535
#define MCPWM_LL_MAX_DEAD_DELAY       65535
#define MCPWM_LL_MAX_PHASE_VALUE      65535


uint32_t mcpwm_ll_intr_get_status(mcpwm_dev_t *mcpwm)
{
	return mcpwm->int_st.val;
}

void mcpwm_ll_intr_clear_status(mcpwm_dev_t *mcpwm, uint32_t intr_mask)
{
	mcpwm->int_clr.val = intr_mask;
}

void mcpwm_ll_intr_disable_all(mcpwm_dev_t *mcpwm)
{
	mcpwm->int_ena.val = 0;
}

//////////// get interrupt status for each event ////////////////

uint32_t mcpwm_ll_intr_get_timer_stop_status(mcpwm_dev_t *mcpwm)
{
	return (mcpwm->int_st.val >> 0) & 0x07;
}

uint32_t mcpwm_ll_intr_get_timer_tez_status(mcpwm_dev_t *mcpwm)
{
	return (mcpwm->int_st.val >> 3) & 0x07;
}

uint32_t mcpwm_ll_intr_get_timer_tep_status(mcpwm_dev_t *mcpwm)
{
	return (mcpwm->int_st.val >> 6) & 0x07;
}

uint32_t mcpwm_ll_intr_get_fault_enter_status(mcpwm_dev_t *mcpwm)
{
	return (mcpwm->int_st.val >> 9) & 0x07;
}

uint32_t mcpwm_ll_intr_get_fault_exit_status(mcpwm_dev_t *mcpwm)
{
	return (mcpwm->int_st.val >> 12) & 0x07;
}

uint32_t mcpwm_ll_intr_get_compare_status(mcpwm_dev_t *mcpwm, uint32_t cmp_id)
{
	return (mcpwm->int_st.val >> (15 + cmp_id * 3)) & 0x07;
}

uint32_t mcpwm_ll_intr_get_trip_cbc_status(mcpwm_dev_t *mcpwm)
{
	return (mcpwm->int_st.val >> 21) & 0x07;
}

uint32_t mcpwm_ll_intr_get_trip_ost_status(mcpwm_dev_t *mcpwm)
{
	return (mcpwm->int_st.val >> 24) & 0x07;
}

uint32_t mcpwm_ll_intr_get_capture_status(mcpwm_dev_t *mcpwm)
{
	return (mcpwm->int_st.val >> 27) & 0x07;
}

//////////// clear interrupt status for each event ////////////////

void mcpwm_ll_intr_clear_timer_stop_status(mcpwm_dev_t *mcpwm, uint32_t timer_mask)
{
	mcpwm->int_clr.val = (timer_mask & 0x07) << 0;
}

void mcpwm_ll_intr_clear_timer_tez_status(mcpwm_dev_t *mcpwm, uint32_t timer_mask)
{
	mcpwm->int_clr.val = (timer_mask & 0x07) << 3;
}

void mcpwm_ll_intr_clear_timer_tep_status(mcpwm_dev_t *mcpwm, uint32_t timer_mask)
{
	mcpwm->int_clr.val = (timer_mask & 0x07) << 6;
}

void mcpwm_ll_intr_clear_fault_enter_status(mcpwm_dev_t *mcpwm, uint32_t fault_mask)
{
	mcpwm->int_clr.val = (fault_mask & 0x07) << 9;
}

void mcpwm_ll_intr_clear_fault_exit_status(mcpwm_dev_t *mcpwm, uint32_t fault_mask)
{
	mcpwm->int_clr.val = (fault_mask & 0x07) << 12;
}

void mcpwm_ll_intr_clear_compare_status(mcpwm_dev_t *mcpwm, uint32_t operator_mask, uint32_t cmp_id)
{
	mcpwm->int_clr.val = (operator_mask & 0x07) << (15 + cmp_id * 3);
}

void mcpwm_ll_intr_clear_trip_cbc_status(mcpwm_dev_t *mcpwm, uint32_t cbc_mask)
{
	mcpwm->int_clr.val = (cbc_mask & 0x07) << 21;
}

void mcpwm_ll_intr_clear_trip_ost_status(mcpwm_dev_t *mcpwm, uint32_t ost_mask)
{
	mcpwm->int_clr.val = (ost_mask & 0x07) << 24;
}

void mcpwm_ll_intr_clear_capture_status(mcpwm_dev_t *mcpwm, uint32_t capture_mask)
{
	mcpwm->int_clr.val = (capture_mask & 0x07) << 27;
}

//////////// enable interrupt for each event ////////////////

void mcpwm_ll_intr_enable_timer_stop(mcpwm_dev_t *mcpwm, uint32_t timer_id, bool enable)
{
	if (enable) {
		mcpwm->int_ena.val |= 1 << (timer_id + 0);
	} else {
		mcpwm->int_ena.val &= ~(1 << (timer_id + 0));
	}
}

void mcpwm_ll_intr_enable_timer_tez(mcpwm_dev_t *mcpwm, uint32_t timer_id, bool enable)
{
	if (enable) {
		mcpwm->int_ena.val |= 1 << (timer_id + 3);
	} else {
		mcpwm->int_ena.val &= ~(1 << (timer_id + 3));
	}
}

void mcpwm_ll_intr_enable_timer_tep(mcpwm_dev_t *mcpwm, uint32_t timer_id, bool enable)
{
	if (enable) {
		mcpwm->int_ena.val |= 1 << (timer_id + 6);
	} else {
		mcpwm->int_ena.val &= ~(1 << (timer_id + 6));
	}
}

void mcpwm_ll_intr_enable_fault_enter(mcpwm_dev_t *mcpwm, uint32_t fault_id, bool enable)
{
	if (enable) {
		mcpwm->int_ena.val |= 1 << (9 + fault_id);  // enter fault interrupt
	} else {
		mcpwm->int_ena.val &= ~(1 << (9 + fault_id));
	}
}

void mcpwm_ll_intr_enable_fault_exit(mcpwm_dev_t *mcpwm, uint32_t fault_id, bool enable)
{
	if (enable) {
		mcpwm->int_ena.val |= 1 << (12 + fault_id); // exit fault interrupt
	} else {
		mcpwm->int_ena.val &= ~(1 << (12 + fault_id));
	}
}

void mcpwm_ll_intr_enable_compare(mcpwm_dev_t *mcpwm, uint32_t operator_id, uint32_t cmp_id, bool enable)
{
	if (enable) {
		mcpwm->int_ena.val |= (1 << (15 + cmp_id * 3 + operator_id));
	} else {
		mcpwm->int_ena.val &= ~(1 << (15 + cmp_id * 3 + operator_id));
	}
}

void mcpwm_ll_intr_enable_trip_cbc(mcpwm_dev_t *mcpwm, uint32_t operator_id, bool enable)
{
	if (enable) {
		mcpwm->int_ena.val |= (1 << (21 + operator_id));
	} else {
		mcpwm->int_ena.val &= ~(1 << (21 + operator_id));
	}
}

void mcpwm_ll_intr_enable_trip_ost(mcpwm_dev_t *mcpwm, uint32_t operator_id, bool enable)
{
	if (enable) {
		mcpwm->int_ena.val |= (1 << (24 + operator_id));
	} else {
		mcpwm->int_ena.val &= ~(1 << (24 + operator_id));
	}
}

void mcpwm_ll_intr_enable_capture(mcpwm_dev_t *mcpwm, uint32_t capture_id, bool enable)
{
	if (enable) {
		mcpwm->int_ena.val |= 1 << (27 + capture_id);
	} else {
		mcpwm->int_ena.val &= ~(1 << (27 + capture_id));
	}
}


void mcpwm_ll_operator_flush_shadow(mcpwm_dev_t *mcpwm, int operator_id)
{
	mcpwm->update_cfg.val ^= (1 << (2 * operator_id + 3));
}

void mcpwm_ll_operator_select_timer(mcpwm_dev_t *mcpwm, int operator_id, int timer_id)
{
	if (operator_id == 0) {
		mcpwm->operator_timersel.operator0_timersel = timer_id;
	} else if (operator_id == 1) {
		mcpwm->operator_timersel.operator1_timersel = timer_id;
	} else {
		mcpwm->operator_timersel.operator2_timersel = timer_id;
	}
}

void mcpwm_ll_operator_update_compare_at_once(mcpwm_dev_t *mcpwm, int operator_id, int compare_id)
{
	mcpwm->operators[operator_id].gen_stmp_cfg.val &= ~(0x0F << (4 * compare_id));
}

void mcpwm_ll_operator_enable_update_compare_on_tez(mcpwm_dev_t *mcpwm, int operator_id, int compare_id, bool enable)
{
	if (enable) {
		mcpwm->operators[operator_id].gen_stmp_cfg.val |= (1 << 0) << (4 * compare_id);
	} else {
		mcpwm->operators[operator_id].gen_stmp_cfg.val &= ~((1 << 0) << (4 * compare_id));
	}
}

void mcpwm_ll_operator_enable_update_compare_on_tep(mcpwm_dev_t *mcpwm, int operator_id, int compare_id, bool enable)
{
	if (enable) {
		mcpwm->operators[operator_id].gen_stmp_cfg.val |= (1 << 1) << (4 * compare_id);
	} else {
		mcpwm->operators[operator_id].gen_stmp_cfg.val &= ~((1 << 1) << (4 * compare_id));
	}
}

void mcpwm_ll_operator_enable_update_compare_on_sync(mcpwm_dev_t *mcpwm, int operator_id, int compare_id, bool enable)
{
	if (enable) {
		mcpwm->operators[operator_id].gen_stmp_cfg.val |= (1 << 2) << (4 * compare_id);
	} else {
		mcpwm->operators[operator_id].gen_stmp_cfg.val &= ~((1 << 2) << (4 * compare_id));
	}
}

void mcpwm_ll_operator_set_compare_value(mcpwm_dev_t *mcpwm, int operator_id, int compare_id, uint32_t compare_value)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(mcpwm->operators[operator_id].timestamp[compare_id], gen, compare_value);
}

uint32_t mcpwm_ll_operator_get_compare_value(mcpwm_dev_t *mcpwm, int operator_id, int compare_id)
{
	return HAL_FORCE_READ_U32_REG_FIELD(mcpwm->operators[operator_id].timestamp[compare_id], gen);
}

void mcpwm_ll_operator_update_action_at_once(mcpwm_dev_t *mcpwm, int operator_id)
{
	mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod = 0;
}

void mcpwm_ll_operator_enable_update_action_on_tez(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
	if (enable) {
		mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod |= 1 << 0;
	} else {
		mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod &= ~(1 << 0);
	}
}

void mcpwm_ll_operator_enable_update_action_on_tep(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
	if (enable) {
		mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod |= 1 << 1;
	} else {
		mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod &= ~(1 << 1);
	}
}

void mcpwm_ll_operator_enable_update_action_on_sync(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
	if (enable) {
		mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod |= 1 << 2;
	} else {
		mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod &= ~(1 << 2);
	}
}

void mcpwm_ll_operator_set_trigger_gpio_fault(mcpwm_dev_t *mcpwm, int operator_id, int trig_id, int fault_id)
{
	mcpwm->operators[operator_id].gen_cfg0.val &= ~(0x07 << (4 + 3 * trig_id));
	mcpwm->operators[operator_id].gen_cfg0.val |= (fault_id << (4 + 3 * trig_id));
}

void mcpwm_ll_operator_set_trigger_timer_sync(mcpwm_dev_t *mcpwm, int operator_id, int trig_id)
{
	// the timer here is not selectable, must be the one connected with the operator
	mcpwm->operators[operator_id].gen_cfg0.val &= ~(0x07 << (4 + 3 * trig_id));
	mcpwm->operators[operator_id].gen_cfg0.val |= (3 << (4 + 3 * trig_id));
}


void mcpwm_ll_deadtime_resolution_to_timer(mcpwm_dev_t *mcpwm, int operator_id, bool same)
{
	// whether to make the resolution of dead time delay module the same to the timer connected with operator
	mcpwm->operators[operator_id].dt_cfg.dt_clk_sel = same;
}

void mcpwm_ll_deadtime_red_select_generator(mcpwm_dev_t *mcpwm, int operator_id, int generator)
{
	mcpwm->operators[operator_id].dt_cfg.dt_red_insel = generator;
}

void mcpwm_ll_deadtime_fed_select_generator(mcpwm_dev_t *mcpwm, int operator_id, int generator)
{
	mcpwm->operators[operator_id].dt_cfg.dt_fed_insel = generator;
}

void mcpwm_ll_deadtime_bypass_path(mcpwm_dev_t *mcpwm, int operator_id, int path, bool bypass)
{
	if (bypass) {
		mcpwm->operators[operator_id].dt_cfg.val |= 1 << (path + 15);
	} else {
		mcpwm->operators[operator_id].dt_cfg.val &= ~(1 << (path + 15));
	}
}

void mcpwm_ll_deadtime_invert_outpath(mcpwm_dev_t *mcpwm, int operator_id, int path, bool invert)
{
	if (invert) {
		mcpwm->operators[operator_id].dt_cfg.val |= 1 << (path + 13);
	} else {
		mcpwm->operators[operator_id].dt_cfg.val &= ~(1 << (path + 13));
	}
}

void mcpwm_ll_deadtime_swap_out_path(mcpwm_dev_t *mcpwm, int operator_id, int path, bool swap)
{
	if (swap) {
		mcpwm->operators[operator_id].dt_cfg.val |= 1 << (path + 9);
	} else {
		mcpwm->operators[operator_id].dt_cfg.val &= ~(1 << (path + 9));
	}
}

void mcpwm_ll_deadtime_enable_deb(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
	mcpwm->operators[operator_id].dt_cfg.dt_deb_mode = enable;
}

uint32_t mcpwm_ll_deadtime_get_switch_topology(mcpwm_dev_t *mcpwm, int operator_id)
{
	return (mcpwm->operators[operator_id].dt_cfg.dt_deb_mode << 8) | (mcpwm->operators[operator_id].dt_cfg.dt_b_outswap << 7) |
		   (mcpwm->operators[operator_id].dt_cfg.dt_a_outswap << 6) | (mcpwm->operators[operator_id].dt_cfg.dt_fed_insel << 5) |
		   (mcpwm->operators[operator_id].dt_cfg.dt_red_insel << 4) | (mcpwm->operators[operator_id].dt_cfg.dt_fed_outinvert << 3) |
		   (mcpwm->operators[operator_id].dt_cfg.dt_red_outinvert << 2) | (mcpwm->operators[operator_id].dt_cfg.dt_a_outbypass << 1) |
		   (mcpwm->operators[operator_id].dt_cfg.dt_b_outbypass << 0);
}

void mcpwm_ll_deadtime_set_falling_delay(mcpwm_dev_t *mcpwm, int operator_id, uint32_t fed)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(mcpwm->operators[operator_id].dt_fed_cfg, dt_fed, fed - 1);
}

uint32_t mcpwm_ll_deadtime_get_falling_delay(mcpwm_dev_t *mcpwm, int operator_id)
{
	return HAL_FORCE_READ_U32_REG_FIELD(mcpwm->operators[operator_id].dt_fed_cfg, dt_fed) + 1;
}

void mcpwm_ll_deadtime_set_rising_delay(mcpwm_dev_t *mcpwm, int operator_id, uint32_t red)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(mcpwm->operators[operator_id].dt_red_cfg, dt_red, red - 1);
}

uint32_t mcpwm_ll_deadtime_get_rising_delay(mcpwm_dev_t *mcpwm, int operator_id)
{
	return HAL_FORCE_READ_U32_REG_FIELD(mcpwm->operators[operator_id].dt_red_cfg, dt_red) + 1;
}

void mcpwm_ll_deadtime_update_delay_at_once(mcpwm_dev_t *mcpwm, int operator_id)
{
	mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod = 0;
	mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod = 0;
}

void mcpwm_ll_deadtime_enable_update_delay_on_tez(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
	if (enable) {
		mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod |= 1 << 0;
		mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod |= 1 << 0;
	} else {
		mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod &= ~(1 << 0);
		mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod &= ~(1 << 0);
	}
}

void mcpwm_ll_deadtime_enable_update_delay_on_tep(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
	if (enable) {
		mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod |= 1 << 1;
		mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod |= 1 << 1;
	} else {
		mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod &= ~(1 << 1);
		mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod &= ~(1 << 1);
	}
}

void mcpwm_ll_deadtime_enable_update_delay_on_sync(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
	if (enable) {
		mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod |= 1 << 2;
		mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod |= 1 << 2;
	} else {
		mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod &= ~(1 << 2);
		mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod &= ~(1 << 2);
	}
}


void mcpwm_ll_fault_enable_detection(mcpwm_dev_t *mcpwm, int fault_sig, bool enable)
{
	if (enable) {
		mcpwm->fault_detect.val |= 1 << fault_sig;
	} else {
		mcpwm->fault_detect.val &= ~(1 << fault_sig);
	}
}

void mcpwm_ll_fault_set_active_level(mcpwm_dev_t *mcpwm, int fault_sig, bool level)
{
	if (level) {
		mcpwm->fault_detect.val |= 1 << (fault_sig + 3);
	} else {
		mcpwm->fault_detect.val &= ~(1 << (fault_sig + 3));
	}
}

void mcpwm_ll_fault_clear_ost(mcpwm_dev_t *mcpwm, int operator_id)
{
	// a posedge can clear the ost fault status
	mcpwm->operators[operator_id].fh_cfg1.fh_clr_ost = 0;
	mcpwm->operators[operator_id].fh_cfg1.fh_clr_ost = 1;
}

void mcpwm_ll_fault_enable_oneshot_mode(mcpwm_dev_t *mcpwm, int operator_id, int fault_sig, bool enable)
{
	mcpwm->operators[operator_id].fh_cfg0.val &= ~(1 << (7 - fault_sig));
	mcpwm->operators[operator_id].fh_cfg0.val |= (enable << (7 - fault_sig));
}

void mcpwm_ll_fault_enable_cbc_mode(mcpwm_dev_t *mcpwm, int operator_id, int fault_sig, bool enable)
{
	mcpwm->operators[operator_id].fh_cfg0.val &= ~(1 << (3 - fault_sig));
	mcpwm->operators[operator_id].fh_cfg0.val |= (enable << (3 - fault_sig));
}

void mcpwm_ll_fault_enable_cbc_refresh_on_tez(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
	if (enable) {
		mcpwm->operators[operator_id].fh_cfg1.val |= 1 << 1;
	} else {
		mcpwm->operators[operator_id].fh_cfg1.val &= ~(1 << 1);
	}
}

void mcpwm_ll_fault_enable_cbc_refresh_on_tep(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
	if (enable) {
		mcpwm->operators[operator_id].fh_cfg1.val |= 1 << 2;
	} else {
		mcpwm->operators[operator_id].fh_cfg1.val &= ~(1 << 2);
	}
}

void mcpwm_ll_fault_enable_sw_cbc(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
	mcpwm->operators[operator_id].fh_cfg0.fh_sw_cbc = enable;
}

void mcpwm_ll_fault_enable_sw_oneshot(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
	mcpwm->operators[operator_id].fh_cfg0.fh_sw_ost = enable;
}

void mcpwm_ll_fault_trigger_sw_cbc(mcpwm_dev_t *mcpwm, int operator_id)
{
	mcpwm->operators[operator_id].fh_cfg1.fh_force_cbc = ~mcpwm->operators[operator_id].fh_cfg1.fh_force_cbc;
}

void mcpwm_ll_fault_trigger_sw_ost(mcpwm_dev_t *mcpwm, int operator_id)
{
	mcpwm->operators[operator_id].fh_cfg1.fh_force_ost = ~mcpwm->operators[operator_id].fh_cfg1.fh_force_ost;
}

void mcpwm_ll_generator_set_action_on_trip_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id,
		mcpwm_timer_direction_t direction, mcpwm_trip_type_t trip, int action)
{
	if (direction == MCPWM_TIMER_DIRECTION_UP) {
		mcpwm->operators[operator_id].fh_cfg0.val &= ~(0x03 << (8 + 8 * generator_id + 4 * trip + 2));
		mcpwm->operators[operator_id].fh_cfg0.val |= action << (8 + 8 * generator_id + 4 * trip + 2);
	} else if (direction == MCPWM_TIMER_DIRECTION_DOWN) {
		mcpwm->operators[operator_id].fh_cfg0.val &= ~(0x03 << (8 + 8 * generator_id + 4 * trip));
		mcpwm->operators[operator_id].fh_cfg0.val |= action << (8 + 8 * generator_id + 4 * trip);
	}
}

bool mcpwm_ll_fault_is_ost_on(mcpwm_dev_t *mcpwm, int op)
{
	return mcpwm->operators[op].fh_status.fh_ost_on;
}

bool mcpwm_ll_fault_is_cbc_on(mcpwm_dev_t *mcpwm, int op)
{
	return mcpwm->operators[op].fh_status.fh_cbc_on;
}

void mcpwm_ll_timer_set_execute_command(mcpwm_dev_t *mcpwm, int timer_id, mcpwm_timer_execute_cmd_t cmd) {
	switch (cmd) {
	case MCPWM_TIMER_STOP_AT_ZERO:
		mcpwm->timer[timer_id].timer_cfg1.timer_start = 0;
		break;
	case MCPWM_TIMER_STOP_AT_PEAK:
		mcpwm->timer[timer_id].timer_cfg1.timer_start = 1;
		break;
	case MCPWM_TIMER_START_NO_STOP:
		mcpwm->timer[timer_id].timer_cfg1.timer_start = 2;
		break;
	case MCPWM_TIMER_START_STOP_AT_ZERO:
		mcpwm->timer[timer_id].timer_cfg1.timer_start = 3;
		break;
	case MCPWM_TIMER_START_STOP_AT_PEAK:
		mcpwm->timer[timer_id].timer_cfg1.timer_start = 4;
		break;
	}
}


