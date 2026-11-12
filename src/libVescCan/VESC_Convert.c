#include "libVescCan/VESC_Consts.h"
#include "libVescCan/VESC_Mux_Consts.h"
#include "libVescCan/VESC_Structs.h"
#include <libVescCan/VESC_Convert.h>
#include <math.h>

bool VESC_convertCmdToRaw(VESC_RawFrame* out, const VESC_CommandFrame* in)
{
	switch (in->command)
	{
	case VESC_COMMAND_SET_DUTY:
		_VESC_WriteRawData32(out, _VESC_OFFSET_COMMANDFRAME, in->commandData, VESC_SCALE_SET_DUTY);
		break;
	case VESC_COMMAND_SET_CURRENT:
		_VESC_WriteRawData32(out, _VESC_OFFSET_COMMANDFRAME, in->commandData, VESC_SCALE_SET_CURRENT);
		break;
	case VESC_COMMAND_SET_CURRENT_BRAKE:
		_VESC_WriteRawData32(out, _VESC_OFFSET_COMMANDFRAME, in->commandData, VESC_SCALE_SET_CURRENT_BRAKE);
		break;
	case VESC_COMMAND_SET_RPM:
		_VESC_WriteRawData32(out, _VESC_OFFSET_COMMANDFRAME, in->commandData, VESC_SCALE_SET_RPM);
		break;
	case VESC_COMMAND_SET_POS:
		_VESC_WriteRawData32(out, _VESC_OFFSET_COMMANDFRAME, in->commandData, VESC_SCALE_SET_POS);
		break;
	case VESC_COMMAND_SET_ORIGIN:
		_VESC_WriteRawData8u(out, _VESC_OFFSET_COMMANDFRAME, in->commandDataExB, VESC_SCALE_NA);
		break;
	case VESC_COMMAND_SET_POS_SPEED_LOOP:
		_VESC_WriteRawData32(out, _VESC_offset_PosSpeedLoop[_VESC_OFFSETIDX_POS_SPEED_LOOP_POSITION], in->commandDataEx_0, VESC_SCALE_SET_POS_SPEED_LOOP_POSITION);
		_VESC_WriteRawData16(out, _VESC_offset_PosSpeedLoop[_VESC_OFFSETIDX_POS_SPEED_LOOP_SPEED], in->commandDataEx_1, VESC_SCALE_SET_POS_SPEED_LOOP_SPEED);
		_VESC_WriteRawData16u(out, _VESC_offset_PosSpeedLoop[_VESC_OFFSETIDX_POS_SPEED_LOOP_ACCELERATION], in->commandDataEx_2, VESC_SCALE_SET_POS_SPEED_LOOP_ACCELERATION);
		break;
	case VESC_COMMAND_SET_CURRENT_REL:
		_VESC_WriteRawData32(out, _VESC_OFFSET_COMMANDFRAME, in->commandData, VESC_SCALE_SET_CURRENT_REL);
		break;
	case VESC_COMMAND_SET_CURRENT_BRAKE_REL:
		_VESC_WriteRawData32(out, _VESC_OFFSET_COMMANDFRAME, in->commandData, VESC_SCALE_SET_CURRENT_BRAKE_REL);
		break;
	case VESC_COMMAND_SET_CURRENT_HANDBRAKE:
		_VESC_WriteRawData32(out, _VESC_OFFSET_COMMANDFRAME, in->commandData, VESC_SCALE_SET_CURRENT_HANDBRAKE);
		break;
	case VESC_COMMAND_SET_CURRENT_HANDBRAKE_REL:
		_VESC_WriteRawData32(out, _VESC_OFFSET_COMMANDFRAME, in->commandData, VESC_SCALE_SET_CURRENT_HANDBRAKE_REL);
		break;
	default:
		return false;
	}
	out->vescID = in->vescID;
	out->command = in->command;
	out->_reserved = VESC_CAN_EXTID_FLAG;

	if(in->command == VESC_COMMAND_SET_ORIGIN)
		out->can_dlc = 1;
	else if(in->command == VESC_COMMAND_SET_POS_SPEED_LOOP)
		out->can_dlc = 8;
	else
		out->can_dlc = 4;

	return true;
}

bool VESC_convertStatus1ToRaw(VESC_RawFrame* out, const VESC_Status_1* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_1;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_1_DLEN;

	_VESC_WriteRawData32(out, _VESC_offset_Status_1[_VESC_OFFSETIDX_STATUS_1_ERPM], in->erpm, VESC_SCALE_STATUS_1_ERPM);
	_VESC_WriteRawData16(out, _VESC_offset_Status_1[_VESC_OFFSETIDX_STATUS_1_CURRENT], in->current, VESC_SCALE_STATUS_1_CURRENT);
	_VESC_WriteRawData16(out, _VESC_offset_Status_1[_VESC_OFFSETIDX_STATUS_1_DUTYCYCLE], in->dutyCycle, VESC_SCALE_STATUS_1_DUTYCYCLE);

	return true;
}

bool VESC_convertStatus2ToRaw(VESC_RawFrame* out, const VESC_Status_2* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_2;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_2_DLEN;

	_VESC_WriteRawData32(out, _VESC_offset_Status_2[_VESC_OFFSETIDX_STATUS_2_AMPHOURS], in->apmHours, VESC_SCALE_STATUS_2_AMPHOURS);
	_VESC_WriteRawData32(out, _VESC_offset_Status_2[_VESC_OFFSETIDX_STATUS_2_AMPHOURSCHG], in->apmHoursChg, VESC_SCALE_STATUS_2_AMPHOURSCHG);

	return true;
}

bool VESC_convertStatus3ToRaw(VESC_RawFrame* out, const VESC_Status_3* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_3;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_3_DLEN;

	_VESC_WriteRawData32(out, _VESC_offset_Status_3[_VESC_OFFSETIDX_STATUS_3_WATTHOURS], in->wattHours, VESC_SCALE_STATUS_3_WATTHOURS);
	_VESC_WriteRawData32(out, _VESC_offset_Status_3[_VESC_OFFSETIDX_STATUS_3_WATTHOURSCHG], in->wattHoursChg, VESC_SCALE_STATUS_3_WATTHOURSCHG);

	return true;
}

bool VESC_convertStatus4ToRaw(VESC_RawFrame* out, const VESC_Status_4* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_4;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_4_DLEN;

	_VESC_WriteRawData16(out, _VESC_offset_Status_4[_VESC_OFFSETIDX_STATUS_4_TEMPFET], in->tempFet, VESC_SCALE_STATUS_4_TEMPFET);
	_VESC_WriteRawData16(out, _VESC_offset_Status_4[_VESC_OFFSETIDX_STATUS_4_TEMPMOTOR], in->tempMotor, VESC_SCALE_STATUS_4_TEMPMOTOR);
	_VESC_WriteRawData16(out, _VESC_offset_Status_4[_VESC_OFFSETIDX_STATUS_4_CURRENTIN], in->currentIn, VESC_SCALE_STATUS_4_CURRENTIN);
	_VESC_WriteRawData16(out, _VESC_offset_Status_4[_VESC_OFFSETIDX_STATUS_4_PIDPOS], in->pidPos, VESC_SCALE_STATUS_4_PIDPOS);

	return true;
}

bool VESC_convertStatus5ToRaw(VESC_RawFrame* out, const VESC_Status_5* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_5;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_5_DLEN;

	_VESC_WriteRawData32(out, _VESC_offset_Status_5[_VESC_OFFSETIDX_STATUS_5_TACHOMETER], in->tachometer, VESC_SCALE_STATUS_5_TACHOMETER);
	_VESC_WriteRawData16(out, _VESC_offset_Status_5[_VESC_OFFSETIDX_STATUS_5_VOLTSIN], in->voltsIn, VESC_SCALE_STATUS_5_VOLTSIN);

	return true;
}

bool VESC_convertStatus6ToRaw(VESC_RawFrame* out, const VESC_Status_6* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_6;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_6_DLEN;

	_VESC_WriteRawData16(out, _VESC_offset_Status_6[_VESC_OFFSETIDX_STATUS_6_ADC1], in->adc1, VESC_SCALE_STATUS_6_ADC1);
	_VESC_WriteRawData16(out, _VESC_offset_Status_6[_VESC_OFFSETIDX_STATUS_6_ADC2], in->adc2, VESC_SCALE_STATUS_6_ADC2);
	_VESC_WriteRawData16(out, _VESC_offset_Status_6[_VESC_OFFSETIDX_STATUS_6_ADC3], in->adc3, VESC_SCALE_STATUS_6_ADC3);
	_VESC_WriteRawData16(out, _VESC_offset_Status_6[_VESC_OFFSETIDX_STATUS_6_PPM], in->ppm, VESC_SCALE_STATUS_6_PPM);

	return true;
}

bool VESC_convertStatus7ToRaw(VESC_RawFrame* out, const VESC_Status_7* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_7;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_7_DLEN;

	_VESC_WriteRawData64(out, _VESC_offset_Status_7[_VESC_OFFSETIDX_STATUS_7_PRECISEPOS], in->precisePos, VESC_SCALE_STATUS_7_PRECISEPOS);

	return true;
}

bool VESC_convertStatus8ToRaw(VESC_RawFrame* out, const VESC_Status_8* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_8;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_8_DLEN;

	_VESC_WriteRawData16(out, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_WEIGHT_A], in->weightA, VESC_SCALE_STATUS_8_WEIGHT_A);
	_VESC_WriteRawData16(out, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_WEIGHT_B], in->weightB, VESC_SCALE_STATUS_8_WEIGHT_B);
	_VESC_WriteRawData16(out, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_WEIGHT_C], in->weightC, VESC_SCALE_STATUS_8_WEIGHT_C);
	_VESC_WriteRawData8u(out, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_PH], in->ph, VESC_SCALE_STATUS_8_PH);
	_VESC_WriteRawData8u(out, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_DISTANCE], in->distance, VESC_SCALE_STATUS_8_DISTANCE);

	return true;
}

bool VESC_convertStatus9ToRaw(VESC_RawFrame* out, const VESC_Status_9* in)
{
	if (out == NULL || in == NULL)
		return false;

	if (!isfinite(in->voltage) || in->voltage < 0.0f || in->voltage > 25.5f ||
		!isfinite(in->current) || in->current < -32.768f || in->current > 32.767f ||
		!isfinite(in->temperature) || in->temperature < -128.0f || in->temperature > 127.0f ||
		!isfinite(in->charge) || in->charge < 0.0f || in->charge > 100.0f)
		return false;

	VESC_RawFrame frame = {0};
	frame.vescID = in->vescID;
	frame.command = VESC_COMMAND_STATUS_9;
	frame._reserved = VESC_CAN_EXTID_FLAG;
	frame.can_dlc = VESC_CAN_STATUS_9_DLEN;

	/* Store explicit bytes to avoid unaligned accesses and signed endian-helper
	 * conversions. Widen before rounding and narrowing signed measurements. */
	const float scaledCurrent = in->current * VESC_SCALE_STATUS_9_CURRENT;
	const int32_t current = (int32_t)(scaledCurrent + (scaledCurrent >= 0.0f ? 0.5f : -0.5f));
	const uint16_t currentBits = (uint16_t)current;
	const int32_t temperature = (int32_t)in->temperature;
	frame.rawData[0] = (uint8_t)(in->voltage * VESC_SCALE_STATUS_9_VOLTAGE + 0.5f);
	frame.rawData[1] = (uint8_t)in->charge;
	frame.rawData[2] = (uint8_t)(currentBits >> 8);
	frame.rawData[3] = (uint8_t)(currentBits & 0xFFU);
	frame.rawData[4] = (uint8_t)temperature;
	frame.rawData[5] = in->minutesToTarget;
	frame.rawData[6] = in->batteryStatus;
	frame.rawData[7] = in->safetyStatus;
	*out = frame;
	return true;
}

bool VESC_convertSetConfigToRaw(VESC_RawFrame* out, const VESC_SetConfig* in)
{
	if (out == NULL || in == NULL)
		return false;

	VESC_RawFrame frame = {0};
	frame.vescID = in->vescID;
	frame.command = VESC_COMMAND_SET_CONFIG;
	frame._reserved = VESC_CAN_EXTID_FLAG;
	frame.can_dlc = VESC_CAN_SET_CONFIG_DLEN;
	memcpy(frame.rawData, in->data, sizeof(in->data));
	*out = frame;
	return true;
}

bool VESC_convertStatus13ToRaw(VESC_RawFrame* out, const VESC_Status_13* in)
{
	if (out == NULL || in == NULL)
		return false;

	VESC_RawFrame frame = {0};
	frame.vescID = in->vescID;
	frame.command = VESC_COMMAND_STATUS_13;
	frame._reserved = VESC_CAN_EXTID_FLAG;
	frame.can_dlc = VESC_CAN_STATUS_13_DLEN;
	memcpy(frame.rawData, in->data, sizeof(in->data));
	*out = frame;
	return true;
}

bool VESC_convertHeartbeatStatusToRaw(VESC_RawFrame* out, const VESC_Heartbeat_Status* in)
{
	if (out == NULL || in == NULL)
		return false;

	VESC_RawFrame frame = {0};
	frame.vescID = in->vescID;
	frame.command = VESC_COMMAND_HEARTBEAT_STATUS;
	frame._reserved = VESC_CAN_EXTID_FLAG;
	frame.can_dlc = VESC_CAN_HEARTBEAT_STATUS_DLEN;
	memcpy(frame.rawData, in->data, sizeof(in->data));
	*out = frame;
	return true;
}

bool VESC_convertStatus10ToRaw(VESC_RawFrame* out, const VESC_Status_10* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_10;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_10_DLEN;

	_VESC_WriteRawData8u(out, _VESC_offset_Status_10[_VESC_OFFSETIDX_STATUS_10_COMMUNICATIONSTATE], in->communicationState, VESC_SCALE_STATUS_10_COMMUNICATIONSTATE);
	_VESC_WriteRawData16u(out, _VESC_offset_Status_10[_VESC_OFFSETIDX_STATUS_10_CONTROLMODE], in->controlMode, VESC_SCALE_STATUS_10_CONTROLMODE);

	return true;
}

bool VESC_convertMuxCamSelToRaw(VESC_RawFrame* out, const VESC_Mux_CamSel* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_MUX_CAMSEL;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_MUX_CAMSEL_DLEN;

	_VESC_WriteRawData8u(out, _VESC_offset_Mux_CamSel[_VESC_OFFSETIDX_MUX_CAMSEL_CAMERA_SELECT], in->cameraSelect, VESC_SCALE_MUX_CAMSEL_CAMERA_SELECT);

	return true;
}

bool VESC_convertMuxStatusToRaw(VESC_RawFrame* out, const VESC_Mux_Status* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_MUX_STATUS;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_MUX_STATUS_DLEN;

	out->rawData[0] = (uint8_t)(((uint32_t)in->settings.state & 0x01U) |
		(((uint32_t)in->settings.mode & 0x03U) << 1) |
		(((uint32_t)in->settings._reserved & 0x1FU) << 3));
	out->rawData[1] = (uint8_t)(((uint32_t)in->vtxConfig.power & 0x03U) |
		(((uint32_t)in->vtxConfig.band & 0x03U) << 2) |
		(((uint32_t)in->vtxConfig.channel & 0x07U) << 4) |
		(((uint32_t)in->vtxConfig._reserved & 0x01U) << 7));
	_VESC_WriteRawData8u(out, _VESC_offset_Mux_Status[_VESC_OFFSETIDX_MUX_STATUS_CAMERA_SELECT], in->cameraSelect, VESC_SCALE_MUX_STATUS_CAMERA_SELECT);
	_VESC_WriteRawData16(out, _VESC_offset_Mux_Status[_VESC_OFFSETIDX_MUX_STATUS_VTX_TEMP], in->vtxTemp, VESC_SCALE_MUX_STATUS_VTX_TEMP);
	_VESC_WriteRawData16(out, _VESC_offset_Mux_Status[_VESC_OFFSETIDX_MUX_STATUS_BOARD_TEMP], in->boardTemp, VESC_SCALE_MUX_STATUS_BOARD_TEMP);

	return true;
}

bool VESC_convertStatus11ToRaw(VESC_RawFrame* out, const VESC_Status_11* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_11;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_11_DLEN;

	_VESC_WriteRawData16(out, _VESC_offset_Status_11[_VESC_OFFSETIDX_STATUS_11_POSITION], in->position, VESC_SCALE_STATUS_11_POSITION);
	_VESC_WriteRawData16(out, _VESC_offset_Status_11[_VESC_OFFSETIDX_STATUS_11_SPEED], in->speed, VESC_SCALE_STATUS_11_SPEED);
	_VESC_WriteRawData16(out, _VESC_offset_Status_11[_VESC_OFFSETIDX_STATUS_11_CURRENT], in->current, VESC_SCALE_STATUS_11_CURRENT);
	_VESC_WriteRawData8(out, _VESC_offset_Status_11[_VESC_OFFSETIDX_STATUS_11_MOTORTEMP], in->motorTemp, VESC_SCALE_STATUS_11_MOTORTEMP);
	_VESC_WriteRawData8u(out, _VESC_offset_Status_11[_VESC_OFFSETIDX_STATUS_11_ERRORCODE], in->errorCode, VESC_SCALE_STATUS_11_ERRORCODE);

	return true;
}

bool VESC_convertStatus12ToRaw(VESC_RawFrame* out, const VESC_Status_12* in)
{
	if (out == NULL || in == NULL)
		return false;

	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_12;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_12_DLEN;

	_VESC_WriteRawData16(out, _VESC_offset_Status_12[_VESC_OFFSETIDX_STATUS_12_W], in->w, VESC_SCALE_STATUS_12_W);
	_VESC_WriteRawData16(out, _VESC_offset_Status_12[_VESC_OFFSETIDX_STATUS_12_X], in->x, VESC_SCALE_STATUS_12_X);
	_VESC_WriteRawData16(out, _VESC_offset_Status_12[_VESC_OFFSETIDX_STATUS_12_Y], in->y, VESC_SCALE_STATUS_12_Y);
	_VESC_WriteRawData16(out, _VESC_offset_Status_12[_VESC_OFFSETIDX_STATUS_12_Z], in->z, VESC_SCALE_STATUS_12_Z);
	return true;
}

bool VESC_convertRawToCmd(VESC_CommandFrame* out, const VESC_RawFrame* in)
{
	switch (in->command)
	{
	case VESC_COMMAND_SET_DUTY:
		_VESC_ReadRawData32(out->commandData, in, _VESC_OFFSET_COMMANDFRAME, VESC_SCALE_SET_DUTY,/*none*/);
		break;
	case VESC_COMMAND_SET_CURRENT:
		_VESC_ReadRawData32(out->commandData, in, _VESC_OFFSET_COMMANDFRAME, VESC_SCALE_SET_CURRENT,/*none*/);
		break;
	case VESC_COMMAND_SET_CURRENT_BRAKE:
		_VESC_ReadRawData32(out->commandData, in, _VESC_OFFSET_COMMANDFRAME, VESC_SCALE_SET_CURRENT_BRAKE,/*none*/);
		break;
	case VESC_COMMAND_SET_RPM:
		_VESC_ReadRawData32(out->commandData, in, _VESC_OFFSET_COMMANDFRAME, VESC_SCALE_SET_RPM,/*none*/);
		break;
	case VESC_COMMAND_SET_POS:
		_VESC_ReadRawData32(out->commandData, in, _VESC_OFFSET_COMMANDFRAME, VESC_SCALE_SET_POS,/*none*/);
		break;
	case VESC_COMMAND_SET_ORIGIN:
		_VESC_ReadRawData8u(out->commandDataExB, in, _VESC_OFFSET_COMMANDFRAME, VESC_SCALE_NA, /*none*/);
		break;
	case VESC_COMMAND_SET_POS_SPEED_LOOP:
		_VESC_ReadRawData32(out->commandDataEx_0, in, _VESC_offset_PosSpeedLoop[_VESC_OFFSETIDX_POS_SPEED_LOOP_POSITION], VESC_SCALE_SET_POS_SPEED_LOOP_POSITION, /*none*/);
		_VESC_ReadRawData16(out->commandDataEx_1, in, _VESC_offset_PosSpeedLoop[_VESC_OFFSETIDX_POS_SPEED_LOOP_SPEED], VESC_SCALE_SET_POS_SPEED_LOOP_SPEED, /*none*/);
		_VESC_ReadRawData16u(out->commandDataEx_2, in, _VESC_offset_PosSpeedLoop[_VESC_OFFSETIDX_POS_SPEED_LOOP_ACCELERATION], VESC_SCALE_SET_POS_SPEED_LOOP_ACCELERATION, /*none*/);
		break;
	case VESC_COMMAND_SET_CURRENT_REL:
		_VESC_ReadRawData32(out->commandData, in, _VESC_OFFSET_COMMANDFRAME, VESC_SCALE_SET_CURRENT_REL,/*none*/);
		break;
	case VESC_COMMAND_SET_CURRENT_BRAKE_REL:
		_VESC_ReadRawData32(out->commandData, in, _VESC_OFFSET_COMMANDFRAME, VESC_SCALE_SET_CURRENT_BRAKE_REL,/*none*/);
		break;
	case VESC_COMMAND_SET_CURRENT_HANDBRAKE:
		_VESC_ReadRawData32(out->commandData, in, _VESC_OFFSET_COMMANDFRAME, VESC_SCALE_SET_CURRENT_HANDBRAKE,/*none*/);
		break;
	case VESC_COMMAND_SET_CURRENT_HANDBRAKE_REL:
		_VESC_ReadRawData32(out->commandData, in, _VESC_OFFSET_COMMANDFRAME, VESC_SCALE_SET_CURRENT_HANDBRAKE_REL,/*none*/);
		break;
	default:
		return false;
	}

	out->vescID = in->vescID;
	out->command = in->command;

	return true;
}

bool VESC_convertRawToStatus1(VESC_Status_1* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_STATUS_1)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData32(out->erpm, in, _VESC_offset_Status_1[_VESC_OFFSETIDX_STATUS_1_ERPM], VESC_SCALE_STATUS_1_ERPM,/*none*/);
	_VESC_ReadRawData16(out->current, in, _VESC_offset_Status_1[_VESC_OFFSETIDX_STATUS_1_CURRENT], VESC_SCALE_STATUS_1_CURRENT,/*none*/);
	_VESC_ReadRawData16(out->dutyCycle, in, _VESC_offset_Status_1[_VESC_OFFSETIDX_STATUS_1_DUTYCYCLE], VESC_SCALE_STATUS_1_DUTYCYCLE,/*none*/);

	return true;
}

bool VESC_convertRawToStatus2(VESC_Status_2* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_STATUS_2)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData32(out->apmHours, in, _VESC_offset_Status_2[_VESC_OFFSETIDX_STATUS_2_AMPHOURS], VESC_SCALE_STATUS_2_AMPHOURS,/*none*/);
	_VESC_ReadRawData32(out->apmHoursChg, in, _VESC_offset_Status_2[_VESC_OFFSETIDX_STATUS_2_AMPHOURSCHG], VESC_SCALE_STATUS_2_AMPHOURSCHG,/*none*/);

	return true;
}

bool VESC_convertRawToStatus3(VESC_Status_3* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_STATUS_3)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData32(out->wattHours, in, _VESC_offset_Status_3[_VESC_OFFSETIDX_STATUS_3_WATTHOURS], VESC_SCALE_STATUS_3_WATTHOURS,/*none*/);
	_VESC_ReadRawData32(out->wattHoursChg, in, _VESC_offset_Status_3[_VESC_OFFSETIDX_STATUS_3_WATTHOURSCHG], VESC_SCALE_STATUS_3_WATTHOURSCHG,/*none*/);

	return true;
}

bool VESC_convertRawToStatus4(VESC_Status_4* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_STATUS_4)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData16(out->tempFet, in, _VESC_offset_Status_4[_VESC_OFFSETIDX_STATUS_4_TEMPFET], VESC_SCALE_STATUS_4_TEMPFET,/*none*/);
	_VESC_ReadRawData16(out->tempMotor, in, _VESC_offset_Status_4[_VESC_OFFSETIDX_STATUS_4_TEMPMOTOR], VESC_SCALE_STATUS_4_TEMPMOTOR,/*none*/);
	_VESC_ReadRawData16(out->currentIn, in, _VESC_offset_Status_4[_VESC_OFFSETIDX_STATUS_4_CURRENTIN], VESC_SCALE_STATUS_4_CURRENTIN,/*none*/);
	_VESC_ReadRawData16(out->pidPos, in, _VESC_offset_Status_4[_VESC_OFFSETIDX_STATUS_4_PIDPOS], VESC_SCALE_STATUS_4_PIDPOS,/*none*/);

	return true;
}

bool VESC_convertRawToStatus5(VESC_Status_5* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_STATUS_5)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData32(out->tachometer, in, _VESC_offset_Status_5[_VESC_OFFSETIDX_STATUS_5_TACHOMETER], VESC_SCALE_STATUS_5_TACHOMETER,/*none*/);
	_VESC_ReadRawData16(out->voltsIn, in, _VESC_offset_Status_5[_VESC_OFFSETIDX_STATUS_5_VOLTSIN], VESC_SCALE_STATUS_5_VOLTSIN,/*none*/);

	return true;
}

bool VESC_convertRawToStatus6(VESC_Status_6* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_STATUS_6)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData16(out->adc1, in, _VESC_offset_Status_6[_VESC_OFFSETIDX_STATUS_6_ADC1], VESC_SCALE_STATUS_6_ADC1,/*none*/);
	_VESC_ReadRawData16(out->adc2, in, _VESC_offset_Status_6[_VESC_OFFSETIDX_STATUS_6_ADC2], VESC_SCALE_STATUS_6_ADC2,/*none*/);
	_VESC_ReadRawData16(out->adc3, in, _VESC_offset_Status_6[_VESC_OFFSETIDX_STATUS_6_ADC3], VESC_SCALE_STATUS_6_ADC3,/*none*/);
	_VESC_ReadRawData16(out->ppm, in, _VESC_offset_Status_6[_VESC_OFFSETIDX_STATUS_6_PPM], VESC_SCALE_STATUS_6_PPM,/*none*/);

	return true;
}

bool VESC_convertRawToStatus7(VESC_Status_7* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_STATUS_7)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData64(out->precisePos, in, _VESC_offset_Status_7[_VESC_OFFSETIDX_STATUS_7_PRECISEPOS], VESC_SCALE_STATUS_7_PRECISEPOS,/*none*/);

	return true;
}

bool VESC_convertRawToStatus8(VESC_Status_8* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_STATUS_8)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData16(out->weightA, in, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_WEIGHT_A], VESC_SCALE_STATUS_8_WEIGHT_A,/*none*/);
	_VESC_ReadRawData16(out->weightB, in, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_WEIGHT_B], VESC_SCALE_STATUS_8_WEIGHT_B,/*none*/);
	_VESC_ReadRawData16(out->weightC, in, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_WEIGHT_C], VESC_SCALE_STATUS_8_WEIGHT_C,/*none*/);
	_VESC_ReadRawData8u(out->ph, in, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_PH], VESC_SCALE_STATUS_8_PH,/*none*/);
	_VESC_ReadRawData8u(out->distance, in, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_DISTANCE], VESC_SCALE_STATUS_8_DISTANCE,/*none*/);

	return true;
}

bool VESC_convertRawToStatus9(VESC_Status_9* out, const VESC_RawFrame* in)
{
	if (out == NULL || in == NULL || in->command != VESC_COMMAND_STATUS_9 ||
		in->can_dlc != VESC_CAN_STATUS_9_DLEN || in->rawData[1] > 100U)
		return false;

	VESC_Status_9 status = {0};
	status.vescID = in->vescID;
	status.voltage = in->rawData[0] / (float)VESC_SCALE_STATUS_9_VOLTAGE;
	status.charge = (float)in->rawData[1];
	const uint16_t currentBits = ((uint16_t)in->rawData[2] << 8) | in->rawData[3];
	const int32_t current = (currentBits & 0x8000U) != 0U ?
		(int32_t)currentBits - 65536 : (int32_t)currentBits;
	const int32_t temperature = (in->rawData[4] & 0x80U) != 0U ?
		(int32_t)in->rawData[4] - 256 : (int32_t)in->rawData[4];
	status.current = current / (float)VESC_SCALE_STATUS_9_CURRENT;
	status.temperature = (float)temperature;
	status.minutesToTarget = in->rawData[5];
	status.batteryStatus = in->rawData[6];
	status.safetyStatus = in->rawData[7];
	*out = status;
	return true;
}

bool VESC_convertRawToSetConfig(VESC_SetConfig* out, const VESC_RawFrame* in)
{
	if (out == NULL || in == NULL || in->command != VESC_COMMAND_SET_CONFIG ||
		in->can_dlc != VESC_CAN_SET_CONFIG_DLEN)
		return false;

	VESC_SetConfig config = {0};
	config.vescID = in->vescID;
	memcpy(config.data, in->rawData, sizeof(config.data));
	*out = config;
	return true;
}

bool VESC_convertRawToStatus13(VESC_Status_13* out, const VESC_RawFrame* in)
{
	if (out == NULL || in == NULL || in->command != VESC_COMMAND_STATUS_13 ||
		in->can_dlc != VESC_CAN_STATUS_13_DLEN)
		return false;

	VESC_Status_13 status = {0};
	status.vescID = in->vescID;
	memcpy(status.data, in->rawData, sizeof(status.data));
	*out = status;
	return true;
}

bool VESC_convertRawToHeartbeatStatus(VESC_Heartbeat_Status* out, const VESC_RawFrame* in)
{
	if (out == NULL || in == NULL || in->command != VESC_COMMAND_HEARTBEAT_STATUS ||
		in->can_dlc != VESC_CAN_HEARTBEAT_STATUS_DLEN)
		return false;

	VESC_Heartbeat_Status heartbeat = {0};
	heartbeat.vescID = in->vescID;
	memcpy(heartbeat.data, in->rawData, sizeof(heartbeat.data));
	*out = heartbeat;
	return true;
}

bool VESC_convertRawToStatus10(VESC_Status_10* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_STATUS_10)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData8u(out->communicationState, in, _VESC_offset_Status_10[_VESC_OFFSETIDX_STATUS_10_COMMUNICATIONSTATE], VESC_SCALE_STATUS_10_COMMUNICATIONSTATE,(VESC_Status_10_CommunicationState));
	_VESC_ReadRawData16u(out->controlMode, in, _VESC_offset_Status_10[_VESC_OFFSETIDX_STATUS_10_CONTROLMODE], VESC_SCALE_STATUS_10_CONTROLMODE,(VESC_Status_10_controlMode_t));

	return true;
}

bool VESC_convertRawToMuxCamSel(VESC_Mux_CamSel* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_MUX_CAMSEL)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData8u(out->cameraSelect, in, _VESC_offset_Mux_CamSel[_VESC_OFFSETIDX_MUX_CAMSEL_CAMERA_SELECT], VESC_SCALE_MUX_CAMSEL_CAMERA_SELECT, (VESC_Mux_CamSel_cameraSelect_t));

	return true;
}

bool VESC_convertRawToMuxStatus(VESC_Mux_Status* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_MUX_STATUS)
		return false;

	out->vescID = in->vescID;

	const uint8_t settings = in->rawData[0];
	const uint8_t vtxConfig = in->rawData[1];
	out->settings.state = (settings & 0x01U) != 0U;
	out->settings.mode = (VESC_Mux_Mode)((settings >> 1) & 0x03U);
	out->settings._reserved = (settings >> 3) & 0x1FU;
	out->vtxConfig.power = (VESC_Mux_Power)(vtxConfig & 0x03U);
	out->vtxConfig.band = (VESC_Mux_Band)((vtxConfig >> 2) & 0x03U);
	out->vtxConfig.channel = (vtxConfig >> 4) & 0x07U;
	out->vtxConfig._reserved = (vtxConfig >> 7) & 0x01U;

	_VESC_ReadRawData8u(out->cameraSelect, in, _VESC_offset_Mux_Status[_VESC_OFFSETIDX_MUX_STATUS_CAMERA_SELECT], VESC_SCALE_MUX_STATUS_CAMERA_SELECT, /*none*/);
	_VESC_ReadRawData16(out->vtxTemp, in, _VESC_offset_Mux_Status[_VESC_OFFSETIDX_MUX_STATUS_VTX_TEMP], VESC_SCALE_MUX_STATUS_VTX_TEMP, /*none*/);
	_VESC_ReadRawData16(out->boardTemp, in, _VESC_offset_Mux_Status[_VESC_OFFSETIDX_MUX_STATUS_BOARD_TEMP], VESC_SCALE_MUX_STATUS_BOARD_TEMP, /*none*/);

	return true;
}

bool VESC_convertRawToStatus11(VESC_Status_11* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_STATUS_11)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData16(out->position, in, _VESC_offset_Status_11[_VESC_OFFSETIDX_STATUS_11_POSITION], VESC_SCALE_STATUS_11_POSITION,/*none*/);
	_VESC_ReadRawData16(out->speed, in, _VESC_offset_Status_11[_VESC_OFFSETIDX_STATUS_11_SPEED], VESC_SCALE_STATUS_11_SPEED,/*none*/);
	_VESC_ReadRawData16(out->current, in, _VESC_offset_Status_11[_VESC_OFFSETIDX_STATUS_11_CURRENT], VESC_SCALE_STATUS_11_CURRENT,/*none*/);
	_VESC_ReadRawData8(out->motorTemp, in, _VESC_offset_Status_11[_VESC_OFFSETIDX_STATUS_11_MOTORTEMP], VESC_SCALE_STATUS_11_MOTORTEMP,/*none*/);
	_VESC_ReadRawData8u(out->errorCode, in, _VESC_offset_Status_11[_VESC_OFFSETIDX_STATUS_11_ERRORCODE], VESC_SCALE_STATUS_11_ERRORCODE, (VESC_Status_11_ErrorCode));

	return true;
}

bool VESC_convertRawToStatus12(VESC_Status_12* out, const VESC_RawFrame* in)
{
	if (out == NULL || in == NULL || in->command != VESC_COMMAND_STATUS_12 ||
		in->can_dlc != VESC_CAN_STATUS_12_DLEN)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData16(out->x, in, _VESC_offset_Status_12[_VESC_OFFSETIDX_STATUS_12_X], VESC_SCALE_STATUS_12_X,/*none*/);
	_VESC_ReadRawData16(out->y, in, _VESC_offset_Status_12[_VESC_OFFSETIDX_STATUS_12_Y], VESC_SCALE_STATUS_12_Y,/*none*/);
	_VESC_ReadRawData16(out->z, in, _VESC_offset_Status_12[_VESC_OFFSETIDX_STATUS_12_Z], VESC_SCALE_STATUS_12_Z,/*none*/);
	_VESC_ReadRawData16(out->w, in, _VESC_offset_Status_12[_VESC_OFFSETIDX_STATUS_12_W], VESC_SCALE_STATUS_12_W,/*none*/);
	return true;
}
