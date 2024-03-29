/*
 * UARTComms.h
 *
 *  Created on: 17 янв. 2023 г.
 *      Author: xottal
 */

#ifndef INC_PARAMETERS_H_
#define INC_PARAMETERS_H_

#define PARAMS_COUNT 100
#define PARAMS_RANGE 1000

#include <stdint.h>
#include <stdbool.h>
#include "UARTCommunication.h"

typedef enum {UINT8_T, UINT16_T, UINT32_T, INT8_T, INT16_T, INT32_T, FLOAT, BOOL} types;

typedef union {
    uint8_t val_uint8_t;
    uint16_t val_uint16_t;
    uint32_t val_uint32_t;
    int8_t val_int8_t;
    int16_t val_int16_t;
    int32_t val_int32_t;
    float val_float;
    bool val_bool;
    uint16_t flashType[2];
} valueTypes;

typedef struct {
    uint16_t commandNumber; //Номер >= 101
    char commandDescription[50]; //Описание для команды $100?
    types type; //Ref to typeList
    bool isCommand; //Является виртуальной командой или хранит значение
    bool readOnly; //Хранимое значение редактируется через UART?
    bool isFlash; //Хранить во flash?
    valueTypes (*get)();
    bool (*set)(valueTypes);
    void (*command)();
    valueTypes value;
    valueTypes valueAbsMin;
    valueTypes valueAbsMax;
} ParStruct;

extern ParStruct* params[PARAMS_COUNT];
extern uint8_t paramTable[PARAMS_RANGE];

void InitParams();

bool setU_HeaterSet(valueTypes value);
valueTypes getU_HeaterSet(void);

bool setU_HeaterMin(valueTypes value);
valueTypes getU_HeaterMin(void);

bool setU_HeaterMax(valueTypes value);
valueTypes getU_HeaterMax(void);

bool setU_HeaterOnOff(valueTypes state);
valueTypes getU_HeaterOnOff(void);

bool setU_24Vmeas(valueTypes value);
valueTypes getU_24Vmeas(void);

bool setU_24Vcoeff(valueTypes value);
valueTypes getU_24Vcoeff(void);

bool setU_HeaterMeas(valueTypes value);
valueTypes getU_HeaterMeas();

bool setU_HeaterCoeff(valueTypes value);
valueTypes getU_HeaterCoeff(void);

bool setU_24V_Min(valueTypes value);
valueTypes getU_24V_Min(void);

bool setU_24V_Max(valueTypes value);
valueTypes getU_24V_Max(void);

bool setI_1A(valueTypes value);
valueTypes getI_1A();
bool setI_1B(valueTypes value);
valueTypes getI_1B();
bool setI_2A(valueTypes value);
valueTypes getI_2A();
bool setI_2B(valueTypes value);
valueTypes getI_2B();

bool setI_1A_Max(valueTypes value);
valueTypes getI_1A_Max(void);
bool setI_1B_Max(valueTypes value);
valueTypes getI_1B_Max(void);
bool setI_2A_Max(valueTypes value);
valueTypes getI_2A_Max(void);
bool setI_2B_Max(valueTypes value);
valueTypes getI_2B_Max(void);

bool setI_1A_Coeff(valueTypes value);
valueTypes getI_1A_Coeff(void);
bool setI_1B_Coeff(valueTypes value);
valueTypes getI_1B_Coeff(void);
bool setI_2A_Coeff(valueTypes value);
valueTypes getI_2A_Coeff(void);
bool setI_2B_Coeff(valueTypes value);
valueTypes getI_2B_Coeff(void);

valueTypes getTemp1();
bool setTemp1(valueTypes value);
valueTypes getTemp2();
bool setTemp2(valueTypes value);
valueTypes getTemp3();
bool setTemp3(valueTypes value);
valueTypes getTemp4();
bool setTemp4(valueTypes value);

bool setTemp1_coeff(valueTypes value);
valueTypes getTemp1_coeff(void);
bool setTemp2_coeff(valueTypes value);
valueTypes getTemp2_coeff(void);
bool setTemp3_coeff(valueTypes value);
valueTypes getTemp3_coeff(void);
bool setTemp4_coeff(valueTypes value);
valueTypes getTemp4_coeff(void);

bool setTemp1_Min(valueTypes value);
valueTypes getTemp1_Min(void);
bool setTemp1_Max(valueTypes value);
valueTypes getTemp1_Max(void);
bool setTemp2_Min(valueTypes value);
valueTypes getTemp2_Min(void);
bool setTemp2_Max(valueTypes value);
valueTypes getTemp2_Max(void);
bool setTemp3_Min(valueTypes value);
valueTypes getTemp3_Min(void);
bool setTemp3_Max(valueTypes value);
valueTypes getTemp3_Max(void);
bool setTemp4_Min(valueTypes value);
valueTypes getTemp4_Min(void);
bool setTemp4_Max(valueTypes value);
valueTypes getTemp4_Max(void);


bool setLoadSelect1(valueTypes state);
valueTypes getLoadSelect1(void);
bool setLoadSelect2(valueTypes state);
valueTypes getLoadSelect2(void);

bool setModeSelect1(valueTypes state);
valueTypes getModeSelect1(void);
bool setModeSelect2(valueTypes state);
valueTypes getModeSelect2(void);

bool setCh1_OnOff(valueTypes state);
valueTypes getCh1_OnOff(void);
bool setCh2_OnOff(valueTypes state);
valueTypes getCh2_OnOff(void);

bool setSourceSelect1(valueTypes state);
valueTypes getSourceSelect1(void);
bool setSourceSelect2(valueTypes state);
valueTypes getSourceSelect2(void);

bool setPcoeff1Temp(valueTypes value);
valueTypes getPcoeff1Temp(void);
bool setPcoeff2Temp(valueTypes value);
valueTypes getPcoeff2Temp(void);
bool setIcoeff1Temp(valueTypes value);
valueTypes getIcoeff1Temp(void);
bool setIcoeff2Temp(valueTypes value);
valueTypes getIcoeff2Temp(void);
bool setDcoeff1Temp(valueTypes value);
valueTypes getDcoeff1Temp(void);
bool setDcoeff2Temp(valueTypes value);
valueTypes getDcoeff2Temp(void);

bool setPcoeff1Freq(valueTypes value);
valueTypes getPcoeff1Freq(void);
bool setPcoeff2Freq(valueTypes value);
valueTypes getPcoeff2Freq(void);
bool setIcoeff1Freq(valueTypes value);
valueTypes getIcoeff1Freq(void);
bool setIcoeff2Freq(valueTypes value);
valueTypes getIcoeff2Freq(void);
bool setDcoeff1Freq(valueTypes value);
valueTypes getDcoeff1Freq(void);
bool setDcoeff2Freq(valueTypes value);
valueTypes getDcoeff2Freq(void);

bool setTempCh1Set(valueTypes value);
valueTypes getTempCh1Set();
bool setTempCh2Set(valueTypes value);
valueTypes getTempCh2Set();

bool setI1Set(valueTypes value);
valueTypes getI1Set(void);
bool setI2Set(valueTypes value);
valueTypes getI2Set(void);

bool setGate1A_OnOff(valueTypes value);
valueTypes getGate1A_OnOff(void);
bool setGate1B_OnOff(valueTypes value);
valueTypes getGate1B_OnOff(void);
bool setGate2A_OnOff(valueTypes value);
valueTypes getGate2A_OnOff(void);
bool setGate2B_OnOff(valueTypes value);
valueTypes getGate2B_OnOff(void);

bool setGateH1A(valueTypes value);
valueTypes getGateH1A(void);
bool setGateH1B(valueTypes value);
valueTypes getGateH1B(void);
bool setGateH2A(valueTypes value);
valueTypes getGateH2A(void);
bool setGateH2B(valueTypes value);
valueTypes getGateH2B(void);

bool setPWM_CH1(valueTypes value);
valueTypes getPWM_CH1(void);
bool setPWM_CH2(valueTypes value);
valueTypes getPWM_CH2(void);
bool setCH1_Polarity(valueTypes value);
valueTypes getCH1_Polarity(void);
bool setCH2_Polarity(valueTypes value);
valueTypes getCH2_Polarity(void);

bool setFreq(valueTypes value);
valueTypes getFreq();
bool setFreqSet(valueTypes value);
valueTypes getFreqSet();

bool setFreqMin(valueTypes value);
valueTypes getFreqMin();
bool setFreqMax(valueTypes value);
valueTypes getFreqMax();

bool setAlarms(valueTypes value);
valueTypes getAlarms();
bool setAlarmMasks(valueTypes value);
valueTypes getAlarmMasks();

void InitParams();
void commandParamList();
void commandSaveFlash();


#endif /* INC_PARAMETERS_H_ */
