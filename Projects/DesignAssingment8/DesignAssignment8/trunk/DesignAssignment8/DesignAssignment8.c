/*
 * DesignAssignment8.c
 *
 * Created: 5/8/2014 9:53:06 AM
 *  Author: Ronobir Mookherjee 
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "MCP475/types.h"
#include "MCP475/defs.h"
#include "MCP475/i2c.h"
#define  F_CPU  80000000UL 
static char LUT[360] = {"2048",
	"2070",
	2092,
	2114,
	2136,
	2158,
	2180,
	2202,
	2224,
	2246,
	2268,
	2290,
	2312,
	2334,
	2356,
	2378,
	2400,
	2422,
	2444,
	2466,
	2488,
	2510,
	2532,
	2554,
	2576,
	2598,
	2620,
	2642,
	2664,
	2686,
	2708,
	2730,
	2752,
	2774,
	2796,
	2818,
	2840,
	2862,
	2884,
	2906,
	2928,
	2950,
	2972,
	2994,
	3016,
	3038,
	3060,
	3082,
	3104,
	3126,
	3148,
	3170,
	3192,
	3214,
	3236,
	3258,
	3280,
	3302,
	3324,
	3346,
	3368,
	3390,
	3412,
	3434,
	3456,
	3478,
	3500,
	3522,
	3544,
	3566,
	3588,
	3610,
	3632,
	3654,
	3676,
	3698,
	3720,
	3742,
	3764,
	3786,
	3808,
	3830,
	3852,
	3874,
	3896,
	3918,
	3940,
	3962,
	3984,
	4006,
	3984,
	3962,
	3940,
	3918,
	3896,
	3874,
	3852,
	3830,
	3808,
	3786,
	3764,
	3742,
	3720,
	3698,
	3676,
	3654,
	3632,
	3610,
	3588,
	3566,
	3544,
	3522,
	3500,
	3478,
	3456,
	3434,
	3412,
	3390,
	3368,
	3346,
	3324,
	3302,
	3280,
	3258,
	3236,
	3214,
	3192,
	3170,
	3148,
	3126,
	3104,
	3082,
	3060,
	3038,
	3016,
	2994,
	2972,
	2950,
	2928,
	2906,
	2884,
	2862,
	2840,
	2818,
	2796,
	2774,
	2752,
	2730,
	2708,
	2686,
	2664,
	2642,
	2620,
	2598,
	2576,
	2554,
	2532,
	2510,
	2488,
	2466,
	2444,
	2422,
	2400,
	2378,
	2356,
	2334,
	2312,
	2290,
	2268,
	2246,
	2224,
	2202,
	2180,
	2158,
	2136,
	2114,
	2092,
	2070,
	2048,
	2026,
	2004,
	1982,
	1960,
	1938,
	1916,
	1894,
	1872,
	1850,
	1828,
	1806,
	1784,
	1762,
	1740,
	1718,
	1696,
	1674,
	1652,
	1630,
	1608,
	1586,
	1564,
	1542,
	1520,
	1498,
	1476,
	1454,
	1432,
	1410,
	1388,
	1366,
	1344,
	1322,
	1300,
	1278,
	1256,
	1234,
	1212,
	1190,
	1168,
	1146,
	1124,
	1102,
	1080,
	1058,
	1036,
	1014,
	992,
	970,
	948,
	926,
	904,
	882,
	860,
	838,
	816,
	794,
	772,
	750,
	728,
	706,
	684,
	662,
	640,
	618,
	596,
	574,
	552,
	530,
	508,
	486,
	464,
	442,
	420,
	398,
	376,
	354,
	332,
	310,
	288,
	266,
	244,
	222,
	200,
	178,
	156,
	134,
	112,
	90,
	68,
	46,
	68,
	90,
	112,
	134,
	156,
	178,
	200,
	222,
	244,
	266,
	288,
	310,
	332,
	354,
	376,
	398,
	420,
	442,
	464,
	486,
	508,
	530,
	552,
	574,
	596,
	618,
	640,
	662,
	684,
	706,
	728,
	750,
	772,
	794,
	816,
	838,
	860,
	882,
	904,
	926,
	948,
	970,
	992,
	1014,
	1036,
	1058,
	1080,
	1102,
	1124,
	1146,
	1168,
	1190,
	1212,
	1234,
	1256,
	1278,
	1300,
	1322,
	1344,
	1366,
	1388,
	1410,
	1432,
	1454,
	1476,
	1498,
	1520,
	1542,
	1564,
	1586,
	1608,
	1630,
	1652,
	1674,
	1696,
	1718,
	1740,
	1762,
	1784,
	1806,
	1828,
	1850,
	1872,
	1894,
	1916,
	1938,
	1960,
	1982,
	2004,
	2026,
};
#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

#define STATUS_LED 5

#define Vout 3000//binary value going into register, 0-4095

#define SLA_W 0xC0//write address
#define SLA_R 0xC1//read address

//Define functions
//======================
void i2cSendStart(void);
void i2cSendStop(void);
void i2cWaitForComplete(void);
void i2cSendByte(unsigned char data);
void i2cInit(void);
void i2cHz(long uP_F, long scl_F);


void delay(void); // general purpose delay
//======================

int main (void)
{
	uint8_t x = 0;
	
	//ADC result vars
	long l;//low register
	long h;//high register
	
	long Vref = 5120;//reference V in mV
		
	
/*    ioinit(); //Setup IO pins and defaults*/
	
		
	//set control bytes
	char lVout = Vout;
	char hVout = (Vout>>8) & 0x0F;
	
	
	
	
	//initilize I2C hardware
	TWCR = 0x00;
	TWBR = 8;
	cbi(TWCR, TWEA);	
	sbi(TWCR, TWEN);
	printf("%x\n", TWCR);
	
	
	//Send start condition 
	i2cSendStart();	
    i2cWaitForComplete();
	
	
	// send slave device address with write
	i2cSendByte(SLA_W);	
	i2cWaitForComplete();	
	
	
	// send first byte to MCP
	TWDR = hVout;
	// begin send
	TWCR = (1<<TWINT)|(1<<TWEN);	
	i2cWaitForComplete();	
	
	
	
	// send second byte to MCP
	TWDR = lVout;
	// begin send
	TWCR = (1<<TWINT)|(1<<TWEN);	
	i2cWaitForComplete();
	
	//send stop condition
	i2cSendStop();
	
	TWCR = 0x00;//stop I2C
	
	primaryfunction(); 
	
	while(1)
	{
		delay();
		 
	}
    return(0);
}

void primaryfunction(void) // main function to send the sine wave value 
{
	 	int DegreeCounter;
		for (DegreeCounter = 0; DegreeCounter < 360; DegreeCounter++)
		{
			i2cMasterSendNI(SLA_W, 12, LUT[DegreeCounter]);
		}
}


void delay(void) // One second delay using timer 
{
		OCR1A = 8000; //1s value at 8mhz clock rate
		//TIMSK1 |= (1 << OCIE1A); //enables CTC mode interrupts
		TCCR1B |= (1 << WGM12); //sets to Mode 4 or CTC mode
		TCCR1B |= (1 << CS12) | (1 << CS10); //clock prescaler that divides clock 1024 for the system clock
		        while ( (TIFR1 & (1 << TOV1) ) > 0)        // wait for the overflow event
		        {
		        }
		        
		        TIFR0 &= ~(1 << TOV0);
}



void i2cInit(void)
{
	// set pull-up resistors on I2C bus pins
	sbi(PORTC, 5);	// i2c SCL on ATmega163,323,16,32,etc
	sbi(PORTC, 4);	// i2c SDA on ATmega163,323,16,32,etc

	// set i2c bit rate to 40KHz
	i2cSetBitrate(100);
	// enable TWI (two-wire interface)
	sbi(TWCR, TWEN);
}

void i2cSetBitrate(unsigned short bitrateKHz)
{
	unsigned char bitrate_div;
	// set i2c bitrate
	// SCL freq = F_CPU/(16+2*TWBR))

		cbi(TWSR, TWPS0);
		cbi(TWSR, TWPS1);
	// calculate bitrate division	
	bitrate_div = ((F_CPU/1000l)/bitrateKHz);
	if(bitrate_div >= 16)
		bitrate_div = (bitrate_div-16)/2;
	outb(TWBR, bitrate_div);
}

void i2cSendStart(void)
{
	// send start condition
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
}

void i2cSendStop(void)
{
	// transmit stop condition
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void i2cWaitForComplete(void)
{
	// wait for i2c interface to complete operation
        while (!(TWCR & (1<<TWINT)));
}

void i2cSendByte(unsigned char data)
{
	// save data to the TWDR
	TWDR = data;
	// begin send
	TWCR = (1<<TWINT)|(1<<TWEN);
}

void i2cReceiveByte(unsigned char ackFlag)
{
	// begin receive over i2c
	if( ackFlag )
	{
		// ackFlag = TRUE: ACK the recevied data
		outb(TWCR, (inb(TWCR)&TWCR_CMD_MASK)|BV(TWINT)|BV(TWEA));
	}
	else
	{
		// ackFlag = FALSE: NACK the recevied data
		outb(TWCR, (inb(TWCR)&TWCR_CMD_MASK)|BV(TWINT));
	}
}

unsigned char i2cGetReceivedByte(void)
{
	// retieve received data byte from i2c TWDR
	return( inb(TWDR) );
}

unsigned char i2cGetStatus(void)
{
	// retieve current i2c status from i2c TWSR
	return( inb(TWSR) );
}



unsigned char i2cMasterSendNI(unsigned char deviceAddr, unsigned char length, unsigned char* data)
{
	unsigned char retval = I2C_OK;
	// send start condition
	i2cSendStart();
        i2cWaitForComplete();
	// send device address with write
	i2cSendByte( deviceAddr & 0xFE );
	i2cWaitForComplete();
	// check if device is present and live
	if( inb(TWSR) == TW_MT_SLA_ACK)
	{
		// send data
		while(length)
		{
			i2cSendByte( *data++ );
			i2cWaitForComplete();
			length--;
		}
	}
	else
	{
		// device did not ACK it's address,
		// data will not be transferred
		// return error
		retval = I2C_ERROR_NODEV;
	}

	// transmit stop condition
	// leave with TWEA on for slave receiving
	i2cSendStop();
	while( !(inb(TWCR) & BV(TWSTO)) );

	return retval;
}

unsigned char i2cMasterReceiveNI(unsigned char deviceAddr, unsigned char length, unsigned char *data)
{
	unsigned char retval = I2C_OK;

	// send start condition
	i2cSendStart();
	i2cWaitForComplete();

	// send device address with read
	i2cSendByte( deviceAddr | 0x01 );
	i2cWaitForComplete();

	// check if device is present and live
	if( inb(TWSR) == TW_MR_SLA_ACK)
	{
		// accept receive data and ack it
		while(length > 1)
		{
			i2cReceiveByte(TRUE);
			i2cWaitForComplete();
			*data++ = i2cGetReceivedByte();
			// decrement length
			length--;
		}

		// accept receive data and nack it (last-byte signal)
		i2cReceiveByte(FALSE);
		i2cWaitForComplete();
		*data++ = i2cGetReceivedByte();
	}
	else
	{
		// device did not ACK it's address,
		// data will not be transferred
		// return error
		retval = I2C_ERROR_NODEV;
	}

	// transmit stop condition
	// leave with TWEA on for slave receiving
	i2cSendStop();

	return retval;
}