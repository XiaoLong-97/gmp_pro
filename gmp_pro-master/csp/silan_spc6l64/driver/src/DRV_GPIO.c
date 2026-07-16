/**
* @file          : GPIO.c
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
#include "driver/inc/GPIO.h"

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

/****************************************************************************
  * @brief      设置GPIO 引脚功能
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre //
  * @see //
  * @par        Example:
                    uint8_t AD : 数字/模拟功能选择位，等于ANALOGY或DIGITAL
                    PA_Type* GPIOx: 引脚组，等于PA,PB 或PC
                    uint8_t gpiopin：引脚组内数，等于0~15
                    uint8_t fun_num: 数字功能复用选择，具体参考引脚分配图的ALTx。使用模拟功能时,设置fun_num=0;
                    * -This example shows how to call the function:
                    Gpio_Af_Sel(DIGITAL,PB,14,2);					// PB14选择数字功能2作为PWM输出管脚PWM0A
                    Gpio_Af_Sel(ANALOGY,PA,1,0);					// PA1选择模拟功能作为ADC输入管脚
  * @code
  * Gpio_Af_Sel();
  * @endcode
  * @warning:
****************************************************************************/
void Gpio_Af_Sel(uint8_t AD, PA_Type *GPIOx, uint8_t gpiopin, uint8_t fun_num)
{
    uint32_t tmp;
    switch (gpiopin)
    {
    case 0x00:
        tmp = GPIOx->CFG[0] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[0] = tmp | fun_num | AD;
        break;

    case 0x01:
        tmp = GPIOx->CFG[1] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[1] = tmp | fun_num | AD;
        break;

    case 0x02:
        tmp = GPIOx->CFG[2] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[2] = tmp | fun_num | AD;
        break;

    case 0x03:
        tmp = GPIOx->CFG[3] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[3] = tmp | fun_num | AD;
        break;

    case 0x04:
        tmp = GPIOx->CFG[4] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[4] = tmp | fun_num | AD;
        break;

    case 0x05:
        tmp = GPIOx->CFG[5] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[5] = tmp | fun_num | AD;
        break;

    case 0x06:
        tmp = GPIOx->CFG[6] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[6] = tmp | fun_num | AD;
        break;

    case 0x07:
        tmp = GPIOx->CFG[7] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[7] = tmp | fun_num | AD;
        break;

    case 0x08:
        tmp = GPIOx->CFG[8] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[8] = tmp | fun_num | AD;
        break;

    case 0x09:
        tmp = GPIOx->CFG[9] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[9] = tmp | fun_num | AD;
        break;

    case 0x0a:
        tmp = GPIOx->CFG[10] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[10] = tmp | fun_num | AD;
        break;

    case 0x0b:
        tmp = GPIOx->CFG[11] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[11] = tmp | fun_num | AD;
        break;

    case 0x0c:
        tmp = GPIOx->CFG[12] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[12] = tmp | fun_num | AD;
        break;

    case 0x0d:
        tmp = GPIOx->CFG[13] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[13] = tmp | fun_num | AD;
        break;

    case 0x0e:
        tmp = GPIOx->CFG[14] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[14] = tmp | fun_num | AD;
        break;

    case 0x0f:
        tmp = GPIOx->CFG[15] &= 0xffffffe8ul;
        ACCESS_EN();
        GPIOx->CFG[15] = tmp | fun_num | AD;
        break;

    default:
        break;
    }
}
/**********************************************************************************

**********************************************************************************/
/****************************************************************************
  * @brief      设置 GPIO上/下拉选择.
                            Gpio_Pupd_Sel(uint8_t PUPD,PA_Type* GPIOx,uint8_t gpiopin)
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre //
  * @see //
  * @par        Example:
                    uint8_t PUPD: 0- 上下拉无效，1-下拉，2-上拉，3-repeater模式,根据引脚电平自动设置上下拉
                    PA_Type* GPIOx: 引脚组，等于PA,PB 或PC
                    uint8_t gpiopin：引脚组内数，等于0~15
                    * -This example shows how to call the function:
                    Gpio_Pupd_Sel(0,PC,13) ;		  			// PC13选择高阻输入
  * @code
  * Gpio_Af_Sel();
  * @endcode
  * @warning:
****************************************************************************/
void Gpio_Pupd_Sel(uint8_t PUPD, PA_Type *GPIOx, uint8_t gpiopin)
{
    uint32_t tmp;

    PUPD = PUPD << 6;

    switch (gpiopin)
    {
    case 0x00:
        tmp = GPIOx->CFG[0] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[0] = tmp | PUPD;
        break;

    case 0x01:
        tmp = GPIOx->CFG[1] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[1] = tmp | PUPD;
        break;

    case 0x02:
        tmp = GPIOx->CFG[2] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[2] = tmp | PUPD;
        break;

    case 0x03:
        tmp = GPIOx->CFG[3] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[3] = tmp | PUPD;
        break;

    case 0x04:
        tmp = GPIOx->CFG[4] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[4] = tmp | PUPD;
        break;

    case 0x05:
        tmp = GPIOx->CFG[5] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[5] = tmp | PUPD;
        break;

    case 0x06:
        tmp = GPIOx->CFG[6] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[6] = tmp | PUPD;
        break;

    case 0x07:
        tmp = GPIOx->CFG[7] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[7] = tmp | PUPD;
        break;

    case 0x08:
        tmp = GPIOx->CFG[8] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[8] = tmp | PUPD;
        break;

    case 0x09:
        tmp = GPIOx->CFG[9] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[9] = tmp | PUPD;
        break;

    case 0x0a:
        tmp = GPIOx->CFG[10] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[10] = tmp | PUPD;
        break;

    case 0x0b:
        tmp = GPIOx->CFG[11] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[11] = tmp | PUPD;
        break;

    case 0x0c:
        tmp = GPIOx->CFG[12] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[12] = tmp | PUPD;
        break;

    case 0x0d:
        tmp = GPIOx->CFG[13] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[13] = tmp | PUPD;
        break;

    case 0x0e:
        tmp = GPIOx->CFG[14] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[14] = tmp | PUPD;
        break;

    case 0x0f:
        tmp = GPIOx->CFG[15] &= 0xffffff3ful;
        ACCESS_EN();
        GPIOx->CFG[15] = tmp | PUPD;
        break;

    default:
        break;
    }
}
/****************************************************************************
  * @brief      设置 外部中断
                            EXINT_Config(uint8_t num, EXINT_PINSEL pin, EXINT_TYPE intype, uint8_t div, uint8_t psc)
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre //
  * @see //
  * @par        Example:

  * @code
  * Gpio_Af_Sel();
  * @endcode
  * @warning:
****************************************************************************/
void EXINT_Config(uint8_t num, EXINT_PINSEL pin, EXINT_TYPE intype, uint8_t div, uint8_t psc)
{
    EXINT->CFG_b[num].FILTA = 1; // 关闭模拟滤波
    EXINT->CFG_b[num].DIV = div; // 数字滤波时钟分频[0-5]
    EXINT->CFG_b[num].PSC = psc; // 数字滤波窗口[0-3]

    EXINT->CFG_b[num].PINSEL = pin; // 选择PA5

    EXINT->CFG[num] &= ~(0XF);
    EXINT->CFG[num] |= (intype);

    //	EXINT->CFG_b[num].INV = 1;//0,正向输入  1,反向输入
    //	EXINT->CFG_b[num].INTTYPE = 0;//0,中断配置为边沿中断  1,中断配置为电平中断
    //	EXINT->CFG_b[num].INTPOS = 1;//上升沿/高电平触发被允许
    //	EXINT->CFG_b[num].INTNEG = 1;//下降沿/低电平触发被允许

    EXINT->INTMASK &= ~(0X0F);
}

/********************************
Function Name: 	GPIO_TOGGLE
Input:	Px(PA,PB,PC,PD,PE,PF)
        n(0~15)
Output:
********************************/
void GPIO_TOGGLE(PA_Type *Px, uint8_t n)
{
    Px->OUTTGL = 1 << n;
}

/**
 * @brief      used as test.
 * @param[in]  void : None.
 * @param[out] void : None.
 * @retval     None
 * @pre //
 * @see //
 * @par        Example:
 * -This example shows how to call the function:
 * @code
 * Gpio_Init();
 * @endcode
 * @warning:
 */

void Gpio_Init(void)
{
    /*注意：模拟功能全部选择功能0*/

    /*********************ADC端口选择**********************/
    Gpio_Af_Sel(ANALOGY, PA, 1, 0);
    Gpio_Af_Sel(ANALOGY, PC, 1, 0);
    Gpio_Af_Sel(ANALOGY, PB, 11, 0);
    Gpio_Af_Sel(ANALOGY, PB, 6, 0);

    /*********************PWM端口选择*************************/
    //	Gpio_Af_Sel(DIGITAL,PA,10,1);//PWM2A
    //	Gpio_Af_Sel(DIGITAL,PA,9,5);//PWM2B

    Gpio_Af_Sel(DIGITAL, PA, 8, 2); // PWM1A
    Gpio_Af_Sel(DIGITAL, PB, 1, 2); // PWM1B

    /*********************运放端口选择**************************/

    Gpio_Af_Sel(ANALOGY, PB, 3, 0); // PB3选择模拟功能作为运放0正端输入管脚OPA0P
    Gpio_Af_Sel(ANALOGY, PB, 4, 0); // PB4选择模拟功能作为运放0负端输入管脚OPA0N
    Gpio_Af_Sel(ANALOGY, PB, 5, 0); // PB5选择模拟功能作为运放0负端输入管脚OPA0O

    /*********************比较器端口选择**************************/
    Gpio_Af_Sel(ANALOGY, PC, 0, 0);

    /*********************UART端口选择***************************/
    Gpio_Af_Sel(DIGITAL, PA, 2, 1); // UART0TX
    Gpio_Af_Sel(DIGITAL, PA, 3, 1); // UART0RX

    /******************通用输入输出端口选择***********************/

    Gpio_Af_Sel(DIGITAL, PA, 0, 0); //
    PA->OUTSET = (1 << 0);
    PA->OUTEN |= (1 << 0);

    Gpio_Af_Sel(DIGITAL, PA, 10, 0);
    PA->OUTSET = (1 << 10);
    PA->OUTEN |= (1 << 10);

    Gpio_Af_Sel(DIGITAL, PA, 9, 0);
    PA->OUTSET = (1 << 9);
    PA->OUTEN |= (1 << 9);

    Gpio_Af_Sel(DIGITAL, PA, 11, 0);
    PA->OUTSET = (1 << 11);
    PA->OUTEN |= (1 << 11);
    /****************************************************
    未使用引脚配置为推挽输出置低
    ****************************************************/
    //
    //	Gpio_Af_Sel(DIGITAL,PB,10,0); // PB10
    //	PB->OUTCLR = (1<<10);
    //	PB->OUTEN |= (1<<10);
    //
    //	Gpio_Af_Sel(DIGITAL,PB,5,0); // PB5
    //	PB->OUTCLR = (1<<5);
    //	PB->OUTEN |= (1<<5);

    /****************************************************
    打线未打出引脚配置为推挽输出置低
    ****************************************************/
    Gpio_Af_Sel(DIGITAL, PB, 12, 0); // PB12
    PB->OUTCLR = (1 << 12);
    PB->OUTEN |= (1 << 12);

    Gpio_Af_Sel(DIGITAL, PB, 13, 0); // PB13
    PB->OUTCLR = (1 << 13);
    PB->OUTEN |= (1 << 13);

    Gpio_Af_Sel(DIGITAL, PB, 14, 0); // PB14
    PB->OUTCLR = (1 << 14);
    PB->OUTEN |= (1 << 14);

    Gpio_Af_Sel(DIGITAL, PB, 15, 0); // PB15
    PB->OUTCLR = (1 << 15);
    PB->OUTEN |= (1 << 15);

    Gpio_Af_Sel(DIGITAL, PB, 9, 0); // PB9
    PB->OUTCLR = (1 << 9);
    PB->OUTEN |= (1 << 9);

    Gpio_Af_Sel(DIGITAL, PB, 2, 0); // PB2
    PB->OUTCLR = (1 << 2);
    PB->OUTEN |= (1 << 2);
}
