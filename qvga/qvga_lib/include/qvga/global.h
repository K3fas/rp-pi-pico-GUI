#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <stdint.h>

// I/O port prefix
#define __IO	volatile

// request to use inline
#define INLINE __attribute__((always_inline)) inline

// avoid to use inline
#define NOINLINE __attribute__((noinline))

// weak function
#define WEAK __attribute__((weak))

// align array to 4-bytes
#define ALIGNED __attribute__((aligned(4)))

// default LED pin
#define LED_PIN 25

// nop instruction
INLINE void nop()
	{ __asm volatile (" nop\n"); }

// compiler barrier
INLINE void cb()
	{ __asm volatile ("" ::: "memory"); }

// ----------------------------------------------------------------------------
//                               Constants
// ----------------------------------------------------------------------------

#define	B0 (1<<0)
#define	B1 (1<<1)
#define	B2 (1<<2)
#define	B3 (1<<3)
#define	B4 (1<<4)
#define	B5 (1<<5)
#define	B6 (1<<6)
#define	B7 (1<<7)
#define	B8 (1U<<8)
#define	B9 (1U<<9)
#define	B10 (1U<<10)
#define	B11 (1U<<11)
#define	B12 (1U<<12)
#define	B13 (1U<<13)
#define	B14 (1U<<14)
#define	B15 (1U<<15)
#define B16 (1UL<<16)
#define B17 (1UL<<17)
#define B18 (1UL<<18)
#define	B19 (1UL<<19)
#define B20 (1UL<<20)
#define B21 (1UL<<21)
#define B22 (1UL<<22)
#define B23 (1UL<<23)
#define B24 (1UL<<24)
#define B25 (1UL<<25)
#define B26 (1UL<<26)
#define B27 (1UL<<27)
#define B28 (1UL<<28)
#define B29 (1UL<<29)
#define B30 (1UL<<30)
#define B31 (1UL<<31)

#define BIT(pos) (1UL<<(pos))

#define	BIGINT	0x40000000 // big int value

#define _T(a) a

#define PI 3.14159265358979324
#define PI2 (3.14159265358979324*2)

#endif // _GLOBAL_H