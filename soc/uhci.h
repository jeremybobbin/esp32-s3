#include <stdio.h>

#define UHCI_LL_GET_HW(num) (((num) == 0) ? (&UHCI0) : (NULL))

typedef enum {
	UHCI_RX_BREAK_CHR_EOF = 0x1,
	UHCI_RX_IDLE_EOF      = 0x2,
	UHCI_RX_LEN_EOF       = 0x4,
	UHCI_RX_EOF_MAX       = 0x7,
} uhci_rxeof_cfg_t;

void uhci_ll_init(uhci_dev_t *hw);
void uhci_ll_attach_uart_port(uhci_dev_t *hw, int uart_num);
void uhci_ll_set_seper_chr(uhci_dev_t *hw, uhci_seper_chr_t *seper_char);
void uhci_ll_get_seper_chr(uhci_dev_t *hw, uhci_seper_chr_t *seper_chr);
void uhci_ll_set_swflow_ctrl_sub_chr(uhci_dev_t *hw, uhci_swflow_ctrl_sub_chr_t *sub_ctr);
void uhci_ll_enable_intr(uhci_dev_t *hw, uint32_t intr_mask);
void uhci_ll_disable_intr(uhci_dev_t *hw, uint32_t intr_mask);
void uhci_ll_clear_intr(uhci_dev_t *hw, uint32_t intr_mask);
uint32_t uhci_ll_get_intr(uhci_dev_t *hw);
void uhci_ll_set_eof_mode(uhci_dev_t *hw, uint32_t eof_mode);
