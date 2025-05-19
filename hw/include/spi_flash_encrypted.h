#include <stdbool.h>
#include <string.h>

typedef enum
{
	FLASH_ENCRYPTION_MANU = 0, ///!< Manually encrypt the flash chip.
	PSRAM_ENCRYPTION_MANU = 1  ///!< Manually encrypt the psram chip.
} flash_encrypt_ll_type_t;

void spi_flash_encrypt_ll_enable(void);
void spi_flash_encrypt_ll_disable(void);
void spi_flash_encrypt_ll_type(flash_encrypt_ll_type_t type);
void spi_flash_encrypt_ll_buffer_length(uint32_t size);
void spi_flash_encrypt_ll_plaintext_save(uint32_t address, const uint32_t* buffer, uint32_t size);
void spi_flash_encrypt_ll_address_save(uint32_t flash_addr);
void spi_flash_encrypt_ll_calculate_start(void);
void spi_flash_encrypt_ll_calculate_wait_idle(void);
void spi_flash_encrypt_ll_done(void);
void spi_flash_encrypt_ll_destroy(void);
bool spi_flash_encrypt_ll_check(uint32_t address, uint32_t length);
