#include <stdlib.h>
#include <stdbool.h>

#include "soc/mwdt.h"

#define RWDT_LL_WDT_WKEY_VALUE 0x50D83AA1

#define RWDT_LL_STG_SEL_OFF             0
#define RWDT_LL_STG_SEL_INT             1
#define RWDT_LL_STG_SEL_RESET_CPU       2
#define RWDT_LL_STG_SEL_RESET_SYSTEM    3
#define RWDT_LL_STG_SEL_RESET_RTC       4

#define RWDT_LL_RESET_LENGTH_100_NS    0
#define RWDT_LL_RESET_LENGTH_200_NS    1
#define RWDT_LL_RESET_LENGTH_300_NS    2
#define RWDT_LL_RESET_LENGTH_400_NS    3
#define RWDT_LL_RESET_LENGTH_500_NS    4
#define RWDT_LL_RESET_LENGTH_800_NS    5
#define RWDT_LL_RESET_LENGTH_1600_NS   6
#define RWDT_LL_RESET_LENGTH_3200_NS   7

void rwdt_ll_enable(rtc_cntl_dev_t *hw);
void rwdt_ll_disable(rtc_cntl_dev_t *hw);
bool rwdt_ll_check_if_enabled(rtc_cntl_dev_t *hw);
void rwdt_ll_config_stage(rtc_cntl_dev_t *hw, wdt_stage_t stage, uint32_t timeout_ticks, wdt_stage_action_t behavior);
void rwdt_ll_disable_stage(rtc_cntl_dev_t *hw, wdt_stage_t stage);
void rwdt_ll_set_cpu_reset_length(rtc_cntl_dev_t *hw, wdt_reset_sig_length_t length);
void rwdt_ll_set_sys_reset_length(rtc_cntl_dev_t *hw, wdt_reset_sig_length_t length);
void rwdt_ll_set_flashboot_en(rtc_cntl_dev_t *hw, bool enable);
void rwdt_ll_set_procpu_reset_en(rtc_cntl_dev_t *hw, bool enable);
void rwdt_ll_set_appcpu_reset_en(rtc_cntl_dev_t *hw, bool enable);
void rwdt_ll_set_pause_in_sleep_en(rtc_cntl_dev_t *hw, bool enable);
void rwdt_ll_set_chip_reset_en(rtc_cntl_dev_t *hw, bool enable);
void rwdt_ll_set_chip_reset_width(rtc_cntl_dev_t *hw, uint32_t width);
void rwdt_ll_feed(rtc_cntl_dev_t *hw);
void rwdt_ll_write_protect_enable(rtc_cntl_dev_t *hw);
void rwdt_ll_write_protect_disable(rtc_cntl_dev_t *hw);
void rwdt_ll_set_intr_enable(rtc_cntl_dev_t *hw, bool enable);
bool rwdt_ll_check_intr_status(rtc_cntl_dev_t *hw);
void rwdt_ll_clear_intr_status(rtc_cntl_dev_t *hw);
