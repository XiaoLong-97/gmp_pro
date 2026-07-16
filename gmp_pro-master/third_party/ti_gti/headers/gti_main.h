/** \file gti_main.h
 * 
 *  This header defines the GTI APIs for initializing the driver and for 
 *  connecting to the target device.
 * 
 *  Copyright (c) 1998-2018, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_MAIN_H
#define GTI_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif


/** Additional setup information structure for GTI_INIT_EX(). 
 *
 *  Initialize this structure by first setting m_structRevision to 
 *  GTI_INIT_INFO_REV and then set m_structLength to sizeof(GTI_INIT_INFO).
 *  Any unused members should be set to zero.
 */
typedef struct{
    GTI_UINT32_TYPE m_structRevision;        /**< GTI_INIT_INFO revision number. */
    GTI_UINT32_TYPE m_structLength;          /**< Size of GTI_INIT_INFO structure. */
    GTI_HANDLE_TYPE m_rtdx_info;             /**< RTDX setup parameters. */
    GTI_HANDLE_TYPE m_pIDspUser;             /**< DSP_USER Interface Pointer (unused). */
    GTI_STRING_TYPE m_sProcDataFileLocation; /**< Processor data file (unused). */
    GTI_HANDLE_TYPE m_ParentOfPRSC;          /**< TargetAdapter pointer to parent router.*/
    GTI_HANDLE_TYPE m_pLoggerId;             /**< Handle to logger calls (unused). */
    GTI_STRING_TYPE m_pszPartNumber;         /**< Device part number (unused). */
    GTI_HANDLE_TYPE m_pMemoryProxy;          /**< TargetAdaptor pointer to memory proxy. */
    GTI_HANDLE_TYPE m_pSectionAccessFactory; /**< Pointer to an instance of ISectionAccessFactory interface */
    GTI_HANDLE_TYPE m_pStatusNotification;   /**< Pointer to an instance of IStatusNotification interface */
    GTI_HANDLE_TYPE m_pStepPastBp;		     /**< Pointer to an instance of SyncSetup::IStepPastBp interface */
    GTI_HANDLE_TYPE m_pszDeviceFamily;	     /* String indicating the "cpu_family" property value from targetdb */              /* REVISION FIRST VALID: 0xB */
    GTI_HANDLE_TYPE m_pSectionAccessFactory64; /* A pointer to an instance of an ISectionAccessFactory64 interface */           /* REVISION FIRST VALID: 0xB */
    GTI_UINT32_TYPE m_nNumProperties;	     /* Array size of the next two members */                                           /* REVISION FIRST VALID: 0xB */
    GTI_STRING_TYPE* m_ppPropertyNames;	     /* Array of setup property names */                                                /* REVISION FIRST VALID: 0xB */
    GTI_STRING_TYPE* m_ppPropertyValues;	 /* Array of setup property values cooresponding to the name of the same index */   /* REVISION FIRST VALID: 0xB */

} GTI_INIT_INFO;

#define GTI_INIT_INFO_REV 0xb; /**< Revision of the GTI_INIT_INFO structure. */



/** Function type for GTI_INIT_EX(). */
typedef GTI_RETURN_TYPE (GTI_FN_INIT_EX) 
    (GTI_PID_TYPE, GTI_STRING_TYPE, GTI_PORT_TYPE, GTI_STRING_TYPE, GTI_PORT_TYPE,
     GTI_DMA_TYPE, GTI_IRQ_TYPE, GTI_INIT_INFO*, GTI_HANDLE_TYPE*);

/** Function type for GTI APIs with the only parameter is the instance handle. 
 *  Used for GTI_QUIT(), GTI_GETPROCTYPE(), GTI_GETCAPABILITIES(), GTI_GETREV(),
 *  GTI_GLOBALSTART(), GTI_RESET(), GTI_NUM_HBP_TYPES(), GTI_GETWORDSIZE(),
 *  GTI_POLL(), and GTI_TESTERR().
 */
typedef GTI_RETURN_TYPE (GTI_FN_GEN)(GTI_HANDLE_TYPE);

/** Function type for GTI_CONNECT(). */
typedef GTI_RETURN_TYPE (GTI_FN_CONNECT)(GTI_HANDLE_TYPE);

/** Function type for GTI_DISCONNECT(). */
typedef GTI_RETURN_TYPE (GTI_FN_DISCONNECT)(GTI_HANDLE_TYPE);

/** Function type for GTI APIs that return a number instead of an error. 
 *  Used for GTI_GET_NUM_RESETS() and GTI_GET_NUM_ROUTER_SYSTEM_FEATURES();
 */
typedef GTI_UINT32_TYPE (GTI_FN_GEN_NUM)(GTI_HANDLE_TYPE);

/** Function type for GTI APIs that return a string instead of an error. 
 *  Used by GTI_GET_HBP_TYPE_NAME().
 */
typedef GTI_STRING_TYPE (GTI_FN_GETNAME)(GTI_HANDLE_TYPE, GTI_INT16_TYPE);

/** Function type for GTI APIs that pass in a number with the instance handle.
 *  Used for GTI_HALT(), GTI_STEP(), and GTI_ENABLE_GLOBAL_BKPTS().
 */
typedef GTI_RETURN_TYPE (GTI_FN_RUN)(GTI_HANDLE_TYPE, GTI_INT16_TYPE);


#ifndef GTI_NO_FUNCTION_DECLARATIONS
/** GTI_INIT_EX() - Initialize the debug session.
 *
 *  This function is called once for each processor to initialize the 
 *  emulation software and communications between debug probe and host. 
 *
 *  The "Session name / cpu name" specified in pathName parameter is used
 *  to uniquely identify the cpu being targetted. If the application is
 *  communicating with multiple debug probes then the "session name" must be
 *  unique for each debug probe connection. The "cpu name" is the name of the
 *  cpu as given in the board config file, but is not case-sensitive.
 *  \n For example, consider the following board config file
 *  \verbatim
    @ cs_dap family=cs_dap irbits=4 drbits=1 subpaths=1 identify=0
        & subpath_1 type=legacy address=0 default=no custom=no force=yes pseudo=yes
            @ cortex_m4_0 family=cortex_mxx irbits=0 drbits=0 identify=0x02000000 traceid=0x0
    \endverbatim
 *  Here the "cpu name" is the text immediately following the @ symbol, so
 *  "cs_dap" is the cpu name for Coresight DAP and "cortex_m4_0" is the cpu
 *  name for Cortex M4 core.
 *  \n Typically the pathName is set to a connectionName_cpuName/cpuName format
 *  where the connectionName_cpuName becomes the "session name". For example to
 *  connect to Cortex M4 core on MSP432 target with an XDS100v2 debug probe,
 *  the path string would look like this:
 *  \verbatim
    connectionName = XDS100v2_MSP432 (user created unique per probe)
    cpuName        = CORTEX_M4_0 (cpu name in board config - case insensitive)
    pathName       = connectionName_cpuName/cpuName
                   = XDS100v2_MSP432_CORTEX_M4_0/CORTEX_M4_0
   \endverbatim
 *  Note that portAddress is only used by Spectrum Digital debug probes.
 *  portAddress is used to contain the debug probe class (e.g.. 0x510).
 *  For all other debug probes, portAddress is ignored.
 *
 * \return 0 on success, -1 on error. On success, new instance handle
 *         is returned in the *hpid parameter.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_INIT_EX(
    GTI_PID_TYPE     procNum,        /**< [in]  Processor number (unused). */
    GTI_STRING_TYPE  pathName,       /**< [in]  Session name / cpu name. */
    GTI_PORT_TYPE    portAddress,    /**< [in]  Debug probe port address. */
    GTI_STRING_TYPE  parmFileName,   /**< [in]  Path and name of board config file. */
    GTI_PORT_TYPE    portAddress2,   /**< [in]  Alternate debug probe port address (unused). */
    GTI_DMA_TYPE     dmaAddress,     /**< [in]  Debug probe DMA address (unused). */
    GTI_IRQ_TYPE     irq,            /**< [in]  Debug probe IRQ number (unused). */
    GTI_INIT_INFO   *additionalInfo, /**< [in]  Additional setup information. */ 
    GTI_HANDLE_TYPE *hpid            /**< [out] GTI API instance handle. */
    );

/** GTI_QUIT() - Terminate the debug session.
 *
 *  This function is called once for each processor to terminate emulation
 *  software and close communications between the debug probe and host.
 * 
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_QUIT(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_CONNECT() - Connect to target. 
 * 
 *  This function is called once for each processor to connect to the
 *  target.
 * 
 * \return 0 on success, -1 on error. 
 */ 
GTI_EXPORT GTI_RETURN_TYPE 
GTI_CONNECT(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_CONNECT2() - Connect to target non-intrusively.
*
*  This function is called once for each processor to connect to the
*  target non-intrusively.
*
* \return 0 on success, -1 on error.
*/
GTI_EXPORT GTI_RETURN_TYPE 
GTI_CONNECT2(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
);

/** GTI_DISCONNECT() - Disconnect from target. 
 * 
 *  This function is called once for each processor to disconnect from the
 *  target.
 * 
 * \return 0 on success, -1 on error. 
 */ 
GTI_EXPORT GTI_RETURN_TYPE 
GTI_DISCONNECT(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_BLINK_LEDS() - Blink LEDs on selected debug probe.
*
*  This function blinks the LEDs on the probe selected in the
*  given board config file (only supported on XDS110 probes).
*
*  This function cannot be called if the probe is already
*  connected. This function is intended to be called before
*  debug launch to help identify which probe is being accessed
*  before launch and connect.
*
* \return 0 on success, -1 on error.
*/
GTI_EXPORT GTI_RETURN_TYPE
GTI_BLINK_LEDS(
    GTI_STRING_TYPE parmFileName /**< [in]  Path and name of board config file. */
    );
#endif /* GTI_NO_FUNCTION_DECLARATIONS */

#ifdef __cplusplus
};
#endif

#endif  /* GTI_MAIN_H */

/* End of File */
