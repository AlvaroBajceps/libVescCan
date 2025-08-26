#ifndef VESC_Structs_h_
#define VESC_Structs_h_

#include <libVescCan/VESC_Defines.h>
#include <libVescCan/VESC_Consts.h>
#include <libVescCan/VESC_Status_10_Consts.h>
#include <libVescCan/VESC_Status_11_Consts.h>

//****
// structs
//****


/// <summary>
/// Basicly CAN Frame.
/// Literally can be reinterpreted as CAN Frame.
/// </summary>
typedef struct _VESC_RawFrame
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    VESC_Id_t vescID;
    VESC_Command_t command;
    uint16_t _reserved;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint16_t _reserved;
    VESC_Command_t command;
    VESC_Id_t vescID;
#else
#error "Unsupported endiannes"
#endif
    uint8_t can_dlc;
    uint8_t _pad0;
    uint8_t _res0;
    uint8_t _res1;

    uint8_t rawData[VESC_CAN_DLEN_MAX];
} _VESC_GCC_ATTRIBUTE_PACKED VESC_RawFrame;

/// <summary>
/// Frame for commanding.
/// For commands 0-4 and 10-13 use `commandData`.
/// For command 5 use `commandDataExB`.
/// For command 6 use `commandDataEx_0`, `commandDataEx_1` and `commandDataEx_2`.
/// Convert to VESC_RawFrame before sending!
/// </summary>
typedef struct _VESC_CommandFrame
{
    VESC_Id_t vescID;
    VESC_Command_t command;
    union {
        //For commands 0-4 and 10-13
        float commandData;

		//For command 5
		uint8_t commandDataExB;

        //For command 6
        struct {
			//For command 6 position
            float commandDataEx_0;
			//For command 6 speed
            float commandDataEx_1;
            //For command 6 acceleration
			float commandDataEx_2;
        };

		uint8_t _commandDataRaw[12];
	};
} VESC_CommandFrame;


/// <summary>
/// Status 1 frame
/// Convert to VESC_RawFrame before sending!
/// </summary>
typedef struct _VESC_Status_1
{
    VESC_Id_t vescID;
    float erpm;
    float current;
    float dutyCycle;
} VESC_Status_1;

/// <summary>
/// Status 2 frame
/// Convert to VESC_RawFrame before sending!
/// </summary>
typedef struct _VESC_Status_2
{
    VESC_Id_t vescID;
    float apmHours;
    float apmHoursChg;
} VESC_Status_2;

/// <summary>
/// Status 3 frame
/// Convert to VESC_RawFrame before sending!
/// </summary>
typedef struct _VESC_Status_3
{
    VESC_Id_t vescID;
    float wattHours;
    float wattHoursChg;
} VESC_Status_3;

/// <summary>
/// Status 4 frame
/// Convert to VESC_RawFrame before sending!
/// </summary>
typedef struct _VESC_Status_4
{
    VESC_Id_t vescID;
    float tempFet;
    float tempMotor;
    float currentIn;
    float pidPos;
} VESC_Status_4;

/// <summary>
/// Status 5 frame
/// Convert to VESC_RawFrame before sending!
/// </summary>
typedef struct _VESC_Status_5
{
    VESC_Id_t vescID;
    float tachometer;
    float voltsIn;
} VESC_Status_5;

/// <summary>
/// Status 6 frame
/// Convert to VESC_RawFrame before sending!
/// </summary>
typedef struct _VESC_Status_6
{
    VESC_Id_t vescID;
    float adc1;
    float adc2;
    float adc3;
    float ppm;
} VESC_Status_6;

/// <summary>
/// Status 7 frame (note: not standard frame)
/// Convert to VESC_RawFrame before sending!
/// </summary>
typedef struct _VESC_Status_7
{
    VESC_Id_t vescID;
    float precisePos;
} VESC_Status_7;

/// <summary>
/// Status 8 frame (note: not standard frame)
/// Convert to VESC_RawFrame before sending!
/// </summary>
typedef struct _VESC_Status_8
{
    VESC_Id_t vescID;
    float weightA;
    float weightB;
    float weightC;
    float ph;
    float distance;
} VESC_Status_8;

/// <summary>
/// Status 9 frame (note: not standard frame)
/// Convert to VESC_RawFrame before sending!
/// </summary>
typedef struct _VESC_Status_9
{
    VESC_Id_t vescID;
    float voltage;
    float current;
    float temperature;
	float charge;
	uint8_t batteryStatus;
	uint8_t hotswapStatus;
} VESC_Status_9;

/// <summary>
/// Status 10 frame (note: not standard frame)
/// See VESC_Status_10_Consts.h for enum values.
/// Convert to VESC_RawFrame before sending!
/// </summary>
typedef struct _VESC_Status_10
{
    VESC_Id_t vescID;
    VESC_Status_10_flags_t flags;
    VESC_Status_10_CommunicationState communicationState;
	VESC_Status_10_ControlMode controlMode;
} VESC_Status_10;

/// <summary>
/// Status 11 frame (note: cubemars frame)
/// Convert to VESC_RawFrame before sending!
/// </summary>
typedef struct _VESC_Status_11
{
    VESC_Id_t vescID;
    float position;
    float speed;
    float current;
    float motorTemp;
    VESC_Status_11_ErrorCode errorCode;

} VESC_Status_11;

#endif //VESC_Structs_h_
