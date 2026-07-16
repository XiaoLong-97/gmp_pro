#ifndef _FILE_ARM_M_GENERAL_H_
#define _FILE_ARM_M_GENERAL_H_

// #define ARCH_NAME "ARM_M"

//////////////////////////////////////////////////////////////////////////'
// Type definition
//
// 2 bytes for each sizeof() result.
#define SIZEOF_UNIT (1)

// C28x BASIC DATA TYPE
#define GMP_PORT_DATA_T              int8_t
#define GMP_PORT_DATA_SIZE_PER_BITS  (8)
#define GMP_PORT_DATA_SIZE_PER_BYTES (1)

// FAST TYPES
#define GMP_PORT_FAST_T                int_fast32_t
#define GMP_PORT_FAST_SIZE_PER_BITS    (32)
#define GMP_PORT_FAST_SIZE_PER_BYTES   (4)

#define GMP_PORT_FAST8_T               int32_t
#define GMP_PORT_FAST8_SIZE_PER_BITS   (32)
#define GMP_PORT_FAST8_SIZE_PER_BYTES  (4)

#define GMP_PORT_FAST16_T              int32_t
#define GMP_PORT_FAST16_SIZE_PER_BITS  (32)
#define GMP_PORT_FAST16_SIZE_PER_BYTES (4)

#define GMP_PORT_FAST32_T              int_fast32_t
#define GMP_PORT_FAST32_SIZE_PER_BITS  (32)
#define GMP_PORT_FAST32_SIZE_PER_BYTES (4)

// time_gt
#define GMP_PORT_TIME_T              uint32_t
#define GMP_PORT_TIME_SIZE_PER_BITS  (32)
#define GMP_PORT_TIME_SIZE_PER_BYTES (4)
#define GMP_PORT_TIME_MAXIMUM        (UINT32_MAX)

// size_gt
#define GMP_PORT_SIZE_T              uint32_t
#define GMP_PORT_SIZE_SIZE_PER_BITS  (32)
#define GMP_PORT_SIZE_SIZE_PER_BYTES (4)

// addr_gt
#define GMP_PORT_ADDR_T              uint32_t
#define GMP_PORT_ADDR_SIZE_PER_BITS  (32)
#define GMP_PORT_ADDR_SIZE_PER_BYTES (4)

// addr32_gt
#define GMP_PORT_ADDR32_T              uint32_t
#define GMP_PORT_ADDR32_SIZE_PER_BITS  (32)
#define GMP_PORT_ADDR32_SIZE_PER_BYTES (4)

// addr16_gt
#define GMP_PORT_ADDR16_T              uint32_t
#define GMP_PORT_ADDR16_SIZE_PER_BITS  (32)
#define GMP_PORT_ADDR16_SIZE_PER_BYTES (4)

// diff_gt
#define GMP_PORT_DIFF_T              int32_t
#define GMP_PORT_DIFF_SIZE_PER_BITS  (32)
#define GMP_PORT_DIFF_SIZE_PER_BYTES (4)

// param_gt
#define GMP_PORT_PARAM_T              int32_t
#define GMP_PORT_PARAM_SIZE_PER_BITS  (32)
#define GMP_PORT_PARAM_SIZE_PER_BYTES (4)

// adc_gt
#define GMP_PORT_ADC_T              uint32_t
#define GMP_PORT_ADC_SIZE_PER_BITS  (32)
#define GMP_PORT_ADC_SIZE_PER_BYTES (4)

// dac_gt
#define GMP_PORT_DAC_T              uint32_t
#define GMP_PORT_DAC_SIZE_PER_BITS  (32)
#define GMP_PORT_DAC_SIZE_PER_BYTES (4)

// pwm_gt
#define GMP_PORT_PWM_T              uint32_t
#define GMP_PORT_PWM_SIZE_PER_BITS  (32)
#define GMP_PORT_PWM_SIZE_PER_BYTES (4)

//////////////////////////////////////////////////////////////////////////
// Optimize for keywords

// These features are provided in the following code in CMSIS.
// + core_cm0.h
// + core_cm0plus.h
// + core_cm1.h
// + core_cm3.h
// + core_cm4.h
// + core_cm7.h
// + core_cm23.h
// + core_cm33.h
// + core_cm35.h

// When applied to a function declaration or definition that returns a pointer type,
// restrict tells the compiler that the function returns an object that is not aliased,
// that is, referenced by any other pointers.
// This allows the compiler to perform additional optimizations.
//
#define GMP_PARAM_RESTRICT __RESTRICT

// This macro define the default static inline behavior.
#define GMP_STATIC_INLINE __STATIC_INLINE

// The following macro will create a section of struct,
//
#define GMP_PARAM_STRACK_PACK __PACKED
#define GMP_PARAM_STRACK_PACK_RELEASE

// This macro will create a section of code.
// The compiler will not perform out of order memory access operations on this interval
#define GMP_MEMORY_BARRIER __COMPILER_BARRIER

//// This macro should clear all the I cache
////
// #define GMP_FLUSH_ICACHE   __ISB()
// #define GMP_FLUSH_DCACHE   __DSB()

#endif // _FILE_ARM_M_GENERAL_H_
