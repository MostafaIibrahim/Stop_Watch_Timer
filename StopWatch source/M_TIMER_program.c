/*
 * M_TIMER_program.c
 *
 *  Created on: Aug 10, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"

#include "mdio_interface.h"
#include "m_timer_register.h"
#include "m_timer_private.h"
#include "m_timer_config.h"
#include "m_timer_interface.h"
//static  void(*pf_icu)(void) = NULL_PTR;
#ifdef      TIMER0
static void (*g_pf)(void) = NULL_PTR ;
/************************************************************************************************
 *                                   Function Definition                                        *
 ************************************************************************************************/
/*
 * Function to Initialize Timer0
 */

void M_TIMER0_voidInit(const TIMER0_Config *timer_config){
#ifdef PREV
	TCNT0 = timer_config->TCNT0_value ;
	/* Configure Wave generation bits based on user selection */
	if(timer_config->timer0_mode == TIMER0_NORMAL_MODE) {
		CLEAR_BIT(TCCR0,TCCR0_WGM00);
		CLEAR_BIT(TCCR0,TCCR0_WGM01);

		/* Enable Interrupt bit for this mode */
		SET_BIT(TIMSK,TIMSK_TOIE0);
	}
	else if(timer_config->timer0_mode == TIMER0_CTC_MODE){
		CLEAR_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);

		SET_BIT(TIMSK,TIMSK_OCIE0);
		OCR0 = timer_config->OCR_value;
		/* ******************* To configure operation mode********************* */
		if(timer_config->CTC_nonPWM_mode == TIMER0_NORMAL_OP){
			CLEAR_BIT(TCCR0,TCCR0_COM00);
			CLEAR_BIT(TCCR0,TCCR0_COM01);
		}
		else if(timer_config->CTC_nonPWM_mode == TIMER0_TOGGLE_OC0_OP){
			SET_BIT(TCCR0,TCCR0_COM00);
			CLEAR_BIT(TCCR0,TCCR0_COM01);
		}
		else if(timer_config->CTC_nonPWM_mode == TIMER0_CLEAR_OC0_OP){
			CLEAR_BIT(TCCR0,TCCR0_COM00);
			SET_BIT(TCCR0,TCCR0_COM01);
		}
		else if(timer_config->CTC_nonPWM_mode == TIMER0_SET_OC0_OP){
			SET_BIT(TCCR0,TCCR0_COM00);
			SET_BIT(TCCR0,TCCR0_COM01);
		}
	}
	else if(timer_config->timer0_mode == TIMER0_PWM_FAST_MODE){
		SET_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);

		OCR0 = timer_config->OCR_value;
		/* ******************* To configure operation mode********************* */
		if(timer_config->PWM_mode == TIMER0_PWM_NORMAL_OP){
			CLEAR_BIT(TCCR0,TCCR0_COM00);
			CLEAR_BIT(TCCR0,TCCR0_COM01);
		}
		else if(timer_config->PWM_mode == TIMER0_NON_INVERTING_MODE){
			CLEAR_BIT(TCCR0,TCCR0_COM00);
			SET_BIT(TCCR0,TCCR0_COM01);
		}
		else if(timer_config->PWM_mode == TIMER0_INVERTING_MODE){
			SET_BIT(TCCR0,TCCR0_COM00);
			SET_BIT(TCCR0,TCCR0_COM01);
		}
	}
/*   Select prescaler    */
	switch(timer_config->select_prescaler){

	case NO_CLK:    CLEAR_BIT(TCCR0,TCCR0_CS00);
					CLEAR_BIT(TCCR0,TCCR0_CS01);
					CLEAR_BIT(TCCR0,TCCR0_CS02);
					break;
	case NO_PRESC:  SET_BIT(TCCR0,TCCR0_CS00);
					CLEAR_BIT(TCCR0,TCCR0_CS01);
					CLEAR_BIT(TCCR0,TCCR0_CS02);
					break;
	case PRESC_8:   CLEAR_BIT(TCCR0,TCCR0_CS00);
	                SET_BIT(TCCR0,TCCR0_CS01);
					CLEAR_BIT(TCCR0,TCCR0_CS02);
					break;
	case PRESC_64:  SET_BIT(TCCR0,TCCR0_CS00);
	                SET_BIT(TCCR0,TCCR0_CS01);
					CLEAR_BIT(TCCR0,TCCR0_CS02);
					break;
	case PRESC_256:
		            CLEAR_BIT(TCCR0,TCCR0_CS00);
					CLEAR_BIT(TCCR0,TCCR0_CS01);
					SET_BIT(TCCR0,TCCR0_CS02);
					break;
	case PRESC_1024:
	            	SET_BIT(TCCR0,TCCR0_CS00);
					CLEAR_BIT(TCCR0,TCCR0_CS01);
					SET_BIT(TCCR0,TCCR0_CS02);
					break;
	case EXTERNAL_FALLING:
		            CLEAR_BIT(TCCR0,TCCR0_CS00);
		            SET_BIT(TCCR0,TCCR0_CS01);
		            SET_BIT(TCCR0,TCCR0_CS02);
					break;
	case EXTERNAL_RISING:
					SET_BIT(TCCR0,TCCR0_CS00);
					SET_BIT(TCCR0,TCCR0_CS01);
					SET_BIT(TCCR0,TCCR0_CS02);
					break;
	default: break;
	}
#else
	/* Initial value of Timer register */
	TCNT0 = timer_config->TCNT0_value;

	/* Configure WGM00 WGM01 of mode */
	TCCR0 = (TCCR0 & 0xBF) |  ((timer_config->timer0_mode & 0x01)<< TCCR0_WGM00) ;
	TCCR0 = (TCCR0 & 0xF7) |  ((timer_config->timer0_mode & 0x02)<< TCCR0_WGM01) ;

	/* Configure CS00 ~ CS02 for prescaler */
	TCCR0= (TCCR0 & 0xF8) | (timer_config->select_prescaler & 0x07);

	if(timer_config->timer0_mode == TIMER0_CTC_MODE){
		//SET_BIT(TCCR0,TCCR0_FOC0);
		OCR0 = timer_config->OCR_value;
		SET_BIT(TIMSK,TIMSK_OCIE0);
		/* Select CTC mode  */
		TCCR0 |= ((timer_config->CTC_nonPWM_mode <<4) & 0x3);
		if(timer_config->CTC_nonPWM_mode != TIMER0_NORMAL_OP){
			//MDIO_voidSetPinDirection(T0_ENABLE_PORT_ID, T0_ENABLE_PIN_ID, DIO_OUTPUT);
		}
	}
	else if(timer_config->timer0_mode == TIMER0_PWM_FAST_MODE){
		//MDIO_voidSetPinDirection(T0_ENABLE_PORT_ID,T0_ENABLE_PIN_ID,DIO_OUTPUT);
		OCR0 = timer_config->OCR_value;
		TCCR0 |= ((timer_config->PWM_mode <<4) & 0x3);
	}
	else{
		SET_BIT(TCCR0,TCCR0_FOC0);
		/* Enable interrupt */
		SET_BIT(TIMSK,TIMSK_TOIE0);
	}
#endif
}

void M_TIMER0_voidSetDutyCylce(u8 duty_cycle){
	OCR0 = duty_cycle;
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
#endif
#ifdef                     TIMER1

static volatile void (*g_ptr_t1)(void) = NULL_PTR;
/*                                          ISR                                           */

void __vector_7(void)       __attribute__((signal));

void __vector_7(void){
	if(g_ptr_t1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_ptr_t1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
void __vector_8(void)       __attribute__((signal));

void __vector_8(void){
	if(g_ptr_t1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_ptr_t1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

void __vector_9(void)       __attribute__((signal));

void __vector_9(void){
	if(g_ptr_t1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_ptr_t1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*                                   Function Prototype                                      */
/*
 * Description: Function to initialize the Timer driver
 * Input: pointer to the configuration structure with type Timer_ConfigType.
 * Output: None
 */
void M_TIMER1_voidInit(const Timer1_ConfigType * Config_Ptr ,u8 topMode){
#ifdef COUNTER_MODE
	GPIO_setupPinDirection(T1_ENABLE_PORT_ID, T1_ENABLE_PIN_ID, PIN_INPUT);
#endif
	/* Timer1 register initial value */
	TCNT1 = Config_Ptr->initial_value;

	/* Configure Wave generation Form in TCCR1 A & B registers  */
	TCCR1A = (TCCR1A & 0xFC) | (Config_Ptr->timer1_mode & 0x03);
	TCCR1B = (TCCR1B & 0xE7) | ((Config_Ptr->timer1_mode & 0x0C)<<1);

	/* Configure Prescaler  in TCCR1B registers */
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->timer1_prescaler & 0x07);

	if((Config_Ptr->timer1_mode != TIMER1_PWM_FAST_MODE_TOP_OCR1A) && (Config_Ptr->timer1_mode != TIMER1_PWM_FAST_MODE_TOP_ICR1)){
		TCCR1A |= (1<<TCCR1A_FOC1A) | (1<<TCCR1A_FOC1B);
	}

	if((Config_Ptr->timer1_mode == TIMER1_PWM_FAST_MODE_TOP_ICR1) &&(Config_Ptr->timer1_mode == TIMER1_PWM_FAST_MODE_TOP_OCR1A) ){
		if(Config_Ptr->index==TIMER1A)
		{
			GPIO_setupPinDirection(OCR1A_OCR1B_ENABLE_PORT_ID, OCR1A_ENABLE_PIN_ID,DIO_OUTPUT);
		}
		else if(Config_Ptr->index==TIMER1B)
		{
			GPIO_setupPinDirection(OCR1A_OCR1B_ENABLE_PORT_ID, OCR1B_ENABLE_PIN_ID,DIO_OUTPUT);
		}
	}
	if(Config_Ptr->timer1_mode != TIMER1_NORMAL_MODE){
		if(Config_Ptr->index == TIMER1A){
			TCCR1A = (TCCR1A & 0x3F) | ((Config_Ptr->timer1_compare_mode & 0x03)<<6);
			OCR1A = Config_Ptr->compare_value;
			SET_BIT(TIMSK,TIMSK_OCIE1A);
		}
		else if(Config_Ptr->index == TIMER1B){
			TCCR1A=(TCCR1A & 0xCF)|((Config_Ptr->timer1_compare_mode & 0x03)<<4); //set compare match event
			OCR1B=Config_Ptr->compare_value; //define compare value
			SET_BIT(TIMSK,TIMSK_OCIE1B); //enable compare interrupt
		}
	}
	else
	{
		SET_BIT(TIMSK,TIMSK_TOIE1); //enable overflow interrupt
	}
}

void M_TIMER1_voidSetTopValue(u16 topMode){

}
/*
 * Description:Function to disable the Timer.
 * Input: None
 * Output: None
 */
void Timer1_deInit(void){
	TCCR1A = 0 ;
	TCCR1B = 0 ;
	TCNT1 = 0 ;
	OCR1A = 0 ;
	OCR1B = 0 ;
	CLEAR_BIT(TIMSK,TIMSK_OCIE1A);
	CLEAR_BIT(TIMSK,TIMSK_OCIE1B);
	CLEAR_BIT(TIMSK,TIMSK_TOIE1);
}
/*
 * Description: Function to set the Call Back function address.
 * Input: None
 * Output: None
 */
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_ptr_t1 = a_ptr ;
}

void Timer1_pwmAdjust(Timer1_ConfigType *ptr_sturct ,u16 duty_cycle)
{
	duty_cycle  = (u16)(((u16)255*duty_cycle)/100); //define compare value
	ptr_sturct->compare_value = duty_cycle;
}
/*
 * Description: Function to change OCR value for Changing duty cycle
 * Input: Pointer to structure
 * Return: None
 */
void Timer1_changeOcr_value(const Timer1_ConfigType * Config_Ptr){
	if(Config_Ptr->index == TIMER1A){
		OCR1A = Config_Ptr->compare_value;
	}
	else if(Config_Ptr->index == TIMER1B){
		OCR1B = Config_Ptr->compare_value;
	}
}
void Timer1_Pause(void){
	TCCR1B &= 0xF8 ;
}
void Timer1_Resume(TIMER1_PRESCALER prescaler){
	/* Configure Prescaler  in TCCR1B registers */
	TCCR1B = (TCCR1B & 0xF8) | (prescaler & 0x07);
}
void Timer1_Reset(void){
	TCNT1 = 0 ;
}




void M_TIMER1_voidInit(TIMER1_TopMode topMode, TIMER1_Mode  Config_Mode ,TIMER1_Prescaler select_Prescaler){
	/* Timer1 Mode */
	switch(topMode){
	case NORMAL_MODE_WAVE_OXFFFF:
		CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
		CLEAR_BIT(TCCR1A,TCCR1A_WGM11);
		CLEAR_BIT(TCCR1B,TCCR1B_WGM12);
		CLEAR_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TOP_CTC_ICR1:
		CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
		CLEAR_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TOP_CTC_OCR1A:
		CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
		CLEAR_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLEAR_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TOP_FPWM_ICR1:
		CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TOP_FPWM_OCR1A:
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	default: break;
	}

	switch(Config_Mode)
	{
	case TOP_NORMAL:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case CTC_TOGGLE:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case CTC_SET :
	SET_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1B0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	SET_BIT(TCCR1A,TCCR1A_COM1B1);
	break;
	case CTC_CLR:
	CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
	CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	SET_BIT(TCCR1A,TCCR1A_COM1B1);
	break;
	case FAST_PWM_NON_INV:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case FAST_PWM_INV :
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	default: break;
	}


	switch(select_Prescaler){
	case DIV_8:
		CLEAR_BIT(TCCR1B,TCCR1B_CS10);
		SET_BIT(TCCR1B,TCCR1B_CS11);
		CLEAR_BIT(TCCR1B,TCCR1B_CS12);
		break;
	case DIV_64:
		SET_BIT(TCCR1B,TCCR1B_CS10);
		SET_BIT(TCCR1B,TCCR1B_CS11);
		CLEAR_BIT(TCCR1B,TCCR1B_CS12);
		break;
	case DIV_256:
		CLEAR_BIT(TCCR1B,TCCR1B_CS10);
		CLEAR_BIT(TCCR1B,TCCR1B_CS11);
		SET_BIT(TCCR1B,TCCR1B_CS12);
		break;
	}
}

/*
 * Function to set top value
 */
void M_TIMER1_voidSetTopValue(u16 topvalue,TIMER1_TopMode topMode){
	switch(topMode){
	case TOP_FPWM_ICR1 :  ICR1 = topvalue; break;
	case TOP_FPWM_OCR1A : OCR1A = topvalue; break;
	case TOP_CTC_ICR1 :   ICR1 = topvalue; break;
	case TOP_CTC_OCR1A :  OCR1A  = topvalue; break;
	default: break;
	}
}
void M_TIMER1_voidSetDutyCycle(u16 duty_cycle){
	OCR1A = duty_cycle;
}

void M_TIMER1_voidIcuEdgeSelect(TIMER1_IcuEdgeType  edge_select){
	switch  (edge_select){
	case RISING_EDGE:   SET_BIT   (TCCR1B,TCCR1B_ICES1);break;
	case FALLING_EDGE:  CLEAR_BIT (TCCR1B,TCCR1B_ICES1);break;
	default:break;
	}
}

void M_TIMER1_voidEnbaleIcu_Interrupt(void){
	SET_BIT(TIMSK,TIMSK_TICIE1);
}
void M_TIMER1_voidDisabaleIcu_Interrupt(void){
	CLEAR_BIT(TIMSK,TIMSK_TICIE1);
}

u16 M_TIMER1_u16GetOcrValue(void){
	return ICR1;
}
void M_TIMER1_voidSetCallBack(void (*l_pf)(void)){
	pf_icu = l_pf;
}
void ICU_clearTimerValue(void)
{
	TCNT1=0;
	ICR1 = 0;
}
/*************************** Set ISR ********************************/

void __vector_6(void)       __attribute__((signal));
void __vector_6(void){
	if(pf_icu != NULL_PTR ){
		(*pf_icu)();
	}
}
#endif
