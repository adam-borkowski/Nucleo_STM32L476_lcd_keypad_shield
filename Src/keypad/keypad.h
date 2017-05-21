/*
 * keypad.h
 *
 *  Created on: May 21, 2017
 *      Author: Adam
 */

#ifndef KEYPAD_KEYPAD_H_
#define KEYPAD_KEYPAD_H_

#include "stdint.h"
#include "stm32l4xx_hal.h"

#define KEY_RIGHT  0
#define KEY_UP     1
#define KEY_DOWN   2
#define KEY_LEFT   3
#define KEY_SELECT 4
#define KEY_NONE   5

uint8_t keypad_init(ADC_HandleTypeDef* hadc)
;uint16_t keypad_read_key(ADC_HandleTypeDef* hadc);


#endif /* KEYPAD_KEYPAD_H_ */
