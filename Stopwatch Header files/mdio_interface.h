/********************************************************************************
   * Author: Mostafa Ibrahim                                                      *
 * Layer: MCAL                                                                  *
 * Module: DIO                                                                  *
 * Version: 1.00                                                                *
 * Date: 8/2/2023                                                               *
 ********************************************************************************/
#ifndef _MDIO_INTERFACE_H_
#define _MDIO_INTERFACE_H_

#define DIO_OUTPUT     1
#define DIO_INPUT      0

#define DIO_HIGH       1
#define DIO_LOW        0

#define DIO_PORTA      1
#define DIO_PORTB      2
#define DIO_PORTC      3
#define DIO_PORTD      4

#define DIO_PIN0       0
#define DIO_PIN1       1
#define DIO_PIN2       2
#define DIO_PIN3       3
#define DIO_PIN4       4
#define DIO_PIN5       5
#define DIO_PIN6       6
#define DIO_PIN7       7

#define MAX_PINS       7

#define PORT_OUTPUT    0xFF
#define PORT_INPUT     0x00

typedef enum{
	Return_Ok,
	Return_Nok,
	Return_NullPointer
}Error_State_t;
void Port_voidInit(void);

void MDIO_voidSetPinDirection(u8 Copy_u8port,u8 Copy_u8pin,u8 Copy_u8Mode);
Error_State_t MDIO_errorStateSetPinValue(u8 Copy_u8port,u8 Copy_u8pin,u8 Copy_u8Mode);
Error_State_t MDIO_errorStateSetPortValue(u8 Copy_u8port,u8 Copy_u8Mode);
Error_State_t MDIO_errorStateGetPinValue(u8 Copy_u8port,u8 Copy_u8pin,u8 *P_u8Value);
Error_State_t MDIO_errorStateGetPortValue(u8 Copy_u8port,u8 *P_u8Value);








#endif
