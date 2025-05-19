
// The LL layer for Timer Group register operations.
// Note that most of the register operations in this layer are non-atomic operations.



#include <stdint.h>
#include <stdbool.h>
#include "hal/misc.h"
#include "soc/timer_periph.h"
#include "soc/timer_group_struct.h"
#include "hal/wdt_types.h"
#include "esp_attr.h"
#include "esp_assert.h"

#define MWDT_LL_STG_SEL_OFF 0
#define MWDT_LL_STG_SEL_INT 1
#define MWDT_LL_STG_SEL_RESET_CPU 2
#define MWDT_LL_STG_SEL_RESET_SYSTEM 3

void mwdt_ll_enable(timg_dev_t *hw)
{
	hw->wdtconfig0.wdt_en = 1;
}

void mwdt_ll_disable(timg_dev_t *hw)
{
	hw->wdtconfig0.wdt_en = 0;
}

bool mwdt_ll_check_if_enabled(timg_dev_t *hw)
{
	return (hw->wdtconfig0.wdt_en) ? true : false;
}

void mwdt_ll_config_stage(timg_dev_t *hw, wdt_stage_t stage, uint32_t timeout, wdt_stage_action_t behavior)
{
	switch (stage) {
	case WDT_STAGE0:
		hw->wdtconfig0.wdt_stg0 = behavior;
		hw->wdtconfig2.wdt_stg0_hold = timeout;
		break;
	case WDT_STAGE1:
		hw->wdtconfig0.wdt_stg1 = behavior;
		hw->wdtconfig3.wdt_stg1_hold = timeout;
		break;
	case WDT_STAGE2:
		hw->wdtconfig0.wdt_stg2 = behavior;
		hw->wdtconfig4.wdt_stg2_hold = timeout;
		break;
	case WDT_STAGE3:
		hw->wdtconfig0.wdt_stg3 = behavior;
		hw->wdtconfig5.wdt_stg3_hold = timeout;
		break;
	default:
		break;
	}
}

void mwdt_ll_disable_stage(timg_dev_t *hw, uint32_t stage)
{
	switch (stage) {
	case WDT_STAGE0:
		hw->wdtconfig0.wdt_stg0 = WDT_STAGE_ACTION_OFF;
		break;
	case WDT_STAGE1:
		hw->wdtconfig0.wdt_stg1 = WDT_STAGE_ACTION_OFF;
		break;
	case WDT_STAGE2:
		hw->wdtconfig0.wdt_stg2 = WDT_STAGE_ACTION_OFF;
		break;
	case WDT_STAGE3:
		hw->wdtconfig0.wdt_stg3 = WDT_STAGE_ACTION_OFF;
		break;
	default:
		break;
	}
}

void mwdt_ll_set_edge_intr(timg_dev_t *hw, bool enable)
{
}

void mwdt_ll_set_level_intr(timg_dev_t *hw, bool enable)
{
	hw->int_ena_timers.wdt_int_ena = enable;
}

void mwdt_ll_set_cpu_reset_length(timg_dev_t *hw, wdt_reset_sig_length_t length)
{
	hw->wdtconfig0.wdt_cpu_reset_length = length;
}

void mwdt_ll_set_sys_reset_length(timg_dev_t *hw, wdt_reset_sig_length_t length)
{
	hw->wdtconfig0.wdt_sys_reset_length = length;
}

void mwdt_ll_set_flashboot_en(timg_dev_t *hw, bool enable)
{
	hw->wdtconfig0.wdt_flashboot_mod_en = (enable) ? 1 : 0;
}

void mwdt_ll_set_prescaler(timg_dev_t *hw, uint32_t prescaler)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->wdtconfig1, wdt_clk_prescale, prescaler);
}

void mwdt_ll_feed(timg_dev_t *hw)
{
	hw->wdtfeed.wdt_feed = 1;
}

void mwdt_ll_write_protect_enable(timg_dev_t *hw)
{
	hw->wdtwprotect.wdt_wkey = 0;
}

void mwdt_ll_write_protect_disable(timg_dev_t *hw)
{
	hw->wdtwprotect.wdt_wkey = MWDT_LL_WKEY_VALUE;
}

void mwdt_ll_clear_intr_status(timg_dev_t *hw)
{
	hw->int_clr_timers.wdt_int_clr = 1;
}

void mwdt_ll_set_intr_enable(timg_dev_t *hw, bool enable)
{
	hw->int_ena_timers.wdt_int_ena = (enable) ? 1 : 0;
}

