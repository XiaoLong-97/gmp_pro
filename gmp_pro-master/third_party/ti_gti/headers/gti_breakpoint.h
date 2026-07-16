/** \file gti_breakpoint.h
 * 
 *  This header defines the GTI APIs for handling breakpoints on target device. 
 * 
 *  Copyright (c) 1998-2015, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_BREAKPOINT_H
#define GTI_BREAKPOINT_H

/** Export attribute for GTI_SETBP_EX() and GTI_CLEARBP_EX(). */
#if TRG_MEMORY_ACCESS_SIZE_BP_EXT
#define TRG_MEMORY_ACCESS_SIZE_BP_EXT_EXPORT GTI_EXPORT
#else
#define TRG_MEMORY_ACCESS_SIZE_BP_EXT_EXPORT 
#endif


#ifdef __cplusplus
extern "C" {
#endif


/** Flags to define type of breakpoint to set or clear.
 *  Used by GTI_SETBP_EX(), GTI_SETBP(), GTI_CLEARBP_EX(), GTI_CLEARBP(),
 *  and GTI_BP_TEST().
 */
#define GTI_BRK_SWBP    0x0000 /**< Software breakpoint. */
#define GTI_BRK_HWBP    0x00FF /**< Hardware breakpoint. */
#define GTI_BRK_SHORT   0x1000 /**< Short (ARM thumb mode) breakpoint. */
#define GTI_BRK_SHARED  0x2000 /**< Breakpoint is already set in shared memory. */

/** Flags for current state of a breakpoint used by GTI_BP_TEST(). */
typedef enum GTI_BP_STAT
{
    GTI_BP_STAT_VALID,  /**< Breakpoint is still valid. */
    GTI_BP_STAT_INVALID /**< Breakpoint is not valid. */
}GTI_BP_STAT;


/** Function type for GTI_SETBP_EX() and GTI_CLEARBP_EX(). */
typedef GTI_RETURN_TYPE (GTI_FN_BP_EX)
    (GTI_HANDLE_TYPE, GTI_ADDRS_TYPE, GTI_INT16_TYPE, GTI_LEN_TYPE, GTI_INT_TYPE);


/** Function type for GTI_SETBP_EX_64() and GTI_CLEARBP_EX_64(). */
typedef GTI_RETURN_TYPE(GTI_FN_BP_EX_64)
(GTI_HANDLE_TYPE, GTI_ADDRS64_TYPE, GTI_INT16_TYPE, GTI_LEN_TYPE, GTI_INT_TYPE);

/** Function type for GTI_SETBP() and GTI_CLEARBP(). */
typedef GTI_RETURN_TYPE (GTI_FN_BP)
    (GTI_HANDLE_TYPE, GTI_ADDRS_TYPE, GTI_INT16_TYPE, GTI_LEN_TYPE);

/** Function type for GTI_SETBP() and GTI_CLEARBP(). */
typedef GTI_RETURN_TYPE(GTI_FN_BP_64)
(GTI_HANDLE_TYPE, GTI_ADDRS64_TYPE, GTI_INT16_TYPE, GTI_LEN_TYPE);

/** Function type for GTI_DONE_REMOVING_DEBUG_STATE(). */
typedef GTI_RETURN_TYPE (GTI_FN_BP_RESET)(GTI_HANDLE_TYPE);

/** Function type for GTI_BP_TEST(). */
typedef GTI_RETURN_TYPE (GTI_FN_BP_TEST)
    (GTI_HANDLE_TYPE, GTI_ADDRS_TYPE, GTI_INT16_TYPE, 
     GTI_LEN_TYPE, GTI_INT_TYPE, GTI_BP_STAT*);

/** Function type for GTI_BP_TEST_64(). */
typedef GTI_RETURN_TYPE(GTI_FN_BP_TEST_64)
(GTI_HANDLE_TYPE, GTI_ADDRS64_TYPE, GTI_INT16_TYPE,
	GTI_LEN_TYPE, GTI_INT_TYPE, GTI_BP_STAT*);

#ifndef GTI_NO_FUNCTION_DECLARATIONS
/** GTI_SETBP_EX() - Set a breakpoint on target device.
 *
 *  This function sets a breakpoint on target device.  This call extends the
 *  GTI_SETBP() call by by letting caller choose a specific access width for 
 *  the memory access for setting software breakpoints.
 *
 * \return 0 on success, -1 on error. 
 */
TRG_MEMORY_ACCESS_SIZE_BP_EXT_EXPORT GTI_RETURN_TYPE 
GTI_SETBP_EX( 
    GTI_HANDLE_TYPE hpid,      /**< [in]  GTI API instance handle. */
    GTI_ADDRS_TYPE  address,   /**< [in]  Breakpoint address. */
    GTI_INT16_TYPE  bpType,    /**< [in]  Type of breakpoint to set. */
    GTI_LEN_TYPE    count,     /**< [in]  Count before halting device. */
    GTI_INT_TYPE    accessSize /**< [in]  Memory access width. */
    );

/** GTI_SETBP() - Set a breakpoint on target device.
 *
 *  This function sets a breakpoint on target device. count is used to delay
 *  halting the target until a "count" number of times the breakpoint has
 *  been hit.  count is only used with hardware breakpoints, for software
 *  breakpoints, you must set count to 1.
 *
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE
GTI_SETBP(
    GTI_HANDLE_TYPE hpid,    /**< [in]  GTI API instance handle. */
    GTI_ADDRS_TYPE  address, /**< [in]  Breakpoint address. */
    GTI_INT16_TYPE  bpType,  /**< [in]  Type of breakpoint to set. */
    GTI_LEN_TYPE    count    /**< [in]  Count before halting device. */
    );

/** GTI_CLEARBP_EX() - Clear a breakpoint on target device.
 *
 *  This function clears a breakpoint on target device.  This call extends the
 *  GTI_CLEARBP() call by by letting caller choose a specific access width for 
 *  the memory access for clearing software breakpoints.
 *
 * \return 0 on success, -1 on error. 
 */
TRG_MEMORY_ACCESS_SIZE_BP_EXT_EXPORT GTI_RETURN_TYPE 
GTI_CLEARBP_EX(
    GTI_HANDLE_TYPE hpid,      /**< [in]  GTI API instance handle. */
    GTI_ADDRS_TYPE  address,   /**< [in]  Breakpoint address. */
    GTI_INT16_TYPE  bpType,    /**< [in]  Type of breakpoint to clear. */
    GTI_LEN_TYPE    count,     /**< [in]  Count before halting device. */
    GTI_INT_TYPE    accessSize /**< [in]  Memory access width. */
    );

/** GTI_CLEARBP() - Clear a breakpoint on target device.
 *
 *  This function clears a breakpoint on target device.
 *
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_CLEARBP(
    GTI_HANDLE_TYPE hpid,    /**< [in]  GTI API instance handle. */
    GTI_ADDRS_TYPE  address, /**< [in]  Breakpoint address. */
    GTI_INT16_TYPE  bpType,  /**< [in]  Type of breakpoint to clear. */
    GTI_LEN_TYPE    count    /**< [in]  Count before halting device. */
    );

/** GTI_DONE_REMOVING_DEBUG_STATE() - Clears all breakpoints on target device.
 *
 *  This function clears all breakpoints that have been set on target device.
 *
 * \return 0 on success, -1 on error. 
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_DONE_REMOVING_DEBUG_STATE(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_BP_TEST() - Tests if a breakpoint is still set on target device.
 *
 *  This function tests whether or not a breakpoint is still set on the target
 *  device. This is primarily used when the device has been powered down in
 *  low power mode, and it may be possible that breakpoints in memory or even
 *  hardware breakpoint settings have been cleared.
 *
 * \return 0 on success, -1 on error. State of breakpoint returned in bpState.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_BP_TEST( 
    GTI_HANDLE_TYPE  hpid,       /**< [in]  GTI API instance handle. */
    GTI_ADDRS_TYPE   address,    /**< [in]  Breakpoint address. */
    GTI_INT16_TYPE   bpType,     /**< [in]  Type of breakpoint to test. */
    GTI_LEN_TYPE     count,      /**< [in]  Count before halting device. */
    GTI_INT_TYPE     accessSize, /**< [in]  Memory access width. */
    GTI_BP_STAT     *bpState     /**< [out] Pointer to return state of breakpoint. */
    );

/** GTI_NUM_HBP_TYPES() - Gets the number of types of hardware breakpoints.
 *
 *  This function gets the number of different types of hardware breakpoints
 *  supported by the driver and target device.
 *
 * \return number of types of hardware breakpoints. 
 */
GTI_EXPORT GTI_RETURN_TYPE
GTI_NUM_HBP_TYPES(
    GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );

/** GTI_GET_HBP_TYPE_NAME() - Gets the description of a hardware breakpoint type.
 *
 *  This function gets the description of a hardware breakpoint type where
 *  hbpType is the index of the type. Use GTI_NUM_HBP_TYPES() to get the 
 *  range of indices for types (hardware breakpoint types start at index 1). 
 *  Note that most drivers will return an empty string when only one type is 
 *  supported.
 *
 * \return the description of a hardware breakpoint type.
 */
GTI_EXPORT GTI_STRING_TYPE 
GTI_GET_HBP_TYPE_NAME(
    GTI_HANDLE_TYPE hpid,   /**< [in]  GTI API instance handle. */
    GTI_INT16_TYPE  hbpType /**< [in]  Index to hardware breakpoint type. */
    );

/** GTI_WAS_HBP_HIT() - Determines if target device hit a hardware breakpoint.
 *
 *  This function determines if the reason the target device halted is because
 *  it hit a hardware breakpoint.
 *
 * \return non-zero if hardware breakpoint was hit. 
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_WAS_HBP_HIT(
    GTI_HANDLE_TYPE  hpid,    /**< [in]  GTI API instance handle. */
    GTI_ADDRS_TYPE   address, /**< [in]  Breakpoint address. */
    GTI_INT16_TYPE   bpType,  /**< [in]  Type of breakpoint. */
    GTI_LEN_TYPE     count    /**< [in]  Count before halting device. */
    );

/** GTI_ENABLE_GLOBAL_BKPTS() - Enable global breakpoints.
 *
 *  This function turns on or off the use of global breakpoints by the target
 *  device. When turned on, the target will halt in response to global events
 *  as triggered by the EMU0/1 pins on the emulation header. Set enableFlag
 *  to 1 to turn on global breakpoints.  Set enableFlag to 0 to turn off
 *  global breakpoints.
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_ENABLE_GLOBAL_BKPTS(
    GTI_HANDLE_TYPE hpid,      /**< [in]  GTI API instance handle. */
    GTI_INT16_TYPE  enableFlag /**< [in]  Flag to turn on or off global breakpoints. */
    );
#endif /* GTI_NO_FUNCTION_DECLARATIONS */


#ifdef __cplusplus
};
#endif

#endif  /* GTI_BREAKPOINT_H */

/* End of File */
