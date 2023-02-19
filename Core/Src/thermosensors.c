/*
 * thermosensors.c
 *
 *  Created on: Jan 29, 2023
 *      Author: xottal
 */

#include "thermosensors.h"

uint16_t rawValues3455[42] = {
		4005, 3976, 3938, 3890, 3831,
		3759, 3673, 3571, 3452, 3316,
		3164, 2998, 2819, 2631, 2437,
		2241, 2047, 1858, 1677, 1507,
		1348, 1202, 1069, 949, 841,
		745, 660, 585, 518, 447,
		408, 362, 323, 288, 257,
		230, 206, 185, 166, 149,
		135, 122
};

uint16_t rawValuesPt1000[51] = {
		0, 89, 178, 267, 355,
		443, 531, 618, 704, 791,
		877, 962, 1047, 1131, 1216,
		1299, 1383, 1465, 1548, 1630,
		1712, 1793, 1874, 1954, 2035,
		2114, 2194, 2273, 2351, 2430,
		2507, 2585, 2662, 2739, 2815,
		2891, 2967, 3042, 3117, 3192,
		3266, 3340, 3413, 3487, 3559,
		3632, 3704, 3776, 3848, 3919,
		3990
};

float getTemp3455(float rawData) {
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
		return 999.9;
	}
}

float getTempPt1000(float rawData) {
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
		return 999.9;
	}
}

