#include "driver/inc/WDT.h"

void WWDT_Config(void)
{
    WWDT->CTRL_b.DIV = 0x06;      // 2^n分频 64分频
    WWDT->CTRL_b.WARNIEN = 0x00;  // 预警功能不使能
    WWDT->CTRL_b.LOWLIMIT = 0x00; // 选择0为窗口下限值
    WWDT->CTRL_b.WARNSEL = 0x00;  // 预警值为计数值一半
    WWDT->CTRL_b.DEBUG = 0x01;    // 调试模式下WDT暂停
    WWDT->RELOAD = 146250;        // 130ms	 时钟72/64=1.125M

    WWDT->CTRL_b.EN = 1; // 看门狗使能

    WWDT->FEED = 0x1ACCE551;
}

void WWDT_Clear(void)
{
    WWDT->FEED = 0x1ACCE551;
}

void IWDT_Config(void)
{
    CHIP_KEY_EN();
    CHIPCTRL->IWDTCFG_b.WINEN = 0; // 窗口功能无效
    CHIP_KEY_EN();
    CHIPCTRL->IWDTCFG_b.WINSEL = 0; // 0,重载值为RLD  1,重载值为RLD/2值

    CHIP_KEY_EN();
    CHIPCTRL->IWDTCLKDIV_b.CLKDIV = 0; // 时钟预分频
    CHIP_KEY_EN();
    CHIPCTRL->IWDTRLD_b.RLD = 3200; // 计数器装载值 100ms复位 时钟32K

    CHIP_KEY_EN();
    CHIPCTRL->IWDTCTRL = 0X05FACCCC;
}

void IWDT_Clear(void)
{
    while (CHIPCTRL->IWDTSTATUS_b.UPDATING == 1)
        ;
    __disable_irq();
    CHIP_KEY_EN();
    CHIPCTRL->IWDTCTRL = 0X05FACCCC;
    __enable_irq();
}
