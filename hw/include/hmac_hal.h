#include <stdint.h>
#include <stdbool.h>

typedef enum {
	HMAC_OUTPUT_USER = 0,           /**< Let user provide a message and read the HMAC result */
	HMAC_OUTPUT_DS = 1,             /**< HMAC is provided to the DS peripheral to decrypt DS private key parameters */
	HMAC_OUTPUT_JTAG_ENABLE = 2,    /**< HMAC is used to enable JTAG after soft-disabling it */
	HMAC_OUTPUT_ALL = 3             /**< HMAC is used for both as DS input for or enabling JTAG */
} hmac_hal_output_t;

void hmac_hal_start(void);
uint32_t hmac_hal_configure(hmac_hal_output_t config, uint32_t key_id);
void hmac_hal_write_one_block_512(const void *block);
void hmac_hal_write_block_512(const void *block);
void hmac_hal_next_block_normal(void);
void hmac_hal_next_block_padding(void);
void hmac_hal_read_result_256(void *result);
void hmac_hal_clean(void);
