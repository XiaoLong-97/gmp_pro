
cmake_minimum_required(VERSION 3.10)

# Use Env Variable GMP_PRO_LOCATION
set(GMP_PRO_LOCATION $ENV{GMP_PRO_LOCATION})

# fix file path bug
string(REPLACE "\\" "/" GMP_PRO_LOCATION "${GMP_PRO_LOCATION}")

# Add include path
	include_directories("${GMP_PRO_LOCATION}/")
	include_directories("${GMP_PRO_LOCATION}/third_party/fmt/include/fmt")
	include_directories("${GMP_PRO_LOCATION}/csp/windows_simulink")
	include_directories("${GMP_PRO_LOCATION}/third_party/asio/include")
	include_directories("${GMP_PRO_LOCATION}/third_party/eigen/Eigen")

# Add Source path
set(GMP_SOURCE_FILES
	"${GMP_PRO_LOCATION}/ctl/framework/src/ctl_nano.c"
	"${GMP_PRO_LOCATION}/core/src/gmp_dev_util.c"
	"${GMP_PRO_LOCATION}/core/src/gmp_ds_list.c"
	"${GMP_PRO_LOCATION}/core/src/gmp_mm_block_memory.c"
	"${GMP_PRO_LOCATION}/core/src/gmp_std_error_code.c"
	"${GMP_PRO_LOCATION}/core/src/gmp_std_port.c"
	"${GMP_PRO_LOCATION}/csp/windows_simulink/src/windows_simulink_main.cpp"
	"${GMP_PRO_LOCATION}/ctl/component/digital_power/src/combo_boost.c"
	"${GMP_PRO_LOCATION}/ctl/component/digital_power/src/combo_buck.c"
	"${GMP_PRO_LOCATION}/ctl/component/digital_power/src/combo_llc.c"
	"${GMP_PRO_LOCATION}/ctl/component/digital_power/src/combo_pfc.c"
	"${GMP_PRO_LOCATION}/ctl/component/motor_control/src/ctl_mc_basic.c"
	"${GMP_PRO_LOCATION}/ctl/component/motor_control/src/ctl_mc_consultant.c"
	"${GMP_PRO_LOCATION}/ctl/component/motor_control/src/ctl_mc_current_loop.c"
	"${GMP_PRO_LOCATION}/ctl/component/motor_control/src/ctl_mc_motion.c"
	"${GMP_PRO_LOCATION}/ctl/component/motor_control/src/ctl_mc_observer.c"
	"${GMP_PRO_LOCATION}/ctl/component/intrinsic/src/ctl_component_advance.c"
	"${GMP_PRO_LOCATION}/ctl/component/intrinsic/src/ctl_component_combo.c"
	"${GMP_PRO_LOCATION}/ctl/component/intrinsic/src/ctl_component_discrete.c"
	"${GMP_PRO_LOCATION}/ctl/component/intrinsic/src/ctl_component_interface.c"
	"${GMP_PRO_LOCATION}/ctl/component/intrinsic/src/ctl_component_protection.c"
)
