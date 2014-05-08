/*
Design Assignment 7 

To use a library and connect to an LCD module, the nokia 5110, and connect to the PCD8544 LCD driver
 * DA7.c
 *
 * Created: 4/22/2014 3:25:27 PM
 *  Author: Ronobir Mookherjee
 */ 

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
#include "Library/glcd-0.5.2/glcd.h"
#include "Library/glcd-0.5.2/glcd_text.h"
#include "Library/glcd-0.5.2/Fonts/font5x7.h"
#include "Library/glcd-0.5.2/Devices/AVR8.h"
#define LCD_BACKLIGHT_PORT PORTC
#define LCD_BACKLIGHT_PIN  4
volatile char DataADC;



void InitialzeLCD(void){
		sbi(DDR(LCD_BACKLIGHT_PORT),LCD_BACKLIGHT_PIN); //setting the LCD backlight pin and port
		sbi(LCD_BACKLIGHT_PORT,LCD_BACKLIGHT_PIN);
		glcd_init(); // initializes the LCD
		glcd_set_contrast(50); // sets constrast to default value
		glcd_clear(); // clears screen and buffer
}

void glcd_tempdata_writer(char Tempdata){ //function that writes to the LCD
	glcd_tiny_set_font(Font5x7,5,7,32,127);
	glcd_clear_buffer();
	glcd_tiny_draw_string(10,10,"Testing");
	glcd_write();
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

void InitADC(){ //initializes ADC
	//select Vref = AVCC and left adjust result setting to 8 bits
	ADMUX = (0<<REFS1)|(0<<REFS0)|(0<<ADLAR);
	ADMUX = (0<<MUX1)|(1<<MUX3)|(0<<MUX2)|(0<<MUX0);
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
	InitialzeLCD(); //initializes LCD
	SetADCChannel(5); // sets ADC channel for temperature sensor 
	InitADC(); // Initializes ADC and timer below to 1 second 
	InitTimer();
	startTimer();
	startADC();
	while(1)
	{
		// Main loop
	}
}

ISR(ADC_vect) //After 1 second, ADC conversion takes place
{

	while(ADIF == 0){ //check to see if ADCH and ADCL have been populated before proceeding
	};
	DataADC = ADCL;
	DataADC = (ADCH << 8) + DataADC;
	glcd_tempdata_writer(DataADC);
	TIFR1 = (0<<OCF1A)|(0<<OCF1B); //disables flag to reset interrupt and start again
	StopADC(); //stops ADC to restart back to main.

	
}