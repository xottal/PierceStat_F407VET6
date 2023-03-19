/*
 * alarms.c
 *
 *  Created on: Feb 9, 2023
 *      Author: gIvanov
 */

#include "alarms.h"
#include "Parameters.h"


uint32_t previousAlarmVector = 0b0;

uint8_t getBit(uint32_t* vector, uint8_t n) {
	if(n > 32)
		return 255;
	return (*vector >> n) & 1U;
}

bool setBit(uint32_t* vector, uint8_t n, uint8_t value) {
	if(n > 32 || value > 1)
		return false;
	uint32_t res = *vector;
	res = (res & ~((uint32_t)1 << n)) | (value << n);
	*vector = res;
	return true;
}

bool handleAlarms() {
	proceedAlarms();
	uint32_t alarmVector = getAlarms().val_uint32_t;
	uint32_t alarmMasksVector = getAlarmMasks().val_uint32_t;

	alarmVector &= alarmMasksVector;
	alarmVector &= previousAlarmVector;

	previousAlarmVector = getAlarms().val_uint32_t;

	if(alarmVector != 0b0) {
		return true;
	}
	return false;
}

void proceedAlarms() {
	uint32_t alarmVector = 0b0;
	//Current Alarm
	if(getI_1A().val_float > getI_1A_Max().val_float || getI_1B().val_float > getI_1B_Max().val_float) {
		setBit(&alarmVector, 0, 1);
	}
	if(getI_2A().val_float > getI_2A_Max().val_float || getI_2B().val_float > getI_2B_Max().val_float) {
		setBit(&alarmVector, 1, 1);
	}
	//U_Power Alarm
	if(getU_24Vmeas().val_float > getU_24V_Max().val_float || getU_24Vmeas().val_float < getU_24V_Min().val_float) {
		setBit(&alarmVector, 2, 1);
	}
	//U_Heater Alarm
	if(getU_HeaterMeas().val_float > getU_HeaterMax().val_float || getU_HeaterMeas().val_float < getU_HeaterMin().val_float) {
		setBit(&alarmVector, 3, 1);
	}
	//Temp Alarms
	if(getTemp1().val_float > getTemp1_Max().val_float || getTemp1().val_float < getTemp1_Min().val_float) {
		setBit(&alarmVector, 4, 1);
	}
	if(getTemp2().val_float > getTemp2_Max().val_float || getTemp2().val_float < getTemp2_Min().val_float) {
		setBit(&alarmVector, 5, 1);
	}
	if(getTemp3().val_float > getTemp3_Max().val_float || getTemp3().val_float < getTemp3_Min().val_float) {
		setBit(&alarmVector, 6, 1);
	}
	if(getTemp4().val_float > getTemp4_Max().val_float || getTemp4().val_float < getTemp4_Min().val_float) {
		setBit(&alarmVector, 7, 1);
	}
	//Freq Alarm
	if(getFreq().val_float > getFreqMax().val_float || getFreq().val_float < getFreq().val_float) {
		setBit(&alarmVector, 8, 1);
	}
	setAlarms((valueTypes)alarmVector);
}
