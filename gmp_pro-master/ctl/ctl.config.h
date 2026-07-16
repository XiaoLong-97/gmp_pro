/**
 * @file ctl.config.h
 * @author Javnson (javnson@zju.edu.cn)
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright GMP(c) 2024
 *
 */

// function naming rules
// ctl_ : as prefix
// <action>_ : such as step(calculate one step), get, init, setup, and so on.
// <target object> : such as ramp, sincos, track_pid, and so on.
// _via_<data_source> : [optional] to specify the data source
//                      such as angle, pos_encoder, and so on.
// _<configurations> : [optional] to specify the key point of this function.
//                     such as 2(another implementation), par(parallel topology), and so on.
// Some examples show as follow
// + ctl_init_pid, ctl_setup_pid, ctl_set_pid_parameter, ctl_set_pid_limit
//   from <pid.h>
// + ctl_init_ramp_gen, ctl_setup_ramp_gen, ctl_setup_ramp_gen_via_amp_freq, ctl_step_ramp_gen
//   from <signal_generator.h>
//

#ifndef _FILE_CTRL_CONFIG_H_
#define _FILE_CTRL_CONFIG_H_

//// global math calculation type
// #ifndef GMP_GLOBAL_MATH_T
// #define GMP_GLOBAL_MATH_T float
// #endif // GMP_GLOBAL_MATH_T
//
//// global control parameter type
// #ifndef GMP_CONTROL_PARAM_T
// #define GMP_CONTROL_PARAM_T float
// #endif //GMP_CONTROL_PARAM_T
//
//// calculation type definition
// typedef GMP_GLOBAL_MATH_T gmp_math_t;
// typedef GMP_CONTROL_PARAM_T gmp_ctrl_param_t;

#ifndef DEFAULT_ADC_RESOLUTION
#define DEFAULT_ADC_RESOLUTION ((12))
#endif // DEFAULT_ADC_RESOLUTION

#ifndef DEFAULT_ADC_IQN
#define DEFAULT_ADC_IQN ((12))
#endif // DEFAULT_ADC_IQN

// User should call this function by yourself.
// Or this function may not be called.
#define GMP_SPECIFY_DISABLE_PRESET_INPUT_ROUTINE

// User should call this function by yourself.
// Or this function may not be called.
#define GMP_SPECIFY_DISABLE_PRESET_OUTPUT_ROUTINE

// User should call this function by yourself.
// Or this function may not be called.
#define GMP_SPECIFY_DISABLE_PRESET_REQUEST_ROUTINE

#endif // _FILE_CTRL_CONFIG_H_
