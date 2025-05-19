

// The Lowlevel layer for SPI Flash Encryption.

#include <stdbool.h>
#include <string.h>
#include "soc/system_reg.h"
#include "soc/hwcrypto_reg.h"
#include "soc/soc.h"
#include "hal/assert.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Choose type of chip you want to encrypt manully
typedef enum
{
	FLASH_ENCRYPTION_MANU = 0, ///!< Manually encrypt the flash chip.
	PSRAM_ENCRYPTION_MANU = 1  ///!< Manually encrypt the psram chip.
} flash_encrypt_ll_type_t;

static inline void spi_flash_encrypt_ll_enable(void)
{
	REG_SET_BIT(SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL_REG,
				SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT |
				SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT);
}

static inline void spi_flash_encrypt_ll_disable(void)
{
	REG_CLR_BIT(SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL_REG,
				SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT);
}

static inline void spi_flash_encrypt_ll_type(flash_encrypt_ll_type_t type)
{
	// Our hardware only support flash encryption
	HAL_ASSERT(type == FLASH_ENCRYPTION_MANU);
	REG_WRITE(AES_XTS_DESTINATION_REG, type);
}

static inline void spi_flash_encrypt_ll_buffer_length(uint32_t size)
{
	// Desired block should not be larger than the block size.
	REG_WRITE(AES_XTS_SIZE_REG, size >> 5);
}

static inline void spi_flash_encrypt_ll_plaintext_save(uint32_t address, const uint32_t* buffer, uint32_t size)
{
	uint32_t plaintext_offs = (address % 64);
	memcpy((void *)(AES_XTS_PLAIN_BASE + plaintext_offs), buffer, size);
}

static inline void spi_flash_encrypt_ll_address_save(uint32_t flash_addr)
{
	REG_WRITE(AES_XTS_PHYSICAL_ADDR_REG, flash_addr);
}

static inline void spi_flash_encrypt_ll_calculate_start(void)
{
	REG_WRITE(AES_XTS_TRIGGER_REG, 1);
}

static inline void spi_flash_encrypt_ll_calculate_wait_idle(void)
{
	while(REG_READ(AES_XTS_STATE_REG) == 0x1) {
	}
}

static inline void spi_flash_encrypt_ll_done(void)
{
	REG_WRITE(AES_XTS_RELEASE_REG, 1);
	while(REG_READ(AES_XTS_STATE_REG) != 0x3) {
	}
}

static inline void spi_flash_encrypt_ll_destroy(void)
{
	REG_WRITE(AES_XTS_DESTROY_REG, 1);
}

static inline bool spi_flash_encrypt_ll_check(uint32_t address, uint32_t length)
{
	return ((address % length) == 0) ? true : false;
}

#ifdef __cplusplus
}
#endif
