
#pragma once
#include <stdint.h>


int chip_usb_dw_init(void);
int chip_usb_dw_did_persist(void);
void chip_usb_dw_prepare_persist(void);
uint32_t chip_usb_get_persist_flags(void);
void chip_usb_set_persist_flags(uint32_t flags);

