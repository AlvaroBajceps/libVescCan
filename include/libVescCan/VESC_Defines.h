#ifndef VESC_Defines_h_
#define VESC_Defines_h_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define VESC_CAN_DLEN_MAX 8

#define VESC_CAN_EXTID_FLAG 0x8000

#ifdef __GNUC__
#define _VESC_GCC_ATTRIBUTE_PACKED __attribute__((packed))
#else
#define _VESC_GCC_ATTRIBUTE_PACKED
#endif //__GNUC__

#define VESC_ZeroMemory(dst,len) memset(dst, 0, len)

#endif //VESC_Defines_h_
