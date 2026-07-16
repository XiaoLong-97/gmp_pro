/** \file gti_private.h
 * 
 *  This header defines GTI APIs and definitions either used internally and not
 *  available or GTI APIs that should not be used by the GTI client.
 * 
 *  Copyright (c) 1998-2015, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_PRIVATE_H
#define GTI_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif


/** <i>Private</i>. Additional information structure used by Do_Initialization(). */
typedef struct
{
    GTI_UINT32_TYPE  m_structRevision; /**< GTI_INIT_PRIVATE_DATA revision number. */
    GTI_INIT_INFO   *m_pInitInfo;      /**< Pointer GTI_INIT_INFO structure from the GTI client. */
} GTI_INIT_PRIVATE_DATA;
#define GTI_INIT_PRIVATE_DATA_REV 0x0 /**< Revision of the GTI_INIT_PRIVATE_DATA structure. */
    
/** <i>Private</i>. Proc ID Type field definitions. */
#define DRVTYPE_EMU      0 /**< Emulation. */
#define DRVTYPE_SIM      1 /**< Simulation. */
#define DRVTYPE_DSK      2 /**< DSK evaluation board . */
#define DRVTYPE_MOD      3 /**< Model. */
#define DRVTYPE_NONDEBUG 4 /**< Non-debuggable device. */
#define DRVTYPE_ROUTER   5 /**< Router device. */

/** <i>Private</i>. Proc ID Family and Sub-Family fields for ICEPick. */
#define PROC_FAMILY_ICEPICK       0xF0   /**< ICEPick Family is 240. */
#define PROC_SUB_FAMILY_ICEPICK   0x000  /**< ICEPick Version 0. */
#define PROC_SUB_FAMILY_ICEPICK_B 0x001  /**< ICEPick Version B. */
#define PROC_SUB_FAMILY_ICEPICK_C 0x002  /**< ICEPick Version C. */
#define PROC_SUB_FAMILY_ICEPICK_D 0x003  /**< ICEPick Version D. */
#define PROC_SUB_FAMILY_ICEPICK_M 0x00C  /**< ICEPick Version M. */

/** <i>Private</i>. Proc ID Family and Sub-Family fields for DEBUGSSM. */
#define PROC_FAMILY_DEBUGSSM      0x3  /**< DEBUGSSM Family is 0x3. */
#define PROC_SUB_FAMILY_DEBUGSSM  0x0  /**< DEBUGSSM Version 0. */

/** <i>Private</i>. Proc ID Family and Sub-Family fields for DAP. */
#define PROC_FAMILY_DAP           0xE0   /**< DAP Family is 224. */
#define PROC_SUB_FAMILY_CS_DAP_PC 0x000  /**< CS_DAP-PC Version 0. */
#define PROC_SUB_FAMILY_CS_DAP    0x001  /**< CS_DAP    Version 1. */

/** <i>Private</i>. Proc ID Family and Sub-Family fields for Security-modules. */

#define PROC_FAMILY_SEC           0xE1   /**< AP Family is 225. */
#define PROC_SUB_FAMILY_SEC_AP    0x000  /**< SEC-AP version 1 */
#define PROC_SUB_FAMILY_AJSM      0x001  /**< SEC-AP version 1 */

/** <i>Private</i>. Proc ID Family and Sub-Family fields for DRP. */
#define PROC_FAMILY_DRP           100    /**< DRP Family is 100 (placeholder). */
#define PROC_SUB_FAMILY_DRP2      2      /**< DRP2 Version 2. */

/** <i>Private</i>. Proc ID Family and Sub-Family fields for CATscan. */
#define PROC_FAMILY_CATSCAN       0xF0   /**< CATscan Family is 240 (use ICEPick). */
#define PROC_SUB_FAMILY_CATSCAN   0x000  /**< CATscan Version 0. */

/** <i>Private</i>. Proc ID Family and Sub-Family fields for HWAs. */
#define PROC_FAMILY_HWA           192    /**< Hardware accelerator (HWA) Family is 192. */
#define PROC_SUB_FAMILY_IME       0      /**< iME device. */
#define PROC_SUB_FAMILY_ILF       1      /**< iLF device. */
#define PROC_SUB_FAMILY_IHWA      0x20   /**< Generic Intelligent HWA, 2x. */

/** <i>Private</i>. Proc ID Family and Sub-Family fields for Trace components. */
#define PROC_FAMILY_ARM           (470)  /**< ARM Family is 470 */
#define PROC_SUB_FAMILY_ETB       (0x25) /**< ETB device */
#define PROC_SUB_FAMILY_CSSTM     (0x26) /**< CS STM device */
#define PROC_SUB_FAMILY_CTSET2    (0x27) /**< CTSET2 device */

/** <i>Private</i>. Proc ID structure. */
typedef struct
{
    unsigned m_nType      :  3; /**< Device Type, bits  2.. 0. */
    unsigned m_nRevision  :  7; /**< Revision,    bits  9.. 3. */
    unsigned m_nSubFamily : 12; /**< Sub-Family,  bits 21..10. */
    unsigned m_nFamily    : 10; /**< Family,      bits 31..22. */
} GTI_PROCESSOR_ID;

#define EMUOUTXDS560       ".\\xds560.out" /**< <i>Private</i>. Default name for XDS560.out file. */
#define NUM_CUSTOM_BUTTONS 0x00000010      /**< <i>Private</i>. Number of custom buttons reserved for error handler. */

/** <i>Private</i>. Flags to define requirements for system features. */
#define GTI_ROUTER_SYSTEM_FEATURE_NO_REQUIREMENT            (0x0) /**< No requirement. */
#define GTI_ROUTER_SYSTEM_FEATURE_NOT_CURRENTLY_SUPPORTED   (0x1) /**< Feature not supported. */
#define GTI_ROUTER_SYSTEM_FEATURE_REQUIRES_CONNECTION       (0x2) /**< Target device must be connected. */
#define GTI_ROUTER_SYSTEM_FEATURE_REQUIRES_DISCONNECTION    (0x4) /**< Target device must be disconnected. */
#define GTI_ROUTER_SYSTEM_FEATURE_REQUIRES_ALL_DISCONNECTED (0x8) /**< All targets must be disconnected. */

/** <i>Private</i>. Feature information structure used by GTI_GET_ROUTER_SYSTEM_FEATURES_INFO(). */
typedef struct 
{
    unsigned int nRevision;       /**< GTI_SYS_FEATURES_INFO revision number. */
    char         pszName[60];     /**< Name to be used in menus. */
    char         pszTooltip[250]; /**< Name to use in the status bar. */
    unsigned int nRequiresSelf;   /**< Requirements to use the feature (self). */
    unsigned int nRequiresOthers; /**< Requirements to use the feature (others). */
} GTI_SYS_FEATURES_INFO;
#define GTI_SYS_FEATURES_INFO_REV 0x0 /**< Revision of the GTI_INIT_PRIVATE_DATA structure. */

/** <i>Private</i>. Command types used internally by block reset code. */
typedef enum
{
    GTI_HALT_CMD,   /**< Halt command. */
    GTI_CONNECT_CMD /**< Connect command. */
} GTI_BLKRST_CMD_TYPE;

/** <i>Private</i>. Execution state flags used internally by router control code. */
typedef enum
{
    EXE_STATE_UNKNOWN,   /**< Unknown execution mode. */
    EXE_STATE_HALT,      /**< Halt mode. */
    EXE_STATE_STEP,      /**< Single step mode. */
    EXE_STATE_RUN_DBG,   /**< Debug run mode (normal run). */
    EXE_STATE_RUN_FREE,  /**< Non-debug run mode (run free). */
    EXE_STATE_RUN_LOWPWR /**< Low power run mode. */
} EXE_STATE;


/** <i>Private</i>. Function type for Do_Initialization(). */
typedef GTI_RETURN_TYPE (GTI_FN_DO_INIT)
    (GTI_PID_TYPE, GTI_STRING_TYPE, GTI_PORT_TYPE, GTI_STRING_TYPE, 
     GTI_PORT_TYPE, GTI_DMA_TYPE, GTI_IRQ_TYPE, GTI_HANDLE_TYPE*,
     GTI_ADDRS_TYPE*, GTI_HANDLE_TYPE);

/** <i>Private</i>. Function type for GTI_GET_EMU_CAPABILITIES(). */
typedef GTI_CAP_TYPE (GTI_FN_GET_EMU_CAPABILITIES) (GTI_HANDLE_TYPE);

/** <i>Private</i>. Function type for GTI_GET_SIM_CAPABILITIES(). */
typedef GTI_CAP_TYPE (GTI_FN_GET_SIM_CAPABILITIES) (GTI_HANDLE_TYPE);

/** <i>Private</i>. Function type for GTI_GETCONFIGPARAM() and GTI_SETCONFIGPARAM(). */
typedef GTI_RETURN_TYPE (GTI_FN_CONFIG)(GTI_HANDLE_TYPE, GTI_CONFIGPARAM_TYPE**, GTI_STRING_TYPE);

/** <i>Private</i>. Function type for GTI_FREECONFIGPARAM(). */
typedef GTI_RETURN_TYPE (GTI_FN_FREECONFIGPARAM)(GTI_HANDLE_TYPE, GTI_CONFIGPARAM_TYPE*);

/** <i>Private</i>. Function type for GTI_GET_ROUTER_SYSTEM_FEATURES_INFO(). */
typedef GTI_RETURN_TYPE (GTI_FN_SYS_INFO)(GTI_HANDLE_TYPE, GTI_UINT32_TYPE, GTI_SYS_FEATURES_INFO*);

/** <i>Private</i>. Function type for GTI_SET_ROUTER_SYSTEM_FEATURE(). */
typedef GTI_RETURN_TYPE (GTI_FN_SYS_EX)(GTI_HANDLE_TYPE, GTI_UINT32_TYPE, GTI_UINT32_TYPE);

/** <i>Private</i>. Function type for GTI_GET_ROUTER_SYSTEM_FEATURE(). */
typedef GTI_RETURN_TYPE (GTI_FN_SYS_EX2)(GTI_HANDLE_TYPE, GTI_UINT32_TYPE, GTI_UINT32_TYPE*);

/** <i>Private</i>. Function type for GTI_SYNCRUN_REQUEST(). */
typedef GTI_RETURN_TYPE (GTI_FN_SYNCRUN_REQUEST)(GTI_HANDLE_TYPE);


#ifndef GTI_NO_FUNCTION_DECLARATIONS
/** Do_Initialization() - <i>Private</i>. Initialize the debug session.
 * 
 *  Called by GTI_INIT_EX(). 
 * 
 * \return 0 on success, -1 on error. On success, new instance handle
 *         is returned in the *hpid parameter.
 */
GTI_EXPORT GTI_RETURN_TYPE 
Do_Initialization( 
    GTI_PID_TYPE     procNum,        /**< [in]  Processor number (unused). */
    GTI_STRING_TYPE  pathName,       /**< [in]  Debug probe and target name \ cpu name. */
    GTI_PORT_TYPE    portAddress,    /**< [in]  Debug probe port address (unused). */
    GTI_STRING_TYPE  parmFileName,   /**< [in]  Path and name of board config file. */
    GTI_PORT_TYPE    portAddress2,   /**< [in]  Alternate debug probe port address (unused). */
    GTI_DMA_TYPE     dmaAddress,     /**< [in]  Debug probe DMA address (unused). */
    GTI_IRQ_TYPE     irq,            /**< [in]  Debug probe IRQ number (unused). */
    GTI_HANDLE_TYPE *hpid,           /**< [out] GTI API instance handle. */
    GTI_ADDRS_TYPE  *options,        /**< [in]  Options flags (unused). */
    GTI_HANDLE_TYPE  hPrivateData    /**< [in]  Additional setup information. */
    );

/** GTI_GETCAPABILITIES() - <i>Private</i>. Gets the supported features of the driver.
 * 
 *  Called by GTI_GET_EXT_CAPABILITIES(). 
 * 
 * \return combination of the GTI_CAPABLE_ flags.
 */
GTI_EXPORT GTI_RETURN_TYPE
GTI_GETCAPABILITIES(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle (unused). */
    );

/** GTI_GET_EMU_CAPABILITIES() - <i>Private</i>. Gets the emulation features of the driver.
 * 
 *  Called by GTI_GET_EXT_CAPABILITIES(). 
 * 
 * \return combination of the GTI_EMUCAP_ flags.
 */
GTI_EXPORT GTI_CAP_TYPE
GTI_GET_EMU_CAPABILITIES(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_GET_SIM_CAPABILITIES() - <i>Private</i>. Gets the simulation features of the driver.
 * 
 *  Called by GTI_GET_EXT_CAPABILITIES().
 * 
 * \return combination of the GTI_SIMCAP_ flags.
 */
GTI_EXPORT GTI_CAP_TYPE
GTI_GET_SIM_CAPABILITIES(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle (unused). */
    );

/** GTI_GETCONFIGPARAM() - <i>Private</i>. Get the configuration parameters.
 * 
 *  Called by GTI_CONFIG().
 * 
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_GETCONFIGPARAM(
    GTI_HANDLE_TYPE        hpid,        /**< [in]  GTI API instance handle. */
    GTI_CONFIGPARAM_TYPE **ppParamList, /**< [out] Pointer to configuration struct. */
    GTI_STRING_TYPE        szBoardName  /**< [in]  Debug probe and target name. */
    );

/** GTI_SETCONFIGPARAM() - <i>Private</i>. Set the configuration parameters.
 * 
 *  Called by GTI_CONFIG().
 * 
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_SETCONFIGPARAM(
    GTI_HANDLE_TYPE        hpid,        /**< [in]  GTI API instance handle. */
    GTI_CONFIGPARAM_TYPE **ppParamList, /**< [in]  Pointer to configuration struct. */
    GTI_STRING_TYPE        szBoardName  /**< [in]  Debug probe and target name. */
    );

/** GTI_FREECONFIGPARAM() - <i>Private</i>. Free the configuration parameter structure.
 * 
 *  Called by GTI_CONFIG().
 * 
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_FREECONFIGPARAM(
    GTI_HANDLE_TYPE       hpid,       /**< [in]  GTI API instance handle. */
    GTI_CONFIGPARAM_TYPE *ppParamList /**< [in]  Pointer to configuration struct. */
    );

/** GTI_GET_NUM_ROUTER_SYSTEM_FEATURES() - <i>Private</i>. Get number of supported router features.
 * 
 *  Called internally by router control code.
 * 
 * \return number of supported features.
 */
GTI_EXPORT GTI_UINT32_TYPE 
GTI_GET_NUM_ROUTER_SYSTEM_FEATURES(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_GET_ROUTER_SYSTEM_FEATURES_INFO() - <i>Private</i>. Get information on supported router features.
 * 
 *  Called internally by router control code.
 * 
 * \return 0 on success, -1 on error.
 */
GTI_RETURN_TYPE 
GTI_GET_ROUTER_SYSTEM_FEATURES_INFO ( 
    GTI_HANDLE_TYPE        hpid,       /**< [in]  GTI API instance handle. */
    GTI_UINT32_TYPE        nFeatureID, /**< [in]  Index to feature to get. */
    GTI_SYS_FEATURES_INFO* pInfo       /**< [out] Pointer to return feature information. */
    );

/** GTI_SET_ROUTER_SYSTEM_FEATURE() - <i>Private</i>. Set router feature state.
 * 
 *  Called internally by router control code.
 * 
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_SET_ROUTER_SYSTEM_FEATURE(
    GTI_HANDLE_TYPE hpid,          /**< [in]  GTI API instance handle. */
    GTI_UINT32_TYPE nFeatureID,    /**< [in]  Index to feature to set. */
    GTI_UINT32_TYPE nFeatureEnable /**< [in]  Feature state to set. */
    );

/** GTI_GET_ROUTER_SYSTEM_FEATURE() - <i>Private</i>. Get router feature state.
 * 
 *  Called internally by router control code.
 * 
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_GET_ROUTER_SYSTEM_FEATURE(
    GTI_HANDLE_TYPE  hpid,          /**< [in]  GTI API instance handle. */
    GTI_UINT32_TYPE  nFeatureID,    /**< [in]  Index to feature to set. */
    GTI_UINT32_TYPE *nFeatureEnable /**< [in]  Pointer to return feature state. */
    );

/** GTI_SYNCRUN_REQUEST() - <i>Private</i>. Queue synchronous (global) run (router method).
 * 
 *  Called internally by synchronous run code.
 * 
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_SYNCRUN_REQUEST(
    GTI_HANDLE_TYPE  hpid /**< [in]  GTI API instance handle. */
    );


#endif /* GTI_NO_FUNCTION_DECLARATIONS */

#ifdef __cplusplus
};
#endif

#endif /* GTI_PRIVATE_H */

/* End of File */

