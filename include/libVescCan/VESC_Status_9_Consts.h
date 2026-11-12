#ifndef VESC_Status_9_Consts_h_
#define VESC_Status_9_Consts_h_

/* B6: packed battery flags, independent of the gauge's register layout. */
#define VESC_STATUS_9_BATTERY_MASK_FD            (1U << 0)
#define VESC_STATUS_9_BATTERY_MASK_FC            (1U << 1)
#define VESC_STATUS_9_BATTERY_MASK_DSG           (1U << 2)
#define VESC_STATUS_9_BATTERY_MASK_LOW_REMAINING (1U << 3)
#define VESC_STATUS_9_BATTERY_MASK_TCA           (1U << 4)
#define VESC_STATUS_9_BATTERY_MASK_TDA           (1U << 5)
#define VESC_STATUS_9_BATTERY_MASK_OTA           (1U << 6)
#define VESC_STATUS_9_BATTERY_MASK_OCA           (1U << 7)

/* B7: grouped safety flags and permanent-failure mode. */
#define VESC_STATUS_9_SAFETY_MASK_UNDERVOLTAGE          (1U << 0)
#define VESC_STATUS_9_SAFETY_MASK_OVERVOLTAGE           (1U << 1)
#define VESC_STATUS_9_SAFETY_MASK_DISCHARGE_OVERCURRENT (1U << 2)
#define VESC_STATUS_9_SAFETY_MASK_CHARGE_OVERCURRENT    (1U << 3)
#define VESC_STATUS_9_SAFETY_MASK_SHORT_CIRCUIT         (1U << 4)
#define VESC_STATUS_9_SAFETY_MASK_TEMPERATURE           (1U << 5)
#define VESC_STATUS_9_SAFETY_MASK_CHARGING_PROCESS      (1U << 6)
#define VESC_STATUS_9_SAFETY_MASK_PERMANENT_FAILURE     (1U << 7)

#define VESC_STATUS_9_MINUTES_AT_LEAST_254 254U
#define VESC_STATUS_9_MINUTES_UNAVAILABLE  255U

#endif //VESC_Status_9_Consts_h_
