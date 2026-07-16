/**
 * @file csp.config.h
 * @author Javnson (javnson@zju.edu.cn)
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright GMP(c) 2024
 *
 */

// This file provide a Chip Support Package configuration for SPC6L64B

#ifndef _FILE_SPC6L64B_CSP_CONFIG_H_
#define _FILE_SPC6L64B_CSP_CONFIG_H_

// using user specified default log print function
#ifndef USER_SPECIFIED_PRINT_FUNCTION
#define USER_SPECIFIED_PRINT_FUNCTION printf
#endif // USER_SPECIFIED_PRINT_FUNCTION

// use CSP specified Math Library
#define USING_CSP_MATH_LIBRARY

// disable CSP exit callback
#define SPECIFY_DISABLE_CSP_EXIT

// #include "IQmathLib.h"
// #include "uart1.h"

// System config

// REPAIR Necessary Constants
#define PI    3.14159265358979
#define SQRT3 1.732050807568877
#define SQRT2 1.414213562373095

#endif // _FILE_SPC6L64B_CSP_CONFIG_H_
