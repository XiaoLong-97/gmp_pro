/**
* @file          : OPA.c
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
#include "driver/inc/OPA.h"


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
  * @brief      OPA init.
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * OPAInit();
  * @endcode
  * @warning:
*/

void OPA1_Init()
{			
	ACCESS_EN();ADC->ADOP1CFG_b.EN   = OPA_ENABLE;		// 运放使能
	
	ACCESS_EN();ADC->ADOP1CFG_b.PRSHT = OPxPRS_RES_ENABLE;// 正相输入端电阻选择
	ACCESS_EN();ADC->ADOP1CFG_b.NRSHT = OPxNRS_RES_ENABLE;
	ACCESS_EN();ADC->ADOP1CFG_b.NS = OPA_FEEDBACK_LOOP_ENABLE;// 反相输入端反馈通路使能/禁止
	ACCESS_EN();ADC->ADOP1CFG_b.OE = OPA_OUTPUT_To_PIN_DISABLE;// 输出到端口使能/禁止	
	
	ACCESS_EN();ADC->ADOP1CFG_b.LP = 1;
	
	ACCESS_EN();ADC->ADOP1CFG_b.PS = OPA_PS_ENABLE;	// 
	ACCESS_EN();ADC->ADOP1CFG_b.CMS = 2;			//输入偏置选择
	ACCESS_EN();ADC->ADOP1CFG_b.BS = 1;				//输出偏置电压选择
	
	ACCESS_EN();ADC->ADOP1CFG_b.GS = OPxGS_8x;     // 增益倍数	
	
}
void OPA0_Init()
{		
	ACCESS_EN();ADC->ADOP0CFG_b.EN = OPA_ENABLE;// 运放使能	

	ACCESS_EN();ADC->ADOP0CFG_b.PRSHT = OPxPRS_RES_ENABLE;	// 正相输入端电阻选择
	ACCESS_EN();ADC->ADOP0CFG_b.NRSHT = OPxNRS_RES_ENABLE;			
	ACCESS_EN();ADC->ADOP0CFG_b.NS = OPA_FEEDBACK_LOOP_ENABLE;	// 反相输入端反馈通路使能/禁止
	ACCESS_EN();ADC->ADOP0CFG_b.OE = OPA_OUTPUT_To_PIN_ENABLE;	//OPA_OUTPUT_To_PIN_DISABLE;// 输出到端口使能/禁止

	ACCESS_EN();ADC->ADOP0CFG_b.LP = 1;
	
	ACCESS_EN();ADC->ADOP0CFG_b.PS = OPA_PS_ENABLE;	// 正向输入端偏置通路使能
	ACCESS_EN();ADC->ADOP0CFG_b.CMS = 2;//输入偏置选择
	ACCESS_EN();ADC->ADOP0CFG_b.BS = 1;//输出偏置电压选择

	ACCESS_EN();ADC->ADOP0CFG_b.GS = OPxGS_8x; // 增益倍数		
}


