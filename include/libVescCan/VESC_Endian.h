#ifndef VESC_Endian_h_
#define VESC_Endian_h_

#include <libVescCan/VESC_Defines.h>

int16_t _VESC_b16_swap(int16_t val);
int32_t _VESC_b32_swap(int32_t val);
int64_t _VESC_b64_swap(int64_t val);

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

#define VESC_htobe16(x) _VESC_b16_swap(x)
#define VESC_htobe32(x) _VESC_b32_swap(x)
#define VESC_htobe64(x) _VESC_b64_swap(x)
#define VESC_be16toh(x) _VESC_b16_swap(x)
#define VESC_be32toh(x) _VESC_b32_swap(x)
#define VESC_be64toh(x) _VESC_b64_swap(x)

#define VESC_htole16(x) (x)
#define VESC_htole32(x) (x)
#define VESC_htole64(x) (x)
#define VESC_le16toh(x) (x)
#define VESC_le32toh(x) (x)
#define VESC_le64toh(x) (x)

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

#define VESC_htobe16(x) (x)
#define VESC_htobe32(x) (x)
#define VESC_htobe64(x) (x)
#define VESC_be16toh(x) (x)
#define VESC_be32toh(x) (x)
#define VESC_be64toh(x) (x)

#define VESC_htole16(x) _VESC_b16_swap(x)
#define VESC_htole32(x) _VESC_b32_swap(x)
#define VESC_htole64(x) _VESC_b64_swap(x)
#define VESC_le16toh(x) _VESC_b16_swap(x)
#define VESC_le32toh(x) _VESC_b32_swap(x)
#define VESC_le64toh(x) _VESC_b64_swap(x)

#else

#error "Unsupported endianess"

#endif //__BYTE_ORDER__ == ...

#endif //VESC_Endian_h_