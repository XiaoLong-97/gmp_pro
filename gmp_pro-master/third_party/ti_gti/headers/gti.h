/** \file gti.h
 * 
 *  This header coordinates including the various header files of the GTI
 *  API. Clients of the API only need to include "gti.h" to use the API.
 * 
 *  Copyright (c) 1998-2017, Texas Instruments Inc., All rights reserved.
 */

/** \mainpage
 *
 *  This documentation describes the specification for the Generic Target 
 *  Interface (GTI) API used to access the Texas Instruments emulation
 *  device drivers. This documentation covers the basic and optional 
 *  capabilities of the device drivers as a set of detailed descriptions 
 *  of each API function.
 *  
 *  For information on how to get started using the API, see the \ref started 
 *  page.
 *  
 *  For basic demonstrations of client code using the GTI API, see the 
 *  examples: GTI_API_Example.cpp and TargetAdapter_Example.cpp. 
 *  
 *  Copyright (c) 2011, Texas Instruments Inc., All rights reserved. <br>
 */

/** \page started Getting Started
 *
 *  To create a GTI client, the following steps must be performed by the 
 *  client application:
 *
 *  1) Include the gti.h header file.  This file serves as the top level 
 *  header that includes all other header in the GTI API.
 *
 *  2) Create a board config file.  The JTAG scan manager uses the board
 *  config file to determine what debug probe to use, how it is set up, and
 *  how to direct scans to the target you wish to debug. Code Composer Studio
 *  (CCS) is needed to create the board configuration file. To do this, open
 *  CCS, go to File -> New -> Target Configuration File. Set the "Connection"
 *  to the debug probe and set the approperiate target in the "Board or Device"
 *  field. Make any necessary configuration changes by clicking on the
 *  "Advanced" tab. Click on "Save". Now click on "Test Connection" button. The
 *  output window indicates the location of the testBoard.dat board config
 *  file. Example output:
 *  \verbatim
      [Start: Texas Instruments XDS110 USB Debug Probe_0]

      Execute the command:

      %ccs_base%/common/uscif/dbgjtag -f %boarddatafile% -rv -o -S integrity
      [Result]

      -----[Print the board config pathname(s)]------------------------------------

      C:\Users\a0270958\AppData\Local\TEXASI~1\
              CCS\CCS611~2.000\0\0\BrdDat\testBoard.dat
      .
      .
      .
      [End: Texas Instruments XDS110 USB Debug Probe_0]
    \endverbatim
 *  You can rename and move this file to use it in your GTI code. Note:
 *  every time the "Test Connection" button is clicked, the testBoard.dat is
 *  recreated by CCS.
 *
 *  3) Set your system PATH to include the primary binary directories of 
 *  the emulation package: common/uscif, common/bin, and emulation/drivers.
 *  If you don't set PATH, you can change the current directory and 
 *  pre-load dependent libraries instead. See the GTI_API_Example.cpp 
 *  example to see how this can be done.
 *
 *  4) Load the appropriate driver file.  Driver files are dynamic libraries
 *  that contain the GTI calls specific to a given device or family of
 *  devices.  On Windows, these are named like, for example, tixds510cortexR.dvr.
 *  On Linux the same driver would be named libtixds510cortexR.so.
 *  The name will indicate the class of debug probe and the device family the 
 *  driver file is used with. 
 * 
 *  Note that the 560 class drivers are used with debug probes where a portion
 *  of the driver code executes inside of the debug probe. This includes all 
 *  versions of 560 debug probes and XDS2xx debug probes. 

 *  510 class drivers are used with debug probes where all of the driver executes 
 *  on the PC host.  This includes the legacy TI XDS510 debug probe and all 
 *  versions of the XDS100 debug probes.
 *
 *  Also note that some third party debug probes use their own emulation software 
 *  stack and their own drivers. Please contact the debug probe's manufacturer
 *  for details of how to use their software stack. Examples for the Spectrum
 *  Digital XDS510USB are provided in this documentation package.
 *
 *  5) Load the GTI API functions you intend to use. Note that many of the 
 *  APIs are optional, and if an API is missing from the driver it simply
 *  means that the driver doesn't support that feature.  Also note that 
 *  there may be different levels of some APIs (particular the memory
 *  calls) where newer versions have added capability.  You should, in
 *  general, try to use the most advanced version the driver exposes.
 *  The documentation indicates which API extends the capability of a
 *  previous API to determine which is the most advanced one.
 * 
 *  6) Use GTI_GET_EXT_CAPABILITIES() to determine what general and
 *  emulation features the driver supports, especially important if your
 *  client is written to be generic and not know in advance anything
 *  about the driver or device.
 *
 *  7) Initialize any \ref TargetAdapter handles your device may need. If the
 *  device is on an ICEPick TAP, then you will need a handle to the ICEPick
 *  for the m_ParentOfPRSC member of the init structure.  Or if your device
 *  is accessed through a host, such as the CLA in Piccolo devices, then
 *  you will need a handle to the host for the m_pMemoryProxy member.
 *
 *  8) To start up the debug session, call these APIs in this order:
 *  - GTI_GET_EXT_CAPABILITIES() (optional)
 *  - Initialize TargetAdapter handles (if needed)
 *  - GTI_CONFIG() or GTI_SETUP_PROPERTIES() (to pass optional parameters to driver)
 *  - GTI_INIT_EX() (does software initialization of driver)
 *  - GTI_CONNECT() (connects debug probe to target device)
 *  - GTI_GET_EXT_CAPABILITIES() (may change to better match connected device)
 *  - Ready now to use any other debug APIs.
 *
 *  9) To close down the debug session, call these APIs in this order:
 *  - GTI_DISCONNECT()
 *  - GTI_QUIT()
 */

/** \example GTI_API_Example.cpp
 *  
 *  Example client code showing how to use the GTI API to connect to a target
 *  Cortex R4 device, access registers, and access memory. This example can
 *  be configured for either XDS100v2 or SD XDS510USB Plus debug probes.
 */

/** \example TargetAdapter_Example.cpp
 *  
 *  Example client code showing how to use the GTI API and Target Adapter to
 *  connect to the PRU, access registers, and access memory. This example can
 *  be configured for either XDS560v2 LAN or SD XDS510USB Plus debug probes.
 */

/** \example CortexA8_PRSC_Example.cpp
 *  
 *  Example client code showing how to use the GTI API and Target Adapter to
 *  initialize the PRSC module, connect to a Cortex A8, access registers, and 
 *  access memory. This example can be configured for either XDS100v2 or 
 *  SD XDS510USB Plus debug probes.
 */

/** \example CortexA8_Linux_Example.cpp
 *  
 *  Example client code showing how to use the GTI API and Target Adapter to
 *  run on a Linux host. This is the CortexA8_PRSC_Example.cpp code modified to
 *  run under Linux.  Use the CortexA8_Linux_Example.mak makefile in the build 
 *  directory to build this example.
 */

/** \example ccBoard0.dat
 * 
 *  Example of a board config file for XDS100v2 debug probe for connecting to the
 *  Cortex R4 of a TMS570PSF762 (Aries) board.
 */

/** \example ccBoard0sd.dat
 * 
 *  Example of a board config file for Spectrum Digital XDS510USB Plus debug probe 
 *  for connecting to the Cortex R4 of a TMS570PSF762 (Aries) board.
 */

/** \example ccBoard1.dat
 *
 * Example of a board config file for Blackhawk XDS560v2 LAN debug probe for  
 * connecting to an OMAPL138 EVM board.
 */

/** \example ccBoard1sd.dat
 *
 * Example of a board config file for Spectrum Digital XDS510USB Plus debug probe 
 * for connecting to an OMAPL138 EVM board.
 */

/** \example ccBoard2.dat
 *
 * Example of a board config file for XDS100v2 debug probe for connecting to an
 * OMAP3530 Beagle board.
 */

/** \example ccBoard2sd.dat
 *
 * Example of a board config file for Spectrum Digital XDS510USB Plus debug probe 
 * for connecting to an OMAP3530 Beagle board.
 */

/** \example ccBoard2linux.dat
 *
 * Example of a board config file for XDS100v2 debug probe for connecting to an
 * OMAP3530 Beagle board for a Linux host.
 */

#ifndef GTI_H
#define GTI_H


#define GTI_REV 0x3200 

#define GTI_EXPORT
#ifndef GTI_NO_FUNCTION_DECLARATIONS
#if defined(_WIN32)
#undef  GTI_EXPORT
#define GTI_EXPORT __declspec(dllexport)
#endif /* _WIN32 */
#endif /* GTI_NO_FUNCTION_DECLARATIONS */

#define GTI_FAR
#define GTI_PRIVATE static

#include "gti_types.h"
#include "gti_main.h"
#include "gti_config.h"
#include "gti_error.h"
#include "gti_status.h"
#include "gti_memory.h"
#include "gti_register.h"
#include "gti_execution.h"
#include "gti_reset.h"
#include "gti_breakpoint.h"
#include "gti_misc.h"
#include "gti_private.h"
#include "gti_deprecated.h"
#include "gti_step_past_bp_events.h"

#endif /* GTI_H */

/* End of File */
