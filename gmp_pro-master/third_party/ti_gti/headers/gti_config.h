/** \file gti_config.h
 * 
 *  This header defines the GTI APIs to determine the capabilities of the driver  
 *  and to control the configuration and parameters of the driver.
 * 
 *  Copyright (c) 1998-2019, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_CONFIG_H
#define GTI_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/** Error reason for GTI_QUERY_INTERFACE(). */
typedef enum
{
    GTI_INTERFACE_NOT_SUPPORTED, /**< Requested feature is not supported. */
    GTI_VERSION_MISMATCH         /**< Requested version is not supported. */
} GTI_QUERY_INTF_ERROR_TYPE;

/** List of device ("processor") types for GTI_GETPROCTYPE(). */
typedef enum GTI_PROCESSOR_TYPE
{
    GTI_C2X,            /**< TMS320C2x processor family (not supported). */
    GTI_C5X,            /**< TMS320C5x processor family (not supported). */
    GTI_C3X,            /**< TMS320C3x processor family (not supported). */
    GTI_C4X,            /**< TMS320C4x processor family (not supported). */
    GTI_C32,            /**< TMS320C32 processor (not supported). */
    GTI_C5X_DSK,        /**< TMS320C5x DSK evaluation board (not supported). */
    GTI_C26_DSK,        /**< TMS320C26 DSK evaluation board (not supported). */
    GTI_C2XX,           /**< TMS320C2xx processor family (not supported). */
    GTI_C5XX,           /**< TMS320C5xx processor family, C54x. */
    GTI_C6X,            /**< TMS320C62x processor family, fixed point. */
    GTI_C67X,           /**< TMS320C67x processor family, floating point. */
    GTI_C27XX,          /**< TMS320C27xx processor family, C27x and C28x. */
    GTI_C55XX,          /**< TMS320C55xx processor family, C55x. */
    GTI_470,            /**< TMS470 micro-controller family, ARM. */
    GTI_C64XX,          /**< TMS320C64xx processor family, Kelvin. */
    GTI_ICEPICK,        /**< ICEPick scan router (not supported). */
    GTI_ICEPICK_B,      /**< ICEPick B scan router. */
    GTI_ICEPICK_C,      /**< ICEPick C scan router. */
    GTI_DAP_PC,         /**< DAP / DAP_PC (debug access port) router. */
    GTI_CS_DAP,         /**< DAP / CS_DAP (debug access port) router. */
    GTI_CATSCAN,        /**< CATscan device. */
    GTI_DRP,            /**< DRP hardware accelerator. */
    GTI_C55P,           /**< TMS320C56xx processor, Ryujin. */
    GTI_ETB11,          /**< ETB11 trace buffer component. */
    GTI_ETBCS,          /**< ETBCS trace buffer component. */
    GTI_IME,            /**< IME hardware accelerator, Motion Estimator. */
    GTI_ILF,            /**< ILF hardware accelerator, Loop Filter. */
    GTI_CSSTM,          /**< STM trace component. */
    GTI_CTSET2,         /**< CTSET2 trace component. */
    GTI_IHWA,           /**< Intelligent Hardware Accelerator. */   
    GTI_ICEPICK_D,      /**< ICEPick D scan router. */
    GTI_ICEPICK_M,      /**< ICEPick M scan router. */
    GTI_DEBUGSSM,       /**< DEBUGSSM scan router. */
    GTI_C60,            /**< TMS320C60 processor (not supported). */
    GTI_ARM7,           /**< ARM7 processor family. */
    GTI_ARM9,           /**< ARM9 processor family. */
    GTI_ARM11,          /**< ARM11 processor family. */
    GTI_CORTEX_A8,      /**< Cortex A8 processor family. */
    GTI_CORTEX_A9,      /**< Cortex A9 processor family. */
    GTI_CORTEX_A9_MP,   /**< Cortex A9 processor family, multicore. */
    GTI_CORTEX_R,       /**< Cortex R processor family. */
    GTI_CORTEX_M,       /**< Cortex M processor family. */
    GTI_PROCESSOR_NONE, /**< Unknown or undefined device type. */
    GTI_C64X,           /**< TMS320C64xx processor family, Kelvin. */
    GTI_ETB,            /**< ETB trace buffer component family. */
    GTI_CORTEX_A15,     /**< Cortex A15 processor family. */
    GTI_C64P,           /**< TMS320C64xx+ processor family, GEM. */
    GTI_CORTEX_A7,      /**< Cortex A7 processor family. */
    GTI_CORTEX_M0,      /**< Cortex M0 processor family. */
    GTI_CORTEX_A53,     /**< Cortex A53 processor family. */
    GTI_C71,            /**< TMS320C71xx processor family */
    GTI_SEC_AP,         /**< SEC-AP processor family. */
    GTI_PROCESSOR_MAX   /**< Marks end of list. */
} GTI_PROCESSOR_TYPE;

/** Flags that define what debug features the driver supports for GTI_GETCAPABILITIES(). */
#define GTI_CAPABLE_BASE                    0x00000000U /**< Only supports basic features, non-debuggable device. */
#define GTI_CAPABLE_BP_HIDING               0x00000001U /**< Hides software breakpoints when doing memory accesses. */
#define GTI_CAPABLE_SYNC_RUN                0x00000002U /**< Capable of doing multi-processor synchronous run. */
#define GTI_CAPABLE_REAL_TIME               0x00000004U /**< Capable of real-time mode debugging. */
#define GTI_CAPABLE_STEPPING                0x00000008U /**< Capable of executing a single step. */
#define GTI_CAPABLE_MULTIPROC               0x00000010U /**< Capable of multiple instances. */
#define GTI_CAPABLE_IRQ                     0x00000020U /**< Requires an IRQ number (unused). */
#define GTI_CAPABLE_DMA                     0x00000040U /**< Requires DMA addresses (unused). */
#define GTI_CAPABLE_2ND_IOPORT              0x00000080U /**< Requires 2 I/O base port addresses (unused). */
#define GTI_CAPABLE_RUN_PROFILING           0x00000100U /**< Capable of profiling. */
#define GTI_CAPABLE_STEP_PROFILING          0x00000200U /**< Capable of profiling while single stepping. */
#define GTI_CAPABLE_GLOBAL_BKPT             0x00000400U /**< Capable of multi-processor global breakpoints. */
#define GTI_CAPABLE_MEMMAP                  0x00000800U /**< Capable of memory map (unused). */
#define GTI_CAPABLE_RTDX                    0x00001000U /**< Capable of supporting RTDX communications. */
#define GTI_CAPABLE_CLOCKSTEP               0x00002000U /**< Capable of executing a single-clock step. */
#define GTI_CAPABLE_NO_1ST_IOPORT           0x00004000U /**< Does not require I/O base port 1 address (unused). */
#define GTI_CAPABLE_RUDE_POLITE             0x00008000U /**< Capable of rude/polite mode switching. */
#define GTI_CAPABLE_NON_INTRUSIVE_STARTUP   0x00010000U /**< Capable of non-intrusive debug startup. */
#define GTI_CAPABLE_MULTIBOARD              0x00020000U /**< Capable of multi-board debugging. */
#define GTI_CAPABLE_THUNDERSTORM            0x00040000U /**< Supports XDS560 class debug probe features. */
#define GTI_CAPABLE_STEP_OVER_BP            0x00080000U /**< Capable of stepping over existing breakpoint. */
#define GTI_CAPABLE_SHARED_MEMORY           0x00100000U /**< Capable of shared memory debugging. */
#define GTI_CAPABLE_DONGLE                  0x00200000U /**< Capable of software dongle (unused). */
#define GTI_CAPABLE_FAST_DOWNLOAD           0x00400000U /**< Capable of supporting the TRG_XXX_DOWNLOAD flags. */
#define GTI_CAPABLE_READ_VERIFY             0x00800000U /**< Capable of doing a read/verify on memory writes. */
#define GTI_CAPABLE_CONNECT                 0x01000000U /**< Capable of target connect/disconnect. */
#define GTI_CAPABLE_CACHE_BYPASS            0x02000000U /**< Capable of bypassing the cache on memory reads. */
#define GTI_SYSTEM_FEATURES_CAP_ROUTER      0x04000000U /**< Driver is capable of providing router/system services. */
#define GTI_CAPABLE_CACHE_MEMORY_VIEWER     0x08000000U /**< Capable of supporting cache memory viewer. */
#define GTI_CAPABLE_QUERY_INTERFACE         0x10000000U /**< Supports the GTI_QUERY_INTERFACE() feature. */
#define GTI_CAPABLE_REALTIME_ONLY           0x20000000U /**< Must always be in real-time mode. */
#define GTI_CAPABLE_NON_DBG_MEMORY_ACCESS   0x40000000U /**< Non-debuggable device supports memory accesses. */
#define GTI_CAPABLE_NON_DBG_REGISTER_ACCESS 0x80000000U /**< Non-debuggable device supports register accesses. */

/** Flags that define what emulation features the driver supports for GTI_GET_EXT_CAPABILITIES(). */
#define GTI_EMUCAP_NULL                     0x00000000U /**< No additional emulation capabilities. */
#define GTI_EMUCAP_PRSC_COM                 0x00000001U /**< Capable of using PRSC module for power/reset control. */
#define GTI_EMUCAP_EXTENDED_STAT            0x00000002U /**< Capable of supplying extended status information. */
#define GTI_EMUCAP_LPRUN                    0x00000004U /**< Capable of executing in low power run mode. */
#define GTI_EMUCAP_PRSC_SYNC_RUN            0x00000008U /**< Capable of doing PRSC controlled synchronous run. */
#define GTI_EMUCAP_WIR                      0x00000010U /**< Capable of supporting wait-in-reset mode. */
/*                                          0x00000020U      Unassigned. */
#define GTI_EMUCAP_MMU_SUPPORT              0x00000040U /**< Driver is capable of providing MMU services. */
/*                                          0x00000080U      Unassigned. */
#define GTI_EMUCAP_MEM_LEVEL_INFO           0x00000100U /**< Supports GTI_GET_MEM_LEVEL_INFO(). */
/*                                          0x00000200U      Reserved, used internally by CCS. */
#define GTI_EMUCAP_PHYSICAL_PAGE_INFO       0x00000400U /**< Capable of address translation services. */
#define GTI_SYSTEM_FEATURES_CAP_ROUTER      0x04000000U /**< Driver is capable of providing router/system services. */

/** Flags that define what simulation features the driver supports for GTI_GET_EXT_CAPABILITIES(). */
#define GTI_SIMCAP_NULL                     0x00000000 /**< No additional simulation capabilities. */
#define GTI_SIMCAP_PINCONNECT               0x00000001 /**< Driver can connect a pin to a file. */
#define GTI_SIMCAP_PORTCONNECT              0x00000002 /**< Driver can connect a port to a file. */
#define GTI_SIMCAP_SIMEMUMODE               0x00000004 /**< Can switch between emulation or simulation mode. */

/** Capabilities type ID for GTI_GET_EXT_CAPABILITIES(). */
enum GTI_CAP_ID
{
    GTI_GEN_CAP, /**< Return the basic capabilities. */
    GTI_SIM_CAP, /**< Return the simulation capabilities. */
    GTI_EMU_CAP  /**< Return the emulation capabilities. */
};

/** Flag for which function to perform for GTI_CONFIG(). */
enum CONFIG_FUNCTION_TYPE 
{
    CONFIG_GET, /**< Retrieve the available configuration parameters. */
    CONFIG_SET, /**< Set the requested configuration parameters. */
    CONFIG_END  /**< Configuration is complete, free memory if necessary. */ 
};

/** Configuration parameter type for FIELD used by GTI_CONFIG(). */
enum FIELD_TYPE 
{
    FIELD_TYPE_STRING_LIST,  /**< String List choice parameter type. */
    FIELD_TYPE_STRING,       /**< String parameter type. */
    FIELD_TYPE_NUMBER,       /**< Number parameter type. */
    FIELD_TYPE_FILE_PATH,    /**< File/Path name parameter type. */
    FIELD_TYPE_CUSTOM,       /**< Custom parameter type (function pointer). */
    FIELD_TYPE_FILE_PATH_EXT /**< File/Path name with File extensions parameter type. */
};

/** String types for FIELD_STRING used by GTI_CONFIG(). */
enum STRING_TYPE 
{
    STRING_TYPE_EDIT,    /**< Editable string type. */
    STRING_TYPE_READONLY /**< Read-only string type. */ 
};

/** File/Path name types for FIELD_NUMBER used by GTI_CONFIG(). */
enum NUMBER_TYPE 
{
    NUMBER_TYPE_UNSIGNED_INT,        /**< Decimal unsigned integer. */
    NUMBER_TYPE_HEX,                 /**< Hexadecimal integer. */
    NUMBER_TYPE_UNSIZGNED_INT_OR_HEX /**< Decimal unsigned or hexadecimal integer. */
};

/** File/Path name types for FIELD_FILE_PATH and FIELD_FILE_PATH_EXT used by GTI_CONFIG(). */
enum FILE_PATH_TYPE 
{
    FILE_PATH_TYPE_FULL_FILE_PATH, /**< Full file and path name. */
    FILE_PATH_TYPE_DIRECTORY       /**< Directory path name only. */
};

/** String List choice parameter type for GTI_CONFIGPARAM_TYPE structure used by GTI_CONFIG(). */
typedef struct 
{
    int    nItemCount; /**< Number of strings in list. */
    char **aszItem;    /**< Array of strings to choose from. */
    int    nIndex;     /**< Index to chosen string. */
} FIELD_STRING_LIST;

/** String parameter type for GTI_CONFIGPARAM_TYPE structure used by GTI_CONFIG(). */
typedef struct 
{
    enum STRING_TYPE  nType;          /**< Type of string. */
    int               nMaxTextLength; /**< Maximum length of string. */
    char             *szText;         /**< Content of string. */
} FIELD_STRING;

/** Number parameter type for GTI_CONFIGPARAM_TYPE structure used by GTI_CONFIG(). */
typedef struct 
{
    enum NUMBER_TYPE nType;       /**< Type of number. */
    int              nRangeUpper; /**< Upper limit of number. */
    int              nRangeLower; /**< Lower limit of number. */
    int              nValue;      /**< Value of number. */
} FIELD_NUMBER;

/** File/Path name parameter type for GTI_CONFIGPARAM_TYPE structure used by GTI_CONFIG(). */
typedef struct 
{
    enum FILE_PATH_TYPE  nType;              /**< Type of File/Path name. */
    int                  nMaxFilePathLength; /**< Maximum length of File/Path name. */
    char                *szFilePath;         /**< File/Path name. */
} FIELD_FILE_PATH;

/** File/Path name with extensions parameter type for GTI_CONFIGPARAM_TYPE structure used by GTI_CONFIG(). */
typedef struct {
    enum FILE_PATH_TYPE  nType;              /**< Type of File/Path name. */
    int                  nMaxFilePathLength; /**< Maximum length of File/Path name. */
    char                *szFilePath;         /**< File/Path name. */
    char                *szExtensions;       /**< Expected file extensions. */
} FIELD_FILE_PATH_EXT;

/** Function type for FIELD_CUSTOM parameter type used by GTI_CONFIG(). */
typedef void (CUSTOM_FIELD_FUNCTION)(void);

/** Custom parameter type for GTI_CONFIGPARAM_TYPE structure used by GTI_CONFIG(). */
typedef struct 
{
    CUSTOM_FIELD_FUNCTION *pFunction;
} FIELD_CUSTOM;

/** Configuration parameter settings type for GTI_CONFIGPARAM_TYPE structure used by GTI_CONFIG(). */
typedef struct 
{
    enum FIELD_TYPE  nType;       /**< Type of configuration parameter. */
    char            *szName;      /**< Name of configuration parameter. */
    int              bCanBeEmpty; /**< Flag if configuration setting can be empty. */
    union _is                     /**< Union of various parameter types. */
    {
        FIELD_STRING_LIST   StringListField;   /**< String List choice parameter. */
        FIELD_STRING        StringField;       /**< String parameter. */
        FIELD_NUMBER        NumberField;       /**< Number parameter. */
        FIELD_FILE_PATH     FilePathField;     /**< File/Path name parameter. */
        FIELD_CUSTOM        CustomField;       /**< Custom parameter (function pointer). */
        FIELD_FILE_PATH_EXT FilePathFieldExt;  /**< File/Path name with File extensions parameter. */
    } is;
} FIELD;

/** Configuration parameters structure used by GTI_CONFIG(). */
typedef struct 
{
    int    nCount; /**< Number of elements in aField array. */
    FIELD *aField; /**< Array of parameter structs. */
} CONFIG_PARAM;
#define GTI_CONFIGPARAM_TYPE CONFIG_PARAM /**< Alternate name for configuration struct type */

/** Flags that define what action to perform by GTI_REALTIME_SWITCH(). */
#define GTI_STOP_TO_RT_MODE     0x1 /**< Switch from stop to real-time mode. */
#define GTI_RT_TO_STOP_MODE     0x2 /**< Switch from real-time to stop mode. */
#define GTI_START_IN_RT_MODE    0x3 /**< Initialize target in real-time mode. */
#define GTI_GET_RT_STATE        0x4 /**< Get current real-time mode state of the target. */
#define GTI_VALIDATE_SWITCH     0x5 /**< Validate that switching modes is OK at this time. */
#define GTI_ALLOW_SWITCH        0x6 /**< Setup to allow real-time mode switching. */
#define GTI_POLITE_TO_RUDE_MODE 0x7 /**< Switch from polite to rude mode. */
#define GTI_RUDE_TO_POLITE_MODE 0x8 /**< Switch from rude to polite mode. */
#define GTI_START_IN_STOP_MODE  0x9 /**< Initialize target in stop mode. */

/** Flags that define the capabilities for GTI_GET_NON_INTRUSIVE_CAPABILITIES(). */
#define GTI_REALTIME_ANYTIME_ACCESS( type ) ( ( type << 16 ) | type )

#define GTI_REALTIME_CAPABLE_MEMORY_READ            0x00000001 /**< Memory reads can be performed while running. */
#define GTI_REALTIME_CAPABLE_MEMORY_WRITE           0x00000002 /**< Memory writes can be performed while running. */
#define GTI_REALTIME_CAPABLE_REGISTER_READ          0x00000004 /**< Register reads can be performed while running. */
#define GTI_REALTIME_CAPABLE_REGISTER_WRITE         0x00000008 /**< Register writes can be performed while running. */
#define GTI_REALTIME_CAPABLE_SW_BREAKPOINT          0x00000010 /**< Software BPs can be set/cleared while running. */
#define GTI_REALTIME_CAPABLE_HW_BREAKPOINT          0x00000020 /**< Hardware BPs can be set/cleared while running. */
#define GTI_REALTIME_CAPABLE_PHYSICAL_MEMORY_READ   0x00000040 /**< Memory reads to physical memory can be 
                                                                                            performed while running*/
#define GTI_REALTIME_CAPABLE_PHYSICAL_MEMORY_WRITE  0x00000080 /**< Memory writes to physical memory can be 
                                                                                            performed while running*/
#define GTI_REALTIME_CAPABLE_INITIALIZE_CTOOLS      0x00000100 /**< Indicates it's safe to initialize ctools while running*/

// Indicates memory reads to physical memory can be performed regardless of the execution state
#define GTI_REALTIME_ANYTIME_CAPABLE_PHYSICAL_MEMORY_READ \
        GTI_REALTIME_ANYTIME_ACCESS( GTI_REALTIME_CAPABLE_PHYSICAL_MEMORY_READ )

// Indicates memory writes to physical memory can be performed regardless of the execution state
#define GTI_REALTIME_ANYTIME_CAPABLE_PHYSICAL_MEMORY_WRITE \
        GTI_REALTIME_ANYTIME_ACCESS( GTI_REALTIME_CAPABLE_PHYSICAL_MEMORY_WRITE )

// Indicates it's safe to initialize ctools regardless of the execution state
#define GTI_REALTIME_ANYTIME_CAPABLE_INITIALIZE_CTOOLS \
        GTI_REALTIME_ANYTIME_ACCESS( GTI_REALTIME_CAPABLE_INITIALIZE_CTOOLS )

/** Function type for GTI_QUERY_INTERFACE(). */
typedef GTI_RETURN_TYPE  (GTI_FN_QUERY_INTERFACE)
    (GTI_HANDLE_TYPE, GTI_STRING_TYPE, GTI_UINT32_TYPE, GTI_HANDLE_TYPE,
     GTI_UINT32_TYPE, GTI_QUERY_INTF_ERROR_TYPE, GTI_HANDLE_TYPE);

/** Function type for GTI_GET_PROC_ID() and GTI_GET_PROC_MINOR_ID(). */
typedef GTI_PROCID_TYPE (GTI_FN_GET_PROC_ID)(GTI_HANDLE_TYPE);

/** Function type for GTI_GET_EXT_CAPABILITIES(). */
typedef GTI_CAP_TYPE (GTI_FN_GET_EXT_CAPABILITIES)(GTI_HANDLE_TYPE, GTI_INT_TYPE);

/** Function type for GTI_SETUP_PROPERTIES(). */
typedef GTI_RETURN_TYPE (GTI_FN_SETUP_PROPERTIES)(GTI_STRING_TYPE, GTI_STRING_TYPE *, GTI_STRING_TYPE *, GTI_LEN_TYPE);

/** Function type for GTI_CONFIG(). */
typedef GTI_RETURN_TYPE (GTI_FN_CONFIG_EX)
    (GTI_HANDLE_TYPE, GTI_CONFIGPARAM_TYPE**, GTI_STRING_TYPE, enum CONFIG_FUNCTION_TYPE);

/** Function type for GTI_REALTIME_SWITCH(). */
typedef GTI_RETURN_TYPE (GTI_FN_REALTIME_SWITCH)(GTI_HANDLE_TYPE, GTI_INT16_TYPE);

/** Function type for GTI_GET_NON_INTRUSIVE_CAPABILITIES(). */
typedef GTI_CAP_TYPE (GTI_FN_GET_NON_INTRUSIVE_CAPABILITIES)(GTI_HANDLE_TYPE);

#ifndef GTI_NO_FUNCTION_DECLARATIONS
/** GTI_GETREV() - Retrieve the GTI API revision of driver.
 * 
 *  Returns the revision of the GTI API that was used to build the driver.
 *  This is used to ensure the API headers match the API used in the driver;
 *  this value should match the GTI_REV definition in gti.h.
 *
 * \return revision of the GTI API in the driver.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_GETREV(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_QUERY_INTERFACE() - Query for additional GTI features.
 * 
 *  A generic interface to query for custom GTI features. The purpose of adding
 *  such a generic query interface is to avoid adding new GTI API when a new
 *  feature (function) is added - such as the function of read cache TAG data.
 *
 * \return 0 on success, -1 on error. Explanation of error is returned via the 
 *         error parameter.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_QUERY_INTERFACE(
    GTI_HANDLE_TYPE            hpid,              /**< [in]  GTI API instance handle. */
    GTI_STRING_TYPE            feature_name,      /**< [in]  Requested feature name. */
    GTI_UINT32_TYPE            version,           /**< [in]  Requested feature version. */
    GTI_HANDLE_TYPE           *feature_handle,    /**< [out] Function pointer to the feature. */
    GTI_UINT32_TYPE           *supported_version, /**< [out] Feature version supported. */
    GTI_QUERY_INTF_ERROR_TYPE *error,             /**< [out] Reason for error return. */
    GTI_HANDLE_TYPE           *obj_inst           /**< [out] Object instance to use with feature. */
    );

/** GTI_GETPROCTYPE() - Get device type of device driver.
 * 
 *  Returns the device type supported by the driver as defined in the 
 *  GTI_PROCESSOR_TYPE enum. Note that the GTI API instance handle (hpid) is not
 *  used, so this can be called before calling GTI_INIT_EX().
 *  <br><br>
 *  While this call is fully supported, it is preferred to use the
 *  GTI_GET_PROC_ID() call instead to determine what type of target is being
 *  accessed.  
 *
 * \return device type.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_GETPROCTYPE(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle (unused). */
    );

/** GTI_GET_PROC_ID() - Get Proc ID of target device.
 * 
 *  Returns a 32-bit identifier, the Proc ID, of the target device. Note that 
 *  the GTI API instance handle (hpid) is optional, and you may call this before
 *  calling GTI_INIT_EX() by passing in 0 for hpid. If you do so, then this
 *  call returns a generic Proc ID for the device type(s) the driver supports. If
 *  called with a valid hpid after calling GTI_CONNECT(), the driver may return
 *  a more specific Proc ID for the connected device.
 *  <br><br>
 *  TODO: Describe proc id format
 * 
 * \return device Proc ID.
 */
GTI_EXPORT GTI_PROCID_TYPE
GTI_GET_PROC_ID(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_GET_PROC_MINOR_ID() - Get minor revision of target device.
 * 
 *  Returns a 32-bit minor revision number used to differentiate between versions
 *  of devices that share the same Proc ID. This should only be called after
 *  GTI_CONNECT() because this call may need to read information from the target
 *  to determine the revision.
 * 
 * \return device minor revision.
 */
GTI_EXPORT GTI_PROCID_TYPE 
GTI_GET_PROC_MINOR_ID(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_GET_EXT_CAPABILITIES() - Gets the supported features of the driver.
 * 
 *  Returns a collection of capability flags detailing what features the driver
 *  supports. Lets you select which set of capability flags are returned:
 *  basic features, emulation features, or simulation features.
 *  <br><br>
 *  Set id to GTI_GEN_CAP for basic capabilities (GTI_CAPABLE_ flags). <br>
 *  Set id to GTI_EMU_CAP for emulation capabilities (GTI_EMUCAP_ flags). <br>
 *  Set id to GTI_SIM_CAP for simulation capabilities (GTI_SIMCAP_ flags). <br>
 * 
 * \return the feature/capability flags for requested capability type.
 */
GTI_EXPORT GTI_CAP_TYPE 
GTI_GET_EXT_CAPABILITIES(
    GTI_HANDLE_TYPE hpid, /**< [in]  GTI API instance handle. */
    GTI_INT_TYPE    id    /**< [in]  Which type of capablities to return. */
    );

/** GTI_SETUP_PROPERTIES() - Sets the configuration parameters of the driver.
 *
 *  Call this immediately before GTI_INIT_EX() to set the driver's configuration
 *  parameters.  Parameters are passed as a pair of arrays. names contains the
 *  text names of the parameters, and values contains the values as strings. 
 *  board_cpuName is the debug probe name and target name (minus the '/' cpu name) 
 *  as was used for pathName in the GTI_INIT_EX() call.
 *  <br><br>
 *  If the driver does not export this call, then it may use GTI_CONFIG() to
 *  set its configuration parameters.
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE
GTI_SETUP_PROPERTIES(
    GTI_STRING_TYPE  board_cpuName, /**< [in]  Debug probe and target name. */
    GTI_STRING_TYPE *names,         /**< [in]  Array of strings containing the configuration parameter names. */
    GTI_STRING_TYPE *values,        /**< [in]  Array of strings containing the parameter values. */
    GTI_LEN_TYPE     nProperties    /**< [in]  The number of parameters in the names and values arrays. */
    );
                                   
/** GTI_CONFIG() - Controls getting and setting configuration parameters.
 * 
 *  This call allows discovery of what configuration parameters the driver
 *  supports, and then lets the caller choose what configurations to set. This
 *  should only be called after GTI_INIT_EX() and before GTI_CONNECT().
 *  <br><br>
 *  In legacy mode, a setup application would use the discovery mode to determine
 *  what parameters could be set. Currently, this is not required because the
 *  parameters are now described in the driver's XML files, and this API may 
 *  be used only to set the parameters.
 *  <br><br>
 *  ppParamList is used to retrieve or send the configuration structure. <br>
 *  szBoardName is the debug probe and target name (minus the '/' cpu name) as was 
 *  used for pathName in the GTI_INIT_EX() call.
 *  <br><br>
 *  Set flag to CONFIG_GET to retrieve the available parameters. The parameters
 *  will be returned via ppParamList as a GTI_CONFIGPARAM_TYPE struct. <br>
 *  Set flag to CONFIG_SET to set specific configurations. Pass the requested
 *  parameters via ppParamList as a GTI_CONFIGPARAM_TYPE struct. <br>
 *  Set flag to CONFIG_END to tell the driver to free any memory used during the
 *  configuration process. <br>
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE  
GTI_CONFIG(
    GTI_HANDLE_TYPE             hpid,        /**< [in]     GTI API instance handle. */
    GTI_CONFIGPARAM_TYPE      **ppParamList, /**< [in,out] Pointer to configuration struct. */
    GTI_STRING_TYPE             szBoardName, /**< [in]     Debug probe and target name. */
    enum CONFIG_FUNCTION_TYPE   flag         /**< [in]     Flag to determine function type. */
    );

#if TRG_REALTIME
/** GTI_REALTIME_SWITCH() - Controls real-time mode setting.
 * 
 *  This call controls how the real-time vs. stop mode settings are used.
 *  <br><br>
 *  Set request to GTI_STOP_TO_RT_MODE to switch from stop to real-time mode. <br>
 *  Set request to GTI_RT_TO_STOP_MODE to switch from real-time to stop mode. <br>
 *  Set request to GTI_START_IN_RT_MODE to initialize target in real-time mode. <br>
 *  Set request to GTI_GET_RT_STATE to get current real-time mode state of the target. <br>
 *  Set request to GTI_VALIDATE_SWITCH to validate that switching modes is OK at this time. <br>
 *  Set request to GTI_ALLOW_SWITCH to setup to allow real-time mode switching. <br>
 *  Set request to GTI_POLITE_TO_RUDE_MODE to switch from polite to rude mode. <br>
 *  Set request to GTI_RUDE_TO_POLITE_MODE to switch from rude to polite mode. <br>
 *  Set request to GTI_START_IN_STOP_MODE to initialize target in stop mode. <br>
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE
GTI_REALTIME_SWITCH(
    GTI_HANDLE_TYPE hpid,   /**< [in]  GTI API instance handle. */
    GTI_INT16_TYPE  request /**< [in]  Flag to determine action to take. */
    );
#endif /* TRG_REALTIME */

/** GTI_GET_NON_INTRUSIVE_CAPABILITIES() - Gets the non-intrusive features of the driver.
 * 
 *  If exported by the driver, this call returns a collection of flags that define 
 *  what non-intrusive features the driver supports (GTI_REALTIME_CABABLE_ flags).
 *  A return of 0 indicates the driver has no support for non-instrusive features;
 *  all accesses to memory, registers, and breakpoints must be done while the target
 *  is halted. Otherwise, the flags for the supported features are set in the return 
 *  value. If the driver supports full realtime mode (GTI_CAPABLE_REAL_TIME), this call
 *  is ignored, and all non-intrusive accesses are assumed to be available.  Make this
 *  call only after GTI_CONNECT().
 *
 * \return the non-intrusive capability flags for the driver.
 */
GTI_EXPORT GTI_CAP_TYPE 
GTI_GET_NON_INTRUSIVE_CAPABILITIES(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );
#endif /* GTI_NO_FUNCTION_DECLARATIONS */

#ifdef __cplusplus
};
#endif

#endif  /* GTI_CONFIG_H */

/* End of File */
