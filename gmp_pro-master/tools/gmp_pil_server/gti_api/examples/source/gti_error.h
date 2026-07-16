/** \file gti_error.h
 * 
 *  This header defines the GTI APIs for retrieving explanations of errors.
 * 
 *  Copyright (c) 1998-2017, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_ERROR_H
#define GTI_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif


/** Error class flags returned from GTI_GETERRSTR_EX3(). 
 *  Error classes represent the context in which the error happened. These may 
 *  be combined when appropriate (e.g. a software breakpoint could be class =
 *  GTI_ERR_BREAK | GTI_ERR_MEMORY).
 */
#define GTI_ERR_CMD          0x00000001 /**< Check validity requested command. */
#define GTI_ERR_MEMORY       0x00000002 /**< Read or write of target memory. */
#define GTI_ERR_REG          0x00000004 /**< Read or write of target register. */
#define GTI_ERR_BREAK        0x00000008 /**< Set or clear of breakpoints. */
#define GTI_ERR_MEMMAP       0x00000010 /**< Memory map. */
#define GTI_ERR_EXEC         0x00000020 /**< Target execution (run, step, halt). */
#define GTI_ERR_INIT         0x00000040 /**< Emulation initialization. */
#define GTI_ERR_COMM         0x00000080 /**< Debug probe communication (unused). */
#define GTI_ERR_CACHE        0x00000100 /**< Manipulating target cache. */
#define GTI_ERR_OCS          0x00000200 /**< The world may never know. */
#define GTI_ERR_PORT         0x00000400 /**< Port access (unused). */
#define GTI_ERR_TIMEOUT      0x00000800 /**< Timeout while waiting for response. */
#define GTI_ERR_TARGET       0x00001000 /**< Error in response from target. */
#define GTI_ERR_CNTRL        0x00002000 /**< Debug probe error. */
#define GTI_ERR_HOST         0x00004000 /**< Host error (unused). */
#define GTI_ERR_CATSCAN      0x00008000 /**< Perform a CATSCAN. */
#define GTI_ERR_RTDX         0x00010000 /**< RTDX. */
#define GTI_ERR_INTERNAL     0x00020000 /**< Internal problem, likely a bug. */
#define GTI_ERR_SECURE       0x00040000 /**< Security. */
#define GTI_ERR_INTERCONNECT 0x00080000 /**< Interconnect Error Support. */
#define GTI_ERR_ICEC         0x00100000 /**< ICECrusher access. */
#define GTI_ERR_TRUSTZONE    0x00200000 /**< ARM Trustzone error (unused). */
#define GTI_ERR_PARTNER      0x00400000 /**< Partner such as DAP (unused). */

/** Error severity flags returned from GTI_GETERRSTR_EX3().
 *  Error severity represents both the severity and the scope of the error. It
 *  indicates how severe the error is and if the error affects the current 
 *  request (operation), target, or whole system.
 *  <br><br>
 *  Controller errors are debug probe problems that affect all targets. <br>
 *  Processor errors are errors that affect only the current target. <br>
 *  Task errors were intended for multi-threaded debug and not supported. <br>
 *  Request errors are errors affecting the current operation or request. <br>
 */
#define GTI_ERR_CONTROLLER_FATAL  0x00800000 /**< Debug probe isn't communicating at all. */
#define GTI_ERR_CONTROLLER_SEVERE 0x00400000 /**< Debug probe is OK but a problem affects all targets. */
#define GTI_ERR_CONTROLLER_WARN   0x00200000 /**< Warning related to debug probe. */
#define GTI_ERR_PROCESSOR_FATAL   0x00020000 /**< Further accesses to this target will fail. */ 
#define GTI_ERR_PROCESSOR_SEVERE  0x00010000 /**< Target may work after resolving this. */
#define GTI_ERR_PROCESSOR_WARN    0x00008000 /**< Warning concerning the current target. */
#define GTI_ERR_TASK_FATAL        0x00000100 /**< Fatal task error (unused). */
#define GTI_ERR_TASK_SEVERE       0x00000080 /**< Severe task error (unused). */
#define GTI_ERR_TASK_WARN         0x00000040 /**< Task error warning (unused). */
#define GTI_ERR_REQUEST_FATAL     0x00000004 /**< Not allowed. */
#define GTI_ERR_REQUEST_SEVERE    0x00000002 /**< Request failed, new requests should work. */
#define GTI_ERR_REQUEST_WARN      0x00000001 /**< Warning concerning the current request. */

/** Icon flags returned from GTI_GETERRSTR_EX3(). */
#define GTI_ERR_ICONSTOP        0x00000001 /**< Stop Sign icon. */
#define GTI_ERR_ICONEXCLAMATION 0x00000002 /**< Exclamation Mark icon. */
#define GTI_ERR_ICONINFORMATION 0x00000003 /**< Information icon. */
#define GTI_ERR_ICONQUESTION    0x00000004 /**< Question Mark icon. */

/** Standard button flags returned from GTI_GETERRSTR_EX3(). */
#define GTI_ERR_OK              0x00000008 /**< OK button, client should cancel current operation. */
#define GTI_ERR_CANCEL          0x00000010 /**< Cancel button, client should cancel current operation. */
#define GTI_ERR_RETRY           0x00000020 /**< Retry button, client should retry current operation. */
#define GTI_ERR_RUDE_RETRY      0x00000040 /**< Rude Retry button, client should retry operation in rude mode. */
#define GTI_ERR_AUTO_RETRY      0x00000080 /**< Auto Retry button, client should continually retry operation. */
#define GTI_ERR_ABORT           0x00000100 /**< Abort button, client should quit the entire application. */
#define GTI_ERR_EMURESET        0x00000200 /**< Reset button, client should disconnect all and reset the debug probe. */

/** Custom button flags returned from GTI_GETERRSTR_EX3(). 
 *  Client should call GTI_SETERRRESPONSE() when one of these is selected. 
 */
#define GTI_CUSTOM_YES          0x00010000 /**< Custom "Yes" button. */
#define GTI_CUSTOM_NO           0x00020000 /**< Custom "No" button. */
#define GTI_CUSTOM_IGNORE       0x00040000 /**< Custom "Ignore" button. */
#define GTI_CUSTOM_ABORT        0x00080000 /**< Custom "Abort" button. */
#define GTI_CUSTOM_FORCE        0x00100000 /**< Custom "Force" button. */
#define GTI_CUSTOM_OK           0x00200000 /**< Custom "OK" button. */
#define GTI_CUSTOM_UPDATE       0x00400000 /**< Custom "Update" button. */
#define GTI_CUSTOM_CONTINUE     0x00800000 /**< Custom "Continue" button. */


/** Function type for GTI_GETERRSTR_EX3(). */
typedef GTI_INT_TYPE (GTI_FN_GETERR_EX3)
    (GTI_HANDLE_TYPE, GTI_INT_TYPE*, GTI_INT_TYPE*, GTI_UINT32_TYPE*, 
     GTI_UINT32_TYPE*, GTI_UINT32_TYPE*, GTI_UINT32_TYPE*, GTI_UINT32_TYPE*,
     GTI_STRING_TYPE, GTI_UINT32_TYPE, GTI_STRING_TYPE, GTI_UINT32_TYPE);

/** Function type for GTI_SETERRRESPONSE(). */
typedef GTI_RETURN_TYPE (GTI_FN_SETERRRESPONSE)(GTI_HANDLE_TYPE, GTI_INT16_TYPE, GTI_UINT32_TYPE);


#ifndef GTI_NO_FUNCTION_DECLARATIONS
/** GTI_GETERRSTR_EX3() - Return pending error message from the driver.
 *
 * This function returns whatever error message is pending in the driver. This
 * also returns information about the severity of the error and describes what 
 * buttons should be displayed for the user. The client should display a dialog
 * with the error text and buttons, and then handle the user's response. 
 *
 * \returns 1 if an error was returned, 0 if no error was returned.
 */
GTI_EXPORT GTI_INT_TYPE 
GTI_GETERRSTR_EX3(
    GTI_HANDLE_TYPE  hpid,                /**< [in]  GTI API instance handle. */
    GTI_INT_TYPE    *pSequenceId,         /**< [out] The command index that caused the failure. */
    GTI_INT_TYPE    *pErrorCode,          /**< [out] The error number that represents the error. */
    GTI_UINT32_TYPE *pErrorClass,         /**< [out] Identifies where in the stack the error occurred. */
    GTI_UINT32_TYPE *pSeverity,           /**< [out] Severity of error and group (e.g. Fatal, Controller). */
    GTI_UINT32_TYPE *pAction,             /**< [out] The default action that client should take (unused). */
    GTI_UINT32_TYPE *pButtons,            /**< [out] Which buttons should be displayed with the error text. */
    GTI_UINT32_TYPE *pIcon,               /**< [out] Which icons should be displayed with the error text. */
    GTI_STRING_TYPE  pszCustomButtons,    /**< [out] A string of at least 64 characters to return custom buttons. */
    GTI_UINT32_TYPE  customButtonsLength, /**< [in]  Length of custom buttons string. */
    GTI_STRING_TYPE  pszErrorMessage,     /**< [out] A string of at least 1024 characters to return error text. */
    GTI_UINT32_TYPE  errorMessageLength   /**< [in]  Length of error string. */
    );

/** GTI_SETERRRESPONSE() - Handles responses to custom error results.
 * 
 * This function provides device specific handling of custom error results.
 * When the error message returned by GTI_GETERRSTR_EX3() includes custom
 * buttons, the client should present a dialog to ask the user to select an
 * action. This function is used to execute the code required to perform
 * the chosen action when the user selects a custom button.
 *
 * \return 0 on success, -1 on error
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_SETERRRESPONSE( 
    GTI_HANDLE_TYPE hpid,   /**< [in]  GTI API instance handle. */
    GTI_INT16_TYPE  button, /**< [in]  Index of custom button pressed. */
    GTI_UINT32_TYPE ErrorID /**< [in]  Error number from GTI_GETERRSTR_EX3() */
    );
#endif /* GTI_NO_FUNCTION_DECLARATIONS */

#ifdef __cplusplus
}
#endif

#endif  /* GTI_ERROR_H */

/* End of File */
