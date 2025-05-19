#include <stdint.h>

#define MIN_ICACHE_SIZE                 16384
#define MAX_ICACHE_SIZE                 32768
#define MIN_DCACHE_SIZE                 32768
#define MAX_DCACHE_SIZE                 65536
#define MIN_ICACHE_WAYS                 4
#define MAX_ICACHE_WAYS                 8
#define MIN_DCACHE_WAYS                 4
#define MAX_DCACHE_WAYS                 4
#define MAX_CACHE_WAYS                  8
#define MIN_CACHE_LINE_SIZE             16
#define TAG_SIZE                        4
#define MIN_ICACHE_BANK_NUM             1
#define MAX_ICACHE_BANK_NUM             2
#define MIN_DCACHE_BANK_NUM             1
#define MAX_DCACHE_BANK_NUM             2
#define CACHE_MEMORY_BANK_NUM           4
#define CACHE_MEMORY_IBANK_SIZE         0x4000
#define CACHE_MEMORY_DBANK_SIZE         0x8000

#define MAX_ITAG_BANK_ITEMS             (MAX_ICACHE_SIZE / MAX_ICACHE_BANK_NUM / MIN_CACHE_LINE_SIZE)
#define MAX_ITAG_BLOCK_ITEMS            (MAX_ICACHE_SIZE / MAX_ICACHE_BANK_NUM / MAX_ICACHE_WAYS / MIN_CACHE_LINE_SIZE)
#define MAX_ITAG_BANK_SIZE              (MAX_ITAG_BANK_ITEMS * TAG_SIZE)
#define MAX_ITAG_BLOCK_SIZE             (MAX_ITAG_BLOCK_ITEMS * TAG_SIZE)
#define MAX_DTAG_BANK_ITEMS             (MAX_DCACHE_SIZE / MAX_DCACHE_BANK_NUM /  MIN_CACHE_LINE_SIZE)
#define MAX_DTAG_BLOCK_ITEMS            (MAX_DCACHE_SIZE / MAX_DCACHE_BANK_NUM / MAX_DCACHE_WAYS / MIN_CACHE_LINE_SIZE)
#define MAX_DTAG_BANK_SIZE              (MAX_DTAG_BANK_ITEMS * TAG_SIZE)
#define MAX_DTAG_BLOCK_SIZE             (MAX_DTAG_BLOCK_ITEMS * TAG_SIZE)

typedef enum {
    CACHE_DCACHE = 0,
    CACHE_ICACHE0 = 1,
    CACHE_ICACHE1 = 2,
} cache_t;

typedef enum {
    CACHE_MEMORY_INVALID = 0,
    CACHE_MEMORY_IBANK0 = 1<<0,
    CACHE_MEMORY_IBANK1 = 1<<1,
    CACHE_MEMORY_IBANK2 = 1<<2,
    CACHE_MEMORY_IBANK3 = 1<<3,
    CACHE_MEMORY_DBANK0 = 1<<0,
    CACHE_MEMORY_DBANK1 = 1<<1,
    CACHE_MEMORY_DBANK2 = 1<<2,
    CACHE_MEMORY_DBANK3 = 1<<3,
} cache_array_t;

#define ICACHE_SIZE_16KB  CACHE_SIZE_HALF
#define ICACHE_SIZE_32KB  CACHE_SIZE_FULL
#define DCACHE_SIZE_32KB  CACHE_SIZE_HALF
#define DCACHE_SIZE_64KB  CACHE_SIZE_FULL

typedef enum {
    CACHE_SIZE_HALF = 0,                /*!< 8KB for icache and dcache */
    CACHE_SIZE_FULL = 1,                /*!< 16KB for icache and dcache */
} cache_size_t;

typedef enum {
    CACHE_4WAYS_ASSOC = 0,              /*!< 4 way associated cache */
    CACHE_8WAYS_ASSOC = 1,              /*!< 8 way associated cache */
} cache_ways_t;

typedef enum {
    CACHE_LINE_SIZE_16B = 0,            /*!< 16 Byte cache line size */
    CACHE_LINE_SIZE_32B = 1,            /*!< 32 Byte cache line size */
    CACHE_LINE_SIZE_64B = 2,            /*!< 64 Byte cache line size */
} cache_line_size_t;

typedef enum {
    CACHE_AUTOLOAD_POSITIVE = 0,        /*!< cache autoload step is positive */
    CACHE_AUTOLOAD_NEGATIVE = 1,        /*!< cache autoload step is negative */
} cache_autoload_order_t;

typedef enum {
    CACHE_AUTOLOAD_REGION0 = 0,         /*!< cache autoload region0 */
    CACHE_AUTOLOAD_REGION1 = 1,         /*!< cache autoload region1 */
} cache_autoload_region_t;

#define CACHE_AUTOLOAD_STEP(i) ((i) - 1)

typedef enum {
    CACHE_AUTOLOAD_MISS_TRIGGER = 0,    /*!< autoload only triggered by cache miss */
    CACHE_AUTOLOAD_HIT_TRIGGER  = 1,    /*!< autoload only triggered by cache hit */
    CACHE_AUTOLOAD_BOTH_TRIGGER = 2,    /*!< autoload triggered both by cache miss and hit */
} cache_autoload_trigger_t;

typedef enum {
    CACHE_FREEZE_ACK_BUSY = 0,          /*!< in this mode, cache ack busy to CPU if a cache miss happens*/
    CACHE_FREEZE_ACK_ERROR  = 1,        /*!< in this mode, cache ack wrong data to CPU and trigger an error if a cache miss happens */
} cache_freeze_mode_t;

struct cache_mode {
    uint32_t cache_size;                /*!< cache size in byte */
    uint16_t cache_line_size;           /*!< cache line size in byte */
    uint8_t cache_ways;                 /*!< cache ways, always 4 */
    uint8_t icache;                     /*!< the cache index, 0 for dcache, 1 for icache */
};

struct icache_tag_item {
    uint32_t valid: 1;                  /*!< the tag item is valid or not */
    uint32_t lock: 1;                   /*!< the cache line is locked or not */
    uint32_t attr: 4;                   /*!< the attribute of the external memory physical address */
    uint32_t fifo_cnt: 3;               /*!< fifo cnt, 0 ~ 3 for 4 ways cache */
    uint32_t tag: 14;                   /*!< the tag is the high part of the cache address, however is only 64MB range, and without low part */
    uint32_t reserved: 9;
};

struct dcache_tag_item {
    uint32_t dirty: 1;                  /*!< the cache line value is dirty or not */
    uint32_t valid: 1;                  /*!< the tag item is valid or not */
    uint32_t lock: 1;                   /*!< the cache line is locked or not */
    uint32_t occupy: 1;                 /*!< the cache line is occupied as internal sram */
    uint32_t attr: 4;                   /*!< the attribute of the external memory physical address */
    uint32_t fifo_cnt: 2;               /*!< fifo cnt, 0 ~ 3 for 4 ways cache */
    uint32_t tag: 13;                   /*!< the tag is the high part of the cache address, however is only 64MB range, and without low part */
    uint32_t reserved: 9;
};

struct autoload_config {
    uint8_t ena;                        /*!< autoload enable */
    uint8_t order;                      /*!< autoload step is positive or negative */
    uint8_t trigger;                    /*!< autoload trigger */
    uint8_t size;                       /*!< autoload size */
};

struct autoload_region_config {
    uint8_t region;                     /*!< autoload region*/
    uint8_t ena;                        /*!< autoload region enable */
    uint32_t addr;                      /*!< autoload region start address */
    uint32_t size;                      /*!< autoload region size */
};

struct tag_group_info {
    struct cache_mode mode;                         /*!< cache and cache mode */
    uint32_t filter_addr;                           /*!< the address that used to generate the struct */
    uint32_t vaddr_offset;                          /*!< virtual address offset of the cache ways */
    uint32_t tag_addr[MAX_CACHE_WAYS];              /*!< tag memory address, only [0~mode.ways-1] is valid to use */
    uint32_t cache_memory_offset[MAX_CACHE_WAYS];   /*!< cache memory address, only [0~mode.ways-1] is valid to use */
    uint8_t use_legacy;                             /*!< 1 for using legacy tag api, 0 for using 2rd tag api */
};

struct lock_config {
    uint32_t addr;                                  /*!< manual lock address*/
    uint16_t size;                                  /*!< manual lock size*/
    uint16_t group;                                 /*!< manual lock group, 0 or 1*/
};

struct cache_internal_stub_table {
    uint32_t (* icache_line_size)(void);
    uint32_t (* dcache_line_size)(void);
    uint32_t (* icache_addr)(uint32_t addr);
    uint32_t (* dcache_addr)(uint32_t addr);
    void (* invalidate_icache_items)(uint32_t addr, uint32_t items);
    void (* invalidate_dcache_items)(uint32_t addr, uint32_t items);
    void (* clean_items)(uint32_t addr, uint32_t items);
    void (* writeback_items)(uint32_t addr, uint32_t items);
    void (* lock_icache_items)(uint32_t addr, uint32_t items);
    void (* lock_dcache_items)(uint32_t addr, uint32_t items);
    void (* unlock_icache_items)(uint32_t addr, uint32_t items);
    void (* unlock_dcache_items)(uint32_t addr, uint32_t items);
    void (* occupy_items)(uint32_t addr, uint32_t items);
    uint32_t (* suspend_icache_autoload)(void);
    void (* resume_icache_autoload)(uint32_t autoload);
    uint32_t (* suspend_dcache_autoload)(void);
    void (* resume_dcache_autoload)(uint32_t autoload);
    void (* freeze_icache_enable)(cache_freeze_mode_t mode);
    void (* freeze_icache_disable)(void);
    void (* freeze_dcache_enable)(cache_freeze_mode_t mode);
    void (* freeze_dcache_disable)(void);
    int (* op_addr)(uint32_t op_icache, uint32_t start_addr, uint32_t size, uint32_t cache_line_size, uint32_t max_sync_num, void(* cache_Iop)(uint32_t, uint32_t), void(* cache_Dop)(uint32_t, uint32_t));
};

typedef void (* cache_op_start)(void);
typedef void (* cache_op_end)(void);

typedef struct {
    cache_op_start start;
    cache_op_end end;
} cache_op_cb_t;

#define ESP_ROM_ERR_INVALID_ARG         1
#define MMU_SET_ADDR_ALIGNED_ERROR      2
#define MMU_SET_PASE_SIZE_ERROR         3
#define MMU_SET_VADDR_OUT_RANGE         4

#define CACHE_OP_ICACHE_Y               1
#define CACHE_OP_ICACHE_N               0

void Cache_MMU_Init(void);
int Cache_Ibus_MMU_Set(uint32_t ext_ram, uint32_t vaddr, uint32_t paddr,  uint32_t psize, uint32_t num, uint32_t fixed);
int Cache_Dbus_MMU_Set(uint32_t ext_ram, uint32_t vaddr, uint32_t paddr, uint32_t psize, uint32_t num, uint32_t fixed);
uint32_t Cache_Count_Flash_Pages(uint32_t bus, uint32_t *page0_mapped);
uint32_t Cache_Flash_To_SPIRAM_Copy(uint32_t bus, uint32_t bus_start_addr, uint32_t start_page, uint32_t *page0_page);
void Cache_Occupy_ICache_MEMORY(cache_array_t icache_low, cache_array_t icache_high);
void Cache_Occupy_DCache_MEMORY(cache_array_t dcache_low, cache_array_t dcache_high);
void Cache_Get_Mode(struct cache_mode *mode);
void Cache_Set_ICache_Mode(cache_size_t cache_size, cache_ways_t ways, cache_line_size_t cache_line_size);
void Cache_Set_DCache_Mode(cache_size_t cache_size, cache_ways_t ways, cache_line_size_t cache_line_size);
uint32_t Cache_Address_Through_ICache(uint32_t addr);
uint32_t Cache_Address_Through_DCache(uint32_t addr);
void Cache_Owner_Init(void);
void Cache_Invalidate_ICache_Items(uint32_t addr, uint32_t items);
void Cache_Invalidate_DCache_Items(uint32_t addr, uint32_t items);
void Cache_Clean_Items(uint32_t addr, uint32_t items);
void Cache_WriteBack_Items(uint32_t addr, uint32_t items);
int Cache_Invalidate_Addr(uint32_t addr, uint32_t size);
int Cache_Clean_Addr(uint32_t addr, uint32_t size);
int Cache_WriteBack_Addr(uint32_t addr, uint32_t size);
void Cache_Invalidate_ICache_All(void);
void Cache_Invalidate_DCache_All(void);
void Cache_Clean_All(void);
void Cache_WriteBack_All(void);
void Cache_Mask_All(void);
void Cache_UnMask_Dram0(void);
uint32_t Cache_Suspend_ICache_Autoload(void);
void Cache_Resume_ICache_Autoload(uint32_t autoload);
uint32_t Cache_Suspend_DCache_Autoload(void);
void Cache_Resume_DCache_Autoload(uint32_t autoload);
uint32_t Cache_Start_ICache_Preload(uint32_t addr, uint32_t size, uint32_t order);
uint32_t Cache_ICache_Preload_Done(void);
void Cache_End_ICache_Preload(uint32_t autoload);
uint32_t Cache_Start_DCache_Preload(uint32_t addr, uint32_t size, uint32_t order);
uint32_t Cache_DCache_Preload_Done(void);
void Cache_End_DCache_Preload(uint32_t autoload);
void Cache_Config_ICache_Autoload(const struct autoload_config *config);
int Cache_Config_ICache_Region_Autoload(const struct autoload_region_config *config);
void Cache_Enable_ICache_Autoload(void);
void Cache_Disable_ICache_Autoload(void);
void Cache_Config_DCache_Autoload(const struct autoload_config *config);
int Cache_Config_DCache_Region_Autoload(const struct autoload_region_config *config);
void Cache_Enable_DCache_Autoload(void);
void Cache_Disable_DCache_Autoload(void);
void Cache_Enable_ICache_PreLock(const struct lock_config *config);
void Cache_Disable_ICache_PreLock(uint16_t group);
void Cache_Lock_ICache_Items(uint32_t addr, uint32_t items);
void Cache_Unlock_ICache_Items(uint32_t addr, uint32_t items);
void Cache_Enable_DCache_PreLock(const struct lock_config *config);
void Cache_Disable_DCache_PreLock(uint16_t group);
void Cache_Lock_DCache_Items(uint32_t addr, uint32_t items);
void Cache_Unlock_DCache_Items(uint32_t addr, uint32_t items);
int Cache_Lock_Addr(uint32_t addr, uint32_t size);
int Cache_Unlock_Addr(uint32_t addr, uint32_t size);
uint32_t Cache_Disable_ICache(void);
void Cache_Enable_ICache(uint32_t autoload);
uint32_t Cache_Disable_DCache(void);
void Cache_Enable_DCache(uint32_t autoload);
uint32_t Cache_Suspend_ICache(void);
void Cache_Resume_ICache(uint32_t autoload);
uint32_t Cache_Suspend_DCache(void);
void Cache_Resume_DCache(uint32_t autoload);
uint32_t Cache_Get_ICache_Line_Size(void);
uint32_t Cache_Get_DCache_Line_Size(void);
void Cache_Set_Default_Mode(void);
void Cache_Enable_Defalut_ICache_Mode(void);
void Cache_Occupy_Items(uint32_t addr, uint32_t items);
int Cache_Occupy_Addr(uint32_t addr, uint32_t size);
void Cache_Freeze_ICache_Enable(cache_freeze_mode_t mode);
void Cache_Freeze_ICache_Disable(void);
void Cache_Freeze_DCache_Enable(cache_freeze_mode_t mode);
void Cache_Freeze_DCache_Disable(void);
void Cache_Travel_Tag_Memory(struct cache_mode * mode, uint32_t filter_addr, void (* process)(struct tag_group_info *));
void Cache_Travel_Tag_Memory2(struct cache_mode * mode, uint32_t filter_addr, void (* process)(struct tag_group_info *));
uint32_t Cache_Get_Virtual_Addr(struct cache_mode *mode, uint32_t tag, uint32_t vaddr_offset);
uint32_t Cache_Get_Memory_BaseAddr(uint32_t icache, uint32_t bank_no);
uint32_t Cache_Get_Memory_Addr(struct cache_mode *mode, uint32_t cache_memory_offset, uint32_t vaddr_offset);

uint32_t Cache_Get_Memory_value(uint32_t cache_memory_addr);

uint32_t Cache_Get_IROM_MMU_End(void);

uint32_t Cache_Get_DROM_MMU_End(void);

int flash2spiram_instruction_offset(void);
int flash2spiram_rodata_offset(void);
uint32_t flash_instr_rodata_start_page(uint32_t bus);
uint32_t flash_instr_rodata_end_page(uint32_t bus);

extern struct cache_internal_stub_table* rom_cache_internal_table_ptr;
extern cache_op_cb_t rom_cache_op_cb;
