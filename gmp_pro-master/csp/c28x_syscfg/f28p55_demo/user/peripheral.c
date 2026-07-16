// This is an example of peripheral.c

// GMP basic core header
#include <gmp_core.h>
#include <ctl/ctl.config.h>

// user main header
#include "user_main.h"

#define   MATH_TYPE      IQ_MATH
// invoke iqmath lib
#include <third_party/iqmath/IQmathLib.h>

// motor control headers, these driver header is from:
// C:\ti\controlSUITE\libs\app_libs\motor_control\drivers\f2803x_v2.0
// C:\ti\controlSUITE\development_kits\~SupportFiles\F2803x_headers
//#include "DSP2803x_EPwm_defines.h" // Include header for PWM defines
//#include "f2803xileg_vdc.h"        // Include header for the ILEG2DCBUSMEAS object
//#include "f2803xpwm.h"             // Include header for the PWMGEN object
//#include "f2803xpwmdac.h"          // Include header for the PWMGEN object
//#include "f2803xqep.h"             // Include header for the QEP object

// dlog module
//#include <dlog4ch.h>

//// Instance a PWM driver instance
//PWMGEN pwm1 = PWMGEN_DEFAULTS;
//
//// 28035 Main core frequency 60MHz
//#define SYSTEM_FREQUENCY 60
//
//// Define the ISR frequency (kHz)
//#define ISR_FREQUENCY 10
//
//// Samping period (sec)
//float32 T = 0.001 / ISR_FREQUENCY;
//
//// Default ADC initialization
//// SOC0 Control Register to SOC15 Control Register
//
//// SOCx Channel Select.
////
//// Selects the channel to be converted when SOCx is received by the ADC.
//int ChSel[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//
//// SOCx Trigger Source Select
////
//// Configures which trigger will set the respective SOCx flag in the ADCSOCFLG1 register to initiate a
//// conversion to start once priority is given to SOCx. This setting can be overridden by the respective
//// SOCx field in the ADCINTSOCSEL1 or ADCINTSOCSEL2 register.
//int TrigSel[16] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
//
//// SOCx Acquisition Prescale. Controls the sample and hold window for SOCx
//int ACQPS[16] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
//
//// Monitor Objects
//// Create an instance of DATALOG Module
//DLOG_4CH dlog = DLOG_4CH_DEFAULTS;
//
//int16 DlogCh1 = 0;
//int16 DlogCh2 = 0;
//int16 DlogCh3 = 0;
//int16 DlogCh4 = 0;
//
//// Instance a PWM DAC driver instance
//PWMDAC pwmdac1 = PWMDAC_DEFAULTS;
//
//
//// prototype of Main ISR
//interrupt void MainISR(void);
//
////////////////////////////////////////////////////////////////////////////
//// Devices on the peripheral
//
//// User should setup all the peripheral in this function.
void setup_peripheral(void)
{
//
//    // Initialize PWMDAC module
//        pwmdac1.PeriodMax=500;          // @60Mhz, 1500->20kHz, 1000-> 30kHz, 500->60kHz
//        pwmdac1.HalfPerMax=pwmdac1.PeriodMax/2;
//        PWMDAC_INIT_MACRO(6,pwmdac1);    // PWM 6A,6B
//        PWMDAC_INIT_MACRO(7,pwmdac1);    // PWM 7A,7B
//
//    // Initialize DATALOG module
//        dlog.iptr1 = &DlogCh1;
//        dlog.iptr2 = &DlogCh2;
//        dlog.iptr3 = &DlogCh3;
//        dlog.iptr4 = &DlogCh4;
//        dlog.trig_value = 0x1;
//        dlog.size = 0x0c8;
//        dlog.prescalar = 5;
//        dlog.init(&dlog);
//
//    // Initialize PWM module
//    pwm1.PeriodMax = SYSTEM_FREQUENCY * 1000000 * T / 2; // Prescaler X1 (T1), ISR period = T x 1
//    pwm1.HalfPerMax = pwm1.PeriodMax / 2;
//    pwm1.Deadband = 2.0 * SYSTEM_FREQUENCY; // 120 counts -> 2.0 usec for TBCLK = SYSCLK/1
//    PWM_INIT_MACRO(1,2,3,pwm1)
//
//    // Initialize ADC for DMC Kit Rev 1.1
//    ChSel[0] = 1;  // Dummy meas. avoid 1st sample issue Rev0 Picollo*/
//    ChSel[1] = 1;  // ChSelect: ADC A1-> Phase A Current
//    ChSel[2] = 9;  // ChSelect: ADC B1-> Phase B Current
//    ChSel[3] = 3;  // ChSelect: ADC A3-> Phase C Current
//    ChSel[4] = 15; // ChSelect: ADC B7-> Phase A Voltage
//    ChSel[5] = 14; // ChSelect: ADC B6-> Phase B Voltage
//    ChSel[6] = 12; // ChSelect: ADC B4-> Phase C Voltage
//    ChSel[7] = 7;  // ChSelect: ADC A7-> DC Bus  Voltage
//
//    ADC_MACRO_INIT(ChSel, TrigSel, ACQPS);
//
//    // ISR register
//    EALLOW; // This is needed to write to EALLOW protected registers
//
//    PieVectTable.ADCINT1 = &MainISR;
//
//    // Enable PIE group 1 interrupt 1 for ADC1_INT
//    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
//
//    // Enable EOC interrupt(after the 4th conversion)
//
//    AdcRegs.ADCINTOVFCLR.bit.ADCINT1 = 1;
//    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
//    AdcRegs.INTSEL1N2.bit.INT1CONT = 1; //
//    AdcRegs.INTSEL1N2.bit.INT1SEL = 4;
//    AdcRegs.INTSEL1N2.bit.INT1E = 1;
//
//    // Enable CPU INT1 for ADC1_INT:
//    IER |= M_INT1;
//
//    // Enable global Interrupts and higher priority real-time debug events:
//    EINT; // Enable Global interrupt INTM
//    ERTM; // Enable Global realtime interrupt DBGM
//
//    EDIS;
}
//
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

