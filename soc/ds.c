#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "soc/ds.h"
#include "soc/gpio.h"

#define DR_REG_DIGITAL_SIGNATURE_BASE           0x6003D000
#define SOC_DS_SIGNATURE_MAX_BIT_LEN (4096)
#define SOC_DS_KEY_PARAM_MD_IV_LENGTH (16)

#define DS_C_BASE                 ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0x000 )
#define DS_C_Y_BASE               ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0x000 )
#define DS_C_M_BASE               ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0x200 )
#define DS_C_RB_BASE              ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0x400 )
#define DS_C_BOX_BASE             ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0x600 )
#define DS_IV_BASE                ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0x630 )
#define DS_X_BASE                 ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0x800 )
#define DS_Z_BASE                 ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0xA00 )

#define DS_SET_START_REG          ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0xE00)
#define DS_SET_ME_REG             ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0xE04)
#define DS_SET_FINISH_REG         ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0xE08)

#define DS_QUERY_BUSY_REG         ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0xE0C)
#define DS_QUERY_KEY_WRONG_REG    ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0xE10)
#define DS_QUERY_CHECK_REG        ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0xE14)

#define DS_QUERY_CHECK_INVALID_DIGEST  (1<<0)
#define DS_QUERY_CHECK_INVALID_PADDING (1<<1)

#define DS_DATE_REG               ((DR_REG_DIGITAL_SIGNATURE_BASE) + 0xE20)


void ds_ll_start(void)
{
	REG_WRITE(DS_SET_START_REG, 1);
}

bool ds_ll_busy(void)
{
	return (REG_READ(DS_QUERY_BUSY_REG) > 0) ? true : false;
}

void ds_ll_wait_busy(void)
{
	while (ds_ll_busy());
}

ds_key_check_t ds_ll_key_error_source(void)
{
	uint32_t key_error = REG_READ(DS_QUERY_KEY_WRONG_REG);
	if (key_error == 0) {
		return DS_NO_KEY_INPUT;
	} else {
		return DS_OTHER_WRONG;
	}
}

void ds_ll_configure_iv(const uint32_t *iv)
{
	for (size_t i = 0; i < (SOC_DS_KEY_PARAM_MD_IV_LENGTH / sizeof(uint32_t)); i++) {
		REG_WRITE(DS_IV_BASE + (i * 4), iv[i]);
	}
}

void ds_ll_write_message(const uint8_t *msg, size_t size)
{
	memcpy((uint8_t *) DS_X_BASE, msg, size);
}

void ds_ll_write_private_key_params(const uint8_t *encrypted_key_params)
{
	/* Note: as the internal peripheral still has RSA 4096 structure,
	   but C is encrypted based on the actual max RSA length (ETS_DS_MAX_BITS), need to fragment it
	   when copying to hardware...

	   (note if ETS_DS_MAX_BITS == 4096, this should be the same as copying data->c to hardware in one fragment)
	*/
	typedef struct {
		uint32_t addr;
		size_t len;
	} frag_t;
	const frag_t frags[] = {
		{DS_C_Y_BASE,  SOC_DS_SIGNATURE_MAX_BIT_LEN / 8},
		{DS_C_M_BASE,  SOC_DS_SIGNATURE_MAX_BIT_LEN / 8},
		{DS_C_RB_BASE, SOC_DS_SIGNATURE_MAX_BIT_LEN / 8},
		{DS_C_BOX_BASE, DS_IV_BASE - DS_C_BOX_BASE},
	};
	const size_t NUM_FRAGS = sizeof(frags) / sizeof(frag_t);
	const uint8_t *from = encrypted_key_params;

	for (int i = 0; i < NUM_FRAGS; i++) {
		memcpy((uint8_t *)frags[i].addr, from, frags[i].len);
		from += frags[i].len;
	}
}

void ds_ll_start_sign(void)
{
	REG_WRITE(DS_SET_ME_REG, 1);
}

ds_signature_check_t ds_ll_check_signature(void)
{
	uint32_t result = REG_READ(DS_QUERY_CHECK_REG);
	switch (result) {
	case 0:
		return DS_SIGNATURE_OK;
	case 1:
		return DS_SIGNATURE_MD_FAIL;
	case 2:
		return DS_SIGNATURE_PADDING_FAIL;
	default:
		return DS_SIGNATURE_PADDING_AND_MD_FAIL;
	}
}

void ds_ll_read_result(uint8_t *result, size_t size)
{
	memcpy(result, (uint8_t *) DS_Z_BASE, size);
}

void ds_ll_finish(void)
{
	REG_WRITE(DS_SET_FINISH_REG, 1);
	ds_ll_wait_busy();
}

