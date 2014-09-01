/*
 * ENGG288_Project_halleffect.c
 *
 * Created: 24-Aug-14 10:54:23 PM
 *  Author: Zakk
 */ 


#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF; // read in from hall effect, out to LED
	DDRC = 0;
	//PORTB = 0; // set internal pull up resister to reduce noise
	PORTC = 0b00000000; // pull up resistor on port d0
	
	// MUST NOT USE B OR D FOR LED AS THEY ARE ALWAYS HIGH!!!
	while(1){
		if(PINC && (1<<PINC0)){
			PORTB &= ~(1<<PINB1);
			PORTB |= (1<<PINB2); // set to green
		} else {
			PORTB &= ~(1<<PINB2);
			PORTB |= (1<<PINB1); // set to blue
		}
	}
}