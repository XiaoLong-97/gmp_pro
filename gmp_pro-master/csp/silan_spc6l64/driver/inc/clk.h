#ifndef __CLK_H__
#define __CLK_H__

//#include "driver/inc/IQmathLib.h"
#include "driver/inc/SLMCU.h"


// MHz,系统时钟  (不建议修改)
//#define SYS_CLK (72)

#define PLLSRC_RCH   0
#define PLLSRC_OSC   1

#define PLLDIV1      0
#define PLLDIV2      1
#define PLLDIV3      2
#define PLLDIV4      3
#define PLLDIV5      4
#define PLLDIV6      5
#define PLLDIV7      6
#define PLLDIV8      7
#define PLLDIV9      8
#define PLLDIV10     9
#define PLLDIV11     10
#define PLLDIV12     11
#define PLLDIV13     12
#define PLLDIV14     13
#define PLLDIV15     14
#define PLLDIV16     15

#define PLLMUL24     0
#define PLLMUL28     1
#define PLLMUL32     2
#define PLLMUL36     3

#define OSCGAIN1_4   0
#define OSCGAIN4_8   1
#define OSCGAIN8_16  2
#define OSCGAIN16_32 3

#define OSCSTB4MS    0
#define OSCSTB8MS    1
#define OSCSTB16MS   2
#define OSCSTB32MS   3

extern void FlashRW_Config(uint8_t wt);
extern void SRAM1_Config(void);
extern void OPENRCL128K(void);
extern void CLOSERCL128K(void);
extern void SYSCLKSET(uint8_t syssel);
extern void OPENRCH(void);
extern void CLOSERCH(void);
extern void RCHSELECT(uint8_t rchsel);
extern uint8_t SYS_Config(uint8_t clk, uint8_t wt);

#endif
