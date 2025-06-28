
#include <stdlib.h>
#include "soc/rtc_io.h"
#include "soc/sens.h"
#include "soc/usb_serial_jtag.h"

#define RTCIO_LL_PIN_FUNC     0

void rtcio_ll_function_select(int rtcio_num, rtcio_ll_func_t func)
{
	if (func == RTCIO_FUNC_RTC) {
		// Disable USB Serial JTAG if pin 19 or pin 20 needs to select the rtc function
		if (rtcio_num == rtc_io_num_map[USB_DM_GPIO_NUM] || rtcio_num == rtc_io_num_map[USB_DP_GPIO_NUM]) {
			USB_SERIAL_JTAG->conf0.usb_pad_enable = 0;
		}
		SENS->sar_peri_clk_gate_conf.iomux_clk_en = 1;
		// 0: GPIO connected to digital GPIO module. 1: GPIO connected to analog RTC module.
		SET_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, (rtc_io_desc[rtcio_num].mux));
		//0:RTC FUNCTION 1,2,3:Reserved
		SET_PERI_REG_BITS(rtc_io_desc[rtcio_num].reg, RTC_IO_TOUCH_PAD1_FUN_SEL_V, RTCIO_LL_PIN_FUNC, rtc_io_desc[rtcio_num].func);
	} else if (func == RTCIO_FUNC_DIGITAL) {
		CLEAR_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, (rtc_io_desc[rtcio_num].mux));
		SENS->sar_peri_clk_gate_conf.iomux_clk_en = 0;
		// USB Serial JTAG pad re-enable won't be done here (it requires both DM and DP pins not in rtc function)
		// Instead, USB_SERIAL_JTAG_USB_PAD_ENABLE needs to be guaranteed to be set in usb_serial_jtag driver
	}
}

void rtcio_ll_output_enable(int rtcio_num)
{
	RTCIO->enable_w1ts.w1ts = (1U << rtcio_num);
}

void rtcio_ll_output_disable(int rtcio_num)
{
	RTCIO->enable_w1tc.w1tc = (1U << rtcio_num);
}

void rtcio_ll_set_level(int rtcio_num, uint32_t level)
{
	if (level) {
		RTCIO->out_w1ts.w1ts = (1U << rtcio_num);
	} else {
		RTCIO->out_w1tc.w1tc = (1U << rtcio_num);
	}
}

void rtcio_ll_input_enable(int rtcio_num)
{
	SET_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].ie);
}

void rtcio_ll_input_disable(int rtcio_num)
{
	CLEAR_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].ie);
}

uint32_t rtcio_ll_get_level(int rtcio_num)
{
	return (uint32_t)(RTCIO->in_val.in >> rtcio_num) & 0x1;
}

void rtcio_ll_set_drive_capability(int rtcio_num, uint32_t strength)
{
	if (rtc_io_desc[rtcio_num].drv_v) {
		SET_PERI_REG_BITS(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].drv_v, strength, rtc_io_desc[rtcio_num].drv_s);
	}
}

uint32_t rtcio_ll_get_drive_capability(int rtcio_num)
{
	return GET_PERI_REG_BITS2(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].drv_v, rtc_io_desc[rtcio_num].drv_s);
}

void rtcio_ll_output_mode_set(int rtcio_num, rtcio_ll_out_mode_t mode)
{
	RTCIO->pin[rtcio_num].pad_driver = mode;
}

void rtcio_ll_pullup_enable(int rtcio_num)
{
	if (rtc_io_desc[rtcio_num].pullup) {
		SET_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].pullup);
	}
}

void rtcio_ll_pullup_disable(int rtcio_num)
{
	// The pull-up value of the USB pins are controlled by the pins’ pull-up value together with USB pull-up value
	// USB DP pin is default to PU enabled
	// Note that from esp32s3 ECO1, USB_EXCHG_PINS feature has been supported. If this efuse is burnt, the gpio pin
	// which should be checked is USB_DM_GPIO_NUM instead.
	if (rtcio_num == USB_DP_GPIO_NUM) {
		SET_PERI_REG_MASK(USB_SERIAL_JTAG_CONF0_REG, USB_SERIAL_JTAG_PAD_PULL_OVERRIDE);
		CLEAR_PERI_REG_MASK(USB_SERIAL_JTAG_CONF0_REG, USB_SERIAL_JTAG_DP_PULLUP);
	}
	if (rtc_io_desc[rtcio_num].pullup) {
		CLEAR_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].pullup);
	}
}

void rtcio_ll_pulldown_enable(int rtcio_num)
{
	if (rtc_io_desc[rtcio_num].pulldown) {
		SET_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].pulldown);
	}
}

void rtcio_ll_pulldown_disable(int rtcio_num)
{
	if (rtc_io_desc[rtcio_num].pulldown) {
		CLEAR_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].pulldown);
	}
}

void rtcio_ll_force_hold_enable(int rtcio_num)
{
	SET_PERI_REG_MASK(RTC_CNTL_PAD_HOLD_REG, rtc_io_desc[rtcio_num].hold_force);
}

void rtcio_ll_force_hold_disable(int rtcio_num)
{
	CLEAR_PERI_REG_MASK(RTC_CNTL_PAD_HOLD_REG, rtc_io_desc[rtcio_num].hold_force);
}

void rtcio_ll_force_hold_all(void)
{
	SET_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_PAD_FORCE_HOLD_M);
}

void rtcio_ll_force_unhold_all(void)
{
	CLEAR_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_PAD_FORCE_HOLD_M);
}

void rtcio_ll_wakeup_enable(int rtcio_num, rtcio_ll_wake_type_t type)
{
	SENS->sar_peri_clk_gate_conf.iomux_clk_en = 1;
	RTCIO->pin[rtcio_num].wakeup_enable = 0x1;
	RTCIO->pin[rtcio_num].int_type = type;
}

void rtcio_ll_wakeup_disable(int rtcio_num)
{
	RTCIO->pin[rtcio_num].wakeup_enable = 0;
	RTCIO->pin[rtcio_num].int_type = RTCIO_WAKEUP_DISABLE;
}

void rtcio_ll_enable_output_in_sleep(gpio_num_t gpio_num)
{
	if (rtc_io_desc[gpio_num].slpoe) {
		SET_PERI_REG_MASK(rtc_io_desc[gpio_num].reg, rtc_io_desc[gpio_num].slpoe);
	}
}

void rtcio_ll_in_sleep_disable_output(gpio_num_t gpio_num)
{
	if (rtc_io_desc[gpio_num].slpoe) {
		CLEAR_PERI_REG_MASK(rtc_io_desc[gpio_num].reg, rtc_io_desc[gpio_num].slpoe);
	}
}

void rtcio_ll_in_sleep_enable_input(gpio_num_t gpio_num)
{
	SET_PERI_REG_MASK(rtc_io_desc[gpio_num].reg, rtc_io_desc[gpio_num].slpie);
}

void rtcio_ll_in_sleep_disable_input(gpio_num_t gpio_num)
{
	CLEAR_PERI_REG_MASK(rtc_io_desc[gpio_num].reg, rtc_io_desc[gpio_num].slpie);
}

void rtcio_ll_enable_sleep_setting(gpio_num_t gpio_num)
{
	SET_PERI_REG_MASK(rtc_io_desc[gpio_num].reg, rtc_io_desc[gpio_num].slpsel);
}

void rtcio_ll_disable_sleep_setting(gpio_num_t gpio_num)
{
	CLEAR_PERI_REG_MASK(rtc_io_desc[gpio_num].reg, rtc_io_desc[gpio_num].slpsel);
}

void rtcio_ll_ext0_set_wakeup_pin(int rtcio_num, int level)
{
	REG_SET_FIELD(RTC_IO_EXT_WAKEUP0_REG, RTC_IO_EXT_WAKEUP0_SEL, rtcio_num);
	// Set level which will trigger wakeup
	SET_PERI_REG_BITS(RTC_CNTL_EXT_WAKEUP_CONF_REG, 0x1,
			level , RTC_CNTL_EXT_WAKEUP0_LV_S);
}

