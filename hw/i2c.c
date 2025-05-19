
// The LL layer for I2C register operations


#include "hal/misc.h"
#include "soc/i2c_periph.h"
#include "soc/soc_caps.h"
#include "soc/i2c_struct.h"
#include "hal/i2c_types.h"
#include "esp_assert.h"


#define I2C_LL_INTR_MASK          (0x3fff) /*!< I2C all interrupt bitmap */
typedef union {
	struct {
		uint32_t byte_num:    8,
				 ack_en:      1,
				 ack_exp:     1,
				 ack_val:     1,
				 op_code:     3,
				 reserved14: 17,
				 done:        1;
	};
	uint32_t val;
} i2c_hw_cmd_t;

typedef enum {
	I2C_INTR_EVENT_ERR,
	I2C_INTR_EVENT_ARBIT_LOST,   /*!< I2C arbition lost event */
	I2C_INTR_EVENT_NACK,         /*!< I2C NACK event */
	I2C_INTR_EVENT_TOUT,         /*!< I2C time out event */
	I2C_INTR_EVENT_END_DET,      /*!< I2C end detected event */
	I2C_INTR_EVENT_TRANS_DONE,   /*!< I2C trans done event */
	I2C_INTR_EVENT_RXFIFO_FULL,  /*!< I2C rxfifo full event */
	I2C_INTR_EVENT_TXFIFO_EMPTY, /*!< I2C txfifo empty event */
} i2c_intr_event_t;

typedef struct {
	uint16_t clkm_div;          /*!< I2C core clock divider */
	uint16_t scl_low;           /*!< I2C scl low period */
	uint16_t scl_high;          /*!< I2C scl hight period */
	uint16_t scl_wait_high;     /*!< I2C scl wait_high period */
	uint16_t sda_hold;          /*!< I2C scl low period */
	uint16_t sda_sample;        /*!< I2C sda sample time */
	uint16_t setup;             /*!< I2C start and stop condition setup period */
	uint16_t hold;              /*!< I2C start and stop condition hold period  */
	uint16_t tout;              /*!< I2C bus timeout period */
} i2c_clk_cal_t;

// I2C operation mode command
#define I2C_LL_CMD_RESTART    6    /*!<I2C restart command */
#define I2C_LL_CMD_WRITE      1    /*!<I2C write command */
#define I2C_LL_CMD_READ       3    /*!<I2C read command */
#define I2C_LL_CMD_STOP       2    /*!<I2C stop command */
#define I2C_LL_CMD_END        4    /*!<I2C end command */

// Get the I2C hardware instance
#define I2C_LL_GET_HW(i2c_num)        (((i2c_num) == 0) ? &I2C0 : &I2C1)
// Get the I2C hardware FIFO address
#define I2C_LL_GET_FIFO_ADDR(i2c_num) (I2C_DATA_APB_REG(i2c_num))
// I2C master TX interrupt bitmap
#define I2C_LL_MASTER_TX_INT          (I2C_NACK_INT_ENA_M|I2C_TIME_OUT_INT_ENA_M|I2C_TRANS_COMPLETE_INT_ENA_M|I2C_ARBITRATION_LOST_INT_ENA_M|I2C_END_DETECT_INT_ENA_M)
// I2C master RX interrupt bitmap
#define I2C_LL_MASTER_RX_INT          (I2C_TIME_OUT_INT_ENA_M|I2C_TRANS_COMPLETE_INT_ENA_M|I2C_ARBITRATION_LOST_INT_ENA_M|I2C_END_DETECT_INT_ENA_M)
// I2C slave TX interrupt bitmap
#define I2C_LL_SLAVE_TX_INT           (I2C_TXFIFO_WM_INT_ENA_M)
// I2C slave RX interrupt bitmap
#define I2C_LL_SLAVE_RX_INT           (I2C_RXFIFO_WM_INT_ENA_M | I2C_TRANS_COMPLETE_INT_ENA_M)
// I2C source clock
#define I2C_LL_CLK_SRC_FREQ(src_clk)  (((src_clk) == I2C_SCLK_RTC) ? 8*1000*1000 : 40*1000*1000); // Another clock is XTAL clock
// I2C max timeout value
#define I2C_LL_MAX_TIMEOUT I2C_TIME_OUT_VALUE_V

void i2c_ll_cal_bus_clk(uint32_t source_clk, uint32_t bus_freq, i2c_clk_cal_t *clk_cal)
{
	uint32_t clkm_div = source_clk / (bus_freq * 1024) +1;
	uint32_t sclk_freq = source_clk / clkm_div;
	uint32_t half_cycle = sclk_freq / bus_freq / 2;
	//SCL
	clk_cal->clkm_div = clkm_div;
	clk_cal->scl_low = half_cycle;
	// default, scl_wait_high < scl_high
	// Make 80KHz as a boundary here, because when working at lower frequency, too much scl_wait_high will faster the frequency
	// according to some hardware behaviors.
	clk_cal->scl_wait_high = (bus_freq >= 80*1000) ? (half_cycle / 2 - 2) : (half_cycle / 4);
	clk_cal->scl_high = half_cycle - clk_cal->scl_wait_high;
	clk_cal->sda_hold = half_cycle / 4;
	clk_cal->sda_sample = half_cycle / 2 + clk_cal->scl_wait_high;
	clk_cal->setup = half_cycle;
	clk_cal->hold = half_cycle;
	//default we set the timeout value to about 10 bus cycles
	// log(20*half_cycle)/log(2) = log(half_cycle)/log(2) +  log(20)/log(2)
	clk_cal->tout = (int)(sizeof(half_cycle) * 8 - __builtin_clz(5 * half_cycle)) + 2;
}

void i2c_ll_update(i2c_dev_t *hw)
{
	hw->ctr.conf_upgate = 1;
}

void i2c_ll_set_bus_timing(i2c_dev_t *hw, i2c_clk_cal_t *bus_cfg)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->clk_conf, sclk_div_num, bus_cfg->clkm_div - 1);
	/* According to the Technical Reference Manual, the following timings must be subtracted by 1.
	 * However, according to the practical measurement and some hardware behaviour, if wait_high_period and scl_high minus one.
	 * The SCL frequency would be a little higher than expected. Therefore, the solution
	 * here is not to minus scl_high as well as scl_wait high, and the frequency will be absolutely accurate to all frequency
	 * to some extent. */
	hw->scl_low_period.scl_low_period = bus_cfg->scl_low - 1;
	hw->scl_high_period.scl_high_period = bus_cfg->scl_high;
	hw->scl_high_period.scl_wait_high_period = bus_cfg->scl_wait_high;
	//sda sample
	hw->sda_hold.sda_hold_time = bus_cfg->sda_hold - 1;
	hw->sda_sample.sda_sample_time = bus_cfg->sda_sample - 1;
	//setup
	hw->scl_rstart_setup.scl_rstart_setup_time = bus_cfg->setup - 1;
	hw->scl_stop_setup.scl_stop_setup_time = bus_cfg->setup - 1;
	//hold
	hw->scl_start_hold.scl_start_hold_time = bus_cfg->hold - 1;
	hw->scl_stop_hold.scl_stop_hold_time = bus_cfg->hold - 1;
	hw->to.time_out_value = bus_cfg->tout;
	hw->to.time_out_en = 1;
}

void i2c_ll_txfifo_rst(i2c_dev_t *hw)
{
	hw->fifo_conf.tx_fifo_rst = 1;
	hw->fifo_conf.tx_fifo_rst = 0;
}

void i2c_ll_rxfifo_rst(i2c_dev_t *hw)
{
	hw->fifo_conf.rx_fifo_rst = 1;
	hw->fifo_conf.rx_fifo_rst = 0;
}

void i2c_ll_set_scl_timing(i2c_dev_t *hw, int high_period, int low_period)
{
	int high_period_output = high_period - 10; // The rising edge by open-drain output + internal pullup (about 50K) is slow
	hw->scl_low_period.scl_low_period = low_period - 1;
	hw->scl_high_period.scl_high_period = high_period_output;
	hw->scl_high_period.scl_wait_high_period = high_period - high_period_output;
}

void i2c_ll_set_scl_clk_timing(i2c_dev_t *hw, int high_period, int low_period, int wait_high_period)
{
	hw->scl_low_period.scl_low_period = low_period;
	hw->scl_high_period.scl_high_period = high_period;
	hw->scl_high_period.scl_wait_high_period = wait_high_period;
}

void i2c_ll_clr_intsts_mask(i2c_dev_t *hw, uint32_t mask)
{
	hw->int_clr.val = mask;
}

void i2c_ll_enable_intr_mask(i2c_dev_t *hw, uint32_t mask)
{
	hw->int_ena.val |= mask;
}

void i2c_ll_disable_intr_mask(i2c_dev_t *hw, uint32_t mask)
{
	hw->int_ena.val &= (~mask);
}

uint32_t i2c_ll_get_intsts_mask(i2c_dev_t *hw)
{
	return hw->int_status.val;
}

void i2c_ll_set_fifo_mode(i2c_dev_t *hw, bool fifo_mode_en)
{
	hw->fifo_conf.nonfifo_en = fifo_mode_en ? 0 : 1;
}

void i2c_ll_set_tout(i2c_dev_t *hw, int tout)
{
	hw->to.time_out_value = tout;
}

void i2c_ll_set_slave_addr(i2c_dev_t *hw, uint16_t slave_addr, bool addr_10bit_en)
{
	hw->slave_addr.slave_addr = slave_addr;
	hw->slave_addr.addr_10bit_en = addr_10bit_en;
}

void i2c_ll_write_cmd_reg(i2c_dev_t *hw, i2c_hw_cmd_t cmd, int cmd_idx)
{
	ESP_STATIC_ASSERT(sizeof(i2c_comd0_reg_t) == sizeof(i2c_hw_cmd_t),
					  "i2c_comdX_reg_t structure size must be equal to i2c_hw_cmd_t structure size");
	volatile i2c_hw_cmd_t* commands = (volatile i2c_hw_cmd_t*) &hw->comd0;
	commands[cmd_idx].val = cmd.val;
}

void i2c_ll_set_start_timing(i2c_dev_t *hw, int start_setup, int start_hold)
{
	hw->scl_rstart_setup.scl_rstart_setup_time = start_setup;
	hw->scl_start_hold.scl_start_hold_time = start_hold - 1;
}

void i2c_ll_set_stop_timing(i2c_dev_t *hw, int stop_setup, int stop_hold)
{
	hw->scl_stop_setup.scl_stop_setup_time = stop_setup;
	hw->scl_stop_hold.scl_stop_hold_time = stop_hold;
}

void i2c_ll_set_sda_timing(i2c_dev_t *hw, int sda_sample, int sda_hold)
{
	hw->sda_hold.sda_hold_time = sda_hold;
	hw->sda_sample.sda_sample_time = sda_sample;
}

void i2c_ll_set_txfifo_empty_thr(i2c_dev_t *hw, uint8_t empty_thr)
{
	hw->fifo_conf.txfifo_wm_thrhd = empty_thr;
}

void i2c_ll_set_rxfifo_full_thr(i2c_dev_t *hw, uint8_t full_thr)
{
	hw->fifo_conf.rxfifo_wm_thrhd = full_thr;
}

void i2c_ll_set_data_mode(i2c_dev_t *hw, i2c_trans_mode_t tx_mode, i2c_trans_mode_t rx_mode)
{
	hw->ctr.tx_lsb_first = tx_mode;
	hw->ctr.rx_lsb_first = rx_mode;
}

void i2c_ll_get_data_mode(i2c_dev_t *hw, i2c_trans_mode_t *tx_mode, i2c_trans_mode_t *rx_mode)
{
	*tx_mode = hw->ctr.tx_lsb_first;
	*rx_mode = hw->ctr.rx_lsb_first;
}

void i2c_ll_get_sda_timing(i2c_dev_t *hw, int *sda_sample, int *sda_hold)
{
	*sda_hold = hw->sda_hold.sda_hold_time;
	*sda_sample = hw->sda_sample.sda_sample_time;
}

uint32_t i2c_ll_get_hw_version(i2c_dev_t *hw)
{
	return hw->date.val;
}

bool i2c_ll_is_bus_busy(i2c_dev_t *hw)
{
	return hw->sr.bus_busy;
}

bool i2c_ll_is_master_mode(i2c_dev_t *hw)
{
	return hw->ctr.ms_mode;
}

uint32_t i2c_ll_get_rxfifo_cnt(i2c_dev_t *hw)
{
	return hw->sr.rxfifo_cnt;
}

uint32_t i2c_ll_get_txfifo_len(i2c_dev_t *hw)
{
	return SOC_I2C_FIFO_LEN - hw->sr.txfifo_cnt;
}

uint32_t i2c_ll_get_tout(i2c_dev_t *hw)
{
	return hw->to.time_out_value;
}

void i2c_ll_trans_start(i2c_dev_t *hw)
{
	hw->ctr.trans_start = 1;
}

void i2c_ll_get_start_timing(i2c_dev_t *hw, int *setup_time, int *hold_time)
{
	*setup_time = hw->scl_rstart_setup.scl_rstart_setup_time;
	*hold_time = hw->scl_start_hold.scl_start_hold_time + 1;
}

void i2c_ll_get_stop_timing(i2c_dev_t *hw, int *setup_time, int *hold_time)
{
	*setup_time = hw->scl_stop_setup.scl_stop_setup_time;
	*hold_time = hw->scl_stop_hold.scl_stop_hold_time;
}

void i2c_ll_get_scl_timing(i2c_dev_t *hw, int *high_period, int *low_period)
{
	*high_period = hw->scl_high_period.scl_high_period + hw->scl_high_period.scl_wait_high_period;
	*low_period = hw->scl_low_period.scl_low_period + 1;
}

void i2c_ll_get_scl_clk_timing(i2c_dev_t *hw, int *high_period, int *low_period, int *wait_high_period)
{
	*high_period = hw->scl_high_period.scl_high_period;
	*wait_high_period = hw->scl_high_period.scl_wait_high_period;
	*low_period = hw->scl_low_period.scl_low_period;
}

void i2c_ll_write_txfifo(i2c_dev_t *hw, uint8_t *ptr, uint8_t len)
{
	for (int i = 0; i< len; i++) {
		HAL_FORCE_MODIFY_U32_REG_FIELD(hw->data, fifo_rdata, ptr[i]);
	}
}

void i2c_ll_read_rxfifo(i2c_dev_t *hw, uint8_t *ptr, uint8_t len)
{
	for(int i = 0; i < len; i++) {
		ptr[i] = HAL_FORCE_READ_U32_REG_FIELD(hw->data, fifo_rdata);
	}
}

void i2c_ll_set_filter(i2c_dev_t *hw, uint8_t filter_num)
{
	if (filter_num > 0) {
		hw->filter_cfg.scl_filter_thres = filter_num;
		hw->filter_cfg.sda_filter_thres = filter_num;
		hw->filter_cfg.scl_filter_en = 1;
		hw->filter_cfg.sda_filter_en = 1;
	} else {
		hw->filter_cfg.scl_filter_en = 0;
		hw->filter_cfg.sda_filter_en = 0;
	}
}

uint8_t i2c_ll_get_filter(i2c_dev_t *hw)
{
	return hw->filter_cfg.scl_filter_thres;
}

void i2c_ll_master_enable_tx_it(i2c_dev_t *hw)
{
	hw->int_clr.val = ~0;
	hw->int_ena.val =  I2C_LL_MASTER_TX_INT;
}

void i2c_ll_master_enable_rx_it(i2c_dev_t *hw)
{
	hw->int_clr.val = ~0;
	hw->int_ena.val = I2C_LL_MASTER_RX_INT;
}

void i2c_ll_master_disable_tx_it(i2c_dev_t *hw)
{
	hw->int_ena.val &= (~I2C_LL_MASTER_TX_INT);
}

void i2c_ll_master_disable_rx_it(i2c_dev_t *hw)
{
	hw->int_ena.val &= (~I2C_LL_MASTER_RX_INT);
}

void i2c_ll_master_clr_tx_it(i2c_dev_t *hw)
{
	hw->int_clr.val = I2C_LL_MASTER_TX_INT;
}

void i2c_ll_master_clr_rx_it(i2c_dev_t *hw)
{
	hw->int_clr.val = I2C_LL_MASTER_RX_INT;
}

void i2c_ll_slave_enable_tx_it(i2c_dev_t *hw)
{
	hw->int_ena.val |= I2C_LL_SLAVE_TX_INT;
}

void i2c_ll_slave_enable_rx_it(i2c_dev_t *hw)
{
	hw->int_ena.val |= I2C_LL_SLAVE_RX_INT;
}

void i2c_ll_slave_disable_tx_it(i2c_dev_t *hw)
{
	hw->int_ena.val &= (~I2C_LL_SLAVE_TX_INT);
}

void i2c_ll_slave_disable_rx_it(i2c_dev_t *hw)
{
	hw->int_ena.val &= (~I2C_LL_SLAVE_RX_INT);
}

void i2c_ll_slave_clr_tx_it(i2c_dev_t *hw)
{
	hw->int_clr.val = I2C_LL_SLAVE_TX_INT;
}

void i2c_ll_slave_clr_rx_it(i2c_dev_t *hw)
{
	hw->int_clr.val = I2C_LL_SLAVE_RX_INT;
}

void i2c_ll_master_fsm_rst(i2c_dev_t *hw)
{
	hw->ctr.fsm_rst = 1;
}

void i2c_ll_master_clr_bus(i2c_dev_t *hw)
{
	hw->scl_sp_conf.scl_rst_slv_num = 9;
	hw->scl_sp_conf.scl_rst_slv_en = 0;
	hw->ctr.conf_upgate = 1;
	hw->scl_sp_conf.scl_rst_slv_en = 1;
}

void i2c_ll_set_source_clk(i2c_dev_t *hw, i2c_sclk_t src_clk)
{
	hw->clk_conf.sclk_sel = (src_clk == I2C_SCLK_RTC) ? 1 : 0;
}

void i2c_ll_master_get_event(i2c_dev_t *hw, i2c_intr_event_t *event)
{
	typeof(hw->int_status) int_sts = hw->int_status;
	if (int_sts.arbitration_lost_int_st) {
		*event = I2C_INTR_EVENT_ARBIT_LOST;
	} else if (int_sts.nack_int_st) {
		*event = I2C_INTR_EVENT_NACK;
	} else if (int_sts.time_out_int_st) {
		*event = I2C_INTR_EVENT_TOUT;
	} else if (int_sts.end_detect_int_st) {
		*event = I2C_INTR_EVENT_END_DET;
	} else if (int_sts.trans_complete_int_st) {
		*event = I2C_INTR_EVENT_TRANS_DONE;
	} else {
		*event = I2C_INTR_EVENT_ERR;
	}
}


void i2c_ll_slave_get_event(i2c_dev_t *hw, i2c_intr_event_t *event)
{
	typeof(hw->int_status) int_sts = hw->int_status;
	if (int_sts.txfifo_wm_int_st) {
		*event = I2C_INTR_EVENT_TXFIFO_EMPTY;
	} else if (int_sts.trans_complete_int_st) {
		*event = I2C_INTR_EVENT_TRANS_DONE;
	} else if (int_sts.rxfifo_wm_int_st) {
		*event = I2C_INTR_EVENT_RXFIFO_FULL;
	} else {
		*event = I2C_INTR_EVENT_ERR;
	}
}

void i2c_ll_master_init(i2c_dev_t *hw)
{
	typeof(hw->ctr) ctrl_reg;
	ctrl_reg.val = 0;
	ctrl_reg.ms_mode = 1;
	ctrl_reg.clk_en = 1;
	ctrl_reg.sda_force_out = 1;
	ctrl_reg.scl_force_out = 1;
	hw->ctr.val = ctrl_reg.val;
}

void i2c_ll_slave_init(i2c_dev_t *hw)
{
	typeof(hw->ctr) ctrl_reg;
	ctrl_reg.val = 0;
	ctrl_reg.sda_force_out = 1;
	ctrl_reg.scl_force_out = 1;
	hw->ctr.val = ctrl_reg.val;
	hw->ctr.slv_tx_auto_start_en = 1;
	hw->fifo_conf.fifo_addr_cfg_en = 0;
}

