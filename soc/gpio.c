#include <stdbool.h>
#include "soc/gpio.h"
#include "soc/usb_serial_jtag.h"
#include "soc/rtc_cntl.h"

// Get GPIO hardware instance with giving gpio num
#define GPIO_LL_GET_HW(num) (((num) == 0) ? (&GPIO) : NULL)

// On ESP32S3, pro cpu and app cpu shares the same interrupt enable bit
#define GPIO_LL_INTR_ENA      (1<<0)
#define GPIO_LL_NMI_INTR_ENA  (1<<1)

#define SIG_GPIO_OUT_IDX  256
#define GPIO_FUNC0_OUT_SEL_CFG_REG          (0x60004000+0x554)

gpio_dev_t *GPIO = (void*)0x60004000;

const uint32_t GPIO_PIN_MUX_REG[SOC_GPIO_PIN_COUNT] = {
	PERIPHS_IO_MUX_GPIO0_U,
	PERIPHS_IO_MUX_GPIO1_U,
	PERIPHS_IO_MUX_GPIO2_U,
	PERIPHS_IO_MUX_GPIO3_U,
	PERIPHS_IO_MUX_GPIO4_U,
	PERIPHS_IO_MUX_GPIO5_U,
	PERIPHS_IO_MUX_GPIO6_U,
	PERIPHS_IO_MUX_GPIO7_U,
	PERIPHS_IO_MUX_GPIO8_U,
	PERIPHS_IO_MUX_GPIO9_U,
	PERIPHS_IO_MUX_GPIO10_U,
	PERIPHS_IO_MUX_GPIO11_U,
	PERIPHS_IO_MUX_GPIO12_U,
	PERIPHS_IO_MUX_GPIO13_U,
	PERIPHS_IO_MUX_GPIO14_U,
	PERIPHS_IO_MUX_XTAL_32K_P_U,
	PERIPHS_IO_MUX_XTAL_32K_N_U,
	PERIPHS_IO_MUX_DAC_1_U,
	PERIPHS_IO_MUX_DAC_2_U,
	PERIPHS_IO_MUX_GPIO19_U,
	PERIPHS_IO_MUX_GPIO20_U,
	PERIPHS_IO_MUX_GPIO21_U,
	0,
	0,
	0,
	0,
	PERIPHS_IO_MUX_SPICS1_U,
	PERIPHS_IO_MUX_SPIHD_U,
	PERIPHS_IO_MUX_SPIWP_U,
	PERIPHS_IO_MUX_SPICS0_U,
	PERIPHS_IO_MUX_SPICLK_U,
	PERIPHS_IO_MUX_SPIQ_U,
	PERIPHS_IO_MUX_SPID_U,
	PERIPHS_IO_MUX_GPIO33_U,
	PERIPHS_IO_MUX_GPIO34_U,
	PERIPHS_IO_MUX_GPIO35_U,
	PERIPHS_IO_MUX_GPIO36_U,
	PERIPHS_IO_MUX_GPIO37_U,
	PERIPHS_IO_MUX_GPIO38_U,
	PERIPHS_IO_MUX_MTCK_U,
	PERIPHS_IO_MUX_MTDO_U,
	PERIPHS_IO_MUX_MTDI_U,
	PERIPHS_IO_MUX_MTMS_U,
	PERIPHS_IO_MUX_U0TXD_U,
	PERIPHS_IO_MUX_U0RXD_U,
	PERIPHS_IO_MUX_GPIO45_U,
	PERIPHS_IO_MUX_GPIO46_U,
	PERIPHS_IO_MUX_SPICLK_P_U,
	PERIPHS_IO_MUX_SPICLK_N_U,
};

const uint32_t GPIO_HOLD_MASK[SOC_GPIO_PIN_COUNT] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1<<1,
	1<<2,
	1<<3,
	1<<4,
	1<<5,
	1<<6,
	1<<7,
	1<<8,
	1<<9,
	1<<10,
	1<<11,
	1<<12,
	1<<13,
	1<<14,
	1<<15,
	1<<16,
	1<<17,
	1<<18,
	1<<19,
	1<<20,
	1<<21,
	1<<22,
	1<<23,
	1<<24,
	1<<25,
	1<<26,
	1<<27,
};

void gpio_ll_pullup_en(gpio_dev_t *hw, gpio_num_t gpio_num) {
	*((volatile int*)GPIO_PIN_MUX_REG[gpio_num]) |= FUN_PU;
}

void gpio_ll_pullup_dis(gpio_dev_t *hw, gpio_num_t gpio_num) {
	// The pull-up value of the USB pins are controlled by the pins’ pull-up value together with USB pull-up value
	// USB DP pin is default to PU enabled
	// Note that from esp32s3 ECO1, USB_EXCHG_PINS feature has been supported. If this efuse is burnt, the gpio pin
	// which should be checked is USB_DM_GPIO_NUM instead.
	if (gpio_num == USB_DP_GPIO_NUM) {
		*((volatile int*)USB_SERIAL_JTAG_CONF0_REG) |= USB_SERIAL_JTAG_PAD_PULL_OVERRIDE;
		*((volatile int*)USB_SERIAL_JTAG_CONF0_REG) &= ~USB_SERIAL_JTAG_DP_PULLUP;
	}
	REG_CLR_BIT(PERIPHS_IO_MUX_GPIO0_U + (gpio_num * 4), FUN_PU);
}

void gpio_ll_pulldown_en(gpio_dev_t *hw, gpio_num_t gpio_num) {
	*((volatile int*)GPIO_PIN_MUX_REG[gpio_num]) |= FUN_PD;
}

void gpio_ll_pulldown_dis(gpio_dev_t *hw, gpio_num_t gpio_num) {
	REG_CLR_BIT(PERIPHS_IO_MUX_GPIO0_U + (gpio_num * 4), FUN_PD);
}

void gpio_ll_set_intr_type(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_int_type_t intr_type) {
	hw->pin[gpio_num].int_type = intr_type;
}

void gpio_ll_get_intr_status(gpio_dev_t *hw, uint32_t core_id, uint32_t *status) {
	// On ESP32S3, pcpu_int register represents GPIO0-31 interrupt status on both cores
	(void)core_id;
	*status = hw->pcpu_int;
}

void gpio_ll_get_intr_status_high(gpio_dev_t *hw, uint32_t core_id, uint32_t *status) {
	// On ESP32S3, pcpu_int1 register represents GPIO32-48 interrupt status on both cores
	(void)core_id;
	*status = hw->pcpu_int1.intr;
}

void gpio_ll_clear_intr_status(gpio_dev_t *hw, uint32_t mask) {
	hw->status_w1tc = mask;
}

void gpio_ll_clear_intr_status_high(gpio_dev_t *hw, uint32_t mask) {
	hw->status1_w1tc.intr_st = mask;
}

void gpio_ll_intr_enable_on_core(gpio_dev_t *hw, uint32_t core_id, gpio_num_t gpio_num) {
	(void)core_id;
	GPIO->pin[gpio_num].int_ena = GPIO_LL_INTR_ENA;     //enable intr
}

void gpio_ll_intr_disable(gpio_dev_t *hw, gpio_num_t gpio_num) {
	hw->pin[gpio_num].int_ena = 0;                             //disable GPIO intr
}

void gpio_ll_input_disable(gpio_dev_t *hw, gpio_num_t gpio_num) {
	PIN_INPUT_DISABLE(PERIPHS_IO_MUX_GPIO0_U + (gpio_num * 4));
}

void gpio_ll_input_enable(gpio_dev_t *hw, gpio_num_t gpio_num) {
	PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

void gpio_ll_output_disable(gpio_dev_t *hw, gpio_num_t gpio_num) {
	if (gpio_num < 32) {
		hw->enable_w1tc = (0x1 << gpio_num);
	} else {
		hw->enable1_w1tc.data = (0x1 << (gpio_num - 32));
	}

	// Ensure no other output signal is routed via GPIO matrix to this pin
	*(volatile uint32_t *)(GPIO_FUNC0_OUT_SEL_CFG_REG + (gpio_num * 4)) = SIG_GPIO_OUT_IDX;
}

void gpio_ll_output_enable(gpio_dev_t *hw, gpio_num_t gpio_num) {
	if (gpio_num < 32) {
		hw->enable_w1ts = (0x1 << gpio_num);
	} else {
		hw->enable1_w1ts.data = (0x1 << (gpio_num - 32));
	}
}

void gpio_ll_od_disable(gpio_dev_t *hw, gpio_num_t gpio_num) {
	hw->pin[gpio_num].pad_driver = 0;
}

void gpio_ll_od_enable(gpio_dev_t *hw, gpio_num_t gpio_num) {
	hw->pin[gpio_num].pad_driver = 1;
}

void gpio_ll_func_sel(gpio_dev_t *hw, uint8_t gpio_num, uint32_t func) {
	if (gpio_num == 19 || gpio_num == 20) {
		*((volatile int*)USB_SERIAL_JTAG_CONF0_REG) &= ~USB_SERIAL_JTAG_USB_PAD_ENABLE;
	}
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U + (gpio_num * 4), func);
}

void gpio_ll_set_level(gpio_dev_t *hw, gpio_num_t gpio_num, uint32_t level) {
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

int gpio_ll_get_level(gpio_dev_t *hw, gpio_num_t gpio_num) {
	if (gpio_num < 32) {
		return (hw->in >> gpio_num) & 0x1;
	} else {
		return (hw->in1.data >> (gpio_num - 32)) & 0x1;
	}
}

void gpio_ll_wakeup_enable(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_int_type_t intr_type) {
	hw->pin[gpio_num].int_type = intr_type;
	hw->pin[gpio_num].wakeup_enable = 0x1;
}

void gpio_ll_wakeup_disable(gpio_dev_t *hw, gpio_num_t gpio_num) {
	hw->pin[gpio_num].wakeup_enable = 0;
}

void gpio_ll_set_drive_capability(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_drive_cap_t strength) {
	SET_PERI_REG_BITS(GPIO_PIN_MUX_REG[gpio_num], FUN_DRV_V, strength, FUN_DRV_S);
}

void gpio_ll_get_drive_capability(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_drive_cap_t *strength) {
	*strength = (gpio_drive_cap_t)GET_PERI_REG_BITS2(GPIO_PIN_MUX_REG[gpio_num], FUN_DRV_V, FUN_DRV_S);
}

void gpio_ll_deep_sleep_hold_en(gpio_dev_t *hw) {
	*((volatile int*)RTC_CNTL_DIG_ISO_REG) &= ~RTC_CNTL_DG_PAD_FORCE_UNHOLD;
	*((volatile int*)RTC_CNTL_DIG_ISO_REG) |= RTC_CNTL_DG_PAD_AUTOHOLD_EN_M;
}

void gpio_ll_deep_sleep_hold_dis(gpio_dev_t *hw) {
	*((volatile int*)RTC_CNTL_DIG_ISO_REG) &= ~RTC_CNTL_DG_PAD_AUTOHOLD_EN_M;
}

bool gpio_ll_deep_sleep_hold_is_en(gpio_dev_t *hw) {
	return !GET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_UNHOLD) && GET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_AUTOHOLD_EN_M);
}

void gpio_ll_hold_en(gpio_dev_t *hw, gpio_num_t gpio_num) {
	*((volatile int*)RTC_CNTL_DIG_PAD_HOLD_REG) |= GPIO_HOLD_MASK[gpio_num];
}

void gpio_ll_hold_dis(gpio_dev_t *hw, gpio_num_t gpio_num) {
	*((volatile int*)RTC_CNTL_DIG_PAD_HOLD_REG) &= ~GPIO_HOLD_MASK[gpio_num];
}

bool gpio_ll_is_digital_io_hold(gpio_dev_t *hw, uint32_t gpio_num) {
	return GET_PERI_REG_MASK(RTC_CNTL_DIG_PAD_HOLD_REG, 1<<gpio_num - 21);
}

void gpio_ll_iomux_in(gpio_dev_t *hw, uint32_t gpio, uint32_t signal_idx) {
	hw->func_in_sel_cfg[signal_idx].sig_in_sel = 0;
	PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio]);
}

void gpio_ll_iomux_func_sel(uint32_t pin_name, uint32_t func) {
	if (pin_name == PERIPHS_IO_MUX_GPIO19_U || pin_name == PERIPHS_IO_MUX_GPIO20_U) {
		*((volatile int*)USB_SERIAL_JTAG_CONF0_REG) &= ~USB_SERIAL_JTAG_USB_PAD_ENABLE;
	}
	PIN_FUNC_SELECT(pin_name, func);
}

void gpio_ll_iomux_out(gpio_dev_t *hw, uint8_t gpio_num, int func, uint32_t oen_inv) {
	hw->func_out_sel_cfg[gpio_num].oen_sel = 0;
	hw->func_out_sel_cfg[gpio_num].oen_inv_sel = oen_inv;
	gpio_ll_iomux_func_sel(GPIO_PIN_MUX_REG[gpio_num], func);
}

void gpio_ll_force_hold_all(gpio_dev_t *hw) {
	*((volatile int*)RTC_CNTL_DIG_ISO_REG) &= ~RTC_CNTL_DG_PAD_FORCE_UNHOLD;
	*((volatile int*)RTC_CNTL_DIG_ISO_REG) |= RTC_CNTL_DG_PAD_FORCE_HOLD;
}

void gpio_ll_force_unhold_all(void) {
	*((volatile int*)RTC_CNTL_DIG_ISO_REG) &= ~RTC_CNTL_DG_PAD_FORCE_HOLD;
	*((volatile int*)RTC_CNTL_DIG_ISO_REG) |= RTC_CNTL_DG_PAD_FORCE_UNHOLD;
	*((volatile int*)RTC_CNTL_DIG_ISO_REG) |= RTC_CNTL_CLR_DG_PAD_AUTOHOLD;
}

void gpio_ll_sleep_sel_en(gpio_dev_t *hw, gpio_num_t gpio_num) {
	PIN_SLP_SEL_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

void gpio_ll_sleep_sel_dis(gpio_dev_t *hw, gpio_num_t gpio_num) {
	PIN_SLP_SEL_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

void gpio_ll_sleep_pullup_dis(gpio_dev_t *hw, gpio_num_t gpio_num) {
	PIN_SLP_PULLUP_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

void gpio_ll_sleep_pullup_en(gpio_dev_t *hw, gpio_num_t gpio_num) {
	PIN_SLP_PULLUP_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

void gpio_ll_sleep_pulldown_en(gpio_dev_t *hw, gpio_num_t gpio_num) {
	PIN_SLP_PULLDOWN_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

void gpio_ll_sleep_pulldown_dis(gpio_dev_t *hw, gpio_num_t gpio_num) {
	PIN_SLP_PULLDOWN_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

void gpio_ll_sleep_input_disable(gpio_dev_t *hw, gpio_num_t gpio_num) {
	PIN_SLP_INPUT_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

void gpio_ll_sleep_input_enable(gpio_dev_t *hw, gpio_num_t gpio_num) {
	PIN_SLP_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

void gpio_ll_sleep_output_disable(gpio_dev_t *hw, gpio_num_t gpio_num) {
	PIN_SLP_OUTPUT_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

void gpio_ll_sleep_output_enable(gpio_dev_t *hw, gpio_num_t gpio_num) {
	PIN_SLP_OUTPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

