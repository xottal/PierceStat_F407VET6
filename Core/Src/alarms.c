/*
 * alarms.c
 *
 *  Created on: Feb 9, 2023
 *      Author: gIvanov
 */

#include "alarms.h"
#include "Parameters.h"

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

void handleAlarms() {
	uint32_t alarmVector = getAlarms().val_uint32_t;
	uint32_t alarmMasksVector = getAlarmMasks().val_uint32_t;

	alarmVector &= alarmMasksVector;
}


