/**
 * @file windows_simulate.cpp
 * @author Javnson (javnson@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2024-09-30
 * 
 * @copyright Copyright GMP(c) 2024
 * 
 */


#include <windows.h>

#include <core/gmp_core.hpp>

using std::cout;

std::thread ctl_thread;

// Model Interface: receive package
// Controller Interface: transmit package
#pragma pack(1)
typedef struct _tag_receive_package_t
{

    double time;

    // other informations are ignored here.
    // ...

} receive_package_t;

extern receive_package_t rx_pak;

// Main ISR function prototype
extern "C" void MainISR(void);

// Global variables

#ifdef USING_SIMULINK_UDP_SIMULATE
// UDP server object
upd_svr_obj_t udp_svr_obj;

#endif // USING_SIMULINK_UDP_SIMULATE

time_gt gmp_port_system_tick()
{
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    return sys.wMinute * 60 + sys.wSecond;
}

time_gt gmp_base_get_system_tick()
{
    return (time_gt)(rx_pak.time * 1000);
}

void gmp_port_system_stuck(void)
{
}

// This function should be implemented by user,
// Every Loop routine, this function would be called.
// And user should ensure that the function has only one thing is to feed the watchdog
void gmp_hal_wd_feed()
{
#if defined SPECIFY_ENABLE_FEED_WATCHDOG


#endif // SPECIFY_ENABLE_FEED_WATCHDOG
}


void gmp_csp_startup(void)
{
    if (init_udp_server() == 1)
    {
        printf("Error, Cannot Establish UDP connection. Please check your configurations, or restart later.\n");
        exit(1);
    }

    // create a new thread for controller
}

// in order to correct control flow direction
// This function may send one package first
// This value is the initial value from user.
//
void csp_post_process(void)
{
#ifdef USING_SIMULINK_UDP_SIMULATE
    if (periodic_transmit_routine(&udp_svr_obj) == 1)
    {
        exit(1);
    }
#endif // USING_SIMULINK_UDP_SIMULATE
}

int gmp_ctl_dispatch(void)
{
#ifdef USING_SIMULINK_UDP_SIMULATE
    if (periodic_recv_routine(&udp_svr_obj) == 1)
    {
        return 1;
    }
#endif // USING_SIMULINK_UDP_SIMULATE

    // User logic will be called here
    ctl_dispatch();

#ifdef USING_SIMULINK_UDP_SIMULATE
    if (periodic_transmit_routine(&udp_svr_obj) == 1)
    {
        return 1;
    }
#endif // USING_SIMULINK_UDP_SIMULATE

    return 0;
}

// Resources need to release
void gmp_exit_routine(void)
{
    release_udp_server();

    cout << "[INFO] All process has done. " << udp_svr_obj.recv_bytes << " bytes are received, "
         << udp_svr_obj.send_bytes << " bytes are sent." << std::endl;
    cout << "[INFO] User-friendly view: receive: " << (double)udp_svr_obj.recv_bytes / 1024
         << " kB, transmit: " << (double)udp_svr_obj.send_bytes / 1024 << " kB." << std::endl;
    cout << "[INFO] Receive Package(s): " << udp_svr_obj.recv_cnt << ", Send Packages(s): " << udp_svr_obj.send_cnt
         << std::endl;
}

// Windows Actual Entry here
int main(int argc, char *argv[])
{
    printf("GMP Simulator says: Hello World~\r\n");
    printf("GMP will launch...\r\n\n\n");

    gmp_entry();
}

// This function may invoke when main loop occurred.
void gmp_csp_loop(void)
{

#if defined CTL_DISABLE_MULTITHREAD

    static size_t ctl_invoked_counter = 0;

    ctl_invoked_counter += 1;

    if (ctl_invoked_counter % CTL_MAIN_LOOP_RUNNING_RATIO == 0)
    {
        MainISR();
    }

#endif // CTL_PC_TEST_ENABLE
}
