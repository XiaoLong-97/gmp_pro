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

#include <ctl/component/motor_control/basic/std_sil_motor_interface.h>

#include <xplt.peripheral.h>


#ifndef _FILE_CTL_INTERFACE_H_
#define _FILE_CTL_INTERFACE_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    //////////////////////////////////////////////////////////////////////////
    // device related functions
    // Controller interface
    //


    // Functions without controller nano framework.
#ifndef SPECIFY_ENABLE_CTL_FRAMEWORK_NANO

    // Input Callback
    GMP_STATIC_INLINE
    void ctl_input_callback(void)
    {

    }

    // Output Callback
    GMP_STATIC_INLINE
    void ctl_output_callback(void)
    {

    }

    // Enable Motor Controller
    // Enable Output
    GMP_STATIC_INLINE
    void ctl_enable_output()
    {

    }

    // Disable Output
    GMP_STATIC_INLINE
    void ctl_disable_output()
    {

    }

#endif // SPECIFY_ENABLE_CTL_FRAMEWORK_NANO

    // Functions with controller nano framework

#ifdef SPECIFY_ENABLE_CTL_FRAMEWORK_NANO

    // Controller Nano input stage routine
    GMP_STATIC_INLINE
    void ctl_fmif_input_stage_routine(ctl_object_nano_t *pctl_obj)
    {
    }

    // Controller Nano output stage routine
    GMP_STATIC_INLINE
    void ctl_fmif_output_stage_routine(ctl_object_nano_t *pctl_obj)
    {
    }

    // Controller Request stage
    GMP_STATIC_INLINE
    void ctl_fmif_request_stage_routine(ctl_object_nano_t *pctl_obj)
    {
    }

    // Enable Output
    GMP_STATIC_INLINE
    void ctl_fmif_output_enable(ctl_object_nano_t *pctl_obj)
    {
    }

    // Disable Output
    GMP_STATIC_INLINE
    void ctl_fmif_output_disable(ctl_object_nano_t *pctl_obj)
    {
    }

#endif // SPECIFY_ENABLE_CTL_FRAMEWORK_NANO

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FILE_CTL_INTERFACE_H_
