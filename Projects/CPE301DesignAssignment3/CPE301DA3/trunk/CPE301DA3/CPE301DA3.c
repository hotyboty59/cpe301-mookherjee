/*
 * CPE301DA3.c
 *
 * Created: 3/11/2014 10:07:33 PM
 *  Author: Ronobir Mookherjee 
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
// All the relevant libraries necessary, taken from the lecture slides 

int fallcount = 0; //variable to hold 16 falling edge detects from INT 0 
int valueofTimer0; //optional variable to store timer value and then output to pins 
int main(void)
{
	//8 bit value for counter
	DDRB |= 0xFF; // Sets the Direction Register for output mode, or all 1s shifted into the register 
	//PORTB |= 0xFF;
	//PORTD &= ~PORTD
	
	//output port for timer to int0
	DDRC = 1<<0; // Sets the direction register for output, for port/pins C, in position 0
	PORTC |= (1<<PORTC0); // Sets PC0 to act as an output, and sets the output to initial High VCC
	PORTC &=  ~(1 << PORTC0); // toggles the pin still as an output but sets the value to GND
	
	//output port for 9th bit toggle 
		DDRC = 1<<1; // Sets the direction register for output, for port/pins C, in position 1
		PORTC |= (1<<PORTC1); // Sets PC1 to act as an output, and sets the output to initial High VCC
		PORTC &=  ~(1 << PORTC1); // toggles the pin still as an output but sets the value to GND
	
	//Turn on Timer1 using interrupts and Prescaler 256, for .5 second period
	OCR1A = 15624; //The OCRxx register, in this case 1A for the 16bit timer, is set to a value following this formula [clock/prescaler]*desired time in seconds - 1, where the output duty cycle is 50%, and the period is .5s
	TCCR1B |= (1 << WGM12); //Sets the mode of timer 1 to begin in CTC
	TIMSK1 |= (1<<OCF1A); //Sets the interrupt for CTC for Timer1A, now you can access ISR after sei has been set
	TCCR1B |= (1<<CS12); // Sets the prescaler value and starts the timer 
	
	// Turn on the INT0 Global interrupt pin 
	EICRA |= (1<<ISC10); // Activate the global pin INT0 to trigger on falling edges 
	EIMSK = (1<<INT0); //enable external interrupt 0
	
	//use timer0 an a counter that outputs its 8bit data to the LED bar. 
	TCNT0 = 0x0; //start time for timer value zero
	TCCR0A |= (0<<WGM01) | (0<<WGM10); //set Timer0 to normal mode 
	TCCR0B |= (0<<WGM00); // setting Timer0 to normal mode
	TIMSK0 |= (1<<TOIE0); // setting an interrupt for Timer0 overflowing
	TCCR0B |= (1<<CS01)|(0<<CS00)|(1<<CS10); // setting the prescaler value, but really now using INT0 as an external clock. 
	
	sei(); //set global interrupts to enable 
	
	
    while(1) //main program loop 
    {
        valueofTimer0 = TCNT0; 
		PORTD = TCNT0; //output the value of counter0 to the output pins assigned
    }
}
	
	ISR (TIMER1_COMPA_vect)// When CTC is met for OCR1A, the timer following interrupt vector subroutine is to be executed. 
	{
		//toggle pin 
		// reset TCNT1
		PORTC ^=  (1 << PORTC0); //toggle's PC0, acting as an external clock with the aforementioned waveform 
		TCNT1 = 0; //sets the timer back to 0 after CTC
	}
	
	ISR (INT0_vect) //Interrupt vector subroutine for INT0
	{
		
		fallcount++; // Increments variable for falling edges
		if (fallcount == 16) // once falling edges reach predefined value of 16 falling pulses, follow this if loop to toggle the 9th bit and port 
		{
			//toggle pin 
			PORTC ^= (1<<PORTC1); //toggle pin of PortC for enabling or disabling the 9th bit of the LED bar
			fallcount = 0;  //reset the value of fallcount back to 0 to restart counting 
		}
	}
	
	ISR(TIMER0_OVF_vect)
	{
		TCNT0 = 0; //sets timer value back to 0 after overflow 
	}
