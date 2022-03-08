/*
 ================================================================================================
 Name        : MC2.c
 Author      : Mostafa Elsharnoby
 Description : MC1 Code in Final Project
 Date        : 25/10/2021
 ================================================================================================
 */


#include "uart.h"
#include "gpio.h"
#include "external_eeprom.h"
#include "twi.h"
#include "password.h"
#include <util/delay.h>
#include "motor.h"
int main(void){
	uint8 val = 0;

	/* Initialize the TWI/I2C Driver */
	TWI_init();
	uint8 key_num;
	Buzz_Init();
	motor_init();

	EEPROM_writeByte(0x0000, 255); /* Write 255 in the external EEPROM to know there is no password set yet */
	_delay_ms(10);
	EEPROM_readByte(0x0000, &val);  /* Read 0x0F from the external EEPROM */
	/* Configure all pins in PORTC as output pins */

	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init(9600);
	key_num = UART_recieveByte();
	/* If key is 255 "So it will check if there's a stored password" */
	if(key_num == 255)	UART_sendByte(255);
	_delay_ms(10);
    while(1){
    	step1();
    }
}
