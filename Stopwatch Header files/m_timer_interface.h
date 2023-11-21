/*
 * m_timer_interface.h
 *
 *  Created on: Aug 10, 2023
 *      Author: SOFT ZONE
 */

#ifndef M_TIMER_INTERFACE_H_
#define M_TIMER_INTERFACE_H_
/*
 *
 * WE NEED TO CONFIGURE THIS DRIVER TO MAKE IT CONFIGURABLE AND ALSO CONFIGURE PINS AS
 * OUTPUT WHENEVER WE INIT ANY FUNCTIONS AND USE BOTH TIMER1 AND TIMER0
 *
 *
 */
#define    TIMER0
#define    BY_ME
//#define    PREV
#ifdef TIMER0
typedef enum{
	TIMER0_NORMAL_MODE,
	TIMER0_CTC_MODE=2,
	TIMER0_PWM_FAST_MODE
}TIMER0_WAVE_GENERATION;

typedef enum{
	TIMER0_NORMAL_OP,
	TIMER0_TOGGLE_OC0_OP,
	TIMER0_CLEAR_OC0_OP,
	TIMER0_SET_OC0_OP
}TIMER0_CTCMODE_NONPWM;

typedef enum{
	TIMER0_PWM_NORMAL_OP,
	TIMER0_NON_INVERTING_MODE=2,
	TIMER0_INVERTING_MODE
}TIMER0_CTCMODE_FASTPWM;

typedef enum{
	NO_CLK,
	NO_PRESC,
	PRESC_8,
	PRESC_64,
	PRESC_256,
	PRESC_1024,
	EXTERNAL_FALLING,
	EXTERNAL_RISING
}TIMER0_PRESCALER;

typedef struct{
	TIMER0_WAVE_GENERATION    timer0_mode;
	TIMER0_PRESCALER          select_prescaler;
	u8                        TCNT0_value;
	u8                        OCR_value;
	TIMER0_CTCMODE_NONPWM     CTC_nonPWM_mode;
	TIMER0_CTCMODE_FASTPWM    PWM_mode;
 }TIMER0_Config;

void M_TIMER0_voidInit(const TIMER0_Config *);
void M_TIMER0_voidDisable(void);
void M_TIMER0_voidSetPreLoad(u8);
void M_TIMER0_voidSelectPrescaler(TIMER0_PRESCALER);
void M_TIMER0_voidSetCallBack(void(*a_ptr)(void));
void M_TIMER0_voidSetDutyCylce(u8 duty_cycle);
#endif

#ifdef                     TIMER1
/*                                   USER Define Type                                         */

typedef enum{
	TIMER1_NORMAL_MODE,
	TIMER1_CTC_MODE_TOP_OCR1A=4,\
	TIMER1_CTC_MODE_TOP_ICR1 = 12,\
	TIMER1_PWM_FAST_MODE_TOP_ICR1=14,
	TIMER1_PWM_FAST_MODE_TOP_OCR1A
}TIMER1_WAVE_GENERATION;
typedef enum{
	TIMER1_NORMAL,TIMER1_TOGGLE,TIMER1_CLEAR,TIMER1_SET
}TIMER1_COMPARE_OUTPUT_MODE;
typedef enum{
	TIMER1_NO_CLK,TIMER1_NO_PRESCALE,TIMER1_8_PRESCALE,TIMER1_64_PRESCALE,TIMER1_256_PRESCALE,\
	TIMER1_1024_PRESCALE,TIMER1_EXTERNAL_CLK_FALLING,TIMER1_EXTERNAL_CLK_RISING
}TIMER1_PRESCALER;
typedef enum {
	NONE,TIMER1A,TIMER1B
}Timer1_Index;
typedef struct{
	u16                                      initial_value;
	u16                                      compare_value;
	TIMER1_WAVE_GENERATION                   timer1_mode;
	TIMER1_PRESCALER                         timer1_prescaler;
	TIMER1_COMPARE_OUTPUT_MODE               timer1_compare_mode;
	Timer1_Index                             index;
}Timer1_ConfigType;
/*                                   Function Prototype                                      */
/*
 * Description: Function to initialize the Timer driver
 * Input: pointer to the configuration structure with type Timer_ConfigType , top mode.
 * Output: None
 */
void M_TIMER1_voidInit(const Timer1_ConfigType * Config_Ptr ,u8 topMode);

/*
 * Function to set top value
 */
void M_TIMER1_voidSetTopValue(u16 topMode);
/*
 * Description: Function to change OCR value for Changing duty cycle
 * Input: Pointer to structure
 * Return: None
 */
void Timer1_changeOcr_value(const Timer1_ConfigType * Config_Ptr);
/*
 * Description:Function to disable the Timer.
 * Input: None
 * Output: None
 */
void Timer1_deInit(void);
void Timer1_Pause(void);
void Timer1_Resume(TIMER1_PRESCALER prescaler);
void Timer1_Reset(void);
/*
 * Description: Function to set the Call Back function address.
 * Input: None
 * Output: None
 */
void Timer1_setCallBack(void(*a_ptr)(void));
void Timer1_pwmAdjust(Timer1_ConfigType *ptr_sturct ,u16 duty_cycle);

#endif

typedef enum{
	TOP_NORMAL,
	CTC_TOGGLE,
	CTC_SET,
	CTC_CLR,
	FAST_PWM_NON_INV,
	FAST_PWM_INV
}TIMER1_Mode;
typedef enum{
	NORMAL_MODE_WAVE_OXFFFF,
	TOP_CTC_OCR1A,
	TOP_CTC_ICR1,
	TOP_FPWM_ICR1,
	TOP_FPWM_OCR1A
}TIMER1_TopMode;
typedef enum{
	DIV_8,
	DIV_64,
	DIV_256
}TIMER1_Prescaler;
typedef enum{
	RISING_EDGE,
	FALLING_EDGE
}TIMER1_IcuEdgeType;
void M_TIMER1_voidInit(TIMER1_TopMode topMode, TIMER1_Mode  Config_Mode ,TIMER1_Prescaler select_Prescaler);

/*
 * Function to set top value
 */
void M_TIMER1_voidSetTopValue(u16 topvalue,TIMER1_TopMode topMode);

void M_TIMER1_voidSetDutyCycle(u16 duty_cycle);
/* ICU ENABLE TIMER1 */
void M_TIMER1_voidIcuEdgeSelect(TIMER1_IcuEdgeType  edge_select);

void M_TIMER1_voidEnbaleIcu_Interrupt(void);
void M_TIMER1_voidDisabaleIcu_Interrupt(void);

u16 M_TIMER1_u16GetOcrValue(void);
void ICU_clearTimerValue(void);
void M_TIMER1_voidSetCallBack(void (*l_pf)(void));
#endif /* M_TIMER_INTERFACE_H_ */
