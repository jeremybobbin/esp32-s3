
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

#define I2C_LL_CMD_RESTART    6    /*!<I2C restart command */
#define I2C_LL_CMD_WRITE      1    /*!<I2C write command */
#define I2C_LL_CMD_READ       3    /*!<I2C read command */
#define I2C_LL_CMD_STOP       2    /*!<I2C stop command */
#define I2C_LL_CMD_END        4    /*!<I2C end command */

#define I2C_LL_GET_HW(i2c_num)        (((i2c_num) == 0) ? &I2C0 : &I2C1)
#define I2C_LL_GET_FIFO_ADDR(i2c_num) (I2C_DATA_APB_REG(i2c_num))
#define I2C_LL_MASTER_TX_INT          (I2C_NACK_INT_ENA_M|I2C_TIME_OUT_INT_ENA_M|I2C_TRANS_COMPLETE_INT_ENA_M|I2C_ARBITRATION_LOST_INT_ENA_M|I2C_END_DETECT_INT_ENA_M)
#define I2C_LL_MASTER_RX_INT          (I2C_TIME_OUT_INT_ENA_M|I2C_TRANS_COMPLETE_INT_ENA_M|I2C_ARBITRATION_LOST_INT_ENA_M|I2C_END_DETECT_INT_ENA_M)
#define I2C_LL_SLAVE_TX_INT           (I2C_TXFIFO_WM_INT_ENA_M)
#define I2C_LL_SLAVE_RX_INT           (I2C_RXFIFO_WM_INT_ENA_M | I2C_TRANS_COMPLETE_INT_ENA_M)
#define I2C_LL_CLK_SRC_FREQ(src_clk)  (((src_clk) == I2C_SCLK_RTC) ? 8*1000*1000 : 40*1000*1000); // Another clock is XTAL clock
#define I2C_LL_MAX_TIMEOUT I2C_TIME_OUT_VALUE_V

void i2c_ll_cal_bus_clk(uint32_t source_clk, uint32_t bus_freq, i2c_clk_cal_t *clk_cal);
void i2c_ll_update(i2c_dev_t *hw);
void i2c_ll_set_bus_timing(i2c_dev_t *hw, i2c_clk_cal_t *bus_cfg);
void i2c_ll_txfifo_rst(i2c_dev_t *hw);
void i2c_ll_rxfifo_rst(i2c_dev_t *hw);
void i2c_ll_set_scl_timing(i2c_dev_t *hw, int high_period, int low_period);
void i2c_ll_set_scl_clk_timing(i2c_dev_t *hw, int high_period, int low_period, int wait_high_period);
void i2c_ll_clr_intsts_mask(i2c_dev_t *hw, uint32_t mask);
void i2c_ll_enable_intr_mask(i2c_dev_t *hw, uint32_t mask);
void i2c_ll_disable_intr_mask(i2c_dev_t *hw, uint32_t mask);
uint32_t i2c_ll_get_intsts_mask(i2c_dev_t *hw);
void i2c_ll_set_fifo_mode(i2c_dev_t *hw, bool fifo_mode_en);
void i2c_ll_set_tout(i2c_dev_t *hw, int tout);
void i2c_ll_set_slave_addr(i2c_dev_t *hw, uint16_t slave_addr, bool addr_10bit_en);
void i2c_ll_write_cmd_reg(i2c_dev_t *hw, i2c_hw_cmd_t cmd, int cmd_idx);
void i2c_ll_set_start_timing(i2c_dev_t *hw, int start_setup, int start_hold);
void i2c_ll_set_stop_timing(i2c_dev_t *hw, int stop_setup, int stop_hold);
void i2c_ll_set_sda_timing(i2c_dev_t *hw, int sda_sample, int sda_hold);
void i2c_ll_set_txfifo_empty_thr(i2c_dev_t *hw, uint8_t empty_thr);
void i2c_ll_set_rxfifo_full_thr(i2c_dev_t *hw, uint8_t full_thr);
void i2c_ll_set_data_mode(i2c_dev_t *hw, i2c_trans_mode_t tx_mode, i2c_trans_mode_t rx_mode);
void i2c_ll_get_data_mode(i2c_dev_t *hw, i2c_trans_mode_t *tx_mode, i2c_trans_mode_t *rx_mode);
void i2c_ll_get_sda_timing(i2c_dev_t *hw, int *sda_sample, int *sda_hold);
uint32_t i2c_ll_get_hw_version(i2c_dev_t *hw);
bool i2c_ll_is_bus_busy(i2c_dev_t *hw);
bool i2c_ll_is_master_mode(i2c_dev_t *hw);
uint32_t i2c_ll_get_rxfifo_cnt(i2c_dev_t *hw);
uint32_t i2c_ll_get_txfifo_len(i2c_dev_t *hw);
uint32_t i2c_ll_get_tout(i2c_dev_t *hw);
void i2c_ll_trans_start(i2c_dev_t *hw);
void i2c_ll_get_start_timing(i2c_dev_t *hw, int *setup_time, int *hold_time);
void i2c_ll_get_stop_timing(i2c_dev_t *hw, int *setup_time, int *hold_time);
void i2c_ll_get_scl_timing(i2c_dev_t *hw, int *high_period, int *low_period);
void i2c_ll_get_scl_clk_timing(i2c_dev_t *hw, int *high_period, int *low_period, int *wait_high_period);
void i2c_ll_write_txfifo(i2c_dev_t *hw, uint8_t *ptr, uint8_t len);
void i2c_ll_read_rxfifo(i2c_dev_t *hw, uint8_t *ptr, uint8_t len);
void i2c_ll_set_filter(i2c_dev_t *hw, uint8_t filter_num);
uint8_t i2c_ll_get_filter(i2c_dev_t *hw);
void i2c_ll_master_enable_tx_it(i2c_dev_t *hw);
void i2c_ll_master_enable_rx_it(i2c_dev_t *hw);
void i2c_ll_master_disable_tx_it(i2c_dev_t *hw);
void i2c_ll_master_disable_rx_it(i2c_dev_t *hw);
void i2c_ll_master_clr_tx_it(i2c_dev_t *hw);
void i2c_ll_master_clr_rx_it(i2c_dev_t *hw);
void i2c_ll_slave_enable_tx_it(i2c_dev_t *hw);
void i2c_ll_slave_enable_rx_it(i2c_dev_t *hw);
void i2c_ll_slave_disable_tx_it(i2c_dev_t *hw);
void i2c_ll_slave_disable_rx_it(i2c_dev_t *hw);
void i2c_ll_slave_clr_tx_it(i2c_dev_t *hw);
void i2c_ll_slave_clr_rx_it(i2c_dev_t *hw);
void i2c_ll_master_fsm_rst(i2c_dev_t *hw);
void i2c_ll_master_clr_bus(i2c_dev_t *hw);
void i2c_ll_set_source_clk(i2c_dev_t *hw, i2c_sclk_t src_clk);
void i2c_ll_master_get_event(i2c_dev_t *hw, i2c_intr_event_t *event);
void i2c_ll_slave_get_event(i2c_dev_t *hw, i2c_intr_event_t *event);
void i2c_ll_master_init(i2c_dev_t *hw);
void i2c_ll_slave_init(i2c_dev_t *hw);
