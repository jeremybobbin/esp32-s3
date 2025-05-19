#include <stdint.h>
#include <stdbool.h>

#define MWDT_LL_WKEY_VALUE 0x50D83AA1

#define MWDT_LL_STG_SEL_OFF 0
#define MWDT_LL_STG_SEL_INT 1
#define MWDT_LL_STG_SEL_RESET_CPU 2
#define MWDT_LL_STG_SEL_RESET_SYSTEM 3

#define MWDT_LL_RESET_LENGTH_100_NS    0
#define MWDT_LL_RESET_LENGTH_200_NS    1
#define MWDT_LL_RESET_LENGTH_300_NS    2
#define MWDT_LL_RESET_LENGTH_400_NS    3
#define MWDT_LL_RESET_LENGTH_500_NS    4
#define MWDT_LL_RESET_LENGTH_800_NS    5
#define MWDT_LL_RESET_LENGTH_1600_NS   6
#define MWDT_LL_RESET_LENGTH_3200_NS   7

void mwdt_ll_enable(timg_dev_t *hw);
void mwdt_ll_disable(timg_dev_t *hw);
bool mwdt_ll_check_if_enabled(timg_dev_t *hw);
void mwdt_ll_config_stage(timg_dev_t *hw, wdt_stage_t stage, uint32_t timeout, wdt_stage_action_t behavior);
void mwdt_ll_disable_stage(timg_dev_t *hw, uint32_t stage);
void mwdt_ll_set_edge_intr(timg_dev_t *hw, bool enable);
void mwdt_ll_set_level_intr(timg_dev_t *hw, bool enable);
void mwdt_ll_set_cpu_reset_length(timg_dev_t *hw, wdt_reset_sig_length_t length);
void mwdt_ll_set_sys_reset_length(timg_dev_t *hw, wdt_reset_sig_length_t length);
void mwdt_ll_set_flashboot_en(timg_dev_t *hw, bool enable);
void mwdt_ll_set_prescaler(timg_dev_t *hw, uint32_t prescaler);
void mwdt_ll_feed(timg_dev_t *hw);
void mwdt_ll_write_protect_enable(timg_dev_t *hw);
void mwdt_ll_write_protect_disable(timg_dev_t *hw);
void mwdt_ll_clear_intr_status(timg_dev_t *hw);
void mwdt_ll_set_intr_enable(timg_dev_t *hw, bool enable);
