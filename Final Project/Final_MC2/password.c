/*
 ================================================================================================
 Name        : MC1.c
 Author      : Mostafa Elsharnoby
 Description : MC1 Code in Final Project
 Date        : 25/10/2021
 ================================================================================================
 */

#include "uart.h"
#include "gpio.h"
#include "password.h"
#include "timer.h"
#include "external_eeprom.h"
#include "twi.h"
#include <util/delay.h>
#include "motor.h"

uint8 password[5];
uint8 password2[5];
uint8 Wrong_count=0;


void step1(void){
	UART_sendByte(STEP1);
	uint8 flag=0;
	for(uint8 i = 0 ; i < 5 ; i++){
	   password[i] = UART_recieveByte();
	}
	for(uint8 i = 0 ; i < 5 ; i++){
		password2[i] = UART_recieveByte();
    }
	for(uint32 i=0x00,j=0;i<=64;i+=16,j++){
		if(password[i] != password2[i]){
			flag=1;
		}
	}
	if(flag==0){
		for(uint32 i=i;i<5;i++){
			EEPROM_writeByte(0x000A+i, password[i]);
			_delay_ms(10);
		}
		step2();
	}else{
		step1();
	}
}
void step2(void){
	UART_sendByte(STEP2);
	uint8 key=UART_recieveByte();
	if(key == '+'){
		step3();
	}else if(key == '-'){
		step4();
	}else{
		step2();
	}
}
void step3(void){
	UART_sendByte(STEP3);
	uint8 flag=0,val=0;
	for(uint32 i=i;i<5;i++){
		EEPROM_readByte(0x000A+i, &val);
		password[i]=val;
	}
	for(uint8 i=0;i<5;i++){
		val = UART_recieveByte();
		if(val != password[i]){
			flag=1;
		}
	}
	if(flag==1){
		Wrong_count++;
		if(Wrong_count==3)	step5();
		step3();
	}else{
		//success
		_delay_ms(10);
		motor_CW();
		_delay_ms(15000);
		motor_stop();
		_delay_ms(2000);
		motor_ACW();
		_delay_ms(15000);
		motor_stop();
		step2();
	}
}
void step4(void){

	UART_sendByte(STEP4);
		uint8 flag=0;
		for(uint8 i = 0 ; i < 5 ; i++){
		   password[i] = UART_recieveByte();
		}
		for(uint8 i = 0 ; i < 5 ; i++){
			password2[i] = UART_recieveByte();
	    }
		for(uint8 i = 0 ; i < 5 ; i++){
			if(password[i] != password2[i]){
				flag=1;
			}
		}
		if(flag==1){
			step1();
		}else{
			step2();
		}
}
void step5(void){
	UART_sendByte(STEP5);
	Buzz_On();
	_delay_ms(600000);
	Buzz_Off();
	Wrong_count=0;
	step2();
}

void Buzz_Init(){
	GPIO_setupPinDirection(PORTC_ID,PIN2_ID,PIN_OUTPUT);
}

void Buzz_On(){
	GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_HIGH);
}

void Buzz_Off(){
	GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_LOW);
}
