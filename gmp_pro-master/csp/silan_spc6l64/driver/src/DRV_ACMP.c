/**
* @file          : ACMP.c
* @author        : SiLan Motor Lab 
* @date          : 02/14/2022
* @brief         : This file is for motor FOC function.
* @version       : Ver. 1.00

* H/W Platform   : SL_FOC FOR MOTOR CONCTROL

*------------------------------------------------------------------------------
 
* Compiler info  : Keil v5.20
 
*------------------------------------------------------------------------------
 
* Note: In this software, the function is used in motor control.

*-------------------------------------------------------------------------------

*  History:  

*              mm/dd/yyyy ver. x.y.z author

*              mm1/dd1/yyyy1 ver. x.y.z author1

*------------------------------------------------------------------------------
* @attention
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, SLMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* THIS SOURCE CODE IS PROTECTED BY A LICENSE.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.

* <h2><center>&copy; COPYRIGHT 2017 SLMicroelectronics</center></h2>
*******************************************************************************
*/

/******************************************************************************
* include file
******************************************************************************/
#include "driver/inc/ACMP.h"
/******************************************************************************
* global data for the project
******************************************************************************/


/******************************************************************************
* loacal define for the current file
******************************************************************************/
//#define ADC_SEL 17

/******************************************************************************
* loacal data for the current file
******************************************************************************/


/******************************************************************************
* loacal prototypes function 
******************************************************************************/


/******************************************************************************
* loacal function for the current file
******************************************************************************/
/**
  * @brief      CMP init.
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * CMP_Init();
  * @endcode
  * @warning:
*/

/*------6.OCP保护点设置------------------------------------------*/

#define CMP_NEG_VREF		10						// 比较器CMP寄存器的值


 void CMP0_Init()
{	
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0PS  = C0PS_INPUT_SEL_OPA_OUTPUT;	// 比较器P端信号选择运放输出
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0OPS = C0OPS_SEL_OP1O;				// 运放输出信号选择OPA1O
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0EN  = CMP_ENABLE;					// 比较器使能
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0VRRL = 1;							// 电阻分压档位低位
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0VRRH = 1;							// 电阻分压档位高位
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0RDS = CMP_NEG_VREF;				// 电阻分压值
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0VRHS = VRHS_SOURCE_SEL_VDD; 		// 内部电阻分压阶梯电源选择VDD
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0REFEN = REFEN_INTERN_REF_ENABLE; 	// 内部参考电压使能
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0HYSEN = HYSEN_WITHOUT_HYSTERESIS; // 关闭迟滞
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0NS = C0NS_NEG_INPUT_SEL_CVREF0;   // 负端输入选择CVREF0
//	 ACCESS_EN();	 ACMP->CP0CFG_b.C0FLG = 1;							// 比较器标志位清除 
//	 ACCESS_EN();	 ACMP->CP0CFG_b.C0GCEN = 1;							// 比较器门控关闭
	 ACCESS_EN();	 ACMP->CP0CFG_b.C0INTS = INTS_RE;					// 上升沿触发
	 ACCESS_EN();	 ACMP->CP0CFG_b.C0INTM = 0;             		
	 ACCESS_EN();	 ACMP->CP0CFG_b.C0DFILT = ((uint16_t)(72*1.5));   	// 数字滤波窗口设置2个周期，对应3us
	 ACCESS_EN();	 ACMP->CP0CFG |=(1<<19);				 			// 关闭32预分频
	 ACCESS_EN();	 ACMP->CP0CFG_b.C0CLKD = 0;   						// 不分频

 }
 void CMP1_Init()
{	
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1PS  = C1PS_INPUT_SEL_CP12P_PIN;		// 比较器P端信号选择CP12P引脚输入
//	 ACCESS_EN();	 ACMP->CP1CTL_b.C1OPS = C0OPS_SEL_OP0O;						// 运放输出信号选择OPA3O
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1EN  = CMP_ENABLE;									// 比较器使能
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1VRRL = 1;													// 电阻分压档位低位
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1VRRH = 0;													// 电阻分压档位高位
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1RDS = 10;//CMP_NEG_VREF;													// 电阻分压值 （0.42V 采样电阻0.1Ω 对应4A保护）
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1VRHS = VRHS_SOURCE_SEL_VDD; 			// 内部电阻分压阶梯电源选择VDD
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1REFEN = REFEN_INTERN_REF_ENABLE; 	// 内部参考电压使能
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1HYSEN = HYSEN_WITHOUT_HYSTERESIS; // 关闭迟滞
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1NS = C0NS_NEG_INPUT_SEL_CVREF0;   // 负端输入选择CVREF0
//	 ACCESS_EN();	 ACMP->CP1CTL_b.C1FLG = 1;												// 比较器标志位清除 
//	 ACCESS_EN();	 ACMP->CP1CTL_b.C1GCEN = 1;												// 比较器门控关闭
	 ACCESS_EN();	 ACMP->CP1CFG_b.C1INTS = INTS_RE;										// 上升沿触发
	 ACCESS_EN();	 ACMP->CP1CFG_b.C1INTM = 0;             						// 打开中断
	 ACCESS_EN();	 ACMP->CP1CFG_b.C1DFILT = 3;   											// 数字滤波窗口设置3个周期，对应1.33us
	 ACCESS_EN();	 ACMP->CP1CFG |= (1<<19);				 										// 关闭32预分频
	 ACCESS_EN();	 ACMP->CP1CFG_b.C1CLKD = 31;   											// 32分频

 }
 void CMP2_Init()
{	
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2PS  = C2PS_INPUT_SEL_OPA_OUTPUT;	// 比较器P端信号选择运放输出
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2OPS = C2OPS_SEL_OP0O;							// 运放输出信号选择OPA3O
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2EN  = CMP_ENABLE;									// 比较器使能
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2VRRL = 0;													// 电阻分压档位低位
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2VRRH = 1;													// 电阻分压档位高位
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2RDS = 0;							// 电阻分压值
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2VRHS = VRHS_SOURCE_SEL_VDD; 			// 内部电阻分压阶梯电源选择VDD
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2REFEN = REFEN_INTERN_REF_ENABLE; 	// 内部参考电压使能
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2HYSEN = HYSEN_WITHOUT_HYSTERESIS; // 关闭迟滞
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2NS = C0NS_NEG_INPUT_SEL_CVREF0;   // 负端输入选择CVREF0
//	 ACCESS_EN();	 ACMP->CP2CTL_b.C2FLG = 1;												// 比较器标志位清除 
//	 ACCESS_EN();	 ACMP->CP2CTL_b.C2GCEN = 1;												// 比较器门控关闭
	 ACCESS_EN();	 ACMP->CP2CFG_b.C2INTS = INTS_RE;										// 上升沿触发
	 ACCESS_EN();	 ACMP->CP2CFG_b.C2INTM = 0;             		
	 ACCESS_EN();	 ACMP->CP2CFG_b.C2DFILT = 3;   										// 数字滤波窗口设置2个周期，对应3us
	 ACCESS_EN();	 ACMP->CP2CFG|=(1<<19);				 											// 关闭32预分频
	 ACCESS_EN();	 ACMP->CP2CFG_b.C2CLKD = 31;   											// 32分频

 }
