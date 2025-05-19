#include "hal/misc.h"
#include "hal/uart_types.h"
#include "soc/uart_periph.h"
#include "soc/uart_struct.h"
#include "esp_attr.h"

#define UART_LL_FIFO_DEF_LEN  (SOC_UART_FIFO_LEN)
#define UART_LL_GET_HW(num) (((num) == 0) ? (&UART0) : (((num) == 1) ? (&UART1) : (&UART2)))

#define UART_LL_MIN_WAKEUP_THRESH (2)
#define UART_LL_INTR_MASK         (0x7ffff) //All interrupt mask

#define UART_LL_FSM_IDLE          (0x0)
#define UART_LL_FSM_TX_WAIT_SEND  (0xf)

typedef enum {
	UART_INTR_RXFIFO_FULL      = (0x1 << 0),
	UART_INTR_TXFIFO_EMPTY     = (0x1 << 1),
	UART_INTR_PARITY_ERR       = (0x1 << 2),
	UART_INTR_FRAM_ERR         = (0x1 << 3),
	UART_INTR_RXFIFO_OVF       = (0x1 << 4),
	UART_INTR_DSR_CHG          = (0x1 << 5),
	UART_INTR_CTS_CHG          = (0x1 << 6),
	UART_INTR_BRK_DET          = (0x1 << 7),
	UART_INTR_RXFIFO_TOUT      = (0x1 << 8),
	UART_INTR_SW_XON           = (0x1 << 9),
	UART_INTR_SW_XOFF          = (0x1 << 10),
	UART_INTR_GLITCH_DET       = (0x1 << 11),
	UART_INTR_TX_BRK_DONE      = (0x1 << 12),
	UART_INTR_TX_BRK_IDLE      = (0x1 << 13),
	UART_INTR_TX_DONE          = (0x1 << 14),
	UART_INTR_RS485_PARITY_ERR = (0x1 << 15),
	UART_INTR_RS485_FRM_ERR    = (0x1 << 16),
	UART_INTR_RS485_CLASH      = (0x1 << 17),
	UART_INTR_CMD_CHAR_DET     = (0x1 << 18),
} uart_intr_t;

void uart_ll_set_reset_core(uart_dev_t *hw, bool core_rst_en);
void uart_ll_set_sclk(uart_dev_t *hw, uart_sclk_t source_clk);
void uart_ll_get_sclk(uart_dev_t *hw, uart_sclk_t *source_clk);
uint32_t uart_ll_get_sclk_freq(uart_dev_t *hw);
void uart_ll_set_baudrate(uart_dev_t *hw, uint32_t baud);
uint32_t uart_ll_get_baudrate(uart_dev_t *hw);
void uart_ll_ena_intr_mask(uart_dev_t *hw, uint32_t mask);
void uart_ll_disable_intr_mask(uart_dev_t *hw, uint32_t mask);
uint32_t uart_ll_get_intsts_mask(uart_dev_t *hw);
void uart_ll_clr_intsts_mask(uart_dev_t *hw, uint32_t mask);
uint32_t uart_ll_get_intr_ena_status(uart_dev_t *hw);
void uart_ll_read_rxfifo(uart_dev_t *hw, uint8_t *buf, uint32_t rd_len);
void uart_ll_write_txfifo(uart_dev_t *hw, const uint8_t *buf, uint32_t wr_len);
void uart_ll_rxfifo_rst(uart_dev_t *hw);
void uart_ll_txfifo_rst(uart_dev_t *hw);
uint32_t uart_ll_get_rxfifo_len(uart_dev_t *hw);
uint32_t uart_ll_get_txfifo_len(uart_dev_t *hw);
void uart_ll_set_stop_bits(uart_dev_t *hw, uart_stop_bits_t stop_bit);
void uart_ll_get_stop_bits(uart_dev_t *hw, uart_stop_bits_t *stop_bit);
void uart_ll_set_parity(uart_dev_t *hw, uart_parity_t parity_mode);
void uart_ll_get_parity(uart_dev_t *hw, uart_parity_t *parity_mode);
void uart_ll_set_rxfifo_full_thr(uart_dev_t *hw, uint16_t full_thrhd);
void uart_ll_set_txfifo_empty_thr(uart_dev_t *hw, uint16_t empty_thrhd);
void uart_ll_set_rx_idle_thr(uart_dev_t *hw, uint32_t rx_idle_thr);
void uart_ll_set_tx_idle_num(uart_dev_t *hw, uint32_t idle_num);
void uart_ll_tx_break(uart_dev_t *hw, uint32_t break_num);
void uart_ll_set_hw_flow_ctrl(uart_dev_t *hw, uart_hw_flowcontrol_t flow_ctrl, uint32_t rx_thrs);
void uart_ll_get_hw_flow_ctrl(uart_dev_t *hw, uart_hw_flowcontrol_t *flow_ctrl);
void uart_ll_set_sw_flow_ctrl(uart_dev_t *hw, uart_sw_flowctrl_t *flow_ctrl, bool sw_flow_ctrl_en);
void uart_ll_set_at_cmd_char(uart_dev_t *hw, uart_at_cmd_t *cmd_char);
void uart_ll_set_data_bit_num(uart_dev_t *hw, uart_word_length_t data_bit);
void uart_ll_get_sclk(uart_dev_t *hw, uart_sclk_t *source_clk);
void uart_ll_set_rts_active_level(uart_dev_t *hw, int level);
void uart_ll_set_dtr_active_level(uart_dev_t *hw, int level);
void uart_ll_set_wakeup_thrd(uart_dev_t *hw, uint32_t wakeup_thrd);
void uart_ll_set_mode_normal(uart_dev_t *hw);
void uart_ll_set_mode_rs485_app_ctrl(uart_dev_t *hw);
void uart_ll_set_mode_rs485_half_duplex(uart_dev_t *hw);
void uart_ll_set_mode_collision_detect(uart_dev_t *hw);
void uart_ll_set_mode_irda(uart_dev_t *hw);
void uart_ll_set_mode(uart_dev_t *hw, uart_mode_t mode);
void uart_ll_get_at_cmd_char(uart_dev_t *hw, uint8_t *cmd_char, uint8_t *char_num);
uint32_t uart_ll_get_wakeup_thrd(uart_dev_t *hw);
void uart_ll_get_data_bit_num(uart_dev_t *hw, uart_word_length_t *data_bit);
bool uart_ll_is_tx_idle(uart_dev_t *hw);
bool uart_ll_is_hw_rts_en(uart_dev_t *hw);
bool uart_ll_is_hw_cts_en(uart_dev_t *hw);
void uart_ll_set_loop_back(uart_dev_t *hw, bool loop_back_en);
void uart_ll_inverse_signal(uart_dev_t *hw, uint32_t inv_mask);
void uart_ll_set_rx_tout(uart_dev_t *hw, uint16_t tout_thrd);
uint16_t uart_ll_get_rx_tout_thr(uart_dev_t *hw);
uint16_t uart_ll_max_tout_thrd(uart_dev_t *hw);
void uart_ll_set_autobaud_en(uart_dev_t *hw, bool enable);
uint32_t uart_ll_get_rxd_edge_cnt(uart_dev_t *hw);
uint32_t uart_ll_get_pos_pulse_cnt(uart_dev_t *hw);
uint32_t uart_ll_get_neg_pulse_cnt(uart_dev_t *hw);
uint32_t uart_ll_get_high_pulse_cnt(uart_dev_t *hw);
uint32_t uart_ll_get_low_pulse_cnt(uart_dev_t *hw);
void uart_ll_force_xoff(uart_port_t uart_num);
void uart_ll_force_xon(uart_port_t uart_num);
uint32_t uart_ll_get_fsm_status(uart_port_t uart_num);
