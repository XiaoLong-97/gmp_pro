//----------------------------------------------------------------------------
// FILENAME: TargetAdapter_example.cpp
//
// Example application of using the GTI API and Target Adapter.  This 
// application does the basic initialization of a driver with sample register 
// and memory accesses.
//
// Tested on a LOGIC OMAPL138 EVM with an XDS560v2 debug probe.
// Tested on a LOGIC OMAPL138 EVM with an SD XDS510USB Plus debug probe.
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


// Set USE_XDS560 to TRUE  for an XDS560v2 debug probe.
// Set USE_XDS560 to FALSE for a Spectrum Digital XDS510USB Plus.
#define USE_XDS560 TRUE

#if USE_XDS560
// Values for the Texas Instruments software for XDS560v2
#define BOARD_FILE       "C:\\ccBoard1.dat"      // Path and name of board config file.
#define C64XPLUS_DRIVER  "tixds560c64x_plus.dvr" // File name of the C64x+ (GEM) driver.
#define PRU_DRIVER       "tixds510pru.dvr"       // File name of the PRU driver.
#define TARGET_ADAPTER   "TargetAdapter.dll"     // File name of the Target Adapter library.
#define PROBE_PORT       0                       // Debug probe port (unused for XDS560v2).
#else
// Values for the Spectrum Digital software for XDS510USB Plus.
#define BOARD_FILE       "C:\\ccBoard1sd.dat"    // Path and name of board config file.
#define C64XPLUS_DRIVER  "sdgo6400usb_plus.dvr"  // File name of the C64x+ (GEM) driver.
#define PRU_DRIVER       "tixds510pru.dvr"       // File name of the PRU driver.
#define TARGET_ADAPTER   "TargetAdapter.dll"     // File name of the Target Adapter library.
#define PROBE_PORT       0x510                   // Debug probe port (class for XDS510USB).
#endif


// Location of emulation package and related subdirectories
#define EMUPACK_DIR    "C:\\ti\\ccsv5\\ccs_base\\"
#define DRIVERS_SUBDIR "emulation\\drivers\\"
#define USCIF_SUBDIR   "common\\uscif\\"
#define COMMON_SUBDIR  "common\\bin\\"

// Board configuration information
#define PROC_BOARD_NAME "OMAPL138_PRU_0"   // Name of board and device to debug (defined by caller)
#define PROC_NAME       "PRU_0"            // Name only of device to debug (as in board config)
#define HOST_BOARD_NAME "OMAPL138_C674X_0" // Name of board and host device (defined by caller)
#define HOST_NAME       "C674X_0"          // Name only of host device (as in board config)

// Register indices as found in common\targetdb\drivers\TI_reg_ids XML files
#define REG_R0_ID 0x40000000
#define REG_R1_ID 0x40000001

// Define function pointers for the GTI API calls used here.
// (Note separate pointers are created for the two different drivers used.)
GTI_FN_INIT_EX          *gem_GTI_INIT_EX               = 0;
GTI_FN_GEN              *gem_GTI_QUIT                  = 0;
GTI_FN_CONNECT          *gem_GTI_CONNECT               = 0;
GTI_FN_DISCONNECT       *gem_GTI_DISCONNECT            = 0;
GTI_FN_GETERR_EX3       *gem_GTI_GETERRSTR_EX3         = 0;
GTI_FN_MEM_WITH_STAT_64 *gem_GTI_READMEM_WITH_STAT_64  = 0;
GTI_FN_MEM_WITH_STAT_64 *gem_GTI_WRITEMEM_WITH_STAT_64 = 0;
GTI_FN_SETUP_PROPERTIES *pru_GTI_SETUP_PROPERTIES      = 0;
GTI_FN_INIT_EX          *pru_GTI_INIT_EX               = 0;
GTI_FN_GEN              *pru_GTI_QUIT                  = 0;
GTI_FN_CONNECT          *pru_GTI_CONNECT               = 0;
GTI_FN_DISCONNECT       *pru_GTI_DISCONNECT            = 0;
GTI_FN_GETERR_EX3       *pru_GTI_GETERRSTR_EX3         = 0;
GTI_FN_REG              *pru_GTI_READREG               = 0;
GTI_FN_REG              *pru_GTI_WRITEREG              = 0;
GTI_FN_MEM_BLK          *pru_GTI_READMEM_BLK           = 0;
GTI_FN_MEM_BLK          *pru_GTI_WRITEMEM_BLK          = 0;

// Define function pointers for the Target Adapter calls used here.
CreateTargetAdapter_t *CreateTargetAdapter = 0;
DeleteTargetAdapter_t *DeleteTargetAdapter = 0;

const char *GetError(GTI_FN_GETERR_EX3 *fnGTI_GETERR_EX3, GTI_HANDLE_TYPE hpid);

void main(void)
{
    GTI_RETURN_TYPE result  = GTI_SUCCESS; // Result from GTI API calls
    GTI_HANDLE_TYPE hpid    = 0;           // Handle to GTI API interface
    GTI_HANDLE_TYPE hTA     = 0;           // Pointer to Target Adapter instance
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

    // Load the C674x (GEM) emulation driver into memory.
    HMODULE hGEM = LoadLibrary(C64XPLUS_DRIVER);

    // Load the PRU emulation driver into memory.
    // Note that the PRU always uses the 510 driver, there is no 560 PRU driver.
    HMODULE hPRU = LoadLibrary(PRU_DRIVER);

    // Load the Target Adapter Library into memory.
    HMODULE hTALib = LoadLibrary(TARGET_ADAPTER);

    if (0 == hGEM) {
        // The driver or a dependent library failed to load
        success = false;
        printf("Failed to load the GEM emulation driver.\n");
    }

    if (0 == hPRU) {
        // The driver or a dependent library failed to load
        success = false;
        printf("Failed to load the PRU emulation driver.\n");
    }

    if (0 == hTALib) {
        // The Target Adapter library failed to load
        success = false;
        printf("Failed to load the Target Adapter library.\n");
    }

    if (success) {
        // Load the GTI API calls from the GEM driver library
        gem_GTI_INIT_EX               = (GTI_FN_INIT_EX*)         GetProcAddress(hGEM, "GTI_INIT_EX");
        gem_GTI_QUIT                  = (GTI_FN_GEN*)             GetProcAddress(hGEM, "GTI_QUIT");
        gem_GTI_CONNECT               = (GTI_FN_CONNECT*)         GetProcAddress(hGEM, "GTI_CONNECT"); 
        gem_GTI_DISCONNECT            = (GTI_FN_DISCONNECT*)      GetProcAddress(hGEM, "GTI_DISCONNECT");
        gem_GTI_GETERRSTR_EX3         = (GTI_FN_GETERR_EX3*)      GetProcAddress(hGEM, "GTI_GETERRSTR_EX3");
        gem_GTI_READMEM_WITH_STAT_64  = (GTI_FN_MEM_WITH_STAT_64*)GetProcAddress(hGEM, "GTI_READMEM_WITH_STAT_64");
        gem_GTI_WRITEMEM_WITH_STAT_64 = (GTI_FN_MEM_WITH_STAT_64*)GetProcAddress(hGEM, "GTI_WRITEMEM_WITH_STAT_64");

        // Check that these loads all worked
        if (0 == gem_GTI_INIT_EX                ||
            0 == gem_GTI_QUIT                   ||
            0 == gem_GTI_CONNECT                ||
            0 == gem_GTI_DISCONNECT             ||
            0 == gem_GTI_GETERRSTR_EX3          ||
            0 == gem_GTI_READMEM_WITH_STAT_64   ||
            0 == gem_GTI_WRITEMEM_WITH_STAT_64) {
            // One or more of the function calls failed to load
            success = false;
            printf("Failed to load function calls from GEM emulation driver.\n");
        }
    }

    if (success) {
        // Load the GTI API calls from the PRU driver library
        pru_GTI_SETUP_PROPERTIES = (GTI_FN_SETUP_PROPERTIES*)GetProcAddress(hPRU, "GTI_SETUP_PROPERTIES");
        pru_GTI_INIT_EX          = (GTI_FN_INIT_EX*)         GetProcAddress(hPRU, "GTI_INIT_EX");
        pru_GTI_QUIT             = (GTI_FN_GEN*)             GetProcAddress(hPRU, "GTI_QUIT");
        pru_GTI_CONNECT          = (GTI_FN_CONNECT*)         GetProcAddress(hPRU, "GTI_CONNECT"); 
        pru_GTI_DISCONNECT       = (GTI_FN_DISCONNECT*)      GetProcAddress(hPRU, "GTI_DISCONNECT");
        pru_GTI_GETERRSTR_EX3    = (GTI_FN_GETERR_EX3*)      GetProcAddress(hPRU, "GTI_GETERRSTR_EX3");
        pru_GTI_READREG          = (GTI_FN_REG*)             GetProcAddress(hPRU, "GTI_READREG");
        pru_GTI_WRITEREG         = (GTI_FN_REG*)             GetProcAddress(hPRU, "GTI_WRITEREG");
        pru_GTI_READMEM_BLK      = (GTI_FN_MEM_BLK*)         GetProcAddress(hPRU, "GTI_READMEM_BLK");
        pru_GTI_WRITEMEM_BLK     = (GTI_FN_MEM_BLK*)         GetProcAddress(hPRU, "GTI_WRITEMEM_BLK");

        // Check that these loads all worked
        if (0 == pru_GTI_SETUP_PROPERTIES ||
            0 == pru_GTI_INIT_EX          ||
            0 == pru_GTI_QUIT             ||
            0 == pru_GTI_CONNECT          ||
            0 == pru_GTI_DISCONNECT       ||
            0 == pru_GTI_GETERRSTR_EX3    ||
            0 == pru_GTI_READREG          ||
            0 == pru_GTI_WRITEREG         ||
            0 == pru_GTI_WRITEMEM_BLK     ||
            0 == pru_GTI_READMEM_BLK)     {
            // One or more of the function calls failed to load
            success = false;
            printf("Failed to load function calls from PRU emulation driver.\n");
        }
    }

    if (success) {
        // Load the Target Adapter calls from the library
        CreateTargetAdapter = (CreateTargetAdapter_t*)GetProcAddress(hTALib, "CreateTargetAdapter");
        DeleteTargetAdapter = (DeleteTargetAdapter_t*)GetProcAddress(hTALib, "DeleteTargetAdapter");

        // Check that these loads both worked
        if (0 == CreateTargetAdapter ||
            0 == DeleteTargetAdapter) {
            // One or more of the function calls failed to load
            success = false;
            printf("Failed to load function calls from Target Adapter library.\n");
        }
    }

    // Note: You must configure your OMAPL138 EVM so that the GEM is not held in reset.

    // The OMAPL138 EVM board comes out of power on reset with the PRU module disabled.
    // Connect first to the GEM driver to command the PSC to turn on the PRU, then 
    // disconnect to continue on with the example for TargetAdapter and the PRU.

    if (success) {
        // Initialize the GEM emulation driver. 
        GTI_INIT_INFO initInfo; // Initialization parameters structure

        memset(&initInfo, 0, sizeof(initInfo));

        initInfo.m_structRevision        = GTI_INIT_INFO_REV; // Structure revision
        initInfo.m_structLength          = sizeof(initInfo);  // Size of structure
        initInfo.m_sProcDataFileLocation = BOARD_FILE;        // Board config file

        result = gem_GTI_INIT_EX(0,              // unused
                                 HOST_BOARD_NAME // Name of board to debug appended
                                 "/" HOST_NAME,  // with a slash and name of device
                                 PROBE_PORT,     // Debug probe port address
                                 BOARD_FILE,     // Board config file
                                 0,              // unused
                                 0,              // unused
                                 0,              // unused
                                 &initInfo,      // Initialization parameters structure
                                 &hpid);         // Pointer to return instance handle

        if (GTI_SUCCESS != result) {
            // Init call failed
            success = false;
            printf("Failed to initialize GEM emulation driver.\n");
        }
    }

    if (success) {
        // Connect to the device being debugged
        result = gem_GTI_CONNECT(hpid);

        if (GTI_SUCCESS != result) {
            // Connect call failed
            success = false;
            printf("Failed to connect debug probe to GEM device.\n%s\n", GetError(gem_GTI_GETERRSTR_EX3, hpid));
        }
        else {
            printf("Connected to GEM device.\n");
        }
    }

    if (success) {
        // Enable the PRU device via the PSC0 in the OMAPL138

        const GTI_ADDRS64_TYPE PSC0_MDSTAT_PRU = 0x1c10834; // PSC0 status register for PRU
        const GTI_ADDRS64_TYPE PSC0_MDCTL_PRU  = 0x1c10a34; // PSC0 control register for PRU
        const GTI_ADDRS64_TYPE PSC0_PTCMD      = 0x1c10120; // PSC0 command register

        GTI_DATA_TYPE data[4];

        // Check to see if the PRU is already enabled
        result = gem_GTI_READMEM_WITH_STAT_64(hpid, PSC0_MDSTAT_PRU, 0, 4, 0, 0, 0, 0, data, -1, 0);

        if (GTI_SUCCESS == result) {
            // Check for PRU enabled status bits
            if ((data[0] & 0x1f) == 0x03) {
                printf("PRU device is already enabled.\n");
            }
            else {
                printf("Enabling PRU device...\n");

                // Read the current control register
                result = gem_GTI_READMEM_WITH_STAT_64(hpid, PSC0_MDCTL_PRU, 0, 4, 0, 0, 0, 0, data, -1, 0);

                if (GTI_SUCCESS == result) {

                    // Set control bits to enable PRU
                    data[0] = (data[0] & 0xe0) | 0x03;

                    // Write control value back 
                    result = gem_GTI_WRITEMEM_WITH_STAT_64(hpid, PSC0_MDCTL_PRU, 0, 4, 0, 0, 0, 0, data, -1, 0);
                }

                if (GTI_SUCCESS == result) {

                    // Set command to accept new control bits
                    memset(data, 0x00, sizeof(data));
                    data[0] = 0x01;

                    // Write command
                    result = gem_GTI_WRITEMEM_WITH_STAT_64(hpid, PSC0_PTCMD, 0, 4, 0, 0, 0, 0, data, -1, 0);

                    // Wait for command to be accepted
                    while (GTI_SUCCESS == result && 0x01 == data[0]) {
                        result = gem_GTI_READMEM_WITH_STAT_64(hpid, PSC0_PTCMD, 0, 4, 0, 0, 0, 0, data, -1, 0);
                    }

                    // Wait for status to update that PRU is enabled                    
                    while (GTI_SUCCESS == result && (data[0] & 0x1f) != 0x03) {
                        result = gem_GTI_READMEM_WITH_STAT_64(hpid, PSC0_MDSTAT_PRU, 0, 4, 0, 0, 0, 0, data, -1, 0);
                    }

                    if (GTI_SUCCESS != result) {
                        // Something during enable process failed
                        success = false;
                        printf("Failed to enable PRU device.\n%s\n", GetError(gem_GTI_GETERRSTR_EX3, hpid));
                    }
                    else {
                        printf("PRU device is enabled.\n");
                    }
                }
            }
        }
    }

    if (success) {
        // Terminate the session with the GEM emulation driver
        result = gem_GTI_DISCONNECT(hpid);

        if (GTI_SUCCESS != result) {
            // Disconnect call failed
            success = false;
            printf("Failed to disconnect from GEM device.\n%s\n", GetError(gem_GTI_GETERRSTR_EX3, hpid));
        }
        else {
            printf("Disconnected from GEM device.\n");
        }
    }

    if (0 != hpid) {
        // Terminate the session with the emulation driver
        result = gem_GTI_QUIT(hpid);

        if (GTI_SUCCESS != result) {
            // Quit call failed
            success = false;
            printf("Failed to terminate GEM emulation driver.\n");
        }
    }

    if (success) {
        // Initialize the Target Adapter handle to host C674x DSP
        hTA = CreateTargetAdapter(EMUPACK_DIR DRIVERS_SUBDIR C64XPLUS_DRIVER, 
                                  HOST_NAME, 
                                  BOARD_FILE,
                                  PROBE_PORT,
                                  0);

        if (0 == hTA) {
            success = false;
            printf("Failed to initialize Target Adapter handle to host.\n");
        }
    }

    if (success) {
        // Supply additional parameter initializations for the PRU driver.
        // This step must be done just prior to calling GTI_INIT_EX().
        GTI_STRING_TYPE names[] = 
        {
            "PRU Base Address",
            "PRU Register Offset",
            "PRU Program RAM Offset",
            "PRU Data RAM Offset",
            "PRU Program RAM Size",
            "PRU Data RAM Size",
            "PRU Device Size"
        };

        GTI_STRING_TYPE values[] =
        {
            "0x01c30000",
            "0x7000",
            "0x8000",
            "0x0000",
            "0x2000",
            "0x2000",
            "0x10000"
        };

        GTI_LEN_TYPE count = 7;

        (void)pru_GTI_SETUP_PROPERTIES(PROC_BOARD_NAME, names, values, count);
    }

    if (success) {
        // Initialize the PRU emulation driver. 
        GTI_INIT_INFO initInfo; // Initialization parameters structure

        memset(&initInfo, 0, sizeof(initInfo));

        initInfo.m_structRevision        = GTI_INIT_INFO_REV; // Structure revision
        initInfo.m_structLength          = sizeof(initInfo);  // Size of structure
        initInfo.m_sProcDataFileLocation = BOARD_FILE;        // Board config file
        initInfo.m_pMemoryProxy          = hTA;               // TargetAdapter pointer to host

        result = pru_GTI_INIT_EX(0,              // unused
                                 PROC_BOARD_NAME // Name of board to debug appended
                                 "/" PROC_NAME,  // with a slash and name of device
                                 PROBE_PORT,     // Debug probe port address
                                 BOARD_FILE,     // Board config file
                                 0,              // unused
                                 0,              // unused
                                 0,              // unused
                                 &initInfo,      // Initialization parameters structure
                                 &hpid);         // Pointer to return instance handle

        if (GTI_SUCCESS != result) {
            // Init call failed
            success = false;
            printf("Failed to initialize emulation driver.\n");
        }
    }

    if (success) {
        // Connect to the device being debugged
        result = pru_GTI_CONNECT(hpid);

        if (GTI_SUCCESS != result) {
            // Connect call failed
            success = false;
            printf("Failed to connect debug probe to PRU device.\n%s\n", GetError(pru_GTI_GETERRSTR_EX3, hpid));
        }
        else {
            printf("Connected to PRU device.\n");
        }
    }

    {
        // Try out the register calls by reading and writing register R0.
        GTI_REGID_TYPE    regID     = REG_R0_ID; // Register index
        GTI_REGISTER_TYPE regValue  = 0;         // Value  read from register
        GTI_REGISTER_TYPE regExpect = 0;         // Value written to register

        if (success) {
            // Read a value from register R0
            result = pru_GTI_READREG(hpid, regID, &regValue);

            if (GTI_SUCCESS != result) {
                // Read register call failed
                success = false;
                printf("Failed to read register.\n%s\n", GetError(pru_GTI_GETERRSTR_EX3, hpid));
            }
            else {
                printf("Read  0x%08x from register.\n", regValue);
            }             
       }

        if (success) {
            // Write a value to register R0
            regExpect = ~regValue;
            result    = pru_GTI_WRITEREG(hpid, regID, &regExpect);

            if (GTI_SUCCESS != result) {
                // Write register call failed
                success = false;
                printf("Failed to write register.\n%s\n", GetError(pru_GTI_GETERRSTR_EX3, hpid));
            }
        }

        if (success) {
            // Read the value back from register R0
            result = pru_GTI_READREG(hpid, regID, &regValue);

            if (GTI_SUCCESS != result) {
                // Read register call failed
                success = false;
                printf("Failed to read register.\n%s\n", GetError(pru_GTI_GETERRSTR_EX3, hpid));
            }
            else {
                printf("Wrote 0x%08x to register\nRead  0x%08x from register.\n", regExpect, regValue);
            }             
        }
    }

    {
        GTI_ADDRS_TYPE  address = 0x0000; // Memory address to access
        GTI_LEN_TYPE    length  = 0x100;  // Number of memory values to read or write
        GTI_DATA_TYPE   buffer[0x100];   // Buffer to hold memory data

        if (success) {
            // Write a block of memory
            memset(buffer, 0xa5, sizeof(buffer));
    
            result = pru_GTI_WRITEMEM_BLK(hpid, address, 0, length, 0, 0, 0, 0, buffer);

            if (GTI_SUCCESS != result) {
                // Write memory call failed
                success = false;
                printf("Failed to write memory.\n%s\n", GetError(pru_GTI_GETERRSTR_EX3, hpid));
            }
            else {
                printf("Wrote 0x%x values to address   0x%08x\n", length, address);
            }             
        }

        if (success) {
            // Write a block of memory
            memset(buffer, 0x00, sizeof(buffer));
    
            result = pru_GTI_READMEM_BLK(hpid, address, 0, length, 0, 0, 0, 0, buffer);

            if (GTI_SUCCESS != result) {
                // Read memory call failed
                success = false;
                printf("Failed to read memory.\n%s\n", GetError(pru_GTI_GETERRSTR_EX3, hpid));
            }
            else {
                printf("Read  0x%x values from address 0x%08x\n", length, address);
            }             
        }
    }

    if (success) {
        // Terminate the session with the emulation driver
        result = pru_GTI_DISCONNECT(hpid);

        if (GTI_SUCCESS != result) {
            // Disconnect call failed
            success = false;
            printf("Failed to disconnect from device.\n%s\n", GetError(pru_GTI_GETERRSTR_EX3, hpid));
        }
        else {
            printf("Disconnected from device.\n");
        }
    }

    if (0 != hpid) {
        // Terminate the session with the emulation driver
        result = pru_GTI_QUIT(hpid);

        if (GTI_SUCCESS != result) {
            // Quit call failed
            success = false;
            printf("Failed to terminate emulation driver.\n");
        }
    }

    // Clean up Target Adapter instance
    if (0 != hTA) DeleteTargetAdapter(hTA);

    // Clean up libraries
    if (0 != hTALib) FreeLibrary(hTALib);
    if (0 != hPRU)   FreeLibrary(hPRU);
    if (0 != hGEM)   FreeLibrary(hGEM);

    if (success) {
        printf("\nDone! Completed with no emulation errors.\n");
    }

    return;
}

const char *GetError(GTI_FN_GETERR_EX3 *fnGTI_GETERRSTR_EX3, GTI_HANDLE_TYPE hpid)
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

    result = fnGTI_GETERRSTR_EX3(hpid, &sequenceId, &errorCode, &errorClass, &severity,
                                 &action, &buttons, &icon, pszCustomButtons, customButtonsLength,
                                 pszErrorMessage, errorMessageLength);

    return errorMessage;
}

// End of File
