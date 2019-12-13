/** @file     main.c
 *
 *  @author   Armstrong Subero (https://github.com/ArmstrongSubero)
 *  @uC       Attiny84A w/Int OSC @ 1 MHz, 3.3v
 *  @Compiler (AVR GCC 4.9.2, AtmelStudio 7)
 *  @version  1.0
 *
 *  @brief    Fades an LED using software PWM
 *
 *  @hardware An Attiny84A has an LED connected via a 1k resistor to PA0
 *
 *  @modified Based on example provided by ?ukasz Podkalicki for ATTINY 13A
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
#define DELAY_MAX   512


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
	
	// variables for fading
	uint16_t delay = 1;
	uint8_t dir = 0;
	
	
	while (1) 
    {
		LED_OFF;
		_delay_loop_2(delay);
		
		LED_ON;
		_delay_loop_2(DELAY_MAX-delay);
		
		 if (dir)
		 {   
			// fade-in
			if (++delay >= (DELAY_MAX - 1)) 
			{
				dir = 0;
			}
			 
		 } 
		 
		 else 
		 { 
			 if (--delay <= 1) 
			 {
				 dir = 1;
			 }
		 }
    }
}  /* main() */



/**
 End of File
*/
