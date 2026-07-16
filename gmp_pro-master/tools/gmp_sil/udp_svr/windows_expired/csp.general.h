/**
 * @file csp.general.h
 * @author Javnson (javnson@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2024-09-30
 * 
 * @copyright Copyright GMP(c) 2024
 * 
 */

#ifndef _FILE_WIN_INCLUDE_H_
#define _FILE_WIN_INCLUDE_H_

// default types
#define GMP_PORT_SIZE_T size_t


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    // Network Support
//#include <winsock2.h>

    // Windows Standard headers
#include <Windows.h>

    // System tick
    typedef struct simulink_timer
    {
        // time from Simulink
        double simulink_time;

        // time from Windows
        SYSTEMTIME system_time;


    };

    // Main ISR function prototype
    void MainISR(void);

#ifdef __cplusplus
}
#endif // __cplusplus


// UDP communication with MATLAB
// UDP server communicate with MATLAB Simulink
#ifdef USING_SIMULINK_UDP_SIMULATE
#include <core/util/udp_svr/udp_svr.hpp>
#endif // USING_SIMULINK_UDP_SIMULATE


// global variables
#ifdef USING_SIMULINK_UDP_SIMULATE
// UDP server object
extern upd_svr_obj_t udp_svr_obj;
#endif // USING_SIMULINK_UDP_SIMULATE


#endif // _FILE_WIN_INCLUDE_H_