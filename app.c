/*
 * app.c
 *
 *  Created on: Aug 12, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"

#include "mdio_interface.h"
#include "m_timer_interface.h"
#include "external_interrupt_interface.h"
#include "mgie_interface.h"
#include "seven_seg_interface.h"

#define MAX_NUMBER_OF_TICKS  500

u16 g_n_of_ticks = 0 ;
u8 g_sec = 0;
u8 g_min = 0;
u8 g_hr = 0;

void PB_Init(void);
void PB_Pause(void);
void PB_Reset(void);
void PB_Resume(void);
void TMR_Init(void);
void TMR_Update(void);

int main(){
	/* Configure port direction */
	Port_voidInit();
	/* Initialize three push buttons  */
	PB_Init();
	/* Enable global interrupt */
	MGIE_voidEnable();

	TMR_Init();

	while(1){
		SEVEN_SEG_voidDisplay(g_sec,g_min,g_hr);
	}
}
void PB_Init(void){
	EXTERNAL_INTERRUPT_Config config_interrupt = {FALLING_EDGE,INT2_FALLING_EDGE};
	void (*L_ptr_INT[3])(void) = {PB_Pause,PB_Reset,PB_Resume};
	/* Enable Interrupt */
	EXTERNAL_INTERRUPT_init(&config_interrupt);

	/* Set Call back for interrupt */
	EXTERNAL_INTERRUPT_SetCallBack(L_ptr_INT);
}
void TMR_Init(void){
	TIMER0_Config config_timer = {TIMER0_CTC_MODE,PRESC_8,0,250};
	/* Enalbe Timer */
	M_TIMER0_voidInit(&config_timer);
	/* Set call back for timer */
	M_TIMER0_voidSetCallBack(TMR_Update);
}
void TMR_Update(void){
	//Enter this func every 2 ms
	// when number of ticks = 500 --> it means 1 sec
	//update counters (SEC, MIN, HR) to be displayed
	g_n_of_ticks++;
	if(g_n_of_ticks == MAX_NUMBER_OF_TICKS){
		g_n_of_ticks = 0 ;
		g_sec++;
		if(g_sec == 60){
			g_sec = 0 ;
			g_min++;
		}
		if(g_min == 60){
			g_min = 0 ;
			g_hr++;
		}
		if(g_hr == 60){
			g_hr = 0 ;
		}
	}
}
void PB_Pause(void){
	M_TIMER0_voidSelectPrescaler(NO_CLK);
}
void PB_Reset(void){

	g_sec = 0 , g_min = 0 , g_hr = 0 ;
	M_TIMER0_voidSetPreLoad(0);
}
void PB_Resume(void){
	M_TIMER0_voidSelectPrescaler(PRESC_8);
}
