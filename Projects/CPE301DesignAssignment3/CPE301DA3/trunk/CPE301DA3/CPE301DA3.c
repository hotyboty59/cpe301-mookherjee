/*
 * CPE301DA3.c
 *
 * Created: 3/11/2014 10:07:33 PM
 *  Author: localmgr
 */ 

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <math.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <avr/boot.h>
#include <avr/io.h>
#include <avr/cpufunc.h>
#include <avr/eeprom.h>
#include <avr/fuse.h>
#include <avr/interrupt.h>
#include <avr/lock.h>
#include <avr/power.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <avr/version.h>
#include <util/crc16.h>
#include <util/delay.h>
#include <util/parity.h>
#include <util/delay_basic.h>
// Todo, Write the code. For clock cycle 

int fallcount = 0; 
int valueofTimer0; 
int main(void)
{
	//8 bit value for counter
	DDRB |= 0xFF;
	//PORTB |= 0xFF;
	//PORTD &= ~PORTD
	
	//output port for timer to int0
	DDRC = 1<<0;
	PORTC |= (1<<PORTC0);
	PORTC &=  ~(1 << PORTC0);
	
	//output port for 9th bit toggle 
		DDRC = 1<<1;
		PORTC |= (1<<PORTC1);
		PORTC &=  ~(1 << PORTC1);
	
	//Turn on Timer1 using interrupts and Prescaler 256, for .5 second period
	OCR1A = 15624;
	TCCR1B |= (1 << WGM12);
	TIMSK1 |= (1<<OCF1A);
	TCCR1B |= (1<<CS12);
	
	// Turn on the INT0 Global interrupt pin 
	EICRA |= (1<<ISC10);
	EIMSK = (1<<INT0); //enable external interrupt 0
	
	TCNT0 = 0x0; 
	TCCR0A |= (0<<WGM01) | (0<<WGM10);
	TCCR0B |= (0<<WGM00);
	TIMSK0 |= (1<<TOIE0);
	TCCR0B |= (1<<CS01)|(0<<CS00)|(1<<CS10);
	
	sei(); 
	
	
    while(1)
    {
        valueofTimer0 = TCNT0;
		PORTD = TCNT0;
    }
}
	
	ISR (TIMER1_COMPA_vect)
	{
		//toggle pin 
		// reset TCNT1
		PORTC ^=  (1 << PORTC0); 
		TCNT1 = 0; 
	}
	
	ISR (INT0_vect)
	{
		
		fallcount++; 
		if (fallcount == 16)
		{
			//toggle pin 
			PORTC ^= (1<<PORTC1);
			fallcount = 0; 
		}
	}
	
	ISR(TIMER0_OVF_vect)
	{
		TCNT0 = 0;
	}
