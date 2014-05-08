/*
 * DesignAssigment5Part1.c
 *
 * Submission for part 1
 Part 1 and 2 were combined into one project, and are being separated and submitted individually. 
 
 The purpose of part 1 is to get the value of the Temperature using ADC once per second and outputting through USART connection to a terminal in the window. 
 
 The three components used include the Temperature sensor LM34 from TI, the Polulu Programmer with TTL serial communications capability and the Atmega328p
 *  Author: Ronobir Mookherjee
 */ 

/*  Below is the standard setup for an AVR project, with preprocessor directives*/
#include <stdlib.h>
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
#include <util/parity.h>


volatile uint8_t DataADC;



void InitialzeIO(void){
	// Debug ports to check if all functions are working 
	DDRC = (0 << DDC0); //Input Port for ADC Temp Sensor
	DDRB = (1<<DDB2); //PWM Channel 
	
}

void InitTimer(void) //Timer used for ADC conversion, set to 1s
{
	OCR1A = 8000; //1s value at 8mhz clock rate
	TIMSK1 |= (1 << OCIE1A); //enables CTC mode interrupts
	TCCR1B |= (1 << WGM12); //sets to Mode 4 or CTC mode 
}
void startTimer(void) //function call that starts timer
{
	TCCR1B |= (1 << CS12) | (1 << CS10); //clock prescaler that divides clock 1024 for the system clock 
}
void stopTimer(void) //stops timer
{
	TCCR1B &= ~((1 << CS12) | (1 << CS10));
	TIMSK1 &=~(1<<OCIE0A);
}

void initPWM(void)
{
	ICR1= 2499;		//fPWM=50Hz	(Period	=	20ms	Standard).
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);								//NON	Inverted	PWM
	//PRESCALER=64	MODE	14(FAST	PWM)
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);
	
}

void InitADC(){ //initializes ADC
	//select Vref = AVCC and left adjust result setting to 8 bits 
	ADMUX = (0<<REFS1)|(0<<REFS0)|(1<<ADLAR);
	//set prescaler, enable autoriggering, enable adc interrupt, and enable adc
	ADCSRA |= (1<<ADPS1)|(1<<ADPS2)|(1<<ADPS0)|(1<<ADATE)|(1<<ADIE)|(1<<ADEN);
	ADCSRB |= (0<<ADTS1)|(1<<ADTS0)|(1<<ADTS2); //Set clock division value to 256
}
void SetADCChannel(int ADCchannel){ //function to select which ADC channel to pickup from for output going to the ADCMUX
	if (ADCchannel == 5)
	{
		ADMUX = (0<<MUX1)|(0<<MUX3)|(1<<MUX2)|(1<<MUX0);
	}
	else if (ADCchannel == 0)
	{
		ADMUX = (0<<MUX1)|(0<<MUX3)|(0<<MUX2)|(0<<MUX0);
	}
	else
	{
		ADMUX = (0<<MUX1)|(1<<MUX3)|(0<<MUX2)|(0<<MUX0);
	}
	
}
void startADC(void) //Starts ADC transmission 
{
	ADCSRA |= (1<<ADSC);
}
void StopADC(void)
{
	ADCSRA &= ~((1<<ADEN)|(1<<ADIE));
}

int main(void) //main body calls all other functions to initialize the proper values of the Transmission protocol, timer and ADC module, then starts them 
{
	InitialzeIO();
	SetADCChannel(0);
	InitADC();
	InitTimer();
	startTimer();
	startADC();
	sei(); // enables interrupts 
	while(1)
	{
		// Main loop
	}
}

ISR(ADC_vect) //After 1 second, ADC conversion takes place
{

	while(ADIF == 0){ //check to see if ADCH and ADCL have been populated before proceeding 
	};
	DataADC = ADCH * 2; // is the value of the temperature sensor captured and stored in the variable
	TIFR1 = (0<<OCF1A)|(0<<OCF1B); //disables flag to reset interrupt and start again 
	StopADC(); //stops ADC to restart back to main. 

	
}