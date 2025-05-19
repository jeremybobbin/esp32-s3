
// The LL layer for Timer Group register operations.
// Note that most of the register operations in this layer are non-atomic operations.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>
#include "hal/wdt_types.h"
#include "soc/rtc_cntl_periph.h"
#include "soc/rtc_cntl_struct.h"
#include "soc/efuse_reg.h"
#include "esp_attr.h"
#include "esp_assert.h"

#define RWDT_LL_STG_SEL_OFF             0
#define RWDT_LL_STG_SEL_INT             1
#define RWDT_LL_STG_SEL_RESET_CPU       2
#define RWDT_LL_STG_SEL_RESET_SYSTEM    3
#define RWDT_LL_STG_SEL_RESET_RTC       4

FORCE_INLINE_ATTR void rwdt_ll_enable(rtc_cntl_dev_t *hw)
{
	hw->wdt_config0.en = 1;
}

FORCE_INLINE_ATTR void rwdt_ll_disable(rtc_cntl_dev_t *hw)
{
	hw->wdt_config0.en = 0;
}

FORCE_INLINE_ATTR bool rwdt_ll_check_if_enabled(rtc_cntl_dev_t *hw)
{
	return (hw->wdt_config0.en) ? true : false;
}

FORCE_INLINE_ATTR void rwdt_ll_config_stage(rtc_cntl_dev_t *hw, wdt_stage_t stage, uint32_t timeout_ticks, wdt_stage_action_t behavior)
{
	switch (stage) {
	case WDT_STAGE0:
		hw->wdt_config0.stg0 = behavior;
		hw->wdt_config1 = timeout_ticks >> 1;
		break;
	case WDT_STAGE1:
		hw->wdt_config0.stg1 = behavior;
		hw->wdt_config2 = timeout_ticks;
		break;
	case WDT_STAGE2:
		hw->wdt_config0.stg2 = behavior;
		hw->wdt_config3 = timeout_ticks;
		break;
	case WDT_STAGE3:
		hw->wdt_config0.stg3 = behavior;
		hw->wdt_config4 = timeout_ticks;
		break;
	default:
		abort();
	}
}

FORCE_INLINE_ATTR void rwdt_ll_disable_stage(rtc_cntl_dev_t *hw, wdt_stage_t stage)
{
	switch (stage) {
	case WDT_STAGE0:
		hw->wdt_config0.stg0 = WDT_STAGE_ACTION_OFF;
		break;
	case WDT_STAGE1:
		hw->wdt_config0.stg1 = WDT_STAGE_ACTION_OFF;
		break;
	case WDT_STAGE2:
		hw->wdt_config0.stg2 = WDT_STAGE_ACTION_OFF;
		break;
	case WDT_STAGE3:
		hw->wdt_config0.stg3 = WDT_STAGE_ACTION_OFF;
		break;
	default:
		abort();
	}
}

FORCE_INLINE_ATTR void rwdt_ll_set_cpu_reset_length(rtc_cntl_dev_t *hw, wdt_reset_sig_length_t length)
{
	hw->wdt_config0.cpu_reset_length = length;
}

FORCE_INLINE_ATTR void rwdt_ll_set_sys_reset_length(rtc_cntl_dev_t *hw, wdt_reset_sig_length_t length)
{
	hw->wdt_config0.sys_reset_length = length;
}

FORCE_INLINE_ATTR void rwdt_ll_set_flashboot_en(rtc_cntl_dev_t *hw, bool enable)
{
	hw->wdt_config0.flashboot_mod_en = (enable) ? 1 : 0;
}

FORCE_INLINE_ATTR void rwdt_ll_set_procpu_reset_en(rtc_cntl_dev_t *hw, bool enable)
{
	hw->wdt_config0.procpu_reset_en = (enable) ? 1 : 0;
}

FORCE_INLINE_ATTR void rwdt_ll_set_appcpu_reset_en(rtc_cntl_dev_t *hw, bool enable)
{
	hw->wdt_config0.appcpu_reset_en = (enable) ? 1 : 0;
}

FORCE_INLINE_ATTR void rwdt_ll_set_pause_in_sleep_en(rtc_cntl_dev_t *hw, bool enable)
{
	hw->wdt_config0.pause_in_slp = (enable) ? 1 : 0;
}

FORCE_INLINE_ATTR void rwdt_ll_set_chip_reset_en(rtc_cntl_dev_t *hw, bool enable)
{
	hw->wdt_config0.chip_reset_en = (enable) ? 1 : 0;
}

FORCE_INLINE_ATTR void rwdt_ll_set_chip_reset_width(rtc_cntl_dev_t *hw, uint32_t width)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->wdt_config0, chip_reset_width, width);
}

FORCE_INLINE_ATTR void rwdt_ll_feed(rtc_cntl_dev_t *hw)
{
	hw->wdt_feed.feed = 1;
}

FORCE_INLINE_ATTR void rwdt_ll_write_protect_enable(rtc_cntl_dev_t *hw)
{
	hw->wdt_wprotect = 0;
}

FORCE_INLINE_ATTR void rwdt_ll_write_protect_disable(rtc_cntl_dev_t *hw)
{
	hw->wdt_wprotect = RWDT_LL_WDT_WKEY_VALUE;
}

FORCE_INLINE_ATTR void rwdt_ll_set_intr_enable(rtc_cntl_dev_t *hw, bool enable)
{
	hw->int_ena.rtc_wdt = (enable) ? 1 : 0;
}

FORCE_INLINE_ATTR bool rwdt_ll_check_intr_status(rtc_cntl_dev_t *hw)
{
	return (hw->int_st.rtc_wdt) ? true : false;
}

FORCE_INLINE_ATTR void rwdt_ll_clear_intr_status(rtc_cntl_dev_t *hw)
{
	hw->int_clr.rtc_wdt = 1;
}

#ifdef __cplusplus
}
#endif
