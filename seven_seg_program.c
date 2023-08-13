/*
 * seven_seg_program.c
 *
 *  Created on: Aug 12, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"
#include "mdio_registers.h"
#include "mdio_interface.h"
#include "seven_seg_interface.h"
#include "seven_seg_private.h"
#include "seven_seg_config.h"
#include "util/delay.h"

void SEVEN_SEG_voidDisplay(u8 sec,u8 min,u8 hr){
	PORTA = (PORTA & 0xC0) | (1<<0);        //Enable second
	PORTC = (PORTC & 0xF0) | (sec%10 & 0x0F);
	_delay_ms(2);

	PORTA = (PORTA & 0xC0) | (1<<1);        //Enable second 7-seg of seconds
	PORTC = (PORTC & 0xF0) | (sec/10 & 0x0F);
	_delay_ms(2);

	PORTA = (PORTA & 0xC0) | (1<<2);        //Enable first 7-seg of mins
	PORTC = (PORTC & 0xF0) | (min%10 & 0x0F);
	_delay_ms(2);

	PORTA = (PORTA & 0xC0) | (1<<3);        //Enable second 7-seg of mins
	PORTC = (PORTC & 0xF0) | (min/10 & 0x0F);
	_delay_ms(2);

	PORTA = (PORTA & 0xC0) | (1<<4);        //Enable first 7-seg of hours
	PORTC = (PORTC & 0xF0) | (hr%10 & 0x0F);
	_delay_ms(2);

	PORTA = (PORTA & 0xC0) | (1<<5);        //Enable second 7-seg of hours
	PORTC = (PORTC & 0xF0) | (hr/10 & 0x0F);
	_delay_ms(2);
}
