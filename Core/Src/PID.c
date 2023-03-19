/*
 * PID.c
 *
 *  Created on: Feb 1, 2023
 *      Author: xottal
 */

#define FALSE (valueTypes)(bool)false
#define TRUE (valueTypes)(bool)true
#define HISTORY_LENGTH 4

#include <stdlib.h>
#include <stm32f4xx.h>
#include "PID.h"
#include "Parameters.h"


extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern uint32_t freq_PWM_MO;
extern uint32_t freq_PWM_CH1;
extern uint32_t freq_PWM_CH2;


float Integral[2] = {0.0, 0.0};
float IntegralMax[2] = {10000.0, 10000.0};
float errorLast[2] = {0.0, 0.0};
uint32_t tStart[2] = {0, 0};
uint32_t tLast[2] = {0, 0};
uint32_t normCoeff[2] = {0, 0};
float freqHistory[HISTORY_LENGTH];


float limitPID(float PID) {
	if(PID > 100.0)
		return 100.0;
	if(PID < -100.0)
		return -100.0;
	else
		return PID;
}

float proceedPID(uint8_t channel) {

	//Frequency check (4 points to search good points)
	for(int i = 0; i < HISTORY_LENGTH; i++) {
		freqHistory[i] = freqHistory[i+1];
	}
	freqHistory[HISTORY_LENGTH - 1] = getFreq().val_float;
	if(freqHistory[0] != 0) {
		if(abs(freqHistory[3] - freqHistory[2]) > 1000.0) {
			if((abs(freqHistory[2] - freqHistory[1]) < 1000.0)) {
				freqHistory[3] = freqHistory[2];
			} else if (abs(freqHistory[1] - freqHistory[0]) < 1000.0) {
				freqHistory[3] = freqHistory[1];
				freqHistory[2] = freqHistory[1];
			} else {
				for(int i = 0; i < 4; i++) {
					freqHistory[i] = 0.0;
				}
			}
		}
	}
	float freqRead = freqHistory[HISTORY_LENGTH - 1];

	switch (channel) { //Channel choice
	case 0: {
		float tempRead;
		bool isFreq = false;


		uint8_t source = getSourceSelect1().val_uint8_t;
		switch (source) { //Source choice ch1
		case 0:
			tempRead = getTemp1().val_float;
			break;
		case 1:
			tempRead = getTemp2().val_float;
			break;
		case 2:
			tempRead = getTemp3().val_float;
			break;
		case 3:
			tempRead = getTemp4().val_float;
			break;
		case 4:
			isFreq = true;
			break;
		}

		if(!isFreq) { //Temp source ch1
			float P = getPcoeff1Temp().val_float;
			float PID = 0.0;
			if(tLast[0] == 0) {
				tStart[0] = __HAL_TIM_GET_COUNTER(&htim5);
				tLast[0] = tStart[0];
				errorLast[0] = tempRead - getTempCh1Set().val_float;
				PID = 0.0;
			}
			else {

				float I = getIcoeff1Temp().val_float;
				float D = getDcoeff1Temp().val_float;
				float error = tempRead - getTempCh1Set().val_float;
				uint32_t time = __HAL_TIM_GET_COUNTER(&htim5);
				if(normCoeff[0] == 0) {
					normCoeff[0] = time - tLast[0];
				}
				Integral[0] += error*(float)(time - tLast[0])/normCoeff[0];
				if(I*Integral[0] > 100.0)
					Integral[0] = 100.0/I;
				if(!getLoadSelect1().val_bool && Integral[0] > 0)
					Integral[0] = 0;
				float Der = (error - errorLast[0])/(time - tLast[0])*normCoeff[0];
				PID = P*error + I*Integral[0] + D*Der;
				tLast[0] = time;
				errorLast[0] = error;
			}
			PID = limitPID(PID);
			return PID;
		}
		else { //Freq source ch1
			if(freqHistory[0] == 0) {
				return 0.0;
			}
			float P = getPcoeff1Freq().val_float;
			float PID = 0.0;
			if(tLast[0] == 0) {
				tStart[0] = __HAL_TIM_GET_COUNTER(&htim5);
				tLast[0] = tStart[0];
				errorLast[0] = freqRead - getFreqSet().val_float;
				PID = 0.0;
			}
			else {

				float I = getIcoeff1Freq().val_float;
				float D = getDcoeff1Freq().val_float;
				float error = (freqRead - getFreqSet().val_float)/500.0;
				uint32_t time = __HAL_TIM_GET_COUNTER(&htim5);
				if(normCoeff[0] == 0) {
					normCoeff[0] = time - tLast[0];
				}
				Integral[0] += error*(float)(time - tLast[0])/normCoeff[0];
				if(I*Integral[0] > 100.0)
					Integral[0] = 100.0/I;
				if(!getLoadSelect1().val_bool && Integral[0] < 0)
					Integral[0] = 0;
				float Der = (error - errorLast[0])/(time - tLast[0])*normCoeff[0];
				PID = P*error + I*Integral[0] + D*Der;
				tLast[0] = time;
				errorLast[0] = error;
			}
			PID = -limitPID(PID);
			return PID;
		}
		break;
	}
	case 1: {
		float tempRead;
		bool isFreq = false;

		uint8_t source = getSourceSelect2().val_uint8_t;
		switch (source) {
		case 0:
			tempRead = getTemp1().val_float;
			break;
		case 1:
			tempRead = getTemp2().val_float;
			break;
		case 2:
			tempRead = getTemp3().val_float;
			break;
		case 3:
			tempRead = getTemp4().val_float;
			break;
		case 4:
			isFreq = true;
			break;
		}

		if(!isFreq) { //Temp source ch2
			float P = getPcoeff2Temp().val_float;
			float PID = 0.0;
			if(tLast[1] == 0) {
				tStart[1] = __HAL_TIM_GET_COUNTER(&htim5);
				tLast[1] = tStart[1];
				errorLast[1] = tempRead - getTempCh2Set().val_float;
				PID = 0.0;
			}
			else {

				float I = getIcoeff2Temp().val_float;
				float D = getDcoeff2Temp().val_float;
				float error = tempRead - getTempCh2Set().val_float;
				uint32_t time = __HAL_TIM_GET_COUNTER(&htim5);
				if(normCoeff[1] == 0) {
					normCoeff[1] = time - tLast[1];
				}
				Integral[1] += error*(float)(time - tLast[1])/normCoeff[1];
				if(I*Integral[1] > 100.0)
					Integral[1] = 100.0/I;
				if(!getLoadSelect2().val_bool && Integral[1] > 0)
					Integral[1] = 0;
				float Der = (error - errorLast[1])/(time - tLast[1])*normCoeff[1];
				PID = P*error + I*Integral[1] + D*Der;
				tLast[1] = time;
				errorLast[1] = error;
			}
			PID = limitPID(PID);
			return PID;
		}
		else { //Freq source ch2
			if(freqHistory[0] == 0) {
				return 0.0;
			}
			float P = getPcoeff2Freq().val_float;
			float PID = 0.0;
			if(tLast[1] == 0) {
				tStart[1] = __HAL_TIM_GET_COUNTER(&htim5);
				tLast[1] = tStart[1];
				errorLast[1] = freqRead - getFreqSet().val_float;
				PID = 0.0;
			}
			else {

				float I = getIcoeff2Freq().val_float;
				float D = getDcoeff2Freq().val_float;
				float error = (freqRead - getFreqSet().val_float)/500.0;
				uint32_t time = __HAL_TIM_GET_COUNTER(&htim5);
				if(normCoeff[1] == 0) {
					normCoeff[1] = time - tLast[1];
				}
				Integral[1] += error*(time - tLast[1])/normCoeff[1];
				if(I*Integral[1] > 100.0)
					Integral[1] = 100.0/I;
				if(!getLoadSelect2().val_bool && Integral[1] < 0)
					Integral[1] = 0;
				float Der = (error - errorLast[1])/(time - tLast[1])*normCoeff[1];
				PID = P*error + I*Integral[0] + D*Der;
				tLast[1] = time;
				errorLast[1] = error;
			}
			PID = -limitPID(PID);
			return PID;
		}
		break;
	}
	default:
		return 0.0;
	}

}

void resetPID(uint8_t channel) {
	if(channel > 1)
		return;
	Integral[channel] = 0.0;
	errorLast[channel] = 0.0;
	tStart[channel] = 0;
	tLast[channel] = 0;
	normCoeff[channel] = 0;
	for(int i = 0; i < HISTORY_LENGTH; i++) {
		freqHistory[i] = 0.0;
	}
}

void setPWM() {
	//Heater PWM
	if(!getCh1_OnOff().val_bool) {
		setPWM_CH1((valueTypes)0.0f);
		setGate1A_OnOff(FALSE);
		setGate1B_OnOff(FALSE);
		setGateH1A(FALSE);
		setGateH1B(FALSE);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
	}
	else {
		setGate1A_OnOff(TRUE);
		setGate1B_OnOff(TRUE);
		if(getModeSelect1().val_bool) {
			setPWM_CH1(getI1Set());
		}
		else
			setPWM_CH1((valueTypes)(-proceedPID(0)));


		float dutyCH1 = getPWM_CH1().val_float/100.0;
		if(!getLoadSelect1().val_bool && dutyCH1 < 0.0f) {
			dutyCH1 = 0.0f;
		}
		if(!getCH1_Polarity().val_bool) {
			dutyCH1 = dutyCH1*(-1.0);
		}


		if(dutyCH1 > 0) {
			setGateH1A(FALSE);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, freq_PWM_MO/freq_PWM_CH1 * dutyCH1 - 1);
			setGateH1B(TRUE);
		}
		else {
			setGateH1B(FALSE);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, freq_PWM_MO/freq_PWM_CH1 * (-dutyCH1) - 1);
			setGateH1A(TRUE);
		}
	}
	if(!getCh2_OnOff().val_bool) {
		setPWM_CH2((valueTypes)0.0f);
		setGate2A_OnOff(FALSE);
		setGate2B_OnOff(FALSE);
		setGateH2A(FALSE);
		setGateH2B(FALSE);
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
	}
	else {
		setGate2A_OnOff(TRUE);
		setGate2B_OnOff(TRUE);
		if(getModeSelect2().val_bool) {
			setPWM_CH2(getI2Set());
		}
		else
			setPWM_CH2((valueTypes)(-proceedPID(1)));

		float dutyCH2 = getPWM_CH2().val_float/100.0f;
		if(!getLoadSelect1().val_bool && dutyCH2 < 0.0f) {
			dutyCH2 = 0.0f;
		}
		if(!getCH2_Polarity().val_bool) {
			dutyCH2 = dutyCH2*(-1.0f);
		}


		if(dutyCH2 > 0) {
			setGateH2A(FALSE);
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, freq_PWM_MO/freq_PWM_CH2 * dutyCH2 - 1);
			setGateH2B(TRUE);
		}
		else {
			setGateH2B(FALSE);
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, freq_PWM_MO/freq_PWM_CH2 * (-dutyCH2) + 1);
			setGateH2A(TRUE);
		}
	}
}


