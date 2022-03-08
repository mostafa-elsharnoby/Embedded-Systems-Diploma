/*
 ================================================================================================
 Name        : MC1.c
 Author      : Mostafa Elsharnoby
 Description : MC1 Code in Final Project
 Date        : 25/10/2021
 ================================================================================================
 */

#include "uart.h"
#include "keypad.h"
#include "lcd.h"
#include "password.h"
#include <util/delay.h>
#define YES 255
#define NO 0


int main(void)
{
	uint8 key_num;
	LCD_init();
	_delay_ms(100);
	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init(9600);
	UART_sendByte(255);
	key_num = UART_recieveByte();
	LCD_displayStringRowColumn(0,1,"Hello");

    while(1){
    	key_num = UART_recieveByte();
    	if(key_num==STEP1)	step1();
    	else if(key_num==STEP2)	step2();
    	else if(key_num==STEP3)	step3();
    	else if(key_num==STEP4)	step4();
    	else if(key_num==STEP5)	step5();
    	else{}
    }
}
