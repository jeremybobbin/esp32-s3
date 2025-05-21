CC=xtensa-esp32s3-elf-gcc
AR=xtensa-esp32s3-elf-ar
CFLAGS=-I./$(@D) -I.
ASFLAGS=-I./$(@D) -I.

build: libsoc.a libxtensa.a libbluetooth.a

soc/adc.o: soc/adc.h
soc/gpio.o: soc/gpio.h soc/usb_serial_jtag.h soc/rtc_cntl.h

libsoc.a: \
	soc/adc.o \
	soc/gpio.o
	$(AR) rcs $@ $?

libxtensa.a: \
	xtensa/attribute.o \
	xtensa/cache_asm.o \
	xtensa/cache.o \
	xtensa/clock.o \
	xtensa/coherence.o \
	xtensa/debug.o \
	xtensa/debug_hndlr.o \
	xtensa/disass.o \
	xtensa/int_asm.o \
	xtensa/interrupts.o \
	xtensa/memcopy.o \
	xtensa/mem_ecc_parity.o \
	xtensa/misc.o \
	xtensa/miscellaneous.o \
	xtensa/mmu.o \
	xtensa/mp_asm.o \
	xtensa/set_region_translate.o \
	xtensa/state.o \
	xtensa/state_asm.o \
	xtensa/syscache_asm.o \
	xtensa/windowspill_asm.o \
	xtensa/xtensa_intr.o
	$(AR) rcs $@ $?

libbluetooth.a: \
	bluetooth/arch_main.o \
	bluetooth/bluetooth.o \
	bluetooth/ble_util_buf.o \
	bluetooth/bluetooth.c \
	bluetooth/btdm_log.o \
	bluetooth/bt_rw_v9.o \
	bluetooth/config_funcs.o \
	bluetooth/dbg_trc_mem.o \
	bluetooth/dbg_trc.o \
	bluetooth/dbg_trc_tl.o \
	bluetooth/emi.o \
	bluetooth/flash.o \
	bluetooth/hci_msg.o \
	bluetooth/hci.o \
	bluetooth/hci_tl.o \
	bluetooth/hl_itf.o \
	bluetooth/intc.o \
	bluetooth/ip_funcs.o \
	bluetooth/ke_task.o \
	bluetooth/llc_con_upd.o \
	bluetooth/llc_dl_upd.o \
	bluetooth/llc_encrypt.o \
	bluetooth/llc_hci.o \
	bluetooth/llc_llcp.o \
	bluetooth/llc.o \
	bluetooth/lld_adv.o \
	bluetooth/lld_con.o \
	bluetooth/lld.o \
	bluetooth/lld_per_adv.o \
	bluetooth/lld_scan.o \
	bluetooth/lld_sync.o \
	bluetooth/llm_adv.o \
	bluetooth/llm_hci.o \
	bluetooth/llm_init.o \
	bluetooth/llm.o \
	bluetooth/llm_scan.o \
	bluetooth/llm_task.o \
	bluetooth/modules_funcs.o \
	bluetooth/nvds.o \
	bluetooth/osi.o \
	bluetooth/plf_funcs.o \
	bluetooth/rf_coexist_hook.o \
	bluetooth/rf_coexist.o \
	bluetooth/rf_espressif.o \
	bluetooth/rf_txpwr.o \
	bluetooth/rwble.o \
	bluetooth/rwip_driver.o \
	bluetooth/rwip.o \
	bluetooth/sch_arb.o \
	bluetooth/sch_plan.o \
	bluetooth/sch_prog.o \
	bluetooth/sdk_config.o \
	bluetooth/task.o \
	bluetooth/vhci.o \
	bluetooth/vshci_task.o
	$(AR) rcs $@ $?

clean:
	rm -f soc/*.o xtensa/*.o libxtensa.a
