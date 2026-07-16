// This file is based on Silan SDK
// H/W Platform   : SL_FOC FOR MOTOR CONCTROL
//


#include <gmp_core.h>

// System Tick
time_gt system_tick = 0;

// User should invoke this function to get time (system tick).
time_gt gmp_base_get_system_tick(void)
{
    return system_tick;
}

// This function may be called and used to initialize all the peripheral.
void gmp_csp_startup(void)
{
    // Close Global Interrupt
    __disable_irq();

    // 
    // Initialize all the peripherals 
    // 
   /*********************CLOCK**********************/
    SYS_Config(72, 3);

    /*********************RAM************************/
    SRAM1_Config();

    /*********************ADC************************/
    ADC_Init();

    /*********************PWM************************/
    PWM_Init(PWM_PERIOD);

    /*********************OPA***********************/
    //	OPA1_Init();
    OPA0_Init();

    /*********************CMP***********************/
    CMP1_Init();

    /*********************GPIO***********************/
    Gpio_Init();

    /*********************BT4************************/
    BT4_0_Init(); // 1ms
    //	BT4_1_Init();  //500us

    /*********************BT0/1************************/
    BT0_capture_test();
    BT1_TimingMode_test();

    /*********************COPROC*********************/
    Coproc_Init();

    /*********************UART0***********************/
    UART_Model123_Config(UART0, 0X01, UART_FUNC_DOUBLE);
    UART_ISR_EN(UART0);

    /*********************SPI***********************/
    SPI_Config();

    /*********************WWDT INIT******************/
    WWDT_Config();

    /*********************IWDT INIT******************/
    IWDT_Config();

    /*********************IRQ INIT*******************/
    IRQ_Init();

    // Open System global interrupt
    // All things is ready
    __enable_irq(); // SETP8: 打开全局中断

}

void gmp_csp_loop()
{
}

void gmp_csp_post_process()
{
}


void Device_Init(void)
{
    /*********************CLOCK**********************/
    SYS_Config(72, 3);
    /*********************RAM************************/
    SRAM1_Config();
    /*********************ADC************************/
    ADC_Init();
    /*********************PWM************************/
    PWM_Init(PWM_PERIOD);
    /*********************OPA***********************/
    //	OPA1_Init();
    OPA0_Init();
    /*********************CMP***********************/
    CMP1_Init();
    /*********************GPIO***********************/
    Gpio_Init();
    /*********************BT4************************/
    BT4_0_Init(); // 1ms
    //	BT4_1_Init();  //500us
    /*********************BT0/1************************/
    BT0_capture_test();
    BT1_TimingMode_test();
    /*********************COPROC*********************/
    Coproc_Init();
    /*********************UART0***********************/
    UART_Model123_Config(UART0, 0X01, UART_FUNC_DOUBLE);
    UART_ISR_EN(UART0);
    /*********************SPI***********************/
    SPI_Config();
    /*********************WWDT INIT******************/
    WWDT_Config();
    /*********************IWDT INIT******************/
    IWDT_Config();
    /*********************IRQ INIT*******************/
    IRQ_Init();
}

// System Main function
int main()
{
    // This function may not return.
    gmp_base_entry();
}

