/** @file     main.c
 *
 *  @author   Armstrong Subero (https://github.com/ArmstrongSubero)
 *  @uC       Attiny84A w/Int OSC @ 1 MHz, 3.3v
 *  @Compiler (AVR GCC 4.9.2, AtmelStudio 7)
 *  @version  1.0
 *
 *  @brief    Reads a pushbutton and turns on an LED
 *
 *  @hardware An Attiny84A has an LED connected via a 1k resistor to PA0 and 
 *            a pushbutton connected via a 10k resistor to PINB1
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
#define F_CPU  1000000UL

#define LED_ON		PORTA |= (1<<PORTA0);
#define LED_OFF		PORTA &= ~(1<<PORTA0);
#define LED_TOGGLE	PINA |=(1<<PINA0);

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
	DDRA |= (1<<DDA0);
	
	// Set B1 as input
	DDRB &= ~(1<<DDB1);
	
	while (1) 
    {
		if(!(PINB & (1<<PINB1)))  // if PINB0 is low turn LED ON
		 {
			 LED_ON;
		 }
		 
		 
		 else                     // else put led off
		 {
			 LED_OFF;
		 }
    }
}  /* main() */



/**
 End of File
*/
