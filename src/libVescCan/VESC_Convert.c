#include <libVescCan/VESC_Convert.h>

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
	out->can_dlc = (int8_t)sizeof(VESC_CommandData_t);
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
	_VESC_WriteRawData16(out, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_DISTANCE], in->distance, VESC_SCALE_STATUS_8_DISTANCE);
	_VESC_WriteRawData8u(out, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_HUMIDITY], in->humidity, VESC_SCALE_STATUS_8_HUMIDITY);
	_VESC_WriteRawData8u(out, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_VIBRATIONS], in->vibrations, VESC_SCALE_NA);
	_VESC_WriteRawData16(out, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_WEIGHT_B], in->weightB, VESC_SCALE_STATUS_8_WEIGHT_B);

	return true;
}

bool VESC_convertStatus9ToRaw(VESC_RawFrame* out, const VESC_Status_9* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_9;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_9_DLEN;

	_VESC_WriteRawData16(out, _VESC_offset_Status_9[_VESC_OFFSETIDX_STATUS_9_POTASSIUM], in->potassium, VESC_SCALE_STATUS_9_POTASSIUM);
	_VESC_WriteRawData16(out, _VESC_offset_Status_9[_VESC_OFFSETIDX_STATUS_9_NITROGEN], in->nitrogen, VESC_SCALE_STATUS_9_NITROGEN);
	_VESC_WriteRawData16(out, _VESC_offset_Status_9[_VESC_OFFSETIDX_STATUS_9_PHOSPHORUS], in->phosphorus, VESC_SCALE_STATUS_9_PHOSPHORUS);
	_VESC_WriteRawData16(out, _VESC_offset_Status_9[_VESC_OFFSETIDX_STATUS_9_PH], in->ph, VESC_SCALE_STATUS_9_PH);

	return true;
}

bool VESC_convertStatus10ToRaw(VESC_RawFrame* out, const VESC_Status_10* in)
{
	out->vescID = in->vescID;
	out->command = VESC_COMMAND_STATUS_10;
	out->_reserved = VESC_CAN_EXTID_FLAG;
	out->can_dlc = VESC_CAN_STATUS_10_DLEN;

	_VESC_WriteRawData8u(out, _VESC_offset_Status_10[_VESC_OFFSETIDX_STATUS_10_FLAGS], in->flags, VESC_SCALE_STATUS_10_FLAGS);
	_VESC_WriteRawData8u(out, _VESC_offset_Status_10[_VESC_OFFSETIDX_STATUS_10_COMMUNICATIONSTATE], in->communicationState, VESC_SCALE_STATUS_10_COMMUNICATIONSTATE);
	_VESC_WriteRawData8u(out, _VESC_offset_Status_10[_VESC_OFFSETIDX_STATUS_10_CONTROLMODE], in->controlMode, VESC_SCALE_STATUS_10_CONTROLMODE);

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
	_VESC_ReadRawData16(out->distance, in, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_DISTANCE], VESC_SCALE_STATUS_8_DISTANCE,/*none*/);
	_VESC_ReadRawData8u(out->humidity, in, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_HUMIDITY], VESC_SCALE_STATUS_8_HUMIDITY,/*nope*/);
	_VESC_ReadRawData8u(out->vibrations, in, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_VIBRATIONS], VESC_SCALE_STATUS_8_VIBRATIONS,/*nope*/);
	_VESC_ReadRawData16(out->weightB, in, _VESC_offset_Status_8[_VESC_OFFSETIDX_STATUS_8_WEIGHT_B], VESC_SCALE_STATUS_8_WEIGHT_B,/*none*/);

	return true;
}

bool VESC_convertRawToStatus9(VESC_Status_9* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_STATUS_9)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData16(out->potassium, in, _VESC_offset_Status_9[_VESC_OFFSETIDX_STATUS_9_POTASSIUM], VESC_SCALE_STATUS_9_POTASSIUM,/*none*/);
	_VESC_ReadRawData16(out->nitrogen, in, _VESC_offset_Status_9[_VESC_OFFSETIDX_STATUS_9_NITROGEN], VESC_SCALE_STATUS_9_NITROGEN,/*none*/);
	_VESC_ReadRawData16(out->phosphorus, in, _VESC_offset_Status_9[_VESC_OFFSETIDX_STATUS_9_PHOSPHORUS], VESC_SCALE_STATUS_9_PHOSPHORUS,/*none*/);
	_VESC_ReadRawData16(out->ph, in, _VESC_offset_Status_9[_VESC_OFFSETIDX_STATUS_9_PH], VESC_SCALE_STATUS_9_PH,/*none*/);

	return true;
}

bool VESC_convertRawToStatus10(VESC_Status_10* out, const VESC_RawFrame* in)
{
	if (in->command != VESC_COMMAND_STATUS_10)
		return false;

	out->vescID = in->vescID;

	_VESC_ReadRawData8u(out->flags, in, _VESC_offset_Status_10[_VESC_OFFSETIDX_STATUS_10_FLAGS], VESC_SCALE_STATUS_10_FLAGS,/*nope*/);
	_VESC_ReadRawData8u(out->communicationState, in, _VESC_offset_Status_10[_VESC_OFFSETIDX_STATUS_10_COMMUNICATIONSTATE], VESC_SCALE_STATUS_10_COMMUNICATIONSTATE,(VESC_Status_10_CommunicationState));
	_VESC_ReadRawData8u(out->controlMode, in, _VESC_offset_Status_10[_VESC_OFFSETIDX_STATUS_10_CONTROLMODE], VESC_SCALE_STATUS_10_CONTROLMODE,(VESC_Status_10_ControlMode));

	return true;
}