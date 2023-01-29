/*
 * flashManag.c
 *
 *  Created on: Jan 29, 2023
 *      Author: xottal
 */

#include "flashManag.h"
#include "eeprom.h"
#include "Parameters.h"

//EEPROM Emulation
uint16_t VirtAddVarTab[NB_OF_VAR];

void InitVirtAddTab() {
	HAL_FLASH_Unlock();
	EE_Init();
	uint8_t counter = 0;
	for(uint8_t i = 0; i < PARAMS_COUNT; i++) {
		if(params[i]->isFlash == true) {
			VirtAddVarTab[counter] = counter+1;
			VirtAddVarTab[counter+1] = counter+2;
			counter +=2;
		}
	}
}

void ReadFlash() {
	uint8_t counter = 0;
	for(uint8_t i = 0; i < PARAMS_COUNT; i++) {
		if(params[i]->isFlash == true) {
			uint16_t var[2];
			EE_ReadVariable(VirtAddVarTab[counter++], &var[0]);
			EE_ReadVariable(VirtAddVarTab[counter++], &var[1]);
			params[i]->value.flashType[0] = var[0];
			params[i]->value.flashType[1] = var[1];
		}
	}
}


void SaveToFlash() {
	uint8_t counter = 0;
	for(uint8_t i = 0; i < PARAMS_COUNT; i++) {
		if(params[i]->isFlash == true) {
			uint16_t var[2];
			var[0] = params[i]->value.flashType[0];
			var[1] = params[i]->value.flashType[1];
			EE_WriteVariable(VirtAddVarTab[counter++], var[0]);
			EE_WriteVariable(VirtAddVarTab[counter++], var[1]);
		}
	}
}

