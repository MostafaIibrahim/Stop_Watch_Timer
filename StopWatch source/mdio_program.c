/********************************************************************************
 * Author: Mostafa Ibrahim                                                      *
 * Layer: MCAL                                                                  *
 * Module: DIO                                                                  *
 * Version: 1.00                                                                *
 * Date: 8/2/2023                                                               *
 ********************************************************************************/
#include "STD_Types.h"
#include "common_macros.h"

#include "mdio_interface.h"
#include "mdio_private.h"
#include "mdio_config.h"
#include "mdio_registers.h"

void Port_voidInit(void){

	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;

	PORTA = PORTA_VALUE;
	PORTB = PORTB_VALUE;
	PORTC = PORTC_VALUE;
	PORTD = PORTD_VALUE;
}


void MDIO_voidSetPinDirection(u8 Copy_u8port,u8 Copy_u8pin,u8 Copy_u8Mode){

	if(Copy_u8Mode == DIO_OUTPUT)
	{
		switch(Copy_u8port)
		{
		case DIO_PORTA: SET_BIT(DDRA,Copy_u8pin); break;
		case DIO_PORTB: SET_BIT(DDRB,Copy_u8pin); break;
		case DIO_PORTC: SET_BIT(DDRC,Copy_u8pin); break;
		case DIO_PORTD: SET_BIT(DDRD,Copy_u8pin); break;
		default: break;
		}
	}
	else if(Copy_u8Mode == DIO_INPUT)
	{
		switch(Copy_u8port)
		{
		case DIO_PORTA: CLEAR_BIT(DDRA,Copy_u8pin); break;
		case DIO_PORTB: CLEAR_BIT(DDRB,Copy_u8pin); break;
		case DIO_PORTC: CLEAR_BIT(DDRC,Copy_u8pin); break;
		case DIO_PORTD: CLEAR_BIT(DDRD,Copy_u8pin); break;
		default: break;
		}
	}

}
Error_State_t MDIO_errorStateSetPinValue(u8 Copy_u8port,u8 Copy_u8pin,u8 Copy_u8Mode){
	Error_State_t Error_state = Return_Ok;
	if(Copy_u8pin > MAX_PINS ){
		Error_state = Return_Nok;
	}
	else{
		if(Copy_u8Mode == DIO_HIGH)
		{
			switch(Copy_u8port)
			{
			case DIO_PORTA: SET_BIT(PORTA,Copy_u8pin); break;
			case DIO_PORTB: SET_BIT(PORTB,Copy_u8pin); break;
			case DIO_PORTC: SET_BIT(PORTC,Copy_u8pin); break;
			case DIO_PORTD: SET_BIT(PORTD,Copy_u8pin); break;
			default: Error_state = Return_Nok; break;
			}
		}
		else if(Copy_u8Mode == DIO_LOW)
		{
			switch(Copy_u8port)
			{
			case DIO_PORTA: CLEAR_BIT(PORTA,Copy_u8pin); break;
			case DIO_PORTB: CLEAR_BIT(PORTB,Copy_u8pin); break;
			case DIO_PORTC: CLEAR_BIT(PORTC,Copy_u8pin); break;
			case DIO_PORTD: CLEAR_BIT(PORTD,Copy_u8pin); break;
			default: Error_state = Return_Nok; break;
			}
		}

	}
	return Error_state;
}
Error_State_t MDIO_errorStateSetPortValue(u8 Copy_u8port,u8 Copy_u8Mode){
	Error_State_t Error_state = Return_Ok;
		switch(Copy_u8port)
		{
		case DIO_PORTA: PORTA = Copy_u8Mode; break;
		case DIO_PORTB: PORTB = Copy_u8Mode; break;
		case DIO_PORTC: PORTC = Copy_u8Mode; break;
		case DIO_PORTD: PORTD = Copy_u8Mode; break;
		default: Error_state = Return_Nok; break;
		}

	return Error_state;
}
Error_State_t MDIO_errorStateGetPinValue(u8 Copy_u8port,u8 Copy_u8pin,u8 *P_u8Value){
	Error_State_t Error_state = Return_Ok;
	if(Copy_u8pin > MAX_PINS ){
		Error_state = Return_Nok;
	}
	else{
		switch(Copy_u8port)
		{
		case DIO_PORTA: *P_u8Value = GET_BIT(PINA,Copy_u8pin); break;
		case DIO_PORTB: *P_u8Value = GET_BIT(PINB,Copy_u8pin); break;
		case DIO_PORTC: *P_u8Value = GET_BIT(PINC,Copy_u8pin); break;
		case DIO_PORTD: *P_u8Value = GET_BIT(PIND,Copy_u8pin); break;
		default: Error_state = Return_NullPointer ; break;
		}
	}
	return Error_state;
}
Error_State_t MDIO_errorStateGetPortValue(u8 Copy_u8port,u8 *P_u8Value){
	Error_State_t Error_state = Return_Ok;
	switch(Copy_u8port)
	{
	case DIO_PORTA: *P_u8Value = PINA; break;
	case DIO_PORTB: *P_u8Value = PINB; break;
	case DIO_PORTC: *P_u8Value = PINC; break;
	case DIO_PORTD: *P_u8Value = PIND; break;
	default: Error_state = Return_NullPointer ; break;
	}
	return Error_state;
}
