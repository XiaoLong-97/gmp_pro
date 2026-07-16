/** \file TargetAdapterIntf.h
 * 
 *  This header defines the APIs for creating and deleting instances
 *  of the TargetAdapter class.
 * 
 *  Copyright (c) 2011-2015, Texas Instruments Inc., All rights reserved.
 */

/** \page TargetAdapter TargetAdapter
 * 
 *  This documentation describes the two functions exported from the
 *  TargetAdapter.dll library.  These functions are used to create and
 *  delete instances of the TargetAdapter class that can be used with
 *  the GTI_INIT_EX() function of the GTI API.
 *
 *  The TargetAdapter class is a thin wrapper around device drivers to
 *  allow drivers to access other devices without a large overhead.  One
 *  main use of the TargetAdapter is to allow drivers to access their
 *  parent router (e.g. ICEPick) so that can have access to advanced power
 *  domain control, system resets, and other features.  Another main 
 *  use is for devices that have no direct connection to JTAG and can only
 *  be accessed via another device's memory space. The TargetAdapter
 *  instance to the host device lets the driver communicate with the child 
 *  device.
 *
 *  To use this interface, load the TargetAdapter.dll library. Use the 
 *  CreateTargetAdapter() call to create a new instance of the TargetAdapter
 *  for the desired host or device. The pointer returned can be used with 
 *  the appropriate fields in the GTI_INIT_INFO structure.  When done, use 
 *  the DeleteTargetAdapter() call to properly dispose of the instance.
 */

#ifndef TARGETADAPTERINTF_H
#define TARGETADAPTERINTF_H


#ifdef __cplusplus
extern "C" {
#endif


/** Function type for CreateTargetAdapter(). */
typedef void* (CreateTargetAdapter_t)(char*, char*, char*, unsigned int, void*);

/** Function type for DeleteTargetAdapter(). */
typedef void (DeleteTargetAdapter_t)(void*);


#ifndef TA_NO_FUNCTION_DECLARATIONS
/** CreateTargetAdapter() - Create a TargetAdapter instance.
 *
 *  Creates an instance of the TargetAdapter class.  Loads the given 
 *  driver library and completes the driver's initialization call.
 *  
 *  Requires that the following directories are located in the system
 *  search path, or that any libraries required by the driver file
 *  are preloaded.
 *  - .../ccs_base/common/bin
 *  - .../ccs_base/common/uscif
 *  - .../ccs_base/emulation/drivers
 *
 *  Note that portAddress is only used with Spectrum Digital emulators
 *  and specifies what class of emulator is being used.  (e.g. use 
 *  0x510 for portAddress when using the SD XDS510USB emulator).
 *
 * \return pointer to a new TargetAdapter instance on success, or null if  
 *         there was an error loading or initializing the driver.
 */
void
*CreateTargetAdapter(
    char         *driver,      /**< File name of driver file to use. */
    char         *boardName,   /**< Target board and device name. */  
    char         *configFile,  /**< Board config file path and name. */
    unsigned int  portAddress, /**< Emulator port address (Spectrum Digital). */
    void         *pParent      /**< Parent router of target. */
    );

/** DeleteTargetAdapter() - Delete a TargetAdapter instance.
 *
 *  Deletes an instance of the TargetAdapter class.
 *
 * \return nothing.
 */
void
DeleteTargetAdapter(
    void *pTargetAdapter /**< Pointer to existing TargetAdapter instance. */
    );
#endif /* TA_NO_FUNCTION_DECLARATIONS */


#ifdef __cplusplus
};
#endif

#endif  /* TARGETADAPTERINTF_H */

/* End of File */
