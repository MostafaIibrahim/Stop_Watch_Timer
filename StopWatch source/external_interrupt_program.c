/*
 * external_interrupt_program.c
 *
 *  Created on: Aug 8, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"

#include "external_interrupt_registers.h"
#include "external_interrupt_private.h"
#include "external_interrupt_config.h"
#include "external_interrupt_interface.h"

static void (*g_ptr_INT[3])(void) = {NULL_PTR};

/* CREATE ISR OR EVERY EXTERNAL INTERRUPT */
void __vector_1(void)   __attribute__((signal));
void __vector_1(void){
	if(g_ptr_INT[0] != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		g_ptr_INT[0]();
	}
}

void __vector_2(void)   __attribute__((signal));
void __vector_2(void){
	if(g_ptr_INT[1] != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		g_ptr_INT[1]();
	}
}
void __vector_3(void)   __attribute__((signal));
void __vector_3(void){
	if(g_ptr_INT[2] != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		g_ptr_INT[2]();
	}
}

/***********************************FUNCTION DEFINITION*****************************************/
/*
 * DESCRIPTION: Function to Initialize external interrupt driver
 * Input: Pointer to structure to configure driver
 * Return: void
 */
void EXTERNAL_INTERRUPT_init(EXTERNAL_INTERRUPT_Config* config){
#ifdef    EXINT_0
		SET_BIT(GICR,GICR_INT0);
		MCUCR &=  0b11111100;
		MCUCR |= (config->INT0_1_CONTROL << 0);
#endif
#ifdef    EXINT_1
		SET_BIT(GICR,GICR_INT1);
		MCUCR &=  0b11110011;
		MCUCR |= (config->INT0_1_CONTROL<<2);
#endif
#ifdef    EXINT_2
		SET_BIT(GICR,GICR_INT2);
		MCUCSR |= (config->INT2_CONTROL<<6);
#endif
}

void EXTERNAL_INTERRUPT_SetCallBack(void (*fPtr[3])(void)) {
	if(fPtr[0] != NULL_PTR){
		g_ptr_INT[0] = fPtr[0];
	}
	if(fPtr[1] != NULL_PTR){
		g_ptr_INT[1] = fPtr[1];
	}
	if(fPtr[2] != NULL_PTR){
		g_ptr_INT[2] = fPtr[2];
	}
}

