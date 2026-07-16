#ifndef _BT01_H
#define _BT01_H

#include "driver/inc/BT01.h"
#include "driver/inc/GPIO.h"
#include "driver/inc/SLMCU.h"

typedef enum
{
    fclk_2 = 0,
    fclk_4 = 1,
    fclk_8 = 2,
    fclk_16 = 3,
    fclk_32 = 4,
    fclk_64 = 5,
    fclk_128 = 6,
    fclk_256 = 7,
} PSC_enum;

typedef enum
{
    EXINT4 = 3,
    ACMP0 = 0,
    ACMP1 = 1,
    ACMP2 = 2,
} TZSEL_enum;

void BT0_TimingMode_test(void);
void BT1_TimingMode_test(void);
void BT0_capture_test(void);
void BT1_capture_test(void);
void BT0_CountMode_test(void);
void BT1_CountMode_test(void);
void BT0_T0PWM_test(void);
void BT1_T0PWM_test(void);
void BT0_capture1_test(void);
void BT1_capture1_test(void);

#endif
