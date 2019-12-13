/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: ATTINY84A w/Int OSC @ 1 MHz, 3.7 v
 * Program: P01_POV
 * Compiler: (AVR GCC 4.9.2, AtmelStudio 7)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows ATTINY84A to use PORTA for a POV display
 * 
 * Hardware Description: Eight LEDs are connected via 150R resistors to PORTA
 *
 * Modified From: PIC18F2685 version written in MikroC by Andrew Hazelden
 *                modified to fit on ATTINY84A
 *                      
 * Created December 12th, 2019, 05:00 PM
 */



/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

//8 pixels high x 7 pixels wide letters
const char letter_SPC[8]= {0,0,0,0,0,0,0};
const char letter_newline[8]= {0,0,0,0,0,0,0};
const char letter_A[8]= {31,36,68,132,68,36,31};
const char letter_B[8]= {255,137,137,137,137,137,118};
const char letter_C[8]= {126,129,129,129,129,129,66};
const char letter_D[8]= {255,129,129,129,129,70,60};
const char letter_E[8]= {255,137,137,137,129,129,129};
const char letter_F[8]= {255,136,136,136,136,128,128};
const char letter_G[8]= {126,129,129,137,137,143,72};
const char letter_H[8]= {255,8,8,8,8,8,255};
const char letter_I[8]= {129,129,129,255,129,129,129};
const char letter_J[8]= {142,129,129,254,128,128,128};
const char letter_K[8]= {255,16,16,16,40,68,131};
const char letter_L[8]= {255,1,1,1,1,1,1};
const char letter_M[8]= {255,128,128,112,128,128,255};
const char letter_N[8]= {255,64,32,16,8,4,255};
const char letter_O[8]= {126,129,129,129,129,129,126};
const char letter_P[8]= {255,136,136,136,136,136,112};
const char letter_Q[8]= {124,130,138,134,131,130,124};
const char letter_R[8]= {255,136,136,136,140,138,113};
const char letter_S[8]= {98,145,145,145,137,137,70};
const char letter_T[8]= {128,128,128,255,128,128,128};
const char letter_U[8]= {255,1,1,1,1,1,255};
const char letter_V[8]= {248,4,2,1,2,4,248};
const char letter_W[8]= {254,1,1,14,1,1,254};
const char letter_X[8]= {129,2,36,24,36,66,129};
const char letter_Y[8]= {128,0,32,31,32,64,128};
const char letter_Z[8]= {131,133,137,145,161,193,129};
const char letter_0[8]= {0,126,133,137,145,161,126};
const char letter_1[8]= {0,33,65,255,1,1,0};
const char letter_2[8]= {65,131,133,137,137,145,99};
const char letter_3[8]= {66,129,129,137,137,149,98};
const char letter_4[8]= {0,12,20,36,68,255,4};
const char letter_5[8]= {121,137,137,137,137,137,134};
const char letter_6[8]= {126,137,137,137,137,137,134};
const char letter_7[8]= {128,128,128,143,144,160,192};
const char letter_8[8]= {118,137,137,129,137,137,118};
const char letter_9[8]= {112,137,137,129,137,137,126};
const char letter_PERIOD[8]= {0,0,0,15,7,0,0};
const char letter_COMMA[8]= {0,0,0,6,7,0,0};
const char letter_QUOTE[8]= {0,120,120,0,120,120,0};
const char letter_SINGLE_QUOTE[8]= {0,0,0,120,120,0,0};
const char letter_QUESTION[8]= {0,96,128,141,144,144,96};
const char letter_EXCLAIM[8]= {0,0,0,253,0,0,0};
const char letter_AT[8]= {0,126,153,165,165,153,120};
const char letter_NUM[8]= {36,255,36,36,36,255,36};
const char letter_DOLLAR[8]= {36,82,82,255,74,74,36};
const char letter_PERCENT[8]= {65,162,68,24,34,69,130};
const char letter_CARRAT[8]= {12,48,64,128,64,48,12};
const char letter_AMPERSAND[8]= {67,163,149,137,141,147,114};
const char letter_ASTERISK[8]= {201,42,28,255,28,42,201};
const char letter_LEFT_PAREN[8]= {0,0,0,126,129,0,0};
const char letter_RIGHT_PAREN[8]= {0,0,129,126,0,0,0};
const char letter_DASH[8]= {8,8,8,8,8,8,8};
const char letter_UNDERSCORE[8]= {1,1,1,1,1,1,1};
const char letter_PLUS[8]= {8,8,8,255,8,8,8};
const char letter_EQUALS[8]= {36,36,36,36,36,36,36};
const char letter_TILDE[8]= {16,48,32,32,16,48,32};
const char letter_TICK[8]= {0,0,96,112,0,0,0};
const char letter_COLON[8]= {0,0,102,102,0,0,0};
const char letter_SEMICOLON[8]= {0,0,102,103,0,0,0};
const char letter_BACK_SLASH[8]= {1,2,4,24,32,64,128};
const char letter_FORWARD_SLASH[8]= {128,64,32,24,4,2,1};
const char letter_LEFT_CHEVRON[8]= {0,36,66,129,0,0,0};
const char letter_RIGHT_CHEVRON[8]= {0,129,66,38,24,24,0};
const char letter_TAB[8]= { 255,255,255,255,255,255,255}; 
const char letter_LEFT_BRACKET[8]= {0,0,0,255,129,129,0};
const char letter_RIGHT_BRACKET[8]= {0,129,129,255,0,0,0};
const char letter_SMILIE[8]= {126,137,165,133,165,137,126};
const char letter_HEART[8]= {120,252,126,63,126,252,120};



//function to print a 8x7 single character
void printChar(char letter);


char counter;
int digit_counter=0;

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Program entry point
 * @Example
    none
 */

int main(void)
{
    int n, i, repeat;
	
	// Set A0 as output
	DDRA = 0xFF;
		
    while (1) 
    {
		 //start word cycle
		 for (repeat=0;repeat<24;repeat++)
		 {
			 
			 //fill a revolution
			 for(n=0;n<2;n++)
			 {
				 printChar(' ');
				 printChar(' ');
				 printChar(' ');
				 printChar('I');
				 printChar(' ');
				 printChar(174); //heart char
				 printChar(' ');
				 printChar('P');
				 printChar('I');
				 printChar('C');
				 printChar(' ');
				 printChar(' ');
				 printChar(' ');
				 printChar('\t');
				 
			 }//end for n
		 } //end for repeat
		 
		 //END word cycle
	}
}

// ----------------------------------------------------------
//
// The printChar function prints prints a single 8x7 chracter.
//
// ----------------------------------------------------------

void printChar(char letter){
	int n;
	digit_counter++;
	for(n=0;n<8;n++){
		
		if(letter == 'A') PORTA = letter_A[n];
		else if(letter == 'B') PORTA = letter_B[n];
		else if(letter == 'C') PORTA = letter_C[n];
		else if(letter == 'D') PORTA = letter_D[n];
		else if(letter == 'E') PORTA = letter_E[n];
		else if(letter == 'F') PORTA = letter_F[n];
		else if(letter == 'G') PORTA = letter_G[n];
		else if(letter == 'H') PORTA = letter_H[n];
		else if(letter == 'I') PORTA = letter_I[n];
		else if(letter == 'J') PORTA = letter_J[n];
		else if(letter == 'K') PORTA = letter_K[n];
		else if(letter == 'L') PORTA = letter_L[n];
		else if(letter == 'M') PORTA = letter_M[n];
		else if(letter == 'N') PORTA = letter_N[n];
		else if(letter == 'O') PORTA = letter_O[n];
		else if(letter == 'P') PORTA = letter_P[n];
		else if(letter == 'Q') PORTA = letter_Q[n];
		else if(letter == 'R') PORTA = letter_R[n];
		else if(letter == 'S') PORTA = letter_S[n];
		else if(letter == 'T') PORTA = letter_T[n];
		else if(letter == 'U') PORTA = letter_U[n];
		else if(letter == 'V') PORTA = letter_V[n];
		else if(letter == 'W') PORTA = letter_W[n];
		else if(letter == 'X') PORTA = letter_X[n];
		else if(letter == 'Y') PORTA = letter_Y[n];
		else if(letter == 'Z') PORTA = letter_Z[n];
		else if(letter == '0') PORTA = letter_0[n];
		else if(letter == '1') PORTA = letter_1[n];
		else if(letter == '2') PORTA = letter_2[n];
		else if(letter == '3') PORTA = letter_3[n];
		else if(letter == '4') PORTA = letter_4[n];
		else if(letter == '5') PORTA = letter_5[n];
		else if(letter == '6') PORTA = letter_6[n];
		else if(letter == '7') PORTA = letter_7[n];
		else if(letter == '8') PORTA = letter_8[n];
		else if(letter == '9') PORTA = letter_9[n];
		else if(letter == '.') PORTA = letter_PERIOD[n];
		else if(letter == ',') PORTA = letter_COMMA[n];
		else if(letter == '?') PORTA = letter_QUESTION[n];
		else if(letter == '!') PORTA = letter_EXCLAIM[n];
		else if(letter == '@') PORTA = letter_AT[n];
		else if(letter == '#') PORTA = letter_NUM[n];
		else if(letter == '$') PORTA = letter_DOLLAR[n];
		else if(letter == '%') PORTA = letter_PERCENT[n];
		else if(letter == '^') PORTA = letter_CARRAT[n];
		else if(letter == '&') PORTA = letter_AMPERSAND[n];
		else if(letter == '*') PORTA = letter_ASTERISK[n];
		else if(letter == '(') PORTA = letter_LEFT_PAREN[n];
		else if(letter == ')') PORTA = letter_RIGHT_PAREN[n];
		else if(letter == '-') PORTA = letter_DASH[n];
		else if(letter == '_') PORTA = letter_UNDERSCORE[n];
		else if(letter == '+') PORTA = letter_PLUS[n];
		else if(letter == '=') PORTA = letter_EQUALS[n];
		else if(letter == '~') PORTA = letter_TILDE[n];
		else if(letter == '`') PORTA = letter_TICK[n];
		else if(letter == ':') PORTA = letter_COLON[n];
		else if(letter == ';') PORTA = letter_SEMICOLON[n];
		else if(letter ==  9 ) PORTA = letter_TAB[n];    
		else if(letter == '[' ) PORTA = letter_LEFT_BRACKET[n];
		else if(letter == ']' ) PORTA = letter_RIGHT_BRACKET[n];
		else if(letter == ' ') PORTA = letter_SPC[n];
		else if(letter == 174) PORTA = letter_HEART[n];  
		else if(letter == '\n') PORTA = letter_newline[n];

		else PORTA = letter_newline[n];  /
		
		if(letter == 174) _delay_ms(2);    
		else _delay_ms(1); 	
	}

	PORTA = 0;
	_delay_ms(2);  
	
} 



