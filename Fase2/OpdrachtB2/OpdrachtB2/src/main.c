/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
 #define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
static int LightBit; 

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


ISR( INT0_vect )
{
	if(LightBit > 128)
	{
	 LightBit >>= 8;
	 PORTC = LightBit;
	}
	LightBit <<=1;
	PORTC = LightBit;
	PORTD = 0b00000000;
	wait(1000);

}

ISR( INT1_vect )
{
	if(LightBit > 128)
	{
		LightBit >>= 8;
	}
	if(LightBit != 1)
	LightBit <<= 1;
	PORTC = LightBit;
	PORTD = 0b00000011;
	wait(1000);
}


int main (void)
{
	LightBit = 0b00000001;
	

	DDRC = 0b11111111;
	DDRD = 0b11111111;

	EICRA |= 0x0B;			
	EIMSK |= 0x03;
	sei();
	/* Insert system clock initialization code here (sysclk_init()). */
	
	PORTD = 0b00000011;
	PORTC = LightBit;
	while (1)
	{
	}
	return 1;
}
