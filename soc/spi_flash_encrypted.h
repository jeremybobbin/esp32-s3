#include <stdbool.h>
#include <string.h>

typedef enum
{
	FLASH_ENCRYPTION_MANU = 0, ///!< Manually encrypt the flash chip.
	PSRAM_ENCRYPTION_MANU = 1  ///!< Manually encrypt the psram chip.
} flash_encrypt_ll_type_t;

#define DR_REG_EXT_MEM_ENC                      0x600CC000

#define SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL_REG          (DR_REG_SYSTEM_BASE + 0x4C)

#define SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL_REG          (DR_REG_SYSTEM_BASE + 0x4C)
/* SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: .*/
#define SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT    (1<<(3))
#define SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT_M  (1<<(3))
#define SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT_V  0x1
#define SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT_S  3

#define SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT    (1<<(0))
#define SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT_M  (1<<(0))
#define SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT_V  0x1
#define SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT_S  0

/* registers for RSA acceleration via Multiple Precision Integer ops */
#define RSA_MEM_M_BLOCK_BASE          ((DR_REG_RSA_BASE)+0x000)
/* RB & Z use the same memory block, depending on phase of operation */
#define RSA_MEM_RB_BLOCK_BASE         ((DR_REG_RSA_BASE)+0x200)
#define RSA_MEM_Z_BLOCK_BASE          ((DR_REG_RSA_BASE)+0x200)
#define RSA_MEM_Y_BLOCK_BASE          ((DR_REG_RSA_BASE)+0x400)
#define RSA_MEM_X_BLOCK_BASE          ((DR_REG_RSA_BASE)+0x600)

/* Configuration registers */
#define RSA_M_DASH_REG                (DR_REG_RSA_BASE + 0x800)
#define RSA_LENGTH_REG                (DR_REG_RSA_BASE + 0x804)
#define RSA_CONSTANT_TIME_REG         (DR_REG_RSA_BASE + 0x820)
#define RSA_SEARCH_OPEN_REG           (DR_REG_RSA_BASE + 0x824)
#define RSA_SEARCH_POS_REG            (DR_REG_RSA_BASE + 0x828)

/* Initialization registers */
#define RSA_QUERY_CLEAN_REG           (DR_REG_RSA_BASE + 0x808)

/* Calculation start registers */
#define RSA_MODEXP_START_REG          (DR_REG_RSA_BASE + 0x80c)
#define RSA_MOD_MULT_START_REG        (DR_REG_RSA_BASE + 0x810)
#define RSA_MULT_START_REG            (DR_REG_RSA_BASE + 0x814)

/* Interrupt registers */
#define RSA_QUERY_INTERRUPT_REG       (DR_REG_RSA_BASE + 0x818)
#define RSA_CLEAR_INTERRUPT_REG       (DR_REG_RSA_BASE + 0x81C)
#define RSA_INTERRUPT_REG             (DR_REG_RSA_BASE + 0x82C)

/* SHA acceleration registers */
#define SHA_MODE_REG                  ((DR_REG_SHA_BASE) + 0x00)
#define SHA_T_STRING_REG              ((DR_REG_SHA_BASE) + 0x04)
#define SHA_T_LENGTH_REG              ((DR_REG_SHA_BASE) + 0x08)
#define SHA_BLOCK_NUM_REG             ((DR_REG_SHA_BASE) + 0x0C)
#define SHA_START_REG                 ((DR_REG_SHA_BASE) + 0x10)
#define SHA_CONTINUE_REG              ((DR_REG_SHA_BASE) + 0x14)
#define SHA_BUSY_REG                  ((DR_REG_SHA_BASE) + 0x18)
#define SHA_DMA_START_REG             ((DR_REG_SHA_BASE) + 0x1C)
#define SHA_DMA_CONTINUE_REG          ((DR_REG_SHA_BASE) + 0x20)
#define SHA_CLEAR_IRQ_REG             ((DR_REG_SHA_BASE) + 0x24)
#define SHA_INT_ENA_REG               ((DR_REG_SHA_BASE) + 0x28)

#define SHA_H_BASE                    ((DR_REG_SHA_BASE) + 0x40)
#define SHA_TEXT_BASE                 ((DR_REG_SHA_BASE) + 0x80)

/* AES Block operation modes (used with DMA) */
#define AES_BLOCK_MODE_ECB     0
#define AES_BLOCK_MODE_CBC     1
#define AES_BLOCK_MODE_OFB     2
#define AES_BLOCK_MODE_CTR     3
#define AES_BLOCK_MODE_CFB8    4
#define AES_BLOCK_MODE_CFB128  5

/* AES acceleration registers */
#define AES_MODE_REG            ((DR_REG_AES_BASE) + 0x40)
#define AES_ENDIAN_REG          ((DR_REG_AES_BASE) + 0x44)
#define AES_TRIGGER_REG         ((DR_REG_AES_BASE) + 0x48)
#define AES_STATE_REG           ((DR_REG_AES_BASE) + 0x4c)
#define AES_DMA_ENABLE_REG      ((DR_REG_AES_BASE) + 0x90)
#define AES_BLOCK_MODE_REG      ((DR_REG_AES_BASE) + 0x94)
#define AES_BLOCK_NUM_REG       ((DR_REG_AES_BASE) + 0x98)
#define AES_INC_SEL_REG         ((DR_REG_AES_BASE) + 0x9C)
#define AES_CONTINUE_REG        ((DR_REG_AES_BASE) + 0xA8)
#define AES_INT_CLR_REG         ((DR_REG_AES_BASE) + 0xAC)
#define AES_INT_ENA_REG         ((DR_REG_AES_BASE) + 0xB0)
#define AES_DATE_REG            ((DR_REG_AES_BASE) + 0xB4)
#define AES_DMA_EXIT_REG        ((DR_REG_AES_BASE) + 0xB8)

#define AES_DMA_ENABLE_REG      ((DR_REG_AES_BASE) + 0x90)
#define AES_BLOCK_MODE_REG      ((DR_REG_AES_BASE) + 0x94)
#define AES_BLOCK_NUM_REG       ((DR_REG_AES_BASE) + 0x98)
#define AES_INC_SEL_REG         ((DR_REG_AES_BASE) + 0x9C)
#define AES_AAD_BLOCK_NUM_REG   ((DR_REG_AES_BASE) + 0xA0)
#define AES_BIT_VALID_NUM_REG   ((DR_REG_AES_BASE) + 0xA4)
#define AES_CONTINUE_REG        ((DR_REG_AES_BASE) + 0xA8)

#define AES_KEY_BASE            ((DR_REG_AES_BASE) + 0x00)
#define AES_TEXT_IN_BASE        ((DR_REG_AES_BASE) + 0x20)
#define AES_TEXT_OUT_BASE       ((DR_REG_AES_BASE) + 0x30)
#define AES_IV_BASE             ((DR_REG_AES_BASE) + 0x50)


/* HMAC Module */
#define HMAC_SET_START_REG             ((DR_REG_HMAC_BASE) + 0x40)
#define HMAC_SET_PARA_PURPOSE_REG      ((DR_REG_HMAC_BASE) + 0x44)
#define HMAC_SET_PARA_KEY_REG          ((DR_REG_HMAC_BASE) + 0x48)
#define HMAC_SET_PARA_FINISH_REG       ((DR_REG_HMAC_BASE) + 0x4c)
#define HMAC_SET_MESSAGE_ONE_REG       ((DR_REG_HMAC_BASE) + 0x50)
#define HMAC_SET_MESSAGE_ING_REG       ((DR_REG_HMAC_BASE) + 0x54)
#define HMAC_SET_MESSAGE_END_REG       ((DR_REG_HMAC_BASE) + 0x58)
#define HMAC_SET_RESULT_FINISH_REG     ((DR_REG_HMAC_BASE) + 0x5c)
#define HMAC_SET_INVALIDATE_JTAG_REG   ((DR_REG_HMAC_BASE) + 0x60)
#define HMAC_INVALIDATE_JTAG           BIT(0)
#define HMAC_SET_INVALIDATE_DS_REG     ((DR_REG_HMAC_BASE) + 0x64)
#define HMAC_QUERY_ERROR_REG           ((DR_REG_HMAC_BASE) + 0x68)
#define HMAC_QUERY_BUSY_REG            ((DR_REG_HMAC_BASE) + 0x6c)

#define HMAC_WDATA_BASE                ((DR_REG_HMAC_BASE) + 0x80)
#define HMAC_RDATA_BASE                ((DR_REG_HMAC_BASE) + 0xC0)
#define HMAC_SET_MESSAGE_PAD_REG       ((DR_REG_HMAC_BASE) + 0xF0)
#define HMAC_ONE_BLOCK_REG             ((DR_REG_HMAC_BASE) + 0xF4)
#define HMAC_SOFT_JTAG_CTRL_REG        ((DR_REG_HMAC_BASE) + 0xF8)
#define HMAC_SOFT_JTAG_CTRL            BIT((0)
#define HMAC_WR_JTAG_REG               ((DR_REG_HMAC_BASE) + 0xFC)

/* AES-XTS registers */
#define AES_XTS_PLAIN_BASE        ((DR_REG_EXT_MEM_ENC) + 0x00)
#define AES_XTS_SIZE_REG          ((DR_REG_EXT_MEM_ENC) + 0x40)
#define AES_XTS_DESTINATION_REG   ((DR_REG_EXT_MEM_ENC) + 0x44)
#define AES_XTS_PHYSICAL_ADDR_REG ((DR_REG_EXT_MEM_ENC) + 0x48)

#define AES_XTS_TRIGGER_REG       ((DR_REG_EXT_MEM_ENC) + 0x4C)
#define AES_XTS_RELEASE_REG       ((DR_REG_EXT_MEM_ENC) + 0x50)
#define AES_XTS_DESTROY_REG       ((DR_REG_EXT_MEM_ENC) + 0x54)
#define AES_XTS_STATE_REG         ((DR_REG_EXT_MEM_ENC) + 0x58)
#define AES_XTS_DATE_REG          ((DR_REG_EXT_MEM_ENC) + 0x5C)

/* Digital Signature registers*/
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



