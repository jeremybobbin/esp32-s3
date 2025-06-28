#include <stdint.h>
#include <stdlib.h>

#include "soc/rtc.h"
#include "soc/rtc_cntl.h"

#define SOC_PHY_DIG_REGS_MEM_SIZE       (21*4)


#define PHY_TX_POWER_LOWEST LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 52)
#define CONFIG_ESP_PHY_MAX_TX_POWER 20

#define SYSTEM_WIFI_CLK_EN_REG SYSCON_WIFI_CLK_EN_REG
/* SYSTEM_WIFI_CLK_EN : R/W ;bitpos:[31:0] ;default: 32'hfffce030 ; */
/*description: */
#define SYSTEM_WIFI_CLK_EN 0x00FB9FCF
#define SYSTEM_WIFI_CLK_EN_M ((SYSTEM_WIFI_CLK_EN_V) << (SYSTEM_WIFI_CLK_EN_S))
#define SYSTEM_WIFI_CLK_EN_V 0x00FB9FCF
#define SYSTEM_WIFI_CLK_EN_S 0

/* Mask for all Wifi clock bits, 6 */
#define SYSTEM_WIFI_CLK_WIFI_EN  0x0
#define SYSTEM_WIFI_CLK_WIFI_EN_M  ((SYSTEM_WIFI_CLK_WIFI_EN_V)<<(SYSTEM_WIFI_CLK_WIFI_EN_S))
#define SYSTEM_WIFI_CLK_WIFI_EN_V  0x0
#define SYSTEM_WIFI_CLK_WIFI_EN_S  0
/* Mask for all Bluetooth clock bits, 11, 16, 17 */
#define SYSTEM_WIFI_CLK_BT_EN  0x0
#define SYSTEM_WIFI_CLK_BT_EN_M  ((SYSTEM_WIFI_CLK_BT_EN_V)<<(SYSTEM_WIFI_CLK_BT_EN_S))
#define SYSTEM_WIFI_CLK_BT_EN_V  0x0
#define SYSTEM_WIFI_CLK_BT_EN_S  0
/* Mask for clock bits used by both WIFI and Bluetooth, 0, 1, 2, 3, 7, 8, 9, 10, 19, 20, 21, 22, 23 */
#define SYSTEM_WIFI_CLK_WIFI_BT_COMMON_M 0x78078F

//bluetooth baseband bit11
#define SYSTEM_BT_BASEBAND_EN (1<<(11))
//bluetooth LC bit16 and bit17
#define SYSTEM_BT_LC_EN ((1<<(16)) | (1<<(17)))

/* Remaining single bit clock masks */
#define SYSTEM_WIFI_CLK_I2C_CLK_EN (1<<(5))
#define SYSTEM_WIFI_CLK_UNUSED_BIT12 (1<<(12))
#define SYSTEM_WIFI_CLK_SDIO_HOST_EN (1<<(13))
#define SYSTEM_WIFI_CLK_EMAC_EN (1<<(14))
#define SYSTEM_WIFI_CLK_RNG_EN (1<<(15))

#define SYSTEM_CORE_RST_EN_REG SYSTEM_WIFI_RST_EN_REG
#define SYSTEM_WIFI_RST_EN_REG SYSCON_WIFI_RST_EN_REG
/* SYSTEM_WIFI_RST : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define SYSTEM_WIFI_RST 0xFFFFFFFF
#define SYSTEM_WIFI_RST_M ((SYSTEM_WIFI_RST_V) << (SYSTEM_WIFI_RST_S))
#define SYSTEM_WIFI_RST_V 0xFFFFFFFF
#define SYSTEM_WIFI_RST_S 0

#define SYSTEM_WIFIBB_RST           (1<<(0))
#define SYSTEM_FE_RST               (1<<(1))
#define SYSTEM_WIFIMAC_RST          (1<<(2))
#define SYSTEM_BTBB_RST             (1<<(3))    /* Bluetooth Baseband */
#define SYSTEM_BTMAC_RST            (1<<(4))    /* deprecated */
#define SYSTEM_SDIO_RST             (1<<(5))
#define SYSTEM_EMAC_RST             (1<<(7))
#define SYSTEM_MACPWR_RST           (1<<(8))
#define SYSTEM_RW_BTMAC_RST         (1<<(9))    /* Bluetooth MAC */
#define SYSTEM_RW_BTLP_RST          (1<<(10))   /* Bluetooth Low Power Module */
#define SYSTEM_RW_BTMAC_REG_RST     (1<<(11))   /* Bluetooth MAC Regsiters */
#define SYSTEM_RW_BTLP_REG_RST      (1<<(12))   /* Bluetooth Low Power Registers */
#define SYSTEM_BTBB_REG_RST         (1<<(13))   /* Bluetooth Baseband Registers */

#define MODEM_RESET_FIELD_WHEN_PU   (SYSTEM_WIFIBB_RST       | \
                                     SYSTEM_FE_RST           | \
                                     SYSTEM_WIFIMAC_RST      | \
                                     SYSTEM_BTBB_RST         | \
                                     SYSTEM_BTMAC_RST        | \
                                     SYSTEM_RW_BTMAC_RST     | \
                                     SYSTEM_RW_BTMAC_REG_RST | \
                                     SYSTEM_BTBB_REG_RST)



typedef struct {
	uint8_t params[128];                    /*!< opaque PHY initialization parameters */
} esp_phy_init_data_t;

typedef struct {
	uint8_t version[4];                     /*!< PHY version */
	uint8_t mac[6];                         /*!< The MAC address of the station */
	uint8_t opaque[1894];                   /*!< calibration data */
} esp_phy_calibration_data_t;

typedef enum {
	PHY_RF_CAL_PARTIAL = 0x00000000,        /*!< Do part of RF calibration. This should be used after power-on reset. */
	PHY_RF_CAL_NONE    = 0x00000001,        /*!< Don't do any RF calibration. This mode is only suggested to be used after deep sleep reset. */
	PHY_RF_CAL_FULL    = 0x00000002         /*!< Do full RF calibration. Produces best results, but also consumes a lot of time and current. Suggested to be used once. */
} esp_phy_calibration_mode_t;

typedef struct {
	uint8_t control_info_checksum[4];     /*!< 4-byte control infomation checksum */
	uint8_t multiple_bin_checksum[4];     /*!< 4-byte multiple bin checksum */
	uint8_t check_algorithm;              /*!< check algorithm */
	uint8_t version;                      /*!< PHY init data bin version */
	uint8_t number;                       /*!< PHY init data bin number */
	uint8_t length[2];                    /*!< Length of each PHY init data bin */
	uint8_t reserved[19];                 /*!< 19-byte reserved  */
} __attribute__ ((packed)) phy_control_info_data_t;

typedef enum {
	ESP_PHY_INIT_DATA_TYPE_DEFAULT = 0,
	ESP_PHY_INIT_DATA_TYPE_SRRC,
	ESP_PHY_INIT_DATA_TYPE_FCC,
	ESP_PHY_INIT_DATA_TYPE_CE,
	ESP_PHY_INIT_DATA_TYPE_NCC,
	ESP_PHY_INIT_DATA_TYPE_KCC,
	ESP_PHY_INIT_DATA_TYPE_MIC,
	ESP_PHY_INIT_DATA_TYPE_IC,
	ESP_PHY_INIT_DATA_TYPE_ACMA,
	ESP_PHY_INIT_DATA_TYPE_ANATEL,
	ESP_PHY_INIT_DATA_TYPE_ISED,
	ESP_PHY_INIT_DATA_TYPE_WPC,
	ESP_PHY_INIT_DATA_TYPE_OFCA,
	ESP_PHY_INIT_DATA_TYPE_IFETEL,
	ESP_PHY_INIT_DATA_TYPE_RCM,
	ESP_PHY_INIT_DATA_TYPE_NUMBER,
} phy_init_data_type_t;

typedef enum {
	ESP_PARTITION_TYPE_APP = 0x00,       //!< Application partition type
	ESP_PARTITION_TYPE_DATA = 0x01,      //!< Data partition type
} esp_partition_type_t;

typedef enum {
	ESP_PARTITION_SUBTYPE_APP_FACTORY = 0x00,                                 //!< Factory application partition
	ESP_PARTITION_SUBTYPE_APP_OTA_MIN = 0x10,                                 //!< Base for OTA partition subtypes
	ESP_PARTITION_SUBTYPE_APP_OTA_0 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 0,  //!< OTA partition 0
	ESP_PARTITION_SUBTYPE_APP_OTA_1 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 1,  //!< OTA partition 1
	ESP_PARTITION_SUBTYPE_APP_OTA_2 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 2,  //!< OTA partition 2
	ESP_PARTITION_SUBTYPE_APP_OTA_3 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 3,  //!< OTA partition 3
	ESP_PARTITION_SUBTYPE_APP_OTA_4 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 4,  //!< OTA partition 4
	ESP_PARTITION_SUBTYPE_APP_OTA_5 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 5,  //!< OTA partition 5
	ESP_PARTITION_SUBTYPE_APP_OTA_6 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 6,  //!< OTA partition 6
	ESP_PARTITION_SUBTYPE_APP_OTA_7 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 7,  //!< OTA partition 7
	ESP_PARTITION_SUBTYPE_APP_OTA_8 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 8,  //!< OTA partition 8
	ESP_PARTITION_SUBTYPE_APP_OTA_9 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 9,  //!< OTA partition 9
	ESP_PARTITION_SUBTYPE_APP_OTA_10 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 10,//!< OTA partition 10
	ESP_PARTITION_SUBTYPE_APP_OTA_11 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 11,//!< OTA partition 11
	ESP_PARTITION_SUBTYPE_APP_OTA_12 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 12,//!< OTA partition 12
	ESP_PARTITION_SUBTYPE_APP_OTA_13 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 13,//!< OTA partition 13
	ESP_PARTITION_SUBTYPE_APP_OTA_14 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 14,//!< OTA partition 14
	ESP_PARTITION_SUBTYPE_APP_OTA_15 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 15,//!< OTA partition 15
	ESP_PARTITION_SUBTYPE_APP_OTA_MAX = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 16,//!< Max subtype of OTA partition
	ESP_PARTITION_SUBTYPE_APP_TEST = 0x20,                                    //!< Test application partition
	ESP_PARTITION_SUBTYPE_DATA_OTA = 0x00,                                    //!< OTA selection partition
	ESP_PARTITION_SUBTYPE_DATA_PHY = 0x01,                                    //!< PHY init data partition
	ESP_PARTITION_SUBTYPE_DATA_NVS = 0x02,                                    //!< NVS partition
	ESP_PARTITION_SUBTYPE_DATA_COREDUMP = 0x03,                               //!< COREDUMP partition
	ESP_PARTITION_SUBTYPE_DATA_NVS_KEYS = 0x04,                               //!< Partition for NVS keys
	ESP_PARTITION_SUBTYPE_DATA_EFUSE_EM = 0x05,                               //!< Partition for emulate eFuse bits
	ESP_PARTITION_SUBTYPE_DATA_UNDEFINED = 0x06,                              //!< Undefined (or unspecified) data partition
	ESP_PARTITION_SUBTYPE_DATA_ESPHTTPD = 0x80,                               //!< ESPHTTPD partition
	ESP_PARTITION_SUBTYPE_DATA_FAT = 0x81,                                    //!< FAT partition
	ESP_PARTITION_SUBTYPE_DATA_SPIFFS = 0x82,                                 //!< SPIFFS partition
	ESP_PARTITION_SUBTYPE_ANY = 0xff,                                         //!< Used to search for partitions with any subtype
} esp_partition_subtype_t;


typedef struct {
	void* flash_chip;            /*!< SPI flash chip on which the partition resides */
	esp_partition_type_t type;          /*!< partition type (app/data) */
	esp_partition_subtype_t subtype;    /*!< partition subtype */
	uint32_t address;                   /*!< starting address of the partition in flash */
	uint32_t size;                      /*!< size of the partition, in bytes */
	char label[17];                     /*!< partition label, zero-terminated ASCII string */
	bool encrypted;                     /*!< flag is set to true if partition is encrypted */
} esp_partition_t;

typedef uint32_t nvs_handle_t;

#define ESP_ERR_NVS_BASE					0x1100
#define ESP_ERR_NVS_NOT_INITIALIZED			(ESP_ERR_NVS_BASE + 0x01)
#define ESP_ERR_NVS_NOT_FOUND				(ESP_ERR_NVS_BASE + 0x02)
#define ESP_ERR_NVS_TYPE_MISMATCH			(ESP_ERR_NVS_BASE + 0x03)
#define ESP_ERR_NVS_READ_ONLY				(ESP_ERR_NVS_BASE + 0x04)
#define ESP_ERR_NVS_NOT_ENOUGH_SPACE		(ESP_ERR_NVS_BASE + 0x05)
#define ESP_ERR_NVS_INVALID_NAME			(ESP_ERR_NVS_BASE + 0x06)
#define ESP_ERR_NVS_INVALID_HANDLE			(ESP_ERR_NVS_BASE + 0x07)
#define ESP_ERR_NVS_REMOVE_FAILED			(ESP_ERR_NVS_BASE + 0x08)
#define ESP_ERR_NVS_KEY_TOO_LONG			(ESP_ERR_NVS_BASE + 0x09)
#define ESP_ERR_NVS_PAGE_FULL				(ESP_ERR_NVS_BASE + 0x0a)
#define ESP_ERR_NVS_INVALID_STATE			(ESP_ERR_NVS_BASE + 0x0b)
#define ESP_ERR_NVS_INVALID_LENGTH			(ESP_ERR_NVS_BASE + 0x0c)
#define ESP_ERR_NVS_NO_FREE_PAGES			(ESP_ERR_NVS_BASE + 0x0d)
#define ESP_ERR_NVS_VALUE_TOO_LONG			(ESP_ERR_NVS_BASE + 0x0e)
#define ESP_ERR_NVS_PART_NOT_FOUND			(ESP_ERR_NVS_BASE + 0x0f)

#define ESP_ERR_NVS_NEW_VERSION_FOUND		(ESP_ERR_NVS_BASE + 0x10)
#define ESP_ERR_NVS_XTS_ENCR_FAILED			(ESP_ERR_NVS_BASE + 0x11)
#define ESP_ERR_NVS_XTS_DECR_FAILED			(ESP_ERR_NVS_BASE + 0x12)
#define ESP_ERR_NVS_XTS_CFG_FAILED			(ESP_ERR_NVS_BASE + 0x13)
#define ESP_ERR_NVS_XTS_CFG_NOT_FOUND		(ESP_ERR_NVS_BASE + 0x14)
#define ESP_ERR_NVS_ENCR_NOT_SUPPORTED		(ESP_ERR_NVS_BASE + 0x15)
#define ESP_ERR_NVS_KEYS_NOT_INITIALIZED	(ESP_ERR_NVS_BASE + 0x16)
#define ESP_ERR_NVS_CORRUPT_KEY_PART		(ESP_ERR_NVS_BASE + 0x17)
#define ESP_ERR_NVS_WRONG_ENCRYPTION		(ESP_ERR_NVS_BASE + 0x19)

#define ESP_ERR_NVS_CONTENT_DIFFERS			(ESP_ERR_NVS_BASE + 0x18)

#define NVS_DEFAULT_PART_NAME				"nvs"

#define NVS_PART_NAME_MAX_SIZE				16
#define NVS_KEY_NAME_MAX_SIZE				16

typedef uint32_t nvs_handle_t;

typedef enum {
	NVS_READONLY,
	NVS_READWRITE
} nvs_open_mode_t;

typedef enum {
	NVS_TYPE_U8	   = 0x01,
	NVS_TYPE_I8	   = 0x11,
	NVS_TYPE_U16   = 0x02,
	NVS_TYPE_I16   = 0x12,
	NVS_TYPE_U32   = 0x04,
	NVS_TYPE_I32   = 0x14,
	NVS_TYPE_U64   = 0x08,
	NVS_TYPE_I64   = 0x18,
	NVS_TYPE_STR   = 0x21,
	NVS_TYPE_BLOB  = 0x42,
	NVS_TYPE_ANY   = 0xff
} nvs_type_t;


typedef struct {
	char namespace_name[16];
	char key[NVS_KEY_NAME_MAX_SIZE];
	nvs_type_t type;
} nvs_entry_info_t;


typedef struct nvs_opaque_iterator_t *nvs_iterator_t;


typedef struct {
	size_t used_entries;
	size_t free_entries;
	size_t total_entries;
	size_t namespace_count;
} nvs_stats_t;

int nvs_open(const char* name, nvs_open_mode_t open_mode, nvs_handle_t *out_handle);
int nvs_open_from_partition(const char *part_name, const char* name, nvs_open_mode_t open_mode, nvs_handle_t *out_handle);
int nvs_set_i8 (nvs_handle_t handle, const char* key, int8_t value);
int nvs_set_u8 (nvs_handle_t handle, const char* key, uint8_t value);
int nvs_set_i16 (nvs_handle_t handle, const char* key, int16_t value);
int nvs_set_u16 (nvs_handle_t handle, const char* key, uint16_t value);
int nvs_set_i32 (nvs_handle_t handle, const char* key, int32_t value);
int nvs_set_u32 (nvs_handle_t handle, const char* key, uint32_t value);
int nvs_set_i64 (nvs_handle_t handle, const char* key, int64_t value);
int nvs_set_u64 (nvs_handle_t handle, const char* key, uint64_t value);
int nvs_set_str (nvs_handle_t handle, const char* key, const char* value);
int nvs_set_blob(nvs_handle_t handle, const char* key, const void* value, size_t length);
int nvs_get_i8 (nvs_handle_t handle, const char* key, int8_t* out_value);
int nvs_get_u8 (nvs_handle_t handle, const char* key, uint8_t* out_value);
int nvs_get_i16 (nvs_handle_t handle, const char* key, int16_t* out_value);
int nvs_get_u16 (nvs_handle_t handle, const char* key, uint16_t* out_value);
int nvs_get_i32 (nvs_handle_t handle, const char* key, int32_t* out_value);
int nvs_get_u32 (nvs_handle_t handle, const char* key, uint32_t* out_value);
int nvs_get_i64 (nvs_handle_t handle, const char* key, int64_t* out_value);
int nvs_get_u64 (nvs_handle_t handle, const char* key, uint64_t* out_value);
int nvs_get_str (nvs_handle_t handle, const char* key, char* out_value, size_t* length);
int nvs_get_blob(nvs_handle_t handle, const char* key, void* out_value, size_t* length);
int nvs_erase_key(nvs_handle_t handle, const char* key);
int nvs_erase_all(nvs_handle_t handle);
int nvs_commit(nvs_handle_t handle);
void nvs_close(nvs_handle_t handle);

int nvs_get_stats(const char *part_name, nvs_stats_t *nvs_stats);
int nvs_get_used_entry_count(nvs_handle_t handle, size_t* used_entries);
nvs_iterator_t nvs_entry_find(const char *part_name, const char *namespace_name, nvs_type_t type);
nvs_iterator_t nvs_entry_next(nvs_iterator_t iterator);
void nvs_entry_info(nvs_iterator_t iterator, nvs_entry_info_t *out_info);
void nvs_release_iterator(nvs_iterator_t iterator);



uint32_t phy_get_rf_cal_version(void);

void phy_xpd_tsens(void);
uint32_t phy_enter_critical(void);
void phy_close_rf(void);

void phy_wakeup_init(void);
void phy_exit_critical(uint32_t level);
void esp_phy_common_clock_enable(void);
void esp_phy_common_clock_disable(void);
void phy_digital_regs_store(void);
void phy_dig_reg_backup(bool, uint32_t *);
void phy_digital_regs_load(void);
void esp_phy_enable(void);
void esp_phy_disable(void);
void esp_wifi_bt_power_domain_on(void);
void esp_wifi_bt_power_domain_off(void);
void esp_phy_modem_init(void);
void esp_phy_modem_deinit(void);
void esp_mac_bb_pd_mem_init(void);
void esp_mac_bb_pd_mem_deinit(void);
void esp_mac_bb_power_up(void);
void esp_mac_bb_power_down(void);
const esp_phy_init_data_t* esp_phy_get_init_data(void);
void esp_phy_release_init_data(const esp_phy_init_data_t* init_data);
const esp_phy_init_data_t* esp_phy_get_init_data(void);
void esp_phy_release_init_data(const esp_phy_init_data_t* init_data);
//int load_cal_data_from_nvs_handle(nvs_handle_t handle, esp_phy_calibration_data_t* out_cal_data);
int store_cal_data_to_nvs_handle(nvs_handle_t handle, const esp_phy_calibration_data_t* cal_data);
int esp_phy_load_cal_data_from_nvs(esp_phy_calibration_data_t* out_cal_data);
int esp_phy_store_cal_data_to_nvs(const esp_phy_calibration_data_t* cal_data);
int esp_phy_erase_cal_data_in_nvs(void);
void esp_phy_reduce_tx_power(esp_phy_init_data_t* init_data);
void esp_phy_load_cal_and_init(void);
int phy_crc_check_init_data(uint8_t* init_data, const uint8_t* checksum, size_t init_data_length);
uint8_t phy_find_bin_type_according_country(const char* country);
int phy_find_bin_data_according_type(uint8_t* out_init_data_store, const phy_control_info_data_t* init_data_control_info, const uint8_t* init_data_multiple, phy_init_data_type_t init_data_type);
int phy_get_multiple_init_data(const esp_partition_t* partition, uint8_t* init_data_store, size_t init_data_store_length, phy_init_data_type_t init_data_type);
int esp_phy_update_init_data(phy_init_data_type_t init_data_type);
int esp_phy_update_country_info(const char *country);
void esp_wifi_bt_power_domain_on(void);
void esp_wifi_bt_power_domain_off(void);

char *get_phy_version_str();
int register_chipv7_phy(const esp_phy_init_data_t* init_data, esp_phy_calibration_data_t *cal_data, esp_phy_calibration_mode_t cal_mode);
