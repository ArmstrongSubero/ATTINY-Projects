/** @file     main.c
 *
 *  @author   Armstrong Subero (https://github.com/ArmstrongSubero)
 *  @uC       Attiny84A w/Int OSC @ 1 MHz, 3.3v
 *  @Compiler (AVR GCC 4.9.2, AtmelStudio 7)
 *  @version  1.0
 *
 *  @brief    Uses the overflow of Timer0 to toggle an LED every second
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

#define LED_ON		PORTA |= (1<<PORTA0);
#define LED_OFF		PORTA &= ~(1<<PORTA0);
#define LED_TOGGLE	PINA |=(1<<PINA0);

/**
  Section: Included Files
*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


/**
  Section: Global Variables
*/
volatile uint8_t count = 0;



/*!
 *
 * @brief Timer0 ISR toggles an LED ever 4 seconds
 *
 */
ISR(TIM0_OVF_vect)
{
	count++;
	
	// toggle every second 0.25s * 4
	if(count == 4)
	{
		LED_TOGGLE;
		count = 0;
	}
}


/*!
 *
 * @brief Main program entry point
 *
 */
int main(void)
{
	// set PA0 output pin
	DDRA |= (1<<DDA0);
	
	// set prescaler to 1024 (CLK=1000000Hz/1024/256= 3.8Hz, 0.25s)
	TCCR0B |= _BV(CS02)|_BV(CS00); 
	
	// enable Timer Overflow interrupt
	TIMSK0 |= _BV(TOIE0); 
	
	// enable global interrupts
	sei(); 
	
	while (1) 
    {
		// Do nothing
    }
}  /* main() */



/**
 End of File
*/
