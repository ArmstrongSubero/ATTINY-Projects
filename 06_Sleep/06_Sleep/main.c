/** @file     main.c
 *
 *  @author   Armstrong Subero (https://github.com/ArmstrongSubero)
 *  @uC       Attiny84A w/Int OSC @ 1 MHz, 3.3v
 *  @Compiler (AVR GCC 4.9.2, AtmelStudio 7)
 *  @version  1.0
 *
 *  @brief    Enters sleep mode and then uses an external interrupt on PINB0 to
 *            wake from sleep mode
 *
 *  @hardware An Attiny84A has an LED connected via a 1k resistor to PA0 
 *            and a pushbutton is connected to PIN B0
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
#include <avr/sleep.h>
#include <avr/interrupt.h>


/*!
 *
 * @brief Interrupts for PB0 (PCINT8)
 *
 */
ISR(PCINT1_vect)
{
	LED_ON;
	_delay_ms(1000);
	LED_OFF;
}



/*!
 *
 * @brief Main program entry point
 *
 */
int main(void)
{
	// set PA0 output pin
	DDRA = 0b00000001;
	
	// Set B1 as input
	DDRB &= ~(1<<DDB1);
	
	// Enable pin change interrupts
	GIMSK = 0b00100000;

	// Turn on interrupts on PIN B0
	PCMSK1 = 0b00000001;
	
	// write to power reduction register and turn everything off
	PRR = 0xFF;
	
	// set sleep mode
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	
	// enable interrupts with global interrupt mask
	sei();
	
	while (1) 
    {
		// delay for 5 seconds so power consumption reading can be taken
		_delay_ms(3000);
		
		// enable sleep, put CPU to sleep and disable sleep when processor wakes up
		sleep_mode();
    }
}  /* main() */



/**
 End of File
*/
