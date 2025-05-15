#include <stdint.h>
#include <stdbool.h>

#define ETS_DS_IV_LEN 16

/* Length of parameter 'C' stored in flash */
#define ETS_DS_C_LEN (12672 / 8)

/* Encrypted ETS data. Recommended to store in flash in this format.
 */
typedef struct {
    /* RSA LENGTH register parameters
     * (number of words in RSA key & operands, minus one).
     *
     * Max value 127 (for RSA 4096).
     *
     * This value must match the length field encrypted and stored in 'c',
     * or invalid results will be returned. (The DS peripheral will
     * always use the value in 'c', not this value, so an attacker can't
     * alter the DS peripheral results this way, it will just truncate or
     * extend the message and the resulting signature in software.)
     */
    unsigned rsa_length;

    /* IV value used to encrypt 'c' */
    uint8_t iv[ETS_DS_IV_LEN];

    /* Encrypted Digital Signature parameters. Result of AES-CBC encryption
       of plaintext values. Includes an encrypted message digest.
    */
    uint8_t c[ETS_DS_C_LEN];
} ets_ds_data_t;

typedef enum {
    ETS_DS_OK,
    ETS_DS_INVALID_PARAM,   /* Supplied parameters are invalid */
    ETS_DS_INVALID_KEY,     /* HMAC peripheral failed to supply key */
    ETS_DS_INVALID_PADDING, /* 'c' decrypted with invalid padding */
    ETS_DS_INVALID_DIGEST,  /* 'c' decrypted with invalid digest */
} ets_ds_result_t;

void ets_ds_enable(void);

void ets_ds_disable(void);
ets_ds_result_t ets_ds_start_sign(const void *message, const ets_ds_data_t *data);
bool ets_ds_is_busy(void);

ets_ds_result_t ets_ds_finish_sign(void *signature, const ets_ds_data_t *data);

typedef struct {
    uint32_t Y[4096 / 32];
    uint32_t M[4096 / 32];
    uint32_t Rb[4096 / 32];
    uint32_t M_prime;
    uint32_t length;
} ets_ds_p_data_t;

typedef enum {
    ETS_DS_KEY_HMAC, /* The HMAC key (as stored in efuse) */
    ETS_DS_KEY_AES,  /* The AES key (as derived from HMAC key by HMAC peripheral in downstream mode) */
} ets_ds_key_t;

ets_ds_result_t ets_ds_encrypt_params(ets_ds_data_t *data, const void *iv, const ets_ds_p_data_t *p_data, const void *key, ets_ds_key_t key_type);
