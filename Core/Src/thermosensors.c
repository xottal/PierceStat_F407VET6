/*
 * thermosensors.c
 *
 *  Created on: Jan 29, 2023
 *      Author: xottal
 */

#include "thermosensors.h"

float getTemp3455(uint16_t rawData) {
	if(rawData < rawValues3455[41] ||
		rawData > rawValues3455[0]) {
		return 999.9;
	}
	else {
		for(int i = 1; i < 42; i++) {
			if(rawData >= rawValues3455[i]) {
				float temp;
				temp = 5.0/(rawValues3455[i-1] - rawValues3455[i]) * (rawValues3455[i-1] - rawData) + i * 5.0 - 60; //C
				return temp;
			}
		}
	}
}

float getTempPt1000(uint16_t rawData) {
	if(rawData > rawValuesPt1000[50]) {
		return 999.9;
	}
	else {
		for(int i = 1; i < 51; i++) {
			if(rawData <= rawValuesPt1000[i]) {
				float temp;
				temp = 5.0/(rawValuesPt1000[i] - rawValuesPt1000[i-1]) * (rawData - rawValuesPt1000[i-1]) + (i-1) * 5.0; //C
				return temp;
			}
		}
	}
}

