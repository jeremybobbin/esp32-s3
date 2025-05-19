#include <stdbool.h>

void usb_phy_ll_int_otg_enable(usb_wrap_dev_t *hw);
void usb_phy_ll_ext_otg_enable(usb_wrap_dev_t *hw);
void usb_phy_ll_int_jtag_enable(usb_serial_jtag_dev_t *hw);
void usb_phy_ll_ext_jtag_enable(usb_serial_jtag_dev_t *hw);
void usb_phy_ll_int_load_conf(usb_wrap_dev_t *hw, bool dp_pu, bool dp_pd, bool dm_pu, bool dm_pd);
void usb_phy_ll_int_enable_test_mode(usb_wrap_dev_t *hw, bool en);
