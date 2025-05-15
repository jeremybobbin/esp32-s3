CC=xtensa-esp32s3-elf-gcc
AR=xtensa-esp32s3-elf-ar
CFLAGS=-I./include/
ASFLAGS=-I./include/

libxt_hal.a: attribute.o \
	cache_asm.o \
	cache.o \
	clock.o \
	coherence.o \
	debug.o \
	debug_hndlr.o \
	disass.o \
	int_asm.o \
	interrupts.o \
	memcopy.o \
	mem_ecc_parity.o \
	misc.o \
	miscellaneous.o \
	mmu.o \
	mp_asm.o \
	set_region_translate.o \
	state.o \
	state_asm.o \
	syscache_asm.o \
	windowspill_asm.o
	$(AR) rcs $@ $?

clean:
	rm -f *.o
