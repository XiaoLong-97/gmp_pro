#ifndef __WDT_H__
#define __WDT_H__

#include "driver/inc/SLMCU.h"

void WWDT_Config(void);
void WWDT_Clear(void);

void IWDT_Config(void);
void IWDT_Clear(void);

#endif
