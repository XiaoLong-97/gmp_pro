#include "../csp/c28x_syscfg/iris_280039c_board/user/psu_ui_logic.h"

#define CHECK(code, condition) do { if (!(condition)) return (code); } while (0)

int main(void)
{
    psu_ui_entry_result_t result;

    result = psu_ui_clamp_entry(400U, 100U);
    CHECK(1, result.value == 100U);
    CHECK(2, result.saturated == 1U);
    CHECK(3, psu_ui_entry_should_restart(1U, result.saturated, 3U) == 1U);

    result = psu_ui_clamp_entry(99U, 100U);
    CHECK(4, result.value == 99U);
    CHECK(5, result.saturated == 0U);
    CHECK(6, psu_ui_entry_should_restart(1U, result.saturated, 2U) == 0U);
    CHECK(7, psu_ui_entry_should_restart(0U, 0U, 0U) == 1U);

    result = psu_ui_clamp_entry(10500U, 10000U);
    CHECK(8, result.value == 10000U);
    CHECK(9, result.saturated == 1U);
    CHECK(25, psu_ui_entry_should_restart(1U, result.saturated, 2U) == 0U);

    CHECK(10, psu_ui_adjust_saturated(100U, 1, 1U, 100U) == 100U);
    CHECK(11, psu_ui_adjust_saturated(100U, -1, 1U, 100U) == 99U);
    CHECK(12, psu_ui_adjust_saturated(0U, -1, 1U, 100U) == 0U);

    CHECK(13, psu_ui_cursor_digit(0U, 0U) == 0U);
    CHECK(14, psu_ui_cursor_digit(1U, 0U) == 1U);
    CHECK(15, psu_ui_cursor_digit(2U, 0U) == 2U);
    CHECK(16, psu_ui_cursor_digit(3U, 0U) == 0U);
    CHECK(17, psu_ui_cursor_digit(2U, 1U) == 0U);

    CHECK(18, psu_ui_blink_on(0U) == 1U);
    CHECK(19, psu_ui_blink_on(249U) == 1U);
    CHECK(20, psu_ui_blink_on(250U) == 0U);
    CHECK(21, psu_ui_blink_on(500U) == 1U);

    CHECK(22, psu_ui_cursor_segment(0x06U, 1U, 1U) == 0x86U);
    CHECK(23, psu_ui_cursor_segment(0x86U, 1U, 0U) == 0x06U);
    CHECK(24, psu_ui_cursor_segment(0x06U, 0U, 0U) == 0x06U);

    CHECK(26, psu_ui_cursor_matches(1U, 1U, 1U) == 1U);
    CHECK(27, psu_ui_cursor_matches(1U, 1U, 0U) == 0U);
    CHECK(28, psu_ui_cursor_matches(0U, 0U, 0U) == 0U);
    CHECK(29, PSU_UI_ENTRY_TIMEOUT_MS == 15000U);
    CHECK(30, psu_ui_entry_timed_out(1U, 14999U) == 0U);
    CHECK(31, psu_ui_entry_timed_out(1U, 15001U) == 1U);
    CHECK(32, psu_ui_entry_timed_out(0U, 15001U) == 0U);

    CHECK(33, psu_ui_entry_can_commit(1U, 0U, 3U) == 1U);
    CHECK(34, psu_ui_entry_can_commit(1U, 1U, 3U) == 0U);
    CHECK(35, psu_ui_entry_can_commit(0U, 0U, 3U) == 0U);
    CHECK(36, psu_ui_entry_can_commit(1U, 0U, 0U) == 0U);

    return 0;
}
