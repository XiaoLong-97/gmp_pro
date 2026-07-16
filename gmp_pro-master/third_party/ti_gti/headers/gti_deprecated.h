/** \file gti_deprecated.h
 * 
 *  This header contains definitions that are deprecated.
 *
 *  The definitions in this header are deprecated and should be removed but
 *  are still being used somewhere in the driver code base. Some of these
 *  are specific to a single driver and belong there.  Some of these simply
 *  shouldn't be used anymore and need to be removed as time permits.
 * 
 *  Copyright (c) 1998-2016, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_DEPRECATED_H
#define GTI_DEPRECATED_H


#ifdef __cplusplus
extern "C" {
#endif

    
/** <i>Deprecated</i>. Driver identification no longer uses the info string. */
#define GTI_INFOSTRING_DEVICE_DRIVER_DESCRIPTION        0x0001
#define GTI_INFOSTRING_DEVICE_DRIVER_DESCRIPTION_STRING "Emulation Device Driver."

/** <i>Deprecated</i>. Board config file version is no longer checked this way. */
#define BOARD_DATA_FILE_VER_TWO 0x2

/** <i>Deprecated</i>. Register indices should be moved to driver or family specific headers. */
#define GTI_REG_PC               0
#define GTI_REG_ANAENBL          0x2F
#define GTI_REG_ANASTAT          0x30
#define GTI_REG_DATBKPT          0x31
#define GTI_REG_DATQUAL          0x32
#define GTI_REG_EVTCNTR          0x33
#define GTI_REG_EVTSELT          0x34
#define GTI_REG_HBPENBL          0x35
#define GTI_REG_PGABKPT          0x36
#define GTI_REG_PROFILE_CLK      0x100
#define GTI_REG_ANK_ST1_ID       6
#define GTI_REG_ANK_ANASTOP_ID   92
#define GTI_REG_ARM_R15          15
#define ARM_ANA_REG_START        38
#define GTI_REG_ARM_ANAENA       ARM_ANA_REG_START+16
#define GTI_REG_ARM_ENDIAN       ARM_ANA_REG_START+18
#define GTI_REG_ARM_ICECRUSHER   ARM_ANA_REG_START+19
#define GTI_REG_ARM_RTDX_ENABLE  ARM_ANA_REG_START+20
#define GTI_REG_C5XX_ST0         0x1
#define GTI_REG_C5XX_PGAQUAL     0x37
#define GTI_REG_C5XX_DATMVAL     0x3C
#define GTI_REG_C5XX_PGABRKP2    0x3D
#define GTI_REG_C5XX_PGAQUAL2    0x3E
#define GTI_REG_C5XX_ARES        0x40
#define GTI_REG_C54X_EXT_PC      0xD2
#define GTI_REG_C6X_CSR          42
#define GTI_REG_C6X_ACR          87
#define GTI_REG_C6X_PCSTOP       93
#define GTI_REG_C6X_AEN          128
#define GTI_REG_C6X_ABE          129
#define GTI_REG_C6X_ADR          130
#define GTI_REG_C6X_ACE          131
#define GTI_REG_C6X_AST          132
#define GTI_REG_C6X_ICNT         133
#define GTI_REG_C6X_XCNT         134
#define GTI_REG_C6X_CLK          135
#define GTI_REG_C6X_ARES         137
#define GTI_C6XCTOOL_FIRST       300
#define GTI_C6XCTOOL_LAST        416
#define GTI_C6XCTL_FIRST         450
#define GTI_C6XCTL_LAST          GTI_C6XCTL_FIRST + (LAST_CTL_REG-FIRST_CTL_REG) 
#define GTI_C6XCTL_OFFSET(n)     (GTI_C6XCTL_FIRST+n)
#define GTI_C6XCTL_PSE_STS_GBKPT GTI_C6XCTL_OFFSET(17)
#define GTI_EMUREG_C6X_DBGSTAT   110
#define GTI_EMUREG_HWBP0         114
#define GTI_EMUREG_HWBP1         115
#define GTI_EMUREG_HWBP2         116
#define GTI_EMUREG_HWBP3         117
#define GTI_EMUREG_RTDX_WADDR    127

/** <i>Deprecated</i>. The serialize API is no longer supported. */
typedef struct 
{
    GTI_UINT32_TYPE nCount;
    GTI_HANDLE_TYPE byteStream;
} CONFIG_SERIALIZE;
#define GTI_CONFIG_SERIALIZE_TYPE CONFIG_SERIALIZE

/** <i>Deprecated</i>. The serialize API is no longer supported. */
enum SERIALIZE_FUNCTION_TYPE 
{
    SERIALIZE_LOAD,
    SERIALIZE_STORE,
    SERIALIZE_END
};


/** <i>Deprecated</i>. GTI_GETERRSTR_EX3() replaces all previous error calls. */
typedef GTI_STRING_TYPE (GTI_FN_GETERR_EX)(GTI_HANDLE_TYPE, GTI_UINT32_TYPE*, GTI_UINT32_TYPE*, GTI_UINT32_TYPE*);

/** <i>Deprecated</i>. GTI_GETERRSTR_EX3() replaces all previous error calls. */
typedef GTI_STRING_TYPE (GTI_FN_GETERR)(GTI_HANDLE_TYPE);


#ifndef GTI_NO_FUNCTION_DECLARATIONS
/** <i>Deprecated</i>. GTI_GETERRSTR_EX3() replaces all previous error calls. */
GTI_EXPORT GTI_FN_GETERR_EX GTI_FAR GTI_GETERRSTR_EX;

/** <i>Deprecated</i>. GTI_GETERRSTR_EX3() replaces all previous error calls. */
GTI_EXPORT GTI_FN_GETERR GTI_FAR GTI_GETERRSTR;
#endif /* GTI_NO_FUNCTION_DECLARATIONS */


#ifdef __cplusplus
};
#endif

#endif /* GTI_DEPRECATED_H */

/* End of File */
