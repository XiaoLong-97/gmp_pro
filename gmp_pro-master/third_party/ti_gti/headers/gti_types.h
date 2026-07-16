/** \file gti_types.h
 * 
 *  This header defines the basic types used by the GTI API.
 * 
 *  Copyright (c) 1998-2015, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_TYPES_H
#define GTI_TYPES_H

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifndef BOOL
#undef TRUE
#undef FALSE
/** Boolean type used by GTI APIs. */
typedef enum {FALSE = 0, TRUE = 1} BOOL; 
#define BOOL BOOL /**< Flag that BOOL type is defined. */
#endif

typedef BOOL            GTI_BOOL;              /**< Boolean type. */
typedef int             GTI_INT_TYPE;          /**< Signed integer type. */
typedef int             GTI_INT16_TYPE;        /**< Signed "at least" 16-bit integer type. */
typedef unsigned int    GTI_UINT32_TYPE;       /**< Unsigned 32-bit integer type. */
typedef uint64_t        GTI_UINT64_TYPE;       /**< Unsigned 64-bit integer type. */
typedef unsigned int    GTI_ADDRS_TYPE;        /**< Memory address type. */
typedef GTI_UINT64_TYPE GTI_ADDRS64_TYPE;      /**< 64-bit wide memory address type. */
typedef int             GTI_PAGE_TYPE;         /**< Memory page index type. */
typedef unsigned int    GTI_REGID_TYPE;        /**< Register index type. */
typedef int             GTI_LEN_TYPE;          /**< General purpose length type. */
typedef int             GTI_PID_TYPE;          /**< Processor family index type. */
typedef void*           GTI_HANDLE_TYPE;       /**< GTI instance handle type. */
typedef unsigned int    GTI_PORT_TYPE;         /**< Hardware port type. */
typedef int             GTI_DMA_TYPE;          /**< DMA address type. */
typedef int             GTI_IRQ_TYPE;          /**< Interrupt number type. */
typedef int             GTI_DATA_TYPE;         /**< Memory data type. */
typedef int             GTI_REGISTER_TYPE;     /**< Register data type. */
typedef char*           GTI_STRING_TYPE;       /**< String type. */
typedef GTI_INT16_TYPE  GTI_RETURN_TYPE;       /**< GTI function return type. */
typedef int             GTI_ATTR_TYPE;         /**< Memory map attribute type. */
typedef unsigned int    GTI_MEM_NUM_ATTR_TYPE; /**< Memory numeric attribute type. */
typedef char*           GTI_MEM_STR_ATTR_TYPE; /**< Memory string attribute type. */
typedef int             GTI_WAIT_STATE_TYPE;   /**< Memory access wait state type. */
typedef GTI_STRING_TYPE GTI_PROC_TYPE;         /**< Processor type string type. */
typedef GTI_UINT32_TYPE GTI_LRETURN_TYPE;      /**< Unsigned 32-bit return type. */
typedef GTI_UINT32_TYPE GTI_CAP_TYPE;          /**< Capabilities flags type. */
typedef GTI_UINT32_TYPE GTI_PROCID_TYPE;       /**< Processor ID type. */
typedef char**          GTI_ARCH_TYPE;         /**< CPU architecture type. */

#define GTI_SUCCESS  0 /**< GTI_RETURN value for success (no errors). */
#define GTI_ERROR   -1 /**< GTI_RETURN value when there's an error. */

#ifndef __cplusplus
#ifndef bool
/** C++ style Boolean type when compiled in C. */
typedef char bool;
#define true  (bool)(1)
#define false (bool)(0)
#define bool bool /**< Flag that bool type is defined. */
#endif
#endif


#ifdef __cplusplus
};
#endif

#endif  /* GTI_TYPES_H */

/* End of File */
