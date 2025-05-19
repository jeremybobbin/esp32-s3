

// The LL layer for ESP32-S3 GPIO register operations


#include <stdbool.h>
#include "soc/soc.h"
#include "soc/gpio_periph.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "soc/usb_serial_jtag_reg.h"
#include "hal/gpio_types.h"
#include "soc/gpio_struct.h"


// Get GPIO hardware instance with giving gpio num
#define GPIO_LL_GET_HW(num) (((num) == 0) ? (&GPIO) : NULL)

// On ESP32S3, pro cpu and app cpu shares the same interrupt enable bit
#define GPIO_LL_INTR_ENA      (BIT(0))
#define GPIO_LL_NMI_INTR_ENA  (BIT(1))

static inline void gpio_ll_pullup_en(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	REG_SET_BIT(GPIO_PIN_MUX_REG[gpio_num], FUN_PU);
}

__attribute__((always_inline))
static inline void gpio_ll_pullup_dis(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	// The pull-up value of the USB pins are controlled by the pins’ pull-up value together with USB pull-up value
	// USB DP pin is default to PU enabled
	// Note that from esp32s3 ECO1, USB_EXCHG_PINS feature has been supported. If this efuse is burnt, the gpio pin
	// which should be checked is USB_DM_GPIO_NUM instead.
	if (gpio_num == USB_DP_GPIO_NUM) {
		SET_PERI_REG_MASK(USB_SERIAL_JTAG_CONF0_REG, USB_SERIAL_JTAG_PAD_PULL_OVERRIDE);
		CLEAR_PERI_REG_MASK(USB_SERIAL_JTAG_CONF0_REG, USB_SERIAL_JTAG_DP_PULLUP);
	}
	REG_CLR_BIT(IO_MUX_GPIO0_REG + (gpio_num * 4), FUN_PU);
}

static inline void gpio_ll_pulldown_en(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	REG_SET_BIT(GPIO_PIN_MUX_REG[gpio_num], FUN_PD);
}

__attribute__((always_inline))
static inline void gpio_ll_pulldown_dis(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	REG_CLR_BIT(IO_MUX_GPIO0_REG + (gpio_num * 4), FUN_PD);
}

static inline void gpio_ll_set_intr_type(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_int_type_t intr_type)
{
	hw->pin[gpio_num].int_type = intr_type;
}

static inline void gpio_ll_get_intr_status(gpio_dev_t *hw, uint32_t core_id, uint32_t *status)
{
	// On ESP32S3, pcpu_int register represents GPIO0-31 interrupt status on both cores
	(void)core_id;
	*status = hw->pcpu_int;
}

static inline void gpio_ll_get_intr_status_high(gpio_dev_t *hw, uint32_t core_id, uint32_t *status)
{
	// On ESP32S3, pcpu_int1 register represents GPIO32-48 interrupt status on both cores
	(void)core_id;
	*status = hw->pcpu_int1.intr;
}

static inline void gpio_ll_clear_intr_status(gpio_dev_t *hw, uint32_t mask)
{
	hw->status_w1tc = mask;
}

static inline void gpio_ll_clear_intr_status_high(gpio_dev_t *hw, uint32_t mask)
{
	hw->status1_w1tc.intr_st = mask;
}

static inline void gpio_ll_intr_enable_on_core(gpio_dev_t *hw, uint32_t core_id, gpio_num_t gpio_num)
{
	(void)core_id;
	GPIO.pin[gpio_num].int_ena = GPIO_LL_INTR_ENA;     //enable intr
}

static inline void gpio_ll_intr_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	hw->pin[gpio_num].int_ena = 0;                             //disable GPIO intr
}

__attribute__((always_inline))
static inline void gpio_ll_input_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	PIN_INPUT_DISABLE(IO_MUX_GPIO0_REG + (gpio_num * 4));
}

static inline void gpio_ll_input_enable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

__attribute__((always_inline))
static inline void gpio_ll_output_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	if (gpio_num < 32) {
		hw->enable_w1tc = (0x1 << gpio_num);
	} else {
		hw->enable1_w1tc.data = (0x1 << (gpio_num - 32));
	}

	// Ensure no other output signal is routed via GPIO matrix to this pin
	REG_WRITE(GPIO_FUNC0_OUT_SEL_CFG_REG + (gpio_num * 4),
			  SIG_GPIO_OUT_IDX);
}

static inline void gpio_ll_output_enable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	if (gpio_num < 32) {
		hw->enable_w1ts = (0x1 << gpio_num);
	} else {
		hw->enable1_w1ts.data = (0x1 << (gpio_num - 32));
	}
}

static inline void gpio_ll_od_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	hw->pin[gpio_num].pad_driver = 0;
}

static inline void gpio_ll_od_enable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	hw->pin[gpio_num].pad_driver = 1;
}

static inline __attribute__((always_inline)) void gpio_ll_func_sel(gpio_dev_t *hw, uint8_t gpio_num, uint32_t func)
{
	if (gpio_num == 19 || gpio_num == 20) {
		CLEAR_PERI_REG_MASK(USB_SERIAL_JTAG_CONF0_REG, USB_SERIAL_JTAG_USB_PAD_ENABLE);
	}
	PIN_FUNC_SELECT(IO_MUX_GPIO0_REG + (gpio_num * 4), func);
}

static inline void gpio_ll_set_level(gpio_dev_t *hw, gpio_num_t gpio_num, uint32_t level)
{
	if (level) {
		if (gpio_num < 32) {
			hw->out_w1ts = (1 << gpio_num);
		} else {
			hw->out1_w1ts.data = (1 << (gpio_num - 32));
		}
	} else {
		if (gpio_num < 32) {
			hw->out_w1tc = (1 << gpio_num);
		} else {
			hw->out1_w1tc.data = (1 << (gpio_num - 32));
		}
	}
}

static inline int gpio_ll_get_level(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	if (gpio_num < 32) {
		return (hw->in >> gpio_num) & 0x1;
	} else {
		return (hw->in1.data >> (gpio_num - 32)) & 0x1;
	}
}

static inline void gpio_ll_wakeup_enable(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_int_type_t intr_type)
{
	hw->pin[gpio_num].int_type = intr_type;
	hw->pin[gpio_num].wakeup_enable = 0x1;
}

static inline void gpio_ll_wakeup_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	hw->pin[gpio_num].wakeup_enable = 0;
}

static inline void gpio_ll_set_drive_capability(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_drive_cap_t strength)
{
	SET_PERI_REG_BITS(GPIO_PIN_MUX_REG[gpio_num], FUN_DRV_V, strength, FUN_DRV_S);
}

static inline void gpio_ll_get_drive_capability(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_drive_cap_t *strength)
{
	*strength = (gpio_drive_cap_t)GET_PERI_REG_BITS2(GPIO_PIN_MUX_REG[gpio_num], FUN_DRV_V, FUN_DRV_S);
}

static inline void gpio_ll_deep_sleep_hold_en(gpio_dev_t *hw)
{
	CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_UNHOLD);
	SET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_AUTOHOLD_EN_M);
}

static inline void gpio_ll_deep_sleep_hold_dis(gpio_dev_t *hw)
{
	CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_AUTOHOLD_EN_M);
}

__attribute__((always_inline))
static inline bool gpio_ll_deep_sleep_hold_is_en(gpio_dev_t *hw)
{
	return !GET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_UNHOLD) && GET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_AUTOHOLD_EN_M);
}

static inline void gpio_ll_hold_en(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	SET_PERI_REG_MASK(RTC_CNTL_DIG_PAD_HOLD_REG, GPIO_HOLD_MASK[gpio_num]);
}

static inline void gpio_ll_hold_dis(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_PAD_HOLD_REG, GPIO_HOLD_MASK[gpio_num]);
}

__attribute__((always_inline))
static inline bool gpio_ll_is_digital_io_hold(gpio_dev_t *hw, uint32_t gpio_num)
{
	return GET_PERI_REG_MASK(RTC_CNTL_DIG_PAD_HOLD_REG, BIT(gpio_num - 21));
}

static inline void gpio_ll_iomux_in(gpio_dev_t *hw, uint32_t gpio, uint32_t signal_idx)
{
	hw->func_in_sel_cfg[signal_idx].sig_in_sel = 0;
	PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio]);
}

static inline __attribute__((always_inline)) void gpio_ll_iomux_func_sel(uint32_t pin_name, uint32_t func)
{
	if (pin_name == IO_MUX_GPIO19_REG || pin_name == IO_MUX_GPIO20_REG) {
		CLEAR_PERI_REG_MASK(USB_SERIAL_JTAG_CONF0_REG, USB_SERIAL_JTAG_USB_PAD_ENABLE);
	}
	PIN_FUNC_SELECT(pin_name, func);
}

static inline void gpio_ll_iomux_out(gpio_dev_t *hw, uint8_t gpio_num, int func, uint32_t oen_inv)
{
	hw->func_out_sel_cfg[gpio_num].oen_sel = 0;
	hw->func_out_sel_cfg[gpio_num].oen_inv_sel = oen_inv;
	gpio_ll_iomux_func_sel(GPIO_PIN_MUX_REG[gpio_num], func);
}

static inline void gpio_ll_force_hold_all(gpio_dev_t *hw)
{
	CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_UNHOLD);
	SET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_HOLD);
}

static inline void gpio_ll_force_unhold_all(void)
{
	CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_HOLD);
	SET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_UNHOLD);
	SET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_CLR_DG_PAD_AUTOHOLD);
}

static inline void gpio_ll_sleep_sel_en(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	PIN_SLP_SEL_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

static inline void gpio_ll_sleep_sel_dis(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	PIN_SLP_SEL_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

static inline void gpio_ll_sleep_pullup_dis(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	PIN_SLP_PULLUP_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

static inline void gpio_ll_sleep_pullup_en(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	PIN_SLP_PULLUP_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

static inline void gpio_ll_sleep_pulldown_en(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	PIN_SLP_PULLDOWN_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

static inline void gpio_ll_sleep_pulldown_dis(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	PIN_SLP_PULLDOWN_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

static inline void gpio_ll_sleep_input_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	PIN_SLP_INPUT_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

static inline void gpio_ll_sleep_input_enable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	PIN_SLP_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

static inline void gpio_ll_sleep_output_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	PIN_SLP_OUTPUT_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

static inline void gpio_ll_sleep_output_enable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
	PIN_SLP_OUTPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

