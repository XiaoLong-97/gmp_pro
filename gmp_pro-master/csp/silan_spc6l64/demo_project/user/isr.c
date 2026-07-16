/**
* @file          : isr.c
* @author        : SiLan Motor Lab 
* @date          : 02/02/2018
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
#include <include.h>
#include "StateMachineFun.h"
/******************************************************************************
* global data for the project
******************************************************************************/
u32 tz_cnt = 0;

/******************************************************************************
* loacal define for the current file
******************************************************************************/


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
  * @brief     interrupt service program.
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * PWM0_IRQHandler();T0_IRQHandler();T6CONT0_IRQHandler();
  * @endcode
  * @warning:
*/
void HardFault_Handler(void)
{
	while (1)
  {
    MotorStop();// OUTPUT_DISABLE;	
  }
}

void NMI_Handler(void)
{
	
}


void SPI0_IRQHandler(void)
{
}

void I2C_IRQHandler(void)
{
}

void GPIO_3_IRQHandler(void)
{
}

void TIMER0_IRQHandler(void)
{
}

void DMA_IRQHandler(void)
{
}

void COPROC_IRQHandler(void)
{
}

void SYS_IRQHandler(void)
{
}

//void WWDT_IRQHandler(void)
//{
//}

//void IWDT_IRQHandler(void)
//{
//}

void GPIO0_IRQHandler(void)
{
}

void GPIO1_IRQHandler(void)
{
}

void GPIO2_IRQHandler(void)
{
}

void ADC0_IRQHandler(void)  // 电机停止 3.8us   电机运行 5.8~14us
{
	ADC->ADINTFLGCLR_b.INT1 = 1;	
	ADC->ADINTFLGCLR = 0XFF;	
	ADC->ADINTOVFCLR = 0XFF;	
	ADC->ADCCUOVFCLR1 =0xFF;
//	
	
	Motor.Modulate.PhaseVoltU = ADC_CHANNEL_BEMF_U;   
	Motor.Modulate.PhaseVoltV = ADC_CHANNEL_BEMF_V;
	Motor.Modulate.PhaseVoltW = ADC_CHANNEL_BEMF_W;
	Motor.Modulate.BusVolt 	  = ADC_CHANNEL_VDC;
	Motor.Modulate.BemfAdcFlag =  Read_ADC_Out(&Motor.Modulate);//Cmp1_Read_Out();// 
	Motor.Modulate.CompCurrentOut = Motor.Modulate.BemfAdcFlag;   //Motor.Modulate.BemfAdcFlag
	
	/*---------------------AD偏置计算 START---------------------------------*/	
	if(Motor.OffsetFlag)//AD偏置计算标志位，初始为1，偏置计算完成清0，退出，进入FOC主程序
	{
		OffsetCount ++;
		if(OffsetCount >= 100 && OffsetCount <= 357)//留有电压建立时间
		{
			OffsetAD();//AD偏置计算程序(control.c)
		}
		else if(OffsetCount > 357)//AD偏置计算相关标志位和计数器清0
		{
			Motor.OffsetFlag = 0;
			OffsetCount = 0;
			AdcCount = 0; 
		}
	}
/*---------------------AD偏置计算 END---------------------------------*/	
	else         // 电机控制
	{
    	BLDC_MAIN_IRQ(&Motor);	       			// 电机控制主函数
	}	

	Time_state.TimeTike_PWM++;
	if(Time_state.TimeTike_PWM>=PWM_FREQUENCY)  //  1ms 到了
	{
			 Time_state.TimeTike_PWM = 0;
			 Time_state.Time_Bit.TIME_1MS_Flag = YES;
  }
}

void ADC1_IRQHandler(void)
{
	
}

void ADC2_IRQHandler(void)
{
}

void ADC_IRQHandler(void)
{
  //SD_ON;
//  LED4_ON;
//  ADC->ADCINTFLGCLR = 0XFF;	
//  ADC->ADCINTOVFCLR = 0XFF;	
//	ADC->ADCSOCOVFCLR1 =0xFF;
}

u32 BT01count = 0;
//进T0中断同时读T0/T1两个标志位，如果T1标志位为1，出T0中断前把T1标志位置1是不是就可以了
void BT00_IRQHandler()    // 计时溢出中断
{
 /***************INTF0*******************/	
     if(BT0->BT0INTF_b.INTF0)
	 {	
	    BT0->BT0INTFC_b.INTFC0 = 1;

	 }	
	 if(BT0->BT0INTF_b.FINTF0) //下降沿
	 {
		 BT0->BT0INTFC_b.FINTFC0 = 1;

	 }		 
	 if(BT0->BT0INTF_b.RINTF0) //上降沿
	 {
		 BT0->BT0INTFC_b.RINTFC0 = 1;
	 }
	
	
	  if(Motor.Status == MOTOR_RUN )
             Motor.Modulate.CommutationT0OverCnt ++; 
	else
		     Motor.Modulate.CommutationT0OverCnt = 0;
	 
}

void BT01_IRQHandler()  // 延时换相中断  占用资源 5us
{
 /***************INTF1 溢出中断*******************/	
	 if(BT0->BT0INTF_b.INTF1)
	 {	
      BT0->BT0INTFC_b.INTFC1 = 1; 
	 }	
	 if(BT0->BT0INTF_b.FINTF1) //下降沿
	 {
		 BT0->BT0INTFC_b.FINTFC1 = 1;
	 }		 
	 if(BT0->BT0INTF_b.RINTF1) //上降沿
	 {
		 BT0->BT0INTFC_b.RINTFC1 = 1;
	 }			 

	BLDC_BT_IRQ(&Motor);
	
}
// 延时换相中断  占用资源 7.6us
void ACMP1_IRQHandler(void)
{	
	//LED2_ON;
	//PA->OUTTGL = 1<<5;
	ACCESS_EN;ACMP->CP1CFG_b.C1FLG = 1; // 清除中断标志位
	CMP1_IE_DISABLE();
	BLDC_ACMP_IRQ(&Motor);
	//LED2_OFF;	
}


void GPIO_4_IRQHandler(void)
{
}

void PWM4_IRQHandler(void)
{
}

void GPIO_5_IRQHandler(void)
{
}

void PWM_COMB_IRQHandler(void)
{
	tz_cnt ++;
	
}


void SysTick_Handler(void)
{
	uart_cnt++;
}

void PWM0_IRQHandler(void)
{	
	PWM0->ETCLR_b.INT = 1;	// 清中断标志	
}




