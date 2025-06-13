#include <stdint.h>
#include <stdbool.h>

#define I2C_LL_INTR_MASK          (0x3fff) /*!< I2C all interrupt bitmap */

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
#define SOC_I2C_FIFO_LEN 32

#define I2C_NACK_INT_ENA    (1<<10)
#define I2C_NACK_INT_ENA_M  (I2C_NACK_INT_ENA_V << I2C_NACK_INT_ENA_S)
#define I2C_NACK_INT_ENA_V  0x00000001U
#define I2C_NACK_INT_ENA_S  10
#define I2C_TRANS_COMPLETE_INT_ENA    (1<<7)
#define I2C_TRANS_COMPLETE_INT_ENA_M  (I2C_TRANS_COMPLETE_INT_ENA_V << I2C_TRANS_COMPLETE_INT_ENA_S)
#define I2C_TRANS_COMPLETE_INT_ENA_V  0x00000001U
#define I2C_TRANS_COMPLETE_INT_ENA_S  7
#define I2C_TIME_OUT_INT_ENA    (BIT(8))
#define I2C_TIME_OUT_INT_ENA_M  (I2C_TIME_OUT_INT_ENA_V << I2C_TIME_OUT_INT_ENA_S)
#define I2C_TIME_OUT_INT_ENA_V  0x00000001U
#define I2C_TIME_OUT_INT_ENA_S  8
#define I2C_ARBITRATION_LOST_INT_ENA    (1<<5)
#define I2C_ARBITRATION_LOST_INT_ENA_M  (I2C_ARBITRATION_LOST_INT_ENA_V << I2C_ARBITRATION_LOST_INT_ENA_S)
#define I2C_ARBITRATION_LOST_INT_ENA_V  0x00000001U
#define I2C_ARBITRATION_LOST_INT_ENA_S  5
#define I2C_TXFIFO_WM_INT_RAW    (1<<1)
#define I2C_TXFIFO_WM_INT_RAW_M  (I2C_TXFIFO_WM_INT_RAW_V << I2C_TXFIFO_WM_INT_RAW_S)
#define I2C_TXFIFO_WM_INT_RAW_V  0x00000001U
#define I2C_TXFIFO_WM_INT_RAW_S  1
#define I2C_INT_ENA_REG (DR_REG_I2C_BASE + 0x28)
#define I2C_RXFIFO_WM_INT_ENA    (1<<0)
#define I2C_RXFIFO_WM_INT_ENA_M  (I2C_RXFIFO_WM_INT_ENA_V << I2C_RXFIFO_WM_INT_ENA_S)
#define I2C_RXFIFO_WM_INT_ENA_V  0x00000001U
#define I2C_RXFIFO_WM_INT_ENA_S  0
#define I2C_END_DETECT_INT_ENA    (1<<3)
#define I2C_END_DETECT_INT_ENA_M  (I2C_END_DETECT_INT_ENA_V << I2C_END_DETECT_INT_ENA_S)
#define I2C_END_DETECT_INT_ENA_V  0x00000001U
#define I2C_END_DETECT_INT_ENA_S  3
#define I2C_TXFIFO_WM_INT_ENA    (1<<1)
#define I2C_TXFIFO_WM_INT_ENA_M  (I2C_TXFIFO_WM_INT_ENA_V << I2C_TXFIFO_WM_INT_ENA_S)
#define I2C_TXFIFO_WM_INT_ENA_V  0x00000001U
#define I2C_TXFIFO_WM_INT_ENA_S  1

#define HAL_FORCE_MODIFY_U32_REG_FIELD(base_reg, reg_field, field_val) { \
	uint32_t temp_val = base_reg.val;                                \
	typeof(base_reg) temp_reg;                                       \
	temp_reg.val = temp_val;                                         \
	temp_reg.reg_field = (field_val);                                \
	(base_reg).val = temp_reg.val;                                   \
}

#define HAL_FORCE_READ_U32_REG_FIELD(base_reg, reg_field) ({    \
	uint32_t temp_val = base_reg.val;                       \
	typeof(base_reg) temp_reg;                              \
	temp_reg.val = temp_val;                                \
	temp_reg.reg_field;                                     \
})



typedef enum {
	I2C_DATA_MODE_MSB_FIRST = 0,  /*!< I2C data msb first */
	I2C_DATA_MODE_LSB_FIRST = 1,  /*!< I2C data lsb first */
	I2C_DATA_MODE_MAX
} i2c_trans_mode_t;

typedef union {
	struct {
		uint32_t scl_low_period:9;
		uint32_t reserved_9:23;
	};
	uint32_t val;
} i2c_scl_low_period_reg_t;

typedef union {
	struct {
		uint32_t sda_hold_time:9;
		uint32_t reserved_9:23;
	};
	uint32_t val;
} i2c_sda_hold_reg_t;

typedef union {
	struct {
		uint32_t sda_sample_time:9;
		uint32_t reserved_9:23;
	};
	uint32_t val;
} i2c_sda_sample_reg_t;

typedef union {
	struct {
		uint32_t scl_high_period:9;
		uint32_t scl_wait_high_period:7;
		uint32_t reserved_16:16;
	};
	uint32_t val;
} i2c_scl_high_period_reg_t;

typedef union {
	struct {
		uint32_t scl_start_hold_time:9;
		uint32_t reserved_9:23;
	};
	uint32_t val;
} i2c_scl_start_hold_reg_t;

typedef union {
	struct {
		uint32_t scl_rstart_setup_time:9;
		uint32_t reserved_9:23;
	};
	uint32_t val;
} i2c_scl_rstart_setup_reg_t;

typedef union {
	struct {
		uint32_t scl_stop_hold_time:9;
		uint32_t reserved_9:23;
	};
	uint32_t val;
} i2c_scl_stop_hold_reg_t;

typedef union {
	struct {
		uint32_t scl_stop_setup_time:9;
		uint32_t reserved_9:23;
	};
	uint32_t val;
} i2c_scl_stop_setup_reg_t;

typedef union {
	struct {
		uint32_t scl_st_to_i2c:5;
		uint32_t reserved_5:27;
	};
	uint32_t val;
} i2c_scl_st_time_out_reg_t;

typedef union {
	struct {
		uint32_t scl_main_st_to_i2c:5;
		uint32_t reserved_5:27;
	};
	uint32_t val;
} i2c_scl_main_st_time_out_reg_t;

typedef union {
	struct {
		uint32_t sda_force_out:1;
		uint32_t scl_force_out:1;
		uint32_t sample_scl_level:1;
		uint32_t rx_full_ack_level:1;
		uint32_t ms_mode:1;
		uint32_t trans_start:1;
		uint32_t tx_lsb_first:1;
		uint32_t rx_lsb_first:1;
		uint32_t clk_en:1;
		uint32_t arbitration_en:1;
		uint32_t fsm_rst:1;
		uint32_t conf_upgate:1;
		uint32_t slv_tx_auto_start_en:1;
		uint32_t addr_10bit_rw_check_en:1;
		uint32_t addr_broadcasting_en:1;
		uint32_t reserved_15:17;
	};
	uint32_t val;
} i2c_ctr_reg_t;

typedef union {
	struct {
		uint32_t time_out_value:5;
		uint32_t time_out_en:1;
		uint32_t reserved_6:26;
	};
	uint32_t val;
} i2c_to_reg_t;

typedef union {
	struct {
		uint32_t slave_addr:15;
		uint32_t reserved_15:16;
		uint32_t addr_10bit_en:1;
	};
	uint32_t val;
} i2c_slave_addr_reg_t;

typedef union {
	struct {
		uint32_t rxfifo_wm_thrhd:5;
		uint32_t txfifo_wm_thrhd:5;
		uint32_t nonfifo_en:1;
		uint32_t fifo_addr_cfg_en:1;
		uint32_t rx_fifo_rst:1;
		uint32_t tx_fifo_rst:1;
		uint32_t fifo_prt_en:1;
		uint32_t reserved_15:17;
	};
	uint32_t val;
} i2c_fifo_conf_reg_t;

typedef union {
	struct {
		uint32_t scl_filter_thres:4;
		uint32_t sda_filter_thres:4;
		uint32_t scl_filter_en:1;
		uint32_t sda_filter_en:1;
		uint32_t reserved_10:22;
	};
	uint32_t val;
} i2c_filter_cfg_reg_t;

typedef union {
	struct {
		uint32_t sclk_div_num:8;
		uint32_t sclk_div_a:6;
		uint32_t sclk_div_b:6;
		uint32_t sclk_sel:1;
		uint32_t sclk_active:1;
		uint32_t reserved_22:10;
	};
	uint32_t val;
} i2c_clk_conf_reg_t;

typedef union {
	struct {
		uint32_t scl_rst_slv_en:1;
		uint32_t scl_rst_slv_num:5;
		uint32_t scl_pd_en:1;
		uint32_t sda_pd_en:1;
		uint32_t reserved_8:24;
	};
	uint32_t val;
} i2c_scl_sp_conf_reg_t;

typedef union {
	struct {
		uint32_t stretch_protect_num:10;
		uint32_t slave_scl_stretch_en:1;
		uint32_t slave_scl_stretch_clr:1;
		uint32_t slave_byte_ack_ctl_en:1;
		uint32_t slave_byte_ack_lvl:1;
		uint32_t reserved_14:18;
	};
	uint32_t val;
} i2c_scl_stretch_conf_reg_t;


typedef union {
	struct {
		uint32_t resp_rec:1;
		uint32_t slave_rw:1;
		uint32_t reserved_2:1;
		uint32_t arb_lost:1;
		uint32_t bus_busy:1;
		uint32_t slave_addressed:1;
		uint32_t reserved_6:2;
		uint32_t rxfifo_cnt:6;
		uint32_t stretch_cause:2;
		uint32_t reserved_16:2;
		uint32_t txfifo_cnt:6;
		uint32_t scl_main_state_last:3;
		uint32_t reserved_27:1;
		uint32_t scl_state_last:3;
		uint32_t reserved_31:1;
	};
	uint32_t val;
} i2c_sr_reg_t;

typedef union {
	struct {
		uint32_t rxfifo_raddr:5;
		uint32_t rxfifo_waddr:5;
		uint32_t txfifo_raddr:5;
		uint32_t txfifo_waddr:5;
		uint32_t reserved_20:2;
		uint32_t slave_rw_point:8;
		uint32_t reserved_30:2;
	};
	uint32_t val;
} i2c_fifo_st_reg_t;

typedef union {
	struct {
		uint32_t fifo_rdata:8;
		uint32_t reserved_8:24;
	};
	uint32_t val;
} i2c_data_reg_t;


typedef union {
	struct {
		uint32_t rxfifo_wm_int_raw:1;
		uint32_t txfifo_wm_int_raw:1;
		uint32_t rxfifo_ovf_int_raw:1;
		uint32_t end_detect_int_raw:1;
		uint32_t byte_trans_done_int_raw:1;
		uint32_t arbitration_lost_int_raw:1;
		uint32_t mst_txfifo_udf_int_raw:1;
		uint32_t trans_complete_int_raw:1;
		uint32_t time_out_int_raw:1;
		uint32_t trans_start_int_raw:1;
		uint32_t nack_int_raw:1;
		uint32_t txfifo_ovf_int_raw:1;
		uint32_t rxfifo_udf_int_raw:1;
		uint32_t scl_st_to_int_raw:1;
		uint32_t scl_main_st_to_int_raw:1;
		uint32_t det_start_int_raw:1;
		uint32_t slave_stretch_int_raw:1;
		uint32_t general_call_int_raw:1;
		uint32_t reserved_18:14;
	};
	uint32_t val;
} i2c_int_raw_reg_t;

typedef union {
	struct {
		uint32_t rxfifo_wm_int_clr:1;
		uint32_t txfifo_wm_int_clr:1;
		uint32_t rxfifo_ovf_int_clr:1;
		uint32_t end_detect_int_clr:1;
		uint32_t byte_trans_done_int_clr:1;
		uint32_t arbitration_lost_int_clr:1;
		uint32_t mst_txfifo_udf_int_clr:1;
		uint32_t trans_complete_int_clr:1;
		uint32_t time_out_int_clr:1;
		uint32_t trans_start_int_clr:1;
		uint32_t nack_int_clr:1;
		uint32_t txfifo_ovf_int_clr:1;
		uint32_t rxfifo_udf_int_clr:1;
		uint32_t scl_st_to_int_clr:1;
		uint32_t scl_main_st_to_int_clr:1;
		uint32_t det_start_int_clr:1;
		uint32_t slave_stretch_int_clr:1;
		uint32_t general_call_int_clr:1;
		uint32_t reserved_18:14;
	};
	uint32_t val;
} i2c_int_clr_reg_t;

typedef union {
	struct {
		uint32_t rxfifo_wm_int_ena:1;
		uint32_t txfifo_wm_int_ena:1;
		uint32_t rxfifo_ovf_int_ena:1;
		uint32_t end_detect_int_ena:1;
		uint32_t byte_trans_done_int_ena:1;
		uint32_t arbitration_lost_int_ena:1;
		uint32_t mst_txfifo_udf_int_ena:1;
		uint32_t trans_complete_int_ena:1;
		uint32_t time_out_int_ena:1;
		uint32_t trans_start_int_ena:1;
		uint32_t nack_int_ena:1;
		uint32_t txfifo_ovf_int_ena:1;
		uint32_t rxfifo_udf_int_ena:1;
		uint32_t scl_st_to_int_ena:1;
		uint32_t scl_main_st_to_int_ena:1;
		uint32_t det_start_int_ena:1;
		uint32_t slave_stretch_int_ena:1;
		uint32_t general_call_int_ena:1;
		uint32_t reserved_18:14;
	};
	uint32_t val;
} i2c_int_ena_reg_t;

typedef union {
	struct {
		uint32_t rxfifo_wm_int_st:1;
		uint32_t txfifo_wm_int_st:1;
		uint32_t rxfifo_ovf_int_st:1;
		uint32_t end_detect_int_st:1;
		uint32_t byte_trans_done_int_st:1;
		uint32_t arbitration_lost_int_st:1;
		uint32_t mst_txfifo_udf_int_st:1;
		uint32_t trans_complete_int_st:1;
		uint32_t time_out_int_st:1;
		uint32_t trans_start_int_st:1;
		uint32_t nack_int_st:1;
		uint32_t txfifo_ovf_int_st:1;
		uint32_t rxfifo_udf_int_st:1;
		uint32_t scl_st_to_int_st:1;
		uint32_t scl_main_st_to_int_st:1;
		uint32_t det_start_int_st:1;
		uint32_t slave_stretch_int_st:1;
		uint32_t general_call_int_st:1;
		uint32_t reserved_18:14;
	};
	uint32_t val;
} i2c_int_status_reg_t;


typedef union {
	struct {
		uint32_t command0:14;
		uint32_t reserved_14:17;
		uint32_t command0_done:1;
	};
	uint32_t val;
} i2c_comd0_reg_t;

typedef union {
	struct {
		uint32_t command1:14;
		uint32_t reserved_14:17;
		uint32_t command1_done:1;
	};
	uint32_t val;
} i2c_comd1_reg_t;

typedef union {
	struct {
		uint32_t command2:14;
		uint32_t reserved_14:17;
		uint32_t command2_done:1;
	};
	uint32_t val;
} i2c_comd2_reg_t;

typedef union {
	struct {
		uint32_t command3:14;
		uint32_t reserved_14:17;
		uint32_t command3_done:1;
	};
	uint32_t val;
} i2c_comd3_reg_t;

typedef union {
	struct {
		uint32_t command4:14;
		uint32_t reserved_14:17;
		uint32_t command4_done:1;
	};
	uint32_t val;
} i2c_comd4_reg_t;

typedef union {
	struct {
		uint32_t command5:14;
		uint32_t reserved_14:17;
		uint32_t command5_done:1;
	};
	uint32_t val;
} i2c_comd5_reg_t;

typedef union {
	struct {
		uint32_t command6:14;
		uint32_t reserved_14:17;
		uint32_t command6_done:1;
	};
	uint32_t val;
} i2c_comd6_reg_t;

typedef union {
	struct {
		uint32_t command7:14;
		uint32_t reserved_14:17;
		uint32_t command7_done:1;
	};
	uint32_t val;
} i2c_comd7_reg_t;


typedef union {
	struct {
		uint32_t date:32;
	};
	uint32_t val;
} i2c_date_reg_t;


typedef union {
	struct {
		uint32_t txfifo_start_addr:32;
	};
	uint32_t val;
} i2c_txfifo_start_addr_reg_t;

typedef union {
	struct {
		uint32_t rxfifo_start_addr:32;
	};
	uint32_t val;
} i2c_rxfifo_start_addr_reg_t;


typedef struct {
	volatile i2c_scl_low_period_reg_t scl_low_period;
	volatile i2c_ctr_reg_t ctr;
	volatile i2c_sr_reg_t sr;
	volatile i2c_to_reg_t to;
	volatile i2c_slave_addr_reg_t slave_addr;
	volatile i2c_fifo_st_reg_t fifo_st;
	volatile i2c_fifo_conf_reg_t fifo_conf;
	volatile i2c_data_reg_t data;
	volatile i2c_int_raw_reg_t int_raw;
	volatile i2c_int_clr_reg_t int_clr;
	volatile i2c_int_ena_reg_t int_ena;
	volatile i2c_int_status_reg_t int_status;
	volatile i2c_sda_hold_reg_t sda_hold;
	volatile i2c_sda_sample_reg_t sda_sample;
	volatile i2c_scl_high_period_reg_t scl_high_period;
	uint32_t reserved_03c;
	volatile i2c_scl_start_hold_reg_t scl_start_hold;
	volatile i2c_scl_rstart_setup_reg_t scl_rstart_setup;
	volatile i2c_scl_stop_hold_reg_t scl_stop_hold;
	volatile i2c_scl_stop_setup_reg_t scl_stop_setup;
	volatile i2c_filter_cfg_reg_t filter_cfg;
	volatile i2c_clk_conf_reg_t clk_conf;
	volatile i2c_comd0_reg_t comd0;
	volatile i2c_comd1_reg_t comd1;
	volatile i2c_comd2_reg_t comd2;
	volatile i2c_comd3_reg_t comd3;
	volatile i2c_comd4_reg_t comd4;
	volatile i2c_comd5_reg_t comd5;
	volatile i2c_comd6_reg_t comd6;
	volatile i2c_comd7_reg_t comd7;
	volatile i2c_scl_st_time_out_reg_t scl_st_time_out;
	volatile i2c_scl_main_st_time_out_reg_t scl_main_st_time_out;
	volatile i2c_scl_sp_conf_reg_t scl_sp_conf;
	volatile i2c_scl_stretch_conf_reg_t scl_stretch_conf;
	uint32_t reserved_088[28];
	volatile i2c_date_reg_t date;
	uint32_t reserved_0fc;
	volatile i2c_txfifo_start_addr_reg_t txfifo_start_addr;
	uint32_t reserved_104[31];
	volatile i2c_rxfifo_start_addr_reg_t rxfifo_start_addr;
} i2c_dev_t;

extern i2c_dev_t I2C0;
extern i2c_dev_t I2C1;

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

typedef enum {
	I2C_SCLK_DEFAULT = 0,    /*!< I2C source clock not selected*/
	I2C_SCLK_XTAL,           /*!< I2C source clock from XTAL, 40M */
	I2C_SCLK_RTC,            /*!< I2C source clock from 8M RTC, 8M */
	I2C_SCLK_REF_TICK,       /*!< I2C source clock from REF_TICK, 1M */
	I2C_SCLK_MAX,
} i2c_sclk_t;

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
