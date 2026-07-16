/** \file gti_memory.h
 * 
 *  This header defines the GTI APIs for accessing memory of the target device.
 *  
 *  The memory APIs use a common set of parameters that are documented here: 
 *  
 *  <b>page</b> is used for architectures that support separate memory pages (e.g. 
 *  C55x has separate program, data, and i/o pages).
 *  
 *  <b>count</b> is the number of memory "units" to read. A memory unit size is 
 *  determined by how memory is addressed by target device. If memory locations
 *  are byte addressable, then a single unit is 8 bits.  If memory locations
 *  are 16-bit addressable, then a single unit is 16 bits. 
 *  
 *  <b>attr</b> defines optional parameters for the memory accesses. These are: <br>
 *  GTI_ATTR_SHARED - Memory access is to shared memory. <br>
 *  GTI_ATTR_CACHE - Memory access should update caches only. <br>
 *  GTI_START_DOWNLOAD - Memory write is the first of a download. <br>
 *  GTI_END_DOWNLOAD - Memory write is the last of a download. <br>
 *  GTI_CONTINUE_DOWNLOAD - Memory write is a continuation of a download. <br>
 *  Note that the DOWNLOAD parameters are to help the driver optimize writing 
 *  large quantities of data. Once the client begins a download by using the 
 *  GTI_START_DOWNLOAD parameter with a memory write, no other GTI API calls
 *  should be made to any targets until the download is complete.  Once
 *  a download has begun, sending a write with GTI_END_DOWNLOAD is required
 *  to end it; you may send a zero length write with this parameter if needed. <br>
 *  GTI_ATTR_READ_VERIFY - Request driver to read verify a memory write. <br>
 *  GTI_ATTR_CACHE_BYPASS - Bypass the cache (C62x & C67x only). <br>
 *  
 *  <b>strAttr</b> defines optional parameters for memory accesses as strings. The only
 *  two attributes supported this way are "|$$SHARED" for access to shared 
 *  memory and "|CACHE" for accesses that should only update the caches. 
 *  
 *  <b>accessSize</b> sets how many bits are accessed at a time by the debug hardware.
 *  Use GTI_ACCESS_SIZE_NONE to have the driver choose the optimal access size. 
 *  Use GTI_ACCESS_SIZE_BYTE, GTI_ACCESS_SIZE_HALF, or GTI_ACCESS_SIZE_WORD to 
 *  force the driver to use 8-bit, 16-bit, and 32-bit accesses respectively.
 *  
 *  <b>buf</b> is an array of 32-bit elements. The number of elements must be 
 *  equal to the count parameter. Each element of the buf array will hold only
 *  one memory unit. So that if the target's memory is byte addressable, each
 *  element in buf will contains just a single 8 bit value. The caller 
 *  allocates this array.
 *  
 *  <b>mem_access_id</b> is a collection of bit flags to determine what memory
 *  and caches levels will be accessed. It is used to, for example, write to
 *  a single cache level, or to bypass a cache. The meaning of these bits are 
 *  determined through the GTI_GET_MEM_LEVEL_INFO() API.  Using -1 for this
 *  is the default meaning "CPU view" of memory.
 *  
 *  <b>pMem_status_buf</b> is an array of GTI_STRUCT_MEM_STAT structures that
 *  return status information for each memory unit accessed. This may be 
 *  set to NULL to skip returning status information. The caller allocates
 *  this array.
 *
 *  Copyright (c) 1998-2015, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_MEMORY_H
#define GTI_MEMORY_H


/** Export attribute for GTI_READMEM_BLK() and GTI_WRITEMEM_BLK(). */
#if TRG_MEMORY_ACCESS_SIZE_EXT
#define TRG_MEMORY_ACCESS_SIZE_EXT_EXPORT GTI_EXPORT
#else
#define TRG_MEMORY_ACCESS_SIZE_EXT_EXPORT 
#endif


#ifdef __cplusplus
extern "C" {
#endif


/** Memory attribute flags.
 *  Used by GTI_READMEM_WITH_STAT_64(), GTI_READMEM_WITH_STAT(), GTI_READMEM_BLK(),
 *  GTI_READMEM_EX(), GTI_WRITEMEM_WITH_STAT_64(), GTI_WRITEMEM_WITH_STAT(), 
 *  GTI_WRITEMEM_BLK(), and GTI_WRITEMEM_EX().
 */
#define GTI_ATTR_SHARED       0x00000100 /**< Memory access is to shared memory. */
#define GTI_ATTR_CACHE        0x00008000 /**< Memory access should update caches only. */
#define GTI_START_DOWNLOAD    0x00010000 /**< Memory write is the first of a download. */
#define GTI_END_DOWNLOAD      0x00020000 /**< Memory write is the last of a download. */
#define GTI_CONTINUE_DOWNLOAD 0x00030000 /**< Memory write is a continuation of a download. */
#define GTI_ATTR_READ_VERIFY  0x00040000 /**< Request driver to read verify a memory write. */
#define GTI_ATTR_CACHE_BYPASS 0x00080000 /**< Bypass the cache (C62x & C67x only). */

/** Memory access width sizes.
 *  Used by GTI_READMEM_WITH_STAT_64(), GTI_READMEM_WITH_STAT(), GTI_READMEM_BLK(),
 *  GTI_WRITEMEM_WITH_STAT_64(), GTI_WRITEMEM_WITH_STAT(), and GTI_WRITEMEM_BLK().
 */
#define GTI_ACCESS_SIZE_NONE 0x0000 /**< Default, let driver choose access size. */
#define GTI_ACCESS_SIZE_BYTE 0x0001 /**< Force memory access to 8-bit width. */
#define GTI_ACCESS_SIZE_HALF 0x0002 /**< Force memory access to 16-bit width. */
#define GTI_ACCESS_SIZE_WORD 0x0004 /**< Force memory access to 32-bit width. */


/** Memory access status result values.
 *  Used by GTI_READMEM_WITH_STAT_64(), GTI_READMEM_WITH_STAT(), 
 *  GTI_WRITEMEM_WITH_STAT_64(), and GTI_WRITEMEM_WITH_STAT().
 */
typedef enum 
{
    GTI_MEM_STAT_PASS = 0,      /**< Memory access succeeded. */
    GTI_MEM_STAT_FAIL,          /**< Memory access failed. */
    GTI_MEM_STAT_SECURITY,      /**< Memory access caused security violation. */
    GTI_MEM_STAT_NOT_PRESENT,   /**< Memory requested is not present in the specified memory level. */
    GTI_MEM_STAT_INVALID,       /**< Memory access was invalid. */
    GTI_MEM_STAT_NOT_ATTEMPTED, /**< Memory access request was not attempted. */
    GTI_MEM_STAT_MMU_FAULT      /**< Memory access caused an MMU fault. */
} GTI_ENUM_MEM_RESULT;

/** Memory access status result structure.
 *  Used by GTI_READMEM_WITH_STAT_64(), GTI_READMEM_WITH_STAT(), 
 *  GTI_WRITEMEM_WITH_STAT_64(), and GTI_WRITEMEM_WITH_STAT().
 */
typedef struct 
{
    GTI_ENUM_MEM_RESULT mem_result; /**< Memory access status result value. */
    GTI_INT_TYPE        mem_hit_id; /**< Memory level "hit" by access. */
} GTI_STRUCT_MEM_STAT;

/** Region sizes for memory attributes used by GTI_GET_MEM_LEVEL_INFO(). */
typedef enum REGION_SIZE
{
    REGION_SIZE_NONE = 0, /**< Invalid region size. */
    REGION_SIZE_0,        /**< Region size =   0. */
    REGION_SIZE_512B,     /**< Region size = 512 B. */
    REGION_SIZE_1KB,      /**< Region size =   1 kB. */
    REGION_SIZE_2KB,      /**< Region size =   2 kB. */
    REGION_SIZE_4KB,      /**< Region size =   4 kB. */
    REGION_SIZE_8KB,      /**< Region size =   8 kB. */
    REGION_SIZE_16KB,     /**< Region size =  16 kB. */
    REGION_SIZE_32KB,     /**< Region size =  32 kB. */
    REGION_SIZE_64KB,     /**< Region size =  64 kB. */
    REGION_SIZE_128KB,    /**< Region size = 128 kB. */
    REGION_SIZE_256KB,    /**< Region size = 256 kB. */
    REGION_SIZE_512KB,    /**< Region size = 512 kB. */
    REGION_SIZE_1MB,      /**< Region size =   1 MB. */
    REGION_SIZE_2MB,      /**< Region size =   2 MB. */
    REGION_SIZE_MAX       /**< Marks end of list. */
} REGION_SIZE_T;

/** Cache line size for memory attributes used by GTI_GET_MEM_LEVEL_INFO(). */
typedef enum 
{
    LINE_SIZE_NONE = 0, /**< Line size   0 bytes, no cache. */
    LINE_SIZE_2B,       /**< Line size   2 bytes. */
    LINE_SIZE_4B,       /**< Line size   4 bytes. */
    LINE_SIZE_8B,       /**< Line size   8 bytes. */
    LINE_SIZE_16B,      /**< Line size  16 bytes. */
    LINE_SIZE_32B,      /**< Line size  32 bytes. */
    LINE_SIZE_64B,      /**< Line size  64 bytes. */
    LINE_SIZE_128B,     /**< Line size 128 bytes. */
    LINE_SIZE_MAX       /**< Marks end of list. */
} LINE_SIZE_T;

/** Maximum length for a memory level name used by GTI_GET_MEM_LEVEL_INFO(). */
#define MEM_LEVEL_MAX_NAME  (30)

/** Memory level bit types used by GTI_GET_MEM_LEVEL_INFO(). */
typedef enum 
{
    GTI_MEM_ACCESS_RESERVED = 0,          /**< Bit is undefined/unused. */
    GTI_MEM_ACCESS_QUERY,                 /**< Bit a query op. */
    GTI_MEM_ACCESS_MEM_LEVEL,             /**< Bit is a memory/cache level. */
    GTI_MEM_ACCESS_OP_MMU_CURRENT,        /**< Bit is a bypass the MMU op. */
    GTI_MEM_ACCESS_OP_COHERENT,           /**< Bit is an access coherency op. */
    GTI_MEM_ACCESS_OP_PRIORITY_BYPASS,    /**< Bit is a bypass/coherency priority op. */
    GTI_MEM_ACCESS_OP_ENDSTATE_RATIONAL,  /**< Bit is an end state of the target op. */
	GTI_MEM_ACCESS_OP_MMU_STAGE2_CURRENT, /**< Bit is a bypass the second stage MMU op. */
    GTI_MEM_ACCESS_BIT_MAX                /**< Marks end of list. */
} GTI_MEM_ACCESS_BIT_TYPE;

/** Memory level attribute structure to define memory levels used by GTI_GET_MEM_LEVEL_INFO(). */
typedef struct GTI_MEM_LEVEL_ATTRIB_tag {
    uint32_t        nMemLevel;                   /**< Memory level, 0-15 (L1 cache = 1, L2 cache = 2, etc). */
    char            pszName[MEM_LEVEL_MAX_NAME]; /**< Memory level name (e.g. "L1D", "L1P Cache", "L2"). */
    bool            bIsBypassable;               /**< If true, this memory level can be bypassed. */
    bool            bIsCache;                    /**< If true, this memory level is cache memory. */
    uint32_t        nCacheLineSize;              /**< Cache line size as an exponent of 2 (e.g. 7 = 128 byte cache line). */
    bool            bIsPaged;                    /**< If true, this is paged memory. */
    bool            bIsIO;                       /**< If true, this is I/O memory space. */
    bool            bIsShared;                   /**< If true, this is shared memory. */
    bool            bIsProgram;                  /**< If true, this is program (instruction) memory. */
    bool            bIsData;                     /**< If true, this is data memory. */
    bool            bIsExternal;                 /**< If true, this is external memory. */
    bool            bIsTCM;                      /**< If true, this is tightly-coupled memory (TCM). */
    REGION_SIZE_T   nTCMRegionSize;              /**< TCM region size as REGION_SIZE enum entry. */
    bool            bCanBeProtected;             /**< If true, this memory can be protected. */
    bool            bCanBeSecured;               /**< If true, this memory can be secured. */
    bool            bIsSimulatedDatalessCache;   /**< If true, indicates simulated dataless cache (simulators only). */
    GTI_UINT32_TYPE nCacheSizeInMAUs;            /**< Maximum size of the cache in memory units. */
    GTI_UINT32_TYPE nVirtualAddressWidth;        /**< Virtual memory address bus width. */
    GTI_UINT32_TYPE nPhysicalAddressWidth;       /**< Physical memory address bus width. */
	GTI_UINT32_TYPE nStage2PhysicalAddressWidth; /**< Physical memory address bus width as seen by stage2. */
} GTI_MEM_LEVEL_ATTRIB;

/** Memory level structure used by GTI_GET_MEM_LEVEL_INFO() to define the bits for mem_access_id. */
typedef struct GTI_MEM_LEVEL_INFO_tag {
    uint32_t                 nRevision;     /**< Revision of this structure and GTI_MEM_LEVEL_ATTRIB structure. */
    GTI_MEM_ACCESS_BIT_TYPE  eBitType;      /**< Defines what type of bit this is (op, memory level, etc.). */
    GTI_MEM_LEVEL_ATTRIB    *pLevelAttribs; /**< Memory level attributes when eBitType == GTI_MEM_ACCESS_MEM_LEVEL. */
} GTI_MEM_LEVEL_INFO;
#define GTI_MEM_ACCESS_REVISION (2) /**< Revision of the GTI_MEM_LEVEL_INFO and GTI_MEM_LEVEL_ATTRIB structures. */


/** Function type for GTI_READMEM_WITH_STAT_64() and GTI_WRITEMEM_WITH_STAT_64(). */
typedef GTI_RETURN_TYPE (GTI_FN_MEM_WITH_STAT_64)
    (GTI_HANDLE_TYPE, GTI_ADDRS64_TYPE, GTI_PAGE_TYPE, GTI_LEN_TYPE, 
     GTI_MEM_NUM_ATTR_TYPE, GTI_MEM_STR_ATTR_TYPE, GTI_WAIT_STATE_TYPE,
     GTI_INT_TYPE, GTI_DATA_TYPE*, GTI_INT_TYPE, GTI_STRUCT_MEM_STAT*);

/** Function type for GTI_READMEM_WITH_STAT() and GTI_WRITEMEM_WITH_STAT(). */
typedef GTI_RETURN_TYPE (GTI_FN_MEM_WITH_STAT) 
    (GTI_HANDLE_TYPE, GTI_ADDRS_TYPE, GTI_PAGE_TYPE, GTI_LEN_TYPE,
     GTI_MEM_NUM_ATTR_TYPE, GTI_MEM_STR_ATTR_TYPE, GTI_WAIT_STATE_TYPE,
     GTI_INT_TYPE, GTI_DATA_TYPE*, GTI_INT_TYPE,  GTI_STRUCT_MEM_STAT*);

/** Function type for GTI_READMEM_BLK() and GTI_WRITEMEM_BLK(). */
typedef GTI_RETURN_TYPE (GTI_FN_MEM_BLK)
    (GTI_HANDLE_TYPE, GTI_ADDRS_TYPE, GTI_PAGE_TYPE, GTI_LEN_TYPE, 
     GTI_MEM_NUM_ATTR_TYPE, GTI_MEM_STR_ATTR_TYPE, GTI_WAIT_STATE_TYPE, 
     GTI_INT_TYPE, GTI_DATA_TYPE*);

/** Function type for GTI_READMEM_EX() and GTI_WRITEMEM_EX(). */
typedef GTI_RETURN_TYPE (GTI_FN_MEM_EX)
    (GTI_HANDLE_TYPE, GTI_ADDRS_TYPE, GTI_PAGE_TYPE, GTI_LEN_TYPE, 
     GTI_MEM_NUM_ATTR_TYPE, GTI_MEM_STR_ATTR_TYPE, GTI_WAIT_STATE_TYPE, 
     GTI_DATA_TYPE*);

/** Function type for GTI_GET_MEM_LEVEL_INFO(). */
typedef GTI_RETURN_TYPE (GTI_FN_MEM_LEVEL_INFO)
    (GTI_HANDLE_TYPE, GTI_UINT32_TYPE, GTI_MEM_LEVEL_INFO*);


#ifndef GTI_NO_FUNCTION_DECLARATIONS
/** GTI_READMEM_WITH_STAT_64() - Read target memory with 64-bit memory addresses.
 *
 *  This function reads a block of memory from target device. This call extends
 *  GTI_READMEM_WITH_STAT() by adding support for 64-bit memory addresses.
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_READMEM_WITH_STAT_64(
    GTI_HANDLE_TYPE        hpid,           /**< [in]  GTI API instance handle. */
    GTI_ADDRS64_TYPE       startAddress,   /**< [in]  Starting address of memory read. */
    GTI_PAGE_TYPE          page,           /**< [in]  Memory page to access. */
    GTI_LEN_TYPE           count,          /**< [in]  Number of memory units to read. */
    GTI_MEM_NUM_ATTR_TYPE  attr,           /**< [in]  Optional parameter flags. */
    GTI_MEM_STR_ATTR_TYPE  strAttr,        /**< [in]  Optional parameter string. */
    GTI_WAIT_STATE_TYPE    waitState,      /**< [in]  Set wait states (unused). */
    GTI_INT_TYPE           accessSize,     /**< [in]  Memory access width. */
    GTI_DATA_TYPE         *buf,            /**< [out] Buffer to return read data. */
    GTI_INT_TYPE           mem_access_id,  /**< [in]  Memory level access flags. */
    GTI_STRUCT_MEM_STAT   *pMem_status_buf /**< [out] Buffer to return status results. */
    );

/** GTI_READMEM_WITH_STAT() - Read target memory with status.
 *
 *  This function reads a block of memory from target device. This call extends
 *  GTI_READMEM_BLK() by letting caller choose specific memory levels to access 
 *  and by returning status for each memory unit accessed.
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_READMEM_WITH_STAT(
    GTI_HANDLE_TYPE        hpid,           /**< [in]  GTI API instance handle. */
    GTI_ADDRS_TYPE         startAddress,   /**< [in]  Starting address of memory read. */
    GTI_PAGE_TYPE          page,           /**< [in]  Memory page to access. */
    GTI_LEN_TYPE           count,          /**< [in]  Number of memory units to read. */
    GTI_MEM_NUM_ATTR_TYPE  attr,           /**< [in]  Optional parameter flags. */
    GTI_MEM_STR_ATTR_TYPE  strAttr,        /**< [in]  Optional parameter string. */
    GTI_WAIT_STATE_TYPE    waitState,      /**< [in]  Set wait states (unused). */
    GTI_INT_TYPE           accessSize,     /**< [in]  Memory access width. */
    GTI_DATA_TYPE         *buf,            /**< [out] Buffer to return read data. */
    GTI_INT_TYPE           mem_access_id,  /**< [in]  Memory level access flags. */
    GTI_STRUCT_MEM_STAT   *pMem_status_buf /**< [out] Buffer to return status results. */
    );

/** GTI_READMEM_BLK() - Read target memory with access size.
 *
 *  This function reads a block of memory from target device. This call extends
 *  GTI_READMEM_EX() by letting caller choose a specific access width for the
 *  memory access.
 *
 * \return 0 on success, -1 on error.
 */
TRG_MEMORY_ACCESS_SIZE_EXT_EXPORT GTI_RETURN_TYPE 
GTI_READMEM_BLK(
    GTI_HANDLE_TYPE        hpid,           /**< [in]  GTI API instance handle. */
    GTI_ADDRS_TYPE         startAddress,   /**< [in]  Starting address of memory read. */
    GTI_PAGE_TYPE          page,           /**< [in]  Memory page to access. */
    GTI_LEN_TYPE           count,          /**< [in]  Number of memory units to read. */
    GTI_MEM_NUM_ATTR_TYPE  attr,           /**< [in]  Optional parameter flags. */
    GTI_MEM_STR_ATTR_TYPE  strAttr,        /**< [in]  Optional parameter string. */
    GTI_WAIT_STATE_TYPE    waitState,      /**< [in]  Set wait states (unused). */
    GTI_INT_TYPE           accessSize,     /**< [in]  Memory access width. */
    GTI_DATA_TYPE         *buf             /**< [out] Buffer to return read data. */
    );

/** GTI_READMEM_EX() - Read target memory.
 *
 *  This function reads a block of memory from target device. 
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_READMEM_EX(
    GTI_HANDLE_TYPE        hpid,           /**< [in]  GTI API instance handle. */
    GTI_ADDRS_TYPE         startAddress,   /**< [in]  Starting address of memory read. */
    GTI_PAGE_TYPE          page,           /**< [in]  Memory page to access. */
    GTI_LEN_TYPE           count,          /**< [in]  Number of memory units to read. */
    GTI_MEM_NUM_ATTR_TYPE  attr,           /**< [in]  Optional parameter flags. */
    GTI_MEM_STR_ATTR_TYPE  strAttr,        /**< [in]  Optional parameter string. */
    GTI_WAIT_STATE_TYPE    waitState,      /**< [in]  Set wait states (unused). */
    GTI_DATA_TYPE         *buf             /**< [out] Buffer to return read data. */
    );

/** GTI_WRITEMEM_WITH_STAT_64() - Write target memory with 64-bit memory addresses.
 *
 *  This function writes a block of memory on target device. This call extends
 *  GTI_WRITEMEM_WITH_STAT() by adding support for 64-bit memory addresses.
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_WRITEMEM_WITH_STAT_64(
    GTI_HANDLE_TYPE        hpid,           /**< [in]  GTI API instance handle. */
    GTI_ADDRS64_TYPE       startAddress,   /**< [in]  Starting address of memory write. */
    GTI_PAGE_TYPE          page,           /**< [in]  Memory page to access. */
    GTI_LEN_TYPE           count,          /**< [in]  Number of memory units to write. */
    GTI_MEM_NUM_ATTR_TYPE  attr,           /**< [in]  Optional parameter flags. */
    GTI_MEM_STR_ATTR_TYPE  strAttr,        /**< [in]  Optional parameter string. */
    GTI_WAIT_STATE_TYPE    waitState,      /**< [in]  Set wait states (unused). */
    GTI_INT_TYPE           accessSize,     /**< [in]  Memory access width. */
    GTI_DATA_TYPE         *buf,            /**< [in]  Buffer with data to write. */
    GTI_INT_TYPE           mem_access_id,  /**< [in]  Memory level access flags. */
    GTI_STRUCT_MEM_STAT   *pMem_status_buf /**< [out] Buffer to return status results. */
    );

/** GTI_WRITEMEM_WITH_STAT() - Write target memory with status.
 *
 *  This function writes a block of memory on target device. This call extends
 *  GTI_WRITEMEM_BLK() by letting caller choose specific memory levels to access 
 *  and by returning status for each memory unit accessed.
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_WRITEMEM_WITH_STAT(
    GTI_HANDLE_TYPE        hpid,           /**< [in]  GTI API instance handle. */
    GTI_ADDRS_TYPE         startAddress,   /**< [in]  Starting address of memory write. */
    GTI_PAGE_TYPE          page,           /**< [in]  Memory page to access. */
    GTI_LEN_TYPE           count,          /**< [in]  Number of memory units to write. */
    GTI_MEM_NUM_ATTR_TYPE  attr,           /**< [in]  Optional parameter flags. */
    GTI_MEM_STR_ATTR_TYPE  strAttr,        /**< [in]  Optional parameter string. */
    GTI_WAIT_STATE_TYPE    waitState,      /**< [in]  Set wait states (unused). */
    GTI_INT_TYPE           accessSize,     /**< [in]  Memory access width. */
    GTI_DATA_TYPE         *buf,            /**< [in]  Buffer with data to write. */
    GTI_INT_TYPE           mem_access_id,  /**< [in]  Memory level access flags. */
    GTI_STRUCT_MEM_STAT   *pMem_status_buf /**< [out] Buffer to return status results. */
    );

/** GTI_WRITEMEM_BLK() - Write target memory with access size.
 *
 *  This function writes a block of memory on target device. This call extends
 *  GTI_WRITEMEM_EX() by letting caller choose a specific access width for the
 *  memory access.
 *
 * \return 0 on success, -1 on error.
 */
TRG_MEMORY_ACCESS_SIZE_EXT_EXPORT GTI_RETURN_TYPE 
GTI_WRITEMEM_BLK(
    GTI_HANDLE_TYPE        hpid,           /**< [in]  GTI API instance handle. */
    GTI_ADDRS_TYPE         startAddress,   /**< [in]  Starting address of memory write. */
    GTI_PAGE_TYPE          page,           /**< [in]  Memory page to access. */
    GTI_LEN_TYPE           count,          /**< [in]  Number of memory units to write. */
    GTI_MEM_NUM_ATTR_TYPE  attr,           /**< [in]  Optional parameter flags. */
    GTI_MEM_STR_ATTR_TYPE  strAttr,        /**< [in]  Optional parameter string. */
    GTI_WAIT_STATE_TYPE    waitState,      /**< [in]  Set wait states (unused). */
    GTI_INT_TYPE           accessSize,     /**< [in]  Memory access width. */
    GTI_DATA_TYPE         *buf             /**< [in]  Buffer with data to write. */
    );

/** GTI_WRITEMEM_EX() - Write target memory.
 *
 *  This function writes a block of memory on target device. 
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE 
GTI_WRITEMEM_EX(
    GTI_HANDLE_TYPE        hpid,           /**< [in]  GTI API instance handle. */
    GTI_ADDRS_TYPE         startAddress,   /**< [in]  Starting address of memory write. */
    GTI_PAGE_TYPE          page,           /**< [in]  Memory page to access. */
    GTI_LEN_TYPE           count,          /**< [in]  Number of memory units to write. */
    GTI_MEM_NUM_ATTR_TYPE  attr,           /**< [in]  Optional parameter flags. */
    GTI_MEM_STR_ATTR_TYPE  strAttr,        /**< [in]  Optional parameter string. */
    GTI_WAIT_STATE_TYPE    waitState,      /**< [in]  Set wait states (unused). */
    GTI_DATA_TYPE         *buf             /**< [in]  Buffer with data to write. */
    );

/** GTI_GET_MEM_LEVEL_INFO() - Query for memory level definitions.
 *
 *  This function enables the client to enumerate through the possible 
 *  mem_access_id bits to determine what memory levels and operations are 
 *  possible for the target device.  This should be called with nMemAccessID
 *  set to a different bit (0 to 30) to learn the meaning of each bit.
 *  Bit 31 always has the meaning "default CPU view" when set no matter what 
 *  other bits are set to support legacy behavior. The caller allocates
 *  the GTI_MEM_LEVEL_INFO structure and GTI_MEM_LEVEL_ATTRIB structure
 *  used by this call and sets nRevision to GTI_MEM_ACCESS_REVISION.
 *
 * \return 0 on success, -1 on error.
 */
GTI_EXPORT GTI_RETURN_TYPE
GTI_GET_MEM_LEVEL_INFO(
    GTI_HANDLE_TYPE     hpid,         /**< [in]     GTI API instance handle. */
    GTI_UINT32_TYPE     nMemAccessID, /**< [in]     Value (0 to 30) of the mem_access_id bit to query. */ 
    GTI_MEM_LEVEL_INFO *pInfo         /**< [in,out] Pointer to return meaning of the mem_access_id bit. */
    );
#endif /* GTI_NO_FUNCTION_DECLARATIONS */


#ifdef __cplusplus
};
#endif

#endif  /* GTI_MEMORY_H */

/* End of File */
