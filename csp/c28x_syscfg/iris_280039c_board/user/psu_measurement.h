#ifndef PSU_MEASUREMENT_H
#define PSU_MEASUREMENT_H

#include <stdint.h>

/* TMS320F280039C ADC and confirmed external feedback scaling. */
#define PSU_ADC_MAX_COUNTS                    4095UL
#define PSU_ADC_REF_MV                        3300UL
#define PSU_VOLTAGE_FEEDBACK_GAIN             4UL
#define PSU_CURRENT_FEEDBACK_MV_PER_MA        20UL
#define PSU_ADC_FILTER_DIVISOR                 4UL

/* Vout = Vadc * 4, with one round-to-nearest operation. */
#define PSU_ADC_VOUT_MV_FROM_COUNTS(raw_counts)                                      \
    ((uint16_t)((((uint32_t)(raw_counts) * PSU_ADC_REF_MV *                         \
                   PSU_VOLTAGE_FEEDBACK_GAIN) + (PSU_ADC_MAX_COUNTS / 2UL)) /       \
                 PSU_ADC_MAX_COUNTS))

/* Vfi is 20 mV/mA. Preserve 0.01 mA resolution for software calibration. */
#define PSU_ADC_IOUT_CENTIMA_FROM_COUNTS(raw_counts)                                \
    ((uint16_t)((((uint32_t)(raw_counts) * PSU_ADC_REF_MV * 100UL) +                \
                  ((PSU_ADC_MAX_COUNTS * PSU_CURRENT_FEEDBACK_MV_PER_MA) / 2UL)) /  \
                 (PSU_ADC_MAX_COUNTS * PSU_CURRENT_FEEDBACK_MV_PER_MA)))

#define PSU_ADC_IOUT_MA_FROM_COUNTS(raw_counts)                                     \
    ((uint16_t)((PSU_ADC_IOUT_CENTIMA_FROM_COUNTS(raw_counts) + 50U) / 100U))

/* Quarter-step IIR. One/two-count changes form a small display deadband. */
#define PSU_ADC_FILTER_BLEND(previous, sample)                                       \
    ((uint16_t)(((uint16_t)(sample) > (uint16_t)(previous))                         \
                    ? ((uint16_t)(previous) +                                       \
                       (uint16_t)((((uint32_t)(sample) - (uint32_t)(previous)) +     \
                                   1UL) / PSU_ADC_FILTER_DIVISOR))                  \
                    : ((uint16_t)(previous) -                                       \
                       (uint16_t)((((uint32_t)(previous) - (uint32_t)(sample)) +     \
                                   1UL) / PSU_ADC_FILTER_DIVISOR))))

typedef struct
{
    uint16_t value;
    uint16_t initialized;
} psu_adc_filter_t;

static inline uint16_t psu_adc_filter_update(psu_adc_filter_t* filter, uint16_t sample)
{
    if (!filter->initialized)
    {
        filter->value = sample;
        filter->initialized = 1U;
    }
    else
    {
        filter->value = PSU_ADC_FILTER_BLEND(filter->value, sample);
    }

    return filter->value;
}

#endif /* PSU_MEASUREMENT_H */
