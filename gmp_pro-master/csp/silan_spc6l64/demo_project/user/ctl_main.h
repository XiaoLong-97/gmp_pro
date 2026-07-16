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

// invoke all the peripheral things
#include <xplt.peripheral.h>

// include all the necessary modules


#ifndef _FILE_CTL_MAIN_H_
#define _FILE_CTL_MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    // controller objects prototype


    // periodic callback function things.
    GMP_STATIC_INLINE void ctl_dispatch(void)
    {

    }

#ifndef SPECIFY_ENABLE_CTL_FRAMEWORK_NANO

    // periodic interrupt function

#else // SPECIFY_ENABLE_CTL_FRAMEWORK_NANO is defined


#endif // SPECIFY_ENABLE_CTL_FRAMEWORK_NANO

#ifdef __cplusplus
}
#endif // _cplusplus

#endif // _FILE_CTL_MAIN_H_
