/*
 * main.c
 *
 *  Created on: Oct 13, 2021
 *      Author: Mostafa Saftawy
 */


#include "DC_motor.h"
#include "lm35_sensor.h"
#include "lcd.h"

void main(void)
{
	LCD_init();
	DcMotor_Init();
	uint64 temp=0;
	uint8 fan_state=0;

	while(1){
		temp=LM35_getTemperature();

		if(temp < 30){
			DcMotor_Rotate(STOP,0);
		}
		else if(temp>= 30 && temp < 60){
			DcMotor_Rotate(CW,64);
			fan_state=1;
		}
		else if(temp>= 60 && temp < 90){
			DcMotor_Rotate(CW,128);
			fan_state=1;
		}
		else if(temp>= 960 && temp < 120){
			DcMotor_Rotate(CW,192);
			fan_state=1;
		}
		else {
			DcMotor_Rotate(CW,255);
			fan_state=1;
		}
		LCD_displayStringRowColumn(0,3,"FAN  is ");
		if(fan_state==OFF){
			LCD_displayString("OFF");
		}
		else {
			LCD_displayString("ON");

		}
		LCD_displayStringRowColumn(1,2,"Temp = ");
		LCD_intgerToString(temp);
		LCD_displayString("C");
	}
}
