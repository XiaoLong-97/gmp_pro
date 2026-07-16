
// This is an example file for GMP project with Controller template.

// GMP basic core header
#include <gmp_core.h>

// Controller Template Library
#include <ctl/ctl_core.h>

// user main header
#include "user_main.h"

#if defined SPECIFY_ENABLE_GMP_CTL

//////////////////////////////////////////////////////////////////////////
// initialize routine here

void ctl_init(void)
{

    return;
}

//////////////////////////////////////////////////////////////////////////
// endless loop function here

void ctl_mainloop(void)
{
    return;
}


//////////////////////////////////////////////////////////////////////////
// Controller Framework

// input stage routine
void ctl_input_stage_routine(ctl_object_nano_t* pctl_obj)
{
    
}


// output stage routine
void ctl_output_stage_routine(ctl_object_nano_t* pctl_obj)
{
}


// request stage routine
void ctl_request_stage_routine(ctl_object_nano_t* pctl_obj)
{
    
}


// controller output enable
void controller_output_enable(ctl_object_nano_t* pctl_obj)
{
    
}


// controller output disable
void controller_output_disable(ctl_object_nano_t* pctl_obj)
{
    
}

#endif // SPECIFY_ENABLE_GMP_CTL
