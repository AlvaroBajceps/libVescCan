#ifndef VESC_Heartbeat_Consts_h_
#define VESC_Heartbeat_Consts_h_

#define VESC_HEARTBEAT_HEADER_BYTE 0U
#define VESC_HEARTBEAT_DEVICE_BYTE 1U

/* All five flags are independent. */
#define VESC_HEARTBEAT_FLAG_OK      (1U << 0)
#define VESC_HEARTBEAT_FLAG_WARN    (1U << 1)
#define VESC_HEARTBEAT_FLAG_ERR     (1U << 2)
#define VESC_HEARTBEAT_FLAG_SPI_ERR (1U << 3)
#define VESC_HEARTBEAT_FLAG_I2C_ERR (1U << 4)
#define VESC_HEARTBEAT_FLAGS_MASK   0x1FU

/* Latest reset cause, recorded by firmware; codes 5..7 are reserved. */
#define VESC_HEARTBEAT_RESET_REASON_MASK  0xE0U
#define VESC_HEARTBEAT_RESET_REASON_SHIFT 5U
#define VESC_HEARTBEAT_RESET_NO_RESET 0U
#define VESC_HEARTBEAT_RESET_WATCHDOG 1U
#define VESC_HEARTBEAT_RESET_BROWNOUT 2U
#define VESC_HEARTBEAT_RESET_SOFTWARE 3U
#define VESC_HEARTBEAT_RESET_NRST_PIN 4U

#endif /* VESC_Heartbeat_Consts_h_ */
