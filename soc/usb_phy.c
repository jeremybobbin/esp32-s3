

#include <stdbool.h>
#include "soc/usb.h"
#include "soc/usb_phy.h"


void usb_phy_ll_int_otg_enable(usb_wrap_dev_t *hw)
{
	hw->otg_conf.pad_enable = 1;
	// USB_OTG use internal PHY
	hw->otg_conf.phy_sel = 0;
	// phy_sel is controlled by the following register value
	RTCCNTL->usb_conf.sw_hw_usb_phy_sel = 1;
	// phy_sel=sw_usb_phy_sel=1, USB_OTG is connected with internal PHY
	RTCCNTL->usb_conf.sw_usb_phy_sel = 1;
}

void usb_phy_ll_ext_otg_enable(usb_wrap_dev_t *hw)
{
	// USB_OTG use external PHY
	hw->otg_conf.phy_sel = 1;
	// phy_sel is controlled by the following register value
	RTCCNTL->usb_conf.sw_hw_usb_phy_sel = 1;
	// phy_sel=sw_usb_phy_sel=0, USB_OTG is connected with external PHY through GPIO Matrix
	RTCCNTL->usb_conf.sw_usb_phy_sel = 0;
}

void usb_phy_ll_int_jtag_enable(usb_serial_jtag_dev_t *hw)
{
	// USB_Serial_JTAG use internal PHY
	hw->conf0.phy_sel = 0;
	// Disable software control USB D+ D- pullup pulldown (Device FS: dp_pullup = 1)
	hw->conf0.pad_pull_override = 0;
	// Enable USB D+ pullup
	hw->conf0.dp_pullup = 1;
	// Enable USB pad function
	hw->conf0.usb_pad_enable = 1;
	// phy_sel is controlled by the following register value
	RTCCNTL->usb_conf.sw_hw_usb_phy_sel = 1;
	// phy_sel=sw_usb_phy_sel=0, USB_Serial_JTAG is connected with internal PHY
	RTCCNTL->usb_conf.sw_usb_phy_sel = 0;
}

void usb_phy_ll_ext_jtag_enable(usb_serial_jtag_dev_t *hw)
{
	// USB_Serial_JTAG use external PHY
	hw->conf0.phy_sel = 1;
	// phy_sel is controlled by the following register value
	RTCCNTL->usb_conf.sw_hw_usb_phy_sel = 1;
	// phy_sel=sw_usb_phy_sel=1, USB_Serial_JTAG is connected with external PHY
	RTCCNTL->usb_conf.sw_usb_phy_sel = 1;
}

void usb_phy_ll_int_load_conf(usb_wrap_dev_t *hw, bool dp_pu, bool dp_pd, bool dm_pu, bool dm_pd)
{
	usb_wrap_otg_conf_reg_t conf = hw->otg_conf;
	conf.pad_pull_override = 1;
	conf.dp_pullup = dp_pu;
	conf.dp_pulldown = dp_pd;
	conf.dm_pullup = dm_pu;
	conf.dm_pulldown = dm_pd;
	hw->otg_conf = conf;
}

void usb_phy_ll_int_enable_test_mode(usb_wrap_dev_t *hw, bool en)
{
	if (en) {
		// Clear USB_WRAP_TEST_CONF_REG
		hw->test_conf.val = 0;
		// Set USB test pad oen
		hw->test_conf.test_usb_wrap_oe = 1;
		// Enable USB test mode
		hw->test_conf.test_enable = 1;
	} else {
		hw->test_conf.test_enable = 0;
	}
}

