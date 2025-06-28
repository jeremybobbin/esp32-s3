#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/lock.h>

#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "soc/phy.h"
#include "soc/gpio.h"
#include "soc/peripherals.h"
#include "soc/trace.h"

#define DR_REG_SYSCON_BASE                      0x60026000
#define SYSCON_WIFI_RST_EN_REG          (DR_REG_SYSCON_BASE + 0x18)
#define LIMIT(val, low, high) ((val < low) ? low : (val > high) ? high : val)

static const esp_phy_init_data_t phy_init_data = { {
	0x00,
	0x00,
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x50),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x50),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x50),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x4c),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x4c),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x48),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x4c),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x48),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x48),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x44),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x4a),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x46),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x46),
	LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x42),
	0x00,
	0x00,
	0x00,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0x74
} };



static const char *TAG = "phy_init";

static _lock_t s_phy_access_lock;

static  struct {
	int     count;  /* power on count of wifi and bt power domain */
	_lock_t lock;
} s_wifi_bt_pd_controller = { .count = 0 };

/* Indicate PHY is calibrated or not */
static bool s_is_phy_calibrated = false;

static bool s_is_phy_reg_stored = false;

/* Reference count of enabling PHY */
static uint8_t s_phy_access_ref = 0;

#if CONFIG_MAC_BB_PD
/* Reference of powering down MAC and BB */
static bool s_mac_bb_pu = true;
#endif

#if CONFIG_IDF_TARGET_ESP32
/* time stamp updated when the PHY/RF is turned on */
static int64_t s_phy_rf_en_ts = 0;
#endif

/* PHY spinlock for libphy.a */
static portMUX_TYPE s_phy_int_mux = portMUX_INITIALIZER_UNLOCKED;

/* Memory to store PHY digital registers */
static uint32_t* s_phy_digital_regs_mem = NULL;
static uint8_t s_phy_modem_init_ref = 0;

#if CONFIG_MAC_BB_PD
uint32_t* s_mac_bb_pd_mem = NULL;
/* Reference count of MAC BB backup memory */
static uint8_t s_macbb_backup_mem_ref = 0;
#endif

#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN
#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN_EMBED
extern uint8_t multi_phy_init_data_bin_start[] asm("_binary_phy_multiple_init_data_bin_start");
extern uint8_t multi_phy_init_data_bin_end[]   asm("_binary_phy_multiple_init_data_bin_end");
#endif
/* The following static variables are only used by Wi-Fi tasks, so they can be handled without lock */
static phy_init_data_type_t s_phy_init_data_type = 0;

static phy_init_data_type_t s_current_apply_phy_init_data = 0;

static char s_phy_current_country[PHY_COUNTRY_CODE_LEN] = {0};

/* Whether it is a new bin */
static bool s_multiple_phy_init_data_bin = false;

/* PHY init data type array */
static char* s_phy_type[ESP_PHY_INIT_DATA_TYPE_NUMBER] = {"DEFAULT", "SRRC", "FCC", "CE", "NCC", "KCC", "MIC", "IC",
	"ACMA", "ANATEL", "ISED", "WPC", "OFCA", "IFETEL", "RCM"};

/* Country and PHY init data type map */
static phy_country_to_bin_type_t s_country_code_map_type_table[] = {
	{"AT",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"AU",  ESP_PHY_INIT_DATA_TYPE_ACMA},
	{"BE",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"BG",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"BR",  ESP_PHY_INIT_DATA_TYPE_ANATEL},
	{"CA",  ESP_PHY_INIT_DATA_TYPE_ISED},
	{"CH",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"CN",  ESP_PHY_INIT_DATA_TYPE_SRRC},
	{"CY",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"CZ",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"DE",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"DK",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"EE",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"ES",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"FI",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"FR",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"GB",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"GR",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"HK",  ESP_PHY_INIT_DATA_TYPE_OFCA},
	{"HR",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"HU",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"IE",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"IN",  ESP_PHY_INIT_DATA_TYPE_WPC},
	{"IS",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"IT",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"JP",  ESP_PHY_INIT_DATA_TYPE_MIC},
	{"KR",  ESP_PHY_INIT_DATA_TYPE_KCC},
	{"LI",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"LT",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"LU",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"LV",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"MT",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"MX",  ESP_PHY_INIT_DATA_TYPE_IFETEL},
	{"NL",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"NO",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"NZ",  ESP_PHY_INIT_DATA_TYPE_RCM},
	{"PL",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"PT",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"RO",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"SE",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"SI",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"SK",  ESP_PHY_INIT_DATA_TYPE_CE},
	{"TW",  ESP_PHY_INIT_DATA_TYPE_NCC},
	{"US",  ESP_PHY_INIT_DATA_TYPE_FCC},
};
#endif
uint32_t phy_enter_critical(void)
{
	if (xPortInIsrContext()) {
		portENTER_CRITICAL_ISR(&s_phy_int_mux);

	} else {
		portENTER_CRITICAL(&s_phy_int_mux);
	}
	// Interrupt level will be stored in current tcb, so always return zero.
	return 0;
}

void phy_exit_critical(uint32_t level)
{
	// Param level don't need any more, ignore it.
	if (xPortInIsrContext()) {
		portEXIT_CRITICAL_ISR(&s_phy_int_mux);
	} else {
		portEXIT_CRITICAL(&s_phy_int_mux);
	}
}

#if CONFIG_IDF_TARGET_ESP32
int64_t esp_phy_rf_get_on_ts(void)
{
	return s_phy_rf_en_ts;
}

void phy_update_wifi_mac_time(bool en_clock_stopped, int64_t now)
{
	static uint32_t s_common_clock_disable_time = 0;

	if (en_clock_stopped) {
		s_common_clock_disable_time = (uint32_t)now;
	} else {
		if (s_common_clock_disable_time) {
			uint32_t diff = (uint64_t)now - s_common_clock_disable_time;

			if (s_wifi_mac_time_update_cb) {
				s_wifi_mac_time_update_cb(diff);
			}
			s_common_clock_disable_time = 0;
		}
	}
}
#endif

void esp_phy_common_clock_enable(void)
{
	wifi_bt_common_module_enable();
}

void esp_phy_common_clock_disable(void)
{
	wifi_bt_common_module_disable();
}

void phy_digital_regs_store(void)
{
	if (s_phy_digital_regs_mem != NULL) {
		phy_dig_reg_backup(true, s_phy_digital_regs_mem);
		s_is_phy_reg_stored = true;
	}
}

void phy_digital_regs_load(void)
{
	if (s_is_phy_reg_stored && s_phy_digital_regs_mem != NULL) {
		phy_dig_reg_backup(false, s_phy_digital_regs_mem);
	}
}

void esp_phy_enable(void)
{
	_lock_acquire(&s_phy_access_lock);

	if (s_phy_access_ref == 0) {
#if CONFIG_IDF_TARGET_ESP32
		// Update time stamp
		s_phy_rf_en_ts = esp_timer_get_time();
		// Update WiFi MAC time before WiFi/BT common clock is enabled
		phy_update_wifi_mac_time(false, s_phy_rf_en_ts);
#endif
		esp_phy_common_clock_enable();

		if (s_is_phy_calibrated == false) {
			esp_phy_load_cal_and_init();
			s_is_phy_calibrated = true;
		}
		else {
			phy_wakeup_init();
			phy_digital_regs_load();
		}

#if CONFIG_IDF_TARGET_ESP32
		coex_bt_high_prio();
#endif
	}
	s_phy_access_ref++;

	_lock_release(&s_phy_access_lock);
}

void esp_phy_disable(void)
{
	_lock_acquire(&s_phy_access_lock);

	s_phy_access_ref--;
	if (s_phy_access_ref == 0) {
		phy_digital_regs_store();
		// Disable PHY and RF.
		phy_close_rf();
#if !CONFIG_IDF_TARGET_ESP32
		// Disable PHY temperature sensor
		phy_xpd_tsens();
#endif
#if CONFIG_IDF_TARGET_ESP32
		// Update WiFi MAC time before disalbe WiFi/BT common peripheral clock
		phy_update_wifi_mac_time(true, esp_timer_get_time());
#endif
		// Disable WiFi/BT common peripheral clock. Do not disable clock for hardware RNG
		esp_phy_common_clock_disable();
	}

	_lock_release(&s_phy_access_lock);
}

void esp_wifi_bt_power_domain_on(void)
{
	_lock_acquire(&s_wifi_bt_pd_controller.lock);
	if (s_wifi_bt_pd_controller.count++ == 0) {
		CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_PWC_REG, RTC_CNTL_WIFI_FORCE_PD);
#if !CONFIG_IDF_TARGET_ESP32
		SET_PERI_REG_MASK(SYSCON_WIFI_RST_EN_REG, MODEM_RESET_FIELD_WHEN_PU);
		CLEAR_PERI_REG_MASK(SYSCON_WIFI_RST_EN_REG, MODEM_RESET_FIELD_WHEN_PU);
#endif
		CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_WIFI_FORCE_ISO);
	}
	_lock_release(&s_wifi_bt_pd_controller.lock);
}

void esp_wifi_bt_power_domain_off(void)
{
	_lock_acquire(&s_wifi_bt_pd_controller.lock);
	if (--s_wifi_bt_pd_controller.count == 0) {
		SET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_WIFI_FORCE_ISO);
		SET_PERI_REG_MASK(RTC_CNTL_DIG_PWC_REG, RTC_CNTL_WIFI_FORCE_PD);
	}
	_lock_release(&s_wifi_bt_pd_controller.lock);
}

void esp_phy_modem_init(void)
{
	_lock_acquire(&s_phy_access_lock);

	s_phy_modem_init_ref++;
	if (s_phy_digital_regs_mem == NULL) {
		s_phy_digital_regs_mem = (uint32_t *)heap_caps_malloc(SOC_PHY_DIG_REGS_MEM_SIZE, MALLOC_CAP_DMA|MALLOC_CAP_INTERNAL);
	}

	_lock_release(&s_phy_access_lock);

}

void esp_phy_modem_deinit(void)
{
	_lock_acquire(&s_phy_access_lock);

	s_phy_modem_init_ref--;
	if (s_phy_modem_init_ref == 0) {
		s_is_phy_reg_stored = false;
		free(s_phy_digital_regs_mem);
		s_phy_digital_regs_mem = NULL;
		/* Fix the issue caused by the power domain off.
		* This issue is only on ESP32C3.
		*/
#if CONFIG_IDF_TARGET_ESP32C3
		phy_init_flag();
#endif
	}

	_lock_release(&s_phy_access_lock);
}

#if CONFIG_MAC_BB_PD
void esp_mac_bb_pd_mem_init(void)
{
	_lock_acquire(&s_phy_access_lock);

	s_macbb_backup_mem_ref++;
	if (s_mac_bb_pd_mem == NULL) {
		s_mac_bb_pd_mem = (uint32_t *)heap_caps_malloc(SOC_MAC_BB_PD_MEM_SIZE, MALLOC_CAP_DMA|MALLOC_CAP_INTERNAL);
	}

	_lock_release(&s_phy_access_lock);
}

void esp_mac_bb_pd_mem_deinit(void)
{
	_lock_acquire(&s_phy_access_lock);

	s_macbb_backup_mem_ref--;
	if (s_macbb_backup_mem_ref == 0) {
		free(s_mac_bb_pd_mem);
		s_mac_bb_pd_mem = NULL;
	}

	_lock_release(&s_phy_access_lock);
}

void esp_mac_bb_power_up(void)
{
	if (s_mac_bb_pd_mem == NULL) {
		return;
	}
	esp_wifi_bt_power_domain_on();
	if (!s_mac_bb_pu) {
		esp_phy_common_clock_enable();
		phy_freq_mem_backup(false, s_mac_bb_pd_mem);
		esp_phy_common_clock_disable();
		s_mac_bb_pu = true;
	}
}

void esp_mac_bb_power_down(void)
{
	if (s_mac_bb_pd_mem == NULL) {
		return;
	}
	if (s_mac_bb_pu) {
		esp_phy_common_clock_enable();
		phy_freq_mem_backup(true, s_mac_bb_pd_mem);
		esp_phy_common_clock_disable();
		s_mac_bb_pu = false;
	}
	esp_wifi_bt_power_domain_off();
}
#endif

// PHY init data handling functions
#if CONFIG_ESP_PHY_INIT_DATA_IN_PARTITION
#include "esp_partition.h"

const esp_phy_init_data_t* esp_phy_get_init_data(void)
{
#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN_EMBED
	size_t init_data_store_length = sizeof(phy_init_magic_pre) +
			sizeof(esp_phy_init_data_t) + sizeof(phy_init_magic_post);
	uint8_t* init_data_store = (uint8_t*) malloc(init_data_store_length);
	if (init_data_store == NULL) {
		return NULL;
	}
	memcpy(init_data_store, multi_phy_init_data_bin_start, init_data_store_length);
#else
	const esp_partition_t* partition = esp_partition_find_first(
			ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_PHY, NULL);
	if (partition == NULL) {
		return NULL;
	}
	size_t init_data_store_length = sizeof(phy_init_magic_pre) +
			sizeof(esp_phy_init_data_t) + sizeof(phy_init_magic_post);
	uint8_t* init_data_store = (uint8_t*) malloc(init_data_store_length);
	if (init_data_store == NULL) {
		return NULL;
	}
	// read phy data from flash
	int err = esp_partition_read(partition, 0, init_data_store, init_data_store_length);
	if (err != ESP_OK) {
		free(init_data_store);
		return NULL;
	}
#endif
	// verify data
	if (memcmp(init_data_store, PHY_INIT_MAGIC, sizeof(phy_init_magic_pre)) != 0 ||
		memcmp(init_data_store + init_data_store_length - sizeof(phy_init_magic_post),
				PHY_INIT_MAGIC, sizeof(phy_init_magic_post)) != 0) {
#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN_EMBED
		free(init_data_store);
		return NULL;
#else
#ifndef CONFIG_ESP_PHY_DEFAULT_INIT_IF_INVALID
		free(init_data_store);
		return NULL;
#else

		memcpy(init_data_store,
			   PHY_INIT_MAGIC, sizeof(phy_init_magic_pre));
		memcpy(init_data_store + sizeof(phy_init_magic_pre),
			   &phy_init_data, sizeof(phy_init_data));
		memcpy(init_data_store + sizeof(phy_init_magic_pre) + sizeof(phy_init_data),
			   PHY_INIT_MAGIC, sizeof(phy_init_magic_post));

		assert(memcmp(init_data_store, PHY_INIT_MAGIC, sizeof(phy_init_magic_pre)) == 0);
		assert(memcmp(init_data_store + init_data_store_length - sizeof(phy_init_magic_post),
					  PHY_INIT_MAGIC, sizeof(phy_init_magic_post)) == 0);

		// write default data
		err = esp_partition_write(partition, 0, init_data_store, init_data_store_length);
		if (err != ESP_OK) {
			free(init_data_store);
			return NULL;
		}
#endif // CONFIG_ESP_PHY_DEFAULT_INIT_IF_INVALID
#endif // CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN_EMBED
	}
#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN
	if ((*(init_data_store + (sizeof(phy_init_magic_pre) + PHY_SUPPORT_MULTIPLE_BIN_OFFSET)))) {
		s_multiple_phy_init_data_bin = true;
	}
#endif
	return (const esp_phy_init_data_t*) (init_data_store + sizeof(phy_init_magic_pre));
}

void esp_phy_release_init_data(const esp_phy_init_data_t* init_data)
{
	free((uint8_t*) init_data - sizeof(phy_init_magic_pre));
}

#else // CONFIG_ESP_PHY_INIT_DATA_IN_PARTITION

// phy_init_data.h will declare static 'phy_init_data' variable initialized with default init data

const esp_phy_init_data_t* esp_phy_get_init_data(void)
{
	return &phy_init_data;
}

void esp_phy_release_init_data(const esp_phy_init_data_t* init_data)
{
	// no-op
}
#endif // CONFIG_ESP_PHY_INIT_DATA_IN_PARTITION


// PHY calibration data handling functions
static const char* PHY_NAMESPACE = "phy";
static const char* PHY_CAL_VERSION_KEY = "cal_version";
static const char* PHY_CAL_MAC_KEY = "cal_mac";
static const char* PHY_CAL_DATA_KEY = "cal_data";

static int load_cal_data_from_nvs_handle(nvs_handle_t handle,
		esp_phy_calibration_data_t* out_cal_data);

static int store_cal_data_to_nvs_handle(nvs_handle_t handle,
		const esp_phy_calibration_data_t* cal_data);

int esp_phy_load_cal_data_from_nvs(esp_phy_calibration_data_t* out_cal_data)
{
	nvs_handle_t handle;
	int err = nvs_open(PHY_NAMESPACE, NVS_READONLY, &handle);
	if (err == ESP_ERR_NVS_NOT_INITIALIZED) {
		return err;
	} else if (err != ESP_OK) {
		return err;
	}
	err = load_cal_data_from_nvs_handle(handle, out_cal_data);
	nvs_close(handle);
	return err;
}

int esp_phy_store_cal_data_to_nvs(const esp_phy_calibration_data_t* cal_data)
{
	nvs_handle_t handle;
	int err = nvs_open(PHY_NAMESPACE, NVS_READWRITE, &handle);
	if (err != ESP_OK) {
		return err;
	}
	else {
		err = store_cal_data_to_nvs_handle(handle, cal_data);
		nvs_close(handle);
		return err;
	}
}

int esp_phy_erase_cal_data_in_nvs(void)
{
	nvs_handle_t handle;
	int err = nvs_open(PHY_NAMESPACE, NVS_READWRITE, &handle);
	if (err != ESP_OK) {
		return err;
	}
	else {
		err = nvs_erase_all(handle);
		if (err != ESP_OK) {
		}
		else {
			err = nvs_commit(handle);
			if (err != ESP_OK) {
			}
		}
	}
	nvs_close(handle);
	return err;
}

static int load_cal_data_from_nvs_handle(nvs_handle_t handle,
		esp_phy_calibration_data_t* out_cal_data)
{
	int err;
	uint32_t cal_data_version;

	err = nvs_get_u32(handle, PHY_CAL_VERSION_KEY, &cal_data_version);
	if (err != ESP_OK) {
		return err;
	}
	uint32_t cal_format_version = phy_get_rf_cal_version() & (~BIT(16));
	if (cal_data_version != cal_format_version) {
		return ESP_FAIL;
	}
	uint8_t cal_data_mac[6];
	size_t length = sizeof(cal_data_mac);
	err = nvs_get_blob(handle, PHY_CAL_MAC_KEY, cal_data_mac, &length);
	if (err != ESP_OK) {
		return err;
	}
	if (length != sizeof(cal_data_mac)) {
		return ESP_ERR_INVALID_SIZE;
	}
	uint8_t sta_mac[6];
	esp_efuse_mac_get_default(sta_mac);
	if (memcmp(sta_mac, cal_data_mac, sizeof(sta_mac)) != 0) {
		return ESP_FAIL;
	}
	length = sizeof(*out_cal_data);
	err = nvs_get_blob(handle, PHY_CAL_DATA_KEY, out_cal_data, &length);
	if (err != ESP_OK) {
		return err;
	}
	if (length != sizeof(*out_cal_data)) {
		return ESP_ERR_INVALID_SIZE;
	}
	return ESP_OK;
}

static int store_cal_data_to_nvs_handle(nvs_handle_t handle,
		const esp_phy_calibration_data_t* cal_data)
{
	int err;

	err = nvs_set_blob(handle, PHY_CAL_DATA_KEY, cal_data, sizeof(*cal_data));
	if (err != ESP_OK) {
		return err;
	}

	uint8_t sta_mac[6];
	esp_efuse_mac_get_default(sta_mac);
	err = nvs_set_blob(handle, PHY_CAL_MAC_KEY, sta_mac, sizeof(sta_mac));
	if (err != ESP_OK) {
		return err;
	}

	uint32_t cal_format_version = phy_get_rf_cal_version() & (~BIT(16));
	err = nvs_set_u32(handle, PHY_CAL_VERSION_KEY, cal_format_version);
	if (err != ESP_OK) {
		return err;
	}

	err = nvs_commit(handle);
	if (err != ESP_OK) {
	}

	return err;
}

#if CONFIG_ESP_PHY_REDUCE_TX_POWER
static void __attribute((unused)) esp_phy_reduce_tx_power(esp_phy_init_data_t* init_data)
{
	uint8_t i;

	for(i = 0; i < PHY_TX_POWER_NUM; i++) {
		// LOWEST_PHY_TX_POWER is the lowest tx power
		init_data->params[PHY_TX_POWER_OFFSET+i] = PHY_TX_POWER_LOWEST;
	}
}
#endif

void esp_phy_load_cal_and_init(void)
{
	char * phy_version = get_phy_version_str();

#if CONFIG_IDF_TARGET_ESP32S2
	phy_eco_version_sel(efuse_hal_get_major_chip_version());
#endif
	esp_phy_calibration_data_t* cal_data =
			(esp_phy_calibration_data_t*) calloc(sizeof(esp_phy_calibration_data_t), 1);
	if (cal_data == NULL) {
		abort();
	}

#if CONFIG_ESP_PHY_REDUCE_TX_POWER
	const esp_phy_init_data_t* phy_init_data = esp_phy_get_init_data();
	if (phy_init_data == NULL) {
		abort();
	}

	esp_phy_init_data_t* init_data = (esp_phy_init_data_t*) malloc(sizeof(esp_phy_init_data_t));
	if (init_data == NULL) {
		abort();
	}

	memcpy(init_data, phy_init_data, sizeof(esp_phy_init_data_t));
	if (esp_reset_reason() == ESP_RST_BROWNOUT) {
		esp_phy_reduce_tx_power(init_data);
	}
#else
	const esp_phy_init_data_t* init_data = esp_phy_get_init_data();
	if (init_data == NULL) {
		abort();
	}
#endif

#if CONFIG_ESP_PHY_ENABLE_USB
	phy_bbpll_en_usb(true);
#endif

#ifdef CONFIG_ESP_PHY_CALIBRATION_AND_DATA_STORAGE
	esp_phy_calibration_mode_t calibration_mode = PHY_RF_CAL_PARTIAL;
	uint8_t sta_mac[6];
	if (esp_rom_get_reset_reason(0) == RESET_REASON_CORE_DEEP_SLEEP) {
		calibration_mode = PHY_RF_CAL_NONE;
	}
	int err = esp_phy_load_cal_data_from_nvs(cal_data);
	if (err != ESP_OK) {
		calibration_mode = PHY_RF_CAL_FULL;
	}

	esp_efuse_mac_get_default(sta_mac);
	memcpy(cal_data->mac, sta_mac, 6);
	int ret = register_chipv7_phy(init_data, cal_data, calibration_mode);
	if (ret == ESP_CAL_DATA_CHECK_FAIL) {
	}

	if ((calibration_mode != PHY_RF_CAL_NONE && err != ESP_OK) ||
			(calibration_mode != PHY_RF_CAL_FULL && ret == ESP_CAL_DATA_CHECK_FAIL)) {
		err = esp_phy_store_cal_data_to_nvs(cal_data);
	} else {
		err = ESP_OK;
	}
#else
	register_chipv7_phy(init_data, cal_data, PHY_RF_CAL_FULL);
#endif

#if CONFIG_ESP_PHY_REDUCE_TX_POWER
	esp_phy_release_init_data(phy_init_data);
	free(init_data);
#else
	esp_phy_release_init_data(init_data);
#endif

	free(cal_data); // PHY maintains a copy of calibration data, so we can free this
}

#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN
static int phy_crc_check_init_data(uint8_t* init_data, const uint8_t* checksum, size_t init_data_length)
{
	uint32_t crc_data = 0;
	crc_data = esp_rom_crc32_le(crc_data, init_data, init_data_length);
	uint32_t crc_size_conversion = htonl(crc_data);

	if (crc_size_conversion != *(uint32_t*)(checksum)) {
		return ESP_FAIL;
	}
	return ESP_OK;
}

static uint8_t phy_find_bin_type_according_country(const char* country)
{
	uint32_t i = 0;
	uint8_t phy_init_data_type = 0;

	for (i = 0; i < sizeof(s_country_code_map_type_table)/sizeof(phy_country_to_bin_type_t); i++)
	{
		if (!memcmp(country, s_country_code_map_type_table[i].cc, sizeof(s_phy_current_country))) {
			phy_init_data_type = s_country_code_map_type_table[i].type;
			break;
		}
	}

	if (i == sizeof(s_country_code_map_type_table)/sizeof(phy_country_to_bin_type_t)) {
		phy_init_data_type = ESP_PHY_INIT_DATA_TYPE_DEFAULT;
	}

	return phy_init_data_type;
}

static int phy_find_bin_data_according_type(uint8_t* out_init_data_store,
		const phy_control_info_data_t* init_data_control_info,
		const uint8_t* init_data_multiple,
		phy_init_data_type_t init_data_type)
{
	  int i = 0;
	  for (i = 0; i < init_data_control_info->number; i++) {
		  if (init_data_type == *(init_data_multiple + (i * sizeof(esp_phy_init_data_t)) + PHY_INIT_DATA_TYPE_OFFSET)) {
			  memcpy(out_init_data_store + sizeof(phy_init_magic_pre),
					  init_data_multiple + (i * sizeof(esp_phy_init_data_t)), sizeof(esp_phy_init_data_t));
			  break;
		  }
	  }

	  if (i == init_data_control_info->number) {
		  return ESP_FAIL;
	  }
	  return ESP_OK;
}

static int phy_get_multiple_init_data(const esp_partition_t* partition,
		uint8_t* init_data_store,
		size_t init_data_store_length,
		phy_init_data_type_t init_data_type)
{
	phy_control_info_data_t* init_data_control_info = (phy_control_info_data_t*) malloc(sizeof(phy_control_info_data_t));
	if (init_data_control_info == NULL) {
		return ESP_FAIL;
	}
	int err = ESP_OK;
#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN_EMBED
	memcpy(init_data_control_info, multi_phy_init_data_bin_start + init_data_store_length, sizeof(phy_control_info_data_t));
#else
	err = esp_partition_read(partition, init_data_store_length, init_data_control_info, sizeof(phy_control_info_data_t));
	if (err != ESP_OK) {
		free(init_data_control_info);
		return ESP_FAIL;
	}
#endif
	if ((init_data_control_info->check_algorithm) == PHY_CRC_ALGORITHM) {
		err =  phy_crc_check_init_data(init_data_control_info->multiple_bin_checksum, init_data_control_info->control_info_checksum,
				sizeof(phy_control_info_data_t) - sizeof(init_data_control_info->control_info_checksum));
		if (err != ESP_OK) {
			free(init_data_control_info);
			return ESP_FAIL;
		}
	} else {
		free(init_data_control_info);
		return ESP_FAIL;
	}

	uint8_t* init_data_multiple = (uint8_t*) malloc(sizeof(esp_phy_init_data_t) * init_data_control_info->number);
	if (init_data_multiple == NULL) {
		free(init_data_control_info);
		return ESP_FAIL;
	}

#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN_EMBED
	memcpy(init_data_multiple, multi_phy_init_data_bin_start + init_data_store_length + sizeof(phy_control_info_data_t), sizeof(esp_phy_init_data_t) * init_data_control_info->number);
#else
	err = esp_partition_read(partition, init_data_store_length + sizeof(phy_control_info_data_t),
			init_data_multiple, sizeof(esp_phy_init_data_t) * init_data_control_info->number);
	if (err != ESP_OK) {
		free(init_data_multiple);
		free(init_data_control_info);
		return ESP_FAIL;
	}
#endif
	if ((init_data_control_info->check_algorithm) == PHY_CRC_ALGORITHM) {
		err = phy_crc_check_init_data(init_data_multiple, init_data_control_info->multiple_bin_checksum,
				sizeof(esp_phy_init_data_t) * init_data_control_info->number);
		if (err != ESP_OK) {
			free(init_data_multiple);
			free(init_data_control_info);
			return ESP_FAIL;
		}
	} else {
		free(init_data_multiple);
		free(init_data_control_info);
		return ESP_FAIL;
	}

	err = phy_find_bin_data_according_type(init_data_store, init_data_control_info, init_data_multiple, init_data_type);
	if (err != ESP_OK) {
		s_phy_init_data_type = ESP_PHY_INIT_DATA_TYPE_DEFAULT;
	} else {
		s_phy_init_data_type = init_data_type;
	}

	free(init_data_multiple);
	free(init_data_control_info);
	return ESP_OK;
}

int esp_phy_update_init_data(phy_init_data_type_t init_data_type)
{
#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN_EMBED
	int err = ESP_OK;
	const esp_partition_t* partition = NULL;
	size_t init_data_store_length = sizeof(phy_init_magic_pre) +
		sizeof(esp_phy_init_data_t) + sizeof(phy_init_magic_post);
	uint8_t* init_data_store = (uint8_t*) malloc(init_data_store_length);
	if (init_data_store == NULL) {
		return ESP_ERR_NO_MEM;
	}
	memcpy(init_data_store, multi_phy_init_data_bin_start, init_data_store_length);
#else
	const esp_partition_t* partition = esp_partition_find_first(
		  ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_PHY, NULL);
	if (partition == NULL) {
		return ESP_FAIL;
	}
	size_t init_data_store_length = sizeof(phy_init_magic_pre) +
		sizeof(esp_phy_init_data_t) + sizeof(phy_init_magic_post);
	uint8_t* init_data_store = (uint8_t*) malloc(init_data_store_length);
	if (init_data_store == NULL) {
		return ESP_ERR_NO_MEM;
	}

	int err = esp_partition_read(partition, 0, init_data_store, init_data_store_length);
	if (err != ESP_OK) {
		free(init_data_store);
		return ESP_FAIL;
	}
#endif
	if (memcmp(init_data_store, PHY_INIT_MAGIC, sizeof(phy_init_magic_pre)) != 0 ||
			memcmp(init_data_store + init_data_store_length - sizeof(phy_init_magic_post),
				PHY_INIT_MAGIC, sizeof(phy_init_magic_post)) != 0) {
		free(init_data_store);
		return ESP_FAIL;
	}

	//find init data bin according init data type
	if (init_data_type != ESP_PHY_INIT_DATA_TYPE_DEFAULT) {
		err = phy_get_multiple_init_data(partition, init_data_store, init_data_store_length, init_data_type);
		if (err != ESP_OK) {
			free(init_data_store);
#if CONFIG_ESP_PHY_INIT_DATA_ERROR
			abort();
#else
			return ESP_FAIL;
#endif
		}
	} else {
		s_phy_init_data_type = ESP_PHY_INIT_DATA_TYPE_DEFAULT;
	}

	if (s_current_apply_phy_init_data != s_phy_init_data_type) {
		err = esp_phy_apply_phy_init_data(init_data_store + sizeof(phy_init_magic_pre));
		if (err != ESP_OK) {
			free(init_data_store);
			return ESP_FAIL;
		}

				s_phy_type[s_current_apply_phy_init_data], s_phy_type[s_phy_init_data_type]);
		s_current_apply_phy_init_data = s_phy_init_data_type;
	}

	free(init_data_store);
	return ESP_OK;
}
#endif

int esp_phy_update_country_info(const char *country)
{
#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN
	uint8_t phy_init_data_type_map = 0;

	if (!s_multiple_phy_init_data_bin) {
		return ESP_FAIL;
	}

	if (!memcmp(country, s_phy_current_country, sizeof(s_phy_current_country))) {
		return ESP_OK;
	}

	memcpy(s_phy_current_country, country, sizeof(s_phy_current_country));

	phy_init_data_type_map = phy_find_bin_type_according_country(country);
	if (phy_init_data_type_map == s_phy_init_data_type) {
		return ESP_OK;
	}

	int err =  esp_phy_update_init_data(phy_init_data_type_map);
	if (err != ESP_OK) {
		return err;
	}
#endif
	return ESP_OK;
}

void esp_wifi_power_domain_on(void) __attribute__((alias("esp_wifi_bt_power_domain_on")));
void esp_wifi_power_domain_off(void) __attribute__((alias("esp_wifi_bt_power_domain_off")));
