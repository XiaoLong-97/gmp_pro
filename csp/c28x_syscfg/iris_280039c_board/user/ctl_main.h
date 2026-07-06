/**
 * @file ctl_main.cpp
 * @author Javnson (javnson@zju.edu.cn)
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright GMP(c) 2024
 *
 */

#include <xplt.peripheral.h>

//=================================================================================================
// include Necessary control modules

#include <ctl/component/interface/adc_channel.h>
#include <ctl/component/interface/pwm_channel.h>
#include <ctl/component/interface/spwm_modulator.h>
#include <ctl/component/intrinsic/discrete/lead_lag.h>
#include <ctl/framework/cia402_state_machine.h>


#ifndef _FILE_CTL_MAIN_H_
#define _FILE_CTL_MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//=================================================================================================
// controller modules with extern




//=================================================================================================
// function prototype

void ctl_init(void);
void ctl_mainloop(void);

void clear_all_controllers();

extern ctl_lead_t dac_a_lead;
extern ctrl_gt dac_a_pu;
extern ctrl_gt dac_a_lead_pu;

//=================================================================================================
// controller process

// periodic callback function things.
GMP_STATIC_INLINE void ctl_dispatch(void)//对于静态内联的解释：就地展开，不浪费控制时间，节省了函数调用和返回的时间
{
    dac_a_lead_pu = ctl_step_lead(&dac_a_lead, dac_a_pu);
}

#ifdef __cplusplus
}
#endif // _cplusplus

#endif // _FILE_CTL_MAIN_H_
