/*
 * mgie_program.c
 *
 *  Created on: Aug 8, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"

#include "mgie_interface.h"
#include "mgie_register.h"
#include "mgie_config.h"
#include "mgie_private.h"


void MGIE_voidEnable(void){
	SET_BIT(SREG,SREG_I);
}
void MGIE_voidDisable(void){
	CLEAR_BIT(SREG,SREG_I);
}
