#ifndef __TIMER_H__
#define __TIMER_H__

#include "driver/inc/GPIO.h"
#include "driver/inc/SLMCU.h"

#define TIM_ARPE_ENABLE       TIMER0->TIM_CR1_b.ARPE = 1; // 预装载使能
#define TIM_ARPE_DISABLE      TIMER0->TIM_CR1_b.ARPE = 0; // 预装载禁止

#define CC1S_OUTPUT           (0 << 0); // CC1S通道设为输出
#define CC1S_INPUT_IC1_To_TI1 (1 << 0); // CC1S通道设为输入并映射到TI1
#define CC1S_INPUT_IC1_To_TI2 (2 << 0); // CC1S通道设为输入并映射到TI2
#define CC1S_INPUT_IC1_To_TRC (3 << 0); // CC1S通道设为输入并映射到TRC
#define CC2S_OUTPUT           (0 << 8); // CC2S通道设为输出
#define CC2S_INPUT_IC2_To_TI2 (1 << 8); // CC2S通道设为输入并映射到TI2
#define CC2S_INPUT_IC2_To_TI1 (2 << 8); // CC2S通道设为输入并映射到TI1
#define CC2S_INPUT_IC2_To_TRC (3 << 8); // CC2S通道设为输入并映射到TRC
#define CC3S_OUTPUT           (0 << 0); // CC3S通道设为输出
#define CC3S_INPUT_IC3_To_TI3 (1 << 0); // CC3S通道设为输入并映射到TI3
#define CC3S_INPUT_IC3_To_TI4 (2 << 0); // CC3S通道设为输入并映射到TI4
#define CC3S_INPUT_IC3_To_TRC (3 << 0); // CC3S通道设为输入并映射到TRC
#define CC4S_OUTPUT           (0 << 8); // CC4S通道设为输出
#define CC4S_INPUT_IC4_To_TI4 (1 << 8); // CC4S通道设为输入并映射到TI4
#define CC4S_INPUT_IC4_To_TI3 (2 << 8); // CC4S通道设为输入并映射到TI3
#define CC4S_INPUT_IC4_To_TRC (3 << 8); // CC4S通道设为输入并映射到TRC

#define CC1E_ENABLE           1; // CC1通道使能
#define CC1E_DISABLE          0; // CC1通道禁止
#define CC1NE_ENABLE          1; // CC1N通道使能
#define CC1NE_DISABLE         0; // CC1N通道禁止
#define CC2E_ENABLE           1; // CC2通道使能
#define CC2E_DISABLE          0; // CC2通道禁止
#define CC2NE_ENABLE          1; // CC2N通道使能
#define CC2NE_DISABLE         0; // CC2N通道禁止
#define CC3E_ENABLE           1; // CC3通道使能
#define CC3E_DISABLE          0; // CC3通道禁止
#define CC3NE_ENABLE          1; // CC3N通道使能
#define CC3NE_DISABLE         0; // CC3N通道禁止
#define CC4E_ENABLE           1; // CC4通道使能
#define CC4E_DISABLE          0; // CC4通道禁止

#define OC1M_FREEZE           (0 << 4);  // 比较输出模式1选择：冻结
#define OC1M_MATCH_HIGH       (1 << 4);  // 比较输出模式1选择：匹配时设为有效电平
#define OC1M_MATCH_LOW        (2 << 4);  // 比较输出模式1选择：匹配时设为无效电平
#define OC1M_MATCH_TOGGLE     (3 << 4);  // 比较输出模式1选择：匹配时翻转电平
#define OC1M_FORCE_LOW        (4 << 4);  // 比较输出模式1选择：强制为无效电平
#define OC1M_FORCE_HIGH       (5 << 4);  // 比较输出模式1选择：强制为有效电平
#define OC1M_PWM_MODE1        (6 << 4);  // 比较输出模式1选择：PWM模式1
#define OC1M_PWM_MODE2        (7 << 4);  // 比较输出模式1选择：PWM模式2
#define OC2M_FREEZE           (0 << 12); // 比较输出模式2选择：冻结
#define OC2M_MATCH_HIGH       (1 << 12); // 比较输出模式2选择：匹配时设为有效电平
#define OC2M_MATCH_LOW        (2 << 12); // 比较输出模式2选择：匹配时设为无效电平
#define OC2M_MATCH_TOGGLE     (3 << 12); // 比较输出模式2选择：匹配时翻转电平
#define OC2M_FORCE_LOW        (4 << 12); // 比较输出模式2选择：强制为无效电平
#define OC2M_FORCE_HIGH       (5 << 12); // 比较输出模式2选择：强制为有效电平
#define OC2M_PWM_MODE1        (6 << 12); // 比较输出模式2选择：PWM模式1
#define OC2M_PWM_MODE2        (7 << 12); // 比较输出模式2选择：PWM模式2
#define OC3M_FREEZE           (0 << 4);  // 比较输出模式3选择：冻结
#define OC3M_MATCH_HIGH       (1 << 4);  // 比较输出模式3选择：匹配时设为有效电平
#define OC3M_MATCH_LOW        (2 << 4);  // 比较输出模式3选择：匹配时设为无效电平
#define OC3M_MATCH_TOGGLE     (3 << 4);  // 比较输出模式3选择：匹配时翻转电平
#define OC3M_FORCE_LOW        (4 << 4);  // 比较输出模式3选择：强制为无效电平
#define OC3M_FORCE_HIGH       (5 << 4);  // 比较输出模式3选择：强制为有效电平
#define OC3M_PWM_MODE1        (6 << 4);  // 比较输出模式3选择：PWM模式1
#define OC3M_PWM_MODE2        (7 << 4);  // 比较输出模式3选择：PWM模式2
#define OC4M_FREEZE           (0 << 12); // 比较输出模式4选择：冻结
#define OC4M_MATCH_HIGH       (1 << 12); // 比较输出模式4选择：匹配时设为有效电平
#define OC4M_MATCH_LOW        (2 << 12); // 比较输出模式4选择：匹配时设为无效电平
#define OC4M_MATCH_TOGGLE     (3 << 12); // 比较输出模式4选择：匹配时翻转电平
#define OC4M_FORCE_LOW        (4 << 12); // 比较输出模式4选择：强制为无效电平
#define OC4M_FORCE_HIGH       (5 << 12); // 比较输出模式4选择：强制为有效电平
#define OC4M_PWM_MODE1        (6 << 12); // 比较输出模式4选择：PWM模式1
#define OC4M_PWM_MODE2        (7 << 12); // 比较输出模式4选择：PWM模式2

#define OC1PE_PRELOAD_ENABLE  (1 << 3);  // 预装载使能
#define OC1PE_PRELOAD_DISABLE (0 << 3);  // 预装载禁止
#define OC2PE_PRELOAD_ENABLE  (1 << 11); // 预装载使能
#define OC2PE_PRELOAD_DISABLE (0 << 11); // 预装载禁止
#define OC3PE_PRELOAD_ENABLE  (1 << 3);  // 预装载使能
#define OC3PE_PRELOAD_DISABLE (0 << 3);  // 预装载禁止
#define OC4PE_PRELOAD_ENABLE  (1 << 11); // 预装载使能
#define OC4PE_PRELOAD_DISABLE (0 << 11); // 预装载禁止
/*****************************************************
                        仅用于输出功能极性配置
******************************************************/
#define CC1P_OUTPUT_HIGH         0; // 高电平有效
#define CC1P_OUTPUT_LOW          1; // 低电平有效
#define CC1NP_OUTPUT_HIGH        0; // 高电平有效
#define CC1NP_OUTPUT_LOW         1; // 低电平有效
#define CC2P_OUTPUT_HIGH         0; // 高电平有效
#define CC2P_OUTPUT_LOW          1; // 低电平有效
#define CC2NP_OUTPUT_HIGH        0; // 高电平有效
#define CC2NP_OUTPUT_LOW         1; // 低电平有效
#define CC3P_OUTPUT_HIGH         0; // 高电平有效
#define CC3P_OUTPUT_LOW          1; // 低电平有效
#define CC3NP_OUTPUT_HIGH        0; // 高电平有效
#define CC3NP_OUTPUT_LOW         1; // 低电平有效
#define CC4P_OUTPUT_HIGH         0; // 高电平有效
#define CC4P_OUTPUT_LOW          1; // 低电平有效

#define CC1IE_ENABLE             1; // 捕捉/比较1中断使能
#define CC1IE_DISABLE            0; // 捕捉/比较1中断禁止
#define CC2IE_ENABLE             1; // 捕捉/比较2中断使能
#define CC2IE_DISABLE            0; // 捕捉/比较2中断禁止
#define CC3IE_ENABLE             1; // 捕捉/比较3中断使能
#define CC3IE_DISABLE            0; // 捕捉/比较3中断禁止
#define CC4IE_ENABLE             1; // 捕捉/比较4中断使能
#define CC4IE_DISABLE            0; // 捕捉/比较4中断禁止
#define UIE_ENABLE               1; // 更新中断使能
#define UIE_DISABLE              0; // 更新中断禁止
#define COMIE_ENABLE             1; // COM中断使能
#define COMIE_DISABLE            0; // COM中断禁止
#define TIE_ENBALE               1; // 触发中断使能
#define TIE_DISABLE              0; // 触发中断禁止
#define BIE_ENABLE               1; // 刹车中断使能
#define BIE_DISABLE              0; // 刹车中断禁止

#define MOE_ENABLE               1; // 主输出使能
#define MOE_DISABLE              0; // 主输出禁止
#define AOE_AUTO_SET             1; // 自动输出使能
#define AOE_SW_SET               0; // 自动输出禁止

#define CNT_CLR_ENABLE           (1 << 17); // 计数器捕获清零使能
#define CNT_CLR_DISABLE          (0 << 17); // 计数器捕获清零禁止

#define CNT_CLR_SEL_CH1          (0 << 15); // 通道1捕获清零
#define CNT_CLR_SEL_CH2          (1 << 15); // 通道2捕获清零
#define CNT_CLR_SEL_CH3          (2 << 15); // 通道3捕获清零
#define CNT_CLR_SEL_CH4          (3 << 15); // 通道4捕获清零

#define CNT_ENABLE               TIMER0->TIM_CR1_b.CEN = 1; // 计数器使能
#define CNT_DISABLE              TIMER0->TIM_CR1_b.CEN = 0; // 计数器禁用

#define CMS_EDGE_ALIGN           0; // 边沿对齐模式
#define CMS_CENTER_MODE1         1; // 中央对齐模式1
#define CMS_CENTER_MODE2         2; // 中央对齐模式2
#define CMS_CENTER_MODE3         3; // 中央对齐模式3

#define DIR_UP                   0 // 增计数(配合边沿对齐模式)
#define DIR_DOWN                 1 // 减计数(配合边沿对齐模式)

#define BKE_BRAKE_ENABLE         1; // 刹车使能
#define BKE_BRAKE_DISABLE        0; // 刹车禁止
#define BKP_BRAKE_POL_HIGH       1; // 刹车输入高电平有效
#define BKP_BRAKE_POL_LOW        0; // 刹车输入低电平有效

#define OIS1_OC1_AFTER_DT_LOW    0; // 死区后置低
#define OIS1_OC1_AFTER_DT_HIGH   1; // 死区后置高
#define OIS1N_OC1N_AFTER_DT_LOW  0; // 死区后置低
#define OIS1N_OC1N_AFTER_DT_HIGH 1; // 死区后置高
#define OIS2_OC1_AFTER_DT_LOW    0; // 死区后置低
#define OIS2_OC1_AFTER_DT_HIGH   1; // 死区后置高
#define OIS2N_OC1N_AFTER_DT_LOW  0; // 死区后置低
#define OIS2N_OC1N_AFTER_DT_HIGH 1; // 死区后置高
#define OIS3_OC1_AFTER_DT_LOW    0; // 死区后置低
#define OIS3_OC1_AFTER_DT_HIGH   1; // 死区后置高
#define OIS3N_OC1N_AFTER_DT_LOW  0; // 死区后置低
#define OIS3N_OC1N_AFTER_DT_HIGH 1; // 死区后置高
#define OIS4_OC1_AFTER_DT_LOW    0; // 死区后置低
#define OIS4_OC1_AFTER_DT_HIGH   1; // 死区后置高

#define TS_ITR0                  0; // 触发源选择ITR0
#define TS_ITR1                  1; // 触发源选择ITR1
#define TS_ITR2                  2; // 触发源选择ITR2
#define TS_ITR3                  3; // 触发源选择ITR3
#define TS_TI1F_ED               4; // 触发源选择TI1F_ED
#define TS_TI1FP1                5; // 触发源选择TI1FP1
#define TS_TI2FP2                6; // 触发源选择TI2FP2
#define TS_ETRF                  7; // 触发源选择ETRF

#define SMS_SLAVE_MODE_DISABLE   0; // 从模式禁止
#define SMS_ENCODER_MODE1        1; // 从模式选择编码器模式1
#define SMS_ENCODER_MODE2        2; // 从模式选择编码器模式2
#define SMS_ENCODER_MODE3        3; // 从模式选择编码器模式3
#define SMS_RESET_MODE           4; // 从模式选择复位模式
#define SMS_GATE_CONTROL         5; // 从模式选择门控模式
#define SMS_TRIG_MODE            6; // 从模式选择触发模式
#define SMS_EXT_CLK_MODE1        7; // 从模式选择外部时钟模式

#define EGR_CNT_UPDATE           TIMER0->TIM_EGR_b.UG = 1; // 产生更新事件

extern void BT4_0_Init(void);
extern void BT4_1_Init(void);
extern void SysTickSet(uint32_t clk);
extern void TIM0_PWM_MEASURE(void);

#endif
