/*
 * menu.h
 *
 *  Created on: Jul 2, 2017
 *      Author: adam
 */

#ifndef MENU_MENU_H_
#define MENU_MENU_H_

#include "stdint.h"

typedef struct menu_item{
	uint8_t* item_text;
	struct menu_item* next;
	struct menu_item* prev;
	struct menu_item* back;
	struct menu_item* submenu;
	void (*menu_callback)(void);
}menu_item_t;

void menu_operation(uint8_t key);


#endif /* MENU_MENU_H_ */
