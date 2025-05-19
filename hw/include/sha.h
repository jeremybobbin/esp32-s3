#include <stdbool.h>
#include "soc/hwcrypto_reg.h"
#include "hal/sha_types.h"
#include "soc/dport_reg.h"

void sha_ll_start_block(esp_sha_type sha_type);
void sha_ll_continue_block(esp_sha_type sha_type);
void sha_ll_start_dma(esp_sha_type sha_type);
void sha_ll_continue_dma(esp_sha_type sha_type);
void sha_ll_load(esp_sha_type sha_type);
void sha_ll_set_block_num(size_t num_blocks);
bool sha_ll_busy(void);
void sha_ll_fill_text_block(const void *input_text, size_t block_word_len);
void sha_ll_read_digest(esp_sha_type sha_type, void *digest_state, size_t digest_word_len);
void sha_ll_write_digest(esp_sha_type sha_type, void *digest_state, size_t digest_word_len);
void sha_ll_t_string_set(uint32_t t_string);
void sha_ll_t_len_set(uint8_t t_len);
