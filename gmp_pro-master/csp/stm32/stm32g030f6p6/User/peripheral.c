// This is an example of peripheral.c

// GMP basic core header
#include <gmp_core.h>
#include <ctl/ctl.config.h>

// user main header
#include "user_main.h"

#define   MATH_TYPE      IQ_MATH
// invoke iqmath lib
#include <third_party/iqmath/IQmathLib.h>



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
//void ctl_fmif_input_stage_routine(ctl_object_nano_t *pctl_obj)
//{
//    // current sensor
////    ctl_input_pmsm_servo_framework(&pmsm_servo,
////                                   // current input
////                                   AdcResult.ADCRESULT1, AdcResult.ADCRESULT2, AdcResult.ADCRESULT3);
//
//    // position encoder
//    //ctl_step_pos_encoder(&pos_enc, gmp_csp_sl_get_rx_buffer()->encoder);
//    //ctl_step_spd_calc(&spd_enc);
//}
//
//void ctl_fmif_output_stage_routine(ctl_object_nano_t *pctl_obj)
//{
//    uint32_t time = gmp_base_get_system_tick() % 10;
//
//
//    pwm1.MfuncC1 =_IQmpy( _IQ(time),_IQ(0.1))-_IQ(0.5);
//       pwm1.MfuncC2 = 0;
//       pwm1.MfuncC3 = _IQ(-0.5);
//       PWM_MACRO(1,2,3,pwm1);
//}
//
//void ctl_fmif_request_stage_routine(ctl_object_nano_t *pctl_obj)
//{
//
//}
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

