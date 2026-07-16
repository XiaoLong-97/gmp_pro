#ifndef __OPA_H__
#define __OPA_H__

#include "driver/inc/SLMCU.h"

extern void OPA0_Init(void);
extern void OPA1_Init(void);

#define OPA_ENABLE                1; // 运放使能
#define OPA_DISABLE               0; // 运放禁止
#define OPA_PS_ENABLE             1; // 内部偏置打开
#define OPA_PS_DISABLE            0; // 内部偏置关闭
#define OPA_FEEDBACK_LOOP_ENABLE  1; // 运放反馈环路使能
#define OPA_FEEDBACK_LOOP_DISABLE 0; // 运放反馈环路禁止
#define OPA_OUTPUT_To_PIN_ENABLE  1; // 运放结果输出到管脚使能
#define OPA_OUTPUT_To_PIN_DISABLE 0; // 运放结果输出到管脚禁止

#define OPxGS_1x                  0; // OPA1/2/3放大倍数设为1
#define OPxGS_2x                  1; // OPA1/2/3放大倍数设为2
#define OPxGS_4x                  2; // OPA1/2/3放大倍数设为3
#define OPxGS_6x                  3; // OPA1/2/3放大倍数设为4
#define OPxGS_8x                  4; // OPA1/2/3放大倍数设为5
#define OPxGS_12x                 5; // OPA1/2/3放大倍数设为6
#define OPxGS_16x                 6; // OPA1/2/3放大倍数设为8
#define OPxGS_20x                 7; // OPA1/2/3放大倍数设为12
#define OPxPRS_RES_ENABLE         0; // OPA1/2/3正相端电阻使能
#define OPxPRS_RES_SHORT          1; // OPA1/2/3正相端电阻短接
#define OPxNRS_RES_ENABLE         0; // OPA1/2/3反相端电阻使能
#define OPxNRS_RES_SHORT          1; // OPA1/2/3反相端电阻短接

#endif
