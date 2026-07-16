#ifndef __GPIO_H__
#define __GPIO_H__

#include "driver/inc/SLMCU.h"

#define DIGITAL (0 << 4)
#define ANALOGY (1 << 4)

typedef enum
{
    EXINT_PINSEL_PA00 = 0,
    EXINT_PINSEL_PA01 = 1,
    EXINT_PINSEL_PA02,
    EXINT_PINSEL_PA03,
    EXINT_PINSEL_PA04,
    EXINT_PINSEL_PA05,
    EXINT_PINSEL_PA06,
    EXINT_PINSEL_PA07,
    EXINT_PINSEL_PA08,
    EXINT_PINSEL_PA09,
    EXINT_PINSEL_PA10,
    EXINT_PINSEL_PA11,
    EXINT_PINSEL_PA12,
    EXINT_PINSEL_PA13,
    EXINT_PINSEL_PA14,
    EXINT_PINSEL_PA15,

    EXINT_PINSEL_PB00,
    EXINT_PINSEL_PB01,
    EXINT_PINSEL_PB02,
    EXINT_PINSEL_PB03,
    EXINT_PINSEL_PB04,
    EXINT_PINSEL_PB05,
    EXINT_PINSEL_PB06,
    EXINT_PINSEL_PB07,
    EXINT_PINSEL_PB08,
    EXINT_PINSEL_PB09,
    EXINT_PINSEL_PB10,
    EXINT_PINSEL_PB11,
    EXINT_PINSEL_PB12,
    EXINT_PINSEL_PB13,
    EXINT_PINSEL_PB14,
    EXINT_PINSEL_PB15,

    EXINT_PINSEL_PC00,
    EXINT_PINSEL_PC01,
    EXINT_PINSEL_PC02,
    EXINT_PINSEL_PC03,
    EXINT_PINSEL_PC04,
    EXINT_PINSEL_PC05,
    EXINT_PINSEL_PC06,
    EXINT_PINSEL_PC07,
    EXINT_PINSEL_PC08,
    EXINT_PINSEL_PC09,
    EXINT_PINSEL_PC10,
    EXINT_PINSEL_PC11,
    EXINT_PINSEL_PC12,
    EXINT_PINSEL_PC13,
    EXINT_PINSEL_PC14,
    EXINT_PINSEL_PC15,
} EXINT_PINSEL;

typedef enum
{
    EXINT_DIR0_INTNON = 0,        // 正向输入、无中断//0000
    EXINT_DIR1_INTNON = 1,        // 反向输入、无中断//0001
    EXINT_DIR0_TYPE0_INTPOS = 4,  // 正向输入，上升沿中断//0100
    EXINT_DIR1_TYPE0_INTPOS = 5,  // 反向输入，上升沿中断//0101
    EXINT_DIR0_TYPE0_INTNEG = 8,  // 正向输入，下降沿中断//1000
    EXINT_DIR1_TYPE0_INTNEG = 9,  // 反向输入，下降沿中断//1001
    EXINT_DIR0_TYPE0_INTDOU = 12, // 正向输入，双边沿中断//1100
    EXINT_DIR1_TYPE0_INTDOU = 13, // 反向输入，双边沿中断//1101

    EXINT_DIR0_TYPE1_INTPOS = 6,  // 正向输入，高电平触发//0110
    EXINT_DIR0_TYPE1_INTNEG = 10, // 正向输入，低电平触发//1010
    EXINT_DIR1_TYPE1_INTPOS = 7,  // 反向输入，高电平触发//0111
    EXINT_DIR1_TYPE1_INTNEG = 11, // 反向输入，低电平触发//1011
} EXINT_TYPE;

#define EXINT_DIV(m) (m)
#define EXINT_PSC(n) (n)

extern void Gpio_Af_Sel(uint8_t, PA_Type *, uint8_t, uint8_t);
extern void Gpio_Init(void);
extern void GPIO_TOGGLE(PA_Type *Px, uint8_t n);
extern void EXINT_Config(uint8_t num, EXINT_PINSEL pin, EXINT_TYPE intype, uint8_t div, uint8_t psc);
extern void System_Deep_Sleep(void);
extern void SPI_Init(void);

#endif
