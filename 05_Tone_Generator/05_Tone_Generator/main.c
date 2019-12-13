/** @file     main.c
 *
 *  @author   Armstrong Subero (https://github.com/ArmstrongSubero)
 *  @uC       Attiny84A w/Int OSC @ 1 MHz, 3.3v
 *  @Compiler (AVR GCC 4.9.2, AtmelStudio 7)
 *  @version  1.0
 *
 *  @brief    Generates a tone on a Piezo Speaker
 *
 *  @hardware An Attiny84A has an Piezo Speaker connected via a 1k resistor to PB0
 *
 *  @par
 *  COPYRIGHT NOTICE: 
 *  (c) 2020 Armstrong Subero. All rights reserved. This software is placed in the
 *  public domain and may be used for any purpose. However, this notice must not
 *  be changed or removed. No warranty is expressed or implied by the publication
 *  or distribution of this source code.
 *                     
 */

/**
  Section: Defines
*/

// define CPU clock frequency 
#define F_CPU 1000000UL

// pin for buzzer
#define BUZZER_ON		PORTB |= (1<<PORTB0);
#define BUZZER_OFF		PORTB &= ~(1<<PORTB0);
#define BUZZER_TOGGLE	PINB |=(1<<PINB0);

/**
  Section: Included Files
*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

/*!
 *
 * @brief This function plays an alarm
 *
 */
void play_alarm()
{
	for (uint8_t i=0; i<10; i++)
	{
		//play x notes inside song array
		BUZZER_TOGGLE;
		_delay_us(1200);
	}
}


/*!
 *
 * @brief Main program entry point
 *
 */
int main(void)
{	
	DDRB  = 0b00000001; // set BUZZER pin as OUTPUT
	PORTB = 0b00000000; // set all pins to LOW

	
	while (1) 
    {
		// play beep
		play_alarm();
		_delay_ms(1000);
    }
}  /* main() */



/**
 End of File
*/
