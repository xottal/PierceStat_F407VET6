/*
 * PID.h
 *
 *  Created on: Feb 1, 2023
 *      Author: xottal
 */

#ifndef INC_PID_H_
#define INC_PID_H_

float proceedPID(uint8_t channel);
void resetPID(uint8_t channel);
void setPWM();

#endif /* INC_PID_H_ */
