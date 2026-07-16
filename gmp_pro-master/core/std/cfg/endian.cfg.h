
#ifndef _FILE_GMP_ENDIAN_CFG_H_
#define _FILE_GMP_ENDIAN_CFG_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////
// big-endian to little-endian
//

GMP_STATIC_INLINE
uint16_t gmp_l2b16(uint16_t data)
{
    return ((data & 0xFF) << 8) | ((data & 0xFF00) >> 8);
}

GMP_STATIC_INLINE
uint32_t gmp_l2b32(uint32_t data)
{
    return ((data & 0xFF000000) >> 24) | ((data & 0xFF0000) >> 8) | ((data & 0xFF00) << 8) | ((data & 0xFF) << 24);
}

#ifdef SPECIFY_ENABLE_INTEGER64
// This function cannot run in CLA
#ifndef __TMS320C28XX_CLA__
GMP_STATIC_INLINE
uint64_t gmp_l2b64(uint64_t data)
{
    return ((data & 0xFF00000000000000) >> 56) | ((data & 0xFF000000000000) >> 40) | ((data & 0xFF0000000000) >> 24) |
           ((data & 0xFF00000000) >> 8) | ((data & 0xFF000000) << 8) | ((data & 0xFF0000) << 24) |
           ((data & 0xFF00) << 40) | ((data & 0xFF) << 56);
}
#endif // __TMS320C28XX_CLA__
#endif // SPECIFY_ENABLE_INTEGER64

// Give Big-endian and little-endian an alias
// User may config these function by <user_config.h>
//
#ifndef L2B16
#define L2B16 gmp_l2b16
#endif // L2B16

#ifndef L2B32
#define L2B32 gmp_l2b32
#endif // L2B32

#ifdef SPECIFY_ENABLE_INTEGER64
#ifndef L2B64
#define L2B64 gmp_l2b64
#endif // L2B64
#endif // SPECIFY_ENABLE_INTEGER64

// Specify the alias of Little endian and little endian data.

//
#if GMP_CHIP_ENDIAN == GMP_CHIP_BIG_ENDIAN

// Specify the chip is Big-endian
//

// Specify the data is Big-endian 12-bit data
//
#define BE12(x) ((x))

// Specify the data is Big-endian 16-bit data
//
#define BE16(x) ((x))

// Specify the data is Big-endian 32-bit data
//
#define BE32(x) ((x))

#ifdef SPECIFY_ENABLE_INTEGER64
// Specify the data is Big-endian 64-bit data
//
#define BE64(x) ((x))
#endif // SPECIFY_ENABLE_INTEGER64

// Specify the data is Little-endian 12-bit data
//
#define LE12 L2B12

// Specify the data is Little-endian 16-bit data
//
#define LE16 L2B16

// Specify the data is Little-endian 32-bit data
//
#define LE32 L2B32

#ifdef SPECIFY_ENABLE_INTEGER64
// Specify the data is Little-endian 64-bit data
//
#define LE64 L2B64
#endif // SPECIFY_ENABLE_INTEGER64

#elif GMP_CHIP_ENDIAN == GMP_CHIP_LITTLE_ENDIAN

// Specify the chip is Little-endian
//

// Specify the data is Big-endian 12-bit data
//
#define BE12 L2B12

// Specify the data is Big-endian 16-bit data
//
#define BE16 L2B16

// Specify the data is Big-endian 32-bit data
//
#define BE32 L2B32

#ifdef SPECIFY_ENABLE_INTEGER64
// Specify the data is Big-endian 64-bit data
//
#define BE64 L2B64
#endif // SPECIFY_ENABLE_INTEGER64

// Specify the data is Little-endian 12-bit data
//
#define LE12(x) ((x))

// Specify the data is Little-endian 16-bit data
//
#define LE16(x) ((x))

// Specify the data is Little-endian 32-bit data
//
#define LE32(x) ((x))

#ifdef SPECIFY_ENABLE_INTEGER64
// Specify the data is Little-endian 64-bit data
//
#define LE64(x) ((x))
#endif // SPECIFY_ENABLE_INTEGER64

#else

// Error Little or Big endian should be ensured.
#error("You should specify at least GMP_CHIP_LITTLE_ENDIAN or GMP_CHIP_BIG_ENDIAN")

#endif // LITTLE_ENDIAN

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FILE_GMP_ENDIAN_CFG_H_
