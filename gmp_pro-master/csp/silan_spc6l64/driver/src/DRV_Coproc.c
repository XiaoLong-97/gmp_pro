/**
* @file          : coproc.c
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
#include "driver/inc/coproc.h"

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
 * @brief      math function init.
 * @param[in]  void : None.
 * @param[out] void : None.
 * @retval     None
 * @pre //
 * @see //
 * @par        Example:
 * -This example shows how to call the function:
 * @code
 * Coproc_Init();
 * @endcode
 * @warning:
 */

void Coproc_Init(void)
{
    /*³Ë·¨*/
    COPROC->MULCTL = 1;
    COPROC->MULCTL = 0x80030000;
    COPROC->SHIFTNUM = GLOBAL_Q;
    /*³ý·¨*/
    COPROC->DIVCTL = 1;
    COPROC->DIVCTL = 0x00000100;
}
