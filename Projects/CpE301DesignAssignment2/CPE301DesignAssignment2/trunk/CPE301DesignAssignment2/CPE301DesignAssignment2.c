/*
 * CPE301DesignAssignment2.c
 *
 * Created: 3/6/2014 3:08:19 PM
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

int main(void)
{
	DDRD = 1<<5; 
	PORTD &= ~(1<<5);
	TCNT1 = 62440;
	TCCR1B = (0<<ICES1);
	TIMSK1 = (1<<ICIE1)|(1<<TOIE1);
	TCCR1B =(1<<CS12)|(1<<CS10);
	sei(); 
}
	ISR (TIMER1_OVF_vect)
	{
		TCNT1 = 62440;
		PORTB ^= (1<<5);
	}
