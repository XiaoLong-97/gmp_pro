/**
 * @file user_main.cpp
 * @author Javnson (javnson@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2024-09-30
 * 
 * @copyright Copyright GMP(c) 2024
 * 
 */
 
//////////////////////////////////////////////////////////////////////////
// invoke headers

// system headers
#include <string.h>
#include <stdio.h>

// Core 
#include <core/gmp_core.hpp>
#include <core/util/ds/data_ring_buffer.h>

// extensions

// Controller Template Library
#include <ctl/ctl_core.h>


//////////////////////////////////////////////////////////////////////////
// global variables here





//////////////////////////////////////////////////////////////////////////
// initialize routine here
GMP_NO_OPT_PREFIX
void user_init(void)
GMP_NO_OPT_SUFFIX
{
//	dbg_uart.write("Hello World!\r\n",14);
	gmp_dbg_prt("Hello World!\r\n");

}


//////////////////////////////////////////////////////////////////////////
// endless loop function here
void user_loop(void)
{

	
}


//////////////////////////////////////////////////////////////////////////
// interrupt functions and callback functions here


