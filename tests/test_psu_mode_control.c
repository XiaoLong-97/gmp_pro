#include "../csp/c28x_syscfg/iris_280039c_board/user/psu_mode_control.h"

#define CHECK(code, condition) do { if (!(condition)) return (code); } while (0)

int main(void)
{
    psu_mode_switch_result_t switched;

    CHECK(1, psu_mode_next_input(PSU_INPUT_MODE_AUTO) == PSU_INPUT_MODE_CV);
    CHECK(2, psu_mode_next_input(PSU_INPUT_MODE_CV) == PSU_INPUT_MODE_CC);
    CHECK(3, psu_mode_next_input(PSU_INPUT_MODE_CC) == PSU_INPUT_MODE_AUTO);

    CHECK(4, psu_mode_allowed_edit(PSU_INPUT_MODE_AUTO, PSU_EDIT_TARGET_VOLTAGE) ==
                 PSU_EDIT_TARGET_VOLTAGE);
    CHECK(5, psu_mode_allowed_edit(PSU_INPUT_MODE_AUTO, PSU_EDIT_TARGET_CURRENT) ==
                 PSU_EDIT_TARGET_CURRENT);
    CHECK(6, psu_mode_allowed_edit(PSU_INPUT_MODE_CV, PSU_EDIT_TARGET_CURRENT) ==
                 PSU_EDIT_TARGET_VOLTAGE);
    CHECK(7, psu_mode_allowed_edit(PSU_INPUT_MODE_CC, PSU_EDIT_TARGET_VOLTAGE) ==
                 PSU_EDIT_TARGET_CURRENT);

    CHECK(8, psu_mode_voltage_target_mv(PSU_INPUT_MODE_AUTO, 8500U) == 8500U);
    CHECK(9, psu_mode_current_target_ma(PSU_INPUT_MODE_AUTO, 50U) == 50U);
    CHECK(10, psu_mode_voltage_target_mv(PSU_INPUT_MODE_CV, 8500U) == 8500U);
    CHECK(11, psu_mode_current_target_ma(PSU_INPUT_MODE_CV, 50U) == 105U);
    CHECK(12, psu_mode_voltage_target_mv(PSU_INPUT_MODE_CC, 8500U) == 10000U);
    CHECK(13, psu_mode_current_target_ma(PSU_INPUT_MODE_CC, 50U) == 50U);

    CHECK(14, psu_mode_regulation_state(PSU_INPUT_MODE_CV, PSU_REGULATION_CC) ==
                  PSU_REGULATION_CV);
    CHECK(15, psu_mode_regulation_state(PSU_INPUT_MODE_CC, PSU_REGULATION_CV) ==
                  PSU_REGULATION_CC);
    CHECK(16, psu_mode_regulation_state(PSU_INPUT_MODE_AUTO, PSU_REGULATION_CC) ==
                  PSU_REGULATION_CC);

    switched = psu_mode_switch(PSU_INPUT_MODE_AUTO, PSU_EDIT_TARGET_CURRENT);
    CHECK(17, switched.input_mode == PSU_INPUT_MODE_CV);
    CHECK(18, switched.edit_target == PSU_EDIT_TARGET_VOLTAGE);
    CHECK(19, switched.output_on == 0U);

    switched = psu_mode_switch(PSU_INPUT_MODE_CV, PSU_EDIT_TARGET_VOLTAGE);
    CHECK(20, switched.input_mode == PSU_INPUT_MODE_CC);
    CHECK(21, switched.edit_target == PSU_EDIT_TARGET_CURRENT);
    CHECK(22, switched.output_on == 0U);

    switched = psu_mode_switch(PSU_INPUT_MODE_CC, PSU_EDIT_TARGET_CURRENT);
    CHECK(23, switched.input_mode == PSU_INPUT_MODE_AUTO);
    CHECK(24, switched.edit_target == PSU_EDIT_TARGET_CURRENT);
    CHECK(25, switched.output_on == 0U);

    return 0;
}
