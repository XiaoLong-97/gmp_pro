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
#include <core/pm/function_scheduler.h>


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
gmp_task_status_t tsk_lead_param_update(gmp_task_t* tsk);//声明低速更新任务

extern ctl_lead_t dac_a_lead;
extern ctrl_gt dac_a_pu;
extern ctrl_gt dac_a_lead_pu;

extern pwm_channel_t dac_a_lead_pwm;//PWM通道对象
extern ctrl_gt dac_a_lead_duty;//映射后的占空比，0~1
extern pwm_gt dac_a_lead_pwm_cmp;//最终写入PWM比较寄存器的值
extern volatile ctrl_gt dac_a_lead_angle_deg;
extern volatile fast_gt dac_a_lead_angle_dirty;
gmp_task_status_t tsk_lead_param_update(gmp_task_t* tsk);

extern ctl_lead_t dac_a_lead;
extern ctl_lead_t dac_a_lead_shadow;

extern volatile fast_gt dac_a_lead_active;
extern volatile ctrl_gt dac_a_lead_angle_deg;
extern volatile fast_gt dac_a_lead_angle_dirty;
//=================================================================================================
// controller process

// periodic callback function things.
GMP_STATIC_INLINE void ctl_dispatch(void)//对于静态内联的解释：就地展开，不浪费控制时间，节省了函数调用和返回的时间
{
    ctl_lead_t* active_lead;
    ctrl_gt lead_pwm_src;

    if (dac_a_lead_active == 0)
        active_lead = &dac_a_lead;
    else
        active_lead = &dac_a_lead_shadow;
        dac_a_lead_pu = ctl_step_lead(active_lead, dac_a_pu);


    lead_pwm_src = ctl_sat(dac_a_lead_pu, 1.0f, -1.0f);
    dac_a_lead_duty = (lead_pwm_src + 1.0f) / 2.0f;//[-1,1]映射到[0,1]
    dac_a_lead_pwm_cmp = ctl_step_pwm_channel(&dac_a_lead_pwm, dac_a_lead_duty);
}

#ifdef __cplusplus
}
#endif // _cplusplus

#endif // _FILE_CTL_MAIN_H_
