.SUFFIXES: .c .o .a .S
CC=xtensa-esp32s3-elf-gcc -fdiagnostics-color=always
AR=xtensa-esp32s3-elf-ar
CFLAGS=-I.
ASFLAGS=-I.

.o.a:
	$(AR) rcs $@ $?

build: \
	libbluetooth.a \
	libsoc.a \
	librtos.a \
	libxtensa.a

#libwifi.a \

soc/adc.o: soc/adc.h
soc/gpio.o: soc/gpio.h soc/usb_serial_jtag.h soc/rtc_cntl.h

libsoc.a: \
	soc/adc.o \
	soc/aes.o \
	soc/brownout.o \
	soc/clk_gate.o \
	soc/cpu.o \
	soc/cross-int.o \
	soc/ds.o \
	soc/efuse.o \
	soc/gdma.o \
	soc/gpio.o \
	soc/gpspi_flash.o \
	soc/hmac.o \
	soc/i2c.o \
	soc/i2s.o \
	soc/interrupt_controller.o \
	soc/interrupt_descriptor_table.o \
	soc/lcd.o \
	soc/ledc.o \
	soc/lldesc.o \
	soc/mcpwm.o \
	soc/mpu.o \
	soc/mwdt.o \
	soc/pcnt.o \
	soc/peripherals.o \
	soc/phy.o \
	soc/random.o \
	soc/rmt.o \
	soc/rtc_cntl.o \
	soc/rtc_io.o \
	soc/rtc.o \
	soc/rwdt.o \
	soc/sens.o \
	soc/sha.o \
	soc/sigmadelta.o \
	soc/soc.o \
	soc/spi_flash_encrypted.o \
	soc/spi_flash.o \
	soc/spimem_flash.o \
	soc/spi.o \
	soc/spiram.o \
	soc/systimer.o \
	soc/timer.o \
	soc/touch_sensor.o \
	soc/trace.o \
	soc/twai.o \
	soc/uart.o \
	soc/uhci.o \
	soc/usb.o \
	soc/usb_phy.o \
	soc/usb_serial_jtag.o \
	soc/xt_wdt.o
	$(AR) rcs $@ $?

libheap.a: \
	heap/heap_caps_init.o \
	heap/heap_caps.o \
	heap/heap_tlsf.o \
	heap/memory_layout.o \
	heap/memory_layout_utils.o \
	heap/multi_heap.o
	$(AR) rcs $@ $?

librtos.a: \
	freertos/croutine.o \
	freertos/event_groups.o \
	freertos/FreeRTOS-openocd.o \
	freertos/list.o \
	freertos/port.o \
	freertos/port_common.o \
	freertos/port_systick.o \
	freertos/queue.o \
	freertos/stream_buffer.o \
	freertos/tasks.o \
	freertos/task_snapshot.o \
	freertos/timers.o \
	freertos/xtensa_init.o \
	freertos/xtensa_overlay_os_hook.o
	$(AR) rcs $@ $?

libwifi.a: \
	wifi/coexist_api.o \
	wifi/coexist_arbit.o \
	wifi/coexist_core.o \
	wifi/coexist_dbg.o \
	wifi/coexist_hw.o \
	wifi/coexist_param.o \
	wifi/coexist_scheme.o \
	wifi/coexist_timer.o \
	wifi/esf_buf.o \
	wifi/esp_adapter.o \
	wifi/espnow.o \
	wifi/hal_ampdu.o \
	wifi/hal_coex.o \
	wifi/hal_crypto.o \
	wifi/hal_mac.o \
	wifi/hal_mac_rx.o \
	wifi/hal_mac_tx.o \
	wifi/hal_sniffer.o \
	wifi/hal_tsf.o \
	wifi/ieee80211_action.o \
	wifi/ieee80211_action_vendor.o \
	wifi/ieee80211_api.o \
	wifi/ieee80211_crypto_ccmp.o \
	wifi/ieee80211_crypto_gcmp.o \
	wifi/ieee80211_crypto.o \
	wifi/ieee80211_crypto_sms4.o \
	wifi/ieee80211_crypto_tkip.o \
	wifi/ieee80211_crypto_wep.o \
	wifi/ieee80211_debug.o \
	wifi/ieee80211_ets.o \
	wifi/ieee80211_ftm.o \
	wifi/ieee80211_hostap.o \
	wifi/ieee80211_ht.o \
	wifi/ieee80211_hwmp.o \
	wifi/ieee80211_ie_vendor.o \
	wifi/ieee80211_input.o \
	wifi/ieee80211_ioctl.o \
	wifi/ieee80211_mesh.o \
	wifi/ieee80211_mesh_quick.o \
	wifi/ieee80211_node.o \
	wifi/ieee80211_nvs.o \
	wifi/ieee80211.o \
	wifi/ieee80211_output.o \
	wifi/ieee80211_phy.o \
	wifi/ieee80211_power.o \
	wifi/ieee80211_proto.o \
	wifi/ieee80211_reg_db.o \
	wifi/ieee80211_regdomain.o \
	wifi/ieee80211_rfid.o \
	wifi/ieee80211_scan.o \
	wifi/ieee80211_sta.o \
	wifi/ieee80211_supplicant.o \
	wifi/ieee80211_timer.o \
	wifi/if_eagle.o \
	wifi/if_hwctrl.o \
	wifi/lmac.o \
	wifi/manatick.o \
	wifi/mesh_common.o \
	wifi/mesh_config.o \
	wifi/mesh_input.o \
	wifi/mesh_io.o \
	wifi/mesh_main.o \
	wifi/mesh_network.o \
	wifi/mesh.o \
	wifi/mesh_parent.o \
	wifi/mesh_quick.o \
	wifi/mesh_route.o \
	wifi/mesh_schedule.o \
	wifi/mesh_sleep.o \
	wifi/mesh_timer.o \
	wifi/mesh_utilities.o \
	wifi/mesh_wifi.o \
	wifi/misc_nvs.o \
	wifi/pm_for_bcn_only_mode.o \
	wifi/pm.o \
	wifi/pp_debug.o \
	wifi/pp.o \
	wifi/pp_timer.o \
	wifi/rate_control.o \
	wifi/sc_airkiss.o \
	wifi/sc_broadcast.o \
	wifi/sc_crypt.o \
	wifi/sc_esptouch.o \
	wifi/sc_esptouch_v2.o \
	wifi/sc_ht40.o \
	wifi/sc_ieee80211.o \
	wifi/sc_sniffer.o \
	wifi/trc.o \
	wifi/wapi_glue.o \
	wifi/wapi.o \
	wifi/wapi_sms4_algo.o \
	wifi/wdev.o \
	wifi/wl_chm.o \
	wifi/wl_cnx.o \
	wifi/wl_offchan.o
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
	rm -f *.a wifi/esp_adapter.o bluetooth/bluetooth.o heap/*.o soc/*.o xtensa/*.o freertos/*.o libxtensa.a
