//
// THIS IS A DEMO SOURCE CODE FOR GMP LIBRARY.
//
// User should add all declarations of controller objects in this file.
//
// User should implement the Main ISR of the controller tasks.
//
// User should ensure that all the controller codes here is platform-independent.
// 
// WARNING: This file must be kept in the include search path during compilation.
//

#ifndef _FILE_CTL_MAIN_H_
#define _FILE_CTL_MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////
// Add all controller macros here
//

// BUILD_LEVEL 1: Voltage Open loop
// BUILD_LEVEL 2: Current Open loop
// BUILD_LEVEL 3: Current Open loop with actual position
// BUILD_LEVEL 4: Speed Close loop
#define BUILD_LEVEL (4)

// controller frequency
#define CONTROLLER_FREQUENCY (10000)

    //////////////////////////////////////////////////////////////////////////
    // include all the necessary CTL modules here.
    //

#include <ctl/suite/motor_control/pmsm_servo/pmsm_servo.h>

#include <ctl/component/motor_control/basic/encoder.h>

// const F & VF controller
#include <ctl/component/motor_control/basic/vf_generator.h>

    //////////////////////////////////////////////////////////////////////////
    // add all controller object declarations here.
    //

    // position encoder
    extern ctl_pos_encoder_t pos_enc;

    // speed encoder
    extern ctl_spd_calculator_t spd_enc;

    // PMSM servo objects
    extern pmsm_servo_fm_t pmsm_servo;

    // PMSM const frequency controller
    extern ctl_const_f_controller const_f;

    //////////////////////////////////////////////////////////////////////////
    // This function may run in Main ISR
    // This function will be called by gmp_base_step();
    //
    // If you use CTL nano, we recommend you to keep this function is a null function.
    //
    GMP_STATIC_INLINE
    void ctl_dispatch(void)
    {
        if (flag_enable_adc_calibrator)
        {
            ctl_step_adc_calibrator(&adc_calibrator, pmsm_ctrl.mtr_interface.uabc.value.dat[index_adc_calibrator]);
        }

        ctl_step_const_f_controller(&const_f);

        ctl_step_spd_calc(&spd_enc);

        ctl_step_pmsm_ctrl(&pmsm_ctrl);
    }

#ifdef SPECIFY_ENABLE_CTL_FRAMEWORK_NANO

    //////////////////////////////////////////////////////////////////////////
    // This function may run in Main ISR
    // This function will be called by gmp_base_step();
    //
    GMP_STATIC_INLINE
    void ctl_fmif_core_stage_routine(ctl_object_nano_t *pctl_obj)
    {
        // constant frequency generator
        ctl_step_const_f_controller(&const_f);

        // run pmsm servo framework ISR function
        ctl_step_pmsm_servo_framework(&pmsm_servo);
    }

#endif // SPECIFY_ENABLE_CTL_FRAMEWORK_NANO

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FILE_CTL_MAIN_H_
