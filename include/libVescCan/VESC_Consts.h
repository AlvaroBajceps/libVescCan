#ifndef VESC_Consts_h_
#define VESC_Consts_h_

#include <libVescCan/VESC_Defines.h>

//****
// typedefs
// for raw can frame layout not structs!
//****

typedef uint8_t VESC_Id_t;
typedef uint8_t VESC_Command_t;

typedef uint32_t VESC_Command_commandData_t;
typedef uint8_t VESC_Command_commandDataExB;
typedef uint32_t VESC_Command_commandDataExF_0;
typedef uint16_t VESC_Command_commandDataExF_1;
typedef uint16_t VESC_Command_commandDataExF_2;

typedef int32_t VESC_Status_1_erpm_t;
typedef int16_t VESC_Status_1_current_t;
typedef int16_t VESC_Status_1_dutyCycle_t;

typedef int32_t VESC_Status_2_ampHours_t;
typedef int32_t VESC_Status_2_ampHoursChg_t;

typedef int32_t VESC_Status_3_wattHours_t;
typedef int32_t VESC_Status_3_wattHoursChg_t;

typedef int16_t VESC_Status_4_tempFet_t;
typedef int16_t VESC_Status_4_tempMotor_t;
typedef int16_t VESC_Status_4_currentIn_t;
typedef int16_t VESC_Status_4_pidPos_t;

typedef int32_t VESC_Status_5_tachometer_t;
typedef int16_t VESC_Status_5_voltsIn_t;

typedef int16_t VESC_Status_6_adc1_t;
typedef int16_t VESC_Status_6_adc2_t;
typedef int16_t VESC_Status_6_adc3_t;
typedef int16_t VESC_Status_6_ppm_t;

typedef int64_t VESC_Status_7_precisePos_t;

typedef int16_t VESC_Status_8_weightA_t;
typedef int16_t VESC_Status_8_weightB_t;
typedef int16_t VESC_Status_8_weightC_t;
typedef int8_t VESC_Status_8_ph_t;
typedef int8_t VESC_Status_8_distance_t;


typedef int16_t VESC_Status_9_voltage_t;
typedef int16_t VESC_Status_9_current_t;
typedef int8_t VESC_Status_9_temperature_t;
typedef uint8_t VESC_Status_9_charge_t;
typedef uint8_t VESC_Status_9_batteryStatus_t;
typedef uint8_t VESC_Status_9_hotswapStatus_t;

typedef int8_t VESC_Status_10_flags_t;
typedef int8_t VESC_Status_10_communicationState_t;
typedef int8_t VESC_Status_10_controlMode_t;

typedef int16_t VESC_Status_11_position_t;
typedef int16_t VESC_Status_11_speed_t;
typedef int16_t VESC_Status_11_current_t;
typedef int8_t VESC_Status_11_motorTemp_t;
typedef int8_t VESC_Status_11_errorCode_t;


//****
// dlen
//****

#define VESC_CAN_STATUS_1_DLEN 8
#define VESC_CAN_STATUS_2_DLEN 8
#define VESC_CAN_STATUS_3_DLEN 8
#define VESC_CAN_STATUS_4_DLEN 8
#define VESC_CAN_STATUS_5_DLEN 6 // hello there
#define VESC_CAN_STATUS_6_DLEN 8
#define VESC_CAN_STATUS_7_DLEN 8
#define VESC_CAN_STATUS_8_DLEN 8
#define VESC_CAN_STATUS_9_DLEN 8
#define VESC_CAN_STATUS_10_DLEN 3
#define VESC_CAN_STATUS_11_DLEN 8


//****
// enums
//****

typedef enum VESC_Command_enum
{
    // Direction ROS --> CAN

    VESC_COMMAND_SET_DUTY = 0,                   // arg unit [% / 100]
    VESC_COMMAND_SET_CURRENT = 1,                // arg unit [A]
    VESC_COMMAND_SET_CURRENT_BRAKE = 2,          // arg unit [A]
    VESC_COMMAND_SET_RPM = 3,                    // arg unit [RPM]
    VESC_COMMAND_SET_POS = 4,                    // arg unit [Deg]
    VESC_COMMAND_SET_ORIGIN = 5,                 // see VESC_SetOrigin_Command_Enum; use commandDataExB
	VESC_COMMAND_SET_POS_SPEED_LOOP = 6,		 // use commandDataEx_0,1,2
    VESC_COMMAND_SET_CURRENT_REL = 10,           // arg unit [% / 100]
    VESC_COMMAND_SET_CURRENT_BRAKE_REL = 11,     // arg unit [% / 100]
    VESC_COMMAND_SET_CURRENT_HANDBRAKE = 12,     // arg unit [A]
    VESC_COMMAND_SET_CURRENT_HANDBRAKE_REL = 13, // arg unit [% / 100]

    // Direction ROS <-- CAN

    VESC_COMMAND_STATUS_1 = 9,
    VESC_COMMAND_STATUS_2 = 14,
    VESC_COMMAND_STATUS_3 = 15,
    VESC_COMMAND_STATUS_4 = 16,
    VESC_COMMAND_STATUS_5 = 27,
    VESC_COMMAND_STATUS_6 = 28,
	// non standard
    VESC_COMMAND_STATUS_7 = 29,
    VESC_COMMAND_STATUS_8 = 30,
    VESC_COMMAND_STATUS_9 = 31,
	VESC_COMMAND_STATUS_10 = 32,
	// cubemars
	VESC_COMMAND_STATUS_11 = 41,
} VESC_Command;

typedef enum VESC_SetOrigin_Command_Enum
{
	VESC_SETORIGIN_COMMAND_TEMP = 0,
	VESC_SETORIGIN_COMMAND_PERMANENT = 1,
} VESC_SetOrigin_Command;


//****
// VESC scales
//****

#define VESC_SCALE_NA 1

#define VESC_SCALE_SET_DUTY 100000
#define VESC_SCALE_SET_CURRENT 1000
#define VESC_SCALE_SET_CURRENT_BRAKE 1000
#define VESC_SCALE_SET_RPM 1
#define VESC_SCALE_SET_POS 1000000
#define VESC_SCALE_SET_POS_SPEED_LOOP_POSITION 10000
#define VESC_SCALE_SET_POS_SPEED_LOOP_SPEED 0.1
#define VESC_SCALE_SET_POS_SPEED_LOOP_ACCELERATION 0.1
#define VESC_SCALE_SET_CURRENT_REL 100000
#define VESC_SCALE_SET_CURRENT_BRAKE_REL 100000
#define VESC_SCALE_SET_CURRENT_HANDBRAKE 1000
#define VESC_SCALE_SET_CURRENT_HANDBRAKE_REL 100000

#define VESC_SCALE_STATUS_1_ERPM 1
#define VESC_SCALE_STATUS_1_CURRENT 10
#define VESC_SCALE_STATUS_1_DUTYCYCLE 1000

#define VESC_SCALE_STATUS_2_AMPHOURS 10000
#define VESC_SCALE_STATUS_2_AMPHOURSCHG 10000

#define VESC_SCALE_STATUS_3_WATTHOURS 10000
#define VESC_SCALE_STATUS_3_WATTHOURSCHG 10000

#define VESC_SCALE_STATUS_4_TEMPFET 10
#define VESC_SCALE_STATUS_4_TEMPMOTOR 10
#define VESC_SCALE_STATUS_4_CURRENTIN 10
#define VESC_SCALE_STATUS_4_PIDPOS 50

#define VESC_SCALE_STATUS_5_TACHOMETER 6
#define VESC_SCALE_STATUS_5_VOLTSIN 10

#define VESC_SCALE_STATUS_6_ADC1 1000
#define VESC_SCALE_STATUS_6_ADC2 1000
#define VESC_SCALE_STATUS_6_ADC3 1000
#define VESC_SCALE_STATUS_6_PPM 1000

#define VESC_SCALE_STATUS_7_PRECISEPOS 1000000

#define VESC_SCALE_STATUS_8_WEIGHT_A 10
#define VESC_SCALE_STATUS_8_WEIGHT_B 10
#define VESC_SCALE_STATUS_8_WEIGHT_C 10
#define VESC_SCALE_STATUS_8_PH 10
#define VESC_SCALE_STATUS_8_DISTANCE 1


#define VESC_SCALE_STATUS_9_VOLTAGE 1000
#define VESC_SCALE_STATUS_9_CURRENT 1000
#define VESC_SCALE_STATUS_9_TEMPERATURE 1
#define VESC_SCALE_STATUS_9_CHARGE 1
#define VESC_SCALE_STATUS_9_BATTERY_STATUS VESC_SCALE_NA
#define VESC_SCALE_STATUS_9_HOTSWAP_STATUS VESC_SCALE_NA

#define VESC_SCALE_STATUS_10_FLAGS VESC_SCALE_NA
#define VESC_SCALE_STATUS_10_COMMUNICATIONSTATE VESC_SCALE_NA
#define VESC_SCALE_STATUS_10_CONTROLMODE VESC_SCALE_NA

#define VESC_SCALE_STATUS_11_POSITION 10
#define VESC_SCALE_STATUS_11_SPEED 0.1
#define VESC_SCALE_STATUS_11_CURRENT 100
#define VESC_SCALE_STATUS_11_MOTORTEMP 1
#define VESC_SCALE_STATUS_11_ERRORCODE VESC_SCALE_NA

//****
// enum for offsets
//****

enum _VESC_offsetIdx_PosSpeedLoop_enum
{
    _VESC_OFFSETIDX_STATUS_1_ERPM = 0,
    _VESC_OFFSETIDX_STATUS_1_CURRENT,
    _VESC_OFFSETIDX_STATUS_1_DUTYCYCLE
};

enum _VESC_offsetIdx_Status_1_enum
{
    _VESC_OFFSETIDX_POS_SPEED_LOOP_POSITION = 0,
    _VESC_OFFSETIDX_POS_SPEED_LOOP_SPEED,
    _VESC_OFFSETIDX_POS_SPEED_LOOP_ACCELERATION
};

enum _VESC_offsetIdx_Status_2_enum
{
    _VESC_OFFSETIDX_STATUS_2_AMPHOURS = 0,
    _VESC_OFFSETIDX_STATUS_2_AMPHOURSCHG
};

enum _VESC_offsetIdx_Status_3_enum
{
    _VESC_OFFSETIDX_STATUS_3_WATTHOURS = 0,
    _VESC_OFFSETIDX_STATUS_3_WATTHOURSCHG
};

enum _VESC_offsetIdx_Status_4_enum
{
    _VESC_OFFSETIDX_STATUS_4_TEMPFET = 0,
    _VESC_OFFSETIDX_STATUS_4_TEMPMOTOR,
    _VESC_OFFSETIDX_STATUS_4_CURRENTIN,
    _VESC_OFFSETIDX_STATUS_4_PIDPOS
};

enum _VESC_offsetIdx_Status_5_enum
{
    _VESC_OFFSETIDX_STATUS_5_TACHOMETER = 0,
    _VESC_OFFSETIDX_STATUS_5_VOLTSIN
};

enum _VESC_offsetIdx_Status_6_enum
{
    _VESC_OFFSETIDX_STATUS_6_ADC1 = 0,
    _VESC_OFFSETIDX_STATUS_6_ADC2,
    _VESC_OFFSETIDX_STATUS_6_ADC3,
    _VESC_OFFSETIDX_STATUS_6_PPM
};

enum _VESC_offsetIdx_Status_7_enum
{
    _VESC_OFFSETIDX_STATUS_7_PRECISEPOS = 0
};

enum _VESC_offsetIdx_Status_8_enum
{
	_VESC_OFFSETIDX_STATUS_8_WEIGHT_A = 0,
	_VESC_OFFSETIDX_STATUS_8_WEIGHT_B,
	_VESC_OFFSETIDX_STATUS_8_WEIGHT_C,
	_VESC_OFFSETIDX_STATUS_8_PH,
	_VESC_OFFSETIDX_STATUS_8_DISTANCE
};

enum _VESC_offsetIdx_Status_9_enum
{
	_VESC_OFFSETIDX_STATUS_9_VOLTAGE = 0,
	_VESC_OFFSETIDX_STATUS_9_CURRENT,
	_VESC_OFFSETIDX_STATUS_9_TEMPERATURE,
	_VESC_OFFSETIDX_STATUS_9_CHARGE,
	_VESC_OFFSETIDX_STATUS_9_BATTERY_STATUS,
	_VESC_OFFSETIDX_STATUS_9_HOTSWAP_STATUS
};

enum _VESC_offsetIdx_Status_10_enum
{
	_VESC_OFFSETIDX_STATUS_10_FLAGS = 0,
	_VESC_OFFSETIDX_STATUS_10_COMMUNICATIONSTATE,
	_VESC_OFFSETIDX_STATUS_10_CONTROLMODE
};

enum _VESC_offsetIdx_Status_11_enum
{
    _VESC_OFFSETIDX_STATUS_11_POSITION = 0,
    _VESC_OFFSETIDX_STATUS_11_SPEED,
    _VESC_OFFSETIDX_STATUS_11_CURRENT,
    _VESC_OFFSETIDX_STATUS_11_MOTORTEMP,
    _VESC_OFFSETIDX_STATUS_11_ERRORCODE,
};


//****
// offsets for conversions to RawFrame
//****

#define _VESC_OFFSET_COMMANDFRAME 0

static const int _VESC_offset_PosSpeedLoop[] =
{
    0,
    sizeof(VESC_Command_commandDataExF_0),
    sizeof(VESC_Command_commandDataExF_0) + sizeof(VESC_Command_commandDataExF_1)
};

static const int _VESC_offset_Status_1[] =
{
    0,
    sizeof(VESC_Status_1_erpm_t),
    sizeof(VESC_Status_1_erpm_t) + sizeof(VESC_Status_1_current_t)
};

static const int _VESC_offset_Status_2[] =
{
    0,
    sizeof(VESC_Status_2_ampHours_t),
};

static const int _VESC_offset_Status_3[] =
{
    0,
    sizeof(VESC_Status_3_wattHours_t),
};

static const int _VESC_offset_Status_4[] =
{
    0,
    sizeof(VESC_Status_4_tempFet_t),
    sizeof(VESC_Status_4_tempFet_t) + sizeof(VESC_Status_4_tempMotor_t),
    sizeof(VESC_Status_4_tempFet_t) + sizeof(VESC_Status_4_tempMotor_t) + sizeof(VESC_Status_4_currentIn_t)
};

static const int _VESC_offset_Status_5[] =
{
    0,
    sizeof(VESC_Status_5_tachometer_t),
};

static const int _VESC_offset_Status_6[] =
{
    0,
    sizeof(VESC_Status_6_adc1_t),
    sizeof(VESC_Status_6_adc1_t) + sizeof(VESC_Status_6_adc2_t),
    sizeof(VESC_Status_6_adc1_t) + sizeof(VESC_Status_6_adc2_t) + sizeof(VESC_Status_6_adc3_t)
};

static const int _VESC_offset_Status_7[] =
{
    0
};

static const int _VESC_offset_Status_8[] =
{
    0,
	sizeof(VESC_Status_8_weightA_t),
	sizeof(VESC_Status_8_weightA_t) + sizeof(VESC_Status_8_weightB_t),
	sizeof(VESC_Status_8_weightA_t) + sizeof(VESC_Status_8_weightB_t) + sizeof(VESC_Status_8_weightC_t),
	sizeof(VESC_Status_8_weightA_t) + sizeof(VESC_Status_8_weightB_t) + sizeof(VESC_Status_8_weightC_t) + sizeof(VESC_Status_8_ph_t),
};

static const int _VESC_offset_Status_9[] =
{
    0,
	sizeof(VESC_Status_9_voltage_t),
	sizeof(VESC_Status_9_voltage_t) + sizeof(VESC_Status_9_current_t),
	sizeof(VESC_Status_9_voltage_t) + sizeof(VESC_Status_9_current_t) + sizeof(VESC_Status_9_temperature_t),
	sizeof(VESC_Status_9_voltage_t) + sizeof(VESC_Status_9_current_t) + sizeof(VESC_Status_9_temperature_t) + sizeof(VESC_Status_9_charge_t),
	sizeof(VESC_Status_9_voltage_t) + sizeof(VESC_Status_9_current_t) + sizeof(VESC_Status_9_temperature_t) + sizeof(VESC_Status_9_charge_t) + sizeof(VESC_Status_9_batteryStatus_t)
};

static const int _VESC_offset_Status_10[] =
{
    0,
	sizeof(VESC_Status_10_flags_t),
	sizeof(VESC_Status_10_flags_t) + sizeof(VESC_Status_10_communicationState_t)
};

static const int _VESC_offset_Status_11[] =
{
    0,
	sizeof(VESC_Status_11_position_t),
	sizeof(VESC_Status_11_position_t) + sizeof(VESC_Status_11_speed_t),
	sizeof(VESC_Status_11_position_t) + sizeof(VESC_Status_11_speed_t) + sizeof(VESC_Status_11_current_t),
	sizeof(VESC_Status_11_position_t) + sizeof(VESC_Status_11_speed_t) + sizeof(VESC_Status_11_current_t) + sizeof(VESC_Status_11_motorTemp_t),
};

#endif // VESC_Consts_h_
