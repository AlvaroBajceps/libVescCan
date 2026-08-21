#ifndef VESC_Mux_Config_1_Consts_h_
#define VESC_Mux_Config_1_Consts_h_

#include <stdint.h>

typedef enum VESC_Mux_Config_1_Mode_enum
{
	VESC_MUX_CONFIG_1_MODE_ALL_OFF = 0,
	VESC_MUX_CONFIG_1_MODE_SELECTED = 1,
	VESC_MUX_CONFIG_1_MODE_NEIGHBOURS = 2,
	VESC_MUX_CONFIG_1_MODE_ALL_ON = 3,
} VESC_Mux_Config_1_Mode;

typedef enum VESC_Mux_Config_1_Power_enum
{
	VESC_MUX_CONFIG_1_POWER_25_MILIW = 0,
	VESC_MUX_CONFIG_1_POWER_200_MILIW = 1,
	VESC_MUX_CONFIG_1_POWER_400_MILIW = 2,
	VESC_MUX_CONFIG_1_POWER_800_MILIW = 3,
} VESC_Mux_Config_1_Power;

typedef enum VESC_Mux_Config_1_Band_enum
{
	VESC_MUX_CONFIG_1_BAND_A = 0,
	VESC_MUX_CONFIG_1_BAND_B = 1,
	VESC_MUX_CONFIG_1_BAND_F = 2,
	VESC_MUX_CONFIG_1_BAND_R = 3,
} VESC_Mux_Config_1_Band;


#endif //VESC_Mux_Config_1_Consts_h_