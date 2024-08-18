#include <libVescCan/VESC_Endian.h>

int16_t _VESC_b16_swap(int16_t val)
{
	int16_t ret = 0;
	ret |= (val & 0x00FF) << 8;
	ret |= (val & 0xFF00) >> 8;
	return ret;
}

int32_t _VESC_b32_swap(int32_t val)
{
	int32_t ret = 0;
	ret |= (val & 0x000000FF) << 24;
	ret |= (val & 0x0000FF00) << 8;
	ret |= (val & 0x00FF0000) >> 8;
	ret |= (val & 0xFF000000) >> 24;
	return ret;
}

int64_t _VESC_b64_swap(int64_t val)
{
	int64_t ret = 0;
	ret |= (val & 0x00000000000000FF) << 56;
	ret |= (val & 0x000000000000FF00) << 40;
	ret |= (val & 0x0000000000FF0000) << 24;
	ret |= (val & 0x00000000FF000000) << 8;
	ret |= (val & 0x000000FF00000000) >> 8;
	ret |= (val & 0x0000FF0000000000) >> 24;
	ret |= (val & 0x00FF000000000000) >> 40;
	ret |= (val & 0xFF00000000000000) >> 56;
	return ret;
}