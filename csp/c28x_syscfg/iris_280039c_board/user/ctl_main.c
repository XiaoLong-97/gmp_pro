
//
// THIS IS A DEMO SOURCE CODE FOR GMP LIBRARY.
//
// User should define your own controller objects,
// and initilize them.
//
// User should implement a ctl loop function, this
// function would be called every main loop.
//
// User should implement a state machine if you are using
// Controller Nanon framework.
//

#include <gmp_core.h>

#include <ctrl_settings.h>

#include "ctl_main.h"

#include <xplt.peripheral.h>

#include <core/pm/function_scheduler.h>

#include <core/dev/pil_core.h>

//=================================================================================================
// global controller variables
ctl_lead_t dac_a_lead;
ctrl_gt dac_a_pu = 0;
ctrl_gt dac_a_lead_pu = 0;

//=================================================================================================
// CTL initialize routine

void ctl_init()
{
        ctl_init_lead_form3(
            &dac_a_lead,
            CTL_PARAM_CONST_PI / 4.0f,
            100.0f,
            CONTROLLER_FREQUENCY
        );
}

//=================================================================================================
// CTL endless loop routine

void ctl_mainloop(void)
{
    return;
}


void gmp_pil_sim_step(const gmp_sim_rx_buf_t* rx, gmp_sim_tx_buf_t* tx)
{

}

//=================================================================================================
// Controller Tasks

//=================================================================================================
// CiA402 default callback routine

