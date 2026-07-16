/**
* @file          : adc.c
* @author        : SiLan Motor Lab 
* @date          : 02/12/2022
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
#include "driver/inc/adc.h"
/******************************************************************************
* global data for the project
******************************************************************************/
/******************************************************************************
* loacal define for the current file
******************************************************************************/

#define ADC_PA1         4  		// 	PA1,ADC4	 
#define ADC_PC1         6  		// 	PC1,ADC6
#define ADC_PB11        8  		// 	PB11,ADC8	
#define ADC_PB6       	11  	// 	PB6,ADC11	
#define ADC_OPA0       	0x13  	// 	OPA0,0x13

/******************************************************************************
* loacal data for the current file
******************************************************************************/
// 同时采样模式(SIMULENx = 1)
uint8_t ChSel[16]   = {ADC_PA1,ADC_PC1,ADC_PB11,ADC_PB6,ADC_OPA0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t ACQPS[16]   = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};
uint8_t TrigSel[16] = {5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
/******************************************************************************
* loacal prototypes function 
******************************************************************************/
/*触发源选择表
		00：软件触发
		01h：保留
		02h：BT41_EVENT
		03h：BT40_EVENT
		04h：保留
		05h：PWM0_SOCA
		06h：PWM0_SOCB
		07h：PWM1_SOCA
		08h：PWM1_SOCB
		09h：PWM2_SOCA
		0Ah：PWM2_SOCB
*/


/******************************************************************************
* loacal function for the current file
******************************************************************************/
/**
  * @brief      ADC init.
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * ADC_Init();
  * @endcode
  * @warning:
*/
void ADC_Init(void)	
{
	uint8_t i = 0;
/*************************基础配置*****************************/	
	ADC_RESET;										 	// ADC模块复位
	ADC_ENABLE;										 	// ADC模块使能

	ACCESS_EN();	ADC->ADCCTL1_b.PD = 0;      		// ADC断电，高电平有效	
	ACCESS_EN();	ADC->ADCCTL2_b.CLKDIV = ADC_CLKDIV_3;// 时钟 3分频后作为ADC模块时钟
	ACCESS_EN();	ADC->ADCCTL2_b.SCDLY  = 2;  		// 采样和开始转换之间的延时
	ACCESS_EN();	ADC->ADCCTL2_b.STRW   = 4;     	// 开始转换的脉冲宽度
	ADC_NONOVERLAP;										// 采样与转换不重叠
	ADC_REF_INTERNAL;									// 内部外部参考源选择，选择内部带隙参考源

/*************************CHANNEL SELECT*****************************/
	for(i=0; i<=15; i++)
	{
		ACCESS_EN();ADC->ADCCUCTL_b[i].ACQPS = ACQPS[i];//CCUx采样窗口选择(ACQPS+1)
		ACCESS_EN();ADC->ADCCUCTL_b[i].CHSEL = ChSel[i];//SOC通道选择
		ACCESS_EN();ADC->ADCCUCTL_b[i].TRIGSEL = TrigSel[i];//CCUx触发源选择		
	}
	
/*************************AD中断配置*****************************/
	ADC_INT_AT_EOC;										// 在ADC结果存入结果寄存器的前一个周期产生INT脉冲		   

	ACCESS_EN();	ADC->INTSEL1N2_b.INT1E = 1;     				// Enable ADCINT0
	ACCESS_EN();	ADC->INTSEL1N2_b.INT1CONT = 1;  				// Cont	
	ACCESS_EN();	ADC->INTSEL1N2_b.INT1SEL = 0; 					// EOC0 is selected as trigger source

/*************************AD使能*****************************/	
	ACCESS_EN();ADC->ADCCTL1_b.EN = 1;   /*Enable ADC*/  
}

