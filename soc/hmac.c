#include "soc/hmac.h"
#include "soc/gpio.h"
#include <stddef.h>

#define SHA256_BLOCK_SZ 64
#define SHA256_DIGEST_SZ 32

#define HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_JTAG 6
#define HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_DIGITAL_SIGNATURE 7
#define HMAC_LL_EFUSE_KEY_PURPOSE_UP 8
#define HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_ALL 5


void hmac_ll_start(void)
{
	REG_WRITE(HMAC_SET_START_REG, 1);
}

void hmac_ll_config_output(hmac_hal_output_t config)
{
	switch(config) {
	case HMAC_OUTPUT_USER:
		REG_WRITE(HMAC_SET_PARA_PURPOSE_REG, HMAC_LL_EFUSE_KEY_PURPOSE_UP);
		break;
	case HMAC_OUTPUT_DS:
		REG_WRITE(HMAC_SET_PARA_PURPOSE_REG, HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_DIGITAL_SIGNATURE);
		break;
	case HMAC_OUTPUT_JTAG_ENABLE:
		REG_WRITE(HMAC_SET_PARA_PURPOSE_REG, HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_JTAG);
		break;
	case HMAC_OUTPUT_ALL:
		REG_WRITE(HMAC_SET_PARA_PURPOSE_REG, HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_ALL);
		break;
	default:
		; // do nothing, error will be indicated by hmac_hal_config_error()
	}
}

void hmac_ll_config_hw_key_id(uint32_t key_id)
{
	REG_WRITE(HMAC_SET_PARA_KEY_REG, key_id);
}

void hmac_ll_config_finish(void)
{
	REG_WRITE(HMAC_SET_PARA_FINISH_REG, 1);
}

uint32_t hmac_ll_query_config_error(void)
{
	return REG_READ(HMAC_QUERY_ERROR_REG);
}

void hmac_ll_wait_idle(void)
{
	uint32_t query;
	do {
		query = REG_READ(HMAC_QUERY_BUSY_REG);
	} while(query != 0);
}

void hmac_ll_write_block_512(const uint32_t *block)
{
	const size_t REG_WIDTH = sizeof(uint32_t);
	for (size_t i = 0; i < SHA256_BLOCK_SZ / REG_WIDTH; i++) {
		REG_WRITE(HMAC_WDATA_BASE + (i * REG_WIDTH), block[i]);
	}

	REG_WRITE(HMAC_SET_MESSAGE_ONE_REG, 1);
}

void hmac_ll_read_result_256(uint32_t *result)
{
	const size_t REG_WIDTH = sizeof(uint32_t);
	for (size_t i = 0; i < SHA256_DIGEST_SZ / REG_WIDTH; i++) {
		result[i] = REG_READ(HMAC_RDATA_BASE + (i * REG_WIDTH));
	}
}

void hmac_ll_clean(void)
{
	REG_WRITE(HMAC_SET_INVALIDATE_DS_REG, 1);
	REG_WRITE(HMAC_SET_INVALIDATE_JTAG_REG, 1);
}

void hmac_ll_msg_padding(void)
{
	REG_WRITE(HMAC_SET_MESSAGE_PAD_REG, 1);
}

void hmac_ll_msg_end(void)
{
	REG_WRITE(HMAC_SET_MESSAGE_END_REG, 1);
}

void hmac_ll_msg_one_block(void)
{
	REG_WRITE(HMAC_ONE_BLOCK_REG, 1);
}

void hmac_ll_msg_continue(void)
{
	REG_WRITE(HMAC_SET_MESSAGE_ING_REG, 1);
}

void hmac_ll_calc_finish(void)
{
	REG_WRITE(HMAC_SET_RESULT_FINISH_REG, 2);
}



void hmac_hal_start(void)
{
	hmac_ll_wait_idle();
	hmac_ll_start();
}

uint32_t hmac_hal_configure(hmac_hal_output_t config, uint32_t key_id)
{
	hmac_ll_wait_idle();
	hmac_ll_config_output(config);
	hmac_ll_config_hw_key_id(key_id);
	hmac_ll_config_finish();
	hmac_ll_wait_idle();

	uint32_t conf_error = hmac_ll_query_config_error();
	if (conf_error) {
		hmac_ll_calc_finish();
		return 1;
	} else if (config != HMAC_OUTPUT_USER) {
		// In "downstream" mode, this will be the last hmac operation. Make sure HMAC is ready for
		// the other peripheral.
		hmac_ll_wait_idle();
	}

	return 0;
}

void hmac_hal_write_one_block_512(const void *block)
{
	hmac_ll_wait_idle();
	hmac_ll_write_block_512(block);
	hmac_ll_wait_idle();
	hmac_ll_msg_one_block();
}

void hmac_hal_write_block_512(const void *block)
{
	hmac_ll_wait_idle();
	hmac_ll_write_block_512(block);
}

void hmac_hal_next_block_padding(void)
{
	hmac_ll_wait_idle();
	hmac_ll_msg_padding();
}

void hmac_hal_next_block_normal(void)
{
	hmac_ll_wait_idle();
	hmac_ll_msg_continue();
}

void hmac_hal_read_result_256(void *result)
{
	hmac_ll_wait_idle();
	hmac_ll_read_result_256(result);
	hmac_ll_calc_finish();
}

void hmac_hal_clean(void)
{
	hmac_ll_wait_idle();
	hmac_ll_clean();
}
