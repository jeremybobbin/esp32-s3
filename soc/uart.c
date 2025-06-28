#include "soc/uart.h"
#include "soc/i2c.h"
#include "soc/gpio.h"

#define SOC_UART_FIFO_LEN          (128)      /*!< The UART hardware FIFO length */

#define UART_LL_FIFO_DEF_LEN  (SOC_UART_FIFO_LEN)
#define UART_LL_GET_HW(num) (((num) == 0) ? (&UART0) : (((num) == 1) ? (&UART1) : (&UART2)))
#define UART_LL_MIN_WAKEUP_THRESH (2)
#define UART_LL_INTR_MASK         (0x7ffff)
#define UART_LL_FSM_IDLE          (0x0)
#define UART_LL_FSM_TX_WAIT_SEND  (0xf)

void uart_ll_set_reset_core(uart_dev_t *hw, bool core_rst_en) {
	hw->clk_conf.rst_core = core_rst_en;
}

void uart_ll_set_sclk(uart_dev_t *hw, uart_sclk_t source_clk) {
	switch (source_clk) {
		default:
		case UART_SCLK_APB:
			hw->clk_conf.sclk_sel = 1;
			break;
		case UART_SCLK_RTC:
			hw->clk_conf.sclk_sel = 2;
			break;
		case UART_SCLK_XTAL:
			hw->clk_conf.sclk_sel = 3;
			break;
	}
}

void uart_ll_get_sclk(uart_dev_t *hw, uart_sclk_t *source_clk)
{
	switch (hw->clk_conf.sclk_sel) {
		default:
		case 1:
			*source_clk = UART_SCLK_APB;
			break;
		case 2:
			*source_clk = UART_SCLK_RTC;
			break;
		case 3:
			*source_clk = UART_SCLK_XTAL;
			break;
	}
}

uint32_t uart_ll_get_sclk_freq(uart_dev_t *hw)
{
	switch (hw->clk_conf.sclk_sel) {
		default:
		case 1:
			return APB_CLK_FREQ;
		case 2:
			return RTC_CLK_FREQ;
		case 3:
			return XTAL_CLK_FREQ;
	}
}

void uart_ll_set_baudrate(uart_dev_t *hw, uint32_t baud)
{
#define DIV_UP(a, b)    (((a) + (b) - 1) / (b))
	uint32_t sclk_freq = uart_ll_get_sclk_freq(hw);
	const uint32_t max_div = (1<<(12)) - 1;   // UART divider integer part only has 12 bits
	int sclk_div = DIV_UP(sclk_freq, max_div * baud);

	uint32_t clk_div = ((sclk_freq) << 4) / (baud * sclk_div);
	// The baud rate configuration register is divided into
	// an integer part and a fractional part.
	hw->clkdiv.clkdiv = clk_div >> 4;
	hw->clkdiv.clkdiv_frag = clk_div &  0xf;
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->clk_conf, sclk_div_num, sclk_div - 1);
#undef DIV_UP
}

uint32_t uart_ll_get_baudrate(uart_dev_t *hw)
{
	uint32_t sclk_freq = uart_ll_get_sclk_freq(hw);
	uart_clkdiv_reg_t div_reg = hw->clkdiv;
	return ((sclk_freq << 4)) /
		(((div_reg.clkdiv << 4) | div_reg.clkdiv_frag) * (HAL_FORCE_READ_U32_REG_FIELD(hw->clk_conf, sclk_div_num) + 1));
}

void uart_ll_ena_intr_mask(uart_dev_t *hw, uint32_t mask)
{
	hw->int_ena.val |= mask;
}

void uart_ll_disable_intr_mask(uart_dev_t *hw, uint32_t mask)
{
	hw->int_ena.val &= (~mask);
}

uint32_t uart_ll_get_intsts_mask(uart_dev_t *hw)
{
	return hw->int_st.val;
}

void uart_ll_clr_intsts_mask(uart_dev_t *hw, uint32_t mask)
{
	hw->int_clr.val = mask;
}

uint32_t uart_ll_get_intr_ena_status(uart_dev_t *hw)
{
	return hw->int_ena.val;
}

void uart_ll_read_rxfifo(uart_dev_t *hw, uint8_t *buf, uint32_t rd_len)
{
	for (int i = 0; i < (int)rd_len; i++) {
		buf[i] = hw->fifo.rxfifo_rd_byte;
	}
}

void uart_ll_write_txfifo(uart_dev_t *hw, const uint8_t *buf, uint32_t wr_len)
{
	for (int i = 0; i < (int)wr_len; i++) {
		hw->fifo.rxfifo_rd_byte = buf[i];
	}
}

void uart_ll_rxfifo_rst(uart_dev_t *hw)
{
	hw->conf0.rxfifo_rst = 1;
	hw->conf0.rxfifo_rst = 0;
}

void uart_ll_txfifo_rst(uart_dev_t *hw)
{
	hw->conf0.txfifo_rst = 1;
	hw->conf0.txfifo_rst = 0;
}

uint32_t uart_ll_get_rxfifo_len(uart_dev_t *hw)
{
	return hw->status.rxfifo_cnt;
}

uint32_t uart_ll_get_txfifo_len(uart_dev_t *hw)
{
	return UART_LL_FIFO_DEF_LEN - hw->status.txfifo_cnt;
}

void uart_ll_set_stop_bits(uart_dev_t *hw, uart_stop_bits_t stop_bit)
{
	hw->conf0.stop_bit_num = stop_bit;
}

void uart_ll_get_stop_bits(uart_dev_t *hw, uart_stop_bits_t *stop_bit)
{
	*stop_bit = (uart_stop_bits_t)hw->conf0.stop_bit_num;
}

void uart_ll_set_parity(uart_dev_t *hw, uart_parity_t parity_mode)
{
	if (parity_mode != UART_PARITY_DISABLE) {
		hw->conf0.parity = parity_mode & 0x1;
	}
	hw->conf0.parity_en = (parity_mode >> 1) & 0x1;
}

void uart_ll_get_parity(uart_dev_t *hw, uart_parity_t *parity_mode)
{
	if (hw->conf0.parity_en) {
		*parity_mode = (uart_parity_t)(0x2 | hw->conf0.parity);
	} else {
		*parity_mode = UART_PARITY_DISABLE;
	}
}

void uart_ll_set_rxfifo_full_thr(uart_dev_t *hw, uint16_t full_thrhd)
{
	hw->conf1.rxfifo_full_thrhd = full_thrhd;
}

void uart_ll_set_txfifo_empty_thr(uart_dev_t *hw, uint16_t empty_thrhd)
{
	hw->conf1.txfifo_empty_thrhd = empty_thrhd;
}

void uart_ll_set_rx_idle_thr(uart_dev_t *hw, uint32_t rx_idle_thr)
{
	hw->idle_conf.rx_idle_thrhd = rx_idle_thr;
}

void uart_ll_set_tx_idle_num(uart_dev_t *hw, uint32_t idle_num)
{
	hw->idle_conf.tx_idle_num = idle_num;
}

void uart_ll_tx_break(uart_dev_t *hw, uint32_t break_num)
{
	if (break_num > 0) {
		HAL_FORCE_MODIFY_U32_REG_FIELD(hw->txbrk_conf, tx_brk_num, break_num);
		hw->conf0.txd_brk = 1;
	} else {
		hw->conf0.txd_brk = 0;
	}
}
void uart_ll_set_hw_flow_ctrl(uart_dev_t *hw, uart_hw_flowcontrol_t flow_ctrl, uint32_t rx_thrs)
{
	//only when UART_HW_FLOWCTRL_RTS is set , will the rx_thresh value be set.
	if (flow_ctrl & UART_HW_FLOWCTRL_RTS) {
		hw->mem_conf.rx_flow_thrhd = rx_thrs;
		hw->conf1.rx_flow_en = 1;
	} else {
		hw->conf1.rx_flow_en = 0;
	}
	if (flow_ctrl & UART_HW_FLOWCTRL_CTS) {
		hw->conf0.tx_flow_en = 1;
	} else {
		hw->conf0.tx_flow_en = 0;
	}
}

void uart_ll_get_hw_flow_ctrl(uart_dev_t *hw, uart_hw_flowcontrol_t *flow_ctrl)
{
	*flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
	if (hw->conf1.rx_flow_en) {
		*flow_ctrl = (uart_hw_flowcontrol_t)((unsigned int)(*flow_ctrl) | (unsigned int)UART_HW_FLOWCTRL_RTS);
	}
	if (hw->conf0.tx_flow_en) {
		*flow_ctrl = (uart_hw_flowcontrol_t)((unsigned int)(*flow_ctrl) | (unsigned int)UART_HW_FLOWCTRL_CTS);
	}
}

void uart_ll_set_sw_flow_ctrl(uart_dev_t *hw, uart_sw_flowctrl_t *flow_ctrl, bool sw_flow_ctrl_en)
{
	if (sw_flow_ctrl_en) {
		hw->flow_conf.xonoff_del = 1;
		hw->flow_conf.sw_flow_con_en = 1;
		hw->swfc_conf1.xon_threshold = flow_ctrl->xon_thrd;
		hw->swfc_conf0.xoff_threshold = flow_ctrl->xoff_thrd;
		HAL_FORCE_MODIFY_U32_REG_FIELD(hw->swfc_conf1, xon_char, flow_ctrl->xon_char);
		HAL_FORCE_MODIFY_U32_REG_FIELD(hw->swfc_conf0, xoff_char, flow_ctrl->xoff_char);
	} else {
		hw->flow_conf.sw_flow_con_en = 0;
		hw->flow_conf.xonoff_del = 0;
	}
}

void uart_ll_set_at_cmd_char(uart_dev_t *hw, uart_at_cmd_t *cmd_char)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->at_cmd_char, at_cmd_char, cmd_char->cmd_char);
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->at_cmd_char, char_num, cmd_char->char_num);
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->at_cmd_postcnt, post_idle_num, cmd_char->post_idle);
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->at_cmd_precnt, pre_idle_num, cmd_char->pre_idle);
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->at_cmd_gaptout, rx_gap_tout, cmd_char->gap_tout);
}

void uart_ll_set_data_bit_num(uart_dev_t *hw, uart_word_length_t data_bit)
{
	hw->conf0.bit_num = data_bit;
}

void uart_ll_set_rts_active_level(uart_dev_t *hw, int level)
{
	hw->conf0.sw_rts = level & 0x1;
}

void uart_ll_set_dtr_active_level(uart_dev_t *hw, int level)
{
	hw->conf0.sw_dtr = level & 0x1;
}

void uart_ll_set_wakeup_thrd(uart_dev_t *hw, uint32_t wakeup_thrd)
{
	hw->sleep_conf.active_threshold = wakeup_thrd - UART_LL_MIN_WAKEUP_THRESH;
}

void uart_ll_set_mode_normal(uart_dev_t *hw)
{
	hw->rs485_conf.rs485_en = 0;
	hw->rs485_conf.rs485tx_rx_en= 0;
	hw->rs485_conf.rs485rxby_tx_en = 0;
	hw->conf0.irda_en = 0;
}

void uart_ll_set_mode_rs485_app_ctrl(uart_dev_t *hw)
{
	// Application software control, remove echo
	hw->rs485_conf.rs485rxby_tx_en = 1;
	hw->conf0.irda_en = 0;
	hw->conf0.sw_rts = 0;
	hw->conf0.irda_en = 0;
	hw->rs485_conf.rs485_en = 1;
}

void uart_ll_set_mode_rs485_half_duplex(uart_dev_t *hw)
{
	// Enable receiver, sw_rts = 1  generates low level on RTS pin
	hw->conf0.sw_rts = 1;
	// Must be set to 0 to automatically remove echo
	hw->rs485_conf.rs485tx_rx_en = 0;
	// This is to void collision
	hw->rs485_conf.rs485rxby_tx_en = 1;
	hw->conf0.irda_en = 0;
	hw->rs485_conf.rs485_en= 1;
}

void uart_ll_set_mode_collision_detect(uart_dev_t *hw)
{
	hw->conf0.irda_en = 0;
	// Transmitters output signal loop back to the receivers input signal
	hw->rs485_conf.rs485tx_rx_en = 1 ;
	// Transmitter should send data when the receiver is busy
	hw->rs485_conf.rs485rxby_tx_en = 1;
	hw->conf0.sw_rts = 0;
	hw->rs485_conf.rs485_en = 1;
}

void uart_ll_set_mode_irda(uart_dev_t *hw)
{
	hw->rs485_conf.rs485_en = 0;
	hw->rs485_conf.rs485tx_rx_en = 0;
	hw->rs485_conf.rs485rxby_tx_en = 0;
	hw->conf0.sw_rts = 0;
	hw->conf0.irda_en = 1;
}

void uart_ll_set_mode(uart_dev_t *hw, uart_mode_t mode)
{
	switch (mode) {
	default:
	case UART_MODE_UART:
		uart_ll_set_mode_normal(hw);
		break;
	case UART_MODE_RS485_COLLISION_DETECT:
		uart_ll_set_mode_collision_detect(hw);
		break;
	case UART_MODE_RS485_APP_CTRL:
		uart_ll_set_mode_rs485_app_ctrl(hw);
		break;
	case UART_MODE_RS485_HALF_DUPLEX:
		uart_ll_set_mode_rs485_half_duplex(hw);
		break;
	case UART_MODE_IRDA:
		uart_ll_set_mode_irda(hw);
		break;
	}
}

void uart_ll_get_at_cmd_char(uart_dev_t *hw, uint8_t *cmd_char, uint8_t *char_num)
{
	*cmd_char = HAL_FORCE_READ_U32_REG_FIELD(hw->at_cmd_char, at_cmd_char);
	*char_num = HAL_FORCE_READ_U32_REG_FIELD(hw->at_cmd_char, char_num);
}

uint32_t uart_ll_get_wakeup_thrd(uart_dev_t *hw)
{
	return hw->sleep_conf.active_threshold + UART_LL_MIN_WAKEUP_THRESH;
}

void uart_ll_get_data_bit_num(uart_dev_t *hw, uart_word_length_t *data_bit)
{
	*data_bit = (uart_word_length_t)hw->conf0.bit_num;
}

bool uart_ll_is_tx_idle(uart_dev_t *hw)
{
	return ((hw->status.txfifo_cnt == 0) && (hw->fsm_status.st_utx_out == 0));
}

bool uart_ll_is_hw_rts_en(uart_dev_t *hw)
{
	return hw->conf1.rx_flow_en;
}

bool uart_ll_is_hw_cts_en(uart_dev_t *hw)
{
	return hw->conf0.tx_flow_en;
}

void uart_ll_set_loop_back(uart_dev_t *hw, bool loop_back_en)
{
	hw->conf0.loopback = loop_back_en;
}

void uart_ll_inverse_signal(uart_dev_t *hw, uint32_t inv_mask)
{
	uart_conf0_reg_t conf0_reg = hw->conf0;
	conf0_reg.irda_tx_inv = (inv_mask & UART_SIGNAL_IRDA_TX_INV) ? 1 : 0;
	conf0_reg.irda_rx_inv = (inv_mask & UART_SIGNAL_IRDA_RX_INV) ? 1 : 0;
	conf0_reg.rxd_inv = (inv_mask & UART_SIGNAL_RXD_INV) ? 1 : 0;
	conf0_reg.cts_inv = (inv_mask & UART_SIGNAL_CTS_INV) ? 1 : 0;
	conf0_reg.dsr_inv = (inv_mask & UART_SIGNAL_DSR_INV) ? 1 : 0;
	conf0_reg.txd_inv = (inv_mask & UART_SIGNAL_TXD_INV) ? 1 : 0;
	conf0_reg.rts_inv = (inv_mask & UART_SIGNAL_RTS_INV) ? 1 : 0;
	conf0_reg.dtr_inv = (inv_mask & UART_SIGNAL_DTR_INV) ? 1 : 0;
	hw->conf0.val = conf0_reg.val;
}

void uart_ll_set_rx_tout(uart_dev_t *hw, uint16_t tout_thrd)
{
	uint16_t tout_val = tout_thrd;
	if(tout_thrd > 0) {
		hw->mem_conf.rx_tout_thrhd = tout_val;
		hw->conf1.rx_tout_en = 1;
	} else {
		hw->conf1.rx_tout_en = 0;
	}
}

uint16_t uart_ll_get_rx_tout_thr(uart_dev_t *hw)
{
	uint16_t tout_thrd = 0;
	if(hw->conf1.rx_tout_en > 0) {
		tout_thrd = hw->mem_conf.rx_tout_thrhd;
	}
	return tout_thrd;
}

uint16_t uart_ll_max_tout_thrd(uart_dev_t *hw)
{
	return UART_RX_TOUT_THRHD_V;
}

void uart_ll_set_autobaud_en(uart_dev_t *hw, bool enable)
{
	hw->conf0.autobaud_en = enable ? 1 : 0;
}

uint32_t uart_ll_get_rxd_edge_cnt(uart_dev_t *hw)
{
	return hw->rxd_cnt.rxd_edge_cnt;
}

uint32_t uart_ll_get_pos_pulse_cnt(uart_dev_t *hw)
{
	return hw->pospulse.posedge_min_cnt;
}

uint32_t uart_ll_get_neg_pulse_cnt(uart_dev_t *hw)
{
	return hw->negpulse.negedge_min_cnt;
}

uint32_t uart_ll_get_high_pulse_cnt(uart_dev_t *hw)
{
	return hw->highpulse.highpulse_min_cnt;
}

uint32_t uart_ll_get_low_pulse_cnt(uart_dev_t *hw)
{
	return hw->lowpulse.lowpulse_min_cnt;
}

void uart_ll_force_xoff(uart_port_t uart_num)
{
	REG_CLR_BIT(UART_FLOW_CONF_REG(uart_num), UART_FORCE_XON);
	REG_SET_BIT(UART_FLOW_CONF_REG(uart_num), UART_SW_FLOW_CON_EN | UART_FORCE_XOFF);
}

void uart_ll_force_xon(uart_port_t uart_num)
{
	REG_CLR_BIT(UART_FLOW_CONF_REG(uart_num), UART_FORCE_XOFF);
	REG_SET_BIT(UART_FLOW_CONF_REG(uart_num), UART_FORCE_XON);
	REG_CLR_BIT(UART_FLOW_CONF_REG(uart_num), UART_SW_FLOW_CON_EN | UART_FORCE_XON);
}

uint32_t uart_ll_get_fsm_status(uart_port_t uart_num)
{
	return REG_GET_FIELD(UART_FSM_STATUS_REG(uart_num), UART_ST_UTX_OUT);
}

