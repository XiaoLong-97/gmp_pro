#ifndef PSU_PROTECTION_H
#define PSU_PROTECTION_H

#define PSU_PROTECTION_MODE_CV              0U
#define PSU_PROTECTION_MODE_CC              1U
#define PSU_PROTECTION_NONE                 0U
#define PSU_PROTECTION_OVERCURRENT          1U
#define PSU_PROTECTION_OVERVOLTAGE          2U
#define PSU_OVERCURRENT_TRIP_MA             101U
#define PSU_OVERVOLTAGE_TRIP_MV             10100U

#define PSU_PROTECTION_REASON(mode, measured_mv, measured_ma)                     \
    (((mode) == PSU_PROTECTION_MODE_CV)                                           \
         ? (((measured_ma) >= PSU_OVERCURRENT_TRIP_MA)                            \
                ? PSU_PROTECTION_OVERCURRENT : PSU_PROTECTION_NONE)               \
         : (((measured_mv) >= PSU_OVERVOLTAGE_TRIP_MV)                            \
                ? PSU_PROTECTION_OVERVOLTAGE : PSU_PROTECTION_NONE))

#endif /* PSU_PROTECTION_H */
