#include <stdint.h>
#include <stdbool.h>

uint32_t periph_ll_get_clk_en_mask(periph_module_t periph);
uint32_t periph_ll_get_rst_en_mask(periph_module_t periph, bool enable);
void periph_ll_enable_clk_clear_rst(periph_module_t periph);
void periph_ll_disable_clk_set_rst(periph_module_t periph);
void IRAM_ATTR periph_ll_wifi_bt_module_enable_clk_clear_rst(void);
void IRAM_ATTR periph_ll_wifi_bt_module_disable_clk_set_rst(void);
void periph_ll_reset(periph_module_t periph);
bool IRAM_ATTR periph_ll_periph_enabled(periph_module_t periph);
void periph_ll_wifi_module_enable_clk_clear_rst(void);
void periph_ll_wifi_module_disable_clk_set_rst(void);
