#ifndef VESC_Mux_Consts_h_
#define VESC_Mux_Consts_h_

/* Analog MUX SET_CONFIG B0; also MUX_STATUS B0. Masks are wire-positioned. */
#define VESC_MUX_SETTINGS_STATE_MASK    0x01U
#define VESC_MUX_SETTINGS_MODE_MASK     0x06U
#define VESC_MUX_SETTINGS_MODE_SHIFT    1U
#define VESC_MUX_SETTINGS_RESERVED_MASK 0xF8U

/* Analog MUX SET_CONFIG B1; also MUX_STATUS B1. */
#define VESC_MUX_VTX_POWER_MASK     0x03U
#define VESC_MUX_VTX_BAND_MASK      0x0CU
#define VESC_MUX_VTX_BAND_SHIFT     2U
#define VESC_MUX_VTX_CHANNEL_MASK   0x70U
#define VESC_MUX_VTX_CHANNEL_SHIFT  4U
#define VESC_MUX_VTX_RESERVED_MASK  0x80U

typedef enum VESC_Mux_Mode_enum
{
    VESC_MUX_MODE_ALL_OFF = 0,
    VESC_MUX_MODE_SELECTED = 1,
    VESC_MUX_MODE_NEIGHBOURS = 2,
    VESC_MUX_MODE_ALL_ON = 3
} VESC_Mux_Mode;

typedef enum VESC_Mux_Power_enum
{
    VESC_MUX_POWER_25_MILIW = 0,
    VESC_MUX_POWER_200_MILIW = 1,
    VESC_MUX_POWER_400_MILIW = 2,
    VESC_MUX_POWER_800_MILIW = 3
} VESC_Mux_Power;

typedef enum VESC_Mux_Band_enum
{
    VESC_MUX_BAND_A = 0,
    VESC_MUX_BAND_B = 1,
    VESC_MUX_BAND_F = 2,
    VESC_MUX_BAND_R = 3
} VESC_Mux_Band;

#endif /* VESC_Mux_Consts_h_ */
