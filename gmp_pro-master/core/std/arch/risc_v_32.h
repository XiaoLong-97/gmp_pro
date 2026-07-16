#ifndef _FILE_ARCH_RISC_V_32_H_
#define _FILE_ARCH_RISC_V_32_H_

#define ARCH_NAME "RISC_V_32"

// 1 bytes for each sizeof() result.
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
#define GMP_PORT_TIME_T              uint64_t
#define GMP_PORT_TIME_SIZE_PER_BITS  (64)
#define GMP_PORT_TIME_SIZE_PER_BYTES (8)
#define GMP_PORT_TIME_MAXIMUM        (UINT64_MAX)

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

#endif // _FILE_ARCH_RISC_V_32_H_
