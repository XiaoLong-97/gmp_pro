#include "../csp/c28x_syscfg/iris_280039c_board/user/psu_auto_control.h"

#define CHECK(code, condition) do { if (!(condition)) return (code); } while (0)

int main(void)
{
    CHECK(1, psu_auto_next_mode(PSU_AUTO_MODE_CV, 8500U, 50U, 8500U, 50U) == PSU_AUTO_MODE_CV);
    CHECK(2, psu_auto_next_mode(PSU_AUTO_MODE_CV, 8500U, 51U, 8500U, 50U) == PSU_AUTO_MODE_CC);
    CHECK(3, psu_auto_next_mode(PSU_AUTO_MODE_CC, 8399U, 50U, 8500U, 50U) == PSU_AUTO_MODE_CC);
    CHECK(4, psu_auto_next_mode(PSU_AUTO_MODE_CC, 8400U, 50U, 8500U, 50U) == PSU_AUTO_MODE_CV);
    CHECK(5, psu_auto_next_mode(PSU_AUTO_MODE_CV, 8500U, 100U, 8500U, 100U) == PSU_AUTO_MODE_CV);
    CHECK(6, psu_auto_next_mode(PSU_AUTO_MODE_CC, 8400U, 51U, 8500U, 50U) == PSU_AUTO_MODE_CV);
    return 0;
}
