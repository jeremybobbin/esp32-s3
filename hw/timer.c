
// The LL layer for Timer Group register operations.
// Note that most of the register operations in this layer are non-atomic operations.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "hal/misc.h"
#include "soc/timer_periph.h"
#include "soc/timer_group_struct.h"
#include "hal/timer_types.h"
#include "hal/assert.h"

_Static_assert(TIMER_INTR_T0 == TIMG_T0_INT_CLR, "Add mapping to LL interrupt handling, since it's no longer naturally compatible with the timer_intr_t");
_Static_assert(TIMER_INTR_T1 == TIMG_T1_INT_CLR, "Add mapping to LL interrupt handling, since it's no longer naturally compatible with the timer_intr_t");
_Static_assert(TIMER_INTR_WDT == TIMG_WDT_INT_CLR, "Add mapping to LL interrupt handling, since it's no longer naturally compatible with the timer_intr_t");

typedef struct {
	timg_dev_t *dev;
	timer_idx_t idx;
} timer_ll_context_t;

// Get timer group instance with giving group number
#define TIMER_LL_GET_HW(num) ((num == 0) ? (&TIMERG0) : (&TIMERG1))

static inline void timer_ll_set_divider(timg_dev_t *hw, timer_idx_t timer_num, uint32_t divider)
{
	HAL_ASSERT(divider >= 2 && divider <= 65536);
	if (divider >= 65536) {
		divider = 0;
	}
	int timer_en = hw->hw_timer[timer_num].config.tn_en;
	hw->hw_timer[timer_num].config.tn_en = 0;
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->hw_timer[timer_num].config, tn_divider, divider);
	hw->hw_timer[timer_num].config.tn_en = timer_en;
}

static inline void timer_ll_get_divider(timg_dev_t *hw, timer_idx_t timer_num, uint32_t *divider)
{
	uint32_t d = HAL_FORCE_READ_U32_REG_FIELD(hw->hw_timer[timer_num].config, tn_divider);
	if (d == 0) {
		d = 65536;
	} else if (d == 1) {
		d = 2;
	}
	*divider = d;
}

static inline void timer_ll_set_counter_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t load_val)
{
	hw->hw_timer[timer_num].loadhi.tn_load_hi = (uint32_t) (load_val >> 32);
	hw->hw_timer[timer_num].loadlo.tn_load_lo = (uint32_t) load_val;
	hw->hw_timer[timer_num].load.tn_load = 1;
}

FORCE_INLINE_ATTR void timer_ll_get_counter_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t *timer_val)
{
	hw->hw_timer[timer_num].update.tn_update = 1;
	while (hw->hw_timer[timer_num].update.tn_update) {}
	*timer_val = ((uint64_t) hw->hw_timer[timer_num].hi.tn_hi << 32) | (hw->hw_timer[timer_num].lo.tn_lo);
}

static inline void timer_ll_set_counter_increase(timg_dev_t *hw, timer_idx_t timer_num, bool increase_en)
{
	hw->hw_timer[timer_num].config.tn_increase = increase_en;
}

static inline bool timer_ll_get_counter_increase(timg_dev_t *hw, timer_idx_t timer_num)
{
	return hw->hw_timer[timer_num].config.tn_increase;
}

FORCE_INLINE_ATTR void timer_ll_set_counter_enable(timg_dev_t *hw, timer_idx_t timer_num, bool counter_en)
{
	hw->hw_timer[timer_num].config.tn_en = counter_en;
}

static inline bool timer_ll_get_counter_enable(timg_dev_t *hw, timer_idx_t timer_num)
{
	return hw->hw_timer[timer_num].config.tn_en;
}

static inline void timer_ll_set_auto_reload(timg_dev_t *hw, timer_idx_t timer_num, bool auto_reload_en)
{
	hw->hw_timer[timer_num].config.tn_autoreload = auto_reload_en;
}

FORCE_INLINE_ATTR bool timer_ll_get_auto_reload(timg_dev_t *hw, timer_idx_t timer_num)
{
	return hw->hw_timer[timer_num].config.tn_autoreload;
}

FORCE_INLINE_ATTR void timer_ll_set_alarm_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t alarm_value)
{
	hw->hw_timer[timer_num].alarmhi.tn_alarm_hi = (uint32_t) (alarm_value >> 32);
	hw->hw_timer[timer_num].alarmlo.tn_alarm_lo = (uint32_t) alarm_value;
}

static inline void timer_ll_get_alarm_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t *alarm_value)
{
	*alarm_value = ((uint64_t) hw->hw_timer[timer_num].alarmhi.tn_alarm_hi  << 32) | (hw->hw_timer[timer_num].alarmlo.tn_alarm_lo);
}

FORCE_INLINE_ATTR void timer_ll_set_alarm_enable(timg_dev_t *hw, timer_idx_t timer_num, bool alarm_en)
{
	hw->hw_timer[timer_num].config.tn_alarm_en = alarm_en;
}

static inline bool timer_ll_get_alarm_enable(timg_dev_t *hw, timer_idx_t timer_num)
{
	return hw->hw_timer[timer_num].config.tn_alarm_en;
}

FORCE_INLINE_ATTR void timer_ll_intr_enable(timg_dev_t *hw, timer_idx_t timer_num)
{
	hw->int_ena_timers.val |= BIT(timer_num);
}

FORCE_INLINE_ATTR void timer_ll_intr_disable(timg_dev_t *hw, timer_idx_t timer_num)
{
	hw->int_ena_timers.val &= (~BIT(timer_num));
}

FORCE_INLINE_ATTR void timer_ll_clear_intr_status(timg_dev_t *hw, timer_idx_t timer_num)
{
	hw->int_clr_timers.val |= BIT(timer_num);
}

FORCE_INLINE_ATTR void timer_ll_get_intr_status(timg_dev_t *hw, uint32_t *intr_status)
{
	*intr_status = hw->int_st_timers.val & 0x03;
}

FORCE_INLINE_ATTR void timer_ll_get_intr_raw_status(timer_group_t group_num, uint32_t *intr_raw_status)
{
	timg_dev_t *hw = TIMER_LL_GET_HW(group_num);
	*intr_raw_status = hw->int_raw_timers.val & 0x03;
}

static inline void timer_ll_set_level_int_enable(timg_dev_t *hw, timer_idx_t timer_num, bool level_int_en)
{
	// Only "level" interrupts are supported on this target
}

static inline bool timer_ll_get_level_int_enable(timg_dev_t *hw, timer_idx_t timer_num)
{
	return true;
}

static inline void timer_ll_set_edge_int_enable(timg_dev_t *hw, timer_idx_t timer_num, bool edge_int_en)
{
}

static inline bool timer_ll_get_edge_int_enable(timg_dev_t *hw, timer_idx_t timer_num)
{
	return false;
}

static inline uint32_t timer_ll_get_intr_status_reg(timg_dev_t *hw)
{
	return (uint32_t) & (hw->int_st_timers.val);
}

static inline uint32_t timer_ll_get_intr_mask_bit(timg_dev_t *hw, timer_idx_t timer_num)
{
	return (1U << timer_num);
}

static inline void timer_ll_set_use_xtal(timg_dev_t *hw, timer_idx_t timer_num, bool use_xtal_en)
{
	hw->hw_timer[timer_num].config.tn_use_xtal = use_xtal_en;
}

static inline bool timer_ll_get_use_xtal(timg_dev_t *hw, timer_idx_t timer_num)
{
	return hw->hw_timer[timer_num].config.tn_use_xtal;
}

#ifdef __cplusplus
}
#endif
