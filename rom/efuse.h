#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "rom/rsa_pss.h"
#include "soc/efuse.h"

/** \defgroup efuse_APIs efuse APIs
  * @brief     ESP32 efuse read/write APIs
  * @attention
  *
  */

/** @addtogroup efuse_APIs
  * @{
  */


typedef struct ets_secure_boot_sig_block ets_secure_boot_sig_block_t;
typedef struct ets_secure_boot_signature ets_secure_boot_signature_t;
typedef struct ets_secure_boot_key_digests ets_secure_boot_key_digests_t;

typedef enum {
	SB_SUCCESS = 0x3A5A5AA5,
	SB_FAILED = 0x7533885E,
} secure_boot_status_t;

int ets_secure_boot_verify_bootloader(uint8_t *verified_hash, bool allow_key_revoke);

secure_boot_status_t ets_secure_boot_verify_bootloader_with_keys(uint8_t *verified_hash, const ets_secure_boot_key_digests_t *trusted_keys, bool stage_load);

secure_boot_status_t ets_secure_boot_verify_signature(const ets_secure_boot_signature_t *sig, const uint8_t *image_digest, const ets_secure_boot_key_digests_t *trusted_keys, uint8_t *verified_digest);

ETS_STATUS ets_secure_boot_read_key_digests(ets_secure_boot_key_digests_t *trusted_keys);

#define CRC_SIGN_BLOCK_LEN 1196
#define SIG_BLOCK_PADDING 4096
#define ETS_SECURE_BOOT_V2_SIGNATURE_MAGIC 0xE7

struct ets_secure_boot_sig_block {
	uint8_t magic_byte;
	uint8_t version;
	uint8_t _reserved1;
	uint8_t _reserved2;
	uint8_t image_digest[32];
	ets_rsa_pubkey_t key;
	uint8_t signature[384];
	uint32_t block_crc;
	uint8_t _padding[16];
};

#define SECURE_BOOT_NUM_BLOCKS 3

struct ets_secure_boot_signature {
	ets_secure_boot_sig_block_t block[SECURE_BOOT_NUM_BLOCKS];
	uint8_t _padding[4096 - (sizeof(ets_secure_boot_sig_block_t) * SECURE_BOOT_NUM_BLOCKS)];
};

#define MAX_KEY_DIGESTS 3

struct ets_secure_boot_key_digests {
	const void *key_digests[MAX_KEY_DIGESTS];
	bool allow_key_revoke;
};

#define ESP_ERR_EFUSE                              0x1600
#define ESP_OK_EFUSE_CNT                          (ESP_ERR_EFUSE + 0x01)
#define ESP_ERR_EFUSE_CNT_IS_FULL                 (ESP_ERR_EFUSE + 0x02)
#define ESP_ERR_EFUSE_REPEATED_PROG               (ESP_ERR_EFUSE + 0x03)
#define ESP_ERR_CODING                            (ESP_ERR_EFUSE + 0x04)
#define ESP_ERR_NOT_ENOUGH_UNUSED_KEY_BLOCKS      (ESP_ERR_EFUSE + 0x05)
#define ESP_ERR_DAMAGED_READING                   (ESP_ERR_EFUSE + 0x06)


/*
typedef struct {
    esp_efuse_block_t   efuse_block: 8;
    uint8_t             bit_start;
    uint16_t            bit_count;
} esp_efuse_desc_t;
*/


typedef enum {
	ESP_EFUSE_ROM_LOG_ALWAYS_ON,
	ESP_EFUSE_ROM_LOG_ON_GPIO_LOW,
	ESP_EFUSE_ROM_LOG_ON_GPIO_HIGH,
	ESP_EFUSE_ROM_LOG_ALWAYS_OFF
} esp_efuse_rom_log_scheme_t;

typedef enum {
	EFUSE_CODING_SCHEME_NONE    = 0,    /**< None */
	EFUSE_CODING_SCHEME_RS      = 3,    /**< Reed-Solomon coding */
} esp_efuse_coding_scheme_t;

typedef enum {
	ETS_EFUSE_KEY_PURPOSE_USER = 0,
	ETS_EFUSE_KEY_PURPOSE_RESERVED = 1,
	ETS_EFUSE_KEY_PURPOSE_XTS_AES_256_KEY_1 = 2,
	ETS_EFUSE_KEY_PURPOSE_XTS_AES_256_KEY_2 = 3,
	ETS_EFUSE_KEY_PURPOSE_XTS_AES_128_KEY = 4,
	ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_ALL = 5,
	ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_JTAG = 6,
	ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_DIGITAL_SIGNATURE = 7,
	ETS_EFUSE_KEY_PURPOSE_HMAC_UP = 8,
	ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST0 = 9,
	ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST1 = 10,
	ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST2 = 11,
	ETS_EFUSE_KEY_PURPOSE_MAX,
} ets_efuse_purpose_t;

typedef enum {
	ETS_EFUSE_BLOCK0 = 0,
	ETS_EFUSE_MAC_SPI_SYS_0 = 1,
	ETS_EFUSE_BLOCK_SYS_DATA = 2,
	ETS_EFUSE_BLOCK_USR_DATA = 3,
	ETS_EFUSE_BLOCK_KEY0 = 4,
	ETS_EFUSE_BLOCK_KEY1 = 5,
	ETS_EFUSE_BLOCK_KEY2 = 6,
	ETS_EFUSE_BLOCK_KEY3 = 7,
	ETS_EFUSE_BLOCK_KEY4 = 8,
	ETS_EFUSE_BLOCK_KEY5 = 9,
	ETS_EFUSE_BLOCK_KEY6 = 10,
	ETS_EFUSE_BLOCK_MAX,
} ets_efuse_block_t;


int esp_efuse_read_field_blob(const esp_efuse_desc_t* field[], void* dst, size_t dst_size_bits);
bool esp_efuse_read_field_bit(const esp_efuse_desc_t *field[]);
int esp_efuse_read_field_cnt(const esp_efuse_desc_t* field[], size_t* out_cnt);
int esp_efuse_write_field_blob(const esp_efuse_desc_t* field[], const void* src, size_t src_size_bits);
int esp_efuse_write_field_cnt(const esp_efuse_desc_t* field[], size_t cnt);
int esp_efuse_write_field_bit(const esp_efuse_desc_t* field[]);
int esp_efuse_set_write_protect(esp_efuse_block_t blk);
int esp_efuse_set_read_protect(esp_efuse_block_t blk);
int esp_efuse_get_field_size(const esp_efuse_desc_t* field[]);
uint32_t esp_efuse_read_reg(esp_efuse_block_t blk, unsigned int num_reg);
int esp_efuse_write_reg(esp_efuse_block_t blk, unsigned int num_reg, uint32_t val);
esp_efuse_coding_scheme_t esp_efuse_get_coding_scheme(esp_efuse_block_t blk);
int esp_efuse_read_block(esp_efuse_block_t blk, void* dst_key, size_t offset_in_bits, size_t size_bits);
int esp_efuse_write_block(esp_efuse_block_t blk, const void* src_key, size_t offset_in_bits, size_t size_bits);
uint32_t esp_efuse_get_pkg_ver(void);
void esp_efuse_reset(void);
int esp_efuse_disable_rom_download_mode(void);
int esp_efuse_set_rom_log_scheme(esp_efuse_rom_log_scheme_t log_scheme);
int esp_efuse_enable_rom_secure_download_mode(void);
uint32_t esp_efuse_read_secure_version(void);
bool esp_efuse_check_secure_version(uint32_t secure_version);
int esp_efuse_update_secure_version(uint32_t secure_version);
#if defined(BOOTLOADER_BUILD) && defined(CONFIG_EFUSE_VIRTUAL) && !defined(CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH)
void esp_efuse_init_virtual_mode_in_ram(void);
#endif
#ifdef CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH
void esp_efuse_init_virtual_mode_in_flash(uint32_t offset, uint32_t size);
#endif
int esp_efuse_batch_write_begin(void);
int esp_efuse_batch_write_cancel(void);
int esp_efuse_batch_write_commit(void);
bool esp_efuse_block_is_empty(esp_efuse_block_t block);
bool esp_efuse_get_key_dis_read(esp_efuse_block_t block);
int esp_efuse_set_key_dis_read(esp_efuse_block_t block);
bool esp_efuse_get_key_dis_write(esp_efuse_block_t block);
int esp_efuse_set_key_dis_write(esp_efuse_block_t block);
bool esp_efuse_key_block_unused(esp_efuse_block_t block);
bool esp_efuse_find_purpose(ets_efuse_purpose_t purpose, esp_efuse_block_t *block);
bool esp_efuse_get_keypurpose_dis_write(esp_efuse_block_t block);
ets_efuse_purpose_t esp_efuse_get_key_purpose(esp_efuse_block_t block);
const esp_efuse_desc_t **esp_efuse_get_purpose_field(esp_efuse_block_t block);
const esp_efuse_desc_t** esp_efuse_get_key(esp_efuse_block_t block);
int esp_efuse_set_key_purpose(esp_efuse_block_t block, ets_efuse_purpose_t purpose);
int esp_efuse_set_keypurpose_dis_write(esp_efuse_block_t block);
esp_efuse_block_t esp_efuse_find_unused_key_block(void);
unsigned esp_efuse_count_unused_key_blocks(void);
bool esp_efuse_get_digest_revoke(unsigned num_digest);
int esp_efuse_set_digest_revoke(unsigned num_digest);
bool esp_efuse_get_write_protect_of_digest_revoke(unsigned num_digest);
int esp_efuse_set_write_protect_of_digest_revoke(unsigned num_digest);
int esp_efuse_write_key(esp_efuse_block_t block, ets_efuse_purpose_t purpose, const void *key, size_t key_size_bytes);
int esp_efuse_write_keys(const ets_efuse_purpose_t purposes[], uint8_t keys[][32], unsigned number_of_keys);
int esp_secure_boot_read_key_digests(ets_secure_boot_key_digests_t *trusted_keys);
int esp_efuse_check_errors(void);



/**
 * @brief set timing accroding the apb clock, so no read error or write error happens.
 *
 * @param clock: apb clock in HZ, only accept 5M(in FPGA), 10M(in FPGA), 20M, 40M, 80M.
 *
 * @return : 0 if success, others if clock not accepted
 */
int ets_efuse_set_timing(uint32_t clock);

/**
 * @brief Enable efuse subsystem. Called after reset. Doesn't need to be called again.
 */
void ets_efuse_start(void);

/**
  * @brief  Efuse read operation: copies data from physical efuses to efuse read registers.
  *
  * @param  null
  *
  * @return : 0 if success, others if apb clock is not accepted
  */
int ets_efuse_read(void);

/**
  * @brief  Efuse write operation: Copies data from efuse write registers to efuse. Operates on a single block of efuses at a time.
  *
  * @note This function does not update read efuses, call ets_efuse_read() once all programming is complete.
  *
  * @return : 0 if success, others if apb clock is not accepted
  */
int ets_efuse_program(ets_efuse_block_t block);

/**
 * @brief Set all Efuse program registers to zero.
 *
 * Call this before writing new data to the program registers.
 */
void ets_efuse_clear_program_registers(void);

/**
 * @brief Program a block of key data to an efuse block
 *
 * @param key_block Block to read purpose for. Must be in range ETS_EFUSE_BLOCK_KEY0 to ETS_EFUSE_BLOCK_KEY6. Key block must be unused (@ref ets_efuse_key_block_unused).
 * @param purpose Purpose to set for this key. Purpose must be already unset.
 * @param data Pointer to data to write.
 * @param data_len Length of data to write.
 *
 * @note This function also calls ets_efuse_program() for the specified block, and for block 0 (setting the purpose)
 */
int ets_efuse_write_key(ets_efuse_block_t key_block, ets_efuse_purpose_t purpose, const void *data, size_t data_len);


/* @brief Return the address of a particular efuse block's first read register
 *
 * @param block Index of efuse block to look up
 *
 * @return 0 if block is invalid, otherwise a numeric read register address
 * of the first word in the block.
 */
uint32_t ets_efuse_get_read_register_address(ets_efuse_block_t block);

/**
 * @brief Return the current purpose set for an efuse key block
 *
 * @param key_block Block to read purpose for. Must be in range ETS_EFUSE_BLOCK_KEY0 to ETS_EFUSE_BLOCK_KEY6.
 */
ets_efuse_purpose_t ets_efuse_get_key_purpose(ets_efuse_block_t key_block);

/**
 * @brief Find a key block with the particular purpose set
 *
 * @param purpose Purpose to search for.
 * @param[out] key_block Pointer which will be set to the key block if found. Can be NULL, if only need to test the key block exists.
 * @return true if found, false if not found. If false, value at key_block pointer is unchanged.
 */
bool ets_efuse_find_purpose(ets_efuse_purpose_t purpose, ets_efuse_block_t *key_block);

/**
 * Return true if the key block is unused, false otherwise.
 *
 * An unused key block is all zero content, not read or write protected,
 * and has purpose 0 (ETS_EFUSE_KEY_PURPOSE_USER)
 *
 * @param key_block key block to check.
 *
 * @return true if key block is unused, false if key block or used
 * or the specified block index is not a key block.
 */
bool ets_efuse_key_block_unused(ets_efuse_block_t key_block);


/**
 * @brief Search for an unused key block and return the first one found.
 *
 * See @ref ets_efuse_key_block_unused for a description of an unused key block.
 *
 * @return First unused key block, or ETS_EFUSE_BLOCK_MAX if no unused key block is found.
 */
ets_efuse_block_t ets_efuse_find_unused_key_block(void);

/**
 * @brief Return the number of unused efuse key blocks (0-6)
 */
unsigned ets_efuse_count_unused_key_blocks(void);

/**
 * @brief Calculate Reed-Solomon Encoding values for a block of efuse data.
 *
 * @param data Pointer to data buffer (length 32 bytes)
 * @param rs_values Pointer to write encoded data to (length 12 bytes)
 */
void ets_efuse_rs_calculate(const void *data, void *rs_values);

/**
  * @brief  Read spi flash pads configuration from Efuse
  *
  * @return
  * - 0 for default SPI pins.
  * - 1 for default HSPI pins.
  * - Other values define a custom pin configuration mask. Pins are encoded as per the EFUSE_SPICONFIG_RET_SPICLK,
  *   EFUSE_SPICONFIG_RET_SPIQ, EFUSE_SPICONFIG_RET_SPID, EFUSE_SPICONFIG_RET_SPICS0, EFUSE_SPICONFIG_RET_SPIHD macros.
  *   WP pin (for quad I/O modes) is not saved in efuse and not returned by this function.
  */
uint32_t ets_efuse_get_spiconfig(void);

/**
  * @brief  Read spi flash wp pad from Efuse
  *
  * @return
  * - 0x3f for invalid.
  * - 0~46 is valid.
  */
uint32_t ets_efuse_get_wp_pad(void);

/**
 * @brief Read opi flash pads configuration from Efuse
 *
 * @return
 * - 0 for default SPI pins.
 * - Other values define a custom pin configuration mask. From the LSB, every 6 bits represent a GPIO number which stand for:
 *   DQS, D4, D5, D6, D7 accordingly.
 */
uint32_t ets_efuse_get_opiconfig(void);

/**
  * @brief  Read if download mode disabled from Efuse
  *
  * @return
  * - true for efuse disable download mode.
  * - false for efuse doesn't disable download mode.
  */
bool ets_efuse_download_modes_disabled(void);

/**
  * @brief  Read if legacy spi flash boot mode disabled from Efuse
  *
  * @return
  * - true for efuse disable legacy spi flash boot mode.
  * - false for efuse doesn't disable legacy spi flash boot mode.
  */
bool ets_efuse_legacy_spi_boot_mode_disabled(void);

/**
  * @brief  Read if uart print control value from Efuse
  *
  * @return
  * - 0 for uart force print.
  * - 1 for uart print when GPIO46 is low when digital reset.
  *   2 for uart print when GPIO46 is high when digital reset.
  *   3 for uart force slient
  */
uint32_t ets_efuse_get_uart_print_control(void);

/**
  * @brief  Read if USB-Serial-JTAG print during rom boot is disabled from Efuse
  *
  * @return
  * - 1 for efuse disable USB-Serial-JTAG print during rom boot.
  * - 0 for efuse doesn't disable USB-Serial-JTAG print during rom boot.
  */
uint32_t ets_efuse_usb_serial_jtag_print_is_disabled(void);

/**
  * @brief  Read if usb download mode disabled from Efuse
  *
  * (Also returns true if security download mode is enabled, as this mode
  * disables USB download.)
  *
  * @return
  * - true for efuse disable usb download mode.
  * - false for efuse doesn't disable usb download mode.
  */
bool ets_efuse_usb_download_mode_disabled(void);

/**
  * @brief  Read if tiny basic mode disabled from Efuse
  *
  * @return
  * - true for efuse disable tiny basic mode.
  * - false for efuse doesn't disable tiny basic mode.
  */
bool ets_efuse_tiny_basic_mode_disabled(void);

/**
  * @brief  Read if usb module disabled from Efuse
  *
  * @return
  * - true for efuse disable usb module.
  * - false for efuse doesn't disable usb module.
  */
bool ets_efuse_usb_module_disabled(void);

/**
  * @brief  Read if security download modes enabled from Efuse
  *
  * @return
  * - true for efuse enable security download mode.
  * - false for efuse doesn't enable security download mode.
  */
bool ets_efuse_security_download_modes_enabled(void);

/**
 * @brief Return true if secure boot is enabled in EFuse
 */
bool ets_efuse_secure_boot_enabled(void);

/**
 * @brief Return true if secure boot aggressive revoke is enabled in EFuse
 */
bool ets_efuse_secure_boot_aggressive_revoke_enabled(void);

/**
 * @brief Return true if cache encryption (flash, PSRAM, etc) is enabled from boot via EFuse
 */
bool ets_efuse_cache_encryption_enabled(void);

/**
 * @brief Return true if EFuse indicates an external phy needs to be used for USB
 */
bool ets_efuse_usb_use_ext_phy(void);

/**
 * @brief Return true if EFuse indicates USB device persistence is disabled
 */
bool ets_efuse_usb_force_nopersist(void);

/**
 * @brief Return true if OPI pins GPIO33-37 are powered by VDDSPI, otherwise by VDD33CPU
 */
bool ets_efuse_flash_opi_5pads_power_sel_vddspi(void);

/**
 * @brief Return true if EFuse indicates an opi flash is attached.
 */
bool ets_efuse_flash_opi_mode(void);

/**
 * @brief Return true if EFuse indicates to send a flash resume command.
 */
bool ets_efuse_force_send_resume(void);

/**
  * @brief  return the time in us ROM boot need wait flash to power on from Efuse
  *
  * @return
  * - uint32_t the time in us.
  */
uint32_t ets_efuse_get_flash_delay_us(void);

#define EFUSE_SPICONFIG_SPI_DEFAULTS 0
#define EFUSE_SPICONFIG_HSPI_DEFAULTS 1

#define EFUSE_SPICONFIG_RET_SPICLK_MASK         0x3f
#define EFUSE_SPICONFIG_RET_SPICLK_SHIFT        0
#define EFUSE_SPICONFIG_RET_SPICLK(ret)         (((ret) >> EFUSE_SPICONFIG_RET_SPICLK_SHIFT) & EFUSE_SPICONFIG_RET_SPICLK_MASK)

#define EFUSE_SPICONFIG_RET_SPIQ_MASK           0x3f
#define EFUSE_SPICONFIG_RET_SPIQ_SHIFT          6
#define EFUSE_SPICONFIG_RET_SPIQ(ret)           (((ret) >> EFUSE_SPICONFIG_RET_SPIQ_SHIFT) & EFUSE_SPICONFIG_RET_SPIQ_MASK)

#define EFUSE_SPICONFIG_RET_SPID_MASK           0x3f
#define EFUSE_SPICONFIG_RET_SPID_SHIFT          12
#define EFUSE_SPICONFIG_RET_SPID(ret)           (((ret) >> EFUSE_SPICONFIG_RET_SPID_SHIFT) & EFUSE_SPICONFIG_RET_SPID_MASK)

#define EFUSE_SPICONFIG_RET_SPICS0_MASK         0x3f
#define EFUSE_SPICONFIG_RET_SPICS0_SHIFT        18
#define EFUSE_SPICONFIG_RET_SPICS0(ret)         (((ret) >> EFUSE_SPICONFIG_RET_SPICS0_SHIFT) & EFUSE_SPICONFIG_RET_SPICS0_MASK)


#define EFUSE_SPICONFIG_RET_SPIHD_MASK          0x3f
#define EFUSE_SPICONFIG_RET_SPIHD_SHIFT         24
#define EFUSE_SPICONFIG_RET_SPIHD(ret)          (((ret) >> EFUSE_SPICONFIG_RET_SPIHD_SHIFT) & EFUSE_SPICONFIG_RET_SPIHD_MASK)

/**
 * @brief Enable JTAG temporarily by writing a JTAG HMAC "key" into
 * the JTAG_CTRL registers.
 *
 * Works if JTAG has been "soft" disabled by burning the EFUSE_SOFT_DIS_JTAG efuse.
 *
 * Will enable the HMAC module to generate a "downstream" HMAC value from a key already saved in efuse, and then write the JTAG HMAC "key" which will enable JTAG if the two keys match.
 *
 * @param jtag_hmac_key Pointer to a 32 byte array containing a valid key. Supplied by user.
 * @param key_block Index of a key block containing the source for this key.
 *
 * @return ETS_FAILED if HMAC operation fails or invalid parameter, ETS_OK otherwise. ETS_OK doesn't necessarily mean that JTAG was enabled.
 */
int ets_jtag_enable_temporarily(const uint8_t *jtag_hmac_key, ets_efuse_block_t key_block);

/**
  * @brief  A crc8 algorithm used for MAC addresses in efuse
  *
  * @param  unsigned char const *p : Pointer to original data.
  *
  * @param  unsigned int len : Data length in byte.
  *
  * @return unsigned char: Crc value.
  */
unsigned char esp_crc8(unsigned char const *p, unsigned int len);
