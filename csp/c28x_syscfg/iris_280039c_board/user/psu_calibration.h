#ifndef PSU_CALIBRATION_H
#define PSU_CALIBRATION_H

#include <stdint.h>

/*
 * Calibration fitted from the 2026-07 measurement set.
 *
 * Measurement:
 *   V_true = 1.061862 * V_raw + 43.616 mV
 *   I_true = 0.996062 * I_raw + 3.817389 mA
 *
 * Command pre-compensation:
 *   V_cmd = 0.992884 * V_target - 21.792 mV
 *   I_cmd = 1.008669 * I_target - 4.191745 mA
 */
#define PSU_CALIBRATION_SCALE                         1000000UL

#define PSU_VOLTAGE_MEAS_GAIN_EXCESS_PPM             61862UL
#define PSU_VOLTAGE_MEAS_OFFSET_SCALED_MV             43616000UL
#define PSU_CURRENT_MEAS_GAIN_DEFICIT_PPM             3938UL
#define PSU_CURRENT_MEAS_OFFSET_SCALED_CENTIMA        381738900UL

#define PSU_VOLTAGE_COMMAND_GAIN_DEFICIT_PPM          7116UL
#define PSU_VOLTAGE_COMMAND_OFFSET_SCALED_MV          21792000UL
#define PSU_CURRENT_COMMAND_GAIN_PPM                  1008669L
#define PSU_CURRENT_COMMAND_OFFSET_SCALED_MA          4191745L

#define PSU_CALIBRATION_VOLTAGE_INPUT_MAX_MV          13200U
#define PSU_CALIBRATION_CURRENT_INPUT_MAX_MA          165U
#define PSU_CALIBRATION_CURRENT_INPUT_MAX_CENTIMA     16500U
/* CV current compliance exceeds the user limit; voltage commands remain within 10.0 V. */
#define PSU_CALIBRATION_VOLTAGE_TARGET_MAX_MV         10000U
#define PSU_CALIBRATION_CURRENT_TARGET_MAX_MA         105U

#define PSU_CALIBRATION_LIMIT(value, maximum)                                 \
    (((uint32_t)(value) > (uint32_t)(maximum)) ? (uint32_t)(maximum)          \
                                                : (uint32_t)(value))

/* Exact six-decimal voltage gain without a 64-bit multiply. */
#define PSU_CALIBRATE_VOLTAGE_MV(raw_mv)                                      \
    ((uint16_t)(PSU_CALIBRATION_LIMIT((raw_mv),                               \
                                      PSU_CALIBRATION_VOLTAGE_INPUT_MAX_MV) + \
                (((PSU_CALIBRATION_LIMIT(                                     \
                       (raw_mv), PSU_CALIBRATION_VOLTAGE_INPUT_MAX_MV) *       \
                   PSU_VOLTAGE_MEAS_GAIN_EXCESS_PPM) +                        \
                  PSU_VOLTAGE_MEAS_OFFSET_SCALED_MV +                         \
                  (PSU_CALIBRATION_SCALE / 2UL)) /                            \
                 PSU_CALIBRATION_SCALE)))

#define PSU_CURRENT_MEAS_CORRECTION_CENTIMA(raw_centima)                      \
    ((uint32_t)(((PSU_CURRENT_MEAS_OFFSET_SCALED_CENTIMA -                    \
                  (PSU_CALIBRATION_LIMIT(                                     \
                       (raw_centima),                                         \
                       PSU_CALIBRATION_CURRENT_INPUT_MAX_CENTIMA) *           \
                   PSU_CURRENT_MEAS_GAIN_DEFICIT_PPM)) +                      \
                 (PSU_CALIBRATION_SCALE / 2UL)) /                             \
                PSU_CALIBRATION_SCALE))

#define PSU_CALIBRATE_CURRENT_CENTIMA(raw_centima)                            \
    ((uint16_t)(PSU_CALIBRATION_LIMIT(                                        \
                    (raw_centima),                                            \
                    PSU_CALIBRATION_CURRENT_INPUT_MAX_CENTIMA) +              \
                PSU_CURRENT_MEAS_CORRECTION_CENTIMA(raw_centima)))

#define PSU_CALIBRATE_CURRENT_MA(raw_ma)                                      \
    ((uint16_t)((PSU_CALIBRATE_CURRENT_CENTIMA(                               \
                     PSU_CALIBRATION_LIMIT(                                   \
                         (raw_ma), PSU_CALIBRATION_CURRENT_INPUT_MAX_MA) *     \
                     100UL) +                                                 \
                 50U) /                                                       \
                100U))

/* Voltage command is kept in 0.1 mV units until the final DAC conversion. */
#define PSU_VOLTAGE_COMMAND_CORRECTION_DECIMV(target_mv)                      \
    ((uint32_t)(((PSU_CALIBRATION_LIMIT(                                      \
                       (target_mv), PSU_CALIBRATION_VOLTAGE_TARGET_MAX_MV) *   \
                   PSU_VOLTAGE_COMMAND_GAIN_DEFICIT_PPM * 10UL) +             \
                  (PSU_VOLTAGE_COMMAND_OFFSET_SCALED_MV * 10UL) +             \
                  (PSU_CALIBRATION_SCALE / 2UL)) /                            \
                 PSU_CALIBRATION_SCALE))

#define PSU_VOLTAGE_COMMAND_DECIMV(target_mv)                                 \
    ((uint32_t)((PSU_CALIBRATION_LIMIT(                                       \
                     (target_mv), PSU_CALIBRATION_VOLTAGE_TARGET_MAX_MV) *     \
                 10UL) >                                                      \
                        PSU_VOLTAGE_COMMAND_CORRECTION_DECIMV(target_mv)       \
                    ? ((PSU_CALIBRATION_LIMIT(                                \
                            (target_mv), PSU_CALIBRATION_VOLTAGE_TARGET_MAX_MV) * \
                        10UL) -                                                \
                       PSU_VOLTAGE_COMMAND_CORRECTION_DECIMV(target_mv))       \
                    : 0UL))

/* Current command is kept in 0.001 mA units until the final DAC conversion. */
#define PSU_CURRENT_COMMAND_SCALED(target_ma)                                 \
    ((int32_t)(PSU_CALIBRATION_LIMIT(                                         \
                   (target_ma), PSU_CALIBRATION_CURRENT_TARGET_MAX_MA) *       \
               (uint32_t)PSU_CURRENT_COMMAND_GAIN_PPM) -                      \
     (int32_t)PSU_CURRENT_COMMAND_OFFSET_SCALED_MA)

#define PSU_CURRENT_COMMAND_MILLI_MA(target_ma)                               \
    ((uint32_t)(PSU_CURRENT_COMMAND_SCALED(target_ma) > 0L                    \
                    ? (PSU_CURRENT_COMMAND_SCALED(target_ma) + 500L) / 1000L  \
                    : 0L))

#define PSU_VOLTAGE_DAC_COUNTS(target_mv, dac_full_scale_counts)              \
    ((uint16_t)(((PSU_VOLTAGE_COMMAND_DECIMV(target_mv) *                     \
                  (uint32_t)(dac_full_scale_counts)) + 50000UL) /             \
                 100000UL))

#define PSU_CURRENT_DAC_COUNTS(target_ma, dac_full_scale_counts)              \
    ((uint16_t)(((PSU_CURRENT_COMMAND_MILLI_MA(target_ma) *                   \
                  (uint32_t)(dac_full_scale_counts)) + 50000UL) /             \
                 100000UL))

#endif /* PSU_CALIBRATION_H */
