/**
* @file          : clk.c
* @author        : SiLan Motor Lab 
* @date          : 01/17/2022
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
#include "driver/inc/clk.h"

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
  * @brief      Motor hardware device layer initalise.
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * Device_Init();
  * @endcode
  * @warning:
*/

void FlashRW_Config(uint8_t wt)
{
	uint32_t flash_tmp1;
	
	flash_tmp1 = ((0XA05FUL<<16)|(wt));
	FLASH->CFG  = flash_tmp1;
}

void SRAM1_Config(void)
{
	
//  ACCESS_EN();SYSCFG->SRAM1WRCTL = (0XA05FUL<<16)|0x00;			// 第5~10K加密
//	ACCESS_EN();SYSCFG->SRAM1WRCTL = (0XA05FUL<<16)|0x01;			// 第6~10K加密
//	ACCESS_EN();SYSCFG->SRAM1WRCTL = (0XA05FUL<<16)|0x03;			// 第7~10K加密
//	ACCESS_EN();SYSCFG->SRAM1WRCTL = (0XA05FUL<<16)|0x07;			// 第8~10K加密
//	ACCESS_EN();SYSCFG->SRAM1WRCTL = (0XA05FUL<<16)|0x0F;			// 第9~10K加密
//	ACCESS_EN();SYSCFG->SRAM1WRCTL = (0XA05FUL<<16)|0x1F;			// 第10K加密
	
	ACCESS_EN();SYSCFG->SRAM1WRCTL = (0XA05FUL<<16);
	ACCESS_EN();SYSCFG->SRAM1WRCTL = 0;
}

/********************************
OPENRCL128K选择
********************************/
void OPENRCL128K(void)
{
	CHIPCTRL->CHIPKEY =0x05fa659aul;
	CHIPCTRL->CLKCTL_b.RCL128KEN=1;
	while(CHIPCTRL->CLKCTL_b.RCL128KSTB == 0x00);
}


/********************************
CLOSERCL128K选择
********************************/
void CLOSERCL128K(void)
{
	CHIPCTRL->CHIPKEY =0x05fa659aul;
	CHIPCTRL->CLKCTL_b.RCL128KEN=0;
}
/********************************
SYSCLKSET
********************************/
void SYSCLKSET(uint8_t syssel)
{
	CHIPCTRL->CHIPKEY =0x05fa659aul;
	CHIPCTRL->CLKCFG1_b.SYSCLKSEL=syssel;
	while(CHIPCTRL->CLKCFG1_b.SYSCLKSEL!=syssel);
	while (CHIPCTRL->CLKCFG1_b.SYSCLKLOCK==0);
}

/********************************
OPENRCH选择
********************************/
void OPENRCH(void)
{
	CHIPCTRL->CHIPKEY =0x05fa659aul;
	CHIPCTRL->CHIPKEY =0x66559905ul;
	CHIPCTRL->CLKCTL_b.RCHEN=1;
	while (CHIPCTRL->CLKCTL_b.RCHSTB==0);
}

/********************************
CLOSERCH选择
********************************/
void CLOSERCH(void)
{
	CHIPCTRL->CHIPKEY =0x05fa659aul;
	CHIPCTRL->CHIPKEY =0x66559905ul;
	CHIPCTRL->CLKCTL_b.RCHEN=0;
	while(CHIPCTRL->CLKCTL_b.RCHEN != 0x00);
}

typedef enum
{
  SYSSEL_RCH = 0,
	SYSSEL_RCL = 3,
}SYSSEL_TypeDef;
#define RCH_48M 0
#define RCH_72M 1


void RCHSELECT(uint8_t rchsel)
{
	CHIPCTRL->CHIPKEY =0x05fa659aul;
	CHIPCTRL->CLKCTL_b.RCHSEL=rchsel;
	while(CHIPCTRL->CLKCTL_b.RCHSEL != rchsel);
}



uint8_t SYS_Config(uint8_t clk, uint8_t wt)
{
	uint8_t err;

	// 所有外设使能
	CHIP_KEY_EN();
	CHIPCTRL->AHB01CLKEN=0xffffffff;
	CHIP_KEY_EN();
	CHIPCTRL->AHB23CLKEN=0xffffffff;
	CHIP_KEY_EN();
	CHIPCTRL->APB01CLKEN=0xffffffff;
	CHIP_KEY_EN();
	CHIPCTRL->APB23CLKEN=0xffffffff;	
		
	FlashRW_Config(wt);
	
	CHIP_KEY_EN();
	CHIPCTRL->CLKCFG2_b.PDIV23 = 0;       // PCLK23 不分频
	CHIP_KEY_EN();
	CHIPCTRL->CLKCFG2_b.PDIV01 = 0;        // PCLK01 不分频
	CHIP_KEY_EN();
	CHIPCTRL->CLKCFG2_b.HDIV = 0;          // HCLK 不分频 
  
	switch(clk)
	{
		case 48:
				CHIP_KEY_EN();
				CHIPCTRL->CLKCTL_b.RCHDIV = 59;         // RCHDIV 选择48分频  3
				OPENRCL128K();
				SYSCLKSET(SYSSEL_RCL);
				CLOSERCH();
				RCHSELECT(RCH_48M);

				OPENRCH();
				SYSCLKSET(SYSSEL_RCH);
				break;

		case 72:
				CHIP_KEY_EN();
				CHIPCTRL->CLKCTL_b.RCHDIV = 89;         // RCHDIV 选择48分频  3
				OPENRCL128K();						//开启RCL 128K时钟
				SYSCLKSET(SYSSEL_RCL);		//设置系统时钟为RCL
				CLOSERCH();								//关闭RCH
				RCHSELECT(RCH_72M);				//设置RCH为72M
				OPENRCH();								//开启RCH
				SYSCLKSET(SYSSEL_RCH);		//设置系统时钟为RCH
			break;
	
		default:
			err = 1;
			break;
	}
		
	
	return err;
}
