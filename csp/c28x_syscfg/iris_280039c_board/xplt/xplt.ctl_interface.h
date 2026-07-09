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

#include <xplt.peripheral.h>
#include <ctl/component/interface/adc_channel.h>

#ifndef _FILE_CTL_INTERFACE_H_
#define _FILE_CTL_INTERFACE_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//=================================================================================================
// Controller interface

// Input Callback
GMP_STATIC_INLINE void ctl_input_callback(void)
{
    static fast_gt adc_init_done = 0;
    static adc_channel_t dac_a_adc;
    static adc_gt dac_a_raw = 0;

    if (!adc_init_done)
    {
        // Convert 0.825V amplitude around 1.65V bias into -1..1 per-unit.
        ctl_init_adc_channel(&dac_a_adc, 4.0f, 0.5f, 12, 24);
        adc_init_done = 1;
    }

    // Change ADC_CH1_RESULT_BASE / ADC_CH1 if DAC A is wired to another ADC input.
    dac_a_raw = ADC_readResult(ADC_CH1_RESULT_BASE, ADC_CH1);
    dac_a_pu = ctl_step_adc_channel(&dac_a_adc, dac_a_raw);
    GMP_UNUSED_VAR(dac_a_pu);
}

// Output Callback
GMP_STATIC_INLINE void ctl_output_callback(void)
{
    if (psu_dac_force_test_enabled)
    {
        DAC_setShadowValue(IRIS_DACA_BASE, psu_vset_dac_counts);
        DAC_setShadowValue(IRIS_DACB_BASE, psu_iset_dac_counts);
        EPWM_setCounterCompareValue(IRIS_EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0);
    }
    else if (psu_output_enabled)
    {
        DAC_setShadowValue(IRIS_DACA_BASE, psu_vset_dac_counts);
        DAC_setShadowValue(IRIS_DACB_BASE, psu_iset_dac_counts);
        EPWM_setCounterCompareValue(IRIS_EPWM1_BASE, EPWM_COUNTER_COMPARE_A, dac_a_lead_pwm_cmp);
    }
    else
    {
        DAC_setShadowValue(IRIS_DACA_BASE, 0);
        DAC_setShadowValue(IRIS_DACB_BASE, 0);
        EPWM_setCounterCompareValue(IRIS_EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0);
    }
}

// function prototype
void GPIO_WritePin(uint16_t gpioNumber, uint16_t outVal);

// Enable Motor Controller
// Enable Output
GMP_STATIC_INLINE void ctl_fast_enable_output()
{
    // Clear any Trip Zone flag
    EPWM_clearTripZoneFlag(PHASE_U_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_clearTripZoneFlag(PHASE_V_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_clearTripZoneFlag(PHASE_W_BASE, EPWM_TZ_FORCE_EVENT_OST);
}

// Disable Output
GMP_STATIC_INLINE void ctl_fast_disable_output()
{
    // Disables the PWM device
    EPWM_forceTripZoneEvent(PHASE_U_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(PHASE_V_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(PHASE_W_BASE, EPWM_TZ_FORCE_EVENT_OST);
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FILE_CTL_INTERFACE_H_
