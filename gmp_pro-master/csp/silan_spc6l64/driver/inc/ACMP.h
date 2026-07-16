#ifndef __ACMP_H__
#define __ACMP_H__

#include "driver/inc/SLMCU.h"

/************************************************************
                         比较器定义
************************************************************/

#define C0PS_INPUT_SEL_OPA_OUTPUT 0 // 比较器0输入选择OPA输出结果
#define C0PS_INPUT_SEL_CP00P_PIN  1 // 比较器0输入选择CP00P管脚输入
#define C0PS_INPUT_SEL_CP01P_PIN  2 // 比较器0输入选择CP01P管脚输入
#define C0PS_INPUT_SEL_CP02P_PIN  3 // 比较器0输入选择CP02P管脚输入

#define C1PS_INPUT_SEL_OPA_OUTPUT 0 // 比较器1输入选择OPA输出结果
#define C1PS_INPUT_SEL_CP10P_PIN  1 // 比较器1输入选择CP10P管脚输入
#define C1PS_INPUT_SEL_CP11P_PIN  2 // 比较器1输入选择CP11P管脚输入
#define C1PS_INPUT_SEL_CP12P_PIN  3 // 比较器1输入选择CP12P管脚输入

#define C2PS_INPUT_SEL_OPA_OUTPUT 0 // 比较器2输入选择OPA输出结果
#define C2PS_INPUT_SEL_CP20P_PIN  1 // 比较器2输入选择CP20P管脚输入
#define C2PS_INPUT_SEL_CP21P_PIN  2 // 比较器2输入选择CP21P管脚输入
#define C2PS_INPUT_SEL_CP22P_PIN  3 // 比较器2输入选择CP22P管脚输入

#define C0OPS_SEL_OP0O            0 // 比较器0输入选择OPA0输出结果
#define C0OPS_SEL_OP1O            1 // 比较器0输入选择OPA1输出结果
#define C0OPS_SEL_OP2O            2 // 比较器0输入选择OPA1输出结果
#define C0OPS_SEL_OP3O            3 // 比较器0输入选择OPA3输出结果
#define C1OPS_SEL_OP0O            0 // 比较器1输入选择OPA0输出结果
#define C1OPS_SEL_OP1O            1 // 比较器1输入选择OPA1输出结果
#define C1OPS_SEL_OP2O            2 // 比较器1输入选择OPA1输出结果
#define C1OPS_SEL_OP3O            3 // 比较器1输入选择OPA3输出结果
#define C2OPS_SEL_OP0O            0 // 比较器2输入选择OPA0输出结果
#define C2OPS_SEL_OP1O            1 // 比较器2输入选择OPA1输出结果
#define C2OPS_SEL_OP2O            2 // 比较器2输入选择OPA1输出结果
#define C2OPS_SEL_OP3O            3 // 比较器2输入选择OPA3输出结果

#define CMP_ENABLE                1 // 比较器使能
#define CMP_DISABLE               0 // 比较器禁止

#define VRHS_SOURCE_SEL_VDD       0 // 内部电阻分压阶梯电源选择VDD
#define VRHS_SOURCE_SEL_VTEST     1 // 内部电阻分压阶梯电源选择VTEST  1.5V

#define REFEN_INTERN_REF_ENABLE   1 // 内部参考电压使能
#define REFEN_INTERN_REF_DISABLE  0 // 内部参考电压禁止

#define HYSEN_WITH_HYSTERESIS     1 // 有迟滞
#define HYSEN_WITHOUT_HYSTERESIS  0 // 无迟滞

#define HYSEN_8MV                 0 // 迟滞-8mV
#define HYSEN_16MV                1 // 迟滞-16mV
#define HYSEN_32MV                2 // 迟滞-32mV
#define HYSEN_110MV               3 // 迟滞-110mV

#define C0NS_NEG_INPUT_SEL_CVREF0 0 // 负端输入选择CVREF0
#define C0NS_NEG_INPUT_SEL_PIN    1 // 负端输入选择外部管脚输入
#define C0NS_NEG_INPUT_SEL_VSS    3 // 负端输入选择VSS

#define INTS_DISABLE              0 // 中断类型选择：禁止
#define INTS_FE                   1 // 中断类型选择下降沿
#define INTS_RE                   2 // 中断类型选择上升沿
#define INTS_FE_RE                3 // 中断类型选择上升沿和下降沿

#define INTM_INT_ENABLE           0 // 不屏蔽中断
#define INTM_INT_DISABLE          1 // 屏蔽中断

extern void CMP0_Init(void);
extern void CMP1_Init(void);
extern void CMP2_Init(void);

#endif
