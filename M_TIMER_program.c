/*
 * M_TIMER_program.c
 *
 *  Created on: Aug 10, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"


#include "m_timer_register.h"
#include "m_timer_private.h"
#include "m_timer_config.h"
#include "m_timer_interface.h"
static void (*g_pf)(void) = NULL_PTR ;
/************************************************************************************************
 *                                   Function Definition                                        *
 ************************************************************************************************/
/*
 * Function to Initialize Timer0
 */
void M_TIMER0_voidInit(const TIMER0_Config *timer_config){

	/* Initial value of Timer register */
	TCNT0 = timer_config->TCNT0_value;
	SET_BIT(TCCR0,TCCR0_FOC0);

	/* Configure WGM00 WGM01 of mode */
	TCCR0 = (TCCR0 & 0xBF) |  ((timer_config->timer0_mode & 0x01)<< TCCR0_WGM00) ;
	TCCR0 = (TCCR0 & 0xF7) |  ((timer_config->timer0_mode & 0x02)<< TCCR0_WGM01) ;

	/* Configure CS00 ~ CS02 for prescaler */
	TCCR0= (TCCR0 & 0xF8) | (timer_config->select_prescaler & 0x07);

	if(timer_config->timer0_mode == TIMER0_CTC_MODE){
		OCR0 = timer_config->OCR_value;
		SET_BIT(TIMSK,TIMSK_OCIE0);
		/* Select CTC mode  */
		TCCR0 |= ((timer_config->CTC_nonPWM_mode <<4) & 0x3);
		if(timer_config->CTC_nonPWM_mode != TIMER0_NORMAL_OP){
		//	MDIO_voidSetPinDirection(T0_ENABLE_PORT_ID, T0_ENABLE_PIN_ID, DIO_OUTPUT);
		}
	}
	else{
		/* Enable interrupt */
		SET_BIT(TIMSK,TIMSK_TOIE0);
	}
}

void M_TIMER0_voidDisable(void){
	/* Select PRESCALER as No_Clk */
	CLEAR_BIT(TCCR0 , TCCR0_CS00);
	CLEAR_BIT(TCCR0 , TCCR0_CS01);
	CLEAR_BIT(TCCR0 , TCCR0_CS02);
}
void M_TIMER0_voidSetPreLoad(u8 preload){
	TCNT0 = preload;
}
void M_TIMER0_voidSetOcrValue(u8  ocr_val){
	OCR0 = ocr_val;
}

void M_TIMER0_voidSetCallBack(void(*a_ptr)(void)){
	g_pf = a_ptr;
}
void M_TIMER0_voidSelectPrescaler(TIMER0_PRESCALER value){
	/* Configure CS00 ~ CS02 for prescaler */
	TCCR0= (TCCR0 & 0xF8) | (value & 0x07);
}

/*************************** Set ISR ********************************/

void __vector_11(void)       __attribute__((signal));
void __vector_11(void){
	if(g_pf != NULL_PTR ){
		(*g_pf)();
	}
}

void __vector_10(void)       __attribute__((signal));

void __vector_10(void){
	if(g_pf != NULL_PTR ){
		(*g_pf)();
	}
}
