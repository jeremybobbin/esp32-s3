#include "freertos/FreeRTOS.h"
#include "soc/clk_gate.h"
#include "heap/soc_memory_layout.h"

static portMUX_TYPE periph_spinlock = portMUX_INITIALIZER_UNLOCKED;
static uint8_t ref_counts[PERIPH_MODULE_MAX] = {0};

void periph_module_enable(periph_module_t periph) {
	assert(periph < PERIPH_MODULE_MAX);
	portENTER_CRITICAL_SAFE(&periph_spinlock);
	if (ref_counts[periph] == 0) {
		periph_ll_enable_clk_clear_rst(periph);
	}
	ref_counts[periph]++;
	portEXIT_CRITICAL_SAFE(&periph_spinlock);
}

void periph_module_disable(periph_module_t periph) {
	assert(periph < PERIPH_MODULE_MAX);
	portENTER_CRITICAL_SAFE(&periph_spinlock);
	ref_counts[periph]--;
	if (ref_counts[periph] == 0) {
		periph_ll_disable_clk_set_rst(periph);
	}
	portEXIT_CRITICAL_SAFE(&periph_spinlock);
}

void periph_module_reset(periph_module_t periph) {
	assert(periph < PERIPH_MODULE_MAX);
	portENTER_CRITICAL_SAFE(&periph_spinlock);
	periph_ll_reset(periph);
	portEXIT_CRITICAL_SAFE(&periph_spinlock);
}

void wifi_bt_common_module_enable(void) {
	portENTER_CRITICAL_SAFE(&periph_spinlock);
	if (ref_counts[PERIPH_WIFI_BT_COMMON_MODULE] == 0) {
		periph_ll_wifi_bt_module_enable_clk_clear_rst();
	}
	ref_counts[PERIPH_WIFI_BT_COMMON_MODULE]++;
	portEXIT_CRITICAL_SAFE(&periph_spinlock);
}

void wifi_bt_common_module_disable(void) {
	portENTER_CRITICAL_SAFE(&periph_spinlock);
	ref_counts[PERIPH_WIFI_BT_COMMON_MODULE]--;
	if (ref_counts[PERIPH_WIFI_BT_COMMON_MODULE] == 0) {
		periph_ll_wifi_bt_module_disable_clk_set_rst();
	}
	portEXIT_CRITICAL_SAFE(&periph_spinlock);
}

void wifi_module_enable(void) {
	portENTER_CRITICAL_SAFE(&periph_spinlock);
	periph_ll_wifi_module_enable_clk_clear_rst();
	portEXIT_CRITICAL_SAFE(&periph_spinlock);
}

void wifi_module_disable(void) {
	portENTER_CRITICAL_SAFE(&periph_spinlock);
	periph_ll_wifi_module_disable_clk_set_rst();
	portEXIT_CRITICAL_SAFE(&periph_spinlock);
}
