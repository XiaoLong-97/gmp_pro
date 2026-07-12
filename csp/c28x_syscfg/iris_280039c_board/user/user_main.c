#include <gmp_core.h>

#include "user_main.h"

#include <oled_driver.h>

#define ENABLE_OLED_UI 1

gpio_halt user_led;

gmp_scheduler_t sched;

gmp_task_t tasks[] = {
    // name,       task,             period(ms), init_phase, is_enabled, pParam
    {"psu_io",    tsk_psu_io,       20,         0,          1,          NULL},
    {"flush_key", tsk_key_flush,    50,         10,         0,          (void*)&ht16k33},
    {"flush_led", tsk_LED_flush,    100,        200,        0,          (void*)&ht16k33},
    {"psu_disp",  tsk_psu_display,  250,        40,         0,          NULL},
    {"startup",   tsk_startup,      250,        0,          1,          NULL},
};

GMP_NO_OPT_PREFIX
void init(void) GMP_NO_OPT_SUFFIX
{
    uint16_t i;

    gmp_scheduler_init(&sched);

    for (i = 0U; i < (uint16_t)(sizeof(tasks) / sizeof(gmp_task_t)); ++i)
        gmp_scheduler_add_task(&sched, &tasks[i]);
}

gmp_task_status_t tsk_startup(gmp_task_t* tsk)
{
    static uint16_t beep_counter = 0U;

    if (beep_counter == 0U)
        beep_on();
    else if (beep_counter == 1U)
        beep_off();
    else if (beep_counter == 2U)
        beep_on();
    else if (beep_counter == 3U)
        beep_off();

    beep_counter += 1U;

    if (beep_counter >= 4U)
    {
        ht16k33_init_t ht16k33_init_struct = {
            .brightness = 15,
            .blink_rate = 0,
            .int_enable = 0,
            .int_act_high = 0
        };
        ec_gt ec = ht16k33_init(&ht16k33, iic_bus, HT16K33_DEFAULT_DEV_ADDR,
                                &ht16k33_init_struct);

        gmp_base_print("HT16K33 init ec = %d\r\n", ec);

        if (ec == GMP_EC_OK)
        {
#if ENABLE_OLED_UI
            oled_init();
#endif
            tsk_psu_display(NULL);
            ec = ht16k33_update_display(&ht16k33);
            gmp_base_print("HT16K33 first display ec = %d\r\n", ec);

            sched.task_list[1]->is_enabled = 1;
            sched.task_list[2]->is_enabled = 1;
            sched.task_list[3]->is_enabled = 1;
        }
        else
        {
            beep_on();
        }

        tsk->is_enabled = 0;
    }

    return GMP_TASK_DONE;
}

GMP_NO_OPT_PREFIX
void mainloop(void) GMP_NO_OPT_SUFFIX
{
    gmp_scheduler_dispatch(&sched);
}
