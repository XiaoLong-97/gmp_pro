/**
* @file          : pwm.c
* @author        : SiLan Motor Lab 
* @date          : 01/18/2022
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
#include "driver/inc/pwm.h"

/******************************************************************************
* global data for the project
******************************************************************************/


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
  * @brief      pwm init to generate Duty cycle and TZ overcurrent interruption
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * PWM_Init();
  * @endcode
  * @warning:
*/


#define PWM_DB 						(72*1.2)  																				// 死区时间(72对应1us)				(不建议修改)


void PWM_Init(uint32_t pwmpr)
{	
//STEP0: 初始化时关闭PWM
	// TZ5作故障源
	GPIO_OUT_HIC;
	STOP_ALL_PWM;

	PWM0->AQSFRC_b.RLDCSF = 3;
	PWM1->AQSFRC_b.RLDCSF = 3;
	PWM2->AQSFRC_b.RLDCSF = 3;
	
	__NOP();__NOP();__NOP();__NOP();
	
	PWM0->AQCSFRC = 9;//0101	
	PWM1->AQCSFRC = 9;//0101		
	PWM2->AQCSFRC = 9;//0101	 	
		
//STEP2: PWM0~PWM2 输出寄存器初始化
	// PWM0 INIT
	PWM0->TBPRD = pwmpr; // PWM Period 
	PWM0->TBPHS = 0; // Set Phase register to zero
	PWM0->TBCTL = 0;
	PWM0->TBCTL_b.CTRMODE = CTRMODE_UPDOWN; // 增减计数
	PWM0->TBCTL_b.PHSEN = PHASE_DISABLE; // Master module
	PWM0->TBCTL_b.PRDLD = PRD_SHADOWON; // TB_SHADOW
	PWM0->TBCTL_b.SYNCOSEL = SYNCOSEL_SYNC; // Sync down-stream module
	PWM0->CMPCTL_b.SHDWAMODE = SHADOWMODE_ON;	// CC_SHADOW
	PWM0->CMPCTL_b.SHDWBMODE = SHADOWMODE_ON;	// CC_SHADOW
	PWM0->CMPCTL_b.LOADAMODE = CMP_LOAD_ZERO;//0; // load on CTR=Zero
	PWM0->CMPCTL_b.LOADBMODE = CMP_LOAD_ZERO;//0; // load on CTR=Zero
	PWM0->AQCTLA_b.CAU = AQ_CAU_CLR; // high actions for EPWM0A CAU
	PWM0->AQCTLA_b.CAD = AQ_CAD_SET;	// low action for EPWM0A CBU
	PWM0->AQCTLB_b.CAU = AQ_CAU_CLR; // high actions for EPWM0A CAU
	PWM0->AQCTLB_b.CAD = AQ_CAD_SET;	// low action for EPWM0A CBU
	PWM0->AQCTLA_b.ZRO = AQ_ZRO_SET;
	PWM0->AQCTLB_b.ZRO = AQ_ZRO_SET;	
	PWM0->AQSFRC_b.RLDCSF = 3;//待确认影子寄存器更新时间
	PWM0->DBCTL_b.INMODE = DB_INMODE_SEL_REA_FEB;
	PWM0->DBCTL_b.OUTMODE = DB_OUTMODE_BOTH_ENABLE; // enable Dead-band module OUT_MODE
	PWM0->DBCTL_b.POLSEL = DB_POLSEL_AHC; // 
	PWM0->DBFED = PWM_DB; // FED = 64 TBCLKs
	PWM0->DBRED = PWM_DB; // RED = 64 TBCLKs

// PWM1 INIT
	PWM1->TBPRD = pwmpr; // Period = 4000 TBCLK counts
	PWM1->TBPHS = 0; // Set Phase register to zero
	PWM1->TBCTL = 0;
	PWM1->TBCTL_b.CTRMODE = CTRMODE_UPDOWN; // 增减计数
	PWM1->TBCTL_b.PHSEN = PHASE_DISABLE; // Master module
	PWM1->TBCTL_b.PRDLD = PRD_SHADOWON; // TB_SHADOW
	PWM1->TBCTL_b.SYNCOSEL = SYNCOSEL_SYNC; // Sync down-stream module
	PWM1->CMPCTL_b.SHDWAMODE = SHADOWMODE_ON;	// CC_SHADOW
	PWM1->CMPCTL_b.SHDWBMODE = SHADOWMODE_ON;	// CC_SHADOW
	PWM1->CMPCTL_b.LOADAMODE = CMP_LOAD_ZERO;//0; // load on CTR=Zero
	PWM1->CMPCTL_b.LOADBMODE = CMP_LOAD_ZERO;//0; // load on CTR=Zero
	PWM1->AQCTLA_b.CAU = AQ_CAU_CLR; // high actions for EPWM1A CAU
	PWM1->AQCTLA_b.CAD = AQ_CAD_SET;	// low action for EPWM1A CBU
	PWM1->AQCTLB_b.CAU = AQ_CAU_CLR; // high actions for EPWM1A CAU
	PWM1->AQCTLB_b.CAD = AQ_CAD_SET;	// low action for EPWM1A CBU
	PWM1->AQCTLA_b.ZRO = AQ_ZRO_SET;
	PWM1->AQCTLB_b.ZRO = AQ_ZRO_SET;	
	PWM1->AQSFRC_b.RLDCSF = 3;//待确认影子寄存器更新时间
	PWM1->DBCTL_b.INMODE = DB_INMODE_SEL_REA_FEB;
	PWM1->DBCTL_b.OUTMODE = DB_OUTMODE_BOTH_ENABLE; // enable Dead-band module OUT_MODE
	PWM1->DBCTL_b.POLSEL = DB_POLSEL_AHC; // 
	PWM1->DBFED = PWM_DB; // FED = 64 TBCLKs
	PWM1->DBRED = PWM_DB; // RED = 64 TBCLKs

// PWM2 INIT	
	PWM2->TBPRD = pwmpr; // Period = 4000 TBCLK counts
	PWM2->TBPHS = 0; // Set Phase register to zero
	PWM2->TBCTL = 0;
	PWM2->TBCTL_b.CTRMODE = CTRMODE_UPDOWN; // 增减计数
	PWM2->TBCTL_b.PHSEN = PHASE_DISABLE; // Master module
	PWM2->TBCTL_b.PRDLD = PRD_SHADOWON; // TB_SHADOW
	PWM2->TBCTL_b.SYNCOSEL = SYNCOSEL_SYNC; // Sync down-stream module
	PWM2->CMPCTL_b.SHDWAMODE = SHADOWMODE_ON;	// CC_SHADOW
	PWM2->CMPCTL_b.SHDWBMODE = SHADOWMODE_ON;	// CC_SHADOW
	PWM2->CMPCTL_b.LOADAMODE = CMP_LOAD_ZERO;//0; // load on CTR=Zero
	PWM2->CMPCTL_b.LOADBMODE = CMP_LOAD_ZERO;//0; // load on CTR=Zero
	PWM2->AQCTLA_b.CAU = AQ_CAU_CLR; // high actions for EPWM2A CAU
	PWM2->AQCTLA_b.CAD = AQ_CBU_SET;	// low action for EPWM2A CBU
	PWM2->AQCTLB_b.CAU = AQ_CAU_CLR; // high actions for EPWM2A CAU
	PWM2->AQCTLB_b.CAD = AQ_CBU_SET;	// low action for EPWM2A CBU
	PWM2->AQCTLA_b.ZRO = AQ_ZRO_SET;
	PWM2->AQCTLB_b.ZRO = AQ_ZRO_SET;	
	PWM2->AQSFRC_b.RLDCSF = 3;//待确认影子寄存器更新时间
	PWM2->DBCTL_b.INMODE = DB_INMODE_SEL_REA_FEB;
	PWM2->DBCTL_b.OUTMODE = DB_OUTMODE_BOTH_ENABLE; // enable Dead-band module OUT_MODE
	PWM2->DBCTL_b.POLSEL = DB_POLSEL_AHC; // 
	PWM2->DBFED = PWM_DB; // FED = 64 TBCLKs
	PWM2->DBRED = PWM_DB; // RED = 64 TBCLKs
	
//STEP3: PWM 触发ADC
	{
	PWM0->ETPS_b.INTPRD = ET_INTPRD_1;			// 1个事件产生中断
	PWM0->ETSEL_b.INTEN = ET_INT_ENABLE;		// 允许中断
	PWM0->ETSEL_b.INTSEL = ET_INTSEL_CTR_ZERO;	// 计数到0
	}
//STEP4: PWM 触发ADC
	{
	PWM0->ETPS_b.SOCAPRD 	= ET_SOCPRD_1;				// 
	PWM0->ETSEL_b.SOCAEN 	= ET_SOC_ENABLE;			// 使能PWM触发ADC
	PWM0->ETSEL_b.SOCASEL 	= ET_SOCSEL_CTR_PRD;  		// 定时器递增，计数器等于CMPA		
		
	PWM0->ETPS_b.SOCBPRD 	= ET_SOCPRD_1;				// 
	PWM0->ETSEL_b.SOCBEN 	= ET_SOC_ENABLE;			// 使能PWM触发ADC
	PWM0->ETSEL_b.SOCBSEL 	= ET_SOCSEL_CBU;  		// 定时器递增，计数器等于CMPB

	PWM1->ETPS_b.SOCBPRD 	= ET_SOCPRD_1;				// 
	PWM1->ETSEL_b.SOCBEN 	= ET_SOC_ENABLE;			// 使能PWM触发ADC
	PWM1->ETSEL_b.SOCBSEL 	= ET_SOCSEL_CBU;			// 定时器递增，计数器等于CMPB

	
	PWM2->ETPS_b.SOCBPRD 	= ET_SOCPRD_1;				// 
	PWM2->ETSEL_b.SOCBEN 	= ET_SOC_ENABLE;			// 使能PWM触发ADC
	PWM2->ETSEL_b.SOCBSEL 	= ET_SOCSEL_CBU;			// 定时器递增，计数器等于CMPB
	}
//STEP5: TZ中断
	if(1)
	{
		ACCESS_EN();	PWM0->TZCTL_b.TZA = TZ_SET_LOW;  //PWM置低 
		ACCESS_EN();	PWM0->TZCTL_b.TZB = TZ_SET_LOW;  //PWM置低 
		ACCESS_EN();	PWM1->TZCTL_b.TZA = TZ_SET_LOW;  //PWM置低 
		ACCESS_EN();	PWM1->TZCTL_b.TZB = TZ_SET_LOW;  //PWM置低 
		ACCESS_EN();	PWM2->TZCTL_b.TZA = TZ_SET_LOW;  //PWM置低 
		ACCESS_EN();	PWM2->TZCTL_b.TZB = TZ_SET_LOW;  //PWM置低 		
			
		ACCESS_EN();SYSCFG->ADCSOCOUTS_b.PWMTZ7SEL = 1;//选择CP1输出作为TZ信号源
		ACCESS_EN(); 	PWM0->TZSEL_b.OSHT7 = TZ_OSHT_ENABLE;// TZ7的单次故障使能
		ACCESS_EN();	PWM1->TZSEL_b.OSHT7 = TZ_OSHT_ENABLE;// TZ7的单次故障使能
		ACCESS_EN();	PWM2->TZSEL_b.OSHT7 = TZ_OSHT_ENABLE;// TZ7的单次故障使能
	

	}
//STEP6: PWM START
	GPIO_OUT_PWM
	START_ALL_PWM
	
//STEP7: 清除TZFlag				
	
	ACCESS_EN();	PWM0->TZCLR = 0x07;
	ACCESS_EN();	PWM1->TZCLR = 0x07;
	ACCESS_EN();	PWM2->TZCLR = 0x07;	
	
//清楚强制动作	
	PWM0->AQCSFRC = 0;
	PWM1->AQCSFRC = 0;
	PWM2->AQCSFRC = 0;
}

/**
  * @brief      pwm output set dowm  by force  
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * Motor_Stop();
  * @endcode
  * @warning:
*/
void Motor_Stop(void)
{ 
		__disable_irq();
	
		PWM0->AQCSFRC = 9;
		PWM1->AQCSFRC = 9;
		PWM2->AQCSFRC = 9;
	
	  __enable_irq();
}

/**
  * @brief      clear the error flag when TZ occurs to restart the motor
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * TZ_Clear();
  * @endcode
  * @warning:
*/
void TZ_Clear(void)
{
	__disable_irq();
//	ACCESS_EN();
//	SYSCFG->PWMCFG  &= ~(1<<23);	
//	ACCESS_EN();
//	SYSCFG->PWMCFG |= (1<<20);	
	ACCESS_EN();	PWM0->TZCLR = 0x07;
	ACCESS_EN();	PWM1->TZCLR = 0x07;
	ACCESS_EN();	PWM2->TZCLR = 0x07;
	
	__enable_irq();
}
/**
  * @brief      PWM比较器寄存器清零
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * Motor_Stop();
  * @endcode
  * @warning:
*/
void Pwm_Cmp_Clr(void)
{ 
	PWM0->CMPA = 0;
	PWM0->CMPB = 0;
	PWM1->CMPA = 0;
	PWM1->CMPB = 0;
	PWM2->CMPA = 0;
	PWM2->CMPB = 0;
}

void Motor_Brake(void)
{ 
		__disable_irq();
	
		PWM0->AQCSFRC = 5;//0101	
		PWM1->AQCSFRC = 5;//0101		
		PWM2->AQCSFRC = 5;//0101	
	
	__enable_irq();
}


