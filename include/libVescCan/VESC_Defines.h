#ifndef VESC_Defines_h_
#define VESC_Defines_h_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define VESC_CAN_DLEN_MAX 8

#define VESC_CAN_EXTID_FLAG 0x8000

#if defined(__GNUC__) && !defined(LIBVESCCAN_DISABLEPACK)
#define _VESC_GCC_ATTRIBUTE_PACKED __attribute__((packed))
#else
#define _VESC_GCC_ATTRIBUTE_PACKED
#endif //defined(__GNUC__) && !defined(LIBVESCCAN_DISABLEPACK)

#define VESC_ZeroMemory(dst,len) memset(dst, 0, len)

#endif //VESC_Defines_h_
