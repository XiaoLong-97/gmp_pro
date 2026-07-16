/** \file gti_register.h
 * 
 *  This header defines the GTI APIs for accessing registers of the target device.
 * 
 *  Copyright (c) 1998-2017, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_REGISTER_H
#define GTI_REGISTER_H

#ifdef __cplusplus
extern "C" {
#endif


/** Function type for GTI_READREG() and GTI_WRITEREG(). */
typedef GTI_RETURN_TYPE (GTI_FN_REG)(GTI_HANDLE_TYPE, GTI_REGID_TYPE, GTI_REGISTER_TYPE *);


#ifndef GTI_NO_FUNCTION_DECLARATIONS
/** GTI_READREG() - Read target register.
 *
 *  This function reads a single register from target core. regNo is an index
 *  to select which register to read.  Register indices supported by the core 
 *  are found in the XML files located in: <br> 
 *  "CCS installation"/ccs_base/common/targetdb/drivers/TI_reg_ids.<br>
 *  The register XML file name that maps to a core can be found in the
 *  "regids_mapping.xml" file located in the same "TI_reg_ids" folder above.
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_READREG(
    GTI_HANDLE_TYPE    hpid,    /**< [in]  GTI API instance handle. */
    GTI_REGID_TYPE     regNo,   /**< [in]  Index of register to read. */
    GTI_REGISTER_TYPE *regValue /**< [out] Pointer to return value read. */
    );

/** GTI_WRITEREG() - Write to target register.
 *
 *  This function writes to a single register on the target core. regNo is an 
 *  index to select which register to write.  Register indices supported by the
 *  core are found in the XML files located in: <br>
 *  "CCS installation"/ccs_base/common/targetdb/drivers/TI_reg_ids.<br>
 *  The register XML file name that maps to a core can be found in the
 *  "regids_mapping.xml" file located in the same "TI_reg_ids" folder above.
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE
GTI_WRITEREG(
    GTI_HANDLE_TYPE    hpid,    /**< [in]  GTI API instance handle. */
    GTI_REGID_TYPE     regNo,   /**< [in]  Index of register to write. */
    GTI_REGISTER_TYPE *regValue /**< [out] Pointer to value to write. */
    );
#endif /* GTI_NO_FUNCTION_DECLARATIONS */


#ifdef __cplusplus
};
#endif

#endif /* GTI_REGISTER_H */

/* End of File */

