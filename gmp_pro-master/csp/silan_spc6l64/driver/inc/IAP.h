/**
* @file          : IAP.h
* @author        : MCU Lab
* @date          : 07/10/2017
* @brief         : This file is for IAP control function.
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

#ifndef _IAP_H_
#define _IAP_H_

#include "driver/inc/SLMCU.h"

#define FLASH_WRITE_ADDR_ST 0XEC00     // EC00-F000 59-60K
#define HMI_READ_ADDR_ST    0XF400     // F400 59-60K
#define SRAM1_WRITE_ADDR_ST 0x20001000 //

#define DATA_LEN            4                               // 数据帧长度(word),包含帧头帧尾
#define DATA_BYTE_LEN       (DATA_LEN * 4)                  // 数据帧长度(byte),包含帧头帧尾
#define SECTOR_DATA_NUM     (uint8_t)(1024 / DATA_BYTE_LEN) // 块内最大存储帧数
extern uint8_t WriteFlashWord(uint32_t addr, uint32_t data);
extern uint8_t EraseFlashSector(uint32_t addr);
extern uint32_t ReadFlashWord(uint32_t addr);
extern uint32_t FlashRead(unsigned long adr, unsigned long size, unsigned char *buff);
extern void Init_FLASH(void);
extern void READ_HMI(void);
extern uint32_t Add_Cur;

#endif
