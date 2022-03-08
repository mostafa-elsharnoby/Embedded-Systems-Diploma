/*
 ================================================================================================
 Name        : password.c
 Author      : Mostafa Elsharnoby
 Description : MC1 Code in Final Project
 Date        : 25/10/2021
 ================================================================================================
 */

#include "uart.h"
#include "gpio.h"
#include "password.h"
#include "lcd.h"
#include "keypad.h"
#include <util/delay.h>


uint8 key;

void step1(void){
	LCD_displayStringRowColumn(0,1,"Pls Enter Pass");
	for(uint8 i = 0 ; i < 5 ; i++){
		/* Get the pressed button from keypad */
		key = KEYPAD_getPressedKey();
		LCD_displayStringRowColumn(1,i+1,"*");
		UART_sendByte(key);
		_delay_ms(300);
	}
	LCD_displayStringRowColumn(0,1,"              ");
	for(uint8 i = 0 ; i < 5 ; i++){
		LCD_displayStringRowColumn(1,i+1," ");
	}
	LCD_displayStringRowColumn(0,1,"Renter Pass");
	for(uint8 i = 0 ; i < 5 ; i++){
		/* Get the pressed button from keypad */
		key = KEYPAD_getPressedKey();
		LCD_displayStringRowColumn(1,i+1,"*");
		UART_sendByte(key);
		_delay_ms(300);
	}
	for(uint8 i = 0 ; i < 5 ; i++){
		LCD_displayStringRowColumn(1,i+1," ");
	}
	LCD_displayStringRowColumn(0,1,"              ");
}
void step2(void){
	LCD_displayStringRowColumn(0,1,"+:Open Door");
	LCD_displayStringRowColumn(1,1,"-:Change Pass");
	key = KEYPAD_getPressedKey();
	UART_sendByte(key);
	LCD_displayStringRowColumn(0,1,"              ");
	LCD_displayStringRowColumn(1,1,"              ");
}
void step3(void){
	LCD_displayStringRowColumn(0,1,"Pls Enter Pass3");
	for(uint8 i = 0 ; i < 5 ; i++){
		/* Get the pressed button from keypad */
		key = KEYPAD_getPressedKey();
		LCD_displayStringRowColumn(1,i+1,"*");
		_delay_ms(300);
		UART_sendByte(key);
	}
	for(uint8 i = 0 ; i < 5 ; i++){
		LCD_displayStringRowColumn(1,i+1," ");
	}
	LCD_displayStringRowColumn(0,1,"                 ");

}
void step4(void){
	LCD_displayStringRowColumn(0,1,"Change Pass");
		for(uint8 i = 0 ; i < 5 ; i++){
			/* Get the pressed button from keypad */
			key = KEYPAD_getPressedKey();
			LCD_displayStringRowColumn(1,i+1,"*");
			_delay_ms(300);
			UART_sendByte(key);
		}
		for(uint8 i = 0 ; i < 5 ; i++){
			LCD_displayStringRowColumn(1,i+1," ");
		}
		LCD_displayStringRowColumn(0,1,"Renter Pass");
		for(uint8 i = 0 ; i < 5 ; i++){
			/* Get the pressed button from keypad */
			key = KEYPAD_getPressedKey();
			LCD_displayStringRowColumn(1,i+1,"*");
			_delay_ms(300);
			UART_sendByte(key);
		}
		for(uint8 i = 0 ; i < 5 ; i++){
			LCD_displayStringRowColumn(1,i+1," ");
		}
		LCD_displayStringRowColumn(0,1,"            ");

}
void step5(void){
	LCD_displayStringRowColumn(0,1,"Error!!!");
	_delay_ms(60000);

}



