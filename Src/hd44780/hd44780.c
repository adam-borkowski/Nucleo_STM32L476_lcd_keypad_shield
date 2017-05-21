/*
 * hd44780.c
 *
 *  Created on: 5 lis 2016
 *      Author: adam.borkowski
 */

#include "hd44780.h"
#include "hd44780_hal.h"


#define CHAR_LCD_INSTRUCTION_REGISTER 0
#define CHAR_LCD_DATA_REGISTER 1
#define CHAR_LCD_READ 1
#define CHAR_LCD_WRITE 0

#define FIRST_ROW_ADDRESS  0x80
#define SECOND_ROW_ADDRESS 0xC0
#define THIRD_ROW_ADDRESS  0x94
#define FOURTH_ROW_ADDRESS 0xD4

/* RS */
static int8_t char_lcd_registers_select(uint8_t data_command_switch);

/* RW */
static int8_t char_lcd_read_write_select(uint8_t read_write_switch);

/* En */
static int8_t char_lcd_read_write_start(uint8_t enable_switch);

/* D4..D7 */
static int8_t char_lcd_4b_write(uint8_t data);
static int8_t char_lcd_4b_read(uint8_t *data);

static int8_t char_lcd_write(uint8_t data, uint8_t data_command_switch);
static int8_t char_lcd_read(uint8_t data);
static int8_t char_lcd_read_busy_flag(void);

static int8_t char_lcd_registers_select(uint8_t data_command_switch) {
	if (data_command_switch == 1) {
		/* Select data register */
		set_r_s_pin(CHAR_LCD_DATA_REGISTER);
	} else if (data_command_switch == 0) {
		/* Select instruction register or read busy flag */
		set_r_s_pin(CHAR_LCD_INSTRUCTION_REGISTER);
	} else {
		/* Wrong value*/
		return -1;
	}
	return 0;
}

static int8_t char_lcd_read_write_select(uint8_t read_write_switch) {
	if (read_write_switch == 1) {
		/* Read operation */
		set_r_w_pin(CHAR_LCD_READ);
	} else if (read_write_switch == 0) {
		/* Write operation */
		set_r_w_pin(CHAR_LCD_WRITE);
	} else {
		/* Wrong value*/
		return -1;
	}
	return 0;
}

static int8_t char_lcd_read_write_start(uint8_t enable_switch) {
	if (enable_switch == 0) {
		/* Disable */
		set_enable_pin(0);
	} else if (enable_switch == 1) {
		/* Enable */
		set_enable_pin(1);
	} else {
		/* Wrong value*/
		return -1;
	}
	return 0;
}


static int8_t char_lcd_4b_write(uint8_t data)
{
	uint8_t temp_data = data;
	temp_data &= 0x0F;
	configure_as_output();
	write_nibble(temp_data);
	char_lcd_read_write_start(1);
//	delay();
	char_lcd_read_write_start(0);

	return 0;
}

static int8_t char_lcd_4b_read(uint8_t *data)
{
	uint8_t temp_data = 0;
	configure_as_input();
	temp_data = read_nibble();
	*data |= (temp_data & 0x0F);
	return 0;
}

static int8_t char_lcd_read(uint8_t data_command_switch)
{
	uint8_t data = 0;
	char_lcd_registers_select(data_command_switch);
	char_lcd_read_write_select(CHAR_LCD_READ);
	set_enable_pin(1);
	char_lcd_4b_read(&data);
	data = data << 4;
	set_enable_pin(0);
	set_enable_pin(1);
	char_lcd_4b_read(&data);
	set_enable_pin(0);
	return data;
}


static int8_t char_lcd_write(uint8_t data, uint8_t data_command_switch)
{
	int8_t busy = 0;
	char_lcd_registers_select(data_command_switch);
	char_lcd_read_write_select(CHAR_LCD_WRITE);
	set_enable_pin(1);
	char_lcd_4b_write(data>>4);
	set_enable_pin(0);
	set_enable_pin(1);
	char_lcd_4b_write(data & 0x0F);
	set_enable_pin(0);
//	HAL_Delay(1);
	do{
		busy = char_lcd_read_busy_flag();
//		HAL_Delay(1);
	}while(busy == 1);

	return 0;
}

/** @return 0 - Display is ready for instruction, 1 - busy */
static int8_t char_lcd_read_busy_flag(void)
{
//	uint8_t temp_data = 0;
//	temp_data = char_lcd_read(CHAR_LCD_INSTRUCTION_REGISTER);
//	temp_data >>= 7;
//	temp_data &= 0x01;
//	return temp_data;
	HAL_Delay(10);
}

int8_t char_lcd_init(void)
{
	HAL_Delay(15);
	/* Write 0x03 instruction 3 times then 0x02 to switch to 4-bit mode */
	for(uint8_t i = 0; i<3; i++)
	{
		set_enable_pin(1);
		char_lcd_4b_write(0x03);
		set_enable_pin(0);
		HAL_Delay(5); //FIXME: Should wait more than 4.1ms
	}

	set_enable_pin(1);
	char_lcd_4b_write(0x02);
	set_enable_pin(0);
	HAL_Delay(2); // FIXME: Should wait for 1ms

	/* Function Set */
	char_lcd_write(0x28, CHAR_LCD_INSTRUCTION_REGISTER);

	/* Display Off */
	char_lcd_write(0x08, CHAR_LCD_INSTRUCTION_REGISTER);

	/* Display Clear */
	char_lcd_write(0x01, CHAR_LCD_INSTRUCTION_REGISTER);

	/* Entry Mode Set */
	char_lcd_write(0x06, CHAR_LCD_INSTRUCTION_REGISTER);

	/* Display On */
	char_lcd_write(0x0F, CHAR_LCD_INSTRUCTION_REGISTER);

	return 0;
}

int8_t char_lcd_write_string(uint8_t * string, uint8_t row, uint8_t column)
{
	uint8_t i = 0;

	if (row == 1)
	{
		char_lcd_write(FIRST_ROW_ADDRESS + column, CHAR_LCD_INSTRUCTION_REGISTER); //Set cursor at the first line
	}
	else if (row == 2)
	{
		char_lcd_write(SECOND_ROW_ADDRESS + column, CHAR_LCD_INSTRUCTION_REGISTER); //Set cursor at the second line
	}
	else if (row == 3)
	{
		char_lcd_write(THIRD_ROW_ADDRESS + column, CHAR_LCD_INSTRUCTION_REGISTER); //Set cursor at the second line
	}
	else if (row == 4)
	{
		char_lcd_write(FOURTH_ROW_ADDRESS + column, CHAR_LCD_INSTRUCTION_REGISTER); //Set cursor at the second line
	}

	for (i = 0; i<strlen(string); i++)
	{
		char_lcd_write(string[i], CHAR_LCD_DATA_REGISTER);
	}
	return -1;
}
