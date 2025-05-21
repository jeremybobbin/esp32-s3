#include <xtensa/config/core.h>

#define RSR(reg, at)         asm volatile ("rsr %0, %1" : "=r" (at) : "i" (reg))
#define WSR(reg, at)         asm volatile ("wsr %0, %1" : : "r" (at), "i" (reg))
#define XSR(reg, at)         asm volatile ("xsr %0, %1" : "+r" (at) : "i" (reg))

#define RER(reg, at)         asm volatile ("rer %0, %1" : "=r" (at) : "r" (reg))

#define WITLB(at, as)        asm volatile ("witlb  %0, %1; \n isync \n " : : "r" (at), "r" (as))
#define WDTLB(at, as)        asm volatile ("wdtlb  %0, %1; \n dsync \n " : : "r" (at), "r" (as))

#define EXTRA_SAVE_AREA_SIZE 32
#define BASE_SAVE_AREA_SIZE  16
#define SAVE_AREA_OFFSET (EXTRA_SAVE_AREA_SIZE + BASE_SAVE_AREA_SIZE)
#define BASE_AREA_SP_OFFSET  12

#ifdef __ASSEMBLER__
    .macro SET_STACK  new_sp tmp1 tmp2
    addi tmp1, new_sp, -SAVE_AREA_OFFSET
    addi tmp2, tmp1, -BASE_AREA_SP_OFFSET
    s32i new_sp, tmp2, 0
    addi new_sp, tmp1, 0
    rsr.ps \tmp1
    movi \tmp2, ~(PS_WOE_MASK | PS_OWB_MASK | PS_CALLINC_MASK)
    and \tmp1, \tmp1, \tmp2
    wsr.ps \tmp1
    rsync

    rsr.windowbase \tmp1
    ssl	\tmp1
    movi \tmp1, 1
    sll	\tmp1, \tmp1
    wsr.windowstart \tmp1
    rsync

    mov sp, \new_sp

    rsr.ps \tmp1
    movi \tmp2, (PS_WOE)
    or \tmp1, \tmp1, \tmp2
    wsr.ps \tmp1
    rsync
    .endm
#else

#define SET_STACK(new_sp) \
    do { \
        uint32_t sp = (uint32_t)new_sp - SAVE_AREA_OFFSET; \
        *(uint32_t*)(sp - BASE_AREA_SP_OFFSET) = (uint32_t)new_sp; \
        uint32_t tmp1 = 0, tmp2 = 0; \
        asm volatile ( \
          "rsr.ps %1 \n"\
          "movi %2, ~" XTSTR( PS_WOE_MASK | PS_OWB_MASK | PS_CALLINC_MASK ) " \n"\
          "and %1, %1, %2 \n"\
          "wsr.ps %1 \n"\
          "rsync \n"\
          " \n"\
          "rsr.windowbase %1 \n"\
          "ssl	%1 \n"\
          "movi %1, 1 \n"\
          "sll	%1, %1 \n"\
          "wsr.windowstart %1 \n"\
          "rsync \n"\
          " \n"\
          "mov sp, %0 \n"\
          "rsr.ps %1 \n"\
          " \n"\
          "movi %2, " XTSTR( PS_WOE_MASK ) "\n"\
          " \n"\
          "or %1, %1, %2 \n"\
          "wsr.ps %1 \n"\
          "rsync \n"\
          : "+r"(sp), "+r"(tmp1), "+r"(tmp2)); \
    } while (0);
#endif // __ASSEMBLER__


#if !defined(_ASMLANGUAGE) && !defined(_NOCLANGUAGE) && !defined(__ASSEMBLER__)

#define XTHAL_USE_CACHE_MACROS

#if XCHAL_ICACHE_SIZE > 0
# define xthal_icache_line_invalidate(addr)	do { void *__a = (void*)(addr); \
		__asm__ __volatile__("ihi %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
#else
# define xthal_icache_line_invalidate(addr)	do {/*nothing*/} while(0)
#endif

#if XCHAL_ICACHE_SIZE > 0 && XCHAL_ICACHE_LINE_LOCKABLE
# define xthal_icache_line_lock(addr)	do { void *__a = (void*)(addr);	 	\
		__asm__ __volatile__("ipfl %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
# define xthal_icache_line_unlock(addr)	do { void *__a = (void*)(addr); 	\
		__asm__ __volatile__("ihu %0, 0" :: "a"(__a) : "memory");	\
		} while(0)
#else
# define xthal_icache_line_lock(addr)		do {/*nothing*/} while(0)
# define xthal_icache_line_unlock(addr)		do {/*nothing*/} while(0)
#endif

#define xthal_icache_sync()							\
		__asm__ __volatile__("isync":::"memory")

#if XCHAL_DCACHE_SIZE > 0

# include <xtensa/tie/xt_datacache.h>

# define xthal_dcache_line_invalidate(addr)	do { void *__a = (void*)(addr); \
		__asm__ __volatile__("dhi %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
# define xthal_dcache_line_writeback(addr)	do { void *__a = (void*)(addr); \
		__asm__ __volatile__("dhwb %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
# define xthal_dcache_line_writeback_inv(addr)	do { void *__a = (void*)(addr); \
		__asm__ __volatile__("dhwbi %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
# define xthal_dcache_sync()							\
		__asm__ __volatile__("" /*"dsync"?*/:::"memory")
# define xthal_dcache_line_prefetch_for_read(addr) do {				\
		XT_DPFR((const int*)addr, 0);					\
		} while(0)
#else
# define xthal_dcache_line_invalidate(addr)		do {/*nothing*/} while(0)
# define xthal_dcache_line_writeback(addr)		do {/*nothing*/} while(0)
# define xthal_dcache_line_writeback_inv(addr)		do {/*nothing*/} while(0)
# define xthal_dcache_sync()				__asm__ __volatile__("":::"memory")
# define xthal_dcache_line_prefetch_for_read(addr)	do {/*nothing*/} while(0)
#endif

#if XCHAL_DCACHE_SIZE > 0 && XCHAL_DCACHE_LINE_LOCKABLE
# define xthal_dcache_line_lock(addr)	do { void *__a = (void*)(addr); 	\
		__asm__ __volatile__("dpfl %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
# define xthal_dcache_line_unlock(addr)	do { void *__a = (void*)(addr); 	\
		__asm__ __volatile__("dhu %0, 0" :: "a"(__a) : "memory"); 	\
		} while(0)
#else
# define xthal_dcache_line_lock(addr)		do {/*nothing*/} while(0)
# define xthal_dcache_line_unlock(addr)		do {/*nothing*/} while(0)
#endif

#if XCHAL_DCACHE_SIZE > 0 && XCHAL_DCACHE_IS_WRITEBACK

# define xthal_dcache_line_prefetch_for_write(addr) do {			\
		XT_DPFW((const int*)addr, 0);					\
		} while(0)
#else
# define xthal_dcache_line_prefetch_for_write(addr)	do {/*nothing*/} while(0)
#endif


/*****   Block Operations   *****/

#if XCHAL_DCACHE_SIZE > 0 && XCHAL_HAVE_CACHE_BLOCKOPS

/* upgrades */

# define _XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, type)		\
		{						\
		type((const int*)addr, size);			\
		}

/*downgrades */

# define _XTHAL_DCACHE_BLOCK_DOWNGRADE(addr, size, type)	\
	unsigned _s = size;					\
	unsigned _a = addr;					\
	do {							\
		unsigned __s = (_s > XCHAL_DCACHE_SIZE) ? 	\
				XCHAL_DCACHE_SIZE : _s; 	\
		type((const int*)_a, __s);			\
		_s -= __s; 					\
		_a += __s;					\
	} while(_s > 0);

# define _XTHAL_DCACHE_BLOCK_DOWNGRADE_MAX(addr, size, type, max)	\
	if (max <= XCHAL_DCACHE_SIZE) {					\
		unsigned _s = size;					\
		unsigned _a = addr;					\
		type((const int*)_a, _s);				\
	}								\
	else {								\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE(addr, size, type);	\
	}

# define xthal_dcache_block_invalidate(addr, size)	do { 		\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE(addr, size, XT_DHI_B);	\
		} while(0)
# define xthal_dcache_block_writeback(addr, size)	do {		\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE(addr, size, XT_DHWB_B);	\
		} while(0)
# define xthal_dcache_block_writeback_inv(addr, size)	do {		\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE(addr, size, XT_DHWBI_B);	\
		} while(0)

# define xthal_dcache_block_invalidate_max(addr, size, max)	do {		\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE_MAX(addr, size, XT_DHI_B, max);	\
		} while(0)
# define xthal_dcache_block_writeback_max(addr, size, max)	do { 		\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE_MAX(addr, size, XT_DHWB_B, max);	\
		} while(0)
# define xthal_dcache_block_writeback_inv_max(addr, size, max)	do {		\
		_XTHAL_DCACHE_BLOCK_DOWNGRADE_MAX(addr, size, XT_DHWBI_B, max);	\
		} while(0)

/* upgrades that are performed even with write-thru caches  */

# define xthal_dcache_block_prefetch_read_write(addr, size) do {	\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFW_B);	\
		} while(0)
# define xthal_dcache_block_prefetch_read_write_grp(addr, size) do {	\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFW_BF);	\
		} while(0)
# define xthal_dcache_block_prefetch_for_read(addr, size) do {		\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFR_B);	\
		} while(0)
# define xthal_dcache_block_prefetch_for_read_grp(addr, size) do {	\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFR_BF);	\
		} while(0)

/* abort all or end optional block cache operations */
# define xthal_dcache_block_abort()	do { 		\
		XT_PFEND_A();				\
		} while(0)
# define xthal_dcache_block_end()	do { 		\
		XT_PFEND_O();				\
		} while(0)

/* wait for all/required block cache operations to finish */
# define xthal_dcache_block_wait()	do { 		\
		XT_PFWAIT_A();				\
		} while(0)
# define xthal_dcache_block_required_wait()	do { 	\
		XT_PFWAIT_R();				\
		} while(0)
/* Start a new group */
# define xthal_dcache_block_newgrp()	do { 		\
		XT_PFNXT_F();				\
		} while(0)
#else
# define xthal_dcache_block_invalidate(addr, size)		do {/*nothing*/} while(0)
# define xthal_dcache_block_writeback(addr, size)		do {/*nothing*/} while(0)
# define xthal_dcache_block_writeback_inv(addr, size)		do {/*nothing*/} while(0)
# define xthal_dcache_block_invalidate_max(addr, size, max)	do {/*nothing*/} while(0)
# define xthal_dcache_block_writeback_max(addr, size, max)	do {/*nothing*/} while(0)
# define xthal_dcache_block_writeback_inv_max(addr, size, max) 	do {/*nothing*/} while(0)
# define xthal_dcache_block_prefetch_read_write(addr, size)	do {/*nothing*/} while(0)
# define xthal_dcache_block_prefetch_read_write_grp(addr, size)	do {/*nothing*/} while(0)
# define xthal_dcache_block_prefetch_for_read(addr, size)	do {/*nothing*/} while(0)
# define xthal_dcache_block_prefetch_for_read_grp(addr, size)	do {/*nothing*/} while(0)
# define xthal_dcache_block_end()   				do {/*nothing*/} while(0)
# define xthal_dcache_block_abort()  				do {/*nothing*/} while(0)
# define xthal_dcache_block_wait()  				do {/*nothing*/} while(0)
# define xthal_dcache_block_required_wait()   			do {/*nothing*/} while(0)
# define xthal_dcache_block_newgrp()				do {/*nothing*/} while(0)
#endif

#if XCHAL_DCACHE_SIZE > 0 && XCHAL_HAVE_CACHE_BLOCKOPS && XCHAL_DCACHE_IS_WRITEBACK

# define xthal_dcache_block_prefetch_for_write(addr, size) do {	\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFW_B);	\
		} while(0)
# define xthal_dcache_block_prefetch_modify(addr, size) do {		\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFM_B);	\
		} while(0)
# define xthal_dcache_block_prefetch_for_write_grp(addr, size) do {	\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFW_BF);	\
		} while(0)
# define xthal_dcache_block_prefetch_modify_grp(addr, size) do {	\
		_XTHAL_DCACHE_BLOCK_UPGRADE(addr, size, XT_DPFM_BF);	\
		} while(0)
#else
# define xthal_dcache_block_prefetch_for_write(addr, size)	do {/*nothing*/} while(0)
# define xthal_dcache_block_prefetch_modify(addr, size) 	do {/*nothing*/} while(0)
# define xthal_dcache_block_prefetch_for_write_grp(addr, size)	do {/*nothing*/} while(0)
# define xthal_dcache_block_prefetch_modify_grp(addr, size)  	do {/*nothing*/} while(0)
#endif

/***************************   INTERRUPTS   ***************************/

/*
 *  Macro versions of:
 *	unsigned  xthal_get_intenable( void );
 *	void      xthal_set_intenable( unsigned );
 *	unsigned  xthal_get_interrupt( void );
 *	void      xthal_set_intset( unsigned );
 *	void      xthal_set_intclear( unsigned );
 *	unsigned  xthal_get_ccount(void);
 *	void      xthal_set_ccompare(int, unsigned);
 *	unsigned  xthal_get_ccompare(int);
 *
 *  NOTE: for {set,get}_ccompare, the first argument MUST be a decimal constant.
 */

#if XCHAL_HAVE_INTERRUPTS
# define XTHAL_GET_INTENABLE()	({ int __intenable; \
				__asm__("rsr.intenable %0" : "=a"(__intenable)); \
				__intenable; })
# define XTHAL_SET_INTENABLE(v)	do { int __intenable = (int)(v); \
			__asm__ __volatile__("wsr.intenable %0" :: "a"(__intenable):"memory"); \
				} while(0)
# define XTHAL_GET_INTERRUPT()	({ int __interrupt; \
				__asm__("rsr.interrupt %0" : "=a"(__interrupt)); \
				__interrupt; })
# define XTHAL_SET_INTSET(v)	do { int __interrupt = (int)(v); \
			__asm__ __volatile__("wsr.intset %0" :: "a"(__interrupt):"memory"); \
				} while(0)
# define XTHAL_SET_INTCLEAR(v)	do { int __interrupt = (int)(v); \
			__asm__ __volatile__("wsr.intclear %0" :: "a"(__interrupt):"memory"); \
				} while(0)
# define XTHAL_GET_CCOUNT()	({ int __ccount; \
				__asm__("rsr.ccount %0" : "=a"(__ccount)); \
				__ccount; })
# define XTHAL_SET_CCOUNT(v)	do { int __ccount = (int)(v); \
			__asm__ __volatile__("wsr.ccount %0" :: "a"(__ccount):"memory"); \
				} while(0)
# define _XTHAL_GET_CCOMPARE(n)	({ int __ccompare; \
				__asm__("rsr.ccompare" #n " %0" : "=a"(__ccompare)); \
				__ccompare; })
# define XTHAL_GET_CCOMPARE(n)	_XTHAL_GET_CCOMPARE(n)
# define _XTHAL_SET_CCOMPARE(n,v) do { int __ccompare = (int)(v); \
			__asm__ __volatile__("wsr.ccompare" #n " %0 ; esync" :: "a"(__ccompare):"memory"); \
				} while(0)
# define XTHAL_SET_CCOMPARE(n,v) _XTHAL_SET_CCOMPARE(n,v)
#else
# define XTHAL_GET_INTENABLE()		0
# define XTHAL_SET_INTENABLE(v)		do {/*nothing*/} while(0)
# define XTHAL_GET_INTERRUPT()		0
# define XTHAL_SET_INTSET(v)		do {/*nothing*/} while(0)
# define XTHAL_SET_INTCLEAR(v)		do {/*nothing*/} while(0)
# define XTHAL_GET_CCOUNT()		0
# define XTHAL_SET_CCOUNT(v)		do {/*nothing*/} while(0)
# define XTHAL_GET_CCOMPARE(n)		0
# define XTHAL_SET_CCOMPARE(n,v)	do {/*nothing*/} while(0)
#endif


/***************************   MISC   ***************************/

/*
 *  Macro or inline versions of:
 *	void	  xthal_clear_regcached_code( void );
 *	unsigned  xthal_get_prid( void );
 *	unsigned  xthal_compare_and_set( int *addr, int testval, int setval );
 */

#if XCHAL_HAVE_LOOPS
# define XTHAL_CLEAR_REGCACHED_CODE()		\
		__asm__ __volatile__("wsr.lcount %0" :: "a"(0) : "memory")
#else
# define XTHAL_CLEAR_REGCACHED_CODE()		do {/*nothing*/} while(0)
#endif

#if XCHAL_HAVE_PRID
# define XTHAL_GET_PRID()	({ int __prid; \
				__asm__("rsr.prid %0" : "=a"(__prid)); \
				__prid; })
#else
# define XTHAL_GET_PRID()	0
#endif


static inline unsigned  XTHAL_COMPARE_AND_SET( int *addr, int testval, int setval )
{
    int result;

#if XCHAL_HAVE_S32C1I && XCHAL_HW_MIN_VERSION_MAJOR >= 2200
    __asm__ __volatile__ (
	"   wsr.scompare1 %2 \n"
	"   s32c1i %0, %3, 0 \n"
	    : "=a"(result) : "0" (setval), "a" (testval), "a" (addr)
	    : "memory");
#elif XCHAL_HAVE_INTERRUPTS
    int tmp;
    __asm__ __volatile__ (
        "   rsil   %4, 15 \n"		// %4 == saved ps
        "   l32i   %0, %3, 0 \n"	// %0 == value to test, return val
        "   bne    %2, %0, 9f \n"	// test
        "   s32i   %1, %3, 0 \n"	// write the new value
	"9: wsr.ps %4 ; rsync \n"	// restore the PS
	: "=a"(result) 
	: "0" (setval), "a" (testval), "a" (addr), "a" (tmp)
	: "memory");
#else
    __asm__ __volatile__ (
        "   l32i  %0, %3, 0 \n"		// %0 == value to test, return val
        "   bne   %2, %0, 9f \n"	// test
        "   s32i  %1, %3, 0 \n"		// write the new value
	"9: \n"
	    : "=a"(result) : "0" (setval), "a" (testval), "a" (addr)
	    : "memory");
#endif
    return result;
}

#if XCHAL_HAVE_EXTERN_REGS

static inline unsigned XTHAL_RER (unsigned int reg)
{
  unsigned result;

  __asm__ __volatile__ (
	"   rer     %0, %1"
	: "=a" (result) : "a" (reg) : "memory");

  return result;
}

static inline void XTHAL_WER (unsigned reg, unsigned value)
{
  __asm__ __volatile__ (
	"   wer     %0, %1"
	: : "a" (value), "a" (reg) : "memory");
}

#endif /* XCHAL_HAVE_EXTERN_REGS */

#endif /* C code */
