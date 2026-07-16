/**
 * @file csp.typedef.h
 * @author Javnson (javnson@zju.edu.cn)
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright GMP(c) 2024
 *
 */

#ifndef _FILE_CSP_TYPE_DEF_H_
#define _FILE_CSP_TYPE_DEF_H_

#include <driver/inc/UART1.h>

// C28x device peripheral
#ifndef GMP_PORT_UART_T
#define GMP_PORT_UART_T UART_PARAM_s *
#endif // GMP_PORT_UART_T

#ifndef GMP_PORT_I2C_T
#define GMP_PORT_I2C_T uint32_t
#endif // GMP_PORT_I2C_T

#ifndef GMP_PORT_SPI_T
#define GMP_PORT_SPI_T uint32_t
#endif // GMP_PORT_SPI_T

#ifndef GMP_PORT_CAN_T
#define GMP_PORT_CAN_T uint32_t
#endif // GMP_PORT_CAN_T

#endif
