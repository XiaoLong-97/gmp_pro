/** \file gti_execution.h
 *
 *  This header defines the GTI APIs for controlling execution state (halt, run,
 *  step) of target device.
 *
 *  Copyright (c) 1998-2015, Texas Instruments Inc., All rights reserved.
 * 
 *  2024.11.21 This file has been modified.
 *  
 */

#ifndef GTI_EXECUTION_H
#define GTI_EXECUTION_H

#ifdef __cplusplus
extern "C"
{
#endif

/** Flags to customize the behavior of the execution APIs.
 *  Used by GTI_HALT(), GTI_RUN_EX(), adn GTI_STEP().
 */
#define GTI_RUN_ATTR_SYNC         0x01  /**< Synchronous (global) run. */
#define GTI_RUN_ATTR_PROFILE      0x02  /**< Run with profiling enabled. */
#define GTI_RUN_ATTR_FREE         0x04  /**< Free run mode (debugging disabled). */
#define GTI_RUN_ATTR_INT_DISABLED 0x08  /**< Run with interrupts disabled. */
#define GTI_RUN_ATTR_CLOCK        0x10  /**< Run single clock cycle (unused). */
#define GTI_RUN_ATTR_LOW_PWR      0x40  /**< Run in low power mode. */
#define GTI_SYNC_RUN_ROUTER       0x80  /**< Synchronous (global) run via router (unused). */
#define GTI_RUN_ATTR_GB_ENABLED   0x100 /**< Indicate that global breakpoints are enabled. */

    /** Addtional run parameters used by GTI_RUN_EX(). */
    typedef struct
    {
        GTI_UINT32_TYPE m_structRevision; /**< GTI_RUN_INFO revision number. */
        GTI_UINT32_TYPE m_structLength;   /**< Size of GTI_RUN_INFO structure. */
        GTI_UINT32_TYPE m_count;          /**< Number of instructions to execute, 0 means normal run. */
    } GTI_RUN_INFO;
#define GTI_RUN_INFO_REV 0x1 /**< Revision of the GTI_RUN_INFO structure. */

    /** Function type for GTI_RUN_EX(). */
    typedef GTI_RETURN_TYPE(GTI_FN_RUN_EX)(GTI_HANDLE_TYPE, GTI_INT16_TYPE, GTI_RUN_INFO *);

    /** Function type for GTI_HALT(), GTI_RUN(), GTI_STEP() */
    typedef GTI_RETURN_TYPE(GTI_FN_EXEC)(GTI_HANDLE_TYPE, GTI_INT16_TYPE);

    /** Function type for GTI_HALT(), GTI_RUN().GTI_STEP() */
    typedef GTI_RETURN_TYPE(GTI_FN_GLOBALSTART)(GTI_HANDLE_TYPE);

#ifndef GTI_NO_FUNCTION_DECLARATIONS
    /** GTI_HALT() - Halt target device.
     *
     *  This function halts execution of code on the target device. Set
     *  runAttrFlag to GTI_RUN_ATTR_SYNC to queue a synchronous run.
     *
     * \return 0 on success, -1 on error.
     */
    GTI_EXPORT GTI_RETURN_TYPE GTI_HALT(GTI_HANDLE_TYPE hpid,      /**< [in]  GTI API instance handle. */
                                        GTI_INT16_TYPE runAttrFlag /**< [in]  Optional attribute flags. */
    );

    /** GTI_RUN() - Run target device.
     *
     *  This function starts the execution of code on target device until an
     *  external event halts the target. The runAttrFlag parameter may be set
     *  to: GTI_RUN_ATTR_SYNC, GTI_RUN_ATTR_PROFILE, GTI_RUN_ATTR_FREE, or
     *  GTI_RUN_ATTR_LOW_PWR.
     *
     * \return 0 on success, -1 on error.
     */
    GTI_EXPORT GTI_RETURN_TYPE GTI_RUN(GTI_HANDLE_TYPE hpid,      /**< [in]  GTI API instance handle. */
                                       GTI_INT16_TYPE runAttrFlag /**< [in]  Optional attribute flags. */
    );

    /** GTI_RUN_EX() - Run target device for a number of instructions.
     *
     *  This function starts the execution of code on target device for
     *  a number of instructions. The runAttrFlag parameter may be set to:
     *  GTI_RUN_ATTR_SYNC, GTI_RUN_ATTR_PROFILE, GTI_RUN_ATTR_FREE, or
     *  GTI_RUN_ATTR_LOW_PWR. Set the m_count member of additionalInfo to
     *  a number to execute that number of instructions. Otherwise, set
     *  m_count to zero to execute code until an external event halts the
     *  target.
     *
     * \return 0 on success, -1 on error.
     */
    GTI_EXPORT GTI_RETURN_TYPE GTI_RUN_EX(GTI_HANDLE_TYPE hpid,        /**< [in]  GTI API instance handle. */
                                          GTI_INT16_TYPE runAttrFlag,  /**< [in]  Optional attribute flags. */
                                          GTI_RUN_INFO *additionalInfo /**< [in]  Additional parameters structure. */
    );

    /** GTI_STEP() - Single step target device.
     *
     *  This function executes a single step on the target device. Set
     *  runAttrFlag to GTI_RUN_ATTR_SYNC to queue a synchronous run. Set
     *  runAttrFlag to GTI_RUN_ATTR_INT_DISABLED to disable interrupts
     *  during the step.
     *
     * \return 0 on success, -1 on error.
     */
    GTI_EXPORT GTI_RETURN_TYPE GTI_STEP(GTI_HANDLE_TYPE hpid,      /**< [in]  GTI API instance handle. */
                                        GTI_INT16_TYPE runAttrFlag /**< [in]  Optional attribute flags. */
    );

    /** GTI_GLOBALSTART() - Start a synchronous run.
     *
     *  This function starts the execution of a queue of synchronous execution
     *  commands. To queue up synchronous commands, call the desired execution
     *  APIs on each target with the GTI_RUN_ATTR_SYNC set in runAttrFlag.  After
     *  the last target device has been queued, issue this call to any one of the
     *  targets in the queue.
     *
     * \return 0 on success, -1 on error.
     */
    GTI_EXPORT GTI_RETURN_TYPE GTI_GLOBALSTART(GTI_HANDLE_TYPE hpid /**< [in]  GTI API instance handle. */
    );
#endif /* GTI_NO_FUNCTION_DECLARATIONS */

#ifdef __cplusplus
};
#endif

#endif /* GTI_EXECUTION_H */

/* End of File */
