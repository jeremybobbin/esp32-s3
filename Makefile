CC=xtensa-esp32s3-elf-gcc
AR=xtensa-esp32s3-elf-ar
CFLAGS=-I./$(@D) -I.
ASFLAGS=-I./$(@D)

build: libsoc.a libxtensa.a

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
	xtensa/windowspill_asm.o
	$(AR) rcs $@ $?

clean:
	rm -f soc/*.o xtensa/*.o libxtensa.a
