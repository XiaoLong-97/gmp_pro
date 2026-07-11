#include "../csp/c28x_syscfg/iris_280039c_board/user/psu_measurement.h"

#define STATIC_ASSERT(name, condition) typedef char static_assert_##name[(condition) ? 1 : -1]

STATIC_ASSERT(zero_voltage, PSU_ADC_VOUT_MV_FROM_COUNTS(0U) == 0U);
STATIC_ASSERT(zero_current, PSU_ADC_IOUT_MA_FROM_COUNTS(0U) == 0U);

/* 2.5 V and 2.0 V at a 3.3 V, 12-bit ADC. */
STATIC_ASSERT(ten_volt_feedback, PSU_ADC_VOUT_MV_FROM_COUNTS(3102U) == 9999U);
STATIC_ASSERT(hundred_milliamp_feedback, PSU_ADC_IOUT_MA_FROM_COUNTS(2482U) == 100U);

/* Preserve headroom so software can observe over-limit values. */
STATIC_ASSERT(voltage_full_scale, PSU_ADC_VOUT_MV_FROM_COUNTS(4095U) == 13200U);
STATIC_ASSERT(current_full_scale, PSU_ADC_IOUT_MA_FROM_COUNTS(4095U) == 165U);

/* A quarter-step IIR with a two-count deadband suppresses ADC display jitter. */
STATIC_ASSERT(filter_rising, PSU_ADC_FILTER_BLEND(0U, 1000U) == 250U);
STATIC_ASSERT(filter_falling, PSU_ADC_FILTER_BLEND(1000U, 0U) == 750U);
STATIC_ASSERT(filter_one_count_deadband, PSU_ADC_FILTER_BLEND(1000U, 1001U) == 1000U);
STATIC_ASSERT(filter_two_count_deadband, PSU_ADC_FILTER_BLEND(1000U, 1002U) == 1000U);

int main(void)
{
    psu_adc_filter_t filter = {0U, 0U};

    if (psu_adc_filter_update(&filter, 1000U) != 1000U)
        return 1;
    if (psu_adc_filter_update(&filter, 2000U) != 1250U)
        return 2;

    return 0;
}
