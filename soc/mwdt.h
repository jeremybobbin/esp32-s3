#include <stdint.h>
#include <stdbool.h>

#include "soc/timer.h"

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

typedef enum {
	WDT_STAGE0 = 0,     /*!< Stage 0 */
	WDT_STAGE1 = 1,     /*!< Stage 1 */
	WDT_STAGE2 = 2,     /*!< Stage 2 */
	WDT_STAGE3 = 3      /*!< Stage 3 */
} wdt_stage_t;

typedef enum {
	WDT_STAGE_ACTION_OFF = 0,           /*!< Disabled. This stage will have no effects on the system. */
	WDT_STAGE_ACTION_INT = 1,           /*!< Trigger an interrupt when the stage expires. */
	WDT_STAGE_ACTION_RESET_CPU = 2,     /*!< Reset a CPU core when the stage expires. */
	WDT_STAGE_ACTION_RESET_SYSTEM = 3,  /*!< Reset the main system when the stage expires. This includes the CPU and all peripherals. The RTC is an exception and will not be reset. */
	WDT_STAGE_ACTION_RESET_RTC = 4,     /*!< Reset the main system and the RTC when the stage expires. ONLY AVAILABLE FOR RWDT */
} wdt_stage_action_t;

typedef enum {
	WDT_RESET_SIG_LENGTH_100ns = 0,    /*!< 100 ns */
	WDT_RESET_SIG_LENGTH_200ns = 1,    /*!< 200 ns */
	WDT_RESET_SIG_LENGTH_300ns = 2,    /*!< 300 ns */
	WDT_RESET_SIG_LENGTH_400ns = 3,    /*!< 400 ns */
	WDT_RESET_SIG_LENGTH_500ns = 4,    /*!< 500 ns */
	WDT_RESET_SIG_LENGTH_800ns = 5,    /*!< 800 ns */
	WDT_RESET_SIG_LENGTH_1_6us = 6,    /*!< 1.6 us */
	WDT_RESET_SIG_LENGTH_3_2us = 7     /*!< 3.2 us */
} wdt_reset_sig_length_t;

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
