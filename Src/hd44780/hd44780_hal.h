/*
 * hd44780_hal.h
 *
 *  Created on: 9 lis 2016
 *      Author: adam.borkowski
 */

#ifndef HD44780_HAL_H_
#define HD44780_HAL_H_

#include "stdint.h"
#include "stm32l4xx_hal.h"

void configure_as_output(void);
void configure_as_input(void);
void set_enable_pin(uint8_t state);
void set_r_w_pin(uint8_t state);
void set_r_s_pin(uint8_t state);
uint8_t read_nibble(void);
void write_nibble(uint8_t nible);

#endif /* HD44780_HAL_H_ */
