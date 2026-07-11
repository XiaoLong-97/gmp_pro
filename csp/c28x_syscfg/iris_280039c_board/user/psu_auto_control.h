#ifndef PSU_AUTO_CONTROL_H
#define PSU_AUTO_CONTROL_H

#include <stdint.h>

#define PSU_AUTO_MODE_CV                0U
#define PSU_AUTO_MODE_CC                1U
#define PSU_AUTO_CURRENT_HYSTERESIS_MA  1U
#define PSU_AUTO_VOLTAGE_HYSTERESIS_MV  100U

static inline uint16_t psu_auto_next_mode(uint16_t mode, uint16_t measured_mv,
                                          uint16_t measured_ma, uint16_t set_mv,
                                          uint16_t set_ma)
{
    uint16_t cc_enter_ma = (set_ma < UINT16_MAX) ? (uint16_t)(set_ma + PSU_AUTO_CURRENT_HYSTERESIS_MA)
                                                  : UINT16_MAX;
    uint16_t cv_enter_mv = (set_mv > PSU_AUTO_VOLTAGE_HYSTERESIS_MV)
                               ? (uint16_t)(set_mv - PSU_AUTO_VOLTAGE_HYSTERESIS_MV)
                               : 0U;

    if (mode == PSU_AUTO_MODE_CV)
        return (measured_ma >= cc_enter_ma) ? PSU_AUTO_MODE_CC : PSU_AUTO_MODE_CV;

    return (measured_mv >= cv_enter_mv) ? PSU_AUTO_MODE_CV : PSU_AUTO_MODE_CC;
}

#endif
