#include <stdbool.h>
#include <string.h>

typedef enum {
	ESP_AES_STATE_IDLE = 0, /* AES accelerator is idle */
	ESP_AES_STATE_BUSY,     /* Transform in progress */
	ESP_AES_STATE_DONE,     /* Transform completed */
} esp_aes_state_t;

typedef enum {
    ESP_AES_BLOCK_MODE_ECB = 0,
    ESP_AES_BLOCK_MODE_CBC,
    ESP_AES_BLOCK_MODE_OFB,
    ESP_AES_BLOCK_MODE_CTR,
    ESP_AES_BLOCK_MODE_CFB8,
    ESP_AES_BLOCK_MODE_CFB128,
    ESP_AES_BLOCK_MODE_GCM,
    ESP_AES_BLOCK_MODE_MAX,
} esp_aes_mode_t;

uint8_t aes_ll_write_key(const uint8_t *key, size_t key_word_len);
void aes_ll_set_mode(int mode, uint8_t key_bytes);
void aes_ll_write_block(const void *input);
void aes_ll_read_block(void *output);
void aes_ll_start_transform(void);
esp_aes_state_t aes_ll_get_state(void);
void aes_ll_set_block_mode(esp_aes_mode_t mode);
void aes_ll_set_inc(void);
void aes_ll_dma_exit(void);
void aes_ll_set_num_blocks(size_t num_blocks);
void aes_ll_set_iv(const uint8_t *iv);
void aes_ll_read_iv(uint8_t *iv);
void aes_ll_dma_enable(bool enable);
void aes_ll_interrupt_enable(bool enable);
void aes_ll_interrupt_clear(void);
