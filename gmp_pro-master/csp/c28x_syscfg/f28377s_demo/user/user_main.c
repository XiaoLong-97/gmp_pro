// This is the example of user main.
 
//////////////////////////////////////////////////////////////////////////
// headers here

// GMP basic core header
#include <gmp_core.h>

// Controller Template Library
#include <ctl/ctl_core.h>

// user main header
#include "user_main.h"

// SPI DAC interface
#include <ext/dac/dac8554/dac8554.h>


//////////////////////////////////////////////////////////////////////////
// global variables here



//////////////////////////////////////////////////////////////////////////
// initialize routine here
GMP_NO_OPT_PREFIX
void init(void)
GMP_NO_OPT_SUFFIX
{
    // light two LED
//    gmp_hal_gpio_write(LEDR, 0);
//    gmp_hal_gpio_write(LEDG, 1);

//    fVal = 10;
//    GMP_DBG_SWBP;

    // Clear Interrupt
//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);
//
//    CLA_forceTasks(CLA1_BASE, CLA_TASKFLAG_1);

    asm(" RPT #255 || NOP");

//    fVal = fResult;

    // communicate with SPI DAC
//    SPI_writeDataBlockingNonFIFO(SPI0_BASE, DAC8554_LDCMD_SINGLE_CH_UPDATE|DAC8554_CHANNEL_A|DAC8554_DISABLE_POWERDOWN);
//    SPI_writeDataBlockingNonFIFO(SPI0_BASE, 0x80);
//    SPI_writeDataBlockingNonFIFO(SPI0_BASE, 0x00);
}


//////////////////////////////////////////////////////////////////////////
// endless loop function here
void mainloop(void)
{
//    gmp_hal_gpio_toggle(LEDG);

//    CLA_forceTasks(CLA1_BASE, CLA_TASKFLAG_1);

    asm(" RPT #255 || NOP");

//    fVal = fResult;

//    GMP_DBG_SWBP;

    static int16_t data = 0;

    data+= 0x10;

    uint16_t cmd = 0;
    // cmd = 0x10 for channel A
    cmd = DAC8554_LDCMD_SINGLE_CH_UPDATE|DAC8554_CHANNEL_A;


//    gmp_hal_gpio_write(SPIA_CS, 0);
//    asm(" RPT #2 || NOP");
//
//    SPI_writeDataBlockingNonFIFO(SPI0_BASE, cmd<<8);
//    SPI_writeDataBlockingNonFIFO(SPI0_BASE, (data & 0xFF00));
//    SPI_writeDataBlockingNonFIFO(SPI0_BASE, (data & 0xFF)<<8);

    asm(" RPT #2 || NOP");

//    gmp_hal_gpio_write(SPIA_CS, 1);

//    asm(" RPT #1000 || NOP");

//    F28x_usDelay(1);
    size_gt i;

    for(i = 0; i < 10; ++i)
        asm(" NOP");
//
//
//        // cmd = 0x10 for channel A
//        cmd = DAC8554_LDCMD_SIMULTANEOUS_UPDATE|DAC8554_CHANNEL_B;
//
//        SPI_writeDataBlockingNonFIFO(SPI0_BASE, cmd<<8);
//        SPI_writeDataBlockingNonFIFO(SPI0_BASE, (data & 0xFF)<<8);
//        SPI_writeDataBlockingNonFIFO(SPI0_BASE, 0x0000);
//
//        asm(" RPT #10 || NOP");
//
//    //    gmp_hal_gpio_write(SPIA_CS, 1);
//
//        F28x_usDelay(2);
//
//                // cmd = 0x10 for channel A
//                cmd = DAC8554_LDCMD_SIMULTANEOUS_UPDATE|DAC8554_CHANNEL_C;
//
//                SPI_writeDataBlockingNonFIFO(SPI0_BASE, cmd<<8);
//                SPI_writeDataBlockingNonFIFO(SPI0_BASE, (data & 0xFF)<<8);
//                SPI_writeDataBlockingNonFIFO(SPI0_BASE, 0x0000);
//
//                asm(" RPT #10 || NOP");
//
//            //    gmp_hal_gpio_write(SPIA_CS, 1);
//
//                F28x_usDelay(2);
//
//                // cmd = 0x10 for channel D
//                        cmd = DAC8554_LDCMD_SIMULTANEOUS_UPDATE|DAC8554_CHANNEL_D;
//
//                        SPI_writeDataBlockingNonFIFO(SPI0_BASE, cmd<<8);
//                        SPI_writeDataBlockingNonFIFO(SPI0_BASE, (data & 0xFF)<<8);
//                        SPI_writeDataBlockingNonFIFO(SPI0_BASE, 0x0000);
//
//                        asm(" RPT #10 || NOP");
//
//                    //    gmp_hal_gpio_write(SPIA_CS, 1);
//
//                        F28x_usDelay(2);

}



