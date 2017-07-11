/*
 * keypad.c
 *
 *  Created on: May 21, 2017
 *      Author: Adam
 */

#include "keypad.h"

uint8_t keypad_init(ADC_HandleTypeDef* hadc)
{
	HAL_ADC_Start(hadc);
	return 0;
}
uint16_t keypad_read_key(ADC_HandleTypeDef* hadc)
{
	uint16_t adc_readout = 0;
	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc, 100);
	adc_readout = HAL_ADC_GetValue(hadc);

	if(adc_readout > 700 && adc_readout < 800)
	{
		return KEY_UP;
	}
	else if (adc_readout > 1700 && adc_readout < 1800)
	{
		return KEY_DOWN;
	}
	else if (adc_readout > 2650 && adc_readout < 2750)
	{
		return KEY_LEFT;
	}
	else if (adc_readout >= 0 && adc_readout < 50)
	{
		return KEY_RIGHT;
	}
//	else if (adc_readout > 4050 && adc_readout < 5050)
//	{
//		return KEY_SELECT;  // FIXME: SELECT i NONE maja taki sam odczyt z ADC. HW problem?
//	}

	return KEY_NONE;
}
