#include "../csp/c28x_syscfg/iris_280039c_board/user/psu_protection.h"

#define STATIC_ASSERT(name, condition) typedef char static_assert_##name[(condition) ? 1 : -1]

STATIC_ASSERT(boundaries_are_safe,
              PSU_PROTECTION_REASON(10000U, 100U) == PSU_PROTECTION_NONE);
STATIC_ASSERT(current_101ma_trips,
              PSU_PROTECTION_REASON(10000U, 101U) == PSU_PROTECTION_OVERCURRENT);
STATIC_ASSERT(voltage_10100mv_trips,
              PSU_PROTECTION_REASON(10100U, 100U) == PSU_PROTECTION_OVERVOLTAGE);
STATIC_ASSERT(overcurrent_has_priority,
              PSU_PROTECTION_REASON(10100U, 101U) == PSU_PROTECTION_OVERCURRENT);

int main(void)
{
    return 0;
}
