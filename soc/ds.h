#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
	DS_KEY_INPUT_OK = 0, /**< The decryption key is ready. */
	DS_NO_KEY_INPUT,     /**< Dependent peripheral providing key hasn't been activated. */
	DS_OTHER_WRONG,      /**< Dependent peripheral running but problem receiving the key. */
} ds_key_check_t;

typedef enum {
	DS_SIGNATURE_OK = 0,                    /**< Signature is valid and can be read. */
	DS_SIGNATURE_PADDING_FAIL = 1,          /**< Padding invalid, signature can be read if user wants it. */
	DS_SIGNATURE_MD_FAIL = 2,               /**< Message digest check failed, signature invalid. */
	DS_SIGNATURE_PADDING_AND_MD_FAIL = 3,   /**< Both padding and MD check failed. */
} ds_signature_check_t;

void ds_ll_start(void);
bool ds_ll_busy(void);
void ds_ll_wait_busy(void);
ds_key_check_t ds_ll_key_error_source(void);
void ds_ll_configure_iv(const uint32_t *iv);
void ds_ll_write_message(const uint8_t *msg, size_t size);
void ds_ll_write_private_key_params(const uint8_t *encrypted_key_params);
void ds_ll_start_sign(void);
ds_signature_check_t ds_ll_check_signature(void);
void ds_ll_read_result(uint8_t *result, size_t size);
void ds_ll_finish(void);
