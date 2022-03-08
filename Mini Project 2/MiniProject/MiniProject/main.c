#include <avr/io.h>
#include <avr/interrupt.h>
#include<util/delay.h>



unsigned char min=0,sec=0,hou=0,g_tick = 0;
unsigned char m1=0,m2=0,s1=0,s2=0,h1=0,h2=0;
unsigned short last_count=0;

void update(){
	if(sec==60){
		sec=0;
		min++;
	}
	if(min==60){
		min=0;
		hou++;
	}
	if(hou==60){
		hou=0;
	}
	s1=sec%10;
	s2=sec/10;
	m1=min%10;
	m2=min/10;
	h1=hou%10;
	h2=hou/10;
}

void Timer1_Init_CTC_Mode(unsigned short tick)
{
    // set up timer with prescaler = 64 and CTC mode
    TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);

    // initialize counter
    TCNT1 = 0;

    // initialize compare value
    OCR1A = 12499;

    // enable compare interrupt
    TIMSK |= (1 << OCIE1A);

    // enable global interrupts
    sei();
}

ISR(TIMER1_COMPA_vect)
{
	sec++;
	update();
}

void set(){
	for(unsigned char i =0;i<6;i++){
		PORTA =0x00;
		if(i==0)	PORTC = (PORTC & 0xF0) | (s1 & 0x0F);
		else if(i==1)	PORTC = (PORTC & 0xF0) | (s2 & 0x0F);
		else if(i==2)	PORTC = (PORTC & 0xF0) | (m1 & 0x0F);
		else if(i==3)	PORTC = (PORTC & 0xF0) | (m2 & 0x0F);
		else if(i==4)	PORTC = (PORTC & 0xF0) | (h1 & 0x0F);
		else if(i==5)	PORTC = (PORTC & 0xF0) | (h2 & 0x0F);
		else{
			PORTC = 0;
		}
		PORTA = 0xFF & (1<<i);
		_delay_us(1);
	}
}

ISR(INT0_vect)
{
	sec = 0,min=0,hou=0;//reset the value of the timer
	TCNT1 = 0;
	update();
}

void INT0_Init(void)
{
	SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
	DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
	PORTD |= (1<<PD2);
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0
	MCUCR |= (1<<ISC00);   				// Trigger INT0 with the falling edge
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}

ISR(INT1_vect)
{
	last_count = TCNT1;
	TIMSK &= ~(1 << OCIE1A);//pause the timer
}

void INT1_Init(void)
{
	SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
	DDRD  &= (~(1<<PD3));               // Configure INT0/PD2 as input pin
	GICR  |= (1<<INT1);                 // Enable external interrupt pin INT0
	MCUCR |= (1<<ISC11)|(1<<ISC10);   	// Trigger INT0 with the falling edge
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}

ISR(INT2_vect)
{
	TCNT1 = last_count;
	TIMSK |= (1 << OCIE1A);//resume the timer
}

void INT2_Init(void)
{
	SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
	DDRB  &= (~(1<<PB2));               // Configure INT0/PB2 as input pin
	PORTB |= (1<<PB2);					//configure internal pull-up resistor
	GICR  |= (1<<INT2);                 // Enable external interrupt pin INT0
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}

int main(void){
	//input -> 0
	//output -> 1
	INT0_Init();	// Enable External INT0
	INT1_Init();	// Enable External INT1
	INT2_Init();	// Enable External INT2


	DDRA |= 0x3F;
	PORTA |= 0x3F;
	DDRC |= 0x0F;

	SREG  |= (1<<7);
	Timer1_Init_CTC_Mode(1000);
	// initialize the 7-segment with value 0 by clear the first four bits in PORTC
	PORTC &= 0xF0;
	update();
	while(1){
		set();
    }
	return 0;
}

