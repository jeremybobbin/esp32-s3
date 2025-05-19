#include <stdint.h>
#include <stdbool.h>
#include "soc/hwcrypto_reg.h"

#define SHA256_BLOCK_SZ 64
#define SHA256_DIGEST_SZ 32

#define HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_JTAG 6
#define HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_DIGITAL_SIGNATURE 7
#define HMAC_LL_EFUSE_KEY_PURPOSE_UP 8
#define HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_ALL 5

typedef enum {
	HMAC_OUTPUT_USER = 0,           /**< Let user provide a message and read the HMAC result */
	HMAC_OUTPUT_DS = 1,             /**< HMAC is provided to the DS peripheral to decrypt DS private key parameters */
	HMAC_OUTPUT_JTAG_ENABLE = 2,    /**< HMAC is used to enable JTAG after soft-disabling it */
	HMAC_OUTPUT_ALL = 3             /**< HMAC is used for both as DS input for or enabling JTAG */
} hmac_hal_output_t;

void hmac_ll_start(void);
void hmac_ll_config_output(hmac_hal_output_t config);
void hmac_ll_config_hw_key_id(uint32_t key_id);
void hmac_ll_config_finish(void);
uint32_t hmac_ll_query_config_error(void);
void hmac_ll_wait_idle(void);
void hmac_ll_write_block_512(const uint32_t *block);
void hmac_ll_read_result_256(uint32_t *result);
void hmac_ll_clean(void);
void hmac_ll_msg_padding(void);
void hmac_ll_msg_end(void);
void hmac_ll_msg_one_block(void);
void hmac_ll_msg_continue(void);
void hmac_ll_calc_finish(void);
void hmac_hal_start(void);
uint32_t hmac_hal_configure(hmac_hal_output_t config, uint32_t key_id);
void hmac_hal_write_one_block_512(const void *block);
void hmac_hal_write_block_512(const void *block);
void hmac_hal_next_block_normal(void);
void hmac_hal_next_block_padding(void);
void hmac_hal_read_result_256(void *result);
void hmac_hal_clean(void);
