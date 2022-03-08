/*
 * dc.h
 *
 *  Created on: Oct 16, 2021
 *      Author: Mostafa Elsharnoby
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_


#include "gpio.h"
#include "PWM_signal.h"

typedef enum
{
	STOP,CW,ACW
}DcMotor_State;

typedef enum
{
	OFF,ON
}FAN_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
