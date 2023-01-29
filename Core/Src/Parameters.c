/*
 * UARTComms.c
 *
 *  Created on: 18 янв. 2023 г.
 *      Author: xottal
 */

#include "main.h"
#include "Parameters.h"


ParStruct* params[PARAMS_COUNT];
uint8_t paramTable[PARAMS_RANGE];
char* typeNames[] = {"UINT8_T", "UINT16_T", "UINT32_T", "INT8_T", "INT16_T", "INT32_T", "FLOAT", "BOOL"};

//Список параметров

ParStruct ParamList = {		.commandNumber = 100,
                            .commandDescription = "Get list of all parameters",
                            .isCommand = true,
							.command = commandParamList};

ParStruct U_PowerSet = {	.commandNumber = 150,
                            .commandDescription = "Set U_Power",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getU_PowerSet,
							.set = setU_PowerSet,
                            .value.val_float = 12.0,
							.valueAbsMin.val_float = 3.9,
							.valueAbsMax.val_float = 24.1};
ParStruct U_PowerMin = {	.commandNumber = 151,
                            .commandDescription = "Set U_Power Min Alarm",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getU_PowerMin,
							.set = setU_PowerMin,
                            .value.val_float = 3.9,
                            .valueAbsMin.val_float = 3.9,
                            .valueAbsMax.val_float = 22.0};
ParStruct U_PowerMax = {	.commandNumber = 152,
                            .commandDescription = "Set U_Power Max Alarm",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getU_PowerMax,
							.set = setU_PowerMax,
                            .value.val_float = 24.1,
                            .valueAbsMin.val_float = 6.0,
                            .valueAbsMax.val_float = 24.1};
ParStruct U_PowerOnOff = {.commandNumber = 153,
                            .commandDescription = "U_Power On Off",
                            .type = BOOL,
                            .isCommand = false,
                            .readOnly = false,
							.get = getU_PowerOnOff,
							.set = setU_PowerOnOff,
                            .value.val_bool = false};
ParStruct U_24Vmeas = {.commandNumber = 200,
                            .commandDescription = "24V input measure",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = true,
							.get = getU_24Vmeas,
							.set = setU_24Vmeas,
							.value.val_float = 0.0};
ParStruct U_24Vcoeff = {.commandNumber = 201,
                            .commandDescription = "24V ADC coeff",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getU_24Vcoeff,
							.set = setU_24Vcoeff,
                            .value.val_float = 0.0116,
                            .valueAbsMin.val_float = 0.001,
                            .valueAbsMax.val_float = 1.0};
ParStruct U_PowerMeas = {.commandNumber = 202,
                            .commandDescription = "U_Power measure",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = true,
							.get = getU_PowerMeas,
							.set = setU_PowerMeas};
ParStruct U_PowerCoeff = {.commandNumber = 203,
                            .commandDescription = "U_Power ADC coeff",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getU_PowerCoeff,
							.set = setU_PowerCoeff,
                            .value.val_float = 0.0116,
                            .valueAbsMin.val_float = 0.001,
                            .valueAbsMax.val_float = 1.0};

ParStruct I_1A = {.commandNumber = 210,
                            .commandDescription = "I_1A measure",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = true,
							.get = getI_1A,
							.set = setI_1A};
ParStruct I_1B = {.commandNumber = 211,
                            .commandDescription = "I_1B measure",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = true,
							.get = getI_1B,
							.set = setI_1B};
ParStruct I_2A = {.commandNumber = 212,
                            .commandDescription = "I_2A measure",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = true,
							.get = getI_2A,
							.set = setI_2A};
ParStruct I_2B = {.commandNumber = 213,
                            .commandDescription = "I_2B measure",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = true,
							.get = getI_2B,
							.set = setI_2B};

ParStruct I_1A_Coeff = {.commandNumber = 214,
                            .commandDescription = "I_1A ADC coeff",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getI_1A_Coeff,
							.set = setI_1A_Coeff,
                            .value.val_float = 0.1,
                            .valueAbsMin.val_float = 0.001,
                            .valueAbsMax.val_float = 1.0};
ParStruct I_1B_Coeff = {.commandNumber = 215,
                            .commandDescription = "I_1B ADC coeff",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getI_1B_Coeff,
							.set = setI_1B_Coeff,
                            .value.val_float = 0.1,
                            .valueAbsMin.val_float = 0.001,
                            .valueAbsMax.val_float = 1.0};
ParStruct I_2A_Coeff = {.commandNumber = 216,
                            .commandDescription = "I_2A ADC coeff",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getI_2A_Coeff,
							.set = setI_2A_Coeff,
                            .value.val_float = 0.1,
                            .valueAbsMin.val_float = 0.001,
                            .valueAbsMax.val_float = 1.0};
ParStruct I_2B_Coeff = {.commandNumber = 217,
                            .commandDescription = "I_2B ADC coeff",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getI_2B_Coeff,
							.set = setI_2B_Coeff,
                            .value.val_float = 0.1,
                            .valueAbsMin.val_float = 0.001,
                            .valueAbsMax.val_float = 1.0};

ParStruct Temp1 = {.commandNumber = 220,
                            .commandDescription = "Temp1 measure",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = true,
							.get = getTemp1,
							.set = setTemp1};
ParStruct Temp2 = {.commandNumber = 221,
                            .commandDescription = "Temp2 measure",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = true,
							.get = getTemp2,
							.set = setTemp2};
ParStruct Temp3 = {			.commandNumber = 222,
                            .commandDescription = "Temp3 measure",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = true,
							.get = getTemp3,
							.set = setTemp3};
ParStruct Temp4 = {			.commandNumber = 223,
							.commandDescription = "Temp4 measure",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = true,
							.get = getTemp4,
							.set = setTemp4};

ParStruct Temp1_coeff = {	.commandNumber = 224,
                            .commandDescription = "Temp1 ADC coeff",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getTemp1_coeff,
							.set = setTemp1_coeff,
                            .value.val_float = 1.0,
                            .valueAbsMin.val_float = 0.8,
                            .valueAbsMax.val_float = 1.2};
ParStruct Temp2_coeff = {	.commandNumber = 225,
                            .commandDescription = "Temp2 ADC coeff",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getTemp2_coeff,
							.set = setTemp2_coeff,
                            .value.val_float = 1.0,
                            .valueAbsMin.val_float = 0.8,
                            .valueAbsMax.val_float = 1.2};
ParStruct Temp3_coeff = {	.commandNumber = 226,
                            .commandDescription = "Temp3 ADC coeff",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getTemp3_coeff,
							.set = setTemp3_coeff,
                            .value.val_float = 1.0,
                            .valueAbsMin.val_float = 0.8,
                            .valueAbsMax.val_float = 1.2};
ParStruct Temp4_coeff = {	.commandNumber = 227,
                            .commandDescription = "Temp4 ADC coeff",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getTemp4_coeff,
							.set = setTemp4_coeff,
                            .value.val_float = 1.0,
                            .valueAbsMin.val_float = 0.8,
                            .valueAbsMax.val_float = 1.2};

ParStruct LoadSelect1 = {	.commandNumber = 301,
							.commandDescription = "1ch select: 0-Res, 1-Peltier",
							.type = BOOL,
							.isCommand = false,
							.readOnly = false,
							.get = getLoadSelect1,
							.set = setLoadSelect1,
							.value.val_bool = 0};
ParStruct LoadSelect2 = {	.commandNumber = 302,
							.commandDescription = "2ch select: 0-Res, 1-Peltier",
							.type = BOOL,
							.isCommand = false,
							.readOnly = false,
							.get = getLoadSelect2,
							.set = setLoadSelect2,
							.value.val_bool = 0};
ParStruct ModeSelect1 = {	.commandNumber = 303,
							.commandDescription = "1ch mode: 0-PID, 1-constI",
							.type = BOOL,
							.isCommand = false,
							.readOnly = false,
							.get = getModeSelect1,
							.set = setModeSelect1,
							.value.val_bool = 0};
ParStruct ModeSelect2 = {	.commandNumber = 304,
							.commandDescription = "2ch mode: 0-PID, 1-constI",
							.type = BOOL,
							.isCommand = false,
							.readOnly = false,
							.get = getModeSelect2,
							.set = setModeSelect2,
							.value.val_bool = 0};
ParStruct Ch1_OnOff = {		.commandNumber = 305,
							.commandDescription = "1ch On Off",
							.type = BOOL,
							.isCommand = false,
							.readOnly = false,
							.get = getCh1_OnOff,
							.set = setCh1_OnOff,
							.value.val_bool = false};
ParStruct Ch2_OnOff = {		.commandNumber = 306,
							.commandDescription = "2ch On Off",
							.type = BOOL,
							.isCommand = false,
							.readOnly = false,
							.get = getCh2_OnOff,
							.set = setCh2_OnOff,
							.value.val_bool = false};
ParStruct SourceSelect1 = {	.commandNumber = 307,
							.commandDescription = "1ch source: 0-3:temp, 4-Piezo",
							.type = UINT8_T,
							.isCommand = false,
							.readOnly = false,
							.get = getSourceSelect1,
							.set = setSourceSelect1,
							.value.val_uint8_t = 0};
ParStruct SourceSelect2 = {	.commandNumber = 308,
							.commandDescription = "2ch source: 0-3:temp, 4-Piezo",
							.type =  UINT8_T,
							.isCommand = false,
							.readOnly = false,
							.get = getSourceSelect2,
							.set = setSourceSelect2,
							.value.val_uint8_t = 0};
ParStruct Pcoeff1Temp = {	.commandNumber = 309,
							.commandDescription = "P coeff Temp 1 ch",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.get = getPcoeff1Temp,
							.set = setPcoeff1Temp,
							.value.val_float = 0.0,
							.valueAbsMin.val_float = 0.0,
							.valueAbsMax.val_float = 100.0};
ParStruct Pcoeff2Temp = {	.commandNumber = 310,
							.commandDescription = "P coeff Temp 2 ch",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.get = getPcoeff2Temp,
							.set = setPcoeff2Temp,
							.value.val_float = 0.0,
							.valueAbsMin.val_float = 0.0,
							.valueAbsMax.val_float = 100.0};
ParStruct Icoeff1Temp = {	.commandNumber = 311,
							.commandDescription = "I coeff Temp 1 ch",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.get = getIcoeff1Temp,
							.set = setIcoeff1Temp,
							.value.val_float = 0.0,
							.valueAbsMin.val_float = 0.0,
							.valueAbsMax.val_float = 100.0};
ParStruct Icoeff2Temp = {	.commandNumber = 312,
							.commandDescription = "I coeff Temp 2 ch",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.get = getIcoeff2Temp,
							.set = setIcoeff2Temp,
							.value.val_float = 0.0,
							.valueAbsMin.val_float = 0.0,
							.valueAbsMax.val_float = 100.0};
ParStruct Dcoeff1Temp = {	.commandNumber = 313,
							.commandDescription = "D coeff Temp 1 ch",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.get = getDcoeff1Temp,
							.set = setDcoeff1Temp,
							.value.val_float = 0.0,
							.valueAbsMin.val_float = 0.0,
							.valueAbsMax.val_float = 100.0};
ParStruct Dcoeff2Temp = {	.commandNumber = 314,
							.commandDescription = "D coeff Temp 2 ch",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.get = getDcoeff2Temp,
							.set = setDcoeff2Temp,
							.value.val_float = 0.0,
							.valueAbsMin.val_float = 0.0,
							.valueAbsMax.val_float = 100.0};
ParStruct Pcoeff1Freq = {	.commandNumber = 315,
							.commandDescription = "P coeff Freq 1 ch",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.get = getPcoeff1Freq,
							.set = setPcoeff1Freq,
							.value.val_float = 0.0,
							.valueAbsMin.val_float = 0.0,
							.valueAbsMax.val_float = 100.0};
ParStruct Pcoeff2Freq = {	.commandNumber = 316,
							.commandDescription = "P coeff Freq 2 ch",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.get = getPcoeff2Freq,
							.set = setPcoeff2Freq,
							.value.val_float = 0.0,
							.valueAbsMin.val_float = 0.0,
							.valueAbsMax.val_float = 100.0};
ParStruct Icoeff1Freq = {	.commandNumber = 317,
							.commandDescription = "I coeff Freq 1 ch",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.get = getIcoeff1Freq,
							.set = setIcoeff1Freq,
							.value.val_float = 0.0,
							.valueAbsMin.val_float = 0.0,
							.valueAbsMax.val_float = 100.0};
ParStruct Icoeff2Freq = {	.commandNumber = 318,
							.commandDescription = "I coeff Freq 2 ch",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.get = getIcoeff2Freq,
							.set = setIcoeff2Freq,
							.value.val_float = 0.0,
							.valueAbsMin.val_float = 0.0,
							.valueAbsMax.val_float = 100.0};
ParStruct Dcoeff1Freq = {	.commandNumber = 319,
							.commandDescription = "D coeff Freq 1 ch",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.get = getDcoeff1Freq,
							.set = setDcoeff1Freq,
							.value.val_float = 0.0,
							.valueAbsMin.val_float = 0.0,
							.valueAbsMax.val_float = 100.0};
ParStruct Dcoeff2Freq = {	.commandNumber = 320,
							.commandDescription = "D coeff Freq 2 ch",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.get = getDcoeff2Freq,
							.set = setDcoeff2Freq,
							.value.val_float = 0.0,
							.valueAbsMin.val_float = 0.0,
							.valueAbsMax.val_float = 100.0};
ParStruct I1Set = {			.commandNumber = 330,
                            .commandDescription = "I1 Set in %",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getI1Set,
							.set = setI1Set,
                            .value.val_float = 0.0,
                            .valueAbsMin.val_float = 0.0,
                            .valueAbsMax.val_float = 100.0};
ParStruct I2Set = {			.commandNumber = 331,
                            .commandDescription = "I2 Set in %",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = false,
							.get = getI2Set,
							.set = setI2Set,
                            .value.val_float = 0.0,
                            .valueAbsMin.val_float = 0.0,
                            .valueAbsMax.val_float = 100.0};

ParStruct Gate1A_OnOff = {	.commandNumber = 401,
                            .commandDescription = "gate1A On Off",
                            .type = BOOL,
                            .isCommand = false,
                            .readOnly = true,
							.get = getGate1A_OnOff,
							.set = setGate1A_OnOff,
                            .value.val_bool = 0};
ParStruct Gate1B_OnOff = {	.commandNumber = 402,
                            .commandDescription = "gate1B On Off",
                            .type = BOOL,
                            .isCommand = false,
                            .readOnly = true,
							.get = getGate1B_OnOff,
							.set = setGate1B_OnOff,
                            .value.val_bool = 0};
ParStruct Gate2A_OnOff = {	.commandNumber = 403,
                            .commandDescription = "gate2A On Off",
                            .type = BOOL,
                            .isCommand = false,
                            .readOnly = true,
							.get = getGate2A_OnOff,
							.set = setGate2A_OnOff,
                            .value.val_bool = 0};
ParStruct Gate2B_OnOff = {	.commandNumber = 404,
                            .commandDescription = "gate2B On Off",
                            .type = BOOL,
                            .isCommand = false,
                            .readOnly = true,
							.get = getGate2B_OnOff,
							.set = setGate2B_OnOff,
                            .value.val_bool = 0};

ParStruct GateH1A = {		.commandNumber = 405,
                            .commandDescription = "Ch1A High Gate",
                            .type = BOOL,
                            .isCommand = false,
                            .readOnly = true,
							.set = setGateH1A,
							.get = getGateH1A,
                            .value.val_bool = 1};
ParStruct GateH1B = {		.commandNumber = 406,
                            .commandDescription = "Ch1B High Gate",
                            .type = BOOL,
                            .isCommand = false,
                            .readOnly = true,
							.set = setGateH1B,
							.get = getGateH1B,
                            .value.val_bool = 1};
ParStruct GateH2A = {		.commandNumber = 407,
                            .commandDescription = "Ch2A High Gate",
                            .type = BOOL,
                            .isCommand = false,
                            .readOnly = true,
							.set = setGateH2A,
							.get = getGateH2A,
                            .value.val_bool = 1};
ParStruct GateH2B = {		.commandNumber = 408,
                            .commandDescription = "Ch2B High Gate",
                            .type = BOOL,
                            .isCommand = false,
                            .readOnly = true,
							.set = setGateH2B,
							.get = getGateH2B,
                            .value.val_bool = 1};

ParStruct PWM_CH1 = {		.commandNumber = 409,
							.commandDescription = "Channel 1 PWM duty (signed)",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.set = setPWM_CH1,
							.get = getPWM_CH1,
							.value.val_float = 20.0,
                            .valueAbsMin.val_float = -100.1,
                            .valueAbsMax.val_float = 100.1};

ParStruct PWM_CH2 = {		.commandNumber = 410,
							.commandDescription = "Channel 2 PWM duty (signed)",
							.type = FLOAT,
							.isCommand = false,
							.readOnly = false,
							.set = setPWM_CH2,
							.get = getPWM_CH2,
							.value.val_float = 20.0,
                            .valueAbsMin.val_float = -100.1,
                            .valueAbsMax.val_float = 100.1};

ParStruct CH1_Polarity = {	.commandNumber = 411,
							.commandDescription = "Ch1 Polarity",
							.type = BOOL,
							.isCommand = false,
							.readOnly = false,
							.set = setCH1_Polarity,
							.get = getCH1_Polarity,
							.value.val_bool = 1};

ParStruct CH2_Polarity = {	.commandNumber = 412,
							.commandDescription = "Ch2 Polarity",
							.type = BOOL,
							.isCommand = false,
							.readOnly = false,
							.set = setCH2_Polarity,
							.get = getCH2_Polarity,
							.value.val_bool = 1};

ParStruct Freq = {			.commandNumber = 500,
                            .commandDescription = "Pierce freq, Hz",
                            .type = FLOAT,
                            .isCommand = false,
                            .readOnly = true,
							.set = setFreq,
							.get = getFreq,
                            .value.val_float = 1.0,
                            .valueAbsMin.val_float = 0.0,
                            .valueAbsMax.val_float = 1000000000.0};


void InitParams() {
	uint8_t i = 0;
	params[i++] = &ParamList;
	params[i++] = &U_PowerSet;
	params[i++] = &U_PowerMin;
	params[i++] = &U_PowerMax;
	params[i++] = &U_PowerOnOff;
	params[i++] = &U_24Vmeas;
	params[i++] = &U_24Vcoeff;
	params[i++] = &U_PowerMeas;
	params[i++] = &U_PowerCoeff;
	params[i++] = &I_1A;
	params[i++] = &I_1B;
	params[i++] = &I_2A;
	params[i++] = &I_2B;
	params[i++] = &I_1A_Coeff;
	params[i++] = &I_1B_Coeff;
	params[i++] = &I_2A_Coeff;
	params[i++] = &I_2B_Coeff;

	params[i++] = &Temp1;
	params[i++] = &Temp2;
	params[i++] = &Temp3;
	params[i++] = &Temp4;
	params[i++] = &Temp1_coeff;
	params[i++] = &Temp2_coeff;
	params[i++] = &Temp3_coeff;
	params[i++] = &Temp4_coeff;

	params[i++] = &LoadSelect1;
	params[i++] = &LoadSelect2;
	params[i++] = &ModeSelect1;
	params[i++] = &ModeSelect2;
	params[i++] = &Ch1_OnOff;
	params[i++] = &Ch2_OnOff;
	params[i++] = &SourceSelect1;
	params[i++] = &SourceSelect2;

	params[i++] = &Pcoeff1Temp;
	params[i++] = &Pcoeff2Temp;
	params[i++] = &Icoeff1Temp;
	params[i++] = &Icoeff2Temp;
	params[i++] = &Dcoeff1Temp;
	params[i++] = &Dcoeff2Temp;

	params[i++] = &Pcoeff1Freq;
	params[i++] = &Pcoeff2Freq;
	params[i++] = &Icoeff1Freq;
	params[i++] = &Icoeff2Freq;
	params[i++] = &Dcoeff1Freq;
	params[i++] = &Dcoeff2Freq;

	params[i++] = &I1Set;
	params[i++] = &I2Set;

	params[i++] = &Gate1A_OnOff;
	params[i++] = &Gate1B_OnOff;
	params[i++] = &Gate2A_OnOff;
	params[i++] = &Gate2B_OnOff;

	params[i++] = &GateH1A;
	params[i++] = &GateH1B;
	params[i++] = &GateH2A;
	params[i++] = &GateH2B;

	params[i++] = &PWM_CH1;
	params[i++] = &PWM_CH2;

	params[i++] = &CH1_Polarity;
	params[i++] = &CH2_Polarity;

	params[i++] = &Freq;


	for(uint8_t j = 0; j < PARAMS_COUNT; j++) {
		paramTable[params[j]->commandNumber] = j+1;
	}
}

bool setU_PowerSet(valueTypes value) {
    if(value.val_float >= U_PowerSet.valueAbsMax.val_float ||
       value.val_float <= U_PowerSet.valueAbsMin.val_float) {
       return false;
    } else {
    	//Set_U_Heater PWM (10 kHz, 16800)
    	extern TIM_HandleTypeDef htim8;
    	int16_t counterSet = 16800*(1.20 - 0.05 * value.val_float);
    	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, counterSet > 0 ? counterSet : 0);
        U_PowerSet.value = value;
        return true;
    }
}
valueTypes getU_PowerSet(void) {
    return U_PowerSet.value;
}

bool setU_PowerOnOff(valueTypes state) {
	HAL_GPIO_WritePin(Disable_DC_DC_GPIO_Port, Disable_DC_DC_Pin, state.val_bool);
    U_PowerOnOff.value = state;
    return true;
}
valueTypes getU_PowerOnOff(void) {
    return U_PowerOnOff.value;
}

bool setU_PowerMin(valueTypes value) {
	if(value.val_float >= U_PowerMin.valueAbsMax.val_float ||
	   value.val_float <= U_PowerMin.valueAbsMin.val_float) {
	   return false;
	} else {
		U_PowerMin.value = value;
		return true;
	}
}
valueTypes getU_PowerMin(void) {
    return U_PowerMin.value;
}

bool setU_PowerMax(valueTypes value) {
	if(value.val_float >= U_PowerMax.valueAbsMax.val_float ||
	   value.val_float <= U_PowerMax.valueAbsMin.val_float) {
	   return false;
	} else {
		U_PowerMax.value = value;
		return true;
	}
}
valueTypes getU_PowerMax(void) {
    return U_PowerMax.value;
}


bool setU_24Vmeas(valueTypes value) {
    U_24Vmeas.value = value;
    return true;
}
valueTypes getU_24Vmeas() {
    return U_24Vmeas.value;
}

bool setU_24Vcoeff(valueTypes value) {
    if(value.val_float >= U_24Vcoeff.valueAbsMax.val_float ||
       value.val_float <= U_24Vcoeff.valueAbsMin.val_float) {
       return false;
    } else {
        U_24Vcoeff.value = value;
        return true;
    }
}

valueTypes getU_24Vcoeff(void) {
    return U_24Vcoeff.value;
}


bool setU_PowerMeas(valueTypes value) {
    U_PowerMeas.value = value;
    return true;
}
valueTypes getU_PowerMeas() {
    return U_PowerMeas.value;
}

bool setU_PowerCoeff(valueTypes value) {
    if(value.val_float >= U_PowerCoeff.valueAbsMax.val_float ||
       value.val_float <= U_PowerCoeff.valueAbsMin.val_float) {
       return false;
    } else {
       U_PowerCoeff.value = value;
       return true;
    }
}

valueTypes getU_PowerCoeff(void) {
    return U_PowerCoeff.value;
}

bool setI_1A(valueTypes value) {
    I_1A.value = value;
    return true;
}
valueTypes getI_1A() {
    return I_1A.value;
}
bool setI_1B(valueTypes value) {
    I_1B.value = value;
    return true;
}
valueTypes getI_1B() {
    return I_1B.value;
}
bool setI_2A(valueTypes value) {
    I_2A.value = value;
    return true;
}
valueTypes getI_2A() {
    return I_2A.value;
}
bool setI_2B(valueTypes value) {
    I_2B.value = value;
    return true;
}
valueTypes getI_2B() {
    return I_2B.value;
}

bool setI_1A_Coeff(valueTypes value) {
    if(value.val_float >= I_1A_Coeff.valueAbsMax.val_float ||
       value.val_float <= I_1A_Coeff.valueAbsMin.val_float) {
       return false;
    } else {
        I_1A_Coeff.value = value;
        return true;
    }
}
valueTypes getI_1A_Coeff(void) {
    return I_1A_Coeff.value;
}
bool setI_1B_Coeff(valueTypes value) {
    if(value.val_float >= I_1B_Coeff.valueAbsMax.val_float ||
       value.val_float <= I_1B_Coeff.valueAbsMin.val_float) {
       return false;
    } else {
        I_1B_Coeff.value = value;
        return true;
    }
}
valueTypes getI_1B_Coeff(void) {
    return I_1B_Coeff.value;
}
bool setI_2A_Coeff(valueTypes value) {
    if(value.val_float >= I_2A_Coeff.valueAbsMax.val_float ||
       value.val_float <= I_2A_Coeff.valueAbsMin.val_float) {
       return false;
    } else {
        I_2A_Coeff.value = value;
        return true;
    }
}
valueTypes getI_2A_Coeff(void) {
    return I_2A_Coeff.value;
}
bool setI_2B_Coeff(valueTypes value) {
    if(value.val_float >= I_2B_Coeff.valueAbsMax.val_float ||
       value.val_float <= I_2B_Coeff.valueAbsMin.val_float) {
       return false;
    } else {
        I_2B_Coeff.value = value;
        return true;
    }
}
valueTypes getI_2B_Coeff(void) {
    return I_2B_Coeff.value;
}


bool setTemp1(valueTypes value) {
    Temp1.value = value;
    return true;
}
valueTypes getTemp1() {
    return Temp1.value;
}
bool setTemp2(valueTypes value) {
    Temp2.value = value;
    return true;
}
valueTypes getTemp2() {
    return Temp2.value;
}
bool setTemp3(valueTypes value) {
    Temp3.value = value;
    return true;
}
valueTypes getTemp3() {
    return Temp3.value;
}
bool setTemp4(valueTypes value) {
    Temp4.value = value;
    return true;
}
valueTypes getTemp4() {
    return Temp4.value;
}

bool setTemp1_coeff(valueTypes value) {
    if(value.val_float >= Temp1_coeff.valueAbsMax.val_float ||
       value.val_float <= Temp1_coeff.valueAbsMin.val_float) {
       return false;
    } else {
        Temp1_coeff.value = value;
        return true;
    }
}
valueTypes getTemp1_coeff(void) {
    return Temp1_coeff.value;
}
bool setTemp2_coeff(valueTypes value) {
    if(value.val_float >= Temp2_coeff.valueAbsMax.val_float ||
       value.val_float <= Temp2_coeff.valueAbsMin.val_float) {
       return false;
    } else {
        Temp2_coeff.value = value;
        return true;
    }
}
valueTypes getTemp2_coeff(void) {
    return Temp2_coeff.value;
}
bool setTemp3_coeff(valueTypes value) {
    if(value.val_float >= Temp3_coeff.valueAbsMax.val_float ||
       value.val_float <= Temp3_coeff.valueAbsMin.val_float) {
       return false;
    } else {
        Temp3_coeff.value = value;
        return true;
    }
}
valueTypes getTemp3_coeff(void) {
    return Temp3_coeff.value;
}
bool setTemp4_coeff(valueTypes value) {
    if(value.val_float >= Temp4_coeff.valueAbsMax.val_float ||
       value.val_float <= Temp4_coeff.valueAbsMin.val_float) {
       return false;
    } else {
        Temp4_coeff.value = value;
        return true;
    }
}
valueTypes getTemp4_coeff(void) {
    return Temp4_coeff.value;
}

bool setLoadSelect1(valueTypes state) {
    LoadSelect1.value = state;
    return true;
}
valueTypes getLoadSelect1(void) {
    return LoadSelect1.value;
}
bool setLoadSelect2(valueTypes state) {
    LoadSelect2.value = state;
    return true;
}
valueTypes getLoadSelect2(void) {
    return LoadSelect2.value;
}

bool setModeSelect1(valueTypes state) {
    ModeSelect1.value = state;
    return true;
}
valueTypes getModeSelect1(void) {
    return ModeSelect1.value;
}
bool setModeSelect2(valueTypes state) {
    ModeSelect2.value = state;
    return true;
}
valueTypes getModeSelect2(void) {
    return ModeSelect2.value;
}

bool setCh1_OnOff(valueTypes state) {
   Ch1_OnOff.value = state;
    return true;
}
valueTypes getCh1_OnOff(void) {
    return Ch1_OnOff.value;
}
bool setCh2_OnOff(valueTypes state) {
    Ch2_OnOff.value = state;
    return true;
}
valueTypes getCh2_OnOff(void) {
    return Ch2_OnOff.value;
}

bool setSourceSelect1(valueTypes state) {
   SourceSelect1.value = state;
    return true;
}
valueTypes getSourceSelect1(void) {
    return SourceSelect1.value;
}
bool setSourceSelect2(valueTypes state) {
    SourceSelect2.value = state;
    return true;
}
valueTypes getSourceSelect2(void) {
    return SourceSelect2.value;
}

bool setPcoeff1Temp(valueTypes value) {
    if(value.val_float >= Pcoeff1Temp.valueAbsMax.val_float ||
       value.val_float <= Pcoeff1Temp.valueAbsMin.val_float) {
       return false;
    } else {
        Pcoeff1Temp.value = value;
        return true;
    }
}
valueTypes getPcoeff1Temp(void) {
    return Pcoeff1Temp.value;
}
bool setPcoeff2Temp(valueTypes value) {
    if(value.val_float >= Pcoeff2Temp.valueAbsMax.val_float ||
       value.val_float <= Pcoeff2Temp.valueAbsMin.val_float) {
       return false;
    } else {
        Pcoeff2Temp.value = value;
        return true;
    }
}
valueTypes getPcoeff2Temp(void) {
    return Pcoeff2Temp.value;
}
bool setIcoeff1Temp(valueTypes value) {
    if(value.val_float >= Icoeff1Temp.valueAbsMax.val_float ||
       value.val_float <= Icoeff1Temp.valueAbsMin.val_float) {
       return false;
    } else {
        Icoeff1Temp.value = value;
        return true;
    }
}
valueTypes getIcoeff1Temp(void) {
    return Icoeff1Temp.value;
}
bool setIcoeff2Temp(valueTypes value) {
    if(value.val_float >= Icoeff2Temp.valueAbsMax.val_float ||
       value.val_float <= Icoeff2Temp.valueAbsMin.val_float) {
       return false;
    } else {
        Icoeff2Temp.value = value;
        return true;
    }
}
valueTypes getIcoeff2Temp(void) {
    return Icoeff2Temp.value;
}
bool setDcoeff1Temp(valueTypes value) {
    if(value.val_float >= Dcoeff1Temp.valueAbsMax.val_float ||
       value.val_float <= Dcoeff1Temp.valueAbsMin.val_float) {
       return false;
    } else {
        Dcoeff1Temp.value = value;
        return true;
    }
}
valueTypes getDcoeff1Temp(void) {
    return Dcoeff1Temp.value;
}
bool setDcoeff2Temp(valueTypes value) {
    if(value.val_float >= Dcoeff2Temp.valueAbsMax.val_float ||
       value.val_float <= Dcoeff2Temp.valueAbsMin.val_float) {
       return false;
    } else {
        Dcoeff2Temp.value = value;
        return true;
    }
}

valueTypes getDcoeff2Temp(void) {
    return Dcoeff2Temp.value;
}


bool setPcoeff1Freq(valueTypes value) {
    if(value.val_float >= Pcoeff1Freq.valueAbsMax.val_float ||
       value.val_float <= Pcoeff1Freq.valueAbsMin.val_float) {
       return false;
    } else {
        Pcoeff1Freq.value = value;
        return true;
    }
}
valueTypes getPcoeff1Freq(void) {
    return Pcoeff1Freq.value;
}
bool setPcoeff2Freq(valueTypes value) {
    if(value.val_float >= Pcoeff2Freq.valueAbsMax.val_float ||
       value.val_float <= Pcoeff2Freq.valueAbsMin.val_float) {
       return false;
    } else {
        Pcoeff2Freq.value = value;
        return true;
    }
}
valueTypes getPcoeff2Freq(void) {
    return Pcoeff2Freq.value;
}
bool setIcoeff1Freq(valueTypes value) {
    if(value.val_float >= Icoeff1Freq.valueAbsMax.val_float ||
       value.val_float <= Icoeff1Freq.valueAbsMin.val_float) {
       return false;
    } else {
        Icoeff1Freq.value = value;
        return true;
    }
}
valueTypes getIcoeff1Freq(void) {
    return Icoeff1Freq.value;
}
bool setIcoeff2Freq(valueTypes value) {
    if(value.val_float >= Icoeff2Freq.valueAbsMax.val_float ||
       value.val_float <= Icoeff2Freq.valueAbsMin.val_float) {
       return false;
    } else {
        Icoeff2Freq.value = value;
        return true;
    }
}
valueTypes getIcoeff2Freq(void) {
    return Icoeff2Freq.value;
}
bool setDcoeff1Freq(valueTypes value) {
    if(value.val_float >= Dcoeff1Freq.valueAbsMax.val_float ||
       value.val_float <= Dcoeff1Freq.valueAbsMin.val_float) {
       return false;
    } else {
        Dcoeff1Freq.value = value;
        return true;
    }
}
valueTypes getDcoeff1Freq(void) {
    return Dcoeff1Freq.value;
}
bool setDcoeff2Freq(valueTypes value) {
    if(value.val_float >= Dcoeff2Freq.valueAbsMax.val_float ||
       value.val_float <= Dcoeff2Freq.valueAbsMin.val_float) {
       return false;
    } else {
        Dcoeff2Freq.value = value;
        return true;
    }
}

valueTypes getDcoeff2Freq(void) {
    return Dcoeff2Freq.value;
}


bool setI1Set(valueTypes value) {
    if(value.val_float >= I1Set.valueAbsMax.val_float ||
       value.val_float <= I1Set.valueAbsMin.val_float) {
       return false;
    } else {
       I1Set.value = value;
       return true;
    }
}
valueTypes getI1Set(void) {
    return I1Set.value;
}
bool setI2Set(valueTypes value) {
    if(value.val_float >= I2Set.valueAbsMax.val_float ||
       value.val_float <= I2Set.valueAbsMin.val_float) {
       return false;
    } else {
       I2Set.value = value;
       return true;
    }
}
valueTypes getI2Set(void) {
    return I2Set.value;
}

bool setGate1A_OnOff(valueTypes value) {
	Gate1A_OnOff.value = value;
    return true;
}
valueTypes getGate1A_OnOff(void) {
    return Gate1A_OnOff.value;
}
bool setGate1B_OnOff(valueTypes value) {
    Gate1B_OnOff.value = value;
    return true;
}
valueTypes getGate1B_OnOff(void) {
    return Gate1B_OnOff.value;
}
bool setGate2A_OnOff(valueTypes value) {
	Gate2A_OnOff.value = value;
    return true;
}
valueTypes getGate2A_OnOff(void) {
    return Gate2A_OnOff.value;
}
bool setGate2B_OnOff(valueTypes value) {
    Gate2B_OnOff.value = value;
    return true;
}
valueTypes getGate2B_OnOff(void) {
    return Gate2B_OnOff.value;
}

bool setGateH1A(valueTypes value) {
	GateH1A.value = value;
	HAL_GPIO_WritePin(GateH1_A_GPIO_Port, GateH1_A_Pin, !value.val_bool);
    return true;
}
valueTypes getGateH1A(void) {
    return GateH1A.value;
}
bool setGateH1B(valueTypes value) {
    GateH1B.value = value;
    HAL_GPIO_WritePin(GateH1_B_GPIO_Port, GateH1_B_Pin, !value.val_bool);
    return true;
}
valueTypes getGateH1B(void) {
    return GateH1B.value;
}
bool setGateH2A(valueTypes value) {
	GateH2A.value = value;
	HAL_GPIO_WritePin(GateH2_A_GPIO_Port, GateH2_A_Pin, !value.val_bool);
    return true;
}
valueTypes getGateH2A(void) {
    return GateH2A.value;
}
bool setGateH2B(valueTypes value) {
    GateH2B.value = value;
    HAL_GPIO_WritePin(GateH2_B_GPIO_Port, GateH2_B_Pin, !value.val_bool);
    return true;
}
valueTypes getGateH2B(void) {
    return GateH2B.value;
}

bool setPWM_CH1(valueTypes value) {
    if(value.val_float >= PWM_CH1.valueAbsMax.val_float ||
       value.val_float <= PWM_CH1.valueAbsMin.val_float) {
       return false;
    } else {
        PWM_CH1.value = value;
        return true;
    }
}
valueTypes getPWM_CH1(void) {
    return PWM_CH1.value;
}

bool setPWM_CH2(valueTypes value) {
    if(value.val_float >= PWM_CH2.valueAbsMax.val_float ||
       value.val_float <= PWM_CH2.valueAbsMin.val_float) {
       return false;
    } else {
    	PWM_CH1.value = value;
        return true;
    }
}
valueTypes getPWM_CH2(void) {
    return PWM_CH2.value;
}

bool setCH1_Polarity(valueTypes value) {
	CH1_Polarity.value = value;
	return true;
}

valueTypes getCH1_Polarity() {
	return CH1_Polarity.value;
}

bool setCH2_Polarity(valueTypes value) {
	CH2_Polarity.value = value;
	return true;
}

valueTypes getCH2_Polarity() {
	return CH2_Polarity.value;
}

bool setFreq(valueTypes value) {
   Freq.value = value;
   return true;
}
valueTypes getFreq() {
    return Freq.value;
}


void commandParamList() {
	for(int i = 0; i < PARAMS_COUNT; i++) {
		if(params[i] == 0) {
			continue;
		} else {
			sprintf(TXbuffer, "%u:%s:%s", params[i]->commandNumber, typeNames[params[i]->type], params[i]->commandDescription);
			UARTtransmit(TXbuffer);
		}
	}
	return;
}


