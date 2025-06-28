#include <stdbool.h>

#define DR_REG_SHA_BASE                         0x6003B000

/* SHA acceleration registers */
#define SHA_MODE_REG                  ((DR_REG_SHA_BASE) + 0x00)
#define SHA_T_STRING_REG              ((DR_REG_SHA_BASE) + 0x04)
#define SHA_T_LENGTH_REG              ((DR_REG_SHA_BASE) + 0x08)
#define SHA_BLOCK_NUM_REG             ((DR_REG_SHA_BASE) + 0x0C)
#define SHA_START_REG                 ((DR_REG_SHA_BASE) + 0x10)
#define SHA_CONTINUE_REG              ((DR_REG_SHA_BASE) + 0x14)
#define SHA_BUSY_REG                  ((DR_REG_SHA_BASE) + 0x18)
#define SHA_DMA_START_REG             ((DR_REG_SHA_BASE) + 0x1C)
#define SHA_DMA_CONTINUE_REG          ((DR_REG_SHA_BASE) + 0x20)
#define SHA_CLEAR_IRQ_REG             ((DR_REG_SHA_BASE) + 0x24)
#define SHA_INT_ENA_REG               ((DR_REG_SHA_BASE) + 0x28)

#define SHA_H_BASE                    ((DR_REG_SHA_BASE) + 0x40)
#define SHA_TEXT_BASE                 ((DR_REG_SHA_BASE) + 0x80)



typedef enum {
	SHA1 = 0,
	SHA2_224,
	SHA2_256,
	SHA2_384,
	SHA2_512,
	SHA2_512224,
	SHA2_512256,
	SHA2_512T,
	SHA_TYPE_MAX
} SHA_TYPE;

typedef struct SHAContext {
	bool start;
	bool in_hardware;               // Is this context currently in peripheral? Needs to be manually cleared if multiple SHAs are interleaved
	SHA_TYPE type;
	uint32_t state[16];             // For SHA1/SHA224/SHA256, used 8, other used 16
	unsigned char buffer[128];      // For SHA1/SHA224/SHA256, used 64, other used 128
	uint32_t total_bits[4];
} SHA_CTX;

typedef SHA_TYPE esp_sha_type;

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


void ets_sha_enable(void);
void ets_sha_disable(void);
int ets_sha_init(SHA_CTX *ctx, SHA_TYPE type);
int ets_sha_starts(SHA_CTX *ctx, uint16_t sha512_t);
void ets_sha_get_state(SHA_CTX *ctx);
void ets_sha_process(SHA_CTX *ctx, const unsigned char *input);
void ets_sha_update(SHA_CTX *ctx, const unsigned char *input, uint32_t input_bytes, bool update_ctx);
int ets_sha_finish(SHA_CTX *ctx, unsigned char *output);

void esp_dport_access_read_buffer(uint32_t *buff_out, uint32_t address, uint32_t num_words);
