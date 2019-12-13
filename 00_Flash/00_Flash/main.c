/** @file     main.c
 *
 *  @author   Armstrong Subero (https://github.com/ArmstrongSubero)
 *  @uC       Attiny84A w/Int OSC @ 1 MHz, 3.3v
 *  @Compiler (AVR GCC 4.9.2, AtmelStudio 7)
 *  @version  1.0
 *
 *  @brief    Flashes an LED at a rate of 1 Hz
 *
 *  @hardware An Attiny84A has an LED connected via a 1k resistor to PA0
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

/**
  Section: Included Files
*/
#include <avr/io.h>
#include <util/delay.h>


/*!
 *
 * @brief Main program entry point
 *
 */
int main(void)
{
	// set PA0 output pin
	DDRA = 0b00000011;
	
	while (1) 
    {
		// toggle LED
	 	PORTA = 0b0000001;
		_delay_ms(500);
		PORTA = 0b00000000;
		_delay_ms(500);
    }
}  /* main() */



/**
 End of File
*/
