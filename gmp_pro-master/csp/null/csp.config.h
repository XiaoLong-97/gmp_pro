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

// This file provide a Chip Support Package configuration for STM32

// using user specified default log print function
#ifndef USER_SPECIFIED_PRINT_FUNCTION
#define USER_SPECIFIED_PRINT_FUNCTION printf
#endif // USER_SPECIFIED_PRINT_FUNCTION

#define SPECIFY_DISABLE_CSP_EXIT
