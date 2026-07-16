#ifndef __PWM_H__
#define __PWM_H__

#include "driver/inc/GPIO.h"
#include "driver/inc/SLMCU.h"

extern void Motor_Stop(void);
extern void Motor_Brake(void);
extern void TZ_Clear(void);
extern void PWM_Init(uint32_t);
extern void Pwm_Cmp_Clr(void);

#define START_ALL_PWM                                                                                                  \
    {                                                                                                                  \
        ACCESS_EN();                                                                                                   \
        SYSCFG->PWMCFG |= 0x00000007ul;                                                                                \
    }
#define STOP_ALL_PWM                                                                                                   \
    {                                                                                                                  \
        ACCESS_EN();                                                                                                   \
        SYSCFG->PWMCFG &= ~0x00000007ul;                                                                               \
    }

#define GPIO_OUT_HIC                                                                                                   \
    {                                                                                                                  \
        ACCESS_EN();                                                                                                   \
        SYSCFG->PWMCFG |= 0x00000700ul;                                                                                \
    }
#define GPIO_OUT_PWM                                                                                                   \
    {                                                                                                                  \
        ACCESS_EN();                                                                                                   \
        SYSCFG->PWMCFG &= ~0x00000700ul;                                                                               \
    }

#define LOWER_PWM_UPPER_FORCELOW                                                                                       \
    {                                                                                                                  \
        PWM0->AQCSFRC = 1;                                                                                             \
        PWM1->AQCSFRC = 1;                                                                                             \
        PWM2->AQCSFRC = 1;                                                                                             \
    }
#define PWM_DUTY_SET(a, b)                                                                                             \
    {                                                                                                                  \
        PWM0->CMPA = a;                                                                                                \
        PWM0->CMPB = b;                                                                                                \
        PWM1->CMPA = a;                                                                                                \
        PWM1->CMPB = b;                                                                                                \
        PWM2->CMPA = a;                                                                                                \
        PWM2->CMPB = b;                                                                                                \
    }

#define CTRMODE_UP             0 // 增计数模式
#define CTRMODE_DOWN           1 // 减计数模式
#define CTRMODE_UPDOWN         2 // 增减计数模式

#define PHASE_ENABLE           1 // 相位装载使能
#define PHASE_DISABLE          0 // 相位装载禁止

#define PRD_SHADOWON           0 // 使能映射寄存器
#define PRD_SHADOWOFF          1 // 禁止映射寄存器

#define SYNCOSEL_SYNC          0 // 同步源选择SYNC
#define SYNCOSEL_CTR_ZERO      1 // 同步源选择CTR=0
#define SYNCOSEL_CTR_CMPB      2 // 同步源选择CTR=CMPB
#define SYNCOSEL_DISABLE       3 // 禁用同步信号

#define SHADOWMODE_ON          0 // 映射模式
#define SHADOWMODE_OFF         1 // 直接模式

#define CMP_LOAD_ZERO          0 // CTR=0时加载
#define CMP_LOAD_PRD           1 // CTR=PRD时加载
#define CMP_LOAD_ZERO_PRD      2 // CTR=0或CTR=PRD时加载
#define CMP_FREEZE             3 // 冻结

#define AQ_CBD_NOACTION        0 // 减计数模式中，CTR=CMPB时，无动作
#define AQ_CBD_CLR             1 // 减计数模式中，CTR=CMPB时，置低
#define AQ_CBD_SET             2 // 减计数模式中，CTR=CMPB时，置高
#define AQ_CBD_TGL             3 // 减计数模式中，CTR=CMPB时，翻转

#define AQ_CBU_NOACTION        0 // 增计数模式中，CTR=CMPB时，无动作
#define AQ_CBU_CLR             1 // 增计数模式中，CTR=CMPB时，置低
#define AQ_CBU_SET             2 // 增计数模式中，CTR=CMPB时，置高
#define AQ_CBU_TGL             3 // 增计数模式中，CTR=CMPB时，翻转

#define AQ_CAD_NOACTION        0 // 减计数模式中，CTR=CMPA时，无动作
#define AQ_CAD_CLR             1 // 减计数模式中，CTR=CMPA时，置低
#define AQ_CAD_SET             2 // 减计数模式中，CTR=CMPA时，置高
#define AQ_CAD_TGL             3 // 减计数模式中，CTR=CMPA时，翻转

#define AQ_CAU_NOACTION        0 // 增计数模式中，CTR=CMPA时，无动作
#define AQ_CAU_CLR             1 // 增计数模式中，CTR=CMPA时，置低
#define AQ_CAU_SET             2 // 增计数模式中，CTR=CMPA时，置高
#define AQ_CAU_TGL             3 // 增计数模式中，CTR=CMPA时，翻转

#define AQ_PRU_NOACTION        0 // 当CTR=PRD时，无动作
#define AQ_PRU_CLR             1 // 当CTR=PRD时，置低
#define AQ_PRU_SET             2 // 当CTR=PRD时，置高
#define AQ_PRU_TGL             3 // 当CTR=PRD时，翻转

#define AQ_ZRO_NOACTION        0 // 当CTR=PRD时，无动作
#define AQ_ZRO_CLR             1 // 当CTR=PRD时，置低
#define AQ_ZRO_SET             2 // 当CTR=PRD时，置高
#define AQ_ZRO_TGL             3 // 当CTR=PRD时，无动作

#define DB_INMODE_SEL_REA_FEA  0 // DB模块输入源下降和上升边沿均选择PWMA
#define DB_INMODE_SEL_REB_FEA  1 // DB模块输入源上升沿选择PWMB，下降沿选择PWMA
#define DB_INMODE_SEL_REA_FEB  2 // DB模块输入源上升沿选择PWMA，下降沿选择PWMB
#define DB_INMODE_SEL_REB_FEB  3 // DB模块输入源上升沿和下降沿均选择PWMB

#define DB_OUTMODE_DISABLE     0 // 死区发生器禁止
#define DB_OUTMODE_RE_DISABLE  1 // 上升沿延迟禁止
#define DB_OUTMODE_FE_DISABLE  2 // 下降沿延迟禁止
#define DB_OUTMODE_BOTH_ENABLE 3 // 对上升沿和下降沿延迟完全使能

#define DB_POLSEL_AH           0 // 高有效模式
#define DB_POLSEL_ALC          1 // 低有效互补模式
#define DB_POLSEL_AHC          2 // 高有效互补模式
#define DB_POLSEL_AL           3 // 低有效模式

#define ET_INTPRD_DISABLE      0 // 禁用中断事件计数器
#define ET_INTPRD_1            1 // 在第一个事件发生时中断
#define ET_INTPRD_2            2 // 在第二个事件发生时中断
#define ET_INTPRD_3            3 // 在第三个事件发生时中断

#define ET_INTSEL_CTR_ZERO     1 // 在CTR=0时产生中断
#define ET_INTSEL_CTR_PRD      2 // 在CTR=PRD时产生中断
#define ET_INTSEL_CAU          4 // 在增计数模式中，CTR=CMPA时产生中断
#define ET_INTSEL_CAD          5 // 在减计数模式中，CTR=CMPA时产生中断
#define ET_INTSEL_CBU          6 // 在增计数模式中，CTR=CMPB时产生中断
#define ET_INTSEL_CBD          7 // 在减计数模式中，CTR=CMPB时产生中断

#define ET_INT_ENABLE          1 // 允许中断生成
#define ET_INT_DISABLE         0 // 禁止中断生成

#define ET_SOCPRD_DISABLE      0 // 禁用SOC事件计数器
#define ET_SOCPRD_1            1 // 在第一个事件上生成SOC脉冲
#define ET_SOCPRD_2            2 // 在第二个事件上生成SOC脉冲
#define ET_SOCPRD_3            3 // 在第三个事件上生成SOC脉冲

#define ET_SOCSEL_CTR_ZERO     1 // 在CTR=0时产生SOC脉冲
#define ET_SOCSEL_CTR_PRD      2 // 在CTR=PRD时产生SOC脉冲
#define ET_SOCSEL_CAU          4 // 在增计数模式中，CTR=CMPA时产生SOC脉冲
#define ET_SOCSEL_CAD          5 // 在减计数模式中，CTR=CMPA时产生SOC脉冲
#define ET_SOCSEL_CBU          6 // 在增计数模式中，CTR=CMPB时产生SOC脉冲
#define ET_SOCSEL_CBD          7 // 在减计数模式中，CTR=CMPB时产生SOC脉冲

#define ET_SOC_ENABLE          1 // 使能SOC脉冲信号
#define ET_SOC_DISABLE         0 // 禁止SOC脉冲信号

#define TZ_OSHT_ENABLE         1 // 单次故障保护使能
#define TZ_OSHT_DISABLE        0 // 单次故障保护禁止
#define TZ_CBC_ENABLE          1 // 周期循环故障保护使能
#define TZ_CBC_DISABLE         0 // 周期循环故障保护禁止

#define TZ_HIGH_R              0 // 高阻态
#define TZ_SET_HIGH            1 // 置高
#define TZ_SET_LOW             2 // 置低
#define TZ_NO_ACTION           3 // 无动作

#endif
