/*
 * menu.c
 *
 *  Created on: Jul 2, 2017
 *      Author: adam
 */
#include "menu.h"
#include "keypad.h"

menu_item_t main_menu;
menu_item_t leds_menu;
menu_item_t relays_menu;

void menu_operation(uint8_t key)
{
	switch (key) {
		case KEY_RIGHT: 	/// Enter submenu or action
			break;
		case KEY_LEFT:		// Exit from submenu
			break;
		case KEY_UP:		// Previous menu item
			break;
		case KEY_DOWN:		// Next menu item
			break;
		case KEY_SELECT:	// Currently not used (not working on LCD shield)
			break;
		default:
			break;
	}
}
