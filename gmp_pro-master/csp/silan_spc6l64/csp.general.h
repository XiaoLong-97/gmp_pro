/**
 * @file csp.general.h
 * @author Javnson (javnson@zju.edu.cn)
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright GMP(c) 2024
 *
 */

#include <csp.config.h>

// Chip Support
#include "driver/inc/ACMP.h"
#include "driver/inc/BT01.h"
#include "driver/inc/DMA.h"
#include "driver/inc/GPIO.h"
#include "driver/inc/IAP.h"
#include "driver/inc/IRQ.h"
#include "driver/inc/OPA.h"
#include "driver/inc/SLMCU.h"
#include "driver/inc/SPI.h"
#include "driver/inc/WDT.h"
#include "driver/inc/adc.h"
#include "driver/inc/clk.h"
#include "driver/inc/config.h"
#include "driver/inc/coproc.h"
#include "driver/inc/math_func.h"
#include "driver/inc/public.h"
#include "driver/inc/pwm.h"
#include "driver/inc/timer.h"
#include "driver/inc/uart1.h"

extern void Main_ISR(void);
extern void T0_ISR(void);
