/**
* @file          : timer.c
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
#include "IQmathLib.h"
#include "driver/inc/clk.h"
#include "driver/inc/config.h"
#include "driver/inc/timer.h"

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
 * @brief      timer TIM6 init.
 * @param[in]  void : None.
 * @param[out] void : None.
 * @retval     None
 * @pre //
 * @see //
 * @par        Example:
 * -This example shows how to call the function:
 * @code
 * BT4_0_Init();
 * @endcode
 * @warning:
 */
void BT4_0_Init()
{
    BT4->BT4COM0 = TIM6_PERIOD;
    BT4->BT4CTL0_b.FREERUN = 1;
    BT4->BT4CTL0_b.CNT0INTE = 1;
    BT4->BT4PSC0 = 0;
    BT4->BT4CTL0_b.CNT0EN = 1;
}
void BT4_1_Init()
{
    BT4->BT4COM1 = TIM6_PERIOD >> 1;
    BT4->BT4CTL1_b.FREERUN = 1;
    BT4->BT4CTL1_b.CNT1INTE = 1;
    BT4->BT4PSC1 = 0;
    BT4->BT4CTL1_b.CNT1EN = 1;
}
