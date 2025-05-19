#include <stdint.h>
#include <stdbool.h>

#define TWAI_LL_STATUS_RBS      (0x1 << 0)      //Receive Buffer Status
#define TWAI_LL_STATUS_DOS      (0x1 << 1)      //Data Overrun Status
#define TWAI_LL_STATUS_TBS      (0x1 << 2)      //Transmit Buffer Status
#define TWAI_LL_STATUS_TCS      (0x1 << 3)      //Transmission Complete Status
#define TWAI_LL_STATUS_RS       (0x1 << 4)      //Receive Status
#define TWAI_LL_STATUS_TS       (0x1 << 5)      //Transmit Status
#define TWAI_LL_STATUS_ES       (0x1 << 6)      //Error Status
#define TWAI_LL_STATUS_BS       (0x1 << 7)      //Bus Status
#define TWAI_LL_STATUS_MS       (0x1 << 8)      //Miss Status

#define TWAI_LL_INTR_RI         (0x1 << 0)      //Receive Interrupt
#define TWAI_LL_INTR_TI         (0x1 << 1)      //Transmit Interrupt
#define TWAI_LL_INTR_EI         (0x1 << 2)      //Error Interrupt
#define TWAI_LL_INTR_EPI        (0x1 << 5)      //Error Passive Interrupt
#define TWAI_LL_INTR_ALI        (0x1 << 6)      //Arbitration Lost Interrupt
#define TWAI_LL_INTR_BEI        (0x1 << 7)      //Bus Error Interrupt

typedef union {
	struct {
		struct {
			uint8_t dlc: 4;				//Data length code (0 to 8) of the frame
			uint8_t self_reception: 1;	//This frame should be transmitted using self reception command
			uint8_t single_shot: 1;		//This frame should be transmitted using single shot command
			uint8_t rtr: 1;				//This frame is a remote transmission request
			uint8_t frame_format: 1;	//Format of the frame (1 = extended, 0 = standard)
		};
		union {
			struct {
				uint8_t id[2];			//11 bit standard frame identifier
				uint8_t data[8];		//Data bytes (0 to 8)
				uint8_t reserved8[2];
			} standard;
			struct {
				uint8_t id[4];			//29 bit extended frame identifier
				uint8_t data[8];		//Data bytes (0 to 8)
			} extended;
		};
	};
	uint8_t bytes[13];
} __attribute__((packed)) twai_ll_frame_buffer_t;

void twai_ll_enter_reset_mode(twai_dev_t *hw);
void twai_ll_exit_reset_mode(twai_dev_t *hw);
bool twai_ll_is_in_reset_mode(twai_dev_t *hw);
void twai_ll_set_mode(twai_dev_t *hw, twai_mode_t mode);
void twai_ll_set_cmd_tx(twai_dev_t *hw);
void twai_ll_set_cmd_tx_single_shot(twai_dev_t *hw);
void twai_ll_set_cmd_abort_tx(twai_dev_t *hw);
void twai_ll_set_cmd_release_rx_buffer(twai_dev_t *hw);
void twai_ll_set_cmd_clear_data_overrun(twai_dev_t *hw);
void twai_ll_set_cmd_self_rx_request(twai_dev_t *hw);
void twai_ll_set_cmd_self_rx_single_shot(twai_dev_t *hw);
uint32_t twai_ll_get_status(twai_dev_t *hw);
bool twai_ll_is_fifo_overrun(twai_dev_t *hw);
bool twai_ll_is_last_tx_successful(twai_dev_t *hw);
uint32_t twai_ll_get_and_clear_intrs(twai_dev_t *hw);
void twai_ll_set_enabled_intrs(twai_dev_t *hw, uint32_t intr_mask);
void twai_ll_set_bus_timing(twai_dev_t *hw, uint32_t brp, uint32_t sjw, uint32_t tseg1, uint32_t tseg2, bool triple_sampling);
void twai_ll_clear_arb_lost_cap(twai_dev_t *hw);
void twai_ll_clear_err_code_cap(twai_dev_t *hw);
void twai_ll_set_err_warn_lim(twai_dev_t *hw, uint32_t ewl);
uint32_t twai_ll_get_err_warn_lim(twai_dev_t *hw);
uint32_t twai_ll_get_rec(twai_dev_t *hw);
void twai_ll_set_rec(twai_dev_t *hw, uint32_t rec);
uint32_t twai_ll_get_tec(twai_dev_t *hw);
void twai_ll_set_tec(twai_dev_t *hw, uint32_t tec);
void twai_ll_set_acc_filter(twai_dev_t* hw, uint32_t code, uint32_t mask, bool single_filter);
void twai_ll_set_tx_buffer(twai_dev_t *hw, twai_ll_frame_buffer_t *tx_frame);
void twai_ll_get_rx_buffer(twai_dev_t *hw, twai_ll_frame_buffer_t *rx_frame);
void twai_ll_format_frame_buffer(uint32_t id, uint8_t dlc, const uint8_t *data, uint32_t flags, twai_ll_frame_buffer_t *tx_frame)
void twai_ll_prase_frame_buffer(twai_ll_frame_buffer_t *rx_frame, uint32_t *id, uint8_t *dlc, uint8_t *data, uint32_t *flags)
uint32_t twai_ll_get_rx_msg_count(twai_dev_t *hw);
void twai_ll_set_clkout(twai_dev_t *hw, uint32_t divider);
