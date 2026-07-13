#include "../csp/c28x_syscfg/iris_280039c_board/user/psu_calibration.h"

#define STATIC_ASSERT(name, condition) typedef char static_assert_##name[(condition) ? 1 : -1]

/* Measurement calibration: output units are mV and mA. */
STATIC_ASSERT(voltage_zero_offset, PSU_CALIBRATE_VOLTAGE_MV(0U) == 44U);
STATIC_ASSERT(voltage_low_point, PSU_CALIBRATE_VOLTAGE_MV(60U) == 107U);
STATIC_ASSERT(voltage_one_volt_point, PSU_CALIBRATE_VOLTAGE_MV(900U) == 999U);
STATIC_ASSERT(voltage_full_scale_point, PSU_CALIBRATE_VOLTAGE_MV(9480U) == 10110U);
STATIC_ASSERT(current_zero_offset, PSU_CALIBRATE_CURRENT_MA(0U) == 4U);
STATIC_ASSERT(current_ten_milliamp_point, PSU_CALIBRATE_CURRENT_MA(10U) == 14U);
STATIC_ASSERT(current_full_scale_point, PSU_CALIBRATE_CURRENT_MA(100U) == 103U);
STATIC_ASSERT(current_centi_low_point,
              PSU_CALIBRATE_CURRENT_CENTIMA(100U) == 481U);
STATIC_ASSERT(current_centi_ten_milliamp_point,
              PSU_CALIBRATE_CURRENT_CENTIMA(1000U) == 1378U);
STATIC_ASSERT(current_centi_full_scale_point,
              PSU_CALIBRATE_CURRENT_CENTIMA(10000U) == 10342U);

/* Command pre-compensation retains 0.1 mV and 0.001 mA before DAC scaling. */
STATIC_ASSERT(voltage_command_zero_clamped,
              PSU_VOLTAGE_COMMAND_DECIMV(0U) == 0U);
STATIC_ASSERT(voltage_command_midpoint,
              PSU_VOLTAGE_COMMAND_DECIMV(5000U) == 49426U);
STATIC_ASSERT(voltage_command_full_scale,
              PSU_VOLTAGE_COMMAND_DECIMV(10000U) == 99070U);
STATIC_ASSERT(current_command_zero_clamped,
              PSU_CURRENT_COMMAND_MILLI_MA(0U) == 0U);
STATIC_ASSERT(current_command_ten_milliamp,
              PSU_CURRENT_COMMAND_MILLI_MA(10U) == 5895U);
STATIC_ASSERT(current_command_midpoint,
              PSU_CURRENT_COMMAND_MILLI_MA(50U) == 46242U);
STATIC_ASSERT(current_command_full_scale,
              PSU_CURRENT_COMMAND_MILLI_MA(100U) == 96675U);

STATIC_ASSERT(voltage_dac_midpoint,
              PSU_VOLTAGE_DAC_COUNTS(5000U, 3102U) == 1533U);
STATIC_ASSERT(voltage_dac_full_scale,
              PSU_VOLTAGE_DAC_COUNTS(10000U, 3102U) == 3073U);
STATIC_ASSERT(voltage_cc_compliance,
              PSU_VOLTAGE_DAC_COUNTS(10300U, 3102U) == 3166U);
STATIC_ASSERT(current_dac_ten_milliamp,
              PSU_CURRENT_DAC_COUNTS(10U, 2482U) == 146U);
STATIC_ASSERT(current_dac_full_scale,
              PSU_CURRENT_DAC_COUNTS(100U, 2482U) == 2399U);
STATIC_ASSERT(current_cv_compliance,
              PSU_CURRENT_DAC_COUNTS(105U, 2482U) == 2525U);

int main(void)
{
    return 0;
}
