#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "bluetooth/bluetooth.h"

#include "heap/esp_heap_caps.h"
#include "heap/esp_heap_caps_init.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/xtensa_api.h"
#include "freertos/portmacro.h"
#include "xtensa/xtensa_intr.h"
#include "timer/esp_timer.h"
#include "rom/rom_layout.h"
#include "soc/peripherals.h"
#include "rom/ets_sys.h"
#include "soc/gpio.h"
#include "soc/hmac.h"
#include "rom/efuse.h"
//#include "soc/efuse.h"
#include "soc/random.h"
#include "soc/phy.h"

#define ESP_MAC_ADDRESS_LEN 8
#define ESP_ERROR_CHECK(...)

#define MAC_BT ((uint8_t[6]){0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1})
#define BT_LOG_TAG                        "BT_INIT"

#define BTDM_INIT_PERIOD                    (5000)    /* ms */

/* Low Power Clock Selection */
#define BTDM_LPCLK_SEL_XTAL      (0)
#define BTDM_LPCLK_SEL_XTAL32K   (1)
#define BTDM_LPCLK_SEL_RTC_SLOW  (2)
#define BTDM_LPCLK_SEL_8M        (3)


#define MAC_ADDR_UNIVERSE_BT_OFFSET 2
#define ESP_MAC_ADDRESS_LEN 8

static uint8_t base_mac_addr[ESP_MAC_ADDRESS_LEN];
static const esp_efuse_desc_t MAC_FACTORY[] = {
	{EFUSE_BLK1, 40, 8}, 	 // Factory MAC addr [0],
	{EFUSE_BLK1, 32, 8}, 	 // Factory MAC addr [1],
	{EFUSE_BLK1, 24, 8}, 	 // Factory MAC addr [2],
	{EFUSE_BLK1, 16, 8}, 	 // Factory MAC addr [3],
	{EFUSE_BLK1, 8, 8}, 	 // Factory MAC addr [4],
	{EFUSE_BLK1, 0, 8}, 	 // Factory MAC addr [5],
};


int esp_base_mac_addr_set(const uint8_t *mac)
{
	if (mac == NULL) {
		return EINVAL;
	}
	if (mac[0] & 0x01) {
		return EINVAL;
	}

	memcpy(base_mac_addr, mac, ESP_MAC_ADDRESS_LEN);

	return 0;
}

int esp_base_mac_addr_get(uint8_t *mac)
{
	if (mac == NULL) {
		return EINVAL;
	}
	if (base_mac_addr[0] == 0 && memcmp(base_mac_addr, &base_mac_addr[1], ESP_MAC_ADDRESS_LEN - 1) == 0) {
		return EINVAL;
	}

	memcpy(mac, base_mac_addr, ESP_MAC_ADDRESS_LEN);

	return 0;
}

extern const esp_efuse_desc_t* ESP_EFUSE_USER_DATA_MAC_CUSTOM[];
extern const esp_efuse_desc_t* ESP_EFUSE_MAC_EXT[];
extern const esp_efuse_desc_t* ESP_EFUSE_MAC_FACTORY[];


int esp_efuse_mac_get_custom(uint8_t *mac)
{
	size_t size_bits = esp_efuse_get_field_size(ESP_EFUSE_USER_DATA_MAC_CUSTOM);
	assert((size_bits % 8) == 0);
	int err = esp_efuse_read_field_blob(ESP_EFUSE_USER_DATA_MAC_CUSTOM, mac, size_bits);
	if (err != 0) {
		return err;
	}
	size_t size = size_bits / 8;
	if (mac[0] == 0 && memcmp(mac, &mac[1], size - 1) == 0) {
		return EINVAL;
	}
	err = esp_efuse_read_field_blob(ESP_EFUSE_MAC_EXT, &mac[6], ESP_MAC_ADDRESS_LEN * 8 - size_bits);
	if (err != 0) {
		return err;
	}
	return 0;
}

int esp_efuse_mac_get_default(uint8_t *mac)
{
	size_t size_bits = esp_efuse_get_field_size(ESP_EFUSE_MAC_FACTORY);
	assert((size_bits % 8) == 0);
	int err = esp_efuse_read_field_blob(ESP_EFUSE_MAC_FACTORY, mac, size_bits);
	if (err != 0) {
		return err;
	}
	err = esp_efuse_read_field_blob(ESP_EFUSE_MAC_EXT, &mac[6], ESP_MAC_ADDRESS_LEN * 8 - size_bits);
	if (err != 0) {
		return err;
	}
	return 0;
}

int esp_derive_local_mac(uint8_t *local_mac, const uint8_t *universal_mac)
{
	if (local_mac == NULL || universal_mac == NULL) {
		return EINVAL;
	}

	memcpy(local_mac, universal_mac, 6);

	const unsigned UL_BIT = 0x2;
	local_mac[0] |= UL_BIT;

	if (local_mac[0] == universal_mac[0]) {
		// universal_mac was already local, so flip this bit instead
		// (this is kept to be compatible with the previous behaviour of this function)
		local_mac[0] ^= 0x4;
	}

	return 0;
}


int esp_read_mac(uint8_t *mac, esp_mac_type_t type) {
	uint8_t efuse_mac[ESP_MAC_ADDRESS_LEN];

	if (mac == NULL) {
		return EINVAL;
	}

	if (type < ESP_MAC_WIFI_STA || type > ESP_MAC_IEEE802154) {
		return EINVAL;
	}

	// if base mac address is not set, read one from EFUSE and then write back
	if (esp_base_mac_addr_get(efuse_mac) != 0) {
		esp_efuse_mac_get_default(efuse_mac);
		esp_base_mac_addr_set(efuse_mac);
	}

	switch (type) {
	case ESP_MAC_WIFI_STA:
		memcpy(mac, efuse_mac, 6);
		break;
	case ESP_MAC_WIFI_SOFTAP:
		esp_derive_local_mac(mac, efuse_mac);
		break;
	case ESP_MAC_BT:
		memcpy(mac, efuse_mac, 6);
		break;
	case ESP_MAC_ETH:
		efuse_mac[5] += 1;
		esp_derive_local_mac(mac, efuse_mac);
		break;
	case ESP_MAC_IEEE802154:
		memcpy(mac, efuse_mac, 8);
		break;
	default:
		break;
	}

	return 0;
}



// wakeup request sources
enum {
	BTDM_ASYNC_WAKEUP_SRC_VHCI = 0,
	BTDM_ASYNC_WAKEUP_SRC_DISA,
	BTDM_ASYNC_WAKEUP_SRC_TMR,
	BTDM_ASYNC_WAKEUP_SRC_MAX,
};

// low power control struct
typedef union {
	struct {
		uint32_t enable                  :  1; // whether low power mode is required
		uint32_t lpclk_sel               :  2; // low power clock source
		uint32_t mac_bb_pd               :  1; // whether hardware(MAC, BB) force-power-down is required during sleep
		uint32_t wakeup_timer_required   :  1; // whether system timer is needed
		uint32_t no_light_sleep          :  1; // do not allow system to enter light sleep after bluetooth is enabled
		uint32_t main_xtal_pu            :  1; // power up main XTAL
		uint32_t reserved                : 25; // reserved
	};
	uint32_t val;
} btdm_lpcntl_t;

// low power control status
typedef union {
	struct {
		uint32_t pm_lock_released        :  1; // whether power management lock is released
		uint32_t mac_bb_pd               :  1; // whether hardware(MAC, BB) is powered down
		uint32_t phy_enabled             :  1; // whether phy is switched on
		uint32_t wakeup_timer_started    :  1; // whether wakeup timer is started
		uint32_t reserved                : 28; // reserved
	};
	uint32_t val;
} btdm_lpstat_t;

/* Sleep and wakeup interval control */
#define BTDM_MIN_SLEEP_DURATION          (24) // threshold of interval in half slots to allow to fall into modem sleep
#define BTDM_MODEM_WAKE_UP_DELAY         (8)  // delay in half slots of modem wake up procedure, including re-enable PHY/RF

#define BT_DEBUG(...)
#define BT_API_CALL_CHECK(info, api_call, ret) \
do{\
	int __err = (api_call);\
	if ((ret) != __err) {\
		BT_DEBUG("%s %d %s ret=0x%X\n", __FUNCTION__, __LINE__, (info), __err);\
		return __err;\
	}\
} while(0)

#define OSI_FUNCS_TIME_BLOCKING  0xffffffff
#define OSI_VERSION              0x00010006
#define OSI_MAGIC_VALUE          0xFADEBEAD

/* Types definition
 ************************************************************************
 */
/* vendor dependent signals to be posted to controller task */
typedef enum {
	BTDM_VND_OL_SIG_WAKEUP_TMR = 0,
	BTDM_VND_OL_SIG_NUM,
} btdm_vnd_ol_sig_t;

/* prototype of function to handle vendor dependent signals */
typedef void (* btdm_vnd_ol_task_func_t)(void *param);

/* VHCI function interface */
typedef struct vhci_host_callback {
	void (*notify_host_send_available)(void);               /*!< callback used to notify that the host can send packet to controller */
	int (*notify_host_recv)(uint8_t *data, uint16_t len);   /*!< callback used to notify that the controller has a packet to send to the host*/
} vhci_host_callback_t;

/* Dram region */
typedef struct {
	esp_bt_mode_t mode;
	intptr_t start;
	intptr_t end;
} btdm_dram_available_region_t;

typedef struct {
	void *handle;
	void *storage;
} btdm_queue_item_t;

typedef void (* osi_intr_handler)(void);

/* OSI function */
struct osi_funcs_t {
	uint32_t _magic;
	uint32_t _version;
	void (*_interrupt_set)(int32_t cpu_no, int32_t intr_source, int32_t interrupt_no, int32_t interrpt_prio);
	void (*_interrupt_clear)(int32_t interrupt_source, int32_t interrupt_no);
	void (*_interrupt_handler_set)(int32_t interrupt_no, void *fn, void *arg);
	void (*_interrupt_disable)(void);
	void (*_interrupt_restore)(void);
	void (*_task_yield)(void);
	void (*_task_yield_from_isr)(void);
	void *(*_semphr_create)(uint32_t max, uint32_t init);
	void (*_semphr_delete)(void *semphr);
	int32_t (*_semphr_take_from_isr)(void *semphr, void *hptw);
	int32_t (*_semphr_give_from_isr)(void *semphr, void *hptw);
	int32_t (*_semphr_take)(void *semphr, uint32_t block_time_ms);
	int32_t (*_semphr_give)(void *semphr);
	void *(*_mutex_create)(void);
	void (*_mutex_delete)(void *mutex);
	int32_t (*_mutex_lock)(void *mutex);
	int32_t (*_mutex_unlock)(void *mutex);
	void *(* _queue_create)(uint32_t queue_len, uint32_t item_size);
	void (* _queue_delete)(void *queue);
	int32_t (* _queue_send)(void *queue, void *item, uint32_t block_time_ms);
	int32_t (* _queue_send_from_isr)(void *queue, void *item, void *hptw);
	int32_t (* _queue_recv)(void *queue, void *item, uint32_t block_time_ms);
	int32_t (* _queue_recv_from_isr)(void *queue, void *item, void *hptw);
	int32_t (* _task_create)(void *task_func, const char *name, uint32_t stack_depth, void *param, uint32_t prio, void *task_handle, uint32_t core_id);
	void (* _task_delete)(void *task_handle);
	bool (* _is_in_isr)(void);
	int (* _cause_sw_intr_to_core)(int core_id, int intr_no);
	void *(* _malloc)(size_t size);
	void *(* _malloc_internal)(size_t size);
	void (* _free)(void *p);
	int32_t (* _read_efuse_mac)(uint8_t mac[6]);
	void (* _srand)(unsigned int seed);
	int (* _rand)(void);
	uint32_t (* _btdm_lpcycles_2_hus)(uint32_t cycles, uint32_t *error_corr);
	uint32_t (* _btdm_hus_2_lpcycles)(uint32_t hus);
	bool (* _btdm_sleep_check_duration)(int32_t *slot_cnt);
	void (* _btdm_sleep_enter_phase1)(uint32_t lpcycles);  /* called when interrupt is disabled */
	void (* _btdm_sleep_enter_phase2)(void);
	void (* _btdm_sleep_exit_phase1)(void);  /* called from ISR */
	void (* _btdm_sleep_exit_phase2)(void);  /* called from ISR */
	void (* _btdm_sleep_exit_phase3)(void);  /* called from task */
	void (* _coex_wifi_sleep_set)(bool sleep);
	int (* _coex_core_ble_conn_dyn_prio_get)(bool *low, bool *high);
	void (* _coex_schm_status_bit_set)(uint32_t type, uint32_t status);
	void (* _coex_schm_status_bit_clear)(uint32_t type, uint32_t status);
	void (* _interrupt_on)(int intr_num);
	void (* _interrupt_off)(int intr_num);
	void (* _esp_hw_power_down)(void);
	void (* _esp_hw_power_up)(void);
	void (* _ets_backup_dma_copy)(uint32_t reg, uint32_t mem_addr, uint32_t num, bool to_rem);
};


/* External functions or values
 ************************************************************************
 */

/* not for user call, so don't put to include file */
/* OSI */
extern int btdm_osi_funcs_register(void *osi_funcs);
/* Initialise and De-initialise */
extern int btdm_controller_init(esp_bt_controller_config_t *config_opts);
extern void btdm_controller_deinit(void);
extern int btdm_controller_enable(esp_bt_mode_t mode);
extern void btdm_controller_disable(void);
extern uint8_t btdm_controller_get_mode(void);
extern const char *btdm_controller_get_compile_version(void);
extern void btdm_rf_bb_init_phase2(void); // shall be called after PHY/RF is enabled
/* Sleep */
extern void btdm_controller_enable_sleep(bool enable);
extern uint8_t btdm_controller_get_sleep_mode(void);
extern bool btdm_power_state_active(void);
extern void btdm_wakeup_request(void);
extern void btdm_in_wakeup_requesting_set(bool in_wakeup_requesting);

/* vendor dependent tasks to be posted and handled by controller task*/
extern int btdm_vnd_offload_task_register(btdm_vnd_ol_sig_t sig, btdm_vnd_ol_task_func_t func);
extern int btdm_vnd_offload_task_deregister(btdm_vnd_ol_sig_t sig);
extern int btdm_vnd_offload_post_from_isr(btdm_vnd_ol_sig_t sig, void *param, bool need_yield);
extern int btdm_vnd_offload_post(btdm_vnd_ol_sig_t sig, void *param);

/* Low Power Clock */
extern bool btdm_lpclk_select_src(uint32_t sel);
extern bool btdm_lpclk_set_div(uint32_t div);
extern int btdm_hci_tl_io_event_post(int event);

/* VHCI */
extern bool API_vhci_host_check_send_available(void);
extern void API_vhci_host_send_packet(uint8_t *data, uint16_t len);
extern int API_vhci_host_register_callback(const vhci_host_callback_t *callback);
/* TX power */
extern int ble_txpwr_set(int power_type, int power_level);
extern int ble_txpwr_get(int power_type);

extern uint16_t l2c_ble_link_get_tx_buf_num(void);
extern int coex_core_ble_conn_dyn_prio_get(bool *low, bool *high);
extern void coex_pti_v2(void);

extern bool btdm_deep_sleep_mem_init(void);
extern void btdm_deep_sleep_mem_deinit(void);
extern void btdm_ble_power_down_dma_copy(bool copy);
extern uint8_t btdm_sleep_clock_sync(void);

#if CONFIG_MAC_BB_PD
extern void esp_mac_bb_power_down(void);
extern void esp_mac_bb_power_up(void);
extern void ets_backup_dma_copy(uint32_t reg, uint32_t mem_addr, uint32_t num, bool to_mem);
#endif

extern uint32_t _bt_bss_start;
extern uint32_t _bt_bss_end;
extern uint32_t _btdm_bss_start;
extern uint32_t _btdm_bss_end;
extern uint32_t _nimble_bss_start;
extern uint32_t _nimble_bss_end;
extern uint32_t _bt_data_start;
extern uint32_t _bt_data_end;
extern uint32_t _btdm_data_start;
extern uint32_t _btdm_data_end;
extern uint32_t _nimble_data_start;
extern uint32_t _nimble_data_end;

/* Local Function Declare
 *********************************************************************
 */
static void interrupt_set_wrapper(int32_t cpu_no, int32_t intr_source, int32_t intr_num, int32_t intr_prio);
static void interrupt_clear_wrapper(int32_t intr_source, int32_t intr_num);
static void interrupt_handler_set_wrapper(int n, void *fn, void *arg);
static void interrupt_disable(void);
static void interrupt_restore(void);
static void task_yield_from_isr(void);
static void *semphr_create_wrapper(uint32_t max, uint32_t init);
static void semphr_delete_wrapper(void *semphr);
static int32_t semphr_take_from_isr_wrapper(void *semphr, void *hptw);
static int32_t semphr_give_from_isr_wrapper(void *semphr, void *hptw);
static int32_t  semphr_take_wrapper(void *semphr, uint32_t block_time_ms);
static int32_t  semphr_give_wrapper(void *semphr);
static void *mutex_create_wrapper(void);
static void mutex_delete_wrapper(void *mutex);
static int32_t mutex_lock_wrapper(void *mutex);
static int32_t mutex_unlock_wrapper(void *mutex);
static void *queue_create_wrapper(uint32_t queue_len, uint32_t item_size);
static void queue_delete_wrapper(void *queue);
static int32_t queue_send_wrapper(void *queue, void *item, uint32_t block_time_ms);
static int32_t queue_send_from_isr_wrapper(void *queue, void *item, void *hptw);
static int32_t queue_recv_wrapper(void *queue, void *item, uint32_t block_time_ms);
static int32_t queue_recv_from_isr_wrapper(void *queue, void *item, void *hptw);
static int32_t task_create_wrapper(void *task_func, const char *name, uint32_t stack_depth, void *param, uint32_t prio, void *task_handle, uint32_t core_id);
static void task_delete_wrapper(void *task_handle);
static bool is_in_isr_wrapper(void);
static void *malloc_internal_wrapper(size_t size);
static int32_t read_mac_wrapper(uint8_t mac[6]);
static void srand_wrapper(unsigned int seed);
static int rand_wrapper(void);
static uint32_t btdm_lpcycles_2_hus(uint32_t cycles, uint32_t *error_corr);
static uint32_t btdm_hus_2_lpcycles(uint32_t hus);
static bool btdm_sleep_check_duration(int32_t *slot_cnt);
static void btdm_sleep_enter_phase1_wrapper(uint32_t lpcycles);
static void btdm_sleep_enter_phase2_wrapper(void);
static void btdm_sleep_exit_phase3_wrapper(void);
static void coex_wifi_sleep_set_hook(bool sleep);
static void coex_schm_status_bit_set_wrapper(uint32_t type, uint32_t status);
static void coex_schm_status_bit_clear_wrapper(uint32_t type, uint32_t status);
static void interrupt_on_wrapper(int intr_num);
static void interrupt_off_wrapper(int intr_num);
static void btdm_hw_mac_power_up_wrapper(void);
static void btdm_hw_mac_power_down_wrapper(void);
static void btdm_backup_dma_copy_wrapper(uint32_t reg, uint32_t mem_addr, uint32_t num,  bool to_mem);

static void btdm_slp_tmr_callback(void *arg);

static int try_heap_caps_add_region(intptr_t start, intptr_t end);

/* Local variable definition
 ***************************************************************************
 */
/* OSI funcs */
static const struct osi_funcs_t osi_funcs_ro = {
	._magic = OSI_MAGIC_VALUE,
	._version = OSI_VERSION,
	._interrupt_set = interrupt_set_wrapper,
	._interrupt_clear = interrupt_clear_wrapper,
	._interrupt_handler_set = interrupt_handler_set_wrapper,
	._interrupt_disable = interrupt_disable,
	._interrupt_restore = interrupt_restore,
	._task_yield = vPortYield,
	._task_yield_from_isr = task_yield_from_isr,
	._semphr_create = semphr_create_wrapper,
	._semphr_delete = semphr_delete_wrapper,
	._semphr_take_from_isr = semphr_take_from_isr_wrapper,
	._semphr_give_from_isr = semphr_give_from_isr_wrapper,
	._semphr_take = semphr_take_wrapper,
	._semphr_give = semphr_give_wrapper,
	._mutex_create = mutex_create_wrapper,
	._mutex_delete = mutex_delete_wrapper,
	._mutex_lock = mutex_lock_wrapper,
	._mutex_unlock = mutex_unlock_wrapper,
	._queue_create = queue_create_wrapper,
	._queue_delete = queue_delete_wrapper,
	._queue_send = queue_send_wrapper,
	._queue_send_from_isr = queue_send_from_isr_wrapper,
	._queue_recv = queue_recv_wrapper,
	._queue_recv_from_isr = queue_recv_from_isr_wrapper,
	._task_create = task_create_wrapper,
	._task_delete = task_delete_wrapper,
	._is_in_isr = is_in_isr_wrapper,
	._cause_sw_intr_to_core = NULL,
	._malloc = malloc,
	._malloc_internal = malloc_internal_wrapper,
	._free = free,
	._read_efuse_mac = read_mac_wrapper,
	._srand = srand_wrapper,
	._rand = rand_wrapper,
	._btdm_lpcycles_2_hus = btdm_lpcycles_2_hus,
	._btdm_hus_2_lpcycles = btdm_hus_2_lpcycles,
	._btdm_sleep_check_duration = btdm_sleep_check_duration,
	._btdm_sleep_enter_phase1 = btdm_sleep_enter_phase1_wrapper,
	._btdm_sleep_enter_phase2 = btdm_sleep_enter_phase2_wrapper,
	._btdm_sleep_exit_phase1 = NULL,
	._btdm_sleep_exit_phase2 = NULL,
	._btdm_sleep_exit_phase3 = btdm_sleep_exit_phase3_wrapper,
	._coex_wifi_sleep_set = coex_wifi_sleep_set_hook,
	._coex_core_ble_conn_dyn_prio_get = coex_core_ble_conn_dyn_prio_get,
	._coex_schm_status_bit_set = coex_schm_status_bit_set_wrapper,
	._coex_schm_status_bit_clear = coex_schm_status_bit_clear_wrapper,
	._interrupt_on = interrupt_on_wrapper,
	._interrupt_off = interrupt_off_wrapper,
	._esp_hw_power_down = btdm_hw_mac_power_down_wrapper,
	._esp_hw_power_up = btdm_hw_mac_power_up_wrapper,
	._ets_backup_dma_copy = btdm_backup_dma_copy_wrapper,
};

static DRAM_ATTR struct osi_funcs_t *osi_funcs_p;

/* Static variable declare */
static DRAM_ATTR esp_bt_controller_status_t btdm_controller_status = ESP_BT_CONTROLLER_STATUS_IDLE;

static DRAM_ATTR portMUX_TYPE global_int_mux = portMUX_INITIALIZER_UNLOCKED;

// low power control struct
static DRAM_ATTR btdm_lpcntl_t s_lp_cntl;
// low power status struct
static DRAM_ATTR btdm_lpstat_t s_lp_stat;
// measured average low power clock period in micro seconds
static DRAM_ATTR uint32_t btdm_lpcycle_us = 0;
// number of fractional bit for btdm_lpcycle_us
static DRAM_ATTR uint8_t btdm_lpcycle_us_frac = 0;
// semaphore used for blocking VHCI API to wait for controller to wake up
static DRAM_ATTR QueueHandle_t s_wakeup_req_sem = NULL;
// wakeup timer
static DRAM_ATTR esp_timer_handle_t s_btdm_slp_tmr;

#ifdef CONFIG_PM_ENABLE
static DRAM_ATTR esp_pm_lock_handle_t s_pm_lock;
// pm_lock to prevent light sleep due to incompatibility currently
static DRAM_ATTR esp_pm_lock_handle_t s_light_sleep_pm_lock;
#endif

void btdm_hw_mac_power_down_wrapper(void)
{
#if CONFIG_MAC_BB_PD
	esp_mac_bb_power_down();
#endif
}

void btdm_hw_mac_power_up_wrapper(void)
{
#if CONFIG_MAC_BB_PD
	esp_mac_bb_power_up();
#endif
}

void btdm_backup_dma_copy_wrapper(uint32_t reg, uint32_t mem_addr, uint32_t num,  bool to_mem)
{
#if CONFIG_MAC_BB_PD
	ets_backup_dma_copy(reg, mem_addr, num, to_mem);
#endif
}

static inline void esp_bt_power_domain_on(void)
{
	// Bluetooth module power up
	esp_wifi_bt_power_domain_on();
}

static inline void esp_bt_power_domain_off(void)
{
	// Bluetooth module power down
	esp_wifi_bt_power_domain_off();
}

static void interrupt_set_wrapper(int32_t cpu_no, int32_t intr_source, int32_t intr_num, int32_t intr_prio)
{
	intr_matrix_set(cpu_no, intr_source, intr_num);
}

static void interrupt_clear_wrapper(int32_t intr_source, int32_t intr_num)
{
}

static void interrupt_handler_set_wrapper(int32_t n, void *fn, void *arg)
{
	xt_set_interrupt_handler(n, (xt_handler)fn, arg);
}

static void interrupt_on_wrapper(int intr_num)
{
	xt_ints_on(1 << intr_num);
}

static void interrupt_off_wrapper(int intr_num)
{
	xt_ints_off(1 << intr_num);
}

static void interrupt_disable(void)
{
	if (xPortInIsrContext()) {
		portENTER_CRITICAL_ISR(&global_int_mux);
	} else {
		portENTER_CRITICAL(&global_int_mux);
	}
}

static void interrupt_restore(void)
{
	if (xPortInIsrContext()) {
		portEXIT_CRITICAL_ISR(&global_int_mux);
	} else {
		portEXIT_CRITICAL(&global_int_mux);
	}
}

static void task_yield_from_isr(void)
{
	portYIELD_FROM_ISR();
}

static void *semphr_create_wrapper(uint32_t max, uint32_t init)
{
	btdm_queue_item_t *semphr = heap_caps_calloc(1, sizeof(btdm_queue_item_t), MALLOC_CAP_8BIT|MALLOC_CAP_INTERNAL);
	assert(semphr);

#if !CONFIG_SPIRAM_USE_MALLOC
	semphr->handle = (void *)xSemaphoreCreateCounting(max, init);
#else

	semphr->storage = heap_caps_malloc(sizeof(StaticQueue_t), MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT);
	assert(semphr->storage);

	semphr->handle = (void *)xSemaphoreCreateCountingStatic(max, init, semphr->storage);
#endif
	assert(semphr->handle);
	return semphr;
}

static void semphr_delete_wrapper(void *semphr)
{
	if (semphr == NULL) {
		return;
	}

	btdm_queue_item_t *semphr_item = (btdm_queue_item_t *)semphr;

	if (semphr_item->handle) {
		vSemaphoreDelete(semphr_item->handle);
	}
#ifdef CONFIG_SPIRAM_USE_MALLOC
	if (semphr_item->storage) {
		free(semphr_item->storage);
	}
#endif

	free(semphr);
}

static int semphr_take_from_isr_wrapper(void *semphr, void *hptw)
{
	return (int)xSemaphoreTakeFromISR(((btdm_queue_item_t *)semphr)->handle, hptw);
}

static int semphr_give_from_isr_wrapper(void *semphr, void *hptw)
{
	return (int)xSemaphoreGiveFromISR(((btdm_queue_item_t *)semphr)->handle, hptw);
}

static int semphr_take_wrapper(void *semphr, uint32_t block_time_ms)
{
	if (block_time_ms == OSI_FUNCS_TIME_BLOCKING) {
		return (int)xSemaphoreTake(((btdm_queue_item_t *)semphr)->handle, portMAX_DELAY);
	} else {
		return (int)xSemaphoreTake(((btdm_queue_item_t *)semphr)->handle, block_time_ms / portTICK_PERIOD_MS);
	}
}

static int semphr_give_wrapper(void *semphr)
{
	return (int)xSemaphoreGive(((btdm_queue_item_t *)semphr)->handle);
}

static void *mutex_create_wrapper(void)
{
	return (void *)xSemaphoreCreateMutex();
}

static void mutex_delete_wrapper(void *mutex)
{
	vSemaphoreDelete(mutex);
}

static int mutex_lock_wrapper(void *mutex)
{
	return (int)xSemaphoreTake(mutex, portMAX_DELAY);
}

static int mutex_unlock_wrapper(void *mutex)
{
	return (int)xSemaphoreGive(mutex);
}

static void *queue_create_wrapper(uint32_t queue_len, uint32_t item_size)
{
	btdm_queue_item_t *queue = NULL;

	queue = (btdm_queue_item_t*)heap_caps_malloc(sizeof(btdm_queue_item_t), MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT);
	assert(queue);

#if CONFIG_SPIRAM_USE_MALLOC

	queue->storage = heap_caps_calloc(1, sizeof(StaticQueue_t) + (queue_len*item_size), MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT);
	assert(queue->storage);

	queue->handle = xQueueCreateStatic( queue_len, item_size, ((uint8_t*)(queue->storage)) + sizeof(StaticQueue_t), (StaticQueue_t*)(queue->storage));
	assert(queue->handle);

#else
	queue->handle = xQueueCreate( queue_len, item_size);
	assert(queue->handle);
#endif

	return queue;
}

static void queue_delete_wrapper(void *queue)
{
	btdm_queue_item_t *queue_item = (btdm_queue_item_t *)queue;
	if (queue_item) {
		if(queue_item->handle){
			vQueueDelete(queue_item->handle);
		}

#if CONFIG_SPIRAM_USE_MALLOC
		if (queue_item->storage) {
			free(queue_item->storage);
		}
#endif

		free(queue_item);
	}
}

static int queue_send_wrapper(void *queue, void *item, uint32_t block_time_ms)
{
	if (block_time_ms == OSI_FUNCS_TIME_BLOCKING) {
		return (int)xQueueSend(((btdm_queue_item_t*)queue)->handle, item, portMAX_DELAY);
	} else {
		return (int)xQueueSend(((btdm_queue_item_t*)queue)->handle, item, block_time_ms / portTICK_PERIOD_MS);
	}
}

static int queue_send_from_isr_wrapper(void *queue, void *item, void *hptw)
{
	return (int)xQueueSendFromISR(((btdm_queue_item_t*)queue)->handle, item, hptw);
}

static int queue_recv_wrapper(void *queue, void *item, uint32_t block_time_ms)
{
	if (block_time_ms == OSI_FUNCS_TIME_BLOCKING) {
		return (int)xQueueReceive(((btdm_queue_item_t*)queue)->handle, item, portMAX_DELAY);
	} else {
		return (int)xQueueReceive(((btdm_queue_item_t*)queue)->handle, item, block_time_ms / portTICK_PERIOD_MS);
	}
}

static int queue_recv_from_isr_wrapper(void *queue, void *item, void *hptw)
{
	return (int)xQueueReceiveFromISR(((btdm_queue_item_t*)queue)->handle, item, hptw);
}

static int task_create_wrapper(void *task_func, const char *name, uint32_t stack_depth, void *param, uint32_t prio, void *task_handle, uint32_t core_id)
{
	return (uint32_t)xTaskCreatePinnedToCore(task_func, name, stack_depth, param, prio, task_handle, (core_id < portNUM_PROCESSORS ? core_id : tskNO_AFFINITY));
}

static void task_delete_wrapper(void *task_handle)
{
	vTaskDelete(task_handle);
}

static bool is_in_isr_wrapper(void)
{
	return (bool)xPortInIsrContext();
}

static void *malloc_internal_wrapper(size_t size)
{
	void *p = heap_caps_malloc(size, MALLOC_CAP_DEFAULT|MALLOC_CAP_INTERNAL|MALLOC_CAP_DMA);
	if(p == NULL) {
	}
	return p;
}

static int read_mac_wrapper(uint8_t mac[6])
{
	int ret = esp_read_mac(mac, ESP_MAC_BT);

	return ret;
}

static void srand_wrapper(unsigned int seed)
{
	/* empty function */
}

static int rand_wrapper(void)
{
	return (int)esp_random();
}

static uint32_t btdm_lpcycles_2_hus(uint32_t cycles, uint32_t *error_corr)
{
	uint64_t local_error_corr = (error_corr == NULL) ? 0 : (uint64_t)(*error_corr);
	uint64_t res = (uint64_t)btdm_lpcycle_us * cycles * 2;
	local_error_corr += res;
	res = (local_error_corr >> btdm_lpcycle_us_frac);
	local_error_corr -= (res << btdm_lpcycle_us_frac);
	if (error_corr) {
		*error_corr = (uint32_t) local_error_corr;
	}
	return (uint32_t)res;
}

/*
 * @brief Converts a duration in half us into a number of low power clock cycles.
 */
static uint32_t btdm_hus_2_lpcycles(uint32_t hus)
{
	// The number of sleep duration(us) should not lead to overflow. Thrs: 100s
	// Compute the sleep duration in us to low power clock cycles, with calibration result applied
	// clock measurement is conducted
	uint64_t cycles = ((uint64_t)(hus) << btdm_lpcycle_us_frac) / btdm_lpcycle_us;
	cycles >>= 1;

	return (uint32_t)cycles;
}

static bool btdm_sleep_check_duration(int32_t *half_slot_cnt)
{
	if (*half_slot_cnt < BTDM_MIN_SLEEP_DURATION) {
		return false;
	}
	/* wake up in advance considering the delay in enabling PHY/RF */
	*half_slot_cnt -= BTDM_MODEM_WAKE_UP_DELAY;
	return true;
}

static void btdm_sleep_enter_phase1_wrapper(uint32_t lpcycles)
{
	if (s_lp_cntl.wakeup_timer_required == 0) {
		return;
	}

	// start a timer to wake up and acquire the pm_lock before modem_sleep awakes
	uint32_t us_to_sleep = btdm_lpcycles_2_hus(lpcycles, NULL) >> 1;

#define BTDM_MIN_TIMER_UNCERTAINTY_US      (1800)
	assert(us_to_sleep > BTDM_MIN_TIMER_UNCERTAINTY_US);
	// allow a maximum time uncertainty to be about 488ppm(1/2048) at least as clock drift
	// and set the timer in advance
	uint32_t uncertainty = (us_to_sleep >> 11);
	if (uncertainty < BTDM_MIN_TIMER_UNCERTAINTY_US) {
		uncertainty = BTDM_MIN_TIMER_UNCERTAINTY_US;
	}

	assert (s_lp_stat.wakeup_timer_started == 0);
	if (esp_timer_start_once(s_btdm_slp_tmr, us_to_sleep - uncertainty) == 0) {
		s_lp_stat.wakeup_timer_started = 1;
	} else {
		assert(0);
	}
}

static void btdm_sleep_enter_phase2_wrapper(void)
{
	if (btdm_controller_get_sleep_mode() == ESP_BT_SLEEP_MODE_1) {
		if (s_lp_stat.phy_enabled) {
			esp_phy_disable();
			s_lp_stat.phy_enabled = 0;
		} else {
			assert(0);
		}

		if (s_lp_stat.pm_lock_released == 0) {
#ifdef CONFIG_PM_ENABLE
			esp_pm_lock_release(s_pm_lock);
#endif
			s_lp_stat.pm_lock_released = 1;
		}
	}
}

static void btdm_sleep_exit_phase3_wrapper(void)
{
#ifdef CONFIG_PM_ENABLE
	// If BT wakeup before esp timer coming due to timer task have no chance to run.
	// Then we will not run into `btdm_sleep_exit_phase0` and acquire PM lock,
	// Do it again here to fix this issue.
	if (s_lp_stat.pm_lock_released) {
		esp_pm_lock_acquire(s_pm_lock);
		s_lp_stat.pm_lock_released = 0;
	}
#endif

	if (btdm_controller_get_sleep_mode() == ESP_BT_SLEEP_MODE_1) {
		if (s_lp_stat.phy_enabled == 0) {
			esp_phy_enable();
			s_lp_stat.phy_enabled = 1;
		}
	}

	// If BT wakeup before esp timer coming due to timer task have no chance to run.
	// Then we will not run into `btdm_sleep_exit_phase0` and stop esp timer,
	// Do it again here to fix this issue.
	if (s_lp_cntl.wakeup_timer_required && s_lp_stat.wakeup_timer_started) {
		esp_timer_stop(s_btdm_slp_tmr);
		s_lp_stat.wakeup_timer_started = 0;
	}

	// wait for the sleep state to change
	// the procedure duration is at micro-second level or less
	while (btdm_sleep_clock_sync()) {
		;
	}
}

static void btdm_sleep_exit_phase0(void *param)
{
	assert(s_lp_cntl.enable == 1);

#ifdef CONFIG_PM_ENABLE
	if (s_lp_stat.pm_lock_released) {
		esp_pm_lock_acquire(s_pm_lock);
		s_lp_stat.pm_lock_released = 0;
	}
#endif

	int event = (int) param;
	if (event == BTDM_ASYNC_WAKEUP_SRC_VHCI || event == BTDM_ASYNC_WAKEUP_SRC_DISA) {
		btdm_wakeup_request();
	}

	if (s_lp_cntl.wakeup_timer_required && s_lp_stat.wakeup_timer_started) {
		esp_timer_stop(s_btdm_slp_tmr);
		s_lp_stat.wakeup_timer_started = 0;
	}

	if (event == BTDM_ASYNC_WAKEUP_SRC_VHCI || event == BTDM_ASYNC_WAKEUP_SRC_DISA) {
		semphr_give_wrapper(s_wakeup_req_sem);
	}
}

static void btdm_slp_tmr_callback(void *arg)
{
#ifdef CONFIG_PM_ENABLE
	btdm_vnd_offload_post(BTDM_VND_OL_SIG_WAKEUP_TMR, (void *)BTDM_ASYNC_WAKEUP_SRC_TMR);
#endif
}


static bool async_wakeup_request(int event)
{
	if (s_lp_cntl.enable == 0) {
		return false;
	}

	bool do_wakeup_request = false;
	switch (event) {
		case BTDM_ASYNC_WAKEUP_SRC_VHCI:
		case BTDM_ASYNC_WAKEUP_SRC_DISA:
			btdm_in_wakeup_requesting_set(true);
			if (!btdm_power_state_active()) {
				btdm_vnd_offload_post(BTDM_VND_OL_SIG_WAKEUP_TMR, (void *)event);
				do_wakeup_request = true;
				semphr_take_wrapper(s_wakeup_req_sem, OSI_FUNCS_TIME_BLOCKING);
			}
			break;
		default:
			break;
	}

	return do_wakeup_request;
}

static void async_wakeup_request_end(int event)
{
	if (s_lp_cntl.enable == 0) {
		return;
	}

	bool allow_to_sleep;
	switch (event) {
		case BTDM_ASYNC_WAKEUP_SRC_VHCI:
		case BTDM_ASYNC_WAKEUP_SRC_DISA:
			allow_to_sleep = true;
			break;
		default:
			allow_to_sleep = true;
			break;
	}

	if (allow_to_sleep) {
		btdm_in_wakeup_requesting_set(false);
	}

	return;
}

static void coex_schm_status_bit_set_wrapper(uint32_t type, uint32_t status)
{
#if CONFIG_SW_COEXIST_ENABLE
	coex_schm_status_bit_set(type, status);
#endif
}

static void coex_schm_status_bit_clear_wrapper(uint32_t type, uint32_t status)
{
#if CONFIG_SW_COEXIST_ENABLE
	coex_schm_status_bit_clear(type, status);
#endif
}

bool esp_vhci_host_check_send_available(void)
{
	if (btdm_controller_status != ESP_BT_CONTROLLER_STATUS_ENABLED) {
		return false;
	}
	return API_vhci_host_check_send_available();
}

void esp_vhci_host_send_packet(uint8_t *data, uint16_t len)
{
	if (btdm_controller_status != ESP_BT_CONTROLLER_STATUS_ENABLED) {
		return;
	}
	async_wakeup_request(BTDM_ASYNC_WAKEUP_SRC_VHCI);

	API_vhci_host_send_packet(data, len);

	async_wakeup_request_end(BTDM_ASYNC_WAKEUP_SRC_VHCI);
}

int esp_vhci_host_register_callback(const esp_vhci_host_callback_t *callback)
{
	if (btdm_controller_status != ESP_BT_CONTROLLER_STATUS_ENABLED) {
		return EPERM;
	}
	return API_vhci_host_register_callback((const vhci_host_callback_t *)callback) == 0 ? 0 : EPERM;
}

static void btdm_controller_mem_init(void)
{
	extern void btdm_controller_rom_data_init(void );
	btdm_controller_rom_data_init();
}

int esp_bt_controller_mem_release(esp_bt_mode_t mode)
{
	intptr_t mem_start=(intptr_t) NULL, mem_end=(intptr_t) NULL;
	if (btdm_controller_status != ESP_BT_CONTROLLER_STATUS_IDLE) {
		return EPERM;
	}

	if (mode & ESP_BT_MODE_BLE) {
		/* if the addresses of rom btdm .data and .bss are consecutive,
		   they are registered in the system heap as a piece of memory
		*/
		if(ets_rom_layout_p->data_end_btdm == ets_rom_layout_p->bss_start_btdm) {
			mem_start = (intptr_t)ets_rom_layout_p->data_start_btdm;
			mem_end = (intptr_t)ets_rom_layout_p->bss_end_btdm;
			if (mem_start != mem_end) {
				ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
			}
		} else {
			mem_start = (intptr_t)ets_rom_layout_p->bss_start_btdm;
			mem_end = (intptr_t)ets_rom_layout_p->bss_end_btdm;
			if (mem_start != mem_end) {
				ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
			}

			mem_start = (intptr_t)ets_rom_layout_p->data_start_btdm;
			mem_end = (intptr_t)ets_rom_layout_p->data_end_btdm;
			if (mem_start != mem_end) {
				ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
			}
		}
		/* if the addresses of rom interface btdm .data and .bss are consecutive,
		   they are registered in the system heap as a piece of memory
		*/
		if(ets_rom_layout_p->data_end_interface_btdm == ets_rom_layout_p->bss_start_interface_btdm) {
			mem_start = (intptr_t)ets_rom_layout_p->data_start_interface_btdm;
			mem_end = (intptr_t)ets_rom_layout_p->bss_end_interface_btdm;
			if (mem_start != mem_end) {
				ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
			}
		} else {
			mem_start = (intptr_t)ets_rom_layout_p->data_start_interface_btdm;
			mem_end = (intptr_t)ets_rom_layout_p->data_end_interface_btdm;
			if (mem_start != mem_end) {
				ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
			}

			mem_start = (intptr_t)ets_rom_layout_p->bss_start_interface_btdm;
			mem_end = (intptr_t)ets_rom_layout_p->bss_end_interface_btdm;
			if (mem_start != mem_end) {
				ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
			}
		}

	}
	return 0;
}

int esp_bt_mem_release(esp_bt_mode_t mode)
{
	int ret;
	intptr_t mem_start, mem_end;

	ret = esp_bt_controller_mem_release(mode);
	if (ret != 0) {
		return ret;
	}

	if (mode & ESP_BT_MODE_BLE) {
		/* if the addresses of btdm .bss and bt .bss are consecutive,
		   they are registered in the system heap as a piece of memory
		*/
		if(_bt_bss_end == _btdm_bss_start) {
			mem_start = (intptr_t)&_bt_bss_start;
			mem_end = (intptr_t)&_btdm_bss_end;
			if (mem_start != mem_end) {
				ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
			}
		} else {
			mem_start = (intptr_t)&_bt_bss_start;
			mem_end = (intptr_t)&_bt_bss_end;
			if (mem_start != mem_end) {
				ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
			}

			mem_start = (intptr_t)&_btdm_bss_start;
			mem_end = (intptr_t)&_btdm_bss_end;
			if (mem_start != mem_end) {
				ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
			}
		}
		/* if the addresses of btdm .data and bt .data are consecutive,
		   they are registered in the system heap as a piece of memory
		*/
		if(_bt_data_end == _btdm_data_start) {
			mem_start = (intptr_t)&_bt_data_start;
			mem_end = (intptr_t)&_btdm_data_end;
			if (mem_start != mem_end) {
				ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
			}
		} else {
			mem_start = (intptr_t)&_bt_data_start;
			mem_end = (intptr_t)&_bt_data_end;
			if (mem_start != mem_end) {
				ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
			}

			mem_start = (intptr_t)&_btdm_data_start;
			mem_end = (intptr_t)&_btdm_data_end;
			if (mem_start != mem_end) {
				ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
			}
		}

		mem_start = (intptr_t)&_nimble_bss_start;
		mem_end = (intptr_t)&_nimble_bss_end;
		if (mem_start != mem_end) {
			ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
		}
		mem_start = (intptr_t)&_nimble_data_start;
		mem_end = (intptr_t)&_nimble_data_end;
		if (mem_start != mem_end) {
			ESP_ERROR_CHECK(try_heap_caps_add_region(mem_start, mem_end));
		}
	}
	return 0;
}

static int try_heap_caps_add_region(intptr_t start, intptr_t end)
{
	int ret = heap_caps_add_region(start, end);
	/* heap_caps_add_region() returns EINVAL if the memory region is
	 * is too small to fit a heap. This cannot be termed as a fatal error and hence
	 * we replace it by 0
	 */

	if (ret == EINVAL) {
		return 0;
	}
	return ret;
}

#if CONFIG_MAC_BB_PD
static void btdm_mac_bb_power_down_cb(void)
{
	if (s_lp_cntl.mac_bb_pd && s_lp_stat.mac_bb_pd == 0) {
		btdm_ble_power_down_dma_copy(true);
		s_lp_stat.mac_bb_pd = 1;
	}
}

static void btdm_mac_bb_power_up_cb(void)
{
	if (s_lp_cntl.mac_bb_pd && s_lp_stat.mac_bb_pd) {
		btdm_ble_power_down_dma_copy(false);
		s_lp_stat.mac_bb_pd = 0;
	}
}
#endif

int esp_bt_controller_init(esp_bt_controller_config_t *cfg)
{
	int err = EPERM;

	if (btdm_controller_status != ESP_BT_CONTROLLER_STATUS_IDLE) {
		return EPERM;
	}

	if (cfg == NULL) {
		return EINVAL;
	}

	if (cfg->controller_task_prio != ESP_TASK_BT_CONTROLLER_PRIO
		|| cfg->controller_task_stack_size < ESP_TASK_BT_CONTROLLER_STACK) {
		return EINVAL;
	}

	if (cfg->bluetooth_mode != ESP_BT_MODE_BLE) {
		return ENOTSUP;
	}

	if (cfg->bluetooth_mode & ESP_BT_MODE_BLE) {
		if ((cfg->ble_max_act <= 0) || (cfg->ble_max_act > BT_CTRL_BLE_MAX_ACT_LIMIT)) {
			return EINVAL;
		}
	}

	if (cfg->sleep_mode == ESP_BT_SLEEP_MODE_1) {
		if (cfg->sleep_clock == ESP_BT_SLEEP_CLOCK_NONE) {
			return EINVAL;
		}
	}

	// overwrite some parameters
	cfg->magic = ESP_BT_CTRL_CONFIG_MAGIC_VAL;

#if CONFIG_MAC_BB_PD
	esp_mac_bb_pd_mem_init();
#endif
	esp_phy_modem_init();
	esp_bt_power_domain_on();

	btdm_controller_mem_init();

#if CONFIG_MAC_BB_PD
	if (esp_register_mac_bb_pd_callback(btdm_mac_bb_power_down_cb) != 0) {
		err = EINVAL;
		goto error;
	}

	if (esp_register_mac_bb_pu_callback(btdm_mac_bb_power_up_cb) != 0) {
		err = EINVAL;
		goto error;
	}
#endif

	osi_funcs_p = (struct osi_funcs_t *)malloc_internal_wrapper(sizeof(struct osi_funcs_t));
	if (osi_funcs_p == NULL) {
		return ENOMEM;
	}

	memcpy(osi_funcs_p, &osi_funcs_ro, sizeof(struct osi_funcs_t));
	if (btdm_osi_funcs_register(osi_funcs_p) != 0) {
		return EINVAL;
	}

	// init low-power control resources
	do {
		// set default values for global states or resources
		s_lp_stat.val = 0;
		s_lp_cntl.val = 0;
		s_lp_cntl.main_xtal_pu = 0;
		s_wakeup_req_sem = NULL;
		s_btdm_slp_tmr = NULL;

		// configure and initialize resources
		s_lp_cntl.enable = (cfg->sleep_mode == ESP_BT_SLEEP_MODE_1) ? 1 : 0;
		s_lp_cntl.no_light_sleep = 0;

		if (s_lp_cntl.enable) {
#if CONFIG_MAC_BB_PD
			if (!btdm_deep_sleep_mem_init()) {
				err = ENOMEM;
				goto error;
			}
			s_lp_cntl.mac_bb_pd = 1;
#endif
#ifdef CONFIG_PM_ENABLE
			s_lp_cntl.wakeup_timer_required = 1;
#endif
			// async wakeup semaphore for VHCI
			s_wakeup_req_sem = semphr_create_wrapper(1, 0);
			if (s_wakeup_req_sem == NULL) {
				err = ENOMEM;
				goto error;
			}
			btdm_vnd_offload_task_register(BTDM_VND_OL_SIG_WAKEUP_TMR, btdm_sleep_exit_phase0);
		}

		if (s_lp_cntl.wakeup_timer_required) {
			esp_timer_create_args_t create_args = {
				.callback = btdm_slp_tmr_callback,
				.arg = NULL,
				.name = "btSlp",
			};
			if ((err = esp_timer_create(&create_args, &s_btdm_slp_tmr)) != 0) {
				goto error;
			}
		}

		// set default bluetooth sleep clock cycle and its fractional bits
		btdm_lpcycle_us_frac = RTC_CLK_CAL_FRACT;
		btdm_lpcycle_us = 2 << (btdm_lpcycle_us_frac);

		// set default bluetooth sleep clock source
		s_lp_cntl.lpclk_sel = BTDM_LPCLK_SEL_XTAL; // set default value
#if CONFIG_BT_CTRL_LPCLK_SEL_EXT_32K_XTAL
		// check whether or not EXT_CRYS is working
		if (rtc_clk_slow_freq_get() == RTC_SLOW_FREQ_32K_XTAL) {
			s_lp_cntl.lpclk_sel = BTDM_LPCLK_SEL_XTAL32K; // External 32 kHz XTAL
		} else {
#if !CONFIG_BT_CTRL_MAIN_XTAL_PU_DURING_LIGHT_SLEEP
			s_lp_cntl.no_light_sleep = 1;
#endif
		}
#elif CONFIG_BT_CTRL_LPCLK_SEL_MAIN_XTAL
#if !CONFIG_BT_CTRL_MAIN_XTAL_PU_DURING_LIGHT_SLEEP
			s_lp_cntl.no_light_sleep = 1;
#endif
#elif CONFIG_BT_CTRL_LPCLK_SEL_RTC_SLOW
		// check whether or not internal 150 kHz RC oscillator is working
		if (rtc_clk_slow_freq_get() == RTC_SLOW_FREQ_RTC) {
			s_lp_cntl.lpclk_sel = BTDM_LPCLK_SEL_RTC_SLOW; // Internal 150 kHz RC oscillator
		} else {
			assert(0);
		}
#endif

		bool select_src_ret __attribute__((unused));
		bool set_div_ret __attribute__((unused));
		if (s_lp_cntl.lpclk_sel == BTDM_LPCLK_SEL_XTAL) {
#ifdef CONFIG_BT_CTRL_MAIN_XTAL_PU_DURING_LIGHT_SLEEP
			ESP_ERROR_CHECK(esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL, ESP_PD_OPTION_ON));
			s_lp_cntl.main_xtal_pu = 1;
#endif
			select_src_ret = btdm_lpclk_select_src(BTDM_LPCLK_SEL_XTAL);
			set_div_ret = btdm_lpclk_set_div(rtc_clk_xtal_freq_get());
			assert(select_src_ret && set_div_ret);
			btdm_lpcycle_us_frac = RTC_CLK_CAL_FRACT;
			btdm_lpcycle_us = 1 << (btdm_lpcycle_us_frac);
		} else if (s_lp_cntl.lpclk_sel == BTDM_LPCLK_SEL_XTAL32K) {
			select_src_ret = btdm_lpclk_select_src(BTDM_LPCLK_SEL_XTAL32K);
			set_div_ret = btdm_lpclk_set_div(0);
			assert(select_src_ret && set_div_ret);
			btdm_lpcycle_us_frac = RTC_CLK_CAL_FRACT;
			btdm_lpcycle_us = (RTC_CLK_CAL_FRACT > 15) ? (1000000 << (RTC_CLK_CAL_FRACT - 15)) :
				(1000000 >> (15 - RTC_CLK_CAL_FRACT));
			assert(btdm_lpcycle_us != 0);
		} else if (s_lp_cntl.lpclk_sel == BTDM_LPCLK_SEL_RTC_SLOW) {
			select_src_ret = btdm_lpclk_select_src(BTDM_LPCLK_SEL_RTC_SLOW);
			set_div_ret = btdm_lpclk_set_div(0);
			assert(select_src_ret && set_div_ret);
			btdm_lpcycle_us_frac = RTC_CLK_CAL_FRACT;
			btdm_lpcycle_us = esp_clk_slowclk_cal_get();
		} else {
			err = EINVAL;
			goto error;
		}
#if CONFIG_SW_COEXIST_ENABLE
		coex_update_lpclk_interval();
#endif

#ifdef CONFIG_PM_ENABLE
		if (s_lp_cntl.no_light_sleep) {
			if ((err = esp_pm_lock_create(ESP_PM_NO_LIGHT_SLEEP, 0, "btLS", &s_light_sleep_pm_lock)) != 0) {
				err = ENOMEM;
				goto error;
			}
		}
		if ((err = esp_pm_lock_create(ESP_PM_APB_FREQ_MAX, 0, "bt", &s_pm_lock)) != 0) {
			err = ENOMEM;
			goto error;
		} else {
			s_lp_stat.pm_lock_released = 1;
		}
#endif
	} while (0);

#if CONFIG_SW_COEXIST_ENABLE
	coex_init();
#endif

	periph_module_enable(PERIPH_BT_MODULE);
	periph_module_reset(PERIPH_BT_MODULE);

	esp_phy_enable();
	s_lp_stat.phy_enabled = 1;

	if (btdm_controller_init(cfg) != 0) {
		err = ENOMEM;
		goto error;
	}
	coex_pti_v2();

	btdm_controller_status = ESP_BT_CONTROLLER_STATUS_INITED;

	return 0;

error:
	if (s_lp_stat.phy_enabled) {
		esp_phy_disable();
		s_lp_stat.phy_enabled = 0;
	}

	do {
		// deinit low power control resources
#ifdef CONFIG_PM_ENABLE
		if (s_lp_cntl.no_light_sleep) {
			if (s_light_sleep_pm_lock != NULL) {
				esp_pm_lock_delete(s_light_sleep_pm_lock);
				s_light_sleep_pm_lock = NULL;
			}
		}
		if (s_pm_lock != NULL) {
			esp_pm_lock_delete(s_pm_lock);
			s_pm_lock = NULL;
			s_lp_stat.pm_lock_released = 0;
		}

#endif
		if (s_lp_cntl.wakeup_timer_required && s_btdm_slp_tmr != NULL) {
			esp_timer_delete(s_btdm_slp_tmr);
			s_btdm_slp_tmr = NULL;
		}

#if CONFIG_MAC_BB_PD
		if (s_lp_cntl.mac_bb_pd) {
			btdm_deep_sleep_mem_deinit();
			s_lp_cntl.mac_bb_pd = 0;
		}
#endif
		if (s_lp_cntl.enable) {
			btdm_vnd_offload_task_deregister(BTDM_VND_OL_SIG_WAKEUP_TMR);
			if (s_wakeup_req_sem != NULL) {
				semphr_delete_wrapper(s_wakeup_req_sem);
				s_wakeup_req_sem = NULL;
			}
		}

		if (s_lp_cntl.lpclk_sel == BTDM_LPCLK_SEL_XTAL) {
#ifdef CONFIG_BT_CTRL_MAIN_XTAL_PU_DURING_LIGHT_SLEEP
			if (s_lp_cntl.main_xtal_pu) {
				ESP_ERROR_CHECK(esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL, ESP_PD_OPTION_OFF));
				s_lp_cntl.main_xtal_pu = 0;
			}
#endif
			btdm_lpclk_select_src(BTDM_LPCLK_SEL_RTC_SLOW);
			btdm_lpclk_set_div(0);
#if CONFIG_SW_COEXIST_ENABLE
			coex_update_lpclk_interval();
#endif
		}

		btdm_lpcycle_us = 0;
	} while (0);

#if CONFIG_MAC_BB_PD
	esp_unregister_mac_bb_pd_callback(btdm_mac_bb_power_down_cb);

	esp_unregister_mac_bb_pu_callback(btdm_mac_bb_power_up_cb);
#endif

	if (osi_funcs_p != NULL) {
		free(osi_funcs_p);
		osi_funcs_p = NULL;
	}
	return err;
}

int esp_bt_controller_deinit(void)
{
	if (btdm_controller_status != ESP_BT_CONTROLLER_STATUS_INITED) {
		return EPERM;
	}

	btdm_controller_deinit();
	periph_module_disable(PERIPH_BT_MODULE);

	if (s_lp_stat.phy_enabled) {
		esp_phy_disable();
		s_lp_stat.phy_enabled = 0;
	} else {
		assert(0);
	}

	// deinit low power control resources
	do {
#if CONFIG_MAC_BB_PD
		btdm_deep_sleep_mem_deinit();
#endif

#ifdef CONFIG_PM_ENABLE
		if (s_lp_cntl.no_light_sleep) {
			esp_pm_lock_delete(s_light_sleep_pm_lock);
			s_light_sleep_pm_lock = NULL;
		}

		esp_pm_lock_delete(s_pm_lock);
		s_pm_lock = NULL;
		s_lp_stat.pm_lock_released = 0;
#endif
		if (s_lp_cntl.wakeup_timer_required) {
			if (s_lp_stat.wakeup_timer_started) {
				esp_timer_stop(s_btdm_slp_tmr);
			}
			s_lp_stat.wakeup_timer_started = 0;
			esp_timer_delete(s_btdm_slp_tmr);
			s_btdm_slp_tmr = NULL;
		}

		if (s_lp_cntl.enable) {
			btdm_vnd_offload_task_deregister(BTDM_VND_OL_SIG_WAKEUP_TMR);

			semphr_delete_wrapper(s_wakeup_req_sem);
			s_wakeup_req_sem = NULL;
		}

		if (s_lp_cntl.lpclk_sel == BTDM_LPCLK_SEL_XTAL) {
#ifdef CONFIG_BT_CTRL_MAIN_XTAL_PU_DURING_LIGHT_SLEEP
			if (s_lp_cntl.main_xtal_pu) {
				ESP_ERROR_CHECK(esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL, ESP_PD_OPTION_OFF));
				s_lp_cntl.main_xtal_pu = 0;
			}
#endif
			btdm_lpclk_select_src(BTDM_LPCLK_SEL_RTC_SLOW);
			btdm_lpclk_set_div(0);
#if CONFIG_SW_COEXIST_ENABLE
			coex_update_lpclk_interval();
#endif
		}

		btdm_lpcycle_us = 0;
	} while (0);

#if CONFIG_MAC_BB_PD
	esp_unregister_mac_bb_pd_callback(btdm_mac_bb_power_down_cb);
	esp_unregister_mac_bb_pu_callback(btdm_mac_bb_power_up_cb);
#endif

	esp_bt_power_domain_off();
#if CONFIG_MAC_BB_PD
	esp_mac_bb_pd_mem_deinit();
#endif
	esp_phy_modem_deinit();

	free(osi_funcs_p);
	osi_funcs_p = NULL;

	btdm_controller_status = ESP_BT_CONTROLLER_STATUS_IDLE;
	return 0;
}

int esp_bt_controller_enable(esp_bt_mode_t mode)
{
	int ret = 0;

	if (btdm_controller_status != ESP_BT_CONTROLLER_STATUS_INITED) {
		return EPERM;
	}

	//As the history reason, mode should be equal to the mode which set in esp_bt_controller_init()
	if (mode != btdm_controller_get_mode()) {
		return EINVAL;
	}

#if CONFIG_SW_COEXIST_ENABLE
	coex_enable();
#endif

	// enable low power mode
	do {
#ifdef CONFIG_PM_ENABLE
		if (s_lp_cntl.no_light_sleep) {
			esp_pm_lock_acquire(s_light_sleep_pm_lock);
		}
		esp_pm_lock_acquire(s_pm_lock);
		s_lp_stat.pm_lock_released = 0;
#endif

		if (s_lp_cntl.enable) {
			btdm_controller_enable_sleep(true);
		}
	} while (0);

	if (btdm_controller_enable(mode) != 0) {
		ret = EPERM;
		goto error;
	}

	btdm_controller_status = ESP_BT_CONTROLLER_STATUS_ENABLED;

	return ret;

error:
	// disable low power mode
	do {
		btdm_controller_enable_sleep(false);
#ifdef CONFIG_PM_ENABLE
		if (s_lp_cntl.no_light_sleep) {
			esp_pm_lock_release(s_light_sleep_pm_lock);
		}
		if (s_lp_stat.pm_lock_released == 0) {
			esp_pm_lock_release(s_pm_lock);
			s_lp_stat.pm_lock_released = 1;
		}
#endif
	} while (0);

	return ret;
}

int esp_bt_controller_disable(void)
{
	if (btdm_controller_status != ESP_BT_CONTROLLER_STATUS_ENABLED) {
		return EPERM;
	}

	async_wakeup_request(BTDM_ASYNC_WAKEUP_SRC_DISA);
	while (!btdm_power_state_active()){}
	btdm_controller_disable();

	async_wakeup_request_end(BTDM_ASYNC_WAKEUP_SRC_DISA);

#if CONFIG_SW_COEXIST_ENABLE
	coex_disable();
#endif

	btdm_controller_status = ESP_BT_CONTROLLER_STATUS_INITED;

	// disable low power mode
	do {
#ifdef CONFIG_PM_ENABLE
		if (s_lp_cntl.no_light_sleep) {
			esp_pm_lock_release(s_light_sleep_pm_lock);
		}

		if (s_lp_stat.pm_lock_released == 0) {
			esp_pm_lock_release(s_pm_lock);
			s_lp_stat.pm_lock_released = 1;
		} else {
			assert(0);
		}
#endif
	} while (0);

	return 0;
}

esp_bt_controller_status_t esp_bt_controller_get_status(void)
{
	return btdm_controller_status;
}

/* extra functions */
int esp_ble_tx_power_set(esp_ble_power_type_t power_type, esp_power_level_t power_level)
{
	int stat = EPERM;

	switch (power_type) {
	case ESP_BLE_PWR_TYPE_ADV:
	case ESP_BLE_PWR_TYPE_SCAN:
	case ESP_BLE_PWR_TYPE_DEFAULT:
		if (ble_txpwr_set(power_type, power_level) == 0) {
			stat = 0;
		}
		break;
	default:
		stat = ENOTSUP;
		break;
	}

	return stat;

}

esp_power_level_t esp_ble_tx_power_get(esp_ble_power_type_t power_type)
{
	esp_power_level_t lvl;

	switch (power_type) {
	case ESP_BLE_PWR_TYPE_ADV:
	case ESP_BLE_PWR_TYPE_SCAN:
		lvl = (esp_power_level_t)ble_txpwr_get(power_type);
		break;
	case ESP_BLE_PWR_TYPE_CONN_HDL0:
	case ESP_BLE_PWR_TYPE_CONN_HDL1:
	case ESP_BLE_PWR_TYPE_CONN_HDL2:
	case ESP_BLE_PWR_TYPE_CONN_HDL3:
	case ESP_BLE_PWR_TYPE_CONN_HDL4:
	case ESP_BLE_PWR_TYPE_CONN_HDL5:
	case ESP_BLE_PWR_TYPE_CONN_HDL6:
	case ESP_BLE_PWR_TYPE_CONN_HDL7:
	case ESP_BLE_PWR_TYPE_CONN_HDL8:
	case ESP_BLE_PWR_TYPE_DEFAULT:
		lvl = (esp_power_level_t)ble_txpwr_get(ESP_BLE_PWR_TYPE_DEFAULT);
		break;
	default:
		lvl = ESP_PWR_LVL_INVALID;
		break;
	}

	return lvl;

}

int esp_bt_sleep_enable (void)
{
	int status;
	if (btdm_controller_status != ESP_BT_CONTROLLER_STATUS_ENABLED) {
		return EPERM;
	}
	if (btdm_controller_get_sleep_mode() == ESP_BT_SLEEP_MODE_1) {
		btdm_controller_enable_sleep (true);
		status = 0;
	} else {
		status = ENOTSUP;
	}

	return status;
}

int esp_bt_sleep_disable (void)
{
	int status;
	if (btdm_controller_status != ESP_BT_CONTROLLER_STATUS_ENABLED) {
		return EPERM;
	}
	if (btdm_controller_get_sleep_mode() == ESP_BT_SLEEP_MODE_1) {
		btdm_controller_enable_sleep (false);
		status = 0;
	} else {
		status = ENOTSUP;
	}

	return status;
}

bool esp_bt_controller_is_sleeping(void)
{
	if (btdm_controller_status != ESP_BT_CONTROLLER_STATUS_ENABLED ||
		btdm_controller_get_sleep_mode() != ESP_BT_SLEEP_MODE_1) {
		return false;
	}

	return !btdm_power_state_active();
}

void esp_bt_controller_wakeup_request(void)
{
	if (btdm_controller_status != ESP_BT_CONTROLLER_STATUS_ENABLED ||
		btdm_controller_get_sleep_mode() != ESP_BT_SLEEP_MODE_1) {
		return;
	}

	btdm_wakeup_request();

}

int esp_bt_h4tl_eif_io_event_notify(int event)
{
	return btdm_hci_tl_io_event_post(event);
}

uint16_t esp_bt_get_tx_buf_num(void)
{
	return l2c_ble_link_get_tx_buf_num();
}

static void coex_wifi_sleep_set_hook(bool sleep)
{

}
