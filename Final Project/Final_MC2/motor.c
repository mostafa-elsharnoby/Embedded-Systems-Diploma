/*
 ================================================================================================
 Name        : MC2 motor.c
 Author      : Mostafa Elsharnoby
 Description : MC2 Code in Final Project
 Date        : 25/10/2021
 ================================================================================================
 */

#include "motor.h"


void motor_init(){
	SET_BIT(DDRB,1);
	SET_BIT(DDRB,2);
	SET_BIT(DDRB,3);

	CLEAR_BIT(PORTB,1);
	CLEAR_BIT(PORTB,2);
	SET_BIT(PORTB,3);
}

void motor_CW(){
	SET_BIT(PORTB,1);
	CLEAR_BIT(PORTB,2);
}
void motor_ACW()
{
	CLEAR_BIT(PORTB,1);
	SET_BIT(PORTB,2);
}
void motor_stop(){
	CLEAR_BIT(PORTB,1);
	CLEAR_BIT(PORTB,2);
}
