#ifndef __COPROC_H__
#define __COPROC_H__

#include "driver/inc/SLMCU.h"


#define MULT_SIGNED      (1 << 31)
#define MULT_UNSIGNED    (0 << 31)
#define SHIFT_EN         (1 << 17)
#define SHIFT_DIS        (0 << 17)
#define SHIFT_SEL_EN     (1 << 16)
#define SHIFT_SEL_NUM    (0 << 16)

#define _IQmpy(A, B)     silan_mult_Iq24(A, B)
#define _IQdiv_MDU(A, B) silan_div_Iq24(A, B)
#define _IQdiv2(A)          ((A)>>1)
#define _IQdiv4(A)          ((A)>>2)

#define MULT_INIT_MACRO()                                                                                              \
    COPROC->MULT_CTRL = (MULT_SIGNED + SHIFT_EN + SHIFT_SEL_EN);                                                       \
    COPROC->SHIFT_NUM = GLOBAL_Q;

// c=a*b
__STATIC_INLINE
int32_t silan_mult(int32_t a, int32_t b)
{
    int32_t c;
    __disable_irq();
    COPROC->MULCTL = 1;
    COPROC->MULCTL = 0x80080000;
    COPROC->MULA = a;
    COPROC->MULB = b;
    __NOP();
    c = COPROC->MULRSLTL;
    __enable_irq();
    return c;
}

// d = (a*b)>>c
__STATIC_INLINE
int64_t silan_mult_Iqx(int32_t a, int32_t b, int32_t c)
{
    int64_t d;
    __disable_irq();
    COPROC->MULCTL = 1;
    COPROC->MULCTL |= 0x80030000;
    COPROC->SHIFTNUM = c;
    COPROC->MULA = a;
    COPROC->MULB = b;
    __NOP();
    d = COPROC->MULRSLTH;
    d <<= 32;
    d |= COPROC->MULRSLTL;
    __enable_irq();
    return d;
}

//__attribute__ ((section ("RAMCODE")))
__STATIC_INLINE
int32_t silan_mult_Iq24(int32_t a, int32_t b)
{
    int32_t c;
    __disable_irq();
    COPROC->MULA = a;
    COPROC->MULB = b;
    __NOP();
    c = COPROC->MULRSLTL;
    __enable_irq();
    return c;
}

// A*B+C*D
__STATIC_INLINE
int32_t silan_mult_abPcd(int32_t a, int32_t b, int32_t c, int32_t d)
{
    int32_t e;
    __disable_irq();
    COPROC->MULA = a;
    COPROC->MULB = b;
    COPROC->MULAADD = c;
    COPROC->MULBADD = d;
    e = COPROC->MULRSLTL;
    __enable_irq();
    return e;
}

// A*B-C*D
__STATIC_INLINE
int32_t silan_mult_abMcd(int32_t a, int32_t b, int32_t c, int32_t d)
{
    int32_t e;
    __disable_irq();
    COPROC->MULA = a;
    COPROC->MULB = b;
    COPROC->MULASUB = c;
    COPROC->MULBSUB = d;
    e = COPROC->MULRSLTL;
    __enable_irq();
    return e;
}

// *****************div***********************
#define DIVIDER_32BIT (1 << 8)
#define DIVIDER_64BIT (0 << 8)

#define DIV_RESET     (COPROC->DIV_CTRL |= 0x01)
#define DIV_INIT_MACRO()                                                                                               \
    COPROC->DIV_CTRL = DIVIDER_64BIT;                                                                                  \
    DIV_RESET;

__STATIC_INLINE
int32_t silan_div(int32_t dividend, int32_t divisor)
{
    int32_t tmp;
    __disable_irq();
    COPROC->DIVCTL = 1;
    COPROC->DIVCTL = 0x00000100;
    COPROC->DIVAL = dividend;
    COPROC->DIVB = divisor;
    __NOP();
    tmp = COPROC->DIVQUOL;
    __enable_irq();

    return tmp;
}

__STATIC_INLINE
int32_t silan_div_Iq24(int32_t dividend, int32_t divisor)
{
    int64_t tmp;
    __disable_irq();
    COPROC->DIVCTL = 1;
    COPROC->DIVCTL = 0x00000000;
    COPROC->DIVAL = 0;
    COPROC->DIVAH = dividend;
    COPROC->DIVB = divisor;
    __NOP();
    __NOP();
    tmp = COPROC->DIVQUOH;
    tmp = (tmp << 32) | COPROC->DIVQUOL;
    tmp = tmp >> 8;

    __enable_irq();
    return tmp;
}

#define MULT_MACRO(a, b)        silan_mult(a, b)
#define MULT_MACRO_IQX(a, b, c) silan_mult_Iqx(a, b, c)
#define DIV_MACRO(a, b)         silan_div(a, b)
#define SINPU_MACRO(a)          silan_sinpu(a)
#define COSPU_MACRO(a)          silan_cospu(a)

extern void MultiTest(void);
extern void MultiIQTest(void);
extern void DivTest(void);
extern void MultiabPcd(void);
extern void MultiabMcd(void);

extern void Coproc_Init(void);

#endif
