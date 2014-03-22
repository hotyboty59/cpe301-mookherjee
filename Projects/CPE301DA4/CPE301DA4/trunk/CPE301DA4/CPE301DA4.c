/*
 * CPE301DA4.c
 *
 * Created: 3/21/2014 5:52:58 PM
 *  Author: Ronobir Mookherjee 
 */ 

/*
*Testing example code from Dr. Venki 
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
//#include <util/delay.h>
#include <util/parity.h>
#include <util/delay_basic.h>
int RED = 25; 
int BLUE = 0;
int GREEN = 0; 


 //Assume XTAL is 8mhz
 // PWM must change from 10% to 90% 
 //Duty cycle changes as follows, DC = Pulse Width * 100/Period 
 //Duty_Cycle = [ON_time / (ON_time + OFF_time) ] * 100
 //Output_Voltage = Duty_Cycle * Input_Voltage
 
int main ()
{
	DDRB |= (1<<DDB3);
	DDRD |= (1<<DDD5) | (1<<DDD6);
	

	
 TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
		
	TCCR0B |= (1 << CS00) | (1<<CS02);
 	// set prescaler to 8 and starts PWM
	 

	
	 TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
	 TCCR2B = _BV(CS21)| _BV(CS22); 
	
	
	//
	
	 OCR1A = 0x30D3;

	 TCCR1B |= (1 << WGM12);
	 // Mode 4, CTC on OCR1A

	 TIMSK1 |= (1 << OCIE1A);
	 //Set interrupt on compare match

	 TCCR1B |= (1 << CS12) | (0 << CS10);
	 // set prescaler to 1024 and start the timer


	 sei();
	 // enable interrupts

	
while (1)
{
	
}

}ISR (TIMER1_COMPA_vect)
{
	OCR2A = BLUE;
	OCR0A = RED;
	OCR0B = GREEN;
		 
	RED = RED + 100; 
	BLUE = BLUE + 100; 
	GREEN = GREEN + 100; 
	


}