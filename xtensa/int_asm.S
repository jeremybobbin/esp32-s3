// 
// int_asm.S - assembly language interrupt utility routines
//
// $Id: //depot/rel/Eaglenest/Xtensa/OS/hal/int_asm.S#1 $

// Copyright (c) 2003-2010 Tensilica Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <xtensa/coreasm.h>


#define GBL(x)   .global x
#define TYP(x)   .type x,@function
#define ALN(x)   .align x
#define SIZ(x)   .size x, . - x
#define MKEND(x) .purgem endfunc ; .macro endfunc ; SIZ(x) ; .purgem endfunc ; .macro endfunc ; .endm ; .endm
#define SYMT(x)  GBL(x); MKEND(x); TYP(x); ALN(4); x:
#define SYM(x)   GBL(x); MKEND(x); ALN(4); x:
	.macro endfunc ; .endm

# define SYMBOL(x)  SYMT(x)


#if XCHAL_HAVE_INTERRUPTS
/*  Offsets of XtHalVPriState structure members (Xthal_vpri_state variable):  */
#define XTHAL_VPRI_VPRI_OFS		0x00
#define XTHAL_VPRI_LOCKLEVEL_OFS	0x01
#define XTHAL_VPRI_LOCKVPRI_OFS		0x02
#define XTHAL_VPRI_PAD0_OFS		0x03
#define XTHAL_VPRI_ENABLED_OFS		0x04
#define XTHAL_VPRI_LOCKMASK_OFS		0x08
#define XTHAL_VPRI_PAD1_OFS		0x0C
#define XTHAL_VPRI_ENABLEMAP_OFS	0x10
#define XTHAL_VPRI_RESOLVEMAP_OFS	(0x10+0x40*(XCHAL_NUM_INTLEVELS+1))
#define XTHAL_VPRI_END_OFS		(0x10+0x40*(XCHAL_NUM_INTLEVELS*2+1))
#endif /* XCHAL_HAVE_INTERRUPTS */


// unsigned xthal_get_intenable(void)
//
SYMT(xthal_get_intenable)
	abi_entry
	rsr	a2, INTENABLE
	abi_return
	endfunc


// void xthal_set_intenable(unsigned)
//
SYMT(xthal_set_intenable)
	abi_entry
	wsr	a2, INTENABLE
	abi_return
	endfunc


// unsigned xthal_get_interrupt(void)
//
SYMT(xthal_get_interrupt)
SYMT(xthal_get_intread)
	abi_entry
	rsr	a2, INTERRUPT
	abi_return
	endfunc

// void xthal_set_intset(unsigned)
//
SYMT(xthal_set_intset)
	abi_entry
	wsr	a2, INTSET
	abi_return
	endfunc

// void xthal_set_intclear(unsigned)
//
SYMT(xthal_set_intclear)
	abi_entry
	wsr	a2, INTCLEAR
	abi_return
	endfunc



// unsigned xthal_get_vpri(void);

SYMBOL(xthal_get_vpri)
	abi_entry
	movi	a2, Xthal_vpri_state
	l8ui	a2, a2, XTHAL_VPRI_VPRI_OFS
	abi_return
	endfunc

// -----------------------------------------------------------------

// void xthal_vpri_lock()
//
// Used internally by the Core HAL to block interrupts of higher or equal
// priority than Xthal_vpri_locklevel during virtual interrupt operations.
//
SYMT(xthal_vpri_lock)
	abi_entry
	rsil	a6, 1				// save a6 = PS, set PS.INTLEVEL = 1

	//     if( Xthal_vpri_level < Xthal_vpri_locklevel )
	//
	movi	a2, Xthal_vpri_state		// a2 := address of global var. Xthal_vpri_state
	//interlock
	l8ui	a3, a2, XTHAL_VPRI_VPRI_OFS	// a3 := Xthal_vpri_level == Xthal_vpri_state.vpri
	l8ui	a5, a2, XTHAL_VPRI_LOCKLEVEL_OFS  // a5 := Xthal_vpri_locklevel
	l32i	a4, a2, XTHAL_VPRI_ENABLED_OFS	// a4 := Xthal_vpri_enabled 
	bgeu	a3, a5, xthal_vpri_lock_done

	//  xthal_set_intenable( Xthal_vpri_enablemap[0][Xthal_vpri_locklevel] & Xthal_vpri_enabled );
	//
	addx4	a3, a5, a2			// a3 := a2 + a5*4  (index into enablemap[] array)
	l32i	a3, a3, XTHAL_VPRI_ENABLEMAP_OFS // a3 := Xthal_vpri_enablemap[0][Xthal_vpri_locklevel]
	//interlock
	and	a2, a4, a3
  	wsr	a2, INTENABLE

xthal_vpri_lock_done:
	wsr	a6, PS				// restore PS.INTLEVEL
	rsync
	abi_return
	endfunc


// void xthal_vpri_unlock(void)
//
// Enable interrupts according to the current virtual interrupt priority.
// This effectively "unlocks" interrupts disabled by xthal_vpri_lock()
// (assuming the virtual interrupt priority hasn't changed).
//
SYMT(xthal_vpri_unlock)
	abi_entry
        //
	//  This should be free of race-conditions.
	//
        //  xthal_set_intenable( Xthal_vpri_enablemap[0][Xthal_vpri_level] & Xthal_vpri_enabled );
	//
	movi	a2, Xthal_vpri_state		 // a2 := address of global var. Xthal_vpri_state
	//interlock
	l8ui	a3, a2, XTHAL_VPRI_VPRI_OFS      // a3 := Xthal_vpri_level == Xthal_vpri_state.vpri
	l32i	a4, a2, XTHAL_VPRI_ENABLED_OFS	 // a4 := Xthal_vpri_enabled 
	addx4	a3, a3, a2                       // a3 := a2 + a3*4  (index into enablemap[] array)
	l32i	a3, a3, XTHAL_VPRI_ENABLEMAP_OFS // a3 := Xthal_vpri_enablemap[0][Xthal_vpri_level]
	//interlock
	and	a2, a4, a3
  	wsr	a2, INTENABLE
	abi_return
	endfunc


