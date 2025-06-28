#include <stdint.h>
#include <stdbool.h>

#define ESP_BT_CTRL_CONFIG_MAGIC_VAL    0x5A5AA5A5
#define ESP_BT_CTRL_CONFIG_VERSION      0x02209230

#define ESP_BT_HCI_TL_MAGIC_VALUE   0xfadebead
#define ESP_BT_HCI_TL_VERSION       0x00010000

typedef enum {
	ESP_BT_MODE_IDLE       = 0x00,   /*!< Bluetooth is not running */
	ESP_BT_MODE_BLE        = 0x01,   /*!< Run BLE mode */
	ESP_BT_MODE_CLASSIC_BT = 0x02,   /*!< Run Classic BT mode */
	ESP_BT_MODE_BTDM       = 0x03,   /*!< Run dual mode */
} esp_bt_mode_t;

typedef enum {
	ESP_BT_CTRL_HCI_TL_UART = 0,      /*!< HCI UART h4 transport layer */
	ESP_BT_CTRL_HCI_TL_VHCI = 1,      /*!< VHCI interface */
} esp_bt_ctrl_hci_tl_t;

typedef enum {
	ESP_MAC_WIFI_STA,
	ESP_MAC_WIFI_SOFTAP,
	ESP_MAC_BT,
	ESP_MAC_ETH,
	ESP_MAC_IEEE802154,
} esp_mac_type_t;

typedef enum {
	ESP_BLE_CE_LEN_TYPE_ORIG = 0,      /*!< original */
	ESP_BLE_CE_LEN_TYPE_CE   = 1,      /*!< use CE_LEN parameter from HCI commands */
	ESP_BLE_CE_LEN_TYPE_SD   = 1,      /*!< Espressif vendor defined */
} esp_ble_ce_len_t;

typedef enum {
	ESP_BT_SLEEP_MODE_NONE = 0,      /*!< Bluetooth sleep mode disabled */
	ESP_BT_SLEEP_MODE_1    = 1,      /*!< Bluetooth sleep mode 1 */
} esp_bt_sleep_mode_t;

typedef enum {
	ESP_BT_SLEEP_CLOCK_NONE            = 0,   /*!< Sleep clock not configured */
	ESP_BT_SLEEP_CLOCK_MAIN_XTAL       = 1,   /*!< SoC main crystal */
	ESP_BT_SLEEP_CLOCK_EXT_32K_XTAL    = 2,   /*!< External 32.768kHz crystal */
	ESP_BT_SLEEP_CLOCK_RTC_SLOW        = 3,   /*!< Internal 90kHz RC oscillator */
	ESP_BT_SLEEP_CLOCK_FPGA_32K        = 4,   /*!< Hardwired 32KHz clock temporarily used for FPGA */
} esp_bt_sleep_clock_t;

enum {
	ESP_BT_ANT_IDX_0 = 0,               /*!< anntena NO 0 */
	ESP_BT_ANT_IDX_1 = 1,               /*!< anntena NO 1 */
};

enum {
	ESP_BT_COEX_PHY_CODED_TX_RX_TIME_LIMIT_FORCE_DISABLE = 0,    /*!< Disable the limit */
	ESP_BT_COEX_PHY_CODED_TX_RX_TIME_LIMIT_FORCE_ENABLE,         /*!< Always Enable the limit */
};

#define ESP_BT_HCI_TL_STATUS_OK            (0)   /*!< HCI_TL Tx/Rx operation status OK */

typedef void (* esp_bt_hci_tl_callback_t) (void *arg, uint8_t status);

#define BT_CTRL_BLE_MAX_ACT_LIMIT           10  //Maximum BLE activity limitation
#define SLAVE_CE_LEN_MIN_DEFAULT             5

#ifdef CONFIG_BT_CTRL_SCAN_DUPL_TYPE
#define SCAN_DUPLICATE_TYPE_VALUE  CONFIG_BT_CTRL_SCAN_DUPL_TYPE
#else
#define SCAN_DUPLICATE_TYPE_VALUE  0
#endif

/* normal adv cache size */
#ifdef CONFIG_BT_CTRL_SCAN_DUPL_CACHE_SIZE
#define NORMAL_SCAN_DUPLICATE_CACHE_SIZE            CONFIG_BT_CTRL_SCAN_DUPL_CACHE_SIZE
#else
#define NORMAL_SCAN_DUPLICATE_CACHE_SIZE            20
#endif

#ifndef CONFIG_BT_CTRL_BLE_MESH_SCAN_DUPL_EN
#define CONFIG_BT_CTRL_BLE_MESH_SCAN_DUPL_EN FALSE
#endif

#define SCAN_DUPLICATE_MODE_NORMAL_ADV_ONLY         0
#define SCAN_DUPLICATE_MODE_NORMAL_ADV_MESH_ADV     1

#if CONFIG_BT_CTRL_BLE_MESH_SCAN_DUPL_EN
	#define SCAN_DUPLICATE_MODE                     SCAN_DUPLICATE_MODE_NORMAL_ADV_MESH_ADV
	#ifdef CONFIG_BT_CTRL_MESH_DUPL_SCAN_CACHE_SIZE
	#define MESH_DUPLICATE_SCAN_CACHE_SIZE          CONFIG_BT_CTRL_MESH_DUPL_SCAN_CACHE_SIZE
	#else
	#define MESH_DUPLICATE_SCAN_CACHE_SIZE          50
	#endif
#else
	#define SCAN_DUPLICATE_MODE SCAN_DUPLICATE_MODE_NORMAL_ADV_ONLY
	#define MESH_DUPLICATE_SCAN_CACHE_SIZE          0
#endif

#ifdef CONFIG_BT_CTRL_SCAN_BACKOFF_UPPERLIMITMAX
#define BT_CTRL_SCAN_BACKOFF_UPPERLIMITMAX CONFIG_BT_CTRL_SCAN_BACKOFF_UPPERLIMITMAX
#else
#define BT_CTRL_SCAN_BACKOFF_UPPERLIMITMAX  0
#endif

#ifdef CONFIG_BT_CTRL_AGC_RECORRECT_EN
#define BT_CTRL_AGC_RECORRECT_EN  CONFIG_BT_CTRL_AGC_RECORRECT_EN
#else
#define BT_CTRL_AGC_RECORRECT_EN        0
#endif

#ifdef CONFIG_BT_CTRL_CODED_AGC_RECORRECT_EN
#define BT_CTRL_CODED_AGC_RECORRECT  CONFIG_BT_CTRL_CODED_AGC_RECORRECT_EN
#else
#define BT_CTRL_CODED_AGC_RECORRECT        0
#endif

#define AGC_RECORRECT_EN       ((BT_CTRL_AGC_RECORRECT_EN << 0) | (BT_CTRL_CODED_AGC_RECORRECT <<1))

#define CFG_MASK_BIT_SCAN_DUPLICATE_OPTION    (1<<0)

#define CFG_MASK      CFG_MASK_BIT_SCAN_DUPLICATE_OPTION

#define BLE_HW_TARGET_CODE_ESP32S3_CHIP_ECO0                      (0x02010000)

#define BT_CONTROLLER_INIT_CONFIG_DEFAULT() {                              \
	.magic = ESP_BT_CTRL_CONFIG_MAGIC_VAL,                                 \
	.version = ESP_BT_CTRL_CONFIG_VERSION,                                 \
	.controller_task_stack_size = ESP_TASK_BT_CONTROLLER_STACK,            \
	.controller_task_prio = ESP_TASK_BT_CONTROLLER_PRIO,                   \
	.controller_task_run_cpu = CONFIG_BT_CTRL_PINNED_TO_CORE,              \
	.bluetooth_mode = CONFIG_BT_CTRL_MODE_EFF,                             \
	.ble_max_act = CONFIG_BT_CTRL_BLE_MAX_ACT_EFF,                         \
	.sleep_mode = CONFIG_BT_CTRL_SLEEP_MODE_EFF,                           \
	.sleep_clock = CONFIG_BT_CTRL_SLEEP_CLOCK_EFF,                         \
	.ble_st_acl_tx_buf_nb = CONFIG_BT_CTRL_BLE_STATIC_ACL_TX_BUF_NB,       \
	.ble_hw_cca_check = CONFIG_BT_CTRL_HW_CCA_EFF,                         \
	.ble_adv_dup_filt_max = CONFIG_BT_CTRL_ADV_DUP_FILT_MAX,               \
	.coex_param_en = false,                                                \
	.ce_len_type = CONFIG_BT_CTRL_CE_LENGTH_TYPE_EFF,                      \
	.coex_use_hooks = false,                                               \
	.hci_tl_type = CONFIG_BT_CTRL_HCI_TL_EFF,                              \
	.hci_tl_funcs = NULL,                                                  \
	.txant_dft = CONFIG_BT_CTRL_TX_ANTENNA_INDEX_EFF,                      \
	.rxant_dft = CONFIG_BT_CTRL_RX_ANTENNA_INDEX_EFF,                      \
	.txpwr_dft = CONFIG_BT_CTRL_DFT_TX_POWER_LEVEL_EFF,                    \
	.cfg_mask = CFG_MASK,                                                  \
	.scan_duplicate_mode = SCAN_DUPLICATE_MODE,                            \
	.scan_duplicate_type = SCAN_DUPLICATE_TYPE_VALUE,                      \
	.normal_adv_size = NORMAL_SCAN_DUPLICATE_CACHE_SIZE,                   \
	.mesh_adv_size = MESH_DUPLICATE_SCAN_CACHE_SIZE,                       \
	.coex_phy_coded_tx_rx_time_limit = CONFIG_BT_CTRL_COEX_PHY_CODED_TX_RX_TLIM_EFF, \
	.hw_target_code = BLE_HW_TARGET_CODE_ESP32S3_CHIP_ECO0,                \
	.slave_ce_len_min = SLAVE_CE_LEN_MIN_DEFAULT,                          \
	.hw_recorrect_en = AGC_RECORRECT_EN,                                   \
	.cca_thresh = CONFIG_BT_CTRL_HW_CCA_VAL,                               \
	.scan_backoff_upperlimitmax = BT_CTRL_SCAN_BACKOFF_UPPERLIMITMAX,      \
}

typedef struct {
	uint32_t _magic;                        /* Magic number */
	uint32_t _version;                      /* version number of the defined structure */
	uint32_t _reserved;                     /* reserved for future use */
	int (* _open)(void);                    /* hci tl open */
	void (* _close)(void);                  /* hci tl close */
	void (* _finish_transfers)(void);       /* hci tl finish trasnfers */
	void (* _recv)(uint8_t *buf, uint32_t len, esp_bt_hci_tl_callback_t callback, void* arg); /* hci tl recv */
	void (* _send)(uint8_t *buf, uint32_t len, esp_bt_hci_tl_callback_t callback, void* arg); /* hci tl send */
	bool (* _flow_off)(void); /* hci tl flow off */
	void (* _flow_on)(void); /* hci tl flow on */
} esp_bt_hci_tl_t;

typedef struct {
	uint32_t magic;                         /*!< Magic number */
	uint32_t version;                       /*!< version number of the defined structure */
	uint16_t controller_task_stack_size;    /*!< Bluetooth controller task stack size */
	uint8_t controller_task_prio;           /*!< Bluetooth controller task priority */
	uint8_t controller_task_run_cpu;        /*!< CPU num that Bluetooth controller task runs on */
	uint8_t bluetooth_mode;                 /*!< Controller mode: BR/EDR, BLE or Dual Mode */
	uint8_t ble_max_act;                    /*!< BLE maximum number of air activities */
	uint8_t sleep_mode;                     /*!< controller sleep mode */
	uint8_t sleep_clock;                    /*!< controller sleep clock */
	uint8_t ble_st_acl_tx_buf_nb;           /*!< controller static ACL TX BUFFER number */
	uint8_t ble_hw_cca_check;               /*!< controller hardware triggered CCA check */
	uint16_t ble_adv_dup_filt_max;          /*!< maxinum number of duplicate scan filter */
	bool coex_param_en;                     /*!< deprecated */
	uint8_t ce_len_type;                    /*!< connection event length computation method */
	bool coex_use_hooks;                    /*!< deprecated */
	uint8_t hci_tl_type;                    /*!< HCI transport layer, UART, VHCI, etc */
	esp_bt_hci_tl_t *hci_tl_funcs;          /*!< hci transport functions used, must be set when hci_tl_type is UART */
	uint8_t txant_dft;                      /*!< default Tx antenna */
	uint8_t rxant_dft;                      /*!< default Rx antenna */
	uint8_t txpwr_dft;                      /*!< default Tx power */
	uint32_t cfg_mask;
	uint8_t scan_duplicate_mode;            /*!< scan duplicate mode */
	uint8_t scan_duplicate_type;            /*!< scan duplicate type */
	uint16_t normal_adv_size;               /*!< Normal adv size for scan duplicate */
	uint16_t mesh_adv_size;                 /*!< Mesh adv size for scan duplicate */
	uint8_t coex_phy_coded_tx_rx_time_limit;  /*!< limit on max tx/rx time in case of connection using CODED-PHY with Wi-Fi coexistence */
	uint32_t hw_target_code;                /*!< hardware target */
	uint8_t slave_ce_len_min;               /*!< slave minimum ce length*/
	uint8_t hw_recorrect_en;
	uint8_t cca_thresh;                     /*!< cca threshold*/
	uint16_t scan_backoff_upperlimitmax;    /*!< scan backoff upperlimitmax value */
} esp_bt_controller_config_t;

typedef enum {
	ESP_BT_CONTROLLER_STATUS_IDLE = 0,
	ESP_BT_CONTROLLER_STATUS_INITED,
	ESP_BT_CONTROLLER_STATUS_ENABLED,
	ESP_BT_CONTROLLER_STATUS_NUM,
} esp_bt_controller_status_t;

typedef enum {
	ESP_BLE_PWR_TYPE_CONN_HDL0  = 0,            /*!< For connection handle 0 */
	ESP_BLE_PWR_TYPE_CONN_HDL1  = 1,            /*!< For connection handle 1 */
	ESP_BLE_PWR_TYPE_CONN_HDL2  = 2,            /*!< For connection handle 2 */
	ESP_BLE_PWR_TYPE_CONN_HDL3  = 3,            /*!< For connection handle 3 */
	ESP_BLE_PWR_TYPE_CONN_HDL4  = 4,            /*!< For connection handle 4 */
	ESP_BLE_PWR_TYPE_CONN_HDL5  = 5,            /*!< For connection handle 5 */
	ESP_BLE_PWR_TYPE_CONN_HDL6  = 6,            /*!< For connection handle 6 */
	ESP_BLE_PWR_TYPE_CONN_HDL7  = 7,            /*!< For connection handle 7 */
	ESP_BLE_PWR_TYPE_CONN_HDL8  = 8,            /*!< For connection handle 8 */
	ESP_BLE_PWR_TYPE_ADV        = 9,            /*!< For advertising */
	ESP_BLE_PWR_TYPE_SCAN       = 10,           /*!< For scan */
	ESP_BLE_PWR_TYPE_DEFAULT    = 11,           /*!< For default, if not set other, it will use default value */
	ESP_BLE_PWR_TYPE_NUM        = 12,           /*!< TYPE numbers */
} esp_ble_power_type_t;

typedef enum {
	ESP_PWR_LVL_N24 = 0,              /*!< Corresponding to -24dbm */
	ESP_PWR_LVL_N21 = 1,              /*!< Corresponding to -21dbm */
	ESP_PWR_LVL_N18 = 2,              /*!< Corresponding to -18dbm */
	ESP_PWR_LVL_N15 = 3,              /*!< Corresponding to -15dbm */
	ESP_PWR_LVL_N12 = 4,              /*!< Corresponding to -12dbm */
	ESP_PWR_LVL_N9  = 5,              /*!< Corresponding to  -9dbm */
	ESP_PWR_LVL_N6  = 6,              /*!< Corresponding to  -6dbm */
	ESP_PWR_LVL_N3  = 7,              /*!< Corresponding to  -3dbm */
	ESP_PWR_LVL_N0  = 8,              /*!< Corresponding to   0dbm */
	ESP_PWR_LVL_P3  = 9,              /*!< Corresponding to  +3dbm */
	ESP_PWR_LVL_P6  = 10,             /*!< Corresponding to  +6dbm */
	ESP_PWR_LVL_P9  = 11,             /*!< Corresponding to  +9dbm */
	ESP_PWR_LVL_P12 = 12,             /*!< Corresponding to  +12dbm */
	ESP_PWR_LVL_P15 = 13,             /*!< Corresponding to  +15dbm */
	ESP_PWR_LVL_P18 = 14,             /*!< Corresponding to  +18dbm */
	ESP_PWR_LVL_P21 = 15,             /*!< Corresponding to  +21dbm */
	ESP_PWR_LVL_INVALID = 0xFF,         /*!< Indicates an invalid value */
} esp_power_level_t;

int esp_ble_tx_power_set(esp_ble_power_type_t power_type, esp_power_level_t power_level);
esp_power_level_t esp_ble_tx_power_get(esp_ble_power_type_t power_type);
int esp_bt_controller_init(esp_bt_controller_config_t *cfg);
int esp_bt_controller_deinit(void);
int esp_bt_controller_enable(esp_bt_mode_t mode);
int esp_bt_controller_disable(void);
esp_bt_controller_status_t esp_bt_controller_get_status(void);

uint16_t esp_bt_get_tx_buf_num(void);
typedef struct esp_vhci_host_callback {
	void (*notify_host_send_available)(void);               /*!< callback used to notify that the host can send packet to controller */
	int (*notify_host_recv)(uint8_t *data, uint16_t len);   /*!< callback used to notify that the controller has a packet to send to the host*/
} esp_vhci_host_callback_t;
bool esp_vhci_host_check_send_available(void);
void esp_vhci_host_send_packet(uint8_t *data, uint16_t len);
int esp_vhci_host_register_callback(const esp_vhci_host_callback_t *callback);
int esp_bt_controller_mem_release(esp_bt_mode_t mode);
int esp_bt_mem_release(esp_bt_mode_t mode);
int esp_bt_sleep_enable(void);
int esp_bt_sleep_disable(void);
bool esp_bt_controller_is_sleeping(void);
void esp_bt_controller_wakeup_request(void);
int esp_bt_h4tl_eif_io_event_notify(int event);
void esp_wifi_bt_power_domain_on(void);

void esp_wifi_bt_power_domain_off(void);
