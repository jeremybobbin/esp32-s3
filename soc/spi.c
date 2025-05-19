

// The LL layer for ESP32-S3 SPI register operations


#include <stdlib.h> //for abs()
#include <string.h>


/// Interrupt not used. Don't use in app.
#define SPI_LL_UNUSED_INT_MASK  (SPI_TRANS_DONE_INT_ENA | SPI_SLV_WR_DMA_DONE_INT_ENA | SPI_SLV_RD_DMA_DONE_INT_ENA | SPI_SLV_WR_BUF_DONE_INT_ENA | SPI_SLV_RD_BUF_DONE_INT_ENA)
/// These 2 masks together will set SPI transaction to one line mode
#define SPI_LL_ONE_LINE_CTRL_MASK (SPI_FREAD_OCT | SPI_FREAD_QUAD | SPI_FREAD_DUAL | SPI_FCMD_OCT | \
		SPI_FCMD_QUAD | SPI_FCMD_DUAL | SPI_FADDR_OCT | SPI_FADDR_QUAD | SPI_FADDR_DUAL)
#define SPI_LL_ONE_LINE_USER_MASK (SPI_FWRITE_OCT | SPI_FWRITE_QUAD | SPI_FWRITE_DUAL)

/// Swap the bit order to its correct place to send
#define HAL_SPI_SWAP_DATA_TX(data, len) HAL_SWAP32((uint32_t)(data) << (32 - len))
/// This is the expected clock frequency
#define SPI_LL_PERIPH_CLK_FREQ (80 * 1000000)
#define SPI_LL_GET_HW(ID) ((ID)==0? ({abort();NULL;}):((ID)==1? &GPSPI2 : &GPSPI3))

#define SPI_LL_DATA_MAX_BIT_LEN (1 << 18)

typedef uint32_t spi_ll_clock_val_t;
typedef spi_dev_t spi_dma_dev_t;

// Type definition of all supported interrupts
typedef enum {
	SPI_LL_INTR_TRANS_DONE =    BIT(0),     ///< A transaction has done
	SPI_LL_INTR_RDBUF =         BIT(6),     ///< Has received RDBUF command. Only available in slave HD.
	SPI_LL_INTR_WRBUF =         BIT(7),     ///< Has received WRBUF command. Only available in slave HD.
	SPI_LL_INTR_RDDMA =         BIT(8),     ///< Has received RDDMA command. Only available in slave HD.
	SPI_LL_INTR_WRDMA =         BIT(9),     ///< Has received WRDMA command. Only available in slave HD.
	SPI_LL_INTR_CMD7 =          BIT(10),    ///< Has received CMD7 command. Only available in slave HD.
	SPI_LL_INTR_CMD8 =          BIT(11),    ///< Has received CMD8 command. Only available in slave HD.
	SPI_LL_INTR_CMD9 =          BIT(12),    ///< Has received CMD9 command. Only available in slave HD.
	SPI_LL_INTR_CMDA =          BIT(13),    ///< Has received CMDA command. Only available in slave HD.
	SPI_LL_INTR_SEG_DONE =      BIT(14),
} spi_ll_intr_t;
FLAG_ATTR(spi_ll_intr_t)

// Flags for conditions under which the transaction length should be recorded
typedef enum {
	SPI_LL_TRANS_LEN_COND_WRBUF =   BIT(0), ///< WRBUF length will be recorded
	SPI_LL_TRANS_LEN_COND_RDBUF =   BIT(1), ///< RDBUF length will be recorded
	SPI_LL_TRANS_LEN_COND_WRDMA =   BIT(2), ///< WRDMA length will be recorded
	SPI_LL_TRANS_LEN_COND_RDDMA =   BIT(3), ///< RDDMA length will be recorded
} spi_ll_trans_len_cond_t;
FLAG_ATTR(spi_ll_trans_len_cond_t)

// SPI base command in esp32s3
typedef enum {
	 /* Slave HD Only */
	SPI_LL_BASE_CMD_HD_WRBUF    = 0x01,
	SPI_LL_BASE_CMD_HD_RDBUF    = 0x02,
	SPI_LL_BASE_CMD_HD_WRDMA    = 0x03,
	SPI_LL_BASE_CMD_HD_RDDMA    = 0x04,
	SPI_LL_BASE_CMD_HD_SEG_END  = 0x05,
	SPI_LL_BASE_CMD_HD_EN_QPI   = 0x06,
	SPI_LL_BASE_CMD_HD_WR_END   = 0x07,
	SPI_LL_BASE_CMD_HD_INT0     = 0x08,
	SPI_LL_BASE_CMD_HD_INT1     = 0x09,
	SPI_LL_BASE_CMD_HD_INT2     = 0x0A,
} spi_ll_base_command_t;

void spi_ll_master_init(spi_dev_t *hw)
{
	//Reset timing
	hw->user1.cs_setup_time = 0;
	hw->user1.cs_hold_time = 0;

	//use all 64 bytes of the buffer
	hw->user.usr_miso_highpart = 0;
	hw->user.usr_mosi_highpart = 0;

	//Disable unneeded ints
	hw->slave.val = 0;
	hw->user.val = 0;

	hw->clk_gate.clk_en = 1;
	hw->clk_gate.mst_clk_active = 1;
	hw->clk_gate.mst_clk_sel = 1;

	hw->dma_conf.val = 0;
	hw->dma_conf.tx_seg_trans_clr_en = 1;
	hw->dma_conf.rx_seg_trans_clr_en = 1;
	hw->dma_conf.dma_seg_trans_en = 0;
}

void spi_ll_slave_init(spi_dev_t *hw)
{
	//Configure slave
	hw->clock.val = 0;
	hw->user.val = 0;
	hw->ctrl.val = 0;
	hw->user.doutdin = 1; //we only support full duplex
	hw->user.sio = 0;
	hw->slave.slave_mode = 1;
	hw->slave.soft_reset = 1;
	hw->slave.soft_reset = 0;
	//use all 64 bytes of the buffer
	hw->user.usr_miso_highpart = 0;
	hw->user.usr_mosi_highpart = 0;

	// Configure DMA In-Link to not be terminated when transaction bit counter exceeds
	hw->dma_conf.rx_eof_en = 0;
	hw->dma_conf.dma_seg_trans_en = 0;

	//Disable unneeded ints
	hw->dma_int_ena.val &= ~SPI_LL_UNUSED_INT_MASK;
}

void spi_ll_slave_hd_init(spi_dev_t *hw)
{
	hw->clock.val = 0;
	hw->user.val = 0;
	hw->ctrl.val = 0;
	hw->user.doutdin = 0;
	hw->user.sio = 0;

	hw->slave.soft_reset = 1;
	hw->slave.soft_reset = 0;
	hw->slave.slave_mode = 1;
}

bool spi_ll_usr_is_done(spi_dev_t *hw)
{
	return hw->dma_int_raw.trans_done;
}

void spi_ll_master_user_start(spi_dev_t *hw)
{
	hw->cmd.update = 1;
	while (hw->cmd.update);
	hw->cmd.usr = 1;
}

void spi_ll_slave_user_start(spi_dev_t *hw)
{
	hw->cmd.usr = 1;
}

uint32_t spi_ll_get_running_cmd(spi_dev_t *hw)
{
	return hw->cmd.val;
}

void spi_ll_slave_reset(spi_dev_t *hw)
{
	hw->slave.soft_reset = 1;
	hw->slave.soft_reset = 0;
}

void spi_ll_cpu_tx_fifo_reset(spi_dev_t *hw)
{
	hw->dma_conf.buf_afifo_rst = 1;
	hw->dma_conf.buf_afifo_rst = 0;
}

void spi_ll_cpu_rx_fifo_reset(spi_dev_t *hw)
{
	hw->dma_conf.rx_afifo_rst = 1;
	hw->dma_conf.rx_afifo_rst = 0;
}

void spi_ll_dma_tx_fifo_reset(spi_dev_t *hw)
{
	hw->dma_conf.dma_afifo_rst = 1;
	hw->dma_conf.dma_afifo_rst = 0;
}

void spi_ll_dma_rx_fifo_reset(spi_dev_t *hw)
{
	hw->dma_conf.rx_afifo_rst = 1;
	hw->dma_conf.rx_afifo_rst = 0;
}

void spi_ll_infifo_full_clr(spi_dev_t *hw)
{
	hw->dma_int_clr.infifo_full_err = 1;
}

void spi_ll_outfifo_empty_clr(spi_dev_t *hw)
{
	hw->dma_int_clr.outfifo_empty_err = 1;
}

void spi_ll_dma_rx_enable(spi_dev_t *hw, bool enable)
{
	hw->dma_conf.dma_rx_ena = enable;
}

void spi_ll_dma_tx_enable(spi_dev_t *hw, bool enable)
{
	hw->dma_conf.dma_tx_ena = enable;
}

void spi_ll_dma_set_rx_eof_generation(spi_dev_t *hw, bool enable)
{
	hw->dma_conf.rx_eof_en = enable;
}

void spi_ll_write_buffer(spi_dev_t *hw, const uint8_t *buffer_to_send, size_t bitlen)
{
	for (size_t x = 0; x < bitlen; x += 32) {
		//Use memcpy to get around alignment issues for txdata
		uint32_t word;
		memcpy(&word, &buffer_to_send[x / 8], 4);
		hw->data_buf[(x / 32)] = word;
	}
}

void spi_ll_write_buffer_byte(spi_dev_t *hw, int byte_id, uint8_t *data, int len)
{
	HAL_ASSERT(byte_id + len <= 64);
	HAL_ASSERT(len > 0);
	HAL_ASSERT(byte_id >= 0);

	while (len > 0) {
		uint32_t word;
		int offset = byte_id % 4;
		int copy_len = 4 - offset;
		if (copy_len > len) {
			copy_len = len;
		}

		//read-modify-write
		if (copy_len != 4) {
			word = hw->data_buf[byte_id / 4];    //read
		}
		memcpy(((uint8_t *)&word) + offset, data, copy_len);  //modify
		hw->data_buf[byte_id / 4] = word;                     //write

		data += copy_len;
		byte_id += copy_len;
		len -= copy_len;
	}
}

void spi_ll_read_buffer(spi_dev_t *hw, uint8_t *buffer_to_rcv, size_t bitlen)
{
	for (size_t x = 0; x < bitlen; x += 32) {
		//Do a memcpy to get around possible alignment issues in rx_buffer
		uint32_t word = hw->data_buf[x / 32];
		int len = bitlen - x;
		if (len > 32) {
			len = 32;
		}
		memcpy(&buffer_to_rcv[x / 8], &word, (len + 7) / 8);
	}
}

void spi_ll_read_buffer_byte(spi_dev_t *hw, int byte_id, uint8_t *out_data, int len)
{
	while (len > 0) {
		uint32_t word = hw->data_buf[byte_id / 4];
		int offset = byte_id % 4;
		int copy_len = 4 - offset;
		if (copy_len > len) {
			copy_len = len;
		}

		memcpy(out_data, ((uint8_t *)&word) + offset, copy_len);
		byte_id += copy_len;
		out_data += copy_len;
		len -= copy_len;
	}
}

void spi_ll_master_set_pos_cs(spi_dev_t *hw, int cs, uint32_t pos_cs)
{
	if (pos_cs) {
		hw->misc.master_cs_pol |= (1 << cs);
	} else {
		hw->misc.master_cs_pol &= ~(1 << cs);
	}
}

void spi_ll_set_tx_lsbfirst(spi_dev_t *hw, bool lsbfirst)
{
	hw->ctrl.wr_bit_order = lsbfirst;
}

void spi_ll_set_rx_lsbfirst(spi_dev_t *hw, bool lsbfirst)
{
	hw->ctrl.rd_bit_order = lsbfirst;
}

void spi_ll_master_set_mode(spi_dev_t *hw, uint8_t mode)
{
	//Configure polarity
	if (mode == 0) {
		hw->misc.ck_idle_edge = 0;
		hw->user.ck_out_edge = 0;
	} else if (mode == 1) {
		hw->misc.ck_idle_edge = 0;
		hw->user.ck_out_edge = 1;
	} else if (mode == 2) {
		hw->misc.ck_idle_edge = 1;
		hw->user.ck_out_edge = 1;
	} else if (mode == 3) {
		hw->misc.ck_idle_edge = 1;
		hw->user.ck_out_edge = 0;
	}
}

void spi_ll_slave_set_mode(spi_dev_t *hw, const int mode, bool dma_used)
{
	if (mode == 0) {
		hw->misc.ck_idle_edge = 0;
		hw->user.rsck_i_edge = 0;
		hw->user.tsck_i_edge = 0;
		hw->slave.clk_mode_13 = 0;
	} else if (mode == 1) {
		hw->misc.ck_idle_edge = 0;
		hw->user.rsck_i_edge = 1;
		hw->user.tsck_i_edge = 1;
		hw->slave.clk_mode_13 = 1;
	} else if (mode == 2) {
		hw->misc.ck_idle_edge = 1;
		hw->user.rsck_i_edge = 1;
		hw->user.tsck_i_edge = 1;
		hw->slave.clk_mode_13 = 0;
	} else if (mode == 3) {
		hw->misc.ck_idle_edge = 1;
		hw->user.rsck_i_edge = 0;
		hw->user.tsck_i_edge = 0;
		hw->slave.clk_mode_13 = 1;
	}
	hw->slave.rsck_data_out = 0;
}

void spi_ll_set_half_duplex(spi_dev_t *hw, bool half_duplex)
{
	hw->user.doutdin = !half_duplex;
}

void spi_ll_set_sio_mode(spi_dev_t *hw, int sio_mode)
{
	hw->user.sio = sio_mode;
}

void spi_ll_master_set_line_mode(spi_dev_t *hw, spi_line_mode_t line_mode)
{
	hw->ctrl.val &= ~SPI_LL_ONE_LINE_CTRL_MASK;
	hw->user.val &= ~SPI_LL_ONE_LINE_USER_MASK;
	hw->ctrl.fcmd_dual = (line_mode.cmd_lines == 2);
	hw->ctrl.fcmd_quad = (line_mode.cmd_lines == 4);
	hw->ctrl.fcmd_oct = (line_mode.cmd_lines == 8);
	hw->ctrl.faddr_dual = (line_mode.addr_lines == 2);
	hw->ctrl.faddr_quad = (line_mode.addr_lines == 4);
	hw->ctrl.faddr_oct = (line_mode.addr_lines == 8);
	hw->ctrl.fread_dual = (line_mode.data_lines == 2);
	hw->user.fwrite_dual = (line_mode.data_lines == 2);
	hw->ctrl.fread_quad = (line_mode.data_lines == 4);
	hw->user.fwrite_quad = (line_mode.data_lines == 4);
	hw->ctrl.fread_oct = (line_mode.data_lines == 8);
	hw->user.fwrite_oct = (line_mode.data_lines == 8);
}

void spi_ll_slave_set_seg_mode(spi_dev_t *hw, bool seg_trans)
{
	hw->dma_conf.dma_seg_trans_en = seg_trans;
}

void spi_ll_master_select_cs(spi_dev_t *hw, int cs_id)
{
	if (hw == &GPSPI2) {
		hw->misc.cs0_dis = (cs_id == 0) ? 0 : 1;
		hw->misc.cs1_dis = (cs_id == 1) ? 0 : 1;
		hw->misc.cs2_dis = (cs_id == 2) ? 0 : 1;
		hw->misc.cs3_dis = (cs_id == 3) ? 0 : 1;
		hw->misc.cs4_dis = (cs_id == 4) ? 0 : 1;
		hw->misc.cs5_dis = (cs_id == 5) ? 0 : 1;
	}

	if (hw == &GPSPI3) {
		hw->misc.cs0_dis = (cs_id == 0) ? 0 : 1;
		hw->misc.cs1_dis = (cs_id == 1) ? 0 : 1;
		hw->misc.cs2_dis = (cs_id == 2) ? 0 : 1;
	}
}

void spi_ll_master_keep_cs(spi_dev_t *hw, int keep_active)
{
	hw->misc.cs_keep_active = (keep_active != 0) ? 1 : 0;
}

void spi_ll_master_set_clock_by_reg(spi_dev_t *hw, const spi_ll_clock_val_t *val)
{
	hw->clock.val = *(uint32_t *)val;
}

int spi_ll_freq_for_pre_n(int fapb, int pre, int n)
{
	return (fapb / (pre * n));
}

int spi_ll_master_cal_clock(int fapb, int hz, int duty_cycle, spi_ll_clock_val_t *out_reg)
{
	typeof(GPSPI2.clock) reg;
	int eff_clk;

	//In hw, n, h and l are 1-64, pre is 1-8K. Value written to register is one lower than used value.
	if (hz > ((fapb / 4) * 3)) {
		//Using Fapb directly will give us the best result here.
		reg.clkcnt_l = 0;
		reg.clkcnt_h = 0;
		reg.clkcnt_n = 0;
		reg.clkdiv_pre = 0;
		reg.clk_equ_sysclk = 1;
		eff_clk = fapb;
	} else {
		//For best duty cycle resolution, we want n to be as close to 32 as possible, but
		//we also need a pre/n combo that gets us as close as possible to the intended freq.
		//To do this, we bruteforce n and calculate the best pre to go along with that.
		//If there's a choice between pre/n combos that give the same result, use the one
		//with the higher n.
		int pre, n, h, l;
		int bestn = -1;
		int bestpre = -1;
		int besterr = 0;
		int errval;
		for (n = 2; n <= 64; n++) { //Start at 2: we need to be able to set h/l so we have at least one high and one low pulse.
			//Effectively, this does pre=round((fapb/n)/hz).
			pre = ((fapb / n) + (hz / 2)) / hz;
			if (pre <= 0) {
				pre = 1;
			}
			if (pre > 16) {
				pre = 16;
			}
			errval = abs(spi_ll_freq_for_pre_n(fapb, pre, n) - hz);
			if (bestn == -1 || errval <= besterr) {
				besterr = errval;
				bestn = n;
				bestpre = pre;
			}
		}

		n = bestn;
		pre = bestpre;
		l = n;
		//This effectively does round((duty_cycle*n)/256)
		h = (duty_cycle * n + 127) / 256;
		if (h <= 0) {
			h = 1;
		}

		reg.clk_equ_sysclk = 0;
		reg.clkcnt_n = n - 1;
		reg.clkdiv_pre = pre - 1;
		reg.clkcnt_h = h - 1;
		reg.clkcnt_l = l - 1;
		eff_clk = spi_ll_freq_for_pre_n(fapb, pre, n);
	}
	if (out_reg != NULL) {
		*(uint32_t *)out_reg = reg.val;
	}
	return eff_clk;
}

int spi_ll_master_set_clock(spi_dev_t *hw, int fapb, int hz, int duty_cycle)
{
	spi_ll_clock_val_t reg_val;
	int freq = spi_ll_master_cal_clock(fapb, hz, duty_cycle, &reg_val);
	spi_ll_master_set_clock_by_reg(hw, &reg_val);
	return freq;
}

void spi_ll_set_mosi_delay(spi_dev_t *hw, int delay_mode, int delay_num)
{
}

void spi_ll_set_miso_delay(spi_dev_t *hw, int delay_mode, int delay_num)
{
}

void spi_ll_master_set_cs_hold(spi_dev_t *hw, int hold)
{
	hw->user1.cs_hold_time = hold;
	hw->user.cs_hold = hold ? 1 : 0;
}

void spi_ll_master_set_cs_setup(spi_dev_t *hw, uint8_t setup)
{
	hw->user1.cs_setup_time = setup - 1;
	hw->user.cs_setup = setup ? 1 : 0;
}

void spi_ll_set_mosi_bitlen(spi_dev_t *hw, size_t bitlen)
{
	if (bitlen > 0) {
		hw->ms_dlen.ms_data_bitlen = bitlen - 1;
	}
}

void spi_ll_set_miso_bitlen(spi_dev_t *hw, size_t bitlen)
{
	if (bitlen > 0) {
		hw->ms_dlen.ms_data_bitlen = bitlen - 1;
	}
}

void spi_ll_slave_set_rx_bitlen(spi_dev_t *hw, size_t bitlen)
{
	//This is not used in esp32s3
}

void spi_ll_slave_set_tx_bitlen(spi_dev_t *hw, size_t bitlen)
{
	//This is not used in esp32s3
}

void spi_ll_set_command_bitlen(spi_dev_t *hw, int bitlen)
{
	hw->user2.usr_command_bitlen = bitlen - 1;
	hw->user.usr_command = bitlen ? 1 : 0;
}

void spi_ll_set_addr_bitlen(spi_dev_t *hw, int bitlen)
{
	hw->user1.usr_addr_bitlen = bitlen - 1;
	hw->user.usr_addr = bitlen ? 1 : 0;
}

void spi_ll_set_address(spi_dev_t *hw, uint64_t addr, int addrlen, uint32_t lsbfirst)
{
	if (lsbfirst) {
		/* The output address start from the LSB of the highest byte, i.e.
		* addr[24] -> addr[31]
		* ...
		* addr[0] -> addr[7]
		* So swap the byte order to let the LSB sent first.
		*/
		addr = HAL_SWAP32(addr);
		//otherwise only addr register is sent
		hw->addr = addr;
	} else {
		// shift the address to MSB of addr register.
		// output address will be sent from MSB to LSB of addr register
		hw->addr = addr << (32 - addrlen);
	}
}

void spi_ll_set_command(spi_dev_t *hw, uint16_t cmd, int cmdlen, bool lsbfirst)
{
	if (lsbfirst) {
		// The output command start from bit0 to bit 15, kept as is.
		HAL_FORCE_MODIFY_U32_REG_FIELD(hw->user2, usr_command_value, cmd);
	} else {
		/* Output command will be sent from bit 7 to 0 of command_value, and
		 * then bit 15 to 8 of the same register field. Shift and swap to send
		 * more straightly.
		 */
		HAL_FORCE_MODIFY_U32_REG_FIELD(hw->user2, usr_command_value, HAL_SPI_SWAP_DATA_TX(cmd, cmdlen));

	}
}

void spi_ll_set_dummy(spi_dev_t *hw, int dummy_n)
{
	hw->user.usr_dummy = dummy_n ? 1 : 0;
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->user1, usr_dummy_cyclelen, dummy_n - 1);
}

void spi_ll_enable_miso(spi_dev_t *hw, int enable)
{
	hw->user.usr_miso = enable;
}

void spi_ll_enable_mosi(spi_dev_t *hw, int enable)
{
	hw->user.usr_mosi = enable;
}

uint32_t spi_ll_slave_get_rcv_bitlen(spi_dev_t *hw)
{
	return hw->slave1.data_bitlen;
}

//helper macros to generate code for each interrupts
#define FOR_EACH_ITEM(op, list) do { list(op) } while(0)
#define INTR_LIST(item)    \
	item(SPI_LL_INTR_TRANS_DONE,    dma_int_ena.trans_done,         dma_int_raw.trans_done,         dma_int_clr.trans_done,         dma_int_set.trans_done_int_set) \
	item(SPI_LL_INTR_RDBUF,         dma_int_ena.rd_buf_done,        dma_int_raw.rd_buf_done,        dma_int_clr.rd_buf_done,        dma_int_set.rd_buf_done_int_set) \
	item(SPI_LL_INTR_WRBUF,         dma_int_ena.wr_buf_done,        dma_int_raw.wr_buf_done,        dma_int_clr.wr_buf_done,        dma_int_set.wr_buf_done_int_set) \
	item(SPI_LL_INTR_RDDMA,         dma_int_ena.rd_dma_done,        dma_int_raw.rd_dma_done,        dma_int_clr.rd_dma_done,        dma_int_set.rd_dma_done_int_set) \
	item(SPI_LL_INTR_WRDMA,         dma_int_ena.wr_dma_done,        dma_int_raw.wr_dma_done,        dma_int_clr.wr_dma_done,        dma_int_set.wr_dma_done_int_set) \
	item(SPI_LL_INTR_SEG_DONE,      dma_int_ena.dma_seg_trans_done, dma_int_raw.dma_seg_trans_done, dma_int_clr.dma_seg_trans_done, dma_int_set.dma_seg_trans_done_int_set) \
	item(SPI_LL_INTR_CMD7,          dma_int_ena.cmd7,               dma_int_raw.cmd7,               dma_int_clr.cmd7,               dma_int_set.cmd7_int_set) \
	item(SPI_LL_INTR_CMD8,          dma_int_ena.cmd8,               dma_int_raw.cmd8,               dma_int_clr.cmd8,               dma_int_set.cmd8_int_set) \
	item(SPI_LL_INTR_CMD9,          dma_int_ena.cmd9,               dma_int_raw.cmd9,               dma_int_clr.cmd9,               dma_int_set.cmd9_int_set) \
	item(SPI_LL_INTR_CMDA,          dma_int_ena.cmda,               dma_int_raw.cmda,               dma_int_clr.cmda,               dma_int_set.cmda_int_set)


void spi_ll_enable_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask)
{
#define ENA_INTR(intr_bit, en_reg, ...) if (intr_mask & (intr_bit)) hw->en_reg = 1;
	FOR_EACH_ITEM(ENA_INTR, INTR_LIST);
#undef ENA_INTR
}

void spi_ll_disable_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask)
{
#define DIS_INTR(intr_bit, en_reg, ...) if (intr_mask & (intr_bit)) hw->en_reg = 0;
	FOR_EACH_ITEM(DIS_INTR, INTR_LIST);
#undef DIS_INTR
}

void spi_ll_set_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask)
{
#define SET_INTR(intr_bit, _, __, ___, set_reg) if (intr_mask & (intr_bit)) hw->set_reg = 1;
	FOR_EACH_ITEM(SET_INTR, INTR_LIST);
#undef SET_INTR
}

void spi_ll_clear_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask)
{
#define CLR_INTR(intr_bit, _, __, clr_reg, ...) if (intr_mask & (intr_bit)) hw->clr_reg = 1;
	FOR_EACH_ITEM(CLR_INTR, INTR_LIST);
#undef CLR_INTR
}

bool spi_ll_get_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask)
{
#define GET_INTR(intr_bit, _, raw_reg, ...) if (intr_mask & (intr_bit) && hw->raw_reg) return true;
	FOR_EACH_ITEM(GET_INTR, INTR_LIST);
	return false;
#undef GET_INTR
}

#undef FOR_EACH_ITEM
#undef INTR_LIST

void spi_ll_disable_int(spi_dev_t *hw)
{
	hw->dma_int_ena.trans_done = 0;
}

void spi_ll_clear_int_stat(spi_dev_t *hw)
{
	hw->dma_int_clr.trans_done = 1;
}

void spi_ll_set_int_stat(spi_dev_t *hw)
{
	hw->dma_int_set.trans_done_int_set = 1;
}

void spi_ll_enable_int(spi_dev_t *hw)
{
	hw->dma_int_ena.trans_done = 1;
}

void spi_ll_slave_hd_set_len_cond(spi_dev_t *hw, spi_ll_trans_len_cond_t cond_mask)
{
	hw->slave.rdbuf_bitlen_en = (cond_mask & SPI_LL_TRANS_LEN_COND_RDBUF) ? 1 : 0;
	hw->slave.wrbuf_bitlen_en = (cond_mask & SPI_LL_TRANS_LEN_COND_WRBUF) ? 1 : 0;
	hw->slave.rddma_bitlen_en = (cond_mask & SPI_LL_TRANS_LEN_COND_RDDMA) ? 1 : 0;
	hw->slave.wrdma_bitlen_en = (cond_mask & SPI_LL_TRANS_LEN_COND_WRDMA) ? 1 : 0;
}

int spi_ll_slave_get_rx_byte_len(spi_dev_t *hw)
{
	return hw->slave1.data_bitlen / 8;
}

uint32_t spi_ll_slave_hd_get_last_addr(spi_dev_t *hw)
{
	return hw->slave1.last_addr;
}

#undef SPI_LL_RST_MASK
#undef SPI_LL_UNUSED_INT_MASK

uint8_t spi_ll_get_slave_hd_base_command(spi_command_t cmd_t)
{
	uint8_t cmd_base = 0x00;
	switch (cmd_t)
	{
	case SPI_CMD_HD_WRBUF:
		cmd_base = SPI_LL_BASE_CMD_HD_WRBUF;
		break;
	case SPI_CMD_HD_RDBUF:
		cmd_base = SPI_LL_BASE_CMD_HD_RDBUF;
		break;
	case SPI_CMD_HD_WRDMA:
		cmd_base = SPI_LL_BASE_CMD_HD_WRDMA;
		break;
	case SPI_CMD_HD_RDDMA:
		cmd_base = SPI_LL_BASE_CMD_HD_RDDMA;
		break;
	case SPI_CMD_HD_SEG_END:
		cmd_base = SPI_LL_BASE_CMD_HD_SEG_END;
		break;
	case SPI_CMD_HD_EN_QPI:
		cmd_base = SPI_LL_BASE_CMD_HD_EN_QPI;
		break;
	case SPI_CMD_HD_WR_END:
		cmd_base = SPI_LL_BASE_CMD_HD_WR_END;
		break;
	case SPI_CMD_HD_INT0:
		cmd_base = SPI_LL_BASE_CMD_HD_INT0;
		break;
	case SPI_CMD_HD_INT1:
		cmd_base = SPI_LL_BASE_CMD_HD_INT1;
		break;
	case SPI_CMD_HD_INT2:
		cmd_base = SPI_LL_BASE_CMD_HD_INT2;
		break;
	default:
		HAL_ASSERT(cmd_base);
	}
	return cmd_base;
}

uint16_t spi_ll_get_slave_hd_command(spi_command_t cmd_t, spi_line_mode_t line_mode)
{
	uint8_t cmd_base = spi_ll_get_slave_hd_base_command(cmd_t);
	uint8_t cmd_mod = 0x00; //CMD:1-bit, ADDR:1-bit, DATA:1-bit

	if (line_mode.data_lines == 2) {
		if (line_mode.addr_lines == 2) {
			cmd_mod = 0x50; //CMD:1-bit, ADDR:2-bit, DATA:2-bit
		} else {
			cmd_mod = 0x10; //CMD:1-bit, ADDR:1-bit, DATA:2-bit
		}
	} else if (line_mode.data_lines == 4) {
		if (line_mode.addr_lines == 4) {
			cmd_mod = 0xA0; //CMD:1-bit, ADDR:4-bit, DATA:4-bit
		} else {
			cmd_mod = 0x20; //CMD:1-bit, ADDR:1-bit, DATA:4-bit
		}
	}
	if (cmd_base == SPI_LL_BASE_CMD_HD_SEG_END || cmd_base == SPI_LL_BASE_CMD_HD_EN_QPI) {
		cmd_mod = 0x00;
	}

	return cmd_base | cmd_mod;
}

int spi_ll_get_slave_hd_dummy_bits(spi_line_mode_t line_mode)
{
	return 8;
}

