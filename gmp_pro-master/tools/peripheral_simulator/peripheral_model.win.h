/**
 * @file peripheral_model.win.h
 * @author Javnson (javnson@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2024-09-30
 * 
 * @copyright Copyright GMP(c) 2024
 * 
 */

// Support FILE type
#include <stdio.h>

#ifndef _FILE_PERIPHERAL_MODEL_WINDOWS_H_
#define _FILE_PERIPHERAL_MODEL_WINDOWS_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    /**
     * @brief UART handle for windows virtual peripheral.
     */
    typedef struct _tag_uart_mapping_to_file
    {
        /**
         * @brief This is the hadnle to a FILE object. Any write or read operation
         * will map to the uart port.
         */
        FILE *virtual_uart_rx;

        /**
         * @brief This is the handle to a FILE obhect. Any write operation
         * will map to the uart port.
         */
        FILE *virtual_uart_tx;

        /**
         * @brief This is a handle of a FILE object.
         * Any operation wil be record to the file.
         */
        FILE *uart_record;

        /**
         * @brief This is a buffer pointer of duplex interface.
         * User may band to this buffer to get necessary informations.
         */
        duplex_ift *buffer;

    } uart_mapping_to_file_t;


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FILE_PERIPHERAL_MODEL_WINDOWS_H_
