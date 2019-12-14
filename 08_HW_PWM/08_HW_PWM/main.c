/** @file     main.c
 *
 *  @author   Armstrong Subero (https://github.com/ArmstrongSubero)
 *  @uC       Attiny84A w/Int OSC @ 1 MHz, 3.3v
 *  @Compiler (AVR GCC 4.9.2, AtmelStudio 7)
 *  @version  1.0
 *
 *  @brief    Demonstrates use of the hardware PWM module on all available PINs 
 *            of the ATTINY84A
 *
 *  @hardware An Attiny84A has LEDs connected via a 1k resistors to PA5, PA6, PA7
 *            and PB2
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
	// Set PWM PINS as outputs
	DDRA |= _BV(DD7) | _BV(DD6) | _BV(DD5);
	DDRB |= _BV(DD2);
	PORTA = 0;
	PORTB = 0;
	
    // Timer 0 based PWM output
    TCCR0A |= _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00);
	TCCR0B |= _BV(CS01); 
	

	 // Timer 1 based PWM output
	 TCCR1A |= _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
	 TCCR1B |= _BV(CS11); 
	
	
	while (1) 
    {
	  // sweep entire range of resolution
	  for(uint8_t duty = 0; duty<= 255; duty++)
	  {
	    OCR0A = duty;
	    OCR0B = duty;
	    OCR1A = duty;
	    OCR1B = duty;
	    _delay_ms(100);
	  } 
	
    }
}  /* main() */



/**
 End of File
*/
