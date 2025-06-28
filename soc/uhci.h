#include <stdio.h>
#include <stdbool.h>

#define UHCI_LL_GET_HW(num) (((num) == 0) ? (&UHCI0) : (NULL))

typedef enum {
	UHCI_RX_BREAK_CHR_EOF = 0x1,
	UHCI_RX_IDLE_EOF      = 0x2,
	UHCI_RX_LEN_EOF       = 0x4,
	UHCI_RX_EOF_MAX       = 0x7,
} uhci_rxeof_cfg_t;

typedef volatile struct uhci_dev_s {
	union {
		struct {
			uint32_t tx_rst                        :    1;
			uint32_t rx_rst                        :    1;
			uint32_t uart0_ce                      :    1;
			uint32_t uart1_ce                      :    1;
			uint32_t uart2_ce                      :    1;
			uint32_t seper_en                      :    1;
			uint32_t head_en                       :    1;
			uint32_t crc_rec_en                    :    1;
			uint32_t uart_idle_eof_en              :    1;
			uint32_t len_eof_en                    :    1;
			uint32_t encode_crc_en                 :    1;
			uint32_t clk_en                        :    1;
			uint32_t uart_rx_brk_eof_en            :    1;
			uint32_t reserved13                    :    19;
		};
		uint32_t val;
	} conf0;
	union {
		struct {
			uint32_t rx_start                      :    1;
			uint32_t tx_start                      :    1;
			uint32_t rx_hung                       :    1;
			uint32_t tx_hung                       :    1;
			uint32_t send_s_q                      :    1;
			uint32_t send_a_q                      :    1;
			uint32_t outlink_eof_err               :    1;
			uint32_t app_ctrl0                     :    1;
			uint32_t app_ctrl1                     :    1;
			uint32_t reserved9                     :    23;
		};
		uint32_t val;
	} int_raw;
	union {
		struct {
			uint32_t rx_start                      :    1;
			uint32_t tx_start                      :    1;
			uint32_t rx_hung                       :    1;
			uint32_t tx_hung                       :    1;
			uint32_t send_s_q                      :    1;
			uint32_t send_a_q                      :    1;
			uint32_t outlink_eof_err               :    1;
			uint32_t app_ctrl0                     :    1;
			uint32_t app_ctrl1                     :    1;
			uint32_t reserved9                     :    23;
		};
		uint32_t val;
	} int_st;
	union {
		struct {
			uint32_t rx_start                      :    1;
			uint32_t tx_start                      :    1;
			uint32_t rx_hung                       :    1;
			uint32_t tx_hung                       :    1;
			uint32_t send_s_q                      :    1;
			uint32_t send_a_q                      :    1;
			uint32_t outlink_eof_err               :    1;
			uint32_t app_ctrl0                     :    1;
			uint32_t app_ctrl1                     :    1;
			uint32_t reserved9                     :    23;
		};
		uint32_t val;
	} int_ena;
	union {
		struct {
			uint32_t rx_start                      :    1;
			uint32_t tx_start                      :    1;
			uint32_t rx_hung                       :    1;
			uint32_t tx_hung                       :    1;
			uint32_t send_s_q                      :    1;
			uint32_t send_a_q                      :    1;
			uint32_t outlink_eof_err               :    1;
			uint32_t app_ctrl0                     :    1;
			uint32_t app_ctrl1                     :    1;
			uint32_t reserved9                     :    23;
		};
		uint32_t val;
	} int_clr;
	union {
		struct {
			uint32_t app_ctrl0_int_set             :    1;
			uint32_t app_ctrl1_int_set             :    1;
			uint32_t reserved2                     :    30;
		};
		uint32_t val;
	} app_int_set;
	union {
		struct {
			uint32_t check_sum_en                  :    1;
			uint32_t check_seq_en                  :    1;
			uint32_t crc_disable                   :    1;
			uint32_t save_head                     :    1;
			uint32_t tx_check_sum_re               :    1;
			uint32_t tx_ack_num_re                 :    1;
			uint32_t reserved6                     :    1;
			uint32_t wait_sw_start                 :    1;
			uint32_t sw_start                      :    1;
			uint32_t reserved9                     :    12;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} conf1;
	union {
		struct {
			uint32_t rx_err_cause                  :    3;
			uint32_t decode_state                  :    3;
			uint32_t reserved6                     :    26;
		};
		uint32_t val;
	} state0;
	union {
		struct {
			uint32_t encode_state                  :    3;
			uint32_t reserved3                     :    29;
		};
		uint32_t val;
	} state1;
	union {
		struct {
			uint32_t tx_c0_esc_en                  :    1;
			uint32_t tx_db_esc_en                  :    1;
			uint32_t tx_11_esc_en                  :    1;
			uint32_t tx_13_esc_en                  :    1;
			uint32_t rx_c0_esc_en                  :    1;
			uint32_t rx_db_esc_en                  :    1;
			uint32_t rx_11_esc_en                  :    1;
			uint32_t rx_13_esc_en                  :    1;
			uint32_t reserved8                     :    24;
		};
		uint32_t val;
	} escape_conf;
	union {
		struct {
			uint32_t txfifo_timeout                :    8;
			uint32_t txfifo_timeout_shift          :    3;
			uint32_t txfifo_timeout_ena            :    1;
			uint32_t rxfifo_timeout                :    8;
			uint32_t rxfifo_timeout_shift          :    3;
			uint32_t rxfifo_timeout_ena            :    1;
			uint32_t reserved24                    :    8;
		};
		uint32_t val;
	} hung_conf;
	union {
		struct {
			uint32_t ack_num                       :    3;
			uint32_t ack_num_load                  :    1;
			uint32_t reserved4                     :    28;
		};
		uint32_t val;
	} ack_num;
	uint32_t rx_head;
	union {
		struct {
			uint32_t single_send_num               :    3;
			uint32_t single_send_en                :    1;
			uint32_t always_send_num               :    3;
			uint32_t always_send_en                :    1;
			uint32_t reserved8                     :    24;
		};
		uint32_t val;
	} quick_sent;
	struct {
		uint32_t word[2];
	} q_data[7];
	union {
		struct {
			uint32_t seper_char                    :    8;
			uint32_t seper_esc_char0               :    8;
			uint32_t seper_esc_char1               :    8;
			uint32_t reserved24                    :    8;
		};
		uint32_t val;
	} esc_conf0;
	union {
		struct {
			uint32_t seq0                          :    8;
			uint32_t seq0_char0                    :    8;
			uint32_t seq0_char1                    :    8;
			uint32_t reserved24                    :    8;
		};
		uint32_t val;
	} esc_conf1;
	union {
		struct {
			uint32_t seq1                          :    8;
			uint32_t seq1_char0                    :    8;
			uint32_t seq1_char1                    :    8;
			uint32_t reserved24                    :    8;
		};
		uint32_t val;
	} esc_conf2;
	union {
		struct {
			uint32_t seq2                          :    8;
			uint32_t seq2_char0                    :    8;
			uint32_t seq2_char1                    :    8;
			uint32_t reserved24                    :    8;
		};
		uint32_t val;
	} esc_conf3;
	union {
		struct {
			uint32_t thrs                          :    13;
			uint32_t reserved13                    :    19;
		};
		uint32_t val;
	} pkt_thres;
	uint32_t date;
} uhci_dev_t;

typedef struct {
	uint8_t seper_chr;        /*!< escape sequence character */
	uint8_t sub_chr1;         /*!< escape sequence sub-character 1 */
	uint8_t sub_chr2;         /*!< escape sequence sub-character 2 */
	bool sub_chr_en;          /*!< enable use of sub-chaacter of escape sequence */
} uhci_seper_chr_t;

typedef struct {
	uint8_t xon_chr;          /*!< character for XON */
	uint8_t xon_sub1;         /*!< sub-character 1 for XON */
	uint8_t xon_sub2;         /*!< sub-character 2 for XON */
	uint8_t xoff_chr;         /*!< character 2 for XOFF */
	uint8_t xoff_sub1;        /*!< sub-character 1 for XOFF */
	uint8_t xoff_sub2;        /*!< sub-character 2 for XOFF */
	uint8_t flow_en;          /*!< enable use of software flow control */
} uhci_swflow_ctrl_sub_chr_t;


extern uhci_dev_t *UHCI0;
extern uhci_dev_t *UHCI1;


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
