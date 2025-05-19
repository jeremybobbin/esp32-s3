#include "soc/soc.h"
#include "soc/system_reg.h"
#include "soc/gpio_sig_map.h"
#include "soc/usb_periph.h"
#include "soc/rtc_cntl_struct.h"

void usb_ll_int_phy_enable(void);
void usb_ll_ext_phy_enable(void);
void usb_ll_int_phy_pullup_conf(bool dp_pu, bool dp_pd, bool dm_pu, bool dm_pd);
