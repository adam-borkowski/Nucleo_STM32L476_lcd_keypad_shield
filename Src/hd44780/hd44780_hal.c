/*
 * hd44780_hal.c
 *
 *  Created on: 9 lis 2016
 *      Author: adam.borkowski
 */

#include "hd44780_hal.h"
#include "stm32l4xx_hal.h"


void configure_as_output(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	  /*Configure GPIO pins : CHAR_LCD_D4_Pin CHAR_LCD_D5_Pin CHAR_LCD_D6_Pin CHAR_LCD_D7_Pin */
	  GPIO_InitStruct.Pin = LCD_DB4_Pin|LCD_DB5_Pin|LCD_DB6_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_DB7_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void configure_as_input(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	  /*Configure GPIO pins : CHAR_LCD_D4_Pin CHAR_LCD_D5_Pin CHAR_LCD_D6_Pin CHAR_LCD_D7_Pin */
	  GPIO_InitStruct.Pin = LCD_DB4_Pin|LCD_DB5_Pin|LCD_DB6_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_DB7_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

uint8_t read_nibble(void)
{
	uint8_t nible = 0;
	nible |= HAL_GPIO_ReadPin(LCD_DB7_GPIO_Port, LCD_DB7_Pin);
	nible <<= 1;
	nible |= HAL_GPIO_ReadPin(LCD_DB6_GPIO_Port, LCD_DB6_Pin);
	nible <<= 1;
	nible |= HAL_GPIO_ReadPin(LCD_DB5_GPIO_Port, LCD_DB5_Pin);
	nible <<= 1;
	nible |= HAL_GPIO_ReadPin(LCD_DB4_GPIO_Port, LCD_DB4_Pin);
	return nible;
}

void write_nibble(uint8_t nible)
{
	HAL_GPIO_WritePin(LCD_DB4_GPIO_Port, LCD_DB4_Pin, (nible & 0x01));
	nible >>= 1;
	HAL_GPIO_WritePin(LCD_DB5_GPIO_Port, LCD_DB5_Pin, (nible & 0x01));
	nible >>= 1;
	HAL_GPIO_WritePin(LCD_DB6_GPIO_Port, LCD_DB6_Pin, (nible & 0x01));
	nible >>= 1;
	HAL_GPIO_WritePin(LCD_DB7_GPIO_Port, LCD_DB7_Pin, (nible & 0x01));
}
void set_enable_pin(uint8_t state)
{
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, (GPIO_PinState)state);
//	HAL_Delay(1);
}

void set_r_w_pin(uint8_t state)
{
//	HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, (GPIO_PinState)state);
}

void set_r_s_pin(uint8_t state)
{
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, (GPIO_PinState)state);
}
