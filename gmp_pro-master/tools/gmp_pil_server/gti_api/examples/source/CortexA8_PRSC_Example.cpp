//----------------------------------------------------------------------------
// FILENAME: CortexA8_PRSC_example.cpp
//
// Example application of using the GTI API.  This application does the basic
// initialization of a driver with sample register and memory accesses. This 
// application also demonstrates setting up the Target Adapter parent for 
// the PRSC features and connecting to a Cortex A8 target.
//
// Tested on an OMAP3530 (Beagle board) with an XDS100v2 debug probe.
// Tested on an OMAP3530 (Beagle board) with an SD XDS510USB Plus debug probe.
//
// Copyright (c) 2011-2014 Texas Instruments Incorporated, All rights reserved
//----------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <string.h>

#define BOOL BOOL
#define GTI_NO_FUNCTION_DECLARATIONS
#include "gti.h"
#define TA_NO_FUNCTION_DECLARATIONS
#include "TargetAdapterIntf.h"


// Set USE_XDS100 to TRUE  for an XDS100v2 debug probe.
// Set USE_XDS100 to FALSE for a Spectrum Digital XDS510USB Plus.
#define USE_XDS100 TRUE

#if USE_XDS100
// Values for the Texas Instruments software for XDS100v2
#define BOARD_FILE       "C:\\ccBoard2.dat"      // Path and name of board config file.
#define CORTEX_A8_DRIVER "tixds510cortexA.dvr"   // File name of the Cortex A8 driver.
#define DAP_PC_DRIVER    "tixds510dap_pc.dvr"    // File name of the DAP PC driver.
#define ICEPICK_DRIVER   "tixds510icepick_c.dvr" // File name of the ICEPick driver.
#define TARGET_ADAPTER   "TargetAdapter.dll"     // File name of the Target Adapter library.
#define PROBE_PORT       0                       // Debug probe port (unused for XDS100v2).
#else
// Values for the Spectrum Digital software for XDS510USB Plus.
#define BOARD_FILE       "C:\\ccBoard2sd.dat"    // Path and name of board config file.
#define CORTEX_A8_DRIVER "sdgocortexAusb.dvr"    // File name of the Cortex A8 driver.
#define DAP_PC_DRIVER    "sdgodap_pcusb.dvr"     // File name of the DAP PC driver.
#define ICEPICK_DRIVER   "sdgoicepickusb_c.dvr"  // File name of the ICEPick driver.
#define TARGET_ADAPTER   "TargetAdapter.dll"     // File name of the Target Adapter library.
#define PROBE_PORT       0x510                   // Debug probe port (class for XDS510USB).
#endif


// Location of emulation package and related subdirectories
#define EMUPACK_DIR    "C:\\ti\\ccsv5\\ccs_base\\"
#define DRIVERS_SUBDIR "emulation\\drivers\\"
#define USCIF_SUBDIR   "common\\uscif\\"
#define COMMON_SUBDIR  "common\\bin\\"

// Board configuration information
#define CORTEX_NAME  "Beagle_cortex_a8_0/cortex_a8_0" // Name of board and Cortex A8 to debug:
                                                      // see documentation of GTI_INIT_EX()
                                                      // for further explanation.
#define ICEPICK_NAME "Beagle_icepick_c_0/icepick_c_0" // Name of board and ICEPick 
#define DAP_NAME     "Beagle_cs_dap_pc_0/cs_dap_pc_0" // Name of board and DAP 

// Define function pointers for the Target Adapter calls used here.
CreateTargetAdapter_t *CreateTargetAdapter = 0;
DeleteTargetAdapter_t *DeleteTargetAdapter = 0;

// Register indices as found in common\targetdb\drivers\TI_reg_ids XML files
#define REG_R0_ID 512
#define REG_R1_ID 513

// Define a structure type for tracking the GTI API details
// for each different driver instance created.
typedef struct _GTI_API_t
{
    GTI_HANDLE_TYPE    hpid;

    GTI_FN_INIT_EX    *GTI_INIT_EX;
    GTI_FN_GEN        *GTI_QUIT;
    GTI_FN_CONNECT    *GTI_CONNECT;
    GTI_FN_DISCONNECT *GTI_DISCONNECT;
    GTI_FN_GETERR_EX3 *GTI_GETERRSTR_EX3;
    GTI_FN_REG        *GTI_READREG;
    GTI_FN_REG        *GTI_WRITEREG;
    GTI_FN_MEM_BLK    *GTI_READMEM_BLK;
    GTI_FN_MEM_BLK    *GTI_WRITEMEM_BLK;
} GTI_API_t;

const char *GetError(GTI_API_t &gti);

void main(void)
{
    GTI_API_t       ctx     = {0};         // Details for the Cortex A8 GTI instance
    GTI_API_t       dap     = {0};         // Details for the DAP GTI isntance
    GTI_RETURN_TYPE result  = GTI_SUCCESS; // Result from GTI API calls
    GTI_HANDLE_TYPE pIP     = 0;           // Target Adapter handle to ICEPick
    GTI_HANDLE_TYPE pDAP    = 0;           // Target Adapter handle to DAP
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

    // Load the Cortex A8 driver into memory.
    HMODULE hCTX = LoadLibrary(CORTEX_A8_DRIVER);

    // Load the DAP driver into memory.
    HMODULE hDAP = LoadLibrary(DAP_PC_DRIVER);

    // Load the Target Adapter Library into memory.
    HMODULE hTA  = LoadLibrary(TARGET_ADAPTER);

    if (0 == hCTX) {
        // The driver or a dependent library failed to load
        success = false;
        printf("Failed to load the Cortex A8 driver.\n");
    }

    if (0 == hDAP) {
        // The driver or a dependent library failed to load
        success = false;
        printf("Failed to load the DAP driver.\n");
    }

    if (0 == hTA) {
        // The Target Adapter library failed to load
        success = false;
        printf("Failed to load the Target Adapter library.\n");
    }

    if (success) {
        // Load the GTI API calls from the Cortex A8 driver library
        ctx.GTI_INIT_EX       = (GTI_FN_INIT_EX*)   GetProcAddress(hCTX, "GTI_INIT_EX");
        ctx.GTI_QUIT          = (GTI_FN_GEN*)       GetProcAddress(hCTX, "GTI_QUIT");
        ctx.GTI_CONNECT       = (GTI_FN_CONNECT*)   GetProcAddress(hCTX, "GTI_CONNECT"); 
        ctx.GTI_DISCONNECT    = (GTI_FN_DISCONNECT*)GetProcAddress(hCTX, "GTI_DISCONNECT");
        ctx.GTI_GETERRSTR_EX3 = (GTI_FN_GETERR_EX3*)GetProcAddress(hCTX, "GTI_GETERRSTR_EX3");
        ctx.GTI_READREG       = (GTI_FN_REG*)       GetProcAddress(hCTX, "GTI_READREG");
        ctx.GTI_WRITEREG      = (GTI_FN_REG*)       GetProcAddress(hCTX, "GTI_WRITEREG");
        ctx.GTI_READMEM_BLK   = (GTI_FN_MEM_BLK*)   GetProcAddress(hCTX, "GTI_READMEM_BLK");
        ctx.GTI_WRITEMEM_BLK  = (GTI_FN_MEM_BLK*)   GetProcAddress(hCTX, "GTI_WRITEMEM_BLK");

        // Check that these loads all worked
        if (0 == ctx.GTI_INIT_EX       ||
            0 == ctx.GTI_QUIT          ||
            0 == ctx.GTI_CONNECT       ||
            0 == ctx.GTI_DISCONNECT    ||
            0 == ctx.GTI_GETERRSTR_EX3 ||
            0 == ctx.GTI_READREG       ||
            0 == ctx.GTI_WRITEREG      ||
            0 == ctx.GTI_WRITEMEM_BLK  ||
            0 == ctx.GTI_READMEM_BLK) {
            // One or more of the function calls failed to load
            success = false;
            printf("Failed to load function calls from Cortex A8 driver.\n");
        }
    }

    if (success) {
        // Load the GTI API calls from the DAP driver library
        dap.GTI_INIT_EX       = (GTI_FN_INIT_EX*)   GetProcAddress(hDAP, "GTI_INIT_EX");
        dap.GTI_QUIT          = (GTI_FN_GEN*)       GetProcAddress(hDAP, "GTI_QUIT");
        dap.GTI_CONNECT       = (GTI_FN_CONNECT*)   GetProcAddress(hDAP, "GTI_CONNECT"); 
        dap.GTI_DISCONNECT    = (GTI_FN_DISCONNECT*)GetProcAddress(hDAP, "GTI_DISCONNECT");
        dap.GTI_GETERRSTR_EX3 = (GTI_FN_GETERR_EX3*)GetProcAddress(hDAP, "GTI_GETERRSTR_EX3");

        // Check that these loads all worked
        if (0 == dap.GTI_INIT_EX         ||
            0 == dap.GTI_QUIT            ||
            0 == dap.GTI_CONNECT         ||
            0 == dap.GTI_DISCONNECT      ||
            0 == dap.GTI_GETERRSTR_EX3) {
            // One or more of the function calls failed to load
            success = false;
            printf("Failed to load function calls from DAP driver.\n");
        }
    }

    if (success) {
        // Load the Target Adapter calls from the library
        CreateTargetAdapter = (CreateTargetAdapter_t*)GetProcAddress(hTA, "CreateTargetAdapter");
        DeleteTargetAdapter = (DeleteTargetAdapter_t*)GetProcAddress(hTA, "DeleteTargetAdapter");

        // Check that these loads both worked
        if (0 == CreateTargetAdapter ||
            0 == DeleteTargetAdapter) {
            // One or more of the function calls failed to load
            success = false;
            printf("Failed to load function calls from Target Adapter library.\n");
        }
    }

    // To set up the PRSC (power-reset-system control) module, the parent router
    // for each device must be specified.  For the OMAP3530, the immediate parent
    // of the Cortex A8 is the DAP router.  The parent of the DAP router is the 
    // ICEPick router. The parents are passed into the GTI_INIT_EX() call via the
    // m_ParentOfPRSC member of the GTI_INIT_INFO structure.  This member is a 
    // pointer to Target Adapter instance pointing to the parent device.

    if (success) {
        // Initialize the Target Adapter handle to ICEPick 
        pIP = CreateTargetAdapter(EMUPACK_DIR DRIVERS_SUBDIR ICEPICK_DRIVER, 
                                  ICEPICK_NAME, 
                                  BOARD_FILE,
                                  PROBE_PORT,
                                  0); // The ICEPick has no parent

        if (0 == pIP) {
            success = false;
            printf("Failed to initialize Target Adapter handle to ICEPick.\n");
        }
    }

    if (success) {
        // Initialize the Target Adapter handle to DAP 
        pDAP = CreateTargetAdapter(EMUPACK_DIR DRIVERS_SUBDIR DAP_PC_DRIVER, 
                                   DAP_NAME, 
                                   BOARD_FILE,
                                   PROBE_PORT,
                                   pIP); // Parent of the DAP is the ICEPick

        if (0 == pDAP) {
            success = false;
            printf("Failed to initialize Target Adapter handle to DAP.\n");
        }
    }

    // As a unique requirement for the Cortex A8, A9, and A15 drivers, the DAP
    // router that is the device's parent must be initialized and connected
    // before connecting to the Cortex.

    if (success) {
        // Initialize the DAP driver. 
        GTI_INIT_INFO initInfo; // Initialization parameters structure

        memset(&initInfo, 0, sizeof(initInfo));

        initInfo.m_structRevision        = GTI_INIT_INFO_REV; // Structure revision
        initInfo.m_structLength          = sizeof(initInfo);  // Size of structure
        initInfo.m_sProcDataFileLocation = BOARD_FILE;        // Board config file
        initInfo.m_ParentOfPRSC          = pIP;               // Handle to parent

        result = dap.GTI_INIT_EX(0,             // unused
                                 DAP_NAME,      // Name of board, ends with slash and name of device to debug
                                 PROBE_PORT,    // Debug probe port address
                                 BOARD_FILE,    // Board config file
                                 0,             // unused
                                 0,             // unused
                                 0,             // unused
                                 &initInfo,     // Initialization parameters structure
                                 &(dap.hpid));  // Pointer to return instance handle

        if (GTI_SUCCESS != result) {
            // Init call failed
            success = false;
            printf("Failed to initialize DAP driver.\n");
        }
    }

    if (success) {
        // Initialize the Cortex A8 driver. 
        GTI_INIT_INFO initInfo; // Initialization parameters structure

        memset(&initInfo, 0, sizeof(initInfo));

        initInfo.m_structRevision        = GTI_INIT_INFO_REV; // Structure revision
        initInfo.m_structLength          = sizeof(initInfo);  // Size of structure
        initInfo.m_sProcDataFileLocation = BOARD_FILE;        // Board config file
        initInfo.m_ParentOfPRSC          = pDAP;              // Handle to parent

        result = ctx.GTI_INIT_EX(0,             // unused
                                 CORTEX_NAME,   // Name of board, ends with slash and name of device to debug
                                 PROBE_PORT,    // Debug probe port address
                                 BOARD_FILE,    // Board config file
                                 0,             // unused
                                 0,             // unused
                                 0,             // unused
                                 &initInfo,     // Initialization parameters structure
                                 &(ctx.hpid));  // Pointer to return instance handle

        if (GTI_SUCCESS != result) {
            // Init call failed
            success = false;
            printf("Failed to initialize Cortex A8 driver.\n");
        }
    }

    if (success) {
        // Connect to the DAP
        result = dap.GTI_CONNECT(dap.hpid);

        if (GTI_SUCCESS != result) {
            // Connect call failed
            success = false;
            printf("Failed to connect debug probe to DAP.\n%s\n", GetError(dap));
        }
        else {
            printf("Connected to DAP.\n");
        }
    }

    if (success) {
        // Connect to the Cortex A8
        result = ctx.GTI_CONNECT(ctx.hpid);

        if (GTI_SUCCESS != result) {
            // Connect call failed
            success = false;
            printf("Failed to connect debug probe to Cortex A8.\n%s\n", GetError(ctx));
        }
        else {
            printf("Connected to Cortex A8.\n");
        }
    }

    {
        // Try out the register calls by reading and writing register R0.
        GTI_REGID_TYPE    regID     = REG_R0_ID; // Register index
        GTI_REGISTER_TYPE regValue  = 0;         // Value  read from register
        GTI_REGISTER_TYPE regExpect = 0;         // Value written to register

        if (success) {
            // Read a value from register R0
            result = ctx.GTI_READREG(ctx.hpid, regID, &regValue);

            if (GTI_SUCCESS != result) {
                // Read register call failed
                success = false;
                printf("Failed to read register.\n%s\n", GetError(ctx));
            }
            else {
                printf("Read  0x%08x from register.\n", regValue);
            }             
       }

        if (success) {
            // Write a value to register R0
            regExpect = ~regValue;
            result    = ctx.GTI_WRITEREG(ctx.hpid, regID, &regExpect);

            if (GTI_SUCCESS != result) {
                // Write register call failed
                success = false;
                printf("Failed to write register.\n%s\n", GetError(ctx));
            }
        }

        if (success) {
            // Read the value back from register R0
            result = ctx.GTI_READREG(ctx.hpid, regID, &regValue);

            if (GTI_SUCCESS != result) {
                // Read register call failed
                success = false;
                printf("Failed to read register.\n%s\n", GetError(ctx));
            }
            else {
                printf("Wrote 0x%08x to register\nRead  0x%08x from register.\n", regExpect, regValue);
            }             
        }
    }

    {
        GTI_ADDRS_TYPE  address = 0x80000000; // Memory address to access
        GTI_LEN_TYPE    length  = 0x100;      // Number of memory values to read or write
        GTI_DATA_TYPE   buffer[0x100];        // Buffer to hold memory data

        if (success) {
            // Write a block of memory
            memset(buffer, 0xa5, sizeof(buffer));
    
            result = ctx.GTI_WRITEMEM_BLK(ctx.hpid, address, 0, length, 0, 0, 0, 0, buffer);

            if (GTI_SUCCESS != result) {
                // Write memory call failed
                success = false;
                printf("Failed to write memory.\n%s\n", GetError(ctx));
            }
            else {
                printf("Wrote 0x%x values to address   0x%08x\n", length, address);
            }             
        }

        if (success) {
            // Write a block of memory
            memset(buffer, 0x00, sizeof(buffer));
    
            result = ctx.GTI_READMEM_BLK(ctx.hpid, address, 0, length, 0, 0, 0, 0, buffer);

            if (GTI_SUCCESS != result) {
                // Read memory call failed
                success = false;
                printf("Failed to read memory.\n%s\n", GetError(ctx));
            }
            else {
                printf("Read  0x%x values from address 0x%08x\n", length, address);
            }             
        }
    }

    if (success) {
        // Terminate the session with the Cortex A8 driver
        result = ctx.GTI_DISCONNECT(ctx.hpid);

        if (GTI_SUCCESS != result) {
            // Disconnect call failed
            success = false;
            printf("Failed to disconnect from Cortex A8.\n%s\n", GetError(ctx));
        }
        else {
            printf("Disconnected from Cortex A8.\n");
        }
    }

    if (success) {
        // Terminate the session with the DAP driver
        result = dap.GTI_DISCONNECT(dap.hpid);

        if (GTI_SUCCESS != result) {
            // Disconnect call failed
            success = false;
            printf("Failed to disconnect from DAP.\n%s\n", GetError(dap));
        }
        else {
            printf("Disconnected from DAP.\n");
        }
    }

    if (0 != ctx.hpid) {
        // Terminate the session with the Cortex A8 driver
        result = ctx.GTI_QUIT(ctx.hpid);

        if (GTI_SUCCESS != result) {
            // Quit call failed
            success = false;
            printf("Failed to terminate Cortex A8 driver.\n");
        }
    }

    if (0 != dap.hpid) {
        // Terminate the session with the DAP driver
        result = dap.GTI_QUIT(dap.hpid);

        if (GTI_SUCCESS != result) {
            // Quit call failed
            success = false;
            printf("Failed to terminate DAP driver.\n");
        }
    }

    // Clean up Target Adapter instances
    if (0 != pDAP) DeleteTargetAdapter(pDAP);
    if (0 != pIP)  DeleteTargetAdapter(pIP);

    // Clean up libraries
    if (0 != hTA)  FreeLibrary(hTA);
    if (0 != hCTX) FreeLibrary(hCTX);
    if (0 != hDAP) FreeLibrary(hDAP);

    if (success) {
        printf("\nDone! Completed with no emulation errors.\n");
    }

    return;
}

const char *GetError(GTI_API_t &gti)
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

    result = gti.GTI_GETERRSTR_EX3(gti.hpid, &sequenceId, &errorCode, &errorClass, &severity,
                                   &action, &buttons, &icon, pszCustomButtons, customButtonsLength,
                                   pszErrorMessage, errorMessageLength);

    return errorMessage;
}

// End of File
