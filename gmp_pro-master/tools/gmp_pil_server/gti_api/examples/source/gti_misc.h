/** \file gti_misc.h
 * 
 *  This header defines miscellaneous GTI APIs.
 * 
 *  Copyright (c) 1998-2015, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_MISC_H
#define GTI_MISC_H

#ifdef __cplusplus
extern "C" {
#endif


/** Execute packet structure for GTI_GET_EXEC_PACKET_INFO(). */
typedef struct
{
    GTI_UINT32_TYPE nExecPacketPC;     /**< Start address of execute packet. */
    GTI_UINT32_TYPE nExecPacketLength; /**< Length of the execute packet. */
} GTI_EXEC_PACKET;

/** Execute packet list structure for GTI_GET_EXEC_PACKET_INFO(). */
typedef struct
{
    GTI_UINT32_TYPE  nSize;        /**< Number of valid execute packets. */
    GTI_EXEC_PACKET *pExecPackets; /**< Array of valid execute packets.*/
} GTI_EXEC_PACKET_INFO;


/** Function type for GTI_GET_EXEC_PACKET_INFO(). */
typedef GTI_RETURN_TYPE (GTI_FN_GET_EXEC_PACKET_INFO)(GTI_HANDLE_TYPE, GTI_EXEC_PACKET_INFO*);

/** Function type for GTI_GET_CONTEXT_CONST(). */
typedef GTI_RETURN_TYPE (GTI_FN_GET_CONTEXT_CONST)(GTI_HANDLE_TYPE, GTI_STRING_TYPE, GTI_UINT32_TYPE*);

/** Function type for GTI_ENABLE_RTDX(). */
typedef GTI_RETURN_TYPE (GTI_FN_ENABLE_RTDX)(GTI_HANDLE_TYPE);

/** Function type for GTI_DISABLE_RTDX(). */
typedef GTI_RETURN_TYPE (GTI_FN_DISABLE_RTDX)(GTI_HANDLE_TYPE);


#ifndef GTI_NO_FUNCTION_DECLARATIONS
/** GTI_GET_EXEC_PACKET_INFO() - Get execute packet information.
 *
 *  This function is used to retrieve information on the instructions that are 
 *  to begin execution on the next architectural cycle. This function differs 
 *  from a simple PC register read in that it handles sets of instructions 
 *  executing in parallel. This function will also return the length of each 
 *  individual execute packet.
 *  <br><br>
 *  The GTI_EXEC_PACKET_INFO structure contains an array of structures that 
 *  supports the return of execute packet information. The client is responsible
 *  for allocating this array. Call GTI_GET_CONTEXT_CONST() with cName set to
 *  "UINT32_CONST_EXEC_PACKET_INFO_ARRSIZE" to retrieve the length of the
 *  pExecPackets array that should be allocated for the GTI_EXEC_PACKET_INFO
 *  structure.
 *  <br><br>
 *  Note: currently this call is only supported by the C64x+ driver.
 *
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_GET_EXEC_PACKET_INFO(
    GTI_HANDLE_TYPE       hpid,           /**< [in]  GTI API instance handle. */
    GTI_EXEC_PACKET_INFO *pExecPacketInfo /**< [out] Pointer to return execute packet list. */
    );

/** GTI_GET_CONTEXT_CONST() - Get an integer constant value.
 *
 *  This function is used to retrieve an integer constant value that is 
 *  specific to the driver or device being used. Use cName to specify by 
 *  text name the constant to retrieve.
 *  <br><br>
 *  Note: currently this call is only supported by the C64x+ driver, and
 *  only for the constant named "UINT32_CONST_EXEC_PACKET_INFO_ARRSIZE".
 *  See GTI_GET_EXEC_PACKET_INFO() for how this constant is used.
 *
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_GET_CONTEXT_CONST(
    GTI_HANDLE_TYPE  hpid,      /**< [in]  GTI API instance handle. */
    GTI_STRING_TYPE  cName,     /**< [in]  Name of constant to get. */
    GTI_UINT32_TYPE *pContainer /**< [out] Pointer to return constant value. */
    );

/** GTI_ENABLE_RTDX() - Enable RTDX feature.
 *
 *  This function is used to enable the RTDX feature which supplies a
 *  communication channel over JTAG between an application running on the 
 *  target and the client on the PC host.
 *
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_ENABLE_RTDX(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_DISABLE_RTDX() - Disable RTDX feature.
 *
 *  This function is used to disable the RTDX feature which supplies a
 *  communication channel over JTAG between an application running on the 
 *  target and the client on the PC host.
 *
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_DISABLE_RTDX(
    GTI_HANDLE_TYPE hpid
    );
#endif /* GTI_NO_FUNCTION_DECLARATIONS */


#ifdef __cplusplus
}
#endif

#endif  /* GTI_MISC_H */

/* End of File */
