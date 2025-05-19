
#define USB_SERIAL_JTAG_PACKET_SZ_BYTES 64

#define USB_SERIAL_JTAG_LL_INTR_MASK         (0x7ffff) //All interrupt mask

typedef enum {
	USB_SERIAL_JTAG_INTR_SOF                    = (1 << 1),
	USB_SERIAL_JTAG_INTR_SERIAL_OUT_RECV_PKT    = (1 << 2),
	USB_SERIAL_JTAG_INTR_SERIAL_IN_EMPTY        = (1 << 3),
	USB_SERIAL_JTAG_INTR_TOKEN_REC_IN_EP1       = (1 << 8),
	USB_SERIAL_JTAG_INTR_BUS_RESET              = (1 << 9),
	USB_SERIAL_JTAG_INTR_EP1_ZERO_PAYLOAD       = (1 << 10),
} usb_serial_jtag_intr_t;

void usb_serial_jtag_ll_ena_intr_mask(uint32_t mask);
void usb_serial_jtag_ll_disable_intr_mask(uint32_t mask);
uint32_t usb_serial_jtag_ll_get_intsts_mask(void);
void usb_serial_jtag_ll_clr_intsts_mask(uint32_t mask);
uint32_t usb_serial_jtag_ll_get_intr_ena_status(void);
uint32_t usb_serial_jtag_ll_read_rxfifo(uint8_t *buf, uint32_t rd_len);
uint32_t usb_serial_jtag_ll_write_txfifo(const uint8_t *buf, uint32_t wr_len);
int usb_serial_jtag_ll_rxfifo_data_available(void);
int usb_serial_jtag_ll_txfifo_writable(void);
void usb_serial_jtag_ll_txfifo_flush(void);
