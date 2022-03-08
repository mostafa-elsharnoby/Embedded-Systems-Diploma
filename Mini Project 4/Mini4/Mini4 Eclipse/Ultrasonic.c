#include "icu.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "gpio.h"
#include "std_types.h"
#include "lcd.h"

uint16 g_edgeCount = 0;
uint16 g_timeHigh = 0;

void Ultrasonic_edgeProcessing(void){
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
	}else{
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
		g_edgeCount=1;
	}
}

void Ultrasonic_init(void){
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	/* Set the Call back function pointer in the ICU driver */
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	/* PB5 Input Pin */
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
	/* Create configuration structure for ICU driver */
	Icu_ConfigType Icu_Config = {F_CPU_8,RISING};
	Icu_init(&Icu_Config);
}

void Ultrasonic_Trigger(void){
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
	_delay_us(20);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);
	_delay_us(20);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();
	while(g_edgeCount < 2){}
	g_edgeCount = 0;
	/* calculate the distance */
	float dist = (float)g_timeHigh/57.5;
	uint32 distance = dist;
	return distance;
}



