/**
 * @file sys_model.stm32.h
 * @author Javnson (javnson@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2024-09-30
 * 
 * @copyright Copyright GMP(c) 2024
 * 
 */
 
// This file implement all the STM32 system core functions.

// Type Definitions
// Reference to `default_types.h`
// Nothing to be changed.
//

// None.


// + Clock Management
// System Clock topology management.
//
#ifdef HAL_RCC_MODULE_ENABLED


#endif

// + Power Management
// System has enable Power configurations.
//
#ifdef HAL_PWR_MODULE_ENABLED

#endif


// Watch Gog
// System has enable Watch Dog module.
//
#if defined HAL_IWDG_MODULE_ENABLED

// IWDG handle
#if defined HAL_IWDG_MODULE_ENABLED
extern IWDG_HandleTypeDef hiwdg;
#endif // HAL_IWDG_MODULE_ENABLED, IWDG enabled

/**
 * @brief This function may fresh IWDG counter.
 * This function should be implemented by CSP,
 * Every Loop routine, this function would be called.
 * CSP implementation should ensure that the function has only one thing is to feed the watchdog
 */
void gmp_hal_wd_feed(void);

#endif // HAL_IWDG_MODULE_ENABLED



// + CRC check
// System enable CRC coding check
//
#ifdef HAL_CRC_MODULE_ENABLED

#endif

