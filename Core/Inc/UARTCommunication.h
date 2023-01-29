/*
 * UARTCommunication.h
 *
 *  Created on: 18 янв. 2023 г.
 *      Author: xottal
 */

#ifndef INC_UARTCOMMUNICATION_H_
#define INC_UARTCOMMUNICATION_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Parameters.h"
#include "stm32f4xx_hal.h"

char** str_split(char* a_str, const char a_delim);
void UARTtransmit(char* string);
void UARTtransmitNum(int com, char* string);
bool UARTget(uint16_t com);
bool UARTset(uint16_t com, char* str);
void commandSearch();

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

extern char IDNstring[];
extern UART_HandleTypeDef huart1;

extern uint8_t RXbufferChar[1];


#endif /* INC_UARTCOMMUNICATION_H_ */
