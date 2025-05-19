CC=xtensa-esp32s3-elf-gcc
AR=xtensa-esp32s3-elf-ar
CFLAGS=-I./$(@D)
ASFLAGS=-I./$(@D)

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
	rm -f xtensa/*.o libxtensa.a
