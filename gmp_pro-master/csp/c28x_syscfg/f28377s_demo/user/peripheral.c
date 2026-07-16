// This is an example of peripheral.c

// GMP basic core header
#include <gmp_core.h>
#include <ctl/ctl.config.h>

// user main header
#include "user_main.h"

//#define   MATH_TYPE      IQ_MATH
//// invoke iqmath lib
//#include <third_party/iqmath/IQmathLib.h>


//
//Task 1 (C) Variables
// NOTE: Do not initialize the Message RAM variables globally, they will be
// reset during the message ram initialization phase in the CLA memory
// configuration routine
//

//#ifdef __cplusplus
//
//#pragma DATA_SECTION("CpuToCla1MsgRAM");
//float fVal;
//
//#pragma DATA_SECTION("Cla1ToCpuMsgRAM");
//float fResult;
//
//#else
//
//#pragma DATA_SECTION(fVal,"CpuToCla1MsgRAM");
//adc_gt adc_data;
//
//#pragma DATA_SECTION(fResult,"Cla1ToCpuMsgRAM");
//float fResult;
//#endif //__cplusplus
//
//
//#ifdef __cplusplus
//#pragma DATA_SECTION("CLADataLS1")
//#else
//#pragma DATA_SECTION(CLAatan2Table,"CLADataLS1")
//#endif //__cplusplus
//float CLAatan2Table[]={
//    0.000000000000, 1.000040679675, -0.007811069750,
//    -0.000003807022, 1.000528067772, -0.023410345493
//};

__interrupt void cla1Isr1()
{
    // output routine
    ctl_fmif_output_stage_routine(&pmsm_servo.base);

    // request routine
    ctl_fmif_request_stage_routine(&pmsm_servo.base);

    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

    //
    // Uncomment to halt debugger and stop here
    //
//    asm(" ESTOP0");
}

////////////////////////////////////////////////////////////////////////////
//// Devices on the peripheral

// User should setup all the peripheral in this function.
// This function has been completed by syscfg
void setup_peripheral(void)
{

}


////////////////////////////////////////////////////////////////////////////
//// device related functions
//#ifdef SPECIFY_ENABLE_CTL_FRAMEWORK_NANO
//

void ctl_fmif_output_enable(ctl_object_nano_t *pctl_obj)
{

}

void ctl_fmif_output_disable(ctl_object_nano_t *pctl_obj)
{

}

fast_gt ctl_fmif_security_routine(ctl_object_nano_t *pctl_obj)
{
    // not implement
    return GMP_EC_OK;
}
//
//
//#endif
//
//
////////////////////////////////////////////////////////////////////////////
//// interrupt functions and callback functions here
//
//// This function should be called in Main ISR
//void gmp_base_ctl_step(void);
//
//interrupt void MainISR(void)
//{
//    // Calculate the new PWM compare values
//
//    pwm1.MfuncC1 = _IQ(0);
//    pwm1.MfuncC2 = _IQ(0);
//    pwm1.MfuncC3 = _IQ(0);
//    PWM_MACRO(1, 2, 3, pwm1)
////    (*ePWM[1]).CMPA.half.CMPA =1375;
////         (*ePWM[2]).CMPA.half.CMPA = 1875;
////         (*ePWM[2]).CMPA.half.CMPA = 1375;
//
//    // call GMP ISR callback function
//    gmp_base_ctl_step();
//
//    // Enable more interrupts from this timer
//    AdcRegs.ADCINTFLG.bit.ADCINT1 = 1;
//
//    // Acknowledge interrupt to recieve more interrupts from PIE group 3
//    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
//}

