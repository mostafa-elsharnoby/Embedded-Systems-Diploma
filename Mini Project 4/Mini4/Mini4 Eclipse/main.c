#include "lcd.h"
#include "icu.h"
#include "Ultrasonic.h"
#include <avr/io.h> /* To use the SREG register */
#include <util/delay.h>
int main(){
	LCD_init();
	Ultrasonic_init();
	while(1){
		uint32 dist = Ultrasonic_readDistance();
		/* display the period on LCD screen */
		LCD_displayStringRowColumn(0,1,"Distance = ");
		LCD_intgerToString(dist);
		LCD_displayString(" CM");
//		_delay_ms(500);
//		LCD_clearScreen();
	}
}
