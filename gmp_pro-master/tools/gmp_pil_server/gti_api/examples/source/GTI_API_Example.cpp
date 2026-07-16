//----------------------------------------------------------------------------
// FILENAME: GTI_API_example.cpp
//
// Example application of using the GTI API.  This application does the basic
// initialization of a driver with sample register and memory accesses.
//
// Tested on a TMS570PSF762 (Aries) with an XDS100v2 debug probe.
// Tested on a TMS570PSF762 (Aries) with an SD XDS510USB Plus debug probe.
//
// Copyright (c) 2011-2014 Texas Instruments Incorporated, All rights reserved
//----------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <string.h>

#define BOOL BOOL
#define GTI_NO_FUNCTION_DECLARATIONS
#include "gti.h"


// Set USE_XDS100 to TRUE  for an XDS100v2 debug probe.
// Set USE_XDS100 to FALSE for a Spectrum Digital XDS510USB Plus.
#define USE_XDS100 TRUE

#if USE_XDS100
// Values for the Texas Instruments software for XDS100v2
#define BOARD_FILE       "C:\\ccBoard0.dat"      // Path and name of board config file.
#define CORTEX_R4_DRIVER "tixds510cortexR.dvr"   // File name of the Cortex R4 driver.
#define PROBE_PORT       0                       // Debug probe port (unused for XDS100v2).
#else
// Values for the Spectrum Digital software for XDS510USB Plus.
#define BOARD_FILE       "C:\\ccBoard0sd.dat"    // Path and name of board config file.
#define CORTEX_R4_DRIVER "sdgocortexRusb.dvr"    // File name of the Cortex R4 driver.
#define PROBE_PORT       0x510                   // Debug probe port (class for XDS510USB).
#endif


// Location of emulation package and related subdirectories
#define EMUPACK_DIR    "C:\\ti\\ccsv5\\ccs_base\\"
#define DRIVERS_SUBDIR "emulation\\drivers\\"
#define USCIF_SUBDIR   "common\\uscif\\"
#define COMMON_SUBDIR  "common\\bin\\"

// Board configuration information
#define BOARD_NAME  "Aries_CortexR4/CortexR4" // Name of board and device to debug:
                                              // see documentation of GTI_INIT_EX()
                                              // for further explanation.

// Register indices as found in common\targetdb\drivers\TI_reg_ids XML files
#define REG_R0_ID 512
#define REG_R1_ID 513

// Define function pointers for the GTI API calls used here.
GTI_FN_INIT_EX    *GTI_INIT_EX       = 0;
GTI_FN_GEN        *GTI_QUIT          = 0;
GTI_FN_CONNECT    *GTI_CONNECT       = 0;
GTI_FN_DISCONNECT *GTI_DISCONNECT    = 0;
GTI_FN_GETERR_EX3 *GTI_GETERRSTR_EX3 = 0;
GTI_FN_REG        *GTI_READREG       = 0;
GTI_FN_REG        *GTI_WRITEREG      = 0;
GTI_FN_MEM_BLK    *GTI_READMEM_BLK   = 0;
GTI_FN_MEM_BLK    *GTI_WRITEMEM_BLK  = 0;

const char *GetError(GTI_HANDLE_TYPE hpid);

void main(void)
{
    GTI_RETURN_TYPE result  = GTI_SUCCESS; // Result from GTI API calls
    GTI_HANDLE_TYPE hpid    = 0;           // Handle to GTI API interface
    bool            success = true;        // Track that everything is working

    // Set up PATH environment variable to locate the GTI API libraries
    const int MAX_ENV_VAR = 8191;   // Max length for command line parameters
    char *oldPath = getenv("PATH"); // Retrieve the current PATH environment variable
    char  newPath[MAX_ENV_VAR + 1]; // Allocate space for the updated PATH

    // Begin the set PATH with the USCIF, common, and drivers paths.
    strncpy(newPath, 
            "PATH="
            EMUPACK_DIR USCIF_SUBDIR ";"
            EMUPACK_DIR COMMON_SUBDIR ";"
            EMUPACK_DIR DRIVERS_SUBDIR ";",
            MAX_ENV_VAR);

    // Append the old PATH environment variable.
    strncat(newPath, oldPath, MAX_ENV_VAR);
    newPath[MAX_ENV_VAR] = 0;

    // Apply the change (affects only this process).
    putenv(newPath);

    // Load the emulation driver into memory.
    HMODULE hDVR = LoadLibrary(CORTEX_R4_DRIVER);

    if (0 == hDVR) {
        // The driver or a dependent library failed to load
        success = false;
        printf("Failed to load the emulation driver.\n");
    }

    if (success) {
        // Load the GTI API calls from the driver library
        GTI_INIT_EX       = (GTI_FN_INIT_EX*)   GetProcAddress(hDVR, "GTI_INIT_EX");
        GTI_QUIT          = (GTI_FN_GEN*)       GetProcAddress(hDVR, "GTI_QUIT");
        GTI_CONNECT       = (GTI_FN_CONNECT*)   GetProcAddress(hDVR, "GTI_CONNECT"); 
        GTI_DISCONNECT    = (GTI_FN_DISCONNECT*)GetProcAddress(hDVR, "GTI_DISCONNECT");
        GTI_GETERRSTR_EX3 = (GTI_FN_GETERR_EX3*)GetProcAddress(hDVR, "GTI_GETERRSTR_EX3");
        GTI_READREG       = (GTI_FN_REG*)       GetProcAddress(hDVR, "GTI_READREG");
        GTI_WRITEREG      = (GTI_FN_REG*)       GetProcAddress(hDVR, "GTI_WRITEREG");
        GTI_READMEM_BLK   = (GTI_FN_MEM_BLK*)   GetProcAddress(hDVR, "GTI_READMEM_BLK");
        GTI_WRITEMEM_BLK  = (GTI_FN_MEM_BLK*)   GetProcAddress(hDVR, "GTI_WRITEMEM_BLK");

        // Check that these loads all worked
        if (0 == GTI_INIT_EX       ||
            0 == GTI_QUIT          ||
            0 == GTI_CONNECT       ||
            0 == GTI_DISCONNECT    ||
            0 == GTI_GETERRSTR_EX3 ||
            0 == GTI_READREG       ||
            0 == GTI_WRITEREG      ||
            0 == GTI_WRITEMEM_BLK  ||
            0 == GTI_READMEM_BLK) {
            // One or more of the function calls failed to load
            success = false;
            printf("Failed to load function calls from emulation driver.\n");
        }
    }

    if (success) {
        // Initialize the emulation driver. 
        GTI_INIT_INFO initInfo; // Initialization parameters structure

        memset(&initInfo, 0, sizeof(initInfo));

        initInfo.m_structRevision        = GTI_INIT_INFO_REV; // Structure revision
        initInfo.m_structLength          = sizeof(initInfo);  // Size of structure
        initInfo.m_sProcDataFileLocation = BOARD_FILE;        // Board config file

        result = GTI_INIT_EX(0,             // unused
                             BOARD_NAME,    // Name of board, ends with slash and name of device to debug
                             PROBE_PORT,    // Debug probe port address (Spectrum Digital)
                             BOARD_FILE,    // Board config file
                             0,             // unused
                             0,             // unused
                             0,             // unused
                             &initInfo,     // Initialization parameters structure
                             &hpid);        // Pointer to return instance handle

        if (GTI_SUCCESS != result) {
            // Init call failed
            success = false;
            printf("Failed to initialize emulation driver.\n");
        }
    }

    if (success) {
        // Connect to the device being debugged
        result = GTI_CONNECT(hpid);

        if (GTI_SUCCESS != result) {
            // Connect call failed
            success = false;
            printf("Failed to connect debug probe to device.\n%s\n", GetError(hpid));
        }
        else {
            printf("Connected to device.\n");
        }
    }

    {
        // Try out the register calls by reading and writing register R0.
        GTI_REGID_TYPE    regID     = REG_R0_ID; // Register index
        GTI_REGISTER_TYPE regValue  = 0;         // Value  read from register
        GTI_REGISTER_TYPE regExpect = 0;         // Value written to register

        if (success) {
            // Read a value from register R0
            result = GTI_READREG(hpid, regID, &regValue);

            if (GTI_SUCCESS != result) {
                // Read register call failed
                success = false;
                printf("Failed to read register.\n%s\n", GetError(hpid));
            }
            else {
                printf("Read  0x%08x from register.\n", regValue);
            }             
       }

        if (success) {
            // Write a value to register R0
            regExpect = ~regValue;
            result    = GTI_WRITEREG(hpid, regID, &regExpect);

            if (GTI_SUCCESS != result) {
                // Write register call failed
                success = false;
                printf("Failed to write register.\n%s\n", GetError(hpid));
            }
        }

        if (success) {
            // Read the value back from register R0
            result = GTI_READREG(hpid, regID, &regValue);

            if (GTI_SUCCESS != result) {
                // Read register call failed
                success = false;
                printf("Failed to read register.\n%s\n", GetError(hpid));
            }
            else {
                printf("Wrote 0x%08x to register\nRead  0x%08x from register.\n", regExpect, regValue);
            }             
        }
    }

    {
        GTI_ADDRS_TYPE  address = 0x8000000; // Memory address to access
        GTI_LEN_TYPE    length  = 0x100;     // Number of memory values to read or write
        GTI_DATA_TYPE   buffer[0x100];       // Buffer to hold memory data

        if (success) {
            // Write a block of memory
            memset(buffer, 0xa5, sizeof(buffer));
    
            result = GTI_WRITEMEM_BLK(hpid, address, 0, length, 0, 0, 0, 0, buffer);

            if (GTI_SUCCESS != result) {
                // Write memory call failed
                success = false;
                printf("Failed to write memory.\n%s\n", GetError(hpid));
            }
            else {
                printf("Wrote 0x%x values to address   0x%08x\n", length, address);
            }             
        }

        if (success) {
            // Write a block of memory
            memset(buffer, 0x00, sizeof(buffer));
    
            result = GTI_READMEM_BLK(hpid, address, 0, length, 0, 0, 0, 0, buffer);

            if (GTI_SUCCESS != result) {
                // Read memory call failed
                success = false;
                printf("Failed to read memory.\n%s\n", GetError(hpid));
            }
            else {
                printf("Read  0x%x values from address 0x%08x\n", length, address);
            }             
        }
    }

    if (success) {
        // Terminate the session with the emulation driver
        result = GTI_DISCONNECT(hpid);

        if (GTI_SUCCESS != result) {
            // Disconnect call failed
            success = false;
            printf("Failed to disconnect from device.\n%s\n", GetError(hpid));
        }
        else {
            printf("Disconnected from device.\n");
        }
    }

    if (0 != hpid) {
        // Terminate the session with the emulation driver
        result = GTI_QUIT(hpid);

        if (GTI_SUCCESS != result) {
            // Quit call failed
            success = false;
            printf("Failed to terminate emulation driver.\n");
        }
    }

    // Clean up libraries
    if (0 != hDVR)   FreeLibrary(hDVR);

    if (success) {
        printf("\nDone! Completed with no emulation errors.\n");
    }

    return;
}

const char *GetError(GTI_HANDLE_TYPE hpid)
{
    GTI_INT_TYPE    result;
    GTI_INT_TYPE    sequenceId;
    GTI_INT_TYPE    errorCode;
    GTI_UINT32_TYPE errorClass;
    GTI_UINT32_TYPE severity;
    GTI_UINT32_TYPE action;
    GTI_UINT32_TYPE buttons;
    GTI_UINT32_TYPE icon;
    char            customButtons[64 + 1];
    GTI_STRING_TYPE pszCustomButtons = customButtons;
    GTI_UINT32_TYPE customButtonsLength = 64;
    static char     errorMessage[1024 + 1];
    GTI_STRING_TYPE pszErrorMessage = errorMessage;
    GTI_UINT32_TYPE errorMessageLength = 1024;

    // Only errorMessage is used here. The other fields are used by CCS to 
    // determine how the error should be treated (such as severity) and what 
    // buttons are put onto the error dialog pop-up.

    result = GTI_GETERRSTR_EX3(hpid, &sequenceId, &errorCode, &errorClass, &severity,
                               &action, &buttons, &icon, pszCustomButtons, customButtonsLength,
                               pszErrorMessage, errorMessageLength);

    return errorMessage;
}

// End of File
