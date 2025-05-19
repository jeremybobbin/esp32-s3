

// The Lowlevel layer for TWAI



#include <stdint.h>
#include <stdbool.h>
#include "esp_assert.h"
#include "hal/misc.h"
#include "hal/twai_types.h"
#include "soc/twai_periph.h"
#include "soc/twai_struct.h"

typedef union {
	struct {
		struct {
			uint8_t dlc: 4;             //Data length code (0 to 8) of the frame
			uint8_t self_reception: 1;  //This frame should be transmitted using self reception command
			uint8_t single_shot: 1;     //This frame should be transmitted using single shot command
			uint8_t rtr: 1;             //This frame is a remote transmission request
			uint8_t frame_format: 1;    //Format of the frame (1 = extended, 0 = standard)
		};
		union {
			struct {
				uint8_t id[2];          //11 bit standard frame identifier
				uint8_t data[8];        //Data bytes (0 to 8)
				uint8_t reserved8[2];
			} standard;
			struct {
				uint8_t id[4];          //29 bit extended frame identifier
				uint8_t data[8];        //Data bytes (0 to 8)
			} extended;
		};
	};
	uint8_t bytes[13];
} __attribute__((packed)) twai_ll_frame_buffer_t;

ESP_STATIC_ASSERT(sizeof(twai_ll_frame_buffer_t) == 13, "TX/RX buffer type should be 13 bytes");

void twai_ll_enter_reset_mode(twai_dev_t *hw)
{
	hw->mode_reg.rm = 1;
}

void twai_ll_exit_reset_mode(twai_dev_t *hw)
{
	hw->mode_reg.rm = 0;
}

bool twai_ll_is_in_reset_mode(twai_dev_t *hw)
{
	return hw->mode_reg.rm;
}

void twai_ll_set_mode(twai_dev_t *hw, twai_mode_t mode)
{
	if (mode == TWAI_MODE_NORMAL) {           //Normal Operating mode
		hw->mode_reg.lom = 0;
		hw->mode_reg.stm = 0;
	} else if (mode == TWAI_MODE_NO_ACK) {    //Self Test Mode (No Ack)
		hw->mode_reg.lom = 0;
		hw->mode_reg.stm = 1;
	} else if (mode == TWAI_MODE_LISTEN_ONLY) {       //Listen Only Mode
		hw->mode_reg.lom = 1;
		hw->mode_reg.stm = 0;
	}
}

void twai_ll_set_cmd_tx(twai_dev_t *hw)
{
	hw->command_reg.tr = 1;
}

void twai_ll_set_cmd_tx_single_shot(twai_dev_t *hw)
{
	hw->command_reg.val = 0x03; //Set command_reg.tr and command_reg.at simultaneously for single shot transmittion request
}

void twai_ll_set_cmd_abort_tx(twai_dev_t *hw)
{
	hw->command_reg.at = 1;
}

void twai_ll_set_cmd_release_rx_buffer(twai_dev_t *hw)
{
	hw->command_reg.rrb = 1;
}

void twai_ll_set_cmd_clear_data_overrun(twai_dev_t *hw)
{
	hw->command_reg.cdo = 1;
}

void twai_ll_set_cmd_self_rx_request(twai_dev_t *hw)
{
	hw->command_reg.srr = 1;
}

void twai_ll_set_cmd_self_rx_single_shot(twai_dev_t *hw)
{
	hw->command_reg.val = 0x12; //Set command_reg.srr and command_reg.at simultaneously for single shot self reception request
}

uint32_t twai_ll_get_status(twai_dev_t *hw)
{
	return hw->status_reg.val;
}

bool twai_ll_is_fifo_overrun(twai_dev_t *hw)
{
	return hw->status_reg.dos;
}

bool twai_ll_is_last_tx_successful(twai_dev_t *hw)
{
	return hw->status_reg.tcs;
}

uint32_t twai_ll_get_and_clear_intrs(twai_dev_t *hw)
{
	return hw->interrupt_reg.val;
}

void twai_ll_set_enabled_intrs(twai_dev_t *hw, uint32_t intr_mask)
{
	hw->interrupt_enable_reg.val = intr_mask;
}

void twai_ll_set_bus_timing(twai_dev_t *hw, uint32_t brp, uint32_t sjw, uint32_t tseg1, uint32_t tseg2, bool triple_sampling)
{
	hw->bus_timing_0_reg.brp = (brp / 2) - 1;
	hw->bus_timing_0_reg.sjw = sjw - 1;
	hw->bus_timing_1_reg.tseg1 = tseg1 - 1;
	hw->bus_timing_1_reg.tseg2 = tseg2 - 1;
	hw->bus_timing_1_reg.sam = triple_sampling;
}

void twai_ll_clear_arb_lost_cap(twai_dev_t *hw)
{
	(void)hw->arbitration_lost_captue_reg.val;
}

void twai_ll_clear_err_code_cap(twai_dev_t *hw)
{
	(void)hw->error_code_capture_reg.val;
}

void twai_ll_set_err_warn_lim(twai_dev_t *hw, uint32_t ewl)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->error_warning_limit_reg, ewl, ewl);
}

uint32_t twai_ll_get_err_warn_lim(twai_dev_t *hw)
{
	return hw->error_warning_limit_reg.val;
}

uint32_t twai_ll_get_rec(twai_dev_t *hw)
{
	return hw->rx_error_counter_reg.val;
}

void twai_ll_set_rec(twai_dev_t *hw, uint32_t rec)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->rx_error_counter_reg, rxerr, rec);
}

uint32_t twai_ll_get_tec(twai_dev_t *hw)
{
	return hw->tx_error_counter_reg.val;
}

void twai_ll_set_tec(twai_dev_t *hw, uint32_t tec)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->tx_error_counter_reg, txerr, tec);
}

void twai_ll_set_acc_filter(twai_dev_t* hw, uint32_t code, uint32_t mask, bool single_filter)
{
	uint32_t code_swapped = HAL_SWAP32(code);
	uint32_t mask_swapped = HAL_SWAP32(mask);
	for (int i = 0; i < 4; i++) {
		HAL_FORCE_MODIFY_U32_REG_FIELD(hw->acceptance_filter.acr[i], byte, ((code_swapped >> (i * 8)) & 0xFF));
		HAL_FORCE_MODIFY_U32_REG_FIELD(hw->acceptance_filter.amr[i], byte, ((mask_swapped >> (i * 8)) & 0xFF));
	}
	hw->mode_reg.afm = single_filter;
}

void twai_ll_set_tx_buffer(twai_dev_t *hw, twai_ll_frame_buffer_t *tx_frame)
{
	//Copy formatted frame into TX buffer
	for (int i = 0; i < 13; i++) {
		hw->tx_rx_buffer[i].val = tx_frame->bytes[i];
	}
}

void twai_ll_get_rx_buffer(twai_dev_t *hw, twai_ll_frame_buffer_t *rx_frame)
{
	//Copy RX buffer registers into frame
	for (int i = 0; i < 13; i++) {
		rx_frame->bytes[i] =  HAL_FORCE_READ_U32_REG_FIELD(hw->tx_rx_buffer[i], byte);
	}
}

void twai_ll_format_frame_buffer(uint32_t id, uint8_t dlc, const uint8_t *data,
											  uint32_t flags, twai_ll_frame_buffer_t *tx_frame)
{
	bool is_extd = flags & TWAI_MSG_FLAG_EXTD;
	bool is_rtr = flags & TWAI_MSG_FLAG_RTR;

	//Set frame information
	tx_frame->dlc = dlc;
	tx_frame->frame_format = is_extd;
	tx_frame->rtr = is_rtr;
	tx_frame->self_reception = (flags & TWAI_MSG_FLAG_SELF) ? 1 : 0;
	tx_frame->single_shot = (flags & TWAI_MSG_FLAG_SS) ? 1 : 0;

	//Set ID. The ID registers are big endian and left aligned, therefore a bswap will be required
	if (is_extd) {
		uint32_t id_temp = HAL_SWAP32((id & TWAI_EXTD_ID_MASK) << 3); //((id << 3) >> 8*(3-i))
		for (int i = 0; i < 4; i++) {
			tx_frame->extended.id[i] = (id_temp >> (8 * i)) & 0xFF;
		}
	} else {
		uint32_t id_temp =  HAL_SWAP16((id & TWAI_STD_ID_MASK) << 5); //((id << 5) >> 8*(1-i))
		for (int i = 0; i < 2; i++) {
			tx_frame->standard.id[i] = (id_temp >> (8 * i)) & 0xFF;
		}
	}

	uint8_t *data_buffer = (is_extd) ? tx_frame->extended.data : tx_frame->standard.data;
	if (!is_rtr) {  //Only copy data if the frame is a data frame (i.e not a remote frame)
		for (int i = 0; (i < dlc) && (i < TWAI_FRAME_MAX_DLC); i++) {
			data_buffer[i] = data[i];
		}
	}
}

void twai_ll_prase_frame_buffer(twai_ll_frame_buffer_t *rx_frame, uint32_t *id, uint8_t *dlc,
											 uint8_t *data, uint32_t *flags)
{
	//Copy frame information
	*dlc = rx_frame->dlc;
	uint32_t flags_temp = 0;
	flags_temp |= (rx_frame->frame_format) ? TWAI_MSG_FLAG_EXTD : 0;
	flags_temp |= (rx_frame->rtr) ? TWAI_MSG_FLAG_RTR : 0;
	flags_temp |= (rx_frame->dlc > TWAI_FRAME_MAX_DLC) ? TWAI_MSG_FLAG_DLC_NON_COMP : 0;
	*flags = flags_temp;

	//Copy ID. The ID registers are big endian and left aligned, therefore a bswap will be required
	if (rx_frame->frame_format) {
		uint32_t id_temp = 0;
		for (int i = 0; i < 4; i++) {
			id_temp |= rx_frame->extended.id[i] << (8 * i);
		}
		id_temp = HAL_SWAP32(id_temp) >> 3;  //((byte[i] << 8*(3-i)) >> 3)
		*id = id_temp & TWAI_EXTD_ID_MASK;
	} else {
		uint32_t id_temp = 0;
		for (int i = 0; i < 2; i++) {
			id_temp |= rx_frame->standard.id[i] << (8 * i);
		}
		id_temp = HAL_SWAP16(id_temp) >> 5;  //((byte[i] << 8*(1-i)) >> 5)
		*id = id_temp & TWAI_STD_ID_MASK;
	}

	uint8_t *data_buffer = (rx_frame->frame_format) ? rx_frame->extended.data : rx_frame->standard.data;
	//Only copy data if the frame is a data frame (i.e. not a remote frame)
	int data_length = (rx_frame->rtr) ? 0 : ((rx_frame->dlc > TWAI_FRAME_MAX_DLC) ? TWAI_FRAME_MAX_DLC : rx_frame->dlc);
	for (int i = 0; i < data_length; i++) {
		data[i] = data_buffer[i];
	}
	//Set remaining bytes of data to 0
	for (int i = data_length; i < TWAI_FRAME_MAX_DLC; i++) {
		data[i] = 0;
	}
}

uint32_t twai_ll_get_rx_msg_count(twai_dev_t *hw)
{
	return hw->rx_message_counter_reg.val;
}

void twai_ll_set_clkout(twai_dev_t *hw, uint32_t divider)
{
	if (divider >= 2 && divider <= 490) {
		hw->clock_divider_reg.co = 0;
		HAL_FORCE_MODIFY_U32_REG_FIELD(hw->clock_divider_reg, cd, (divider / 2) - 1);
	} else if (divider == 1) {
		//Setting the divider reg to max value (255) means a divider of 1
		hw->clock_divider_reg.co = 0;
		HAL_FORCE_MODIFY_U32_REG_FIELD(hw->clock_divider_reg, cd, 255);
	} else {
		hw->clock_divider_reg.co = 1;
		HAL_FORCE_MODIFY_U32_REG_FIELD(hw->clock_divider_reg, cd, 0);
	}
}

