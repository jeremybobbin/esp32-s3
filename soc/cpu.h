#include <stdint.h>
#include <stdbool.h>
#include "heap/soc_memory_layout.h"

extern bool g_spiram_ok;

uint32_t cpu_ll_get_core_id(void);
uint32_t cpu_ll_get_cycle_count(void);
void cpu_ll_set_cycle_count(uint32_t val);
void *cpu_ll_get_sp(void);
void cpu_ll_init_hwloop(void);
void cpu_ll_set_breakpoint(int id, uint32_t pc);
void cpu_ll_clear_breakpoint(int id);
uint32_t cpu_ll_ptr_to_pc(const void *addr);
void *cpu_ll_pc_to_ptr(uint32_t pc);
void cpu_ll_set_watchpoint(int id, const void *addr, size_t size, bool on_read, bool on_write);
void cpu_ll_clear_watchpoint(int id);
bool cpu_ll_is_debugger_attached(void);
void cpu_ll_break(void);
void cpu_ll_set_vecbase(const void *vecbase);
void cpu_ll_waiti(void);
uint32_t cpu_ll_read_dedic_gpio_in(void);
uint32_t cpu_ll_read_dedic_gpio_out(void);
void cpu_ll_write_dedic_gpio_all(uint32_t value);
void cpu_ll_write_dedic_gpio_mask(uint32_t mask, uint32_t value);
