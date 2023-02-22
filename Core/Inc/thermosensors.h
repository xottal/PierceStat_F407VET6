/*
 * thermosensors.h
 *
 *  Created on: Jan 29, 2023
 *      Author: xottal
 */

#ifndef INC_THERMOSENSORS_H_
#define INC_THERMOSENSORS_H_

#include <stdint.h>



float getTemp3455(float rawData);

float getTempPt1000(float rawData);

#endif /* INC_THERMOSENSORS_H_ */
