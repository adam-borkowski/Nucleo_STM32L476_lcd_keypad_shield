/*
 * hd44780.h
 *
 *  Created on: 5 lis 2016
 *      Author: adam.borkowski
 */

#ifndef HD44780_H_
#define HD44780_H_

#include "stdint.h"

int8_t char_lcd_init(void);
int8_t char_lcd_write_string(uint8_t * string, uint8_t row, uint8_t column);

#endif /* HD44780_H_ */
