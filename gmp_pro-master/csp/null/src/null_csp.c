#include <gmp_core.h>

// System Tick
time_gt system_tick = 0;

// User should invoke this function to get time (system tick).
time_gt gmp_base_get_system_tick(void)
{
    return system_tick;
}

// This function may be called and used to initialize all the peripheral.
void gmp_csp_startup(void)
{
}

void gmp_csp_loop()
{
}

void gmp_csp_post_process()
{
}
