#include <stdint.h>
#include <stdbool.h>

#define SHA256_BLOCK_SZ 64
#define SHA256_DIGEST_SZ 32
#define DR_REG_HMAC_BASE                        0x6003E000

#define HMAC_SET_START_REG             ((DR_REG_HMAC_BASE) + 0x40)
#define HMAC_SET_PARA_PURPOSE_REG      ((DR_REG_HMAC_BASE) + 0x44)
#define HMAC_SET_PARA_KEY_REG          ((DR_REG_HMAC_BASE) + 0x48)
#define HMAC_SET_RESULT_FINISH_REG     ((DR_REG_HMAC_BASE) + 0x5c)
#define HMAC_SET_PARA_KEY_REG          ((DR_REG_HMAC_BASE) + 0x48)
#define HMAC_SET_PARA_FINISH_REG       ((DR_REG_HMAC_BASE) + 0x4c)
#define HMAC_QUERY_ERROR_REG           ((DR_REG_HMAC_BASE) + 0x68)
#define HMAC_QUERY_BUSY_REG            ((DR_REG_HMAC_BASE) + 0x6c)
#define HMAC_WDATA_BASE                ((DR_REG_HMAC_BASE) + 0x80)
#define HMAC_RDATA_BASE                ((DR_REG_HMAC_BASE) + 0xC0)
#define HMAC_SET_PARA_FINISH_REG       ((DR_REG_HMAC_BASE) + 0x4c)
#define HMAC_SET_MESSAGE_ONE_REG       ((DR_REG_HMAC_BASE) + 0x50)
#define HMAC_SET_MESSAGE_ING_REG       ((DR_REG_HMAC_BASE) + 0x54)
#define HMAC_SET_MESSAGE_END_REG       ((DR_REG_HMAC_BASE) + 0x58)
#define HMAC_SET_RESULT_FINISH_REG     ((DR_REG_HMAC_BASE) + 0x5c)
#define HMAC_SET_INVALIDATE_JTAG_REG   ((DR_REG_HMAC_BASE) + 0x60)
#define HMAC_SET_INVALIDATE_DS_REG     ((DR_REG_HMAC_BASE) + 0x64)
#define HMAC_SET_MESSAGE_PAD_REG       ((DR_REG_HMAC_BASE) + 0xF0)
#define HMAC_ONE_BLOCK_REG             ((DR_REG_HMAC_BASE) + 0xF4)

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
