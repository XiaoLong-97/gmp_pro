
#ifndef _FILE_SILAN_CONFIG_H_
#define _FILE_SILAN_CONFIG_H_

// System config
#define SYS_CLK        72     // MHz,系统时钟  (不建议修改)
#define PWM_FREQUENCY  18     // PWM开关频率(kHZ)	(可修改，但不建议超过30KHZ)
#define T0_FREQUENCY   1      // 外环执行频率(kHZ)(不建议修改)
#define UART0_BAUDRATE 115200 // 串口波特率UART0
#define UART1_BAUDRATE 115200 // 串口波特率UART1

/*---------------------时间相关中间值计算，不需要修改--------------------------------*/
#define PWM_PERIOD  (SYS_CLK * 500 / PWM_FREQUENCY) //
#define TIM6_PERIOD (SYS_CLK * 1000 / T0_FREQUENCY) //
#define TPWM        (0.001 / PWM_FREQUENCY)         // PWM周期值 (s)
#define TSP         (TPWM)                          // PWM周期值 (s)
#define TS0         (0.001 / T0_FREQUENCY)          // T0周期值  (s)

/*-----------------------标幺值,单位均为pu ，不需要修改------------------------------*/

#define UART0_IBRD (unsigned long)(SYS_CLK * 1000000 / (16 * UART0_BAUDRATE))
#define UART0_FBRD                                                                                                     \
    (unsigned long)((SYS_CLK * 1000000 % UART0_BAUDRATE >= (UART0_BAUDRATE >> 1))                                      \
                        ? (SYS_CLK * 1000000 / UART0_BAUDRATE - UART0_IBRD * 16 + 1)                                   \
                        : (SYS_CLK * 1000000 / UART0_BAUDRATE - UART0_IBRD * 16))

#define UART1_IBRD (unsigned long)(SYS_CLK * 1000000 / (16 * UART1_BAUDRATE))
#define UART1_FBRD                                                                                                     \
    (unsigned long)((SYS_CLK * 1000000 % UART1_BAUDRATE >= (UART1_BAUDRATE >> 1))                                      \
                        ? (SYS_CLK * 1000000 / UART1_BAUDRATE - UART1_IBRD * 16 + 1)                                   \
                        : (SYS_CLK * 1000000 / UART1_BAUDRATE - UART1_IBRD * 16))

//	ADC 转换结果
#define ADC_CHANNEL_PEAK_CURRENT ADC->ADCRESULT[0] // 峰值电流
#define ADC_CHANNEL_BEMF_U       ADC->ADCRESULT[1] // 反电势
#define ADC_CHANNEL_BEMF_V       ADC->ADCRESULT[2]
#define ADC_CHANNEL_BEMF_W       ADC->ADCRESULT[3]
#define ADC_CHANNEL_VDC          ADC->ADCRESULT[4] // 母线电压
#define ADC_CHANNEL_IDC          ADC->ADCRESULT[5] // 母线平均电流
#define ADC_CHANNEL_SPEED        ADC->ADCRESULT[6] // 外部调试开关
#define ADC_CHANNEL_NTC          ADC->ADCRESULT[7] // 温度检测
#define ADC_CHANNEL_BATNTC       ADC->ADCRESULT[8] // 2.5V偏置补偿

#endif //_FILE_SILAN_CONFIG_H_
