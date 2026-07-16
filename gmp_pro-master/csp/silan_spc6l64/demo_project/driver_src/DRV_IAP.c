/**
* @file          : FLASH.c
* @author        : MCU Lab 
* @date          : 07/10/2017
* @brief         : This file is for FLASH control function.
* @version       : Ver. 0.00

* H/W Platform       : SILAN THREE SHUNT MOTOR CONCTROL

 *------------------------------------------------------------------------------
 
 * Compiler info     :keil v5
 
 *------------------------------------------------------------------------------
 
Note: In this software, the function is used in motor control.

*-------------------------------------------------------------------------------

*  History:  

*              07/10/2017   ver0.0  MCU Lab 

*           

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

* <h2><center>&copy; COPYRIGHT 2015 SLMicroelectronics</center></h2>
*******************************************************************************/

#include "driver/inc/IAP.h"

/********************************************************************************************
  * @brief      WriteFlashWord.
  * @param[in]  u32 addr,u32 data 
  * @param[out] uint8_t : err  0：无故障   1：有故障
  * @retval     none
  * @pre  
  * @see  
  * @par        
  * -This example shows how to call the function:
  * @code
  * uint8_t WriteFlashWord(u32 addr,u32 data);
  * @endcode
  * @warning:   none
********************************************************************************************/
uint8_t WriteFlashWord(uint32_t addr,uint32_t data)
{
	uint8_t err = 0;
	__disable_irq(); 														
	FLASH->CCLR = 0x3E;						// FLASH操作使能清除
	FLASH->ICR = 0x7F;						// 清除所有故障标志位
	FLASH->IEN = 0x7F;						// 使能所有中断
	FLASH->ADDR = addr;						// 地址赋值
	FLASH->DATA = data;						// 数据赋值
	FLASH->CSET_b.PROGEN = 1;			// 字编程使能
	FLASH->FEED = 0x12345678;			// 写入操作启动KEY
	FLASH->FEED = 0x87654321;
	FLASH->CSET_b.OPSTART = 1;		// 操作启动
	while((FLASH->ISR & 0x01ul) == 0)	// 等待操作完成
	{
		if((FLASH->ISR & 0x7E) != 0) //错误判断
		{
			err = 1;
			break;
		}
	}
	FLASH->ICR = 0x7F;						// 清除所有故障标志位
	FLASH->CCLR_b.PROGEN = 1;			// 清除字编程使能位
	__enable_irq();	
	return err;
}										

/********************************************************************************************
  * @brief      EraseFlashSector.
  * @param[in]  u32 address 
  * @param[out] uint8_t : err  0：无故障   1：有故障
  * @retval     none
  * @pre  
  * @see  
  * @par        
  * -This example shows how to call the function:
  * @code
  * uint8_t EraseFlashSector(u32 addr);
  * @endcode
  * @warning:   none
********************************************************************************************/
uint8_t EraseFlashSector(uint32_t addr)
{
	uint8_t err = 0;														
	FLASH->CCLR = 0x3E;						// FLASH操作使能清除
	FLASH->ICR = 0x7F;						// 清除所有故障标志位
	FLASH->IEN = 0x7F;						// 使能所有中断
	FLASH->ADDR = addr;						// 地址赋值
	FLASH->CSET_b.PAGEEN = 1;			// 块擦除使能
	FLASH->FEED = 0x12345678;			// 写入操作启动KEY
	FLASH->FEED = 0x87654321;
	FLASH->CSET_b.OPSTART = 1;		// 操作启动
	while((FLASH->ISR & 0x01ul) == 0)	// 等待操作完成
	{
		if((FLASH->ISR & 0x7E) != 0) //错误判断
		{
			err = 1;
			break;
		}
	}
	FLASH->ICR = 0x7F;						// 清除所有故障标志位
	FLASH->CCLR_b.PAGEEN = 1;			// 清除字编程使能位
	return err;
}										



/********************************************************************************************
  * @brief      ReadFlashWord.
  * @param[in]  u32 address
  * @param[out] u32 data
  * @retval     none
  * @pre  
  * @see  
  * @par        
  * -This example shows how to call the function:
  * @code
  * u32 ReadFlashWord(u32 addr);
  * @endcode
  * @warning:   none   避免在块擦除之后马上读取数据，如有该需求，请联系原厂
********************************************************************************************/
uint32_t ReadFlashWord(uint32_t addr)
{
	uint32_t dat = 0;					
	uint32_t *ptr;
	ptr = (uint32_t *)addr;				// 指针指向地址
	dat = *ptr;							// 读取数据
	return dat;      					// 操作用时240ns
}


uint32_t	FlashRead(unsigned long adr, unsigned long size, unsigned char *buff)
{
	__disable_irq();
	FLASH->CCLR = 0xFF;//控制清零
	FLASH->IEN  = 0xFF;//中断使能
	FLASH->ICR  = 0xFF;//中断状态清除
	
	while(size)
	{
		FLASH->CSET_b.RDEN = 1;   //读取使能
		FLASH->ADDR = adr;
		FLASH->FEED = 0x12345678ul;
		FLASH->FEED = 0x87654321ul;//启动FLASH编程或块擦除操作
		FLASH->CSET_b.OPSTART = 1;// 操作开始
	   while (FLASH->ISR_b.COMPLETE == 0x00)
	  {
		if(FLASH->ISR_b.PROTECT == 1)
		{
			return(1);
		}
		if(FLASH->ISR_b.ERROR == 1)
		{
			return(1);
		}				
		if(FLASH->ISR_b.RCHOFF == 1)
		{
			return(1);
		}
		if(FLASH->ISR_b.DRDERR == 1)
		{
			return(1);
		}
	  }
	FLASH->ICR_b.COMPCLR = 1;//操作结束中断标志清除
	FLASH->CCLR_b.RDEN = 1;//读取使能清除
	*buff = FLASH->DATA;
	*(buff + 1) = (FLASH->DATA >> 8);
	*(buff + 2) = (FLASH->DATA >> 16);
	*(buff + 3) = (FLASH->DATA >> 24);
	buff += 0x04;
	adr += 0x04;
	size -= 0x04;
	}
	FLASH->IEN = 0x00; 
	__enable_irq();
	return (0); 	
}




	
