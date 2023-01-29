/*
 * UARTCommunication.c
 *
 *  Created on: 18 янв. 2023 г.
 *      Author: xottal
 */

#include "UARTCommunication.h"

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

void UARTtransmit(char* string) {
	uint16_t size = sprintf(TXbuffer, "%s%c",string, EOL);
	HAL_UART_Transmit(&huart1, TXbuffer, size, TXtimeout);
}

bool UARTget(uint16_t com) {
	if(params[paramTable[com]-1]->get) {
		valueTypes value = params[paramTable[com]-1]->get();
		switch(params[paramTable[com]-1]->type) {
		case UINT8_T:
			sprintf(TXbuffer, "$%u:%u",com, value.val_uint8_t);
			UARTtransmit(TXbuffer);
			break;
		case UINT16_T:
				sprintf(TXbuffer, "$%u:%u",com,value.val_uint16_t);
				UARTtransmit(TXbuffer);
				break;
		case UINT32_T:
				sprintf(TXbuffer, "$%u:%u",com, value.val_uint32_t);
				UARTtransmit(TXbuffer);
				break;
		case INT8_T:
				sprintf(TXbuffer, "$%u:%d",com, value.val_int8_t);
				UARTtransmit(TXbuffer);
				break;
		case INT16_T:
				sprintf(TXbuffer, "$%u:%d",com, value.val_int16_t);
				UARTtransmit(TXbuffer);
				break;
		case INT32_T:
				sprintf(TXbuffer, "$%u:%d",com, value.val_int32_t);
				UARTtransmit(TXbuffer);
				break;
		case FLOAT:
				sprintf(TXbuffer, "$%u:%f",com, value.val_float);
				UARTtransmit(TXbuffer);
				break;
		case BOOL:
				sprintf(TXbuffer, "$%u:%s",com, value.val_bool ? "true" : "false");
				UARTtransmit(TXbuffer);
				break;
		}
		return true;
	}
	else {
		UARTtransmitNum(com, "Error\%no get function");
		return false;
	}
}

bool UARTset(uint16_t com, char* str) {
	if(!params[paramTable[com]-1]->set) {
		UARTtransmitNum(com, "Error\%no set function");
		return false;
	} else if(params[paramTable[com]-1]->readOnly) {
		UARTtransmitNum(com, "Error\%read only");
		return false;
	}
	valueTypes value;
	switch(params[paramTable[com] - 1]->type) {
	case UINT8_T:
		sscanf(str, "%u", &value);
		break;
	case UINT16_T:
		sscanf(str, "%u", &value);
		break;
	case UINT32_T:
		sscanf(str, "%u", &value);
		break;
	case INT8_T:
		sscanf(str, "%d", &value);
		break;
	case INT16_T:
		sscanf(str, "%d", &value);
		break;
	case INT32_T:
		sscanf(str, "%d", &value);
		break;
	case FLOAT:
		sscanf(str, "%f", &value);
		break;
	case BOOL:
		value = (valueTypes)(bool)!strcmp(str, "true");
		break;
	}
	bool setRes = params[paramTable[com]-1]->set((valueTypes)value);
	sprintf(TXbuffer, "$%u:%s",com, setRes ? "Y" : "N");
	UARTtransmit(TXbuffer);
	return setRes;
}

void UARTtransmitNum(int com, char* string) {
	sprintf(TXbuffer, "%d:%s",com, string);
	UARTtransmit(TXbuffer);
}

void commandSearch() {
//TODO

	char** commands;
	commands = str_split(RXbufferLong, delim);
	if (commands)
	{
		int i;
		for (i = 0; *(commands + i); i++)
		{
			char* command = *(commands + i);
			sprintf(TXbuffer, "command%d=[%s]",i, command);
			UARTtransmit(TXbuffer); // echo
			if(strlen(command) < 5) {
				UARTtransmit("Error\%invalid command style");
			} else if(!strcmp(command, "*IDN?")) {
				UARTtransmit(IDNstring);
			} else if(command[0] == '$') {
				char attr[10];
				int com;
				sscanf(&command[1], "%d%s", &com, attr);
				if(com < 100 || com > PARAMS_RANGE - 1) {
					UARTtransmitNum(com,"Error\%invalid command");
				}
				else if(!params[paramTable[com]-1])
				{
					UARTtransmitNum(com,"Error\%invalid parameter");
				}
				else if(attr[0] == '?') {
					if(params[paramTable[com]-1]->isCommand) {
						params[paramTable[com]-1]->command();
					}
					else  {
						UARTget(com);
					}
				}
				else if (attr[0] == ':') {
					UARTset(com, &attr[1]);
				}
				else {
					UARTtransmitNum(com, "Error\%invalid command style");
				}
			} else {
				UARTtransmit("Error\%invalid command style");
			}

			free(*(commands + i));
		}
		printf("\n");
		free(commands);
	}
}
