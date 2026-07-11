#ifndef PSU_UI_LOGIC_H
#define PSU_UI_LOGIC_H

#include <stdint.h>

#define PSU_UI_ENTRY_DIGITS 3U
#define PSU_UI_BLINK_HALF_PERIOD_MS 250U
#define PSU_UI_ENTRY_TIMEOUT_MS 8000U

typedef struct
{
    uint16_t value;
    uint16_t saturated;
} psu_ui_entry_result_t;

static inline psu_ui_entry_result_t psu_ui_clamp_entry(uint32_t value, uint16_t maximum)
{
    psu_ui_entry_result_t result;

    result.saturated = (value > (uint32_t)maximum) ? 1U : 0U;
    result.value = result.saturated ? maximum : (uint16_t)value;
    return result;
}

static inline uint16_t psu_ui_entry_should_restart(uint16_t active, uint16_t saturated,
                                                    uint16_t digit_count)
{
    return (!active || (saturated && digit_count >= PSU_UI_ENTRY_DIGITS)) ? 1U : 0U;
}

static inline uint16_t psu_ui_adjust_saturated(uint16_t value, int16_t steps,
                                                uint16_t unit_step, uint16_t maximum)
{
    int32_t adjusted = (int32_t)value + (int32_t)steps * (int32_t)unit_step;

    if (adjusted < 0)
        adjusted = 0;
    if (adjusted > (int32_t)maximum)
        adjusted = (int32_t)maximum;
    return (uint16_t)adjusted;
}

static inline uint16_t psu_ui_cursor_digit(uint16_t digit_count, uint16_t saturated)
{
    if (saturated || digit_count >= PSU_UI_ENTRY_DIGITS)
        return 0U;
    return digit_count;
}

static inline uint16_t psu_ui_blink_on(uint32_t tick_ms)
{
    return ((tick_ms / PSU_UI_BLINK_HALF_PERIOD_MS) & 1U) ? 0U : 1U;
}

static inline uint16_t psu_ui_cursor_matches(uint16_t entry_active, uint16_t cursor,
                                              uint16_t position)
{
    return (entry_active && cursor == position) ? 1U : 0U;
}

static inline uint16_t psu_ui_cursor_segment(uint16_t segment, uint16_t is_cursor,
                                              uint16_t blink_on)
{
    if (!is_cursor)
        return segment;
    return blink_on ? (uint16_t)(segment | 0x80U) : (uint16_t)(segment & 0x7FU);
}

#endif
