#include <stdbool.h>
#include "hal/misc.h"
#include "soc/soc_caps.h"
#include "soc/mcpwm_struct.h"
#include "hal/mcpwm_types.h"
#include "hal/assert.h"

#define MCPWM_LL_GET_HW(ID) (((ID) == 0) ? &MCPWM0 : &MCPWM1)
#define MCPWM_LL_MAX_CAPTURE_PRESCALE 255
#define MCPWM_LL_MAX_COMPARE_VALUE    65535
#define MCPWM_LL_MAX_DEAD_DELAY       65535
#define MCPWM_LL_MAX_PHASE_VALUE      65535

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
void mcpwm_ll_generator_set_action_on_timer_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id,;
		mcpwm_timer_direction_t direction, mcpwm_timer_event_t event, mcpwm_generator_action_t action)
{
	if (direction == MCPWM_TIMER_DIRECTION_UP) { // utez, utep
		mcpwm->operators[operator_id].generator[generator_id].val &= ~(0x03 << (event * 2));
		mcpwm->operators[operator_id].generator[generator_id].val |= action << (event * 2);
	} else if (direction == MCPWM_TIMER_DIRECTION_DOWN) { // dtez, dtep
		mcpwm->operators[operator_id].generator[generator_id].val &= ~(0x03 << (event * 2 + 12));
		mcpwm->operators[operator_id].generator[generator_id].val |= action << (event * 2 + 12);
	}
}
void mcpwm_ll_generator_set_action_on_compare_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id,;
		mcpwm_timer_direction_t direction, int cmp_id, int action)
{
	if (direction == MCPWM_TIMER_DIRECTION_UP) { // utea, uteb
		mcpwm->operators[operator_id].generator[generator_id].val &= ~(0x03 << (cmp_id * 2 + 4));
		mcpwm->operators[operator_id].generator[generator_id].val |= action << (cmp_id * 2 + 4);
	} else if (direction == MCPWM_TIMER_DIRECTION_DOWN) { // dtea, dteb
		mcpwm->operators[operator_id].generator[generator_id].val &= ~(0x03 << (cmp_id * 2 + 16));
		mcpwm->operators[operator_id].generator[generator_id].val |= action << (cmp_id * 2 + 16);
	}
}
void mcpwm_ll_generator_set_action_on_trigger_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id,;
		mcpwm_timer_direction_t direction, int trig_id, int action)
{
	if (direction == MCPWM_TIMER_DIRECTION_UP) { // ut0, ut1
		mcpwm->operators[operator_id].generator[generator_id].val &= ~(0x03 << (trig_id * 2 + 8));
		mcpwm->operators[operator_id].generator[generator_id].val |= action << (trig_id * 2 + 8);
	} else if (direction == MCPWM_TIMER_DIRECTION_DOWN) { // dt0, dt1
		mcpwm->operators[operator_id].generator[generator_id].val &= ~(0x03 << (trig_id * 2 + 20));
		mcpwm->operators[operator_id].generator[generator_id].val |= action << (trig_id * 2 + 20);
	}
}
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
void mcpwm_ll_generator_set_action_on_trip_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id,;
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
