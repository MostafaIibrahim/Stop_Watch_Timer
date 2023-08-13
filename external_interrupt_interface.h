/*
 * external_interrupt_interface.h
 *
 *  Created on: Aug 8, 2023
 *      Author: SOFT ZONE
 */

#ifndef EXTERNAL_INTERRUPT_INTERFACE_H_
#define EXTERNAL_INTERRUPT_INTERFACE_H_

typedef enum{
	LOW_LEVEL,ANY_LEVEL,FALLING_EDGE,RISING_EDGE
}INT0_INT1_CONTROL;
typedef enum{
	INT2_FALLING_EDGE,INT2_RISING_EDGE
}INT2_CONTROL;

typedef struct{
	INT0_INT1_CONTROL    INT0_1_CONTROL;
	INT2_CONTROL         INT2_CONTROL;
}EXTERNAL_INTERRUPT_Config;

void EXTERNAL_INTERRUPT_init(EXTERNAL_INTERRUPT_Config* config);
void EXTERNAL_INTERRUPT_SetCallBack(void (*fPtr[3])(void));
#endif /* EXTERNAL_INTERRUPT_INTERFACE_H_ */
