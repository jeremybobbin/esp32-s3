
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "soc/sha.h"
#include "soc/gpio.h"



void sha_ll_start_block(esp_sha_type sha_type)
{
	REG_WRITE(SHA_MODE_REG, sha_type);
	REG_WRITE(SHA_START_REG, 1);
}

void sha_ll_continue_block(esp_sha_type sha_type)
{
	REG_WRITE(SHA_MODE_REG, sha_type);
	REG_WRITE(SHA_CONTINUE_REG, 1);
}

void sha_ll_start_dma(esp_sha_type sha_type)
{
	REG_WRITE(SHA_MODE_REG, sha_type);
	REG_WRITE(SHA_DMA_START_REG, 1);
}

void sha_ll_continue_dma(esp_sha_type sha_type)
{
	REG_WRITE(SHA_MODE_REG, sha_type);
	REG_WRITE(SHA_DMA_CONTINUE_REG, 1);
}

void sha_ll_load(esp_sha_type sha_type)
{
}

void sha_ll_set_block_num(size_t num_blocks)
{
	REG_WRITE(SHA_BLOCK_NUM_REG, num_blocks);
}

bool sha_ll_busy(void)
{
	return REG_READ(SHA_BUSY_REG);
}

void sha_ll_fill_text_block(const void *input_text, size_t block_word_len)
{
	uint32_t *data_words = (uint32_t *)input_text;
	uint32_t *reg_addr_buf = (uint32_t *)(SHA_TEXT_BASE);

	for (size_t i = 0; i < block_word_len; i++) {
		REG_WRITE(&reg_addr_buf[i], data_words[i]);
	}
}

void sha_ll_read_digest(esp_sha_type sha_type, void *digest_state, size_t digest_word_len)
{
	uint32_t *digest_state_words = (uint32_t *)digest_state;

	esp_dport_access_read_buffer(digest_state_words, SHA_H_BASE, digest_word_len);
}

void sha_ll_write_digest(esp_sha_type sha_type, void *digest_state, size_t digest_word_len)
{
	uint32_t *digest_state_words = (uint32_t *)digest_state;
	uint32_t *reg_addr_buf = (uint32_t *)(SHA_H_BASE);

	for (size_t i = 0; i < digest_word_len; i++) {
		REG_WRITE(&reg_addr_buf[i], digest_state_words[i]);
	}
}

void sha_ll_t_string_set(uint32_t t_string)
{
	REG_WRITE(SHA_T_STRING_REG, t_string);
}

void sha_ll_t_len_set(uint8_t t_len)
{
	REG_WRITE(SHA_T_LENGTH_REG, t_len);
}

