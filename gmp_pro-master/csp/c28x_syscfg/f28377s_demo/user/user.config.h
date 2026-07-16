// This is the example of user.config.h

/////////////////////////////////////////////////
// global runtime environment config

// Specify the running environment
#define MASTERCHIP GMP_AUTO_STM32

// Disable Base print function
#define SPECIFY_BASE_PRINT_NOT_IMPL


////////////////////////////////////////////////
// GMP CTL config

// Specify enable CTL library
#define SPECIFY_ENABLE_GMP_CTL

// Specify enable CTL framework nano
// CTL FRAMEWORK NANO will be enabled.
#define SPECIFY_ENABLE_CTL_FRAMEWORK_NANO

// Specify call periodic dispatch manually
// User should call the following 4 functions manually,
// at the right time in correct order.
// + ctl_fmif_input_stage_routine(ctl_object_nano_t*)
// + ctl_fmif_core_stage_routine(ctl_object_nano_t*)
// + ctl_fmif_output_stage_routine(ctl_object_nano_t*)
// + ctl_fmif_request_stage_routine(ctl_object_nano_t*)
//
#define SPECIFY_CALL_PERIODIC_DISPATCH_MANUALLY

// #define SPECIFY_CTRL_GT_TYPE USING_DOUBLE_FPU
 #define SPECIFY_CTRL_GT_TYPE USING_FLOAT_FPU
//#define SPECIFY_CTRL_GT_TYPE USING_FIXED_TI_IQ_LIBRARY



