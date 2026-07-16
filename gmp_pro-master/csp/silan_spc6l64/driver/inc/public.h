#ifndef __PUBLIC_H__
#define __PUBLIC_H__

#include "driver/inc/SLMCU.h"
#include "driver/inc/IAP.h"

// #define		ACCESS_EN  						            SYSCFG->ACCESSEN = 0x05FA659A;
// #define  	__CHIPCTRL_CHIP_KEY     					CHIPCTRL->CHIPKEY = 0x05FA659A;

#define pllmul_24  0
#define pllmul_28  1
#define pllmul_32  2
#define pllmul_36  3

#define plldiv_(x) (x - 1)

typedef enum
{
    FALSE = 0,
    TRUE = 1,
} Bool_e;

#define INPUT   0
#define OUTPUT  1

#define LOW     0
#define HIGH    1

#define DIGITAL (0 << 4)
#define ANALOGY (1 << 4)

#define RCH_48M 0
#define RCH_72M 1

typedef enum
{
    RCL32K = 0,
    RCH = 1,
    LFCLK = 7,
    SYSCLK = 8,
    SCLK = 9,
    FCLK = 10,
    DCLK = 11,
    CM0_HCLK = 12,
    PCLK01 = 13,
    PCLK23 = 14,
    IAPCLK = 15,
} XCLKSEL_TypeDef;

typedef enum
{
    SYSSEL_RCH = 0,
    SYSSEL_RCL = 3,
} SYSSEL_TypeDef;

typedef enum
{
    XCLKDIV_1 = 0,
    XCLKDIV_2 = 1,
    XCLKDIV_4 = 2,
    XCLKDIV_8 = 3,
    XCLKDIV_16 = 4,
    XCLKDIV_32 = 5,
    XCLKDIV_64 = 6,
    XCLKDIV_128 = 7,
} XCLKDIV_TypeDef;

/** PA0 gpio alternat function selection */
typedef enum
{
    PA_CFG0_FUNC_GPIO = 0,
    PA_CFG0_FUNC_SPI0SCK = 4,
} PA_CFG0_FUNC_Enum;

/** PA1 gpio alternat function selection */
typedef enum
{
    PA_CFG1_FUNC_GPIO = 0,
    PA_CFG1_FUNC_SPI0SCK = 3,
} PA_CFG1_FUNC_Enum;

/** PA2 gpio alternat function selection */
typedef enum
{
    PA_CFG2_FUNC_GPIO = 0,
    PA_CFG2_FUNC_UART0TX = 1,
    PA_CFG2_FUNC_UART1TX = 2,
    PA_CFG2_FUNC_SPI0MOSI = 4,
} PA_CFG2_FUNC_Enum;

/** PA3 gpio alternat function selection */
typedef enum
{
    PA_CFG3_FUNC_GPIO = 0,
    PA_CFG3_FUNC_UART0RX = 1,
    PA_CFG3_FUNC_UART1RX = 2,
    PA_CFG3_FUNC_SPI0MISO = 4,
    PA_CFG3_FUNC_CMP0OUT = 6,
} PA_CFG3_FUNC_Enum;

/** PA4 gpio alternat function selection */
typedef enum
{
    PA_CFG4_FUNC_GPIO = 0,
    PA_CFG4_FUNC_UART1TX = 1,
    PA_CFG4_FUNC_CMP1OUT = 2,
    PA_CFG4_FUNC_BT10OUT = 3,
    PA_CFG4_FUNC_SPI0MOSI = 4,
    PA_CFG4_FUNC_SPI0NSS = 5,
    PA_CFG4_FUNC_ADCSAMPLE = 7,
} PA_CFG4_FUNC_Enum;

/** PA5 gpio alternat function selection */
typedef enum
{
    PA_CFG5_FUNC_GPIO = 0,
    PA_CFG5_FUNC_UART1RX = 1,
    PA_CFG5_FUNC_CMP2OUT = 3,
    PA_CFG5_FUNC_BT10OUT = 4,
    PA_CFG5_FUNC_SPI0SCK = 5,
} PA_CFG5_FUNC_Enum;

/** PA6 gpio alternat function selection */
typedef enum
{
    PA_CFG6_FUNC_GPIO = 0,
    PA_CFG6_FUNC_PWMTZ0 = 1,
    PA_CFG6_FUNC_PWMTZ2 = 2,
    PA_CFG6_FUNC_PWM0B = 3,
    PA_CFG6_FUNC_BT00OUT = 4,
    PA_CFG6_FUNC_SPI0MISO = 5,
    PA_CFG6_FUNC_CMP0OUT = 6,
} PA_CFG6_FUNC_Enum;

/** PA7 gpio alternat function selection */
typedef enum
{
    PA_CFG7_FUNC_GPIO = 0,
    PA_CFG7_FUNC_PWM0B = 1,
    PA_CFG7_FUNC_BT00OUT = 2,
    PA_CFG7_FUNC_PWM0A = 3,
    PA_CFG7_FUNC_BT10OUT = 4,
    PA_CFG7_FUNC_SPI0MOSI = 5,
} PA_CFG7_FUNC_Enum;

/** PA8 gpio alternat function selection */
typedef enum
{
    PA_CFG8_FUNC_GPIO = 0,
    PA_CFG8_FUNC_PWM0A = 1,
    PA_CFG8_FUNC_PWM1A = 2,
    PA_CFG8_FUNC_BT00OUT = 4,
    PA_CFG8_FUNC_PWM0B = 5,
    PA_CFG8_FUNC_SPI0NSS = 6,
} PA_CFG8_FUNC_Enum;

/** PA9 gpio alternat function selection */
typedef enum
{
    PA_CFG9_FUNC_GPIO = 0,
    PA_CFG9_FUNC_PWM1A = 1,
    PA_CFG9_FUNC_PWM2A = 2,
    PA_CFG9_FUNC_UART0TX = 3,
    PA_CFG9_FUNC_BT00OUT = 4,
    PA_CFG9_FUNC_PWM2B = 5,
    PA_CFG9_FUNC_SPI0MISO = 6,
} PA_CFG9_FUNC_Enum;

/** PA10 gpio alternat function selection */
typedef enum
{
    PA_CFG10_FUNC_GPIO = 0,
    PA_CFG10_FUNC_PWM2A = 1,
    PA_CFG10_FUNC_PWM0B = 2,
    PA_CFG10_FUNC_UART0RX = 3,
    PA_CFG10_FUNC_PWM1B = 4,
    PA_CFG10_FUNC_SPI0MOSI = 5,
    PA_CFG10_FUNC_PWMTZ1 = 7,
} PA_CFG10_FUNC_Enum;

/** PA11 gpio alternat function selection */
typedef enum
{
    PA_CFG11_FUNC_GPIO = 0,
    PA_CFG11_FUNC_PWM2A = 1,
    PA_CFG11_FUNC_PWM1B = 2,
    PA_CFG11_FUNC_PWMTZ0 = 3,
    PA_CFG11_FUNC_SPI0NSS = 5,
    PA_CFG11_FUNC_BT10OUT = 6,
    PA_CFG11_FUNC_SPI0MISO = 7,
} PA_CFG11_FUNC_Enum;

/** PA12 gpio alternat function selection */
typedef enum
{
    PA_CFG12_FUNC_GPIO = 0,
    PA_CFG12_FUNC_PWM2B = 1,
    PA_CFG12_FUNC_BT10OUT = 2,
    PA_CFG12_FUNC_SPI0SCK = 5,
    PA_CFG12_FUNC_UART0TX = 6,
    PA_CFG12_FUNC_SPI0MOSI = 7,
} PA_CFG12_FUNC_Enum;

/** PA13 gpio alternat function selection */
typedef enum
{
    PA_CFG13_FUNC_GPIO = 0,
    PA_CFG13_FUNC_UART0RX = 3,
    PA_CFG13_FUNC_UART1RX = 4,
    PA_CFG13_FUNC_UART1TX = 5,
} PA_CFG13_FUNC_Enum;

/** PA14 gpio alternat function selection */
typedef enum
{
    PA_CFG14_FUNC_GPIO = 0,
    PA_CFG14_FUNC_UART0TX = 3,
    PA_CFG14_FUNC_UART1TX = 4,
    PA_CFG14_FUNC_UART1RX = 5,
} PA_CFG14_FUNC_Enum;

/** PA15 gpio alternat function selection */
typedef enum
{
    PA_CFG15_FUNC_GPIO = 0,
    PA_CFG15_FUNC_SPI0NSS = 2,
    PA_CFG15_FUNC_UART0RX = 3,
    PA_CFG15_FUNC_UART1RX = 4,
    PA_CFG15_FUNC_EXTSYNI = 5,
    PA_CFG15_FUNC_UART0TX = 6,
} PA_CFG15_FUNC_Enum;

/** PB0 gpio alternat function selection */
typedef enum
{
    PB_CFG0_FUNC_GPIO = 0,
    PB_CFG0_FUNC_PWM0A = 2,
    PB_CFG0_FUNC_PWM1B = 3,
    PB_CFG0_FUNC_BT10OUT = 4,
    PB_CFG0_FUNC_SPI0NSS = 5,
    PB_CFG0_FUNC_CMP2OUT = 6,
} PB_CFG0_FUNC_Enum;

/** PB1 gpio alternat function selection */
typedef enum
{
    PB_CFG1_FUNC_GPIO = 0,
    PB_CFG1_FUNC_PWM2B = 1,
    PB_CFG1_FUNC_PWM1B = 2,
    PB_CFG1_FUNC_BT00OUT = 4,
    PB_CFG1_FUNC_BT10OUT = 5,
    PB_CFG1_FUNC_CMP1OUT = 6,
} PB_CFG1_FUNC_Enum;

/** PB2 gpio alternat function selection */
typedef enum
{
    PB_CFG2_FUNC_GPIO = 0,
    PB_CFG2_FUNC_BT10OUT = 2,
    PB_CFG2_FUNC_XCLKOUT = 5,
    PB_CFG2_FUNC_SPI0MISO = 6,
} PB_CFG2_FUNC_Enum;

/** PB3 gpio alternat function selection */
typedef enum
{
    PB_CFG3_FUNC_GPIO = 0,
    PB_CFG3_FUNC_PWMTZ1 = 1,
    PB_CFG3_FUNC_SPI0SCK = 2,
    PB_CFG3_FUNC_BT10OUT = 3,
    PB_CFG3_FUNC_XCLKOUT = 4,
    PB_CFG3_FUNC_PWM1A = 5,
    PB_CFG3_FUNC_ADCEOC = 7,
} PB_CFG3_FUNC_Enum;

/** PB4 gpio alternat function selection */
typedef enum
{
    PB_CFG4_FUNC_GPIO = 0,
    PB_CFG4_FUNC_PWM1B = 1,
    PB_CFG4_FUNC_SPI0MISO = 2,
    PB_CFG4_FUNC_PWMTZ1 = 3,
    PB_CFG4_FUNC_BT00OUT = 4,
    PB_CFG4_FUNC_UART0RX = 5,
    PB_CFG4_FUNC_ADCSOC = 6,
} PB_CFG4_FUNC_Enum;

/** PB5 gpio alternat function selection */
typedef enum
{
    PB_CFG5_FUNC_GPIO = 0,
    PB_CFG5_FUNC_PWM1A = 1,
    PB_CFG5_FUNC_SPI0MOSI = 2,
    PB_CFG5_FUNC_UART0TX = 3,
    PB_CFG5_FUNC_BT00OUT = 4,
    PB_CFG5_FUNC_PWMTZ0 = 5,
} PB_CFG5_FUNC_Enum;

/** PB6 gpio alternat function selection */
typedef enum
{
    PB_CFG6_FUNC_GPIO = 0,
    PB_CFG6_FUNC_PWM2B = 1,
    PB_CFG6_FUNC_PWM2A = 2,
    PB_CFG6_FUNC_UART1TX = 3,
    PB_CFG6_FUNC_BT10OUT = 4,
    PB_CFG6_FUNC_SPI0MOSI = 5,
    PB_CFG6_FUNC_SPI0MISO = 6,
} PB_CFG6_FUNC_Enum;

/** PB7 gpio alternat function selection */
typedef enum
{
    PB_CFG7_FUNC_GPIO = 0,
    PB_CFG7_FUNC_PWM2A = 1,
    PB_CFG7_FUNC_UART1RX = 3,
    PB_CFG7_FUNC_CMP2OUT = 5,
    PB_CFG7_FUNC_SPI0MOSI = 6,
} PB_CFG7_FUNC_Enum;

/** PB8 gpio alternat function selection */
typedef enum
{
    PB_CFG8_FUNC_GPIO = 0,
    PB_CFG8_FUNC_SPI0SCK = 2,
    PB_CFG8_FUNC_EXTSYNI = 4,
    PB_CFG8_FUNC_CMP1OUT = 5,
    PB_CFG8_FUNC_BT00OUT = 6,
} PB_CFG8_FUNC_Enum;

/** PB9 gpio alternat function selection */
typedef enum
{
    PB_CFG9_FUNC_GPIO = 0,
    PB_CFG9_FUNC_PWM0A = 1,
    PB_CFG9_FUNC_PWMTZ2 = 2,
    PB_CFG9_FUNC_SPI0NSS = 4,
    PB_CFG9_FUNC_BT00OUT = 5,
    PB_CFG9_FUNC_BT10OUT = 5,
} PB_CFG9_FUNC_Enum;

/** PB10 gpio alternat function selection */
typedef enum
{
    PB_CFG10_FUNC_GPIO = 0,
    PB_CFG10_FUNC_PWM1A = 1,
    PB_CFG10_FUNC_PWM2B = 2,
    PB_CFG10_FUNC_PWMTZ0 = 3,
    PB_CFG10_FUNC_UART0TX = 4,
    PB_CFG10_FUNC_UART1TX = 6,
    PB_CFG10_FUNC_UART1RX = 7,
} PB_CFG10_FUNC_Enum;

/** PB11 gpio alternat function selection */
typedef enum
{
    PB_CFG11_FUNC_GPIO = 0,
    PB_CFG11_FUNC_PWM2A = 1,
    PB_CFG11_FUNC_PWMTZ2 = 3,
    PB_CFG11_FUNC_CMP1OUT = 4,
    PB_CFG11_FUNC_BT00OUT = 5,
} PB_CFG11_FUNC_Enum;

/** PB15 gpio alternat function selection */
typedef enum
{
    PB_CFG15_FUNC_GPIO = 0,
    PB_CFG15_FUNC_PWM2B = 1,
    PB_CFG15_FUNC_PWM1B = 2,
    PB_CFG15_FUNC_SPI0MOSI = 3,
    PB_CFG15_FUNC_PWM0A = 5,
} PB_CFG15_FUNC_Enum;

/** PC0 gpio alternat function selection */
typedef enum
{
    PC_CFG0_FUNC_GPIO = 0,
    PC_CFG0_FUNC_BT00OUT = 4,
    PC_CFG0_FUNC_PWMTZ1 = 5,
} PC_CFG0_FUNC_Enum;

/** PC1 gpio alternat function selection */
typedef enum
{
    PC_CFG1_FUNC_GPIO = 0,
    PC_CFG1_FUNC_XCLKOUT = 5,
    PC_CFG1_FUNC_EXTSYNO = 6,
} PC_CFG1_FUNC_Enum;

void GPIO_MuxSel(PA_Type *GPIOx, uint8_t GPIO_Pin, uint8_t AF_Mode, uint8_t AD);
void GPIO_TOGGLE(PA_Type *Px, uint8_t n);
void GPIO_MODE_SET(PA_Type *Px, uint8_t n, uint8_t inout);
void GPIO_OUTPUT(PA_Type *Px, uint8_t n, uint8_t output);
void delay(uint32_t time_data);
void mclk_out(void);
void set_pll(uint8_t plldiv, uint8_t pllmul);
uint8_t SYS_Config(uint8_t clk, uint8_t wt);

#endif
