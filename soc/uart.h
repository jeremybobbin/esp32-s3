#include <stdint.h>
#include <stdbool.h>

#define DR_REG_UART_BASE                        0x60000000
#define REG_UART_BASE( i )  (DR_REG_UART_BASE + (i) * 0x10000 + ( (i) > 1 ? 0xe000 : 0 ) )
#define UART_FSM_STATUS_REG(i) (REG_UART_BASE(i) + 0x6c)
#define DR_REG_UART1_BASE                       0x60010000
#define DR_REG_UART2_BASE                       0x6002E000


#define UART_LL_FIFO_DEF_LEN  (SOC_UART_FIFO_LEN)
#define UART_LL_GET_HW(num) (((num) == 0) ? (&UART0) : (((num) == 1) ? (&UART1) : (&UART2)))

#define UART_LL_MIN_WAKEUP_THRESH (2)
#define UART_LL_INTR_MASK         (0x7ffff) //All interrupt mask

#define UART_LL_FSM_IDLE          (0x0)
#define UART_LL_FSM_TX_WAIT_SEND  (0xf)

#define  APB_CLK_FREQ_ROM                            (40*1000000)
#define  CPU_CLK_FREQ_ROM                            APB_CLK_FREQ_ROM
#define  UART_CLK_FREQ_ROM                           (40*1000000)
#define  EFUSE_CLK_FREQ_ROM                          (20*1000000)
#define  CPU_CLK_FREQ                                APB_CLK_FREQ
#define  APB_CLK_FREQ                                (80*1000000)
#define  REF_CLK_FREQ                                (1000000)
#define  RTC_CLK_FREQ                                (20*1000000)
#define  XTAL_CLK_FREQ                               (40*1000000)
#define  UART_CLK_FREQ                               APB_CLK_FREQ
#define  WDT_CLK_FREQ                                APB_CLK_FREQ
#define  TIMER_CLK_FREQ                              (80000000>>4) //80MHz divided by 16
#define  SPI_CLK_DIV                                 4
#define  TICKS_PER_US_ROM                            40              // CPU is 80MHz
#define  GPIO_MATRIX_DELAY_NS                        0

#define UART_RX_TOUT_THRHD    0x000003FFU
#define UART_RX_TOUT_THRHD_M  (UART_RX_TOUT_THRHD_V << UART_RX_TOUT_THRHD_S)
#define UART_RX_TOUT_THRHD_V  0x000003FFU
#define UART_RX_TOUT_THRHD_S  17

#define UART_FORCE_XON    (1<<(2))
#define UART_FORCE_XON_M  (UART_FORCE_XON_V << UART_FORCE_XON_S)
#define UART_FORCE_XON_V  0x00000001U
#define UART_FORCE_XON_S  2
#define UART_FLOW_CONF_REG(i) (REG_UART_BASE(i) + 0x34)
#define UART_SW_FLOW_CON_EN    (1<<(0))
#define UART_SW_FLOW_CON_EN_M  (UART_SW_FLOW_CON_EN_V << UART_SW_FLOW_CON_EN_S)
#define UART_SW_FLOW_CON_EN_V  0x00000001U
#define UART_SW_FLOW_CON_EN_S  0

#define UART_FORCE_XON    (1<<(2))
#define UART_FORCE_XON_M  (UART_FORCE_XON_V << UART_FORCE_XON_S)
#define UART_FORCE_XON_V  0x00000001U
#define UART_FORCE_XON_S  2
/** UART_FORCE_XOFF : R/W; bitpos: [3]; default: 0;
 *  Set this bit to stop the  transmitter from sending data.
 */
#define UART_FORCE_XOFF    (1<<(3))
#define UART_FORCE_XOFF_M  (UART_FORCE_XOFF_V << UART_FORCE_XOFF_S)
#define UART_FORCE_XOFF_V  0x00000001U
#define UART_FORCE_XOFF_S  3
/** UART_SEND_XON : R/W/SS/SC; bitpos: [4]; default: 0;
 *  Set this bit to send Xon char. It is cleared by hardware automatically.
 */
#define UART_SEND_XON    (1<<(4))
#define UART_SEND_XON_M  (UART_SEND_XON_V << UART_SEND_XON_S)
#define UART_SEND_XON_V  0x00000001U
#define UART_SEND_XON_S  4
/** UART_SEND_XOFF : R/W/SS/SC; bitpos: [5]; default: 0;
 *  Set this bit to send Xoff char. It is cleared by hardware automatically.
 */
#define UART_SEND_XOFF    (BIT(5))
#define UART_SEND_XOFF_M  (UART_SEND_XOFF_V << UART_SEND_XOFF_S)
#define UART_SEND_XOFF_V  0x00000001U
#define UART_SEND_XOFF_S  5

#define UART_ST_UTX_OUT    0x0000000FU
#define UART_ST_UTX_OUT_M  (UART_ST_UTX_OUT_V << UART_ST_UTX_OUT_S)
#define UART_ST_UTX_OUT_V  0x0000000FU
#define UART_ST_UTX_OUT_S  4


typedef int uart_port_t;


typedef enum {
	UART_MODE_UART = 0x00,
	UART_MODE_RS485_HALF_DUPLEX = 0x01,
	UART_MODE_IRDA = 0x02,
	UART_MODE_RS485_COLLISION_DETECT = 0x03,
	UART_MODE_RS485_APP_CTRL = 0x04,
} uart_mode_t;


typedef enum {
	UART_DATA_5_BITS   = 0x0,
	UART_DATA_6_BITS   = 0x1,
	UART_DATA_7_BITS   = 0x2,
	UART_DATA_8_BITS   = 0x3,
	UART_DATA_BITS_MAX = 0x4,
} uart_word_length_t;


typedef enum {
	UART_STOP_BITS_1   = 0x1,
	UART_STOP_BITS_1_5 = 0x2,
	UART_STOP_BITS_2   = 0x3,
	UART_STOP_BITS_MAX = 0x4,
} uart_stop_bits_t;


typedef enum {
	UART_PARITY_DISABLE	 = 0x0,
	UART_PARITY_EVEN	 = 0x2,
	UART_PARITY_ODD		 = 0x3
} uart_parity_t;


typedef enum {
	UART_HW_FLOWCTRL_DISABLE = 0x0,
	UART_HW_FLOWCTRL_RTS	 = 0x1,
	UART_HW_FLOWCTRL_CTS	 = 0x2,
	UART_HW_FLOWCTRL_CTS_RTS = 0x3,
	UART_HW_FLOWCTRL_MAX	 = 0x4,
} uart_hw_flowcontrol_t;


typedef enum {
	UART_SIGNAL_INV_DISABLE	 =	0,
	UART_SIGNAL_IRDA_TX_INV	 = (0x1 << 0),
	UART_SIGNAL_IRDA_RX_INV	 = (0x1 << 1),
	UART_SIGNAL_RXD_INV		 = (0x1 << 2),
	UART_SIGNAL_CTS_INV		 = (0x1 << 3),
	UART_SIGNAL_DSR_INV		 = (0x1 << 4),
	UART_SIGNAL_TXD_INV		 = (0x1 << 5),
	UART_SIGNAL_RTS_INV		 = (0x1 << 6),
	UART_SIGNAL_DTR_INV		 = (0x1 << 7),
} uart_signal_inv_t;


typedef enum {
	UART_SCLK_APB = 0x0,
	UART_SCLK_RTC = 0x1,
	UART_SCLK_XTAL = 0x2,
} uart_sclk_t;


typedef struct {
	uint8_t	 cmd_char;
	uint8_t	 char_num;
	uint32_t gap_tout;
	uint32_t pre_idle;
	uint32_t post_idle;
} uart_at_cmd_t;


typedef struct {
	uint8_t	 xon_char;
	uint8_t	 xoff_char;
	uint8_t xon_thrd;
	uint8_t xoff_thrd;
} uart_sw_flowctrl_t;


typedef struct {
	int baud_rate;
	uart_word_length_t data_bits;
	uart_parity_t parity;
	uart_stop_bits_t stop_bits;
	uart_hw_flowcontrol_t flow_ctrl;
	uint8_t rx_flow_ctrl_thresh;
	uart_sclk_t source_clk;
} uart_config_t;


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

typedef union {
	struct {
		uint32_t rxfifo_rd_byte;
	};
	uint32_t val;
} uart_fifo_reg_t;

typedef union {
	struct {
		uint32_t reserved_0:1;
		uint32_t rx_size:3;
		uint32_t tx_size:3;
		uint32_t rx_flow_thrhd:10;
		uint32_t rx_tout_thrhd:10;
		uint32_t mem_force_pd:1;
		uint32_t mem_force_pu:1;
		uint32_t reserved_29:3;
	};
	uint32_t val;
} uart_mem_conf_reg_t;

typedef union {
	struct {
		uint32_t rxfifo_full_int_raw:1;
		uint32_t txfifo_empty_int_raw:1;
		uint32_t parity_err_int_raw:1;
		uint32_t frm_err_int_raw:1;
		uint32_t rxfifo_ovf_int_raw:1;
		uint32_t dsr_chg_int_raw:1;
		uint32_t cts_chg_int_raw:1;
		uint32_t brk_det_int_raw:1;
		uint32_t rxfifo_tout_int_raw:1;
		uint32_t sw_xon_int_raw:1;
		uint32_t sw_xoff_int_raw:1;
		uint32_t glitch_det_int_raw:1;
		uint32_t tx_brk_done_int_raw:1;
		uint32_t tx_brk_idle_done_int_raw:1;
		uint32_t tx_done_int_raw:1;
		uint32_t rs485_parity_err_int_raw:1;
		uint32_t rs485_frm_err_int_raw:1;
		uint32_t rs485_clash_int_raw:1;
		uint32_t at_cmd_char_det_int_raw:1;
		uint32_t wakeup_int_raw:1;
		uint32_t reserved_20:12;
	};
	uint32_t val;
} uart_int_raw_reg_t;

typedef union {
	struct {
		uint32_t rxfifo_full_int_st:1;
		uint32_t txfifo_empty_int_st:1;
		uint32_t parity_err_int_st:1;
		uint32_t frm_err_int_st:1;
		uint32_t rxfifo_ovf_int_st:1;
		uint32_t dsr_chg_int_st:1;
		uint32_t cts_chg_int_st:1;
		uint32_t brk_det_int_st:1;
		uint32_t rxfifo_tout_int_st:1;
		uint32_t sw_xon_int_st:1;
		uint32_t sw_xoff_int_st:1;
		uint32_t glitch_det_int_st:1;
		uint32_t tx_brk_done_int_st:1;
		uint32_t tx_brk_idle_done_int_st:1;
		uint32_t tx_done_int_st:1;
		uint32_t rs485_parity_err_int_st:1;
		uint32_t rs485_frm_err_int_st:1;
		uint32_t rs485_clash_int_st:1;
		uint32_t at_cmd_char_det_int_st:1;
		uint32_t wakeup_int_st:1;
		uint32_t reserved_20:12;
	};
	uint32_t val;
} uart_int_st_reg_t;

typedef union {
	struct {
		uint32_t rxfifo_full_int_ena:1;
		uint32_t txfifo_empty_int_ena:1;
		uint32_t parity_err_int_ena:1;
		uint32_t frm_err_int_ena:1;
		uint32_t rxfifo_ovf_int_ena:1;
		uint32_t dsr_chg_int_ena:1;
		uint32_t cts_chg_int_ena:1;
		uint32_t brk_det_int_ena:1;
		uint32_t rxfifo_tout_int_ena:1;
		uint32_t sw_xon_int_ena:1;
		uint32_t sw_xoff_int_ena:1;
		uint32_t glitch_det_int_ena:1;
		uint32_t tx_brk_done_int_ena:1;
		uint32_t tx_brk_idle_done_int_ena:1;
		uint32_t tx_done_int_ena:1;
		uint32_t rs485_parity_err_int_ena:1;
		uint32_t rs485_frm_err_int_ena:1;
		uint32_t rs485_clash_int_ena:1;
		uint32_t at_cmd_char_det_int_ena:1;
		uint32_t wakeup_int_ena:1;
		uint32_t reserved_20:12;
	};
	uint32_t val;
} uart_int_ena_reg_t;

typedef union {
	struct {
		uint32_t rxfifo_full_int_clr:1;
		uint32_t txfifo_empty_int_clr:1;
		uint32_t parity_err_int_clr:1;
		uint32_t frm_err_int_clr:1;
		uint32_t rxfifo_ovf_int_clr:1;
		uint32_t dsr_chg_int_clr:1;
		uint32_t cts_chg_int_clr:1;
		uint32_t brk_det_int_clr:1;
		uint32_t rxfifo_tout_int_clr:1;
		uint32_t sw_xon_int_clr:1;
		uint32_t sw_xoff_int_clr:1;
		uint32_t glitch_det_int_clr:1;
		uint32_t tx_brk_done_int_clr:1;
		uint32_t tx_brk_idle_done_int_clr:1;
		uint32_t tx_done_int_clr:1;
		uint32_t rs485_parity_err_int_clr:1;
		uint32_t rs485_frm_err_int_clr:1;
		uint32_t rs485_clash_int_clr:1;
		uint32_t at_cmd_char_det_int_clr:1;
		uint32_t wakeup_int_clr:1;
		uint32_t reserved_20:12;
	};
	uint32_t val;
} uart_int_clr_reg_t;

typedef union {
	struct {
		uint32_t clkdiv:12;
		uint32_t reserved_12:8;
		uint32_t clkdiv_frag:4;
		uint32_t reserved_24:8;
	};
	uint32_t val;
} uart_clkdiv_reg_t;

typedef union {
	struct {
		uint32_t glitch_filt:8;
		uint32_t glitch_filt_en:1;
		uint32_t reserved_9:23;
	};
	uint32_t val;
} uart_rx_filt_reg_t;

typedef union {
	struct {
		uint32_t parity:1;
		uint32_t parity_en:1;
		uint32_t bit_num:2;
		uint32_t stop_bit_num:2;
		uint32_t sw_rts:1;
		uint32_t sw_dtr:1;
		uint32_t txd_brk:1;
		uint32_t irda_dplx:1;
		uint32_t irda_tx_en:1;
		uint32_t irda_wctl:1;
		uint32_t irda_tx_inv:1;
		uint32_t irda_rx_inv:1;
		uint32_t loopback:1;
		uint32_t tx_flow_en:1;
		uint32_t irda_en:1;
		uint32_t rxfifo_rst:1;
		uint32_t txfifo_rst:1;
		uint32_t rxd_inv:1;
		uint32_t cts_inv:1;
		uint32_t dsr_inv:1;
		uint32_t txd_inv:1;
		uint32_t rts_inv:1;
		uint32_t dtr_inv:1;
		uint32_t clk_en:1;
		uint32_t err_wr_mask:1;
		uint32_t autobaud_en:1;
		uint32_t mem_clk_en:1;
		uint32_t reserved_29:3;
	};
	uint32_t val;
} uart_conf0_reg_t;

typedef union {
	struct {
		uint32_t rxfifo_full_thrhd:10;
		uint32_t txfifo_empty_thrhd:10;
		uint32_t dis_rx_dat_ovf:1;
		uint32_t rx_tout_flow_dis:1;
		uint32_t rx_flow_en:1;
		uint32_t rx_tout_en:1;
		uint32_t reserved_24:8;
	};
	uint32_t val;
} uart_conf1_reg_t;

typedef union {
	struct {
		uint32_t sw_flow_con_en:1;
		uint32_t xonoff_del:1;
		uint32_t force_xon:1;
		uint32_t force_xoff:1;
		uint32_t send_xon:1;
		uint32_t send_xoff:1;
		uint32_t reserved_6:26;
	};
	uint32_t val;
} uart_flow_conf_reg_t;

typedef union {
	struct {
		uint32_t active_threshold:10;
		uint32_t reserved_10:22;
	};
	uint32_t val;
} uart_sleep_conf_reg_t;

typedef union {
	struct {
		uint32_t xoff_threshold:10;
		uint32_t xoff_char:8;
		uint32_t reserved_18:14;
	};
	uint32_t val;
} uart_swfc_conf0_reg_t;

typedef union {
	struct {
		uint32_t xon_threshold:10;
		uint32_t xon_char:8;
		uint32_t reserved_18:14;
	};
	uint32_t val;
} uart_swfc_conf1_reg_t;

typedef union {
	struct {
		uint32_t tx_brk_num:8;
		uint32_t reserved_8:24;
	};
	uint32_t val;
} uart_txbrk_conf_reg_t;

typedef union {
	struct {
		uint32_t rx_idle_thrhd:10;
		uint32_t tx_idle_num:10;
		uint32_t reserved_20:12;
	};
	uint32_t val;
} uart_idle_conf_reg_t;

typedef union {
	struct {
		uint32_t rs485_en:1;
		uint32_t dl0_en:1;
		uint32_t dl1_en:1;
		uint32_t rs485tx_rx_en:1;
		uint32_t rs485rxby_tx_en:1;
		uint32_t rs485_rx_dly_num:1;
		uint32_t rs485_tx_dly_num:4;
		uint32_t reserved_10:22;
	};
	uint32_t val;
} uart_rs485_conf_reg_t;

typedef union {
	struct {
		uint32_t sclk_div_b:6;
		uint32_t sclk_div_a:6;
		uint32_t sclk_div_num:8;
		uint32_t sclk_sel:2;
		uint32_t sclk_en:1;
		uint32_t rst_core:1;
		uint32_t tx_sclk_en:1;
		uint32_t rx_sclk_en:1;
		uint32_t tx_rst_core:1;
		uint32_t rx_rst_core:1;
		uint32_t reserved_28:4;
	};
	uint32_t val;
} uart_clk_conf_reg_t;


typedef union {
	struct {
		uint32_t rxfifo_cnt:10;
		uint32_t reserved_10:3;
		uint32_t dsrn:1;
		uint32_t ctsn:1;
		uint32_t rxd:1;
		uint32_t txfifo_cnt:10;
		uint32_t reserved_26:3;
		uint32_t dtrn:1;
		uint32_t rtsn:1;
		uint32_t txd:1;
	};
	uint32_t val;
} uart_status_reg_t;

typedef union {
	struct {
		uint32_t apb_tx_waddr:10;
		uint32_t reserved_10:1;
		uint32_t tx_raddr:10;
		uint32_t reserved_21:11;
	};
	uint32_t val;
} uart_mem_tx_status_reg_t;

typedef union {
	struct {
		uint32_t apb_rx_raddr:10;
		uint32_t reserved_10:1;
		uint32_t rx_waddr:10;
		uint32_t reserved_21:11;
	};
	uint32_t val;
} uart_mem_rx_status_reg_t;

typedef union {
	struct {
		uint32_t st_urx_out:4;
		uint32_t st_utx_out:4;
		uint32_t reserved_8:24;
	};
	uint32_t val;
} uart_fsm_status_reg_t;


typedef union {
	struct {
		uint32_t lowpulse_min_cnt:12;
		uint32_t reserved_12:20;
	};
	uint32_t val;
} uart_lowpulse_reg_t;

typedef union {
	struct {
		uint32_t highpulse_min_cnt:12;
		uint32_t reserved_12:20;
	};
	uint32_t val;
} uart_highpulse_reg_t;

typedef union {
	struct {
		uint32_t rxd_edge_cnt:10;
		uint32_t reserved_10:22;
	};
	uint32_t val;
} uart_rxd_cnt_reg_t;

typedef union {
	struct {
		uint32_t posedge_min_cnt:12;
		uint32_t reserved_12:20;
	};
	uint32_t val;
} uart_pospulse_reg_t;

typedef union {
	struct {
		uint32_t negedge_min_cnt:12;
		uint32_t reserved_12:20;
	};
	uint32_t val;
} uart_negpulse_reg_t;


typedef union {
	struct {
		uint32_t pre_idle_num:16;
		uint32_t reserved_16:16;
	};
	uint32_t val;
} uart_at_cmd_precnt_reg_t;

typedef union {
	struct {
		uint32_t post_idle_num:16;
		uint32_t reserved_16:16;
	};
	uint32_t val;
} uart_at_cmd_postcnt_reg_t;

typedef union {
	struct {
		uint32_t rx_gap_tout:16;
		uint32_t reserved_16:16;
	};
	uint32_t val;
} uart_at_cmd_gaptout_reg_t;

typedef union {
	struct {
		uint32_t at_cmd_char:8;
		uint32_t char_num:8;
		uint32_t reserved_16:16;
	};
	uint32_t val;
} uart_at_cmd_char_reg_t;


typedef union {
	struct {
		uint32_t date:32;
	};
	uint32_t val;
} uart_date_reg_t;

typedef union {
	struct {
		uint32_t id:30;
		uint32_t high_speed:1;
		uint32_t reg_update:1;
	};
	uint32_t val;
} uart_id_reg_t;


typedef struct {
	volatile uart_fifo_reg_t fifo;
	volatile uart_int_raw_reg_t int_raw;
	volatile uart_int_st_reg_t int_st;
	volatile uart_int_ena_reg_t int_ena;
	volatile uart_int_clr_reg_t int_clr;
	volatile uart_clkdiv_reg_t clkdiv;
	volatile uart_rx_filt_reg_t rx_filt;
	volatile uart_status_reg_t status;
	volatile uart_conf0_reg_t conf0;
	volatile uart_conf1_reg_t conf1;
	volatile uart_lowpulse_reg_t lowpulse;
	volatile uart_highpulse_reg_t highpulse;
	volatile uart_rxd_cnt_reg_t rxd_cnt;
	volatile uart_flow_conf_reg_t flow_conf;
	volatile uart_sleep_conf_reg_t sleep_conf;
	volatile uart_swfc_conf0_reg_t swfc_conf0;
	volatile uart_swfc_conf1_reg_t swfc_conf1;
	volatile uart_txbrk_conf_reg_t txbrk_conf;
	volatile uart_idle_conf_reg_t idle_conf;
	volatile uart_rs485_conf_reg_t rs485_conf;
	volatile uart_at_cmd_precnt_reg_t at_cmd_precnt;
	volatile uart_at_cmd_postcnt_reg_t at_cmd_postcnt;
	volatile uart_at_cmd_gaptout_reg_t at_cmd_gaptout;
	volatile uart_at_cmd_char_reg_t at_cmd_char;
	volatile uart_mem_conf_reg_t mem_conf;
	volatile uart_mem_tx_status_reg_t mem_tx_status;
	volatile uart_mem_rx_status_reg_t mem_rx_status;
	volatile uart_fsm_status_reg_t fsm_status;
	volatile uart_pospulse_reg_t pospulse;
	volatile uart_negpulse_reg_t negpulse;
	volatile uart_clk_conf_reg_t clk_conf;
	volatile uart_date_reg_t date;
	volatile uart_id_reg_t id;
} uart_dev_t;

extern uart_dev_t UART0;
extern uart_dev_t UART1;
extern uart_dev_t UART2;


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
