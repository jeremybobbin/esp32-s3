#include "soc/random.h"
#include "soc/rtc.h"
#include "soc/gpio.h"
#include <string.h>

#define APB_CYCLE_WAIT_NUM (1778)
#define MIN(a, b) (a) > (b) ? (b) : (a)

uint32_t esp_random(void)
{
	uint32_t cpu_to_apb_freq_ratio = esp_clk_cpu_freq() / esp_clk_apb_freq();

	static uint32_t last_ccount = 0;
	uint32_t ccount;
	uint32_t result = 0;
	do {
		ccount = cpu_ll_get_cycle_count();
		result ^= REG_READ(WDEV_RND_REG);
	} while (ccount - last_ccount < cpu_to_apb_freq_ratio * APB_CYCLE_WAIT_NUM);
	last_ccount = ccount;
	return result ^ REG_READ(WDEV_RND_REG);
}

void esp_fill_random(void *buf, size_t len)
{
	uint8_t *buf_bytes = (uint8_t *)buf;
	while (len > 0) {
		uint32_t word = esp_random();
		uint32_t to_copy = MIN(sizeof(word), len);
		memcpy(buf_bytes, &word, to_copy);
		buf_bytes += to_copy;
		len -= to_copy;
	}
}

