/*
 * dc.c
 *
 *  Created on: Oct 16, 2021
 *      Author: Mostafa Elsharnoby
 */

#include "DC_motor.h"

void DcMotor_Init(void)
{
	/* setup port c as output and configure pin 0 , pin 1 to the motor */

	GPIO_setupPortDirection(PORTB_ID,PORT_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT);

	/* start motor with stop state */

	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);

}

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	PWM_Timer0_Init(speed);
	if(state == 0){
		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
		GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
	}
	else if(state == 1){
		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
		GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_HIGH);
	}
	else if(state == 2){
		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_HIGH);
		GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
	}
}
