
#pragma once

#include <stdint.h>
#include <stdbool.h>


#define USB_DESCRIPTOR_TYPE_ACM 0
#define USB_DESCRIPTOR_TYPE_DFU 1

void usb_set_current_descriptor(int descriptor_type);

bool usb_get_descriptor(uint16_t type_index, uint16_t lang_id,
                        int32_t *len, uint8_t **data);

