/*
 * m_timer_interface.h
 *
 *  Created on: Aug 10, 2023
 *      Author: SOFT ZONE
 */

#ifndef M_TIMER_INTERFACE_H_
#define M_TIMER_INTERFACE_H_

typedef enum{
	TIMER0_NORMAL_MODE,TIMER0_CTC_MODE=2,TIMER0_PWM_FAST_MODE
}TIMER0_WAVE_GENERATION;
typedef enum{
	TIMER0_NORMAL_OP,TIMER0_TOGGLE_OC0_OP,TIMER0_CLEAR_OC0_OP,TIMER0_SET_OC0_OP
}TIMER0_CTCMODE_NONPWM;
typedef enum{
	NO_CLK,NO_PRESC,PRESC_8,PRESC_64,PRESC_256,PRESC_1024,EXTERNAL_FALLING,EXTERNAL_RISING
}TIMER0_PRESCALER;

typedef struct{
	TIMER0_WAVE_GENERATION    timer0_mode;
	TIMER0_PRESCALER          select_prescaler;
	u8                        TCNT0_value;
	u8                        OCR_value;
	TIMER0_CTCMODE_NONPWM     CTC_nonPWM_mode;
 }TIMER0_Config;

void M_TIMER0_voidInit(const TIMER0_Config *);
void M_TIMER0_voidDisable(void);
void M_TIMER0_voidSetPreLoad(u8);
void M_TIMER0_voidSelectPrescaler(TIMER0_PRESCALER);
void M_TIMER0_voidSetOcrValue(u8);
void M_TIMER0_voidSetCallBack(void(*a_ptr)(void));
#endif /* M_TIMER_INTERFACE_H_ */
