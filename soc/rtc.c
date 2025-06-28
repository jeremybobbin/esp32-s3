#include "rom/ets_sys.h"
#include "soc/gpio.h"
#include "rom/rtc.h"
#include "soc/rtc.h"
//#include "soc/rtc_cntl.h"


#define MHZ (1000000)
#define MIN(a, b) (a) > (b) ? (b) : (a)


// g_ticks_us defined in ROMs for PRO and APP CPU
extern uint32_t g_ticks_per_us_pro;
static portMUX_TYPE s_esp_rtc_time_lock = portMUX_INITIALIZER_UNLOCKED;
static uint64_t s_esp_rtc_time_us, s_rtc_last_ticks;

int s_get_cpu_freq_mhz(void) {
	return ets_get_cpu_frequency();
}

int esp_clk_cpu_freq(void) {
	return s_get_cpu_freq_mhz() * MHZ;
}

int esp_clk_apb_freq(void) {
	return MIN(s_get_cpu_freq_mhz(), 80) * MHZ;
}

int esp_clk_xtal_freq(void) {
	return rtc_clk_xtal_freq_get() * MHZ;
}

void ets_update_cpu_frequency(uint32_t ticks_per_us) {
	g_ticks_per_us_pro = ticks_per_us;
}

uint64_t esp_rtc_get_time_us(void) {
	portENTER_CRITICAL_SAFE(&s_esp_rtc_time_lock);
	const uint32_t cal = esp_clk_slowclk_cal_get();
	if (cal == 0) {
		s_esp_rtc_time_us = 0;
		s_rtc_last_ticks = 0;
	}
	const uint64_t rtc_this_ticks = rtc_time_get();
	const uint64_t ticks = rtc_this_ticks - s_rtc_last_ticks;
	const uint64_t ticks_low = ticks & UINT32_MAX;
	const uint64_t ticks_high = ticks >> 32;
	const uint64_t delta_time_us = ((ticks_low * cal) >> RTC_CLK_CAL_FRACT) + ((ticks_high * cal) << (32 - RTC_CLK_CAL_FRACT));
	s_esp_rtc_time_us += delta_time_us;
	s_rtc_last_ticks = rtc_this_ticks;
	portEXIT_CRITICAL_SAFE(&s_esp_rtc_time_lock);
	return s_esp_rtc_time_us;
}

void esp_clk_slowclk_cal_set(uint32_t new_cal) {
	REG_WRITE(RTC_SLOW_CLK_CAL_REG, new_cal);
}

uint32_t esp_clk_slowclk_cal_get(void) {
	return REG_READ(RTC_SLOW_CLK_CAL_REG);
}

uint64_t esp_clk_rtc_time(void) {
	return 0;
}

void esp_clk_private_lock(void) {
	portENTER_CRITICAL(&s_esp_rtc_time_lock);
}

void esp_clk_private_unlock(void) {
	portEXIT_CRITICAL(&s_esp_rtc_time_lock);
}

