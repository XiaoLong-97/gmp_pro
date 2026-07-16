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

// This file provide a Chip Support Package configuration for Windows Simulation Platform


// Specify this is the PC test environment.
#define SPECIFY_PC_ENVIRONMENT

// Specify the maximum loop times
// User may cover this value via redefine this macro
#ifndef PC_ENV_MAX_ITERATION
#define PC_ENV_MAX_ITERATION ((100000))
#endif // PC_ENV_MAX_ITERATION

