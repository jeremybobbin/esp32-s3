#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "soc/hwcrypto_reg.h"
#include "soc/soc_caps.h"

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
