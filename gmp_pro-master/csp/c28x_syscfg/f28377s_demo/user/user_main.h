// This is a example of user_main.h


#ifndef _FILE_USER_MAIN_H_
#define _FILE_USER_MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif

    // CLA variables
    extern float CLAatan2Table[];
    extern float fVal;
    extern float fResult;

    // CLA global symbol
    __interrupt void CLATaskCallback1 ( void );
    __interrupt void cla1Isr1 ();

    //////////////////////////////////////////////////////////////////////////
    // Handle Type definition, copy from <main.c>
    // 
    // 
    
#ifndef SPECIFY_PC_TEST_ENV



#endif // SPECIFY_PC_TEST_ENV


    //////////////////////////////////////////////////////////////////////////
    // Peripheral Variables



    //////////////////////////////////////////////////////////////////////////
    // Devices on the peripheral



    //////////////////////////////////////////////////////////////////////////
    // functions


    // User should implement this 3 functions at least
    //
    void init(void);
    void mainloop(void);
    void setup_peripheral(void);

    // For Controller projects user should implement the following functions
    //
    void ctl_init(void);
    void ctl_mainloop(void);

    // For Controller framework project, the following functions should be implemented.
    // 


    //////////////////////////////////////////////////////////////////////////
    // Additionally functions prototypes 



#ifdef __cplusplus
}
#endif

#endif // _FILE_USER_MAIN_H_
