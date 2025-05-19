#include <stdbool.h>
#include "soc/rtc_cntl_periph.h"

#define XT_WDT_LL_XTAL32_DEAD_INTR_MASK RTC_CNTL_XTAL32K_DEAD_INT_ST_M

void xt_wdt_ll_enable(rtc_cntl_dev_t *hw, bool enable);
bool xt_wdt_ll_check_if_enabled(rtc_cntl_dev_t *hw);
void xt_wdt_ll_set_timeout(rtc_cntl_dev_t *hw, uint8_t timeout);
void xt_wdt_ll_reset(rtc_cntl_dev_t *hw);
void xt_wdt_ll_set_backup_clk_factor(rtc_cntl_dev_t *hw, uint32_t backup_clk_val);
void xt_wdt_ll_auto_backup_enable(rtc_cntl_dev_t *hw, bool enable);
void xt_wdt_ll_intr_enable(rtc_cntl_dev_t *hw, bool enable);
