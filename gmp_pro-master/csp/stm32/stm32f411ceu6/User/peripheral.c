// This is an example of peripheral.c

// GMP basic core header
#include <gmp_core.h>

// user main header
#include "user_main.h"


//////////////////////////////////////////////////////////////////////////
// Devices on the peripheral

// User should setup all the peripheral in this function.
void setup_peripheral(void)
{
}

//////////////////////////////////////////////////////////////////////////
// interrupt functions and callback functions here

// This function should be called in Main ISR
void gmp_base_ctl_step(void);

