
// The LL layer of the USB-serial-jtag controller

#include "soc/usb_serial_jtag_reg.h"
#include "soc/usb_serial_jtag_struct.h"


//The in and out endpoints are this long.
#define USB_SERIAL_JTAG_PACKET_SZ_BYTES 64

#define USB_SERIAL_JTAG_LL_INTR_MASK         (0x7ffff) //All interrupt mask

// Define USB_SERIAL_JTAG interrupts
// Note the hardware has more interrupts, but they're only useful for debugging
// the hardware.
typedef enum {
	USB_SERIAL_JTAG_INTR_SOF                    = (1 << 1),
	USB_SERIAL_JTAG_INTR_SERIAL_OUT_RECV_PKT    = (1 << 2),
	USB_SERIAL_JTAG_INTR_SERIAL_IN_EMPTY        = (1 << 3),
	USB_SERIAL_JTAG_INTR_TOKEN_REC_IN_EP1       = (1 << 8),
	USB_SERIAL_JTAG_INTR_BUS_RESET              = (1 << 9),
	USB_SERIAL_JTAG_INTR_EP1_ZERO_PAYLOAD       = (1 << 10),
} usb_serial_jtag_intr_t;

static inline void usb_serial_jtag_ll_ena_intr_mask(uint32_t mask)
{
	USB_SERIAL_JTAG.int_ena.val |= mask;
}

static inline void usb_serial_jtag_ll_disable_intr_mask(uint32_t mask)
{
	USB_SERIAL_JTAG.int_ena.val &= (~mask);
}

static inline uint32_t usb_serial_jtag_ll_get_intsts_mask(void)
{
	return USB_SERIAL_JTAG.int_st.val;
}

static inline void usb_serial_jtag_ll_clr_intsts_mask(uint32_t mask)
{
	USB_SERIAL_JTAG.int_clr.val = mask;
}

static inline uint32_t usb_serial_jtag_ll_get_intr_ena_status(void)
{
	return USB_SERIAL_JTAG.int_ena.val;
}

static inline uint32_t usb_serial_jtag_ll_read_rxfifo(uint8_t *buf, uint32_t rd_len)
{
	uint32_t i;
	for (i = 0; i < rd_len; i++) {
		if (!USB_SERIAL_JTAG.ep1_conf.serial_out_ep_data_avail) break;
		buf[i] = USB_SERIAL_JTAG.ep1.rdwr_byte;
	}
	return i;
}

static inline uint32_t usb_serial_jtag_ll_write_txfifo(const uint8_t *buf, uint32_t wr_len)
{
	uint32_t i;
	for (i = 0; i < wr_len; i++) {
		if (!USB_SERIAL_JTAG.ep1_conf.serial_in_ep_data_free) break;
		USB_SERIAL_JTAG.ep1.rdwr_byte = buf[i];
	}
	return i;
}

static inline int usb_serial_jtag_ll_rxfifo_data_available(void)
{
	return USB_SERIAL_JTAG.ep1_conf.serial_out_ep_data_avail;
}

static inline int usb_serial_jtag_ll_txfifo_writable(void)
{
	return USB_SERIAL_JTAG.ep1_conf.serial_in_ep_data_free;
}

static inline void usb_serial_jtag_ll_txfifo_flush(void)
{
	USB_SERIAL_JTAG.ep1_conf.wr_done=1;
}


