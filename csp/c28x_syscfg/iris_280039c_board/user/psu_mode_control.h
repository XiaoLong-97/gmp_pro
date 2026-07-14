#ifndef PSU_MODE_CONTROL_H
#define PSU_MODE_CONTROL_H

#include <stdint.h>

#define PSU_INPUT_MODE_AUTO             0U
#define PSU_INPUT_MODE_CV               1U
#define PSU_INPUT_MODE_CC               2U

#define PSU_REGULATION_CV               0U
#define PSU_REGULATION_CC               1U

#define PSU_EDIT_TARGET_VOLTAGE         0U
#define PSU_EDIT_TARGET_CURRENT         1U

#define PSU_MODE_VOLTAGE_COMPLIANCE_MV  10000U
#define PSU_MODE_CURRENT_COMPLIANCE_MA  105U

typedef struct
{
    uint16_t input_mode;
    uint16_t edit_target;
    uint16_t output_on;
} psu_mode_switch_result_t;

static inline uint16_t psu_mode_next_input(uint16_t input_mode)
{
    if (input_mode == PSU_INPUT_MODE_AUTO)
        return PSU_INPUT_MODE_CV;
    if (input_mode == PSU_INPUT_MODE_CV)
        return PSU_INPUT_MODE_CC;
    return PSU_INPUT_MODE_AUTO;
}

static inline uint16_t psu_mode_allowed_edit(uint16_t input_mode,
                                              uint16_t requested_edit)
{
    if (input_mode == PSU_INPUT_MODE_CV)
        return PSU_EDIT_TARGET_VOLTAGE;
    if (input_mode == PSU_INPUT_MODE_CC)
        return PSU_EDIT_TARGET_CURRENT;
    return (requested_edit == PSU_EDIT_TARGET_CURRENT)
               ? PSU_EDIT_TARGET_CURRENT : PSU_EDIT_TARGET_VOLTAGE;
}

static inline uint16_t psu_mode_voltage_target_mv(uint16_t input_mode,
                                                   uint16_t user_set_mv)
{
    return (input_mode == PSU_INPUT_MODE_CC)
               ? PSU_MODE_VOLTAGE_COMPLIANCE_MV : user_set_mv;
}

static inline uint16_t psu_mode_current_target_ma(uint16_t input_mode,
                                                  uint16_t user_set_ma)
{
    return (input_mode == PSU_INPUT_MODE_CV)
               ? PSU_MODE_CURRENT_COMPLIANCE_MA : user_set_ma;
}

static inline uint16_t psu_mode_regulation_state(uint16_t input_mode,
                                                  uint16_t auto_state)
{
    if (input_mode == PSU_INPUT_MODE_CV)
        return PSU_REGULATION_CV;
    if (input_mode == PSU_INPUT_MODE_CC)
        return PSU_REGULATION_CC;
    return (auto_state == PSU_REGULATION_CC) ? PSU_REGULATION_CC
                                              : PSU_REGULATION_CV;
}

static inline psu_mode_switch_result_t psu_mode_switch(uint16_t input_mode,
                                                        uint16_t edit_target)
{
    psu_mode_switch_result_t result;

    result.input_mode = psu_mode_next_input(input_mode);
    result.edit_target = psu_mode_allowed_edit(result.input_mode, edit_target);
    result.output_on = 0U;
    return result;
}

#endif /* PSU_MODE_CONTROL_H */
