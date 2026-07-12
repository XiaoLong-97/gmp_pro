
// GMP basic core header
#include <gmp_core.h>

// user main header
#include "user_main.h"
#include <stdlib.h>
#include <stdio.h>
#include <oled_driver.h>
#include "psu_measurement.h"
#include "psu_protection.h"
#include "psu_ui_logic.h"
#include "psu_auto_control.h"

// peripheral
#include <core/dev/display/ht16k33.h>
#include <core/dev/gpio/pca9555.h>
#include <core/dev/sensor/hdc1080.h>

//=================================================================================================
// BEEP control function

gpio_halt gpio_beep;

void beep_on()
{
    gmp_hal_gpio_write(gpio_beep, 1);
}

void beep_off()
{
    gmp_hal_gpio_write(gpio_beep, 0);
}

//=================================================================================================
// LED control function

// devices
iic_halt iic_bus;
ht16k33_dev_t ht16k33;
hdc1080_dev_t hdc1080;

// 共阴极数码管段码表
// 包含: 0-9, A-F, H, L, P, U, -, ., 暗, r
const unsigned char led_lut[] = {
    0x3F, // 0  (a,b,c,d,e,f)
    0x06, // 1  (b,c)
    0x5B, // 2  (a,b,d,e,g)
    0x4F, // 3  (a,b,c,d,g)
    0x66, // 4  (b,c,f,g)
    0x6D, // 5  (a,c,d,f,g)
    0x7D, // 6  (a,c,d,e,f,g)
    0x07, // 7  (a,b,c)
    0x7F, // 8  (a,b,c,d,e,f,g)
    0x6F, // 9  (a,b,c,d,f,g)
    0x77, // A  (a,b,c,e,f,g)
    0x7C, // b  (c,d,e,f,g)  - 通常用小写b区分数字8
    0x39, // C  (a,d,e,f)
    0x5E, // d  (b,c,d,e,g)  - 通常用小写d区分数字0
    0x79, // E  (a,d,e,f,g)
    0x71, // F  (a,e,f,g)
    0x76, // H  (b,c,e,f,g)
    0x38, // L  (d,e,f)
    0x73, // P  (a,b,e,f,g)
    0x3E, // U  (b,c,d,e,f)
    0x40, // -  (g) - 负号或横杠
    0x80, // .  (dp) - 小数点
    0x00, // 无显示 (全灭)
    0x50  // r  (e,g)
};

void update_led_content_8byte(ht16k33_dev_t* dev, uint16_t ch1, uint16_t ch2, uint16_t ch3, uint16_t ch4, uint16_t ch5,
                              uint16_t ch6, uint16_t ch7, uint16_t ch8)
{
    dev->display_ram[0] = ch1;
    dev->display_ram[2] = ch2;
    dev->display_ram[4] = ch3;
    dev->display_ram[6] = ch4;
    dev->display_ram[8] = ch5;
    dev->display_ram[10] = ch6;
    dev->display_ram[12] = ch7;
    dev->display_ram[14] = ch8;
    dev->is_dirty = 1;
}


gmp_task_status_t tsk_LED_flush(gmp_task_t* tsk)
{
    ht16k33_dev_t* dev = (ht16k33_dev_t*)tsk->user_data;
    static uint16_t err_count = 0;

    // fresh LED buffer here.
    ec_gt ret = ht16k33_update_display(dev);

    if (ret != GMP_EC_OK)
    {
        if (err_count < 5)
        {
            gmp_base_print("HT16K33 LED flush error: %d\r\n", ret);
            err_count += 1;
        }
        return GMP_TASK_DONE;
    }

    err_count = 0;

    return GMP_TASK_DONE;
}


static void psu_handle_key(fast_gt key_id);

gmp_task_status_t tsk_key_flush(gmp_task_t* tsk)
{
    ht16k33_dev_t* dev = (ht16k33_dev_t*)tsk->user_data;
    static uint16_t err_count = 0;
    static fast_gt last_key_id = 0;
    static time_gt last_key_tick = 0;
    fast_gt key_id = 0;

    ec_gt ret = ht16k33_read_keys(dev, &key_id);

    if (ret != GMP_EC_OK)
    {
        if (err_count < 5)
        {
            gmp_base_print("HT16K33 key scan error: %d\r\n", ret);
            err_count += 1;
        }
        return GMP_TASK_DONE;
    }

    err_count = 0;

    if (key_id != 0)
    {
        if (key_id != last_key_id || gmp_base_get_diff_system_tick(last_key_tick) > 350)
        {
            psu_handle_key(key_id);
            last_key_id = key_id;
            last_key_tick = gmp_base_get_system_tick();
        }
    }

    return GMP_TASK_DONE;
}

//=================================================================================================
// Digitally controlled DC power supply UI

#define PSU_ENABLE_OLED_UI           1
// Keep the board FPGA driver available, but isolate it from this PSU application.
#define PSU_ENABLE_FPGA_LINK         0
#define PSU_ENABLE_GPIO_BUTTONS      1

#define PSU_VSET_MAX_MV              10000U
#define PSU_ISET_MAX_MA              100U
#define PSU_V_FINE_STEP_MV           100
#define PSU_V_COARSE_STEP_MV         500
#define PSU_I_FINE_STEP_MA           1
#define PSU_I_COARSE_STEP_MA         5
#define PSU_DAC_MAX_COUNTS           4095U
#define PSU_DAC_REF_MV               3300U
#define PSU_VSET_DACOUT_MAX_MV       2500U
#define PSU_ISET_DACOUT_MAX_MV       2000U
#define PSU_DAC_FORCE_TEST           0
#define PSU_DACA_FORCE_TEST_COUNTS   1551U
#define PSU_DACB_FORCE_TEST_COUNTS   2482U
#define PSU_BUTTON_DEBOUNCE_MS       120U
#define PSU_GPIO_BUTTON_ACTIVE_LEVEL 0U
#define PSU_OLED_COLUMNS             16U

#define PSU_ENCODER_BASE             IRIS_EQEP1_BASE
#define PSU_ENCODER_MAX_POSITION     10000UL
#define PSU_ENCODER_COUNTS_PER_STEP  4L
#define PSU_ENCODER_REVERSE          0

// The external encoder module routes its S/KEY pin to QEP1 Index on J9.
#define PSU_ENCODER_BUTTON_GPIO      IRIS_EQEP1_EQEPINDEX_GPIO
#define PSU_OUTPUT_BUTTON_GPIO       IRIS_GPIO5
#define PSU_EDIT_BUTTON_GPIO         IRIS_GPIO6

// HT16K33 key_id = COM * 13 + K + 1. These values map board labels SW1..SW17.
#define PSU_KEY_DIGIT_1              8U
#define PSU_KEY_DIGIT_2              9U
#define PSU_KEY_DIGIT_3              1U
#define PSU_KEY_DIGIT_4              2U
#define PSU_KEY_DIGIT_5              3U
#define PSU_KEY_DIGIT_6              4U
#define PSU_KEY_DIGIT_7              5U
#define PSU_KEY_DIGIT_8              6U
#define PSU_KEY_DIGIT_9              7U
#define PSU_KEY_DIGIT_0              21U
#define PSU_KEY_DECIMAL              22U
#define PSU_KEY_CONFIRM              14U
#define PSU_KEY_EDIT_TOGGLE          15U
#define PSU_KEY_OUTPUT_TOGGLE        16U
#define PSU_KEY_STEP_TOGGLE          17U
#define PSU_KEY_CLEAR_ENTRY          18U

#define PSU_VFB_ADC_RESULT_BASE      ADC_CH1_RESULT_BASE
#define PSU_VFB_ADC_SOC              ADC_CH1
#define PSU_IFB_ADC_RESULT_BASE      ADC_CH5_RESULT_BASE
#define PSU_IFB_ADC_SOC              ADC_CH5

#define PSU_FPGA_REG_CONTROL         0x01U
#define PSU_FPGA_REG_VSET            0x02U
#define PSU_FPGA_REG_ISET            0x03U
#define PSU_FPGA_REG_STATUS          0x04U

typedef enum
{
    PSU_MODE_CV = 0,
    PSU_MODE_CC = 1
} psu_mode_t;

typedef enum
{
    PSU_EDIT_VOLTAGE = 0,
    PSU_EDIT_CURRENT = 1
} psu_edit_t;

typedef enum
{
    PSU_STEP_FINE = 0,
    PSU_STEP_COARSE = 1
} psu_step_t;

typedef struct
{
    psu_mode_t mode;
    psu_edit_t edit;
    psu_step_t step;
    fast_gt output_on;
    fast_gt alarm_latched;
    fast_gt alarm_reason;
    uint16_t set_mv;
    uint16_t set_ma;
    uint16_t meas_mv;
    uint16_t meas_ma;
    fast_gt dirty;
} psu_ui_t;

typedef struct
{
    uint16_t pin;
    uint16_t last_level;
    time_gt last_change_tick;
} psu_button_t;

volatile uint16_t psu_vset_dac_counts = 0;
volatile uint16_t psu_iset_dac_counts = 0;
volatile fast_gt psu_output_enabled = 0;
volatile fast_gt psu_dac_force_test_enabled = 0;

static psu_ui_t psu_ui = {
    PSU_MODE_CV,
    PSU_EDIT_VOLTAGE,
    PSU_STEP_FINE,
    0,
    0,
    PSU_PROTECTION_NONE,
    5000U,
    50U,
    0,
    0,
    1
};

static char psu_entry_buf[8];
static uint16_t psu_entry_len = 0;
static fast_gt psu_entry_active = 0;
static fast_gt psu_entry_decimal_seen = 0;
static fast_gt psu_entry_saturated = 0;
static uint16_t psu_entry_digit_count = 0;
static uint16_t psu_entry_preview = 0;
static time_gt psu_entry_tick = 0;

static psu_button_t psu_encoder_button = {PSU_ENCODER_BUTTON_GPIO, 1U, 0};
static psu_button_t psu_output_button = {PSU_OUTPUT_BUTTON_GPIO, 1U, 0};
static psu_button_t psu_edit_button = {PSU_EDIT_BUTTON_GPIO, 1U, 0};

static void psu_init_gpio_buttons(void)
{
#if PSU_ENABLE_GPIO_BUTTONS
    static fast_gt initialized = 0;

    if (initialized)
        return;

    GPIO_setPadConfig(PSU_ENCODER_BUTTON_GPIO, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPadConfig(PSU_OUTPUT_BUTTON_GPIO, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPadConfig(PSU_EDIT_BUTTON_GPIO, GPIO_PIN_TYPE_PULLUP);

    GPIO_setQualificationMode(PSU_ENCODER_BUTTON_GPIO, GPIO_QUAL_3SAMPLE);
    GPIO_setQualificationMode(PSU_OUTPUT_BUTTON_GPIO, GPIO_QUAL_3SAMPLE);
    GPIO_setQualificationMode(PSU_EDIT_BUTTON_GPIO, GPIO_QUAL_3SAMPLE);

    GPIO_setDirectionMode(PSU_ENCODER_BUTTON_GPIO, GPIO_DIR_MODE_IN);
    GPIO_setDirectionMode(PSU_OUTPUT_BUTTON_GPIO, GPIO_DIR_MODE_IN);
    GPIO_setDirectionMode(PSU_EDIT_BUTTON_GPIO, GPIO_DIR_MODE_IN);

    psu_encoder_button.last_level = (uint16_t)GPIO_readPin(psu_encoder_button.pin);
    psu_output_button.last_level = (uint16_t)GPIO_readPin(psu_output_button.pin);
    psu_edit_button.last_level = (uint16_t)GPIO_readPin(psu_edit_button.pin);

    initialized = 1;
#else
    return;
#endif
}

static void psu_entry_reset(void);
static void psu_handle_key(fast_gt key_id);


static uint16_t psu_dacout_mv_to_counts(uint16_t dacout_mv)
{
    if (dacout_mv >= PSU_DAC_REF_MV)
        return PSU_DAC_MAX_COUNTS;

    return (uint16_t)(((uint32_t)dacout_mv * PSU_DAC_MAX_COUNTS +
                       (uint32_t)(PSU_DAC_REF_MV / 2U)) / PSU_DAC_REF_MV);
}

static uint16_t psu_scale_to_dac(uint16_t value, uint16_t full_scale, uint16_t dacout_full_scale_mv)
{
    uint16_t dac_full_scale_counts;

    if (full_scale == 0U)
        return 0U;

    dac_full_scale_counts = psu_dacout_mv_to_counts(dacout_full_scale_mv);
    return (uint16_t)(((uint32_t)value * dac_full_scale_counts +
                       (uint32_t)(full_scale / 2U)) / full_scale);
}
static void psu_sync_dac_globals(void)
{
#if PSU_DAC_FORCE_TEST
    psu_vset_dac_counts = PSU_DACA_FORCE_TEST_COUNTS;
    psu_iset_dac_counts = PSU_DACB_FORCE_TEST_COUNTS;
    psu_dac_force_test_enabled = 1;
    psu_output_enabled = 0;
    return;
#endif

    psu_dac_force_test_enabled = 0;
    psu_vset_dac_counts = psu_scale_to_dac(psu_ui.set_mv, PSU_VSET_MAX_MV, PSU_VSET_DACOUT_MAX_MV);
    psu_iset_dac_counts = psu_scale_to_dac(psu_ui.set_ma, PSU_ISET_MAX_MA, PSU_ISET_DACOUT_MAX_MV);
    psu_output_enabled = (psu_ui.output_on && !psu_ui.alarm_latched) ? 1 : 0;
}

static void psu_write_dac_outputs(void)
{
    DAC_enableOutput(IRIS_DACA_BASE);
    DAC_enableOutput(IRIS_DACB_BASE);

    if (psu_dac_force_test_enabled || psu_output_enabled)
    {
        DAC_setShadowValue(IRIS_DACA_BASE, psu_vset_dac_counts);
        DAC_setShadowValue(IRIS_DACB_BASE, psu_iset_dac_counts);
    }
    else
    {
        DAC_setShadowValue(IRIS_DACA_BASE, 0U);
        DAC_setShadowValue(IRIS_DACB_BASE, 0U);
    }
}

static void psu_set_dirty(void)
{
    psu_ui.dirty = 1;
    psu_sync_dac_globals();
    psu_write_dac_outputs();
}

static void psu_toggle_step(void)
{
    psu_ui.step = (psu_ui.step == PSU_STEP_FINE) ? PSU_STEP_COARSE : PSU_STEP_FINE;
    psu_entry_reset();
    psu_set_dirty();
}

static void psu_toggle_edit(void)
{
    psu_ui.edit = (psu_ui.edit == PSU_EDIT_VOLTAGE) ? PSU_EDIT_CURRENT : PSU_EDIT_VOLTAGE;
    psu_entry_reset();
    psu_set_dirty();
}

static void psu_toggle_output(void)
{
    if (psu_ui.alarm_latched)
    {
        psu_ui.alarm_latched = 0;
        psu_ui.alarm_reason = PSU_PROTECTION_NONE;
        psu_ui.output_on = 0;
        beep_off();
    }
    else
    {
        psu_ui.output_on = psu_ui.output_on ? 0 : 1;
    }

    psu_entry_reset();
    psu_set_dirty();
}

static void psu_adjust_selected(int16_t steps)
{
    uint16_t unit_step;

    if (steps == 0)
        return;

    psu_entry_reset();
    if (psu_ui.edit == PSU_EDIT_VOLTAGE)
    {
        unit_step = (psu_ui.step == PSU_STEP_FINE) ? PSU_V_FINE_STEP_MV : PSU_V_COARSE_STEP_MV;
        psu_ui.set_mv = psu_ui_adjust_saturated(psu_ui.set_mv, steps, unit_step, PSU_VSET_MAX_MV);
    }
    else
    {
        unit_step = (psu_ui.step == PSU_STEP_FINE) ? PSU_I_FINE_STEP_MA : PSU_I_COARSE_STEP_MA;
        psu_ui.set_ma = psu_ui_adjust_saturated(psu_ui.set_ma, steps, unit_step, PSU_ISET_MAX_MA);
    }

    psu_set_dirty();
}

static int16_t psu_key_to_digit(fast_gt key_id)
{
    switch (key_id)
    {
    case PSU_KEY_DIGIT_0: return 0;
    case PSU_KEY_DIGIT_1: return 1;
    case PSU_KEY_DIGIT_2: return 2;
    case PSU_KEY_DIGIT_3: return 3;
    case PSU_KEY_DIGIT_4: return 4;
    case PSU_KEY_DIGIT_5: return 5;
    case PSU_KEY_DIGIT_6: return 6;
    case PSU_KEY_DIGIT_7: return 7;
    case PSU_KEY_DIGIT_8: return 8;
    case PSU_KEY_DIGIT_9: return 9;
    default: return -1;
    }
}

static void psu_entry_reset(void)
{
    uint16_t i;

    for (i = 0; i < sizeof(psu_entry_buf); ++i)
        psu_entry_buf[i] = 0;

    psu_entry_len = 0;
    psu_entry_active = 0;
    psu_entry_decimal_seen = 0;
    psu_entry_saturated = 0;
    psu_entry_digit_count = 0;
    psu_entry_preview = 0;
}

static void psu_entry_prepare(void)
{
    if (psu_ui_entry_should_restart((uint16_t)psu_entry_active,
                                    (uint16_t)psu_entry_saturated,
                                    psu_entry_digit_count) ||
        psu_ui_entry_timed_out((uint16_t)psu_entry_active,
                               (uint32_t)gmp_base_get_diff_system_tick(psu_entry_tick)))
        psu_entry_reset();

    psu_entry_active = 1;
    psu_entry_tick = gmp_base_get_system_tick();
}

static void psu_apply_entry(void)
{
    uint16_t i;
    uint32_t whole = 0;
    uint16_t tenth = 0;
    fast_gt after_decimal = 0;
    fast_gt got_tenth = 0;
    psu_ui_entry_result_t result;

    if (psu_entry_len == 0)
        return;

    for (i = 0; i < psu_entry_len; ++i)
    {
        char c = psu_entry_buf[i];

        if (c == '.')
        {
            after_decimal = 1;
            continue;
        }

        if (c < '0' || c > '9')
            continue;

        if (psu_ui.edit == PSU_EDIT_VOLTAGE)
        {
            if (!after_decimal)
            {
                whole = whole * 10U + (uint32_t)(c - '0');
            }
            else if (!got_tenth)
            {
                tenth = (uint16_t)(c - '0');
                got_tenth = 1;
            }
        }
        else
        {
            whole = whole * 10U + (uint32_t)(c - '0');
        }
    }

    if (psu_ui.edit == PSU_EDIT_VOLTAGE)
    {
        result = psu_ui_clamp_entry(whole * 1000U + (uint32_t)tenth * 100U, PSU_VSET_MAX_MV);
        psu_entry_preview = result.value;
        psu_entry_saturated = (fast_gt)result.saturated;
    }
    else
    {
        result = psu_ui_clamp_entry(whole, PSU_ISET_MAX_MA);
        psu_entry_preview = result.value;
        psu_entry_saturated = (fast_gt)result.saturated;
    }

    psu_ui.dirty = 1;
}

static void psu_entry_confirm(void)
{
    if (!psu_ui_entry_can_commit((uint16_t)psu_entry_active,
                                 (uint16_t)psu_entry_saturated,
                                 psu_entry_len))
        return;

    if (psu_ui.edit == PSU_EDIT_VOLTAGE)
        psu_ui.set_mv = psu_entry_preview;
    else
        psu_ui.set_ma = psu_entry_preview;

    psu_entry_reset();
    psu_set_dirty();
}

static void psu_entry_append_digit(uint16_t digit)
{
    if (psu_entry_digit_count >= PSU_UI_ENTRY_DIGITS)
        psu_entry_reset();

    psu_entry_prepare();

    if (psu_entry_len >= sizeof(psu_entry_buf) - 1U)
        return;

    psu_entry_buf[psu_entry_len++] = (char)('0' + digit);
    psu_entry_buf[psu_entry_len] = 0;
    psu_entry_digit_count += 1U;
    psu_apply_entry();
}

static void psu_entry_append_decimal(void)
{
    if (psu_ui.edit != PSU_EDIT_VOLTAGE)
    {
        psu_toggle_step();
        return;
    }

    psu_entry_prepare();

    if (psu_entry_decimal_seen || psu_entry_len >= sizeof(psu_entry_buf) - 1U)
        return;

    psu_entry_buf[psu_entry_len++] = '.';
    psu_entry_buf[psu_entry_len] = 0;
    psu_entry_decimal_seen = 1;
    psu_apply_entry();
}

static void psu_handle_key(fast_gt key_id)
{
    int16_t digit = psu_key_to_digit(key_id);

    if (digit >= 0)
    {
        psu_entry_append_digit((uint16_t)digit);
        return;
    }

    switch (key_id)
    {
    case PSU_KEY_CONFIRM:
        psu_entry_confirm();
        break;
    case PSU_KEY_DECIMAL:
        psu_entry_append_decimal();
        break;
    case PSU_KEY_EDIT_TOGGLE:
        psu_toggle_edit();
        break;
    case PSU_KEY_OUTPUT_TOGGLE:
        psu_toggle_output();
        break;
    case PSU_KEY_STEP_TOGGLE:
        psu_toggle_step();
        break;
    case PSU_KEY_CLEAR_ENTRY:
        psu_entry_reset();
        psu_set_dirty();
        break;
    default:
        gmp_base_print("Key: %d\r\n", key_id);
        break;
    }
}

static int16_t psu_read_encoder_steps(void)
{
    static fast_gt initialized = 0;
    static uint32_t last_pos = 0;
    static int32_t accum = 0;
    uint32_t pos;
    int32_t delta;
    int16_t steps = 0;

    if (!initialized)
    {
        EQEP_setPositionCounterConfig(PSU_ENCODER_BASE, EQEP_POSITION_RESET_MAX_POS,
                                      (uint32_t)PSU_ENCODER_MAX_POSITION);
        EQEP_setPosition(PSU_ENCODER_BASE, 0U);
        last_pos = 0U;
        accum = 0;
        initialized = 1;
        return 0;
    }

    pos = EQEP_getPosition(PSU_ENCODER_BASE);
    delta = (int32_t)pos - (int32_t)last_pos;
    if (delta > (int32_t)(PSU_ENCODER_MAX_POSITION / 2UL))
        delta -= (int32_t)(PSU_ENCODER_MAX_POSITION + 1UL);
    else if (delta < -((int32_t)(PSU_ENCODER_MAX_POSITION / 2UL)))
        delta += (int32_t)(PSU_ENCODER_MAX_POSITION + 1UL);

    last_pos = pos;
    accum += delta;

    while (accum >= PSU_ENCODER_COUNTS_PER_STEP)
    {
        steps += 1;
        accum -= PSU_ENCODER_COUNTS_PER_STEP;
    }

    while (accum <= -PSU_ENCODER_COUNTS_PER_STEP)
    {
        steps -= 1;
        accum += PSU_ENCODER_COUNTS_PER_STEP;
    }

#if PSU_ENCODER_REVERSE
    steps = -steps;
#endif

    return steps;
}

static fast_gt psu_button_pressed(psu_button_t* button)
{
#if PSU_ENABLE_GPIO_BUTTONS
    uint16_t level = (uint16_t)GPIO_readPin(button->pin);

    if (level != button->last_level && gmp_base_get_diff_system_tick(button->last_change_tick) > PSU_BUTTON_DEBOUNCE_MS)
    {
        button->last_level = level;
        button->last_change_tick = gmp_base_get_system_tick();
        if (level == PSU_GPIO_BUTTON_ACTIVE_LEVEL)
            return 1;
    }
#else
    GMP_UNUSED_VAR(button);
#endif

    return 0;
}

static void psu_poll_buttons(void)
{
    psu_init_gpio_buttons();

    if (psu_button_pressed(&psu_encoder_button))
        psu_toggle_step();

    if (psu_button_pressed(&psu_output_button))
        psu_toggle_output();

    if (psu_button_pressed(&psu_edit_button))
        psu_toggle_edit();
}

static void psu_read_feedback(void)
{
    static psu_adc_filter_t voltage_filter = {0U, 0U};
    static psu_adc_filter_t current_filter = {0U, 0U};
    uint16_t raw_v;
    uint16_t raw_i;
    uint16_t filtered_v;
    uint16_t filtered_i;

    raw_v = (uint16_t)ADC_readResult(PSU_VFB_ADC_RESULT_BASE, PSU_VFB_ADC_SOC);
    raw_i = (uint16_t)ADC_readResult(PSU_IFB_ADC_RESULT_BASE, PSU_IFB_ADC_SOC);

    filtered_v = psu_adc_filter_update(&voltage_filter, raw_v);
    filtered_i = psu_adc_filter_update(&current_filter, raw_i);

    psu_ui.meas_mv = PSU_ADC_VOUT_MV_FROM_COUNTS(filtered_v);
    psu_ui.meas_ma = PSU_ADC_IOUT_MA_FROM_COUNTS(filtered_i);
}

static void psu_update_auto_mode(void)
{
    psu_mode_t next_mode;

    if (!psu_ui.output_on || psu_ui.alarm_latched)
        next_mode = PSU_MODE_CV;
    else
        next_mode = (psu_mode_t)psu_auto_next_mode((uint16_t)psu_ui.mode,
                                                   psu_ui.meas_mv, psu_ui.meas_ma,
                                                   psu_ui.set_mv, psu_ui.set_ma);

    if (next_mode != psu_ui.mode)
    {
        psu_ui.mode = next_mode;
        psu_ui.dirty = 1;
    }
}

static void psu_trip_alarm(fast_gt reason)
{
    psu_ui.output_on = 0;
    psu_ui.alarm_latched = 1;
    psu_ui.alarm_reason = reason;
    beep_on();
    psu_set_dirty();
}

static void psu_check_protection(void)
{
    fast_gt reason;

    if (!psu_ui.output_on || psu_ui.alarm_latched)
        return;

    reason = PSU_PROTECTION_REASON(psu_ui.meas_mv, psu_ui.meas_ma);
    if (reason != PSU_PROTECTION_NONE)
        psu_trip_alarm(reason);
}

static void psu_update_board_leds(void)
{
    fast_gt alarm_led_on = 0;

    if (psu_ui.alarm_latched)
        alarm_led_on = ((gmp_base_get_system_tick() / 250U) & 1U) ? 1 : 0;

    /* The board LEDs are wired to 3.3 V through resistors, so low means on. */
    gmp_hal_gpio_write(IRIS_LED1, psu_output_enabled ? 0 : 1);
    gmp_hal_gpio_write(IRIS_LED2, alarm_led_on ? 0 : 1);
}

static void psu_sync_fpga(void)
{
#if PSU_ENABLE_FPGA_LINK
    uint16_t ctrl = 0;

    if (psu_output_enabled)
        ctrl |= 0x0001U;
    if (psu_ui.mode == PSU_MODE_CC)
        ctrl |= 0x0002U;
    if (psu_ui.alarm_latched)
        ctrl |= 0x0004U;
    if (psu_ui.edit == PSU_EDIT_CURRENT)
        ctrl |= 0x0008U;
    if (psu_ui.step == PSU_STEP_COARSE)
        ctrl |= 0x0010U;

    SPI_writeReg(PSU_FPGA_REG_CONTROL, ctrl);
    SPI_writeReg(PSU_FPGA_REG_VSET, psu_vset_dac_counts);
    SPI_writeReg(PSU_FPGA_REG_ISET, psu_iset_dac_counts);
    SPI_writeReg(PSU_FPGA_REG_STATUS, ((uint16_t)psu_ui.meas_ma << 8) | (uint16_t)(psu_ui.meas_mv / 100U));
#endif
}

static void psu_render_led_voltage(uint16_t mv)
{
    uint16_t whole = mv / 1000U;
    uint16_t tenth = (mv % 1000U) / 100U;
    uint16_t cursor = psu_ui_led_cursor_digit(
        psu_ui_cursor_digit(psu_entry_digit_count, (uint16_t)psu_entry_saturated));
    uint16_t blink = psu_ui_blink_on((uint32_t)gmp_base_get_system_tick());
    uint16_t digit0 = (whole >= 10U) ? led_lut[1] : led_lut[22];
    uint16_t digit1 = led_lut[whole % 10U] | 0x80U;
    uint16_t digit2 = led_lut[tenth];

    digit0 = psu_ui_cursor_segment(
        digit0, psu_ui_cursor_matches((uint16_t)psu_entry_active, cursor, 0U), blink);
    digit1 = psu_ui_cursor_segment(
        digit1, psu_ui_cursor_matches((uint16_t)psu_entry_active, cursor, 1U), blink);
    digit2 = psu_ui_cursor_segment(
        digit2, psu_ui_cursor_matches((uint16_t)psu_entry_active, cursor, 2U), blink);

    update_led_content_8byte(
        &ht16k33,
        led_lut[19],
        led_lut[22],
        digit0,
        digit1,
        digit2,
        led_lut[22],
        (psu_ui.output_on && !psu_ui.alarm_latched) ? led_lut[0] : led_lut[20],
        psu_ui.alarm_latched ? led_lut[10] : led_lut[22]
    );
}

static void psu_render_led_current(uint16_t ma)
{
    uint16_t cursor = psu_ui_led_cursor_digit(
        psu_ui_cursor_digit(psu_entry_digit_count, (uint16_t)psu_entry_saturated));
    uint16_t blink = psu_ui_blink_on((uint32_t)gmp_base_get_system_tick());
    uint16_t digit0 = (ma >= 100U) ? led_lut[(ma / 100U) % 10U] : led_lut[22];
    uint16_t digit1 = (ma >= 10U) ? led_lut[(ma / 10U) % 10U] : led_lut[22];
    uint16_t digit2 = led_lut[ma % 10U];

    digit0 = psu_ui_cursor_segment(
        digit0, psu_ui_cursor_matches((uint16_t)psu_entry_active, cursor, 0U), blink);
    digit1 = psu_ui_cursor_segment(
        digit1, psu_ui_cursor_matches((uint16_t)psu_entry_active, cursor, 1U), blink);
    digit2 = psu_ui_cursor_segment(
        digit2, psu_ui_cursor_matches((uint16_t)psu_entry_active, cursor, 2U), blink);

    update_led_content_8byte(
        &ht16k33,
        led_lut[10],
        led_lut[22],
        digit0,
        digit1,
        digit2,
        led_lut[22],
        (psu_ui.output_on && !psu_ui.alarm_latched) ? led_lut[0] : led_lut[20],
        psu_ui.alarm_latched ? led_lut[10] : led_lut[22]
    );
}

static void psu_render_led(void)
{
    uint16_t display_value;

    if (psu_ui.alarm_latched)
    {
        update_led_content_8byte(
            &ht16k33,
            led_lut[10], led_lut[17], led_lut[10], led_lut[23],
            led_lut[22], led_lut[22], led_lut[22], led_lut[22]);
    }
    else if (psu_ui.edit == PSU_EDIT_VOLTAGE)
    {
        display_value = psu_entry_active ? psu_entry_preview : psu_ui.set_mv;
        psu_render_led_voltage(display_value);
    }
    else
    {
        display_value = psu_entry_active ? psu_entry_preview : psu_ui.set_ma;
        psu_render_led_current(display_value);
    }
}
static void psu_oled_show_line(uint8_t y_page, const char* text)
{
#if PSU_ENABLE_OLED_UI
    char padded[PSU_OLED_COLUMNS + 1U];
    uint16_t i;

    for (i = 0U; i < PSU_OLED_COLUMNS; ++i)
        padded[i] = ' ';
    padded[PSU_OLED_COLUMNS] = '\0';

    for (i = 0U; i < PSU_OLED_COLUMNS && text[i] != '\0'; ++i)
        padded[i] = text[i];

    oled_show_str(0, y_page, padded);
#else
    GMP_UNUSED_VAR(y_page);
    GMP_UNUSED_VAR(text);
#endif
}

static void psu_render_oled(void)
{
#if PSU_ENABLE_OLED_UI
    static fast_gt oled_cleared = 0;
    char line[24];
    uint16_t measured_centivolts;
    uint16_t display_mv = (psu_entry_active && psu_ui.edit == PSU_EDIT_VOLTAGE)
                              ? psu_entry_preview : psu_ui.set_mv;
    uint16_t display_ma = (psu_entry_active && psu_ui.edit == PSU_EDIT_CURRENT)
                              ? psu_entry_preview : psu_ui.set_ma;
    const char* voltage_label = (psu_entry_active && psu_ui.edit == PSU_EDIT_VOLTAGE)
                                    ? "Unew" : "Uset";
    const char* current_label = (psu_entry_active && psu_ui.edit == PSU_EDIT_CURRENT)
                                    ? "Inew" : "Iset";
    uint16_t cursor = psu_ui_cursor_digit(psu_entry_digit_count, (uint16_t)psu_entry_saturated);
    uint16_t blink = psu_ui_blink_on((uint32_t)gmp_base_get_system_tick());

    if (!oled_cleared)
    {
        oled_clear();
        oled_cleared = 1;
    }

    sprintf(line, "%s %s %s", (psu_ui.mode == PSU_MODE_CV) ? "CV" : "CC",
            (psu_output_enabled) ? "ON" : "OFF",
            (psu_ui.step == PSU_STEP_FINE) ? "FINE" : "COARSE");
    psu_oled_show_line(0, line);

    sprintf(line, "%s %2u.%1uV", voltage_label, (unsigned int)(display_mv / 1000U),
            (unsigned int)((display_mv % 1000U) / 100U));
    if (psu_ui.edit == PSU_EDIT_VOLTAGE && psu_entry_active && blink)
        line[(cursor == 0U) ? 5U : ((cursor == 1U) ? 6U : 8U)] = '_';
    psu_oled_show_line(1, line);

    measured_centivolts = (uint16_t)((psu_ui.meas_mv + 5U) / 10U);
    sprintf(line, "Uout %2u.%02uV", (unsigned int)(measured_centivolts / 100U),
            (unsigned int)(measured_centivolts % 100U));
    psu_oled_show_line(2, line);

    sprintf(line, "%s %3umA", current_label, (unsigned int)display_ma);
    if (psu_ui.edit == PSU_EDIT_CURRENT && psu_entry_active && blink)
        line[5U + cursor] = '_';
    psu_oled_show_line(3, line);

    sprintf(line, "Iout %3umA", (unsigned int)psu_ui.meas_ma);
    psu_oled_show_line(4, line);

    if (psu_entry_active && psu_entry_saturated)
        psu_oled_show_line(6, "ENTRY:RANGE ERR");
    else if (psu_ui.alarm_reason == PSU_PROTECTION_OVERCURRENT)
        psu_oled_show_line(6, "ALARM:OVER I");
    else if (psu_ui.alarm_reason == PSU_PROTECTION_OVERVOLTAGE)
        psu_oled_show_line(6, "ALARM:OVER V");
    else if (psu_ui.edit == PSU_EDIT_VOLTAGE)
        psu_oled_show_line(6, "EDIT:U SET");
    else
        psu_oled_show_line(6, "EDIT:I SET");
#endif
}
gmp_task_status_t tsk_psu_display(gmp_task_t* tsk)
{
    GMP_UNUSED_VAR(tsk);

    if (psu_ui_entry_timed_out((uint16_t)psu_entry_active,
                               (uint32_t)gmp_base_get_diff_system_tick(psu_entry_tick)))
        psu_entry_reset();

    psu_render_led();
    psu_render_oled();
    psu_ui.dirty = 0;

    return GMP_TASK_DONE;
}

//=================================================================================================
// FPGA and slow UI service task

gmp_task_status_t tsk_psu_io(gmp_task_t* tsk)
{
    int16_t encoder_steps;

    GMP_UNUSED_VAR(tsk);

    encoder_steps = psu_read_encoder_steps();
    if (encoder_steps != 0)
        psu_adjust_selected(encoder_steps);

    psu_poll_buttons();
    psu_read_feedback();
    psu_update_auto_mode();
    psu_check_protection();
    psu_sync_dac_globals();
    psu_write_dac_outputs();
    psu_update_board_leds();
    psu_sync_fpga();

    return GMP_TASK_DONE;
}
