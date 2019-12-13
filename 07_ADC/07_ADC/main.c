/** @file     main.c
 *
 *  @author   Armstrong Subero (https://github.com/ArmstrongSubero)
 *  @uC       Attiny84A w/Int OSC @ 1 MHz, 3.3v
 *  @Compiler (AVR GCC 4.9.2, AtmelStudio 7)
 *  @version  1.0
 *
 *  @brief    Reads the ADC module to turn an LED on an off
 *
 *  @hardware An Attiny84A has an LED connected via a 1k resistor to PA0 and a
 *            50k potentiometer to PA1
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

/*!
 *
 * @brief This function initializes the ADC
 *
 */
void initADC()
{
  /* 
    ADC Notes
	
	Prescaler
	
	ADC Prescaler needs to be set so that the ADC input frequency is between 50 - 200kHz.
	
	Example prescaler values for various frequencies
	
	Clock   Available prescaler values
   ---------------------------------------
	 1 MHz   8 (125kHz), 16 (62.5kHz)
	 4 MHz   32 (125kHz), 64 (62.5kHz)
	 8 MHz   64 (125kHz), 128 (62.5kHz)
	16 MHz   128 (125kHz)

   below example set prescaler to 16 for mcu running at 1MHz


  */

   ADMUX =
            (0 << REFS1) |     // Sets ref. voltage to Vcc, bit 1   
            (0 << REFS0) |     // Sets ref. voltage to Vcc, bit 0
            (0 << MUX5)  |     // use ADC1 for input (PA1), MUX bit 5
            (0 << MUX4)  |     // use ADC1 for input (PA1), MUX bit 4
            (0 << MUX3)  |     // use ADC1 for input (PA1), MUX bit 3
            (0 << MUX2)  |     // use ADC1 for input (PA1), MUX bit 2
            (0 << MUX1)  |     // use ADC1 for input (PA1), MUX bit 1
            (1 << MUX0);       // use ADC1 for input (PA1), MUX bit 0

  ADCSRA = 
            (1 << ADEN)  |     // Enable ADC 
            (1 << ADPS2) |     // set prescaler to 16, bit 2 
            (0 << ADPS1) |     // set prescaler to 16, bit 1 
            (0 << ADPS0);      // set prescaler to 16, bit 0 
			
  ADCSRB = 
            (1 << ADLAR);      // left shift result (for 8-bit values)
	//        (0 << ADLAR);      // right shift result (for 10-bit values)
}


/*!
 *
 * @brief Main program entry point
 *
 */
int main(void)
{
	// set PA0 output pin
	DDRA = 0b0000001;
	
	initADC();
	
	while (1) 
    {
		ADCSRA |= (1 << ADSC);         // start ADC measurement
		while (ADCSRA & (1 << ADSC) ); // wait till conversion complete

        // if voltage is more than half turn the led On
		if (ADCH > 128)
		{
			LED_ON;
		} 
		else 
		{
			LED_OFF;
		}

    }
}  /* main() */



/**
 End of File
*/
