#ifndef __ADC_H__
#define __ADC_H__
#include "driver/inc/SLMCU.h"

#define ADC_CLKDIV_2  0  // 2分频
#define ADC_CLKDIV_3  1  // 3分频
#define ADC_CLKDIV_4  2  // 4分频
#define ADC_CLKDIV_5  3  // 5分频
#define ADC_CLKDIV_6  4  // 6分频
#define ADC_CLKDIV_8  5  // 8分频
#define ADC_CLKDIV_10 6  // 10分频
#define ADC_CLKDIV_12 7  // 12分频
#define ADC_CLKDIV_14 8  // 14分频
#define ADC_CLKDIV_16 9  // 16分频
#define ADC_CLKDIV_18 10 // 18分频
#define ADC_CLKDIV_20 11 // 20分频
#define ADC_CLKDIV_26 12 // 26分频
#define ADC_CLKDIV_32 13 // 32分频
#define ADC_CLKDIV_64 14 // 64分频

// #define ACCESS_EN() SYSCFG->ACCESSEN = 0x05fa659a										// 关闭写保护
#define ADC_RESET                                                                                                      \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.RESET = 1; // ADC模块重启
#define ADC_ENABLE                                                                                                     \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.EN = 1; // ADC模块使能
#define ADC_DISABLE                                                                                                    \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.EN = 0; // ADC模块禁止
#define ADC_NONOVERLAP                                                                                                 \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL2 |= (1 << 1); // 采样与转换不重叠
#define ADC_OVERLAP                                                                                                    \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL2 &= ~(1 << 1);                      // 采样与转换重叠
#define ADC_MODE2       ADC->ADCTRIM_b.mode2 = 1;   // ADC模式2
#define ADC_VOL_SEL_50V ADC->ADCTRIM_b.vol_sel = 1; // 内部电压参考选择5.0V
#define ADC_VOL_SEL_33V ADC->ADCTRIM_b.vol_sel = 0; // 内部电压参考选择3.3V
#define ADC_INT_AT_EOC                                                                                                 \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.INTPLSC = 1; // EOC脉冲产生于放入结果寄存器前的一个周期
#define ADC_INT_AT_SOC                                                                                                 \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.INTPLSC = 0; // EOC脉冲产生于转换开始时
#define ADC_REF_INTERNAL                                                                                               \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.REFSEL = 0; // ADC使用内部参考电压
#define ADC_REF_EXT_VREF                                                                                               \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.REFSEL = 1; // ADC使用外部参考电压

extern void ADC_Init(void);

#endif
