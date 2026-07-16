
// Using this header may avoid redefine controller variables.
#include <ctl_main.h>



// This file is platform related


#ifndef _FILE_CTL_INTERFACE_H_
#define _FILE_CTL_INTERFACE_H_

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

// Input routine
// Input ADCs and other necessary messages.
GMP_STATIC_INLINE
void ctl_fmif_input_stage_routine(ctl_object_nano_t *pctl_obj)
{
    pmsm_servo_fm_t* pmsm = (pmsm_servo_fm_t*) pctl_obj;

    ctl_step_adc_tri_channel(&pmsm->iabc_input,
                             ADC_readResult(ADC_B_RESULT_BASE, MOTOR_IU),
                             ADC_readResult(ADC_C_RESULT_BASE, MOTOR_IV),
                             ADC_readResult(ADC_A_RESULT_BASE, MOTOR_IW));

//    ctl_step_adc_tri_channel(&pmsm->vabc_input,
//                             ADC_readResult(ADC_B_RESULT_BASE, MOTOR_VU),
//                             ADC_readResult(ADC_C_RESULT_BASE, MOTOR_VV),
//                             ADC_readResult(ADC_A_RESULT_BASE, MOTOR_VW));
    ctl_step_adc_channel(&pmsm->udc_input, ADC_readResult(ADC_A_RESULT_BASE, MOTOR_VDC));
}


// output all the PWM and other digital or analog signal
GMP_STATIC_INLINE
void ctl_fmif_output_stage_routine(ctl_object_nano_t *pctl_obj)
{
    pmsm_servo_fm_t* pmsm = (pmsm_servo_fm_t*) pctl_obj;

    ctl_vector3_t Tabc;

    ctl_ct_svpwm_calc(&pmsm->current_ctrl.iab0, &Tabc);

    EPWM_setCounterCompareValue(EPWMU_BASE, EPWM_COUNTER_COMPARE_A,
                        Tabc.dat[phase_U]);
    EPWM_setCounterCompareValue(EPWMV_BASE, EPWM_COUNTER_COMPARE_A,
                        Tabc.dat[phase_V]);
    EPWM_setCounterCompareValue(EPWMW_BASE, EPWM_COUNTER_COMPARE_A,
                        Tabc.dat[phase_W]);
}


// request other information via peripheral, for instance SPI.
GMP_STATIC_INLINE
void ctl_fmif_request_stage_routine(ctl_object_nano_t *pctl_obj)
{
}



#ifdef __cplusplus
}
#endif // _cplusplus

#endif //_FILE_CTL_INTERFACE_H_
