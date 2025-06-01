#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "aes.h"
#include "gpio.h"

#define ESP_AES_ENCRYPT     1
#define AES_BLOCK_WORDS     4
#define DR_REG_AES_BASE                         0x6003A000
#define IV_WORDS            (4)
/* AES Block operation modes (used with DMA) */
#define AES_BLOCK_MODE_ECB     0
#define AES_BLOCK_MODE_CBC     1
#define AES_BLOCK_MODE_OFB     2
#define AES_BLOCK_MODE_CTR     3
#define AES_BLOCK_MODE_CFB8    4
#define AES_BLOCK_MODE_CFB128  5

/* AES acceleration registers */
#define AES_MODE_REG            ((DR_REG_AES_BASE) + 0x40)
#define AES_ENDIAN_REG          ((DR_REG_AES_BASE) + 0x44)
#define AES_TRIGGER_REG         ((DR_REG_AES_BASE) + 0x48)
#define AES_STATE_REG           ((DR_REG_AES_BASE) + 0x4c)
#define AES_DMA_ENABLE_REG      ((DR_REG_AES_BASE) + 0x90)
#define AES_BLOCK_MODE_REG      ((DR_REG_AES_BASE) + 0x94)
#define AES_BLOCK_NUM_REG       ((DR_REG_AES_BASE) + 0x98)
#define AES_INC_SEL_REG         ((DR_REG_AES_BASE) + 0x9C)
#define AES_CONTINUE_REG        ((DR_REG_AES_BASE) + 0xA8)
#define AES_INT_CLR_REG         ((DR_REG_AES_BASE) + 0xAC)
#define AES_INT_ENA_REG         ((DR_REG_AES_BASE) + 0xB0)
#define AES_DATE_REG            ((DR_REG_AES_BASE) + 0xB4)
#define AES_DMA_EXIT_REG        ((DR_REG_AES_BASE) + 0xB8)

#define AES_DMA_ENABLE_REG      ((DR_REG_AES_BASE) + 0x90)
#define AES_BLOCK_MODE_REG      ((DR_REG_AES_BASE) + 0x94)
#define AES_BLOCK_NUM_REG       ((DR_REG_AES_BASE) + 0x98)
#define AES_INC_SEL_REG         ((DR_REG_AES_BASE) + 0x9C)
#define AES_AAD_BLOCK_NUM_REG   ((DR_REG_AES_BASE) + 0xA0)
#define AES_BIT_VALID_NUM_REG   ((DR_REG_AES_BASE) + 0xA4)
#define AES_CONTINUE_REG        ((DR_REG_AES_BASE) + 0xA8)

#define AES_KEY_BASE            ((DR_REG_AES_BASE) + 0x00)
#define AES_TEXT_IN_BASE        ((DR_REG_AES_BASE) + 0x20)
#define AES_TEXT_OUT_BASE       ((DR_REG_AES_BASE) + 0x30)
#define AES_IV_BASE             ((DR_REG_AES_BASE) + 0x50)



uint8_t aes_ll_write_key(const uint8_t *key, size_t key_word_len)
{
	/* This variable is used for fault injection checks, so marked volatile to avoid optimisation */
	volatile uint8_t key_in_hardware = 0;
	/* Memcpy to avoid potential unaligned access */
	uint32_t key_word;
	for (int i = 0; i < key_word_len; i++) {
		memcpy(&key_word, key + 4 * i, 4);
		REG_WRITE(AES_KEY_BASE + i * 4,  key_word);
		key_in_hardware += 4;
	}
	return key_in_hardware;
}

void aes_ll_set_mode(int mode, uint8_t key_bytes)
{
	const uint32_t MODE_DECRYPT_BIT = 4;
	unsigned mode_reg_base = (mode == ESP_AES_ENCRYPT) ? 0 : MODE_DECRYPT_BIT;

	/* See TRM for the mapping between keylength and mode bit */
	REG_WRITE(AES_MODE_REG, mode_reg_base + ((key_bytes / 8) - 2));
}

void aes_ll_write_block(const void *input)
{
	uint32_t input_word;

	for (int i = 0; i < AES_BLOCK_WORDS; i++) {
		memcpy(&input_word, (uint8_t*)input + 4 * i, 4);
		REG_WRITE(AES_TEXT_IN_BASE + i * 4, input_word);
	}
}

void aes_ll_read_block(void *output)
{
	uint32_t output_word;
	const size_t REG_WIDTH = sizeof(uint32_t);

	for (size_t i = 0; i < AES_BLOCK_WORDS; i++) {
		output_word = REG_READ(AES_TEXT_OUT_BASE + (i * REG_WIDTH));
		/* Memcpy to avoid potential unaligned access */
		memcpy( (uint8_t*)output + i * 4, &output_word, sizeof(output_word));
	}
}

void aes_ll_start_transform(void)
{
	REG_WRITE(AES_TRIGGER_REG, 1);
}


esp_aes_state_t aes_ll_get_state(void)
{
	return REG_READ(AES_STATE_REG);
}


void aes_ll_set_block_mode(esp_aes_mode_t mode)
{
	REG_WRITE(AES_BLOCK_MODE_REG, mode);
}

void aes_ll_set_inc(void)
{
	REG_WRITE(AES_INC_SEL_REG, 0);
}

void aes_ll_dma_exit(void)
{
	REG_WRITE(AES_DMA_EXIT_REG, 0);
}

void aes_ll_set_num_blocks(size_t num_blocks)
{
	REG_WRITE(AES_BLOCK_NUM_REG, num_blocks);
}

void aes_ll_set_iv(const uint8_t *iv)
{
	uint32_t *reg_addr_buf = (uint32_t *)(AES_IV_BASE);
	uint32_t iv_word;

	for (int i = 0; i < IV_WORDS; i++ ) {
		/* Memcpy to avoid potential unaligned access */
		memcpy(&iv_word, iv + 4 * i, sizeof(iv_word));
		REG_WRITE(&reg_addr_buf[i], iv_word);
	}
}

void aes_ll_read_iv(uint8_t *iv)
{
	uint32_t iv_word;
	const size_t REG_WIDTH = sizeof(uint32_t);

	for (size_t i = 0; i < IV_WORDS; i++) {
		iv_word = REG_READ(AES_IV_BASE + (i * REG_WIDTH));
		/* Memcpy to avoid potential unaligned access */
		memcpy(iv + i * 4, &iv_word, sizeof(iv_word));
	}
}

void aes_ll_dma_enable(bool enable)
{
	REG_WRITE(AES_DMA_ENABLE_REG, enable);
}

void aes_ll_interrupt_enable(bool enable)
{
	REG_WRITE(AES_INT_ENA_REG, enable);
}

void aes_ll_interrupt_clear(void)
{
	REG_WRITE(AES_INT_CLR_REG, 1);
}


