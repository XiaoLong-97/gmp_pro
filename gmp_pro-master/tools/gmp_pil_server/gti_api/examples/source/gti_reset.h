/** \file gti_reset.h
 * 
 *  This header defines the GTI APIs for resetting the target device. 
 * 
 *  Copyright (c) 1998-2015, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_RESET_H
#define GTI_RESET_H

#ifdef __cplusplus
extern "C" {
#endif


/** Flags to define the requirements to use a reset for GTI_GET_RESET_INFO(). */
#define GTI_RESET_REQUIRES_NONE             (0x00) /**< Reset requires no special conditions. */
#define GTI_RESET_REQUIRES_HALT             (0x01) /**< Reset requires the target is halted. */
#define GTI_RESET_REQUIRES_CONNECTION       (0x02) /**< Reset requires the target is connected. */
#define GTI_RESET_REQUIRES_DISCONNECTION    (0x04) /**< Reset requires the target is disconnected. */
#define GTI_RESET_REQUIRES_ALL_DISCONNECTED (0x08) /**< Reset requires all targets are disconnected. */

/** Structure that defines a custom reset for GTI_GET_RESET_INFO(). */
typedef struct 
{
    unsigned int nRevision;       /**< GTI_RESET_INFO revision number. */
    char         pszName[60];     /**< Name of reset to be shown in menus. */
    char         pszTooltip[250]; /**< Text description to appear in status displays. */
    unsigned int nRequires;       /**< Flags that define requirements for using this reset. */
} GTI_RESET_INFO;
#define GTI_RESET_INFO_REV 0x1 /**< Revision of the GTI_RESET_INFO structure. */

/** Flags to control the block reset mode used by GTI_BLOCK_RESET(). */
typedef enum GTI_BLOCK_RESET_TYPE
{
    GTI_BLOCK_RESET_OFF  = 0, /**< Disable block reset mode, apply resets normally. */
    GTI_BLOCK_RESET_ONCE = 1, /**< Set block reset mode to block resets one time only. */
    GTI_BLOCK_RESET_STAY = 2  /**< Set block reset mode to block all resets. */
} GTI_BLOCK_RESET_TYPE;


/** Function type for GTI_RESET_EX(). */
typedef GTI_RETURN_TYPE (GTI_FN_GEN_EX)(GTI_HANDLE_TYPE, GTI_UINT32_TYPE);

/** Function type for GTI_GET_RESET_INFO(). */
typedef GTI_RETURN_TYPE (GTI_FN_GEN_INFO)(GTI_HANDLE_TYPE, GTI_UINT32_TYPE, GTI_RESET_INFO*);

/** Function type for GTI_EMURESET_EX(). */
typedef GTI_RETURN_TYPE (GTI_FN_EMURESET_EX)(GTI_PORT_TYPE, GTI_STRING_TYPE);

/** Function type for GTI_SET_WAIT_IN_RESET(). */
typedef GTI_RETURN_TYPE (GTI_FN_SET_WAIT_IN_RESET)(GTI_HANDLE_TYPE, GTI_BOOL);

/** Function type for GTI_GET_WAIT_IN_RESET_MODE(). */
typedef GTI_RETURN_TYPE(GTI_FN_GET_WAIT_IN_RESET_MODE)(GTI_HANDLE_TYPE, GTI_BOOL*);

/** Function type for GTI_BLOCK_RESET(). */
typedef GTI_RETURN_TYPE (GTI_FN_BLOCK_RESET)(GTI_HANDLE_TYPE, GTI_BLOCK_RESET_TYPE);


#ifndef GTI_NO_FUNCTION_DECLARATIONS
/** GTI_RESET() - Reset target device.
 *
 *  This function resets the device. The type of reset performed depends on
 *  the specific device driver, but usually this is a software only reset.
 *
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_RESET(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_RESET_EX() - Reset target device.
 *
 *  This function resets the device using nResetID to request the specific type
 *  of reset to use.  The supported types of resets are determined by using the
 *  GTI_GET_NUM_RESETS() and GTI_GET_RESET_INFO() calls.
 *
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE
GTI_RESET_EX(
    GTI_HANDLE_TYPE  hpid,    /**< [in]  GTI API instance handle. */
    GTI_UINT32_TYPE  nResetID /**< [in]  Index to the type of reset to use. */
    );

/** GTI_GET_NUM_RESETS() - Get number of reset types available for this device.
 *
 *  This call returns the number of reset types available for this driver and 
 *  target device. Use this number with GTI_GET_RESET_INFO() to build a list of 
 *  available reset types that can be used with GTI_RESET_EX().
 *
 * \return number of reset types available for this device. 
 */
GTI_EXPORT GTI_UINT32_TYPE  
GTI_GET_NUM_RESETS(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_GET_RESET_INFO() - Get details for each available reset type.
 *
 *  This call fills in a GTI_RESET_INFO structure with the details of the
 *  reset type requested by the nResetID index.  Use GTI_GET_NUM_RESETS()
 *  to determine the range of legal reset indices for this target device.
 *
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE
GTI_GET_RESET_INFO(
    GTI_HANDLE_TYPE  hpid,     /**< [in]  GTI API instance handle. */
    GTI_UINT32_TYPE  nResetID, /**< [in]  Index to the reset to get info on. */
    GTI_RESET_INFO  *pInfo     /**< [out] Pointer to return info about the reset. */
    );

/** GTI_EMURESET_EX() - Reset the debug probe.
 *
 *  This call does a JTAG reset on the target debug probe specified in the 
 *  board config file passed in via parmFileName.  This call can only be 
 *  made when no targets are currently connected to the debug probe.
 *
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_EMURESET_EX(
    GTI_PORT_TYPE   portAddress, /**< [in]  Debug probe port address (unused). */
    GTI_STRING_TYPE parmFileName /**< [in]  Path and name of board config file. */
    ); 
    
/** GTI_SET_WAIT_IN_RESET() - Set the wait-in-reset (WIR) mode.
 *
 *  Turns on or off the wait-in-reset (WIR) mode of the device.  WIR mode
 *  causes the device to remain halted at the reset vector after a reset.
 *  Set bWIREnable to TRUE to turn on WIR mode, FALSE to turn off WIR mode.
 *
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE  
GTI_SET_WAIT_IN_RESET(
    GTI_HANDLE_TYPE hpid,      /**< [in]  GTI API instance handle. */
	GTI_BOOL bWIREnable	  /**< [in]  Flag to turn on or off WIR mode. */
    );

/** GTI_GET_WAIT_IN_RESET() - Get the wait-in-reset (WIR) mode.
 *
 *  Returns the current wait-in-reset (WIR) mode setting of the device. WIR
 *  mode causes the device to remain halted at the reset vector after a reset.
 *  Returns TRUE if WIR mode is on, FALSE if it is off.
 *
 * \return 0 on success, -1 on error. Current setting is returned in bWIREnable. 
 */
GTI_EXPORT GTI_RETURN_TYPE  
GTI_GET_WAIT_IN_RESET_MODE(
    GTI_HANDLE_TYPE  hpid,      /**< [in]  GTI API instance handle. */
	GTI_BOOL* bWIREnable  /**< [out] Pointer to return current WIR mode setting. */
    );

/** GTI_BLOCK_RESET() - Set the block reset mode.
 *
 *  Set the block reset mode of the device. Block reset mode causes the parent
 *  router of the device (e.g. ICEPick router) to intercept hardware resets
 *  and prevent them from being seen by the device. WIR mode must be disabled
 *  prior to using block reset mode. Set nBlockMode to the desired 
 *  GTI_BLOCK_RESET_TYPE to set the mode.
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE  
GTI_BLOCK_RESET( 
    GTI_HANDLE_TYPE      hpid, 
    GTI_BLOCK_RESET_TYPE nBlockMode
    );
#endif /* GTI_NO_FUNCTION_DECLARATIONS */


#ifdef __cplusplus
}
#endif

#endif /* GTI_RESET_H */

/* End of File */

