/** @file     main.c
 *
 *  @author   Armstrong Subero (https://github.com/ArmstrongSubero)
 *  @uC       Attiny84A w/Int OSC @ 1 MHz, 3.3v
 *  @Compiler (AVR GCC 4.9.2, AtmelStudio 7)
 *  @version  1.0
 *
 *  @brief    Uses the LSB of a Linear Feedback Shift Register based 16-bit
 *            pseudo random number generator to randomly flash an LED
 *
 *  @hardware An Attiny84A has an LED connected via a 1k resistor to PA0
 *
 *  @modified Based on example provided by Lukasz Podkalicki for ATTINY 13A
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

// constants for PRNG
#define LFSR_SEED 91
#define DELAY     64

/**
  Section: Included Files
*/
#include <avr/io.h>
#include <util/delay.h>

/*!
 *
 * @brief  Use a Linear Feedback Shift Register to generate 16-bit Pseudo-Random Numbers
 * @return The pseudo random number
 *
 */
static uint16_t prng_lfsr16(void)
{
	static uint16_t cnt16 = LFSR_SEED;
	return (cnt16 = (cnt16 >> 1) ^ (-(cnt16 & 1) & 0xB400));
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
	
	// Set B1 as input
	DDRB &= ~(1<<DDB1);
	
	while (1) 
    {
		 // take the last bit of the randomly generated number
		 // and use it to flash the LED
		 if (prng_lfsr16() & 1)  
		 {
			 LED_ON;
		 }
		 
		 else                   
		 {
			 LED_OFF;
		 }
		 
		 _delay_ms(DELAY);
    }
}  /* main() */



/**
 End of File
*/
