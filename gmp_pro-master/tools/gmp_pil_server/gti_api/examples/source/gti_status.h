/** \file gti_status.h
 * 
 *  This header defines the GTI APIs to retrieve the current status of the
 *  target device.
 * 
 *  Copyright (c) 1998-2016, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_STATUS_H
#define GTI_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif


/** Status values that can be returned from GTI_STAT(). */
enum GTI_STATUS_TYPE
{
    GTI_STATUS_RUNNING,              /**< Target device is running in debug mode. */
    GTI_STATUS_HALTED,               /**< Target device is halted. */
    GTI_STATUS_NOPOWER,              /**< Target board has no power. */
    GTI_STATUS_ILLOP,                /**< Target device halted because of illegal operation. */
    GTI_STATUS_COMM,                 /**< Debug probe lost communications with target board. */
    GTI_STATUS_ERROR,                /**< An error occurred retrieving status. */
    GTI_STATUS_HW_BKPT_HIT,          /**< Target device halted because of hardware breakpoint. */
    GTI_STATUS_NO_CLOCK,             /**< Target board has no JTAG clock. */
    GTI_STATUS_SW_BKPT_HIT,          /**< Target device halted because of software breakpoint. */
    GTI_STATUS_FREE_RUNNING,         /**< Target device is running free (not under debug control). */
    GTI_STATUS_CABLE_BREAK,          /**< Debug probe cable is disconnected from the target board. */
    GTI_STATUS_DISCONNECTED_RUNNING, /**< Target device was disconnected while running. */
    GTI_STATUS_DISCONNECTED_HALTED,  /**< Target device was disconnected while halted. */
    GTI_STATUS_NON_DEBUG_NORMAL,     /**< Non-debuggable device state unchanged since last status call. */
    GTI_STATUS_NON_DEBUG_CHANGE,     /**< Non-debuggable device state has changed. */
    GTI_STATUS_GLOBAL_BKPT_HIT,      /**< Target device halted because of global breakpoint. */
    GTI_STATUS_HALT_CIO_SEMIHOSTING  /**< Target halted due to CIO/Semi-hosting SWBP. */
};

/** Status values that can be returned from GTI_STAT_EX2(). */
typedef enum 
{
    /** Execution status values. */
    GTI_STAT_UNKNOWN=0,                   /**< Target device execution status could not be determined. */
	GTI_STAT_RUN,				  /**< Target device is running in debug mode. */
    GTI_STAT_LOW_POWER_RUN,               /**< Target device is running in low power mode. */
    GTI_STAT_FREE_RUN,                    /**< Target device is running free (not under debug control). */
    GTI_STAT_HALTED_USER,                 /**< Target device halted because of user request. */
    GTI_STAT_HALTED_SWBP,                 /**< Target device halted because of software breakpoint. */
    GTI_STAT_HALTED_HWBP,                 /**< Target device halted because of hardware breakpoint. */
    GTI_STAT_HALTED_OTHER,                /**< Target device halted for undetermined reason. */
    GTI_STAT_HALTED_GBLBP,                /**< Target device halted because of global breakpoint. */
    GTI_STAT_HALTED_ASYS,                 /**< Halted by analysis break. */
    GTI_STAT_HALTED_SEMI_HOSTING,         /**< Halted by semi-hosting breakpoint. */

    /** Power status values. */
    GTI_STAT_POWERED = 0x100,             /**< Target device has power. */
    GTI_STAT_UNPOWERED,                   /**< Target device is powered down. */
    GTI_STAT_POWERED_DBG_OVERRIDE,        /**< Target device has power (forced by debug). */

    /** Reset status values. */
    GTI_STAT_RESET_ASSERTED = 0x200,      /**< Reset is currently asserted on target device. */
    GTI_STAT_RESET_SINCE_LAST_STAT,       /**< Target device was reset since last status call. */
    GTI_STAT_RESET_NONE,                  /**< Reset is not asserted on target device. */
    GTI_STAT_RESET_BLOCK_ENABLE,          /**< Reset block mode is enabled. */

    /** Secure status values. */
    GTI_STAT_SECURE_MODE = 0x300,         /**< Target device is in secure mode. */
    GTI_STAT_NON_SECURE_MODE,             /**< Target device is in non-secure mode. */

    /** Connection status values. */
    GTI_STAT_CONNECTED = 0x400,           /**< Target device is connected. */
    GTI_STAT_DISCONNECTED,                /**< Target device is disconnected. */

    /** Error status values. */
    GTI_STAT_ERR_ILLEGAL_OP = 0x500,      /**< Illegal operation was attempted. */
    GTI_STAT_ERR_COMM,                    /**< Debug probe lost communications with target board. */
    GTI_STAT_ERR_NO_JTAG_CLK,             /**< Target board has no JTAG clock. */
    GTI_STAT_ERR_CABLE_BREAK,             /**< Debug probe cable is disconnected from the target board. */
    GTI_STAT_DEBUG_COMM_POWER_LOSS,       /**< Target board has no power. */
    GTI_STAT_STUCK_IN_FAULT,              /**< Target is stuck in a fault state. */
    GTI_STAT_CLOCK_DISAPPEARED,           /**< A clock disappeared on the target. */
    GTI_STAT_FAULT_OCCURRED,               /**< A fault occurred on the target. */

    /** Misc. status values. */
    GTI_STAT_NON_DEBUG_NO_CHANGE = 0x600, /**< Non-debuggable device state unchanged since last status call. */
    GTI_STAT_NON_DEBUG_CHANGE,            /**< Non-debuggable device state has changed. */

    /** Rewind status values. (Only valid for simulators.) */
    GTI_STAT_SIM_FORWARD = 0x1000,        /**< Advance normally (unused, simulators only). */
    GTI_STAT_SIM_REWIND                   /**< Rewind mode (unused, simulators only). */

} GTI_STAT_TYPE;

/** Status return structure for GTI_STAT_EX2(). */
typedef struct GTI_STAT_STRUCT_ {
        GTI_STAT_TYPE   exeState;         /**< Execution status. */
        GTI_STAT_TYPE   powerStatus;      /**< Power status. */
        GTI_STAT_TYPE   resetStatus;      /**< Reset status. */
        GTI_STAT_TYPE   secureStatus;     /**< Secure status. */
        GTI_STAT_TYPE   connectionStatus; /**< Connection status. */
        GTI_STAT_TYPE   errorStatus;      /**< Error status. */
        GTI_STAT_TYPE   miscStatus;       /**< Misc. status. */
        GTI_STAT_TYPE   rewindStatus;     /**< Rewind status (only valid for simulators). */
}GTI_STAT_STRUCT;

/** Indices of which target property to return for GTI_GET_TARGET_PROPERTIES(). */
#define GTI_TRG_BIG_ENDIAN        0x00000001 /**< Request endianness of target device. */
#define GTI_TRG_BOARD_REV         0x00000002 /**< Request board revision of target. */
#define GTI_TRG_SILICON_REV       0x00000003 /**< Request device (silicon) revision of target. */
#define GTI_TRG_DEVICE_DRIVER_REV 0x00000004 /**< Request driver revision. */
#define GTI_TRG_CACHE_BYPASS      0x00000005 /**< Request if target supports cache bypass. */
#define GTI_TRG_CPU_MODE          0x00000006 /**< Request current cpu mode - ARMv8 only */

#define GTI_CPU_MODE_AARCH32 1
#define GTI_CPU_MODE_AARCH64 2

/** Function type for GTI_STAT(). */
typedef enum GTI_STATUS_TYPE (GTI_FN_STAT)(GTI_HANDLE_TYPE hpid); 

/** Function type for GTI_STAT_EX2(). */
typedef GTI_RETURN_TYPE (GTI_FN_STAT_EX2)(GTI_HANDLE_TYPE hpid, GTI_STAT_STRUCT *stat);

/** Function type for GTI_GET_TARGET_PROPERTIES(). */
typedef GTI_LRETURN_TYPE (GTI_FN_GET_TARGET_PROPERTIES)(GTI_HANDLE_TYPE hpid, GTI_INT_TYPE ndx);


#ifndef GTI_NO_FUNCTION_DECLARATIONS
/** GTI_STAT() - Retrieve current status of the target device.
 *
 *  This function returns a GTI_STATUS_TYPE value representing the most
 *  relevent description of the target device's current status.
 *
 * \return current status value.
 */
GTI_EXPORT enum GTI_STATUS_TYPE 
GTI_STAT(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_STAT_EX2() - Retrieve extended status of the target device.
 *
 *  This function returns extended status of the target device
 *  in a GTI_STAT_STRUCT structure.
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE
GTI_STAT_EX2(
    GTI_HANDLE_TYPE  hpid, /**< [in]  GTI API instance handle. */
    GTI_STAT_STRUCT *stat  /**< [out] Extended status of target. */
    );

/** GTI_GET_TARGET_PROPERTIES() - Retrieve properties of the target device.
 *
 *  This function returns various properties of the target device.  Which
 *  property to retrieve is determined by the property index in ndx.
 *  <br><br>
 *  Set ndx to GTI_TRG_BIG_ENDIAN to retrieve target endianness. 0 = little
 *  endian, 1 = big endian. <br>
 *  Set ndx to GTI_TRG_BOARD_REV to retrieve target board revision. <br>
 *  Set ndx to GTI_TRG_SILICON_REV to retrieve target device (silicon) revision. <br>
 *  Set ndx to GTI_TRG_DEVICE_DRIVER_REV to retrieve device driver revision. <br>
 *  Set ndx to GTI_TRG_CACHE_BYPASS to retrieve if device supports cache <br>
 *  bypass (C62x and C67x devices only).
 *
 * \return requested property value.
 */
GTI_EXPORT GTI_LRETURN_TYPE
GTI_GET_TARGET_PROPERTIES(
    GTI_HANDLE_TYPE  hpid, /**< [in]  GTI API instance handle. */
    GTI_INT_TYPE     ndx   /**< [in]  Index of which property to return. */
    );
#endif /* GTI_NO_FUNCTION_DECLARATIONS */


#ifdef __cplusplus
}
#endif

#endif /* GTI_STATUS_H */

/* End of File */

