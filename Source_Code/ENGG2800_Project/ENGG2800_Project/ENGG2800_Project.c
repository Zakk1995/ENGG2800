/*
 * ENGG2800_Project.c
 *
 * Created: 14/08/2014 4:19:20 PM
 *  Author: s4321402
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <util/delay.h>

int dutyCycle=0;
int dutyCycleGreen=0;
int dutyCycleBlue=0;
int dutyCycleRed=0;
int mode= 0;
int incrementing=1;

void changeMode(){
	mode=0;
}

void changeMode2(){
	mode=1;
}

void fadeinoutblue(){
	if(dutyCycleBlue<=255&&incrementing){
		dutyCycleBlue++;
	}
	if(dutyCycleBlue>=255&&incrementing){
		incrementing=0;
	}
	if(incrementing==0){
		dutyCycleBlue--;
	}
}

void fadeinoutcyan(){
	if(dutyCycleBlue<=255&&incrementing){
		dutyCycleBlue++;
		dutyCycleGreen++;
	}
	if(dutyCycleBlue>=255&&incrementing){
		incrementing=0;
	}
	if(incrementing==0){
		dutyCycleBlue--;
		dutyCycleGreen--;
	}
}

void fadeinoutyellow(){
	if(dutyCycleRed<=255&&incrementing){
		dutyCycleRed++;
		dutyCycleGreen++;
	}
	if(dutyCycleRed>=255&&incrementing){
		incrementing=0;
	}
	if(incrementing==0){
		dutyCycleRed--;
		dutyCycleGreen--;
	}	
}

void fadeinoutgreen(){
	if(dutyCycleGreen<=255&&incrementing){
		dutyCycleGreen++;
	}
	if(dutyCycleGreen>=255&&incrementing){
		incrementing=0;
	}
	if(incrementing==0){
		dutyCycleGreen--;
	}
}

void fadeinoutwhite(){
	if(dutyCycleBlue<=255&&incrementing){
		dutyCycleBlue++;
		dutyCycleGreen++;
		dutyCycleRed++;
	}
	if(dutyCycleBlue>=255&&incrementing){
		incrementing=0;
	}
	if(incrementing==0){
		dutyCycleBlue--;
		dutyCycleGreen--;
		dutyCycleRed--;
	}
}

void fadeinoutmagenta(){
	if(dutyCycleBlue<=255&&incrementing){
		dutyCycleBlue++;
		dutyCycleRed++;
	}
	if(dutyCycleBlue>=255&&incrementing){
		incrementing=0;
	}
	if(incrementing==0){
		dutyCycleBlue--;
		dutyCycleRed--;
	}
}

void fadeinoutred(){
	if(dutyCycleRed<=255&&incrementing){
		dutyCycleRed++;
	}
	if(dutyCycleRed>=255&&incrementing){
		incrementing=0;
	}
	if(incrementing==0){
		dutyCycleRed--;
	}
}

void initialise(){
	dutyCycleRed=0;
	dutyCycleGreen=0;
	dutyCycleBlue=0;
	incrementing=1;
}

int main(void){
	incrementing = 1;
	int first = 0;
	int isblue=1;
	int isgreen=0;
	int isred=0;
	int iscyan=0;
	int ismagenta=0;
	int isyellow=0;
	int iswhite=0;
	mode=0;
	DDRD = (1<<PORTD6)|(1<<PORTD5); // for OC0A enabled pin (Pin D6)
	DDRC = 0;
	DDRB=(1<<PORTB1);
	TCCR0A |= (1<<COM0A1)|(1<<COM0B1)|(1<<WGM01)|(1<<WGM00); // timer0 control register A set for output compare match
	TCCR1A |= (1<<COM1A1)|(1<<WGM10); //TIMER 1 control register a set to output compare match
	TIMSK0 |= (1<<OCIE0A)|(1<<OCIE0B); // interrupt enabled on compare
	TIMSK1 |= (1<<OCIE1A); // interrupt enabled on compare
	OCR0A=255; // represents amount of time to be on
	OCR0B=255;
	OCR1A=255;
	sei();
	TCCR0B |= (1<<CS00); // set prescaler to be 1. starts timer
	TCCR1B |= (1<<WGM12)|(1<<CS10); // prescaler 1
	while(1){
		
		
		if(PINC&&(1<<PINC5)){
			mode=1;
		}
		else{
			mode=0;
		}
		
// 		if(mode==2){
// 			if(first){
// 				initialise();
// 			}
// 			first=0;
// 			isred=1;
// 			fadeinoutred();
// 		}
		
		if(mode==0){
			if(isblue){
				dutyCycleBlue=255;
			}
			if(isred){
				dutyCycleRed=255;
			}
			if(isgreen&&(dutyCycleGreen!=255)){
				dutyCycleGreen=255;
			}
			if(iscyan&&(dutyCycleBlue!=255)){
				dutyCycleBlue=255;
				dutyCycleGreen=255;
			}
			if(isyellow&&(dutyCycleRed!=255)){
				dutyCycleRed=255;
				dutyCycleGreen=255;
			}
			if(ismagenta&&(dutyCycleBlue!=255)){
				dutyCycleBlue=255;
				dutyCycleRed=255;
			}
			if(iswhite&&(dutyCycleBlue!=255)){
				dutyCycleBlue=255;
				dutyCycleGreen=255;
				dutyCycleRed=255;
			}
		}
		//red 
		// dutyCycleGreen=0;
		//dutyCycleBlue=0;
		//dutyCycleRed=255;
		
		//blue
		// dutyCycleGreen=0;
		//dutyCycleBlue=255;
		//dutyCycleRed=0;
		
		//green
		// dutyCycleGreen=255;
		//dutyCycleBlue=0;
		//dutyCycleRed=0;
		
		//cyan
		// dutyCycleGreen=255;
		//dutyCycleBlue=255;
		//dutyCycleRed=0;
		
		//magenta
		// dutyCycleGreen=0;
		//dutyCycleBlue=255;
		//dutyCycleRed=255;
		
		//yellow
		// dutyCycleGreen=255;
		//dutyCycleBlue=0;
		//dutyCycleRed=255;
		
		//white
		// dutyCycleGreen=255;
		//dutyCycleBlue=255;
		//dutyCycleRed=255;
		
		//blue->cyan->yellow->green->white->magenta->red->blue:
		
		if(mode==1){
			_delay_ms(1);
			if(isblue){
				fadeinoutblue();
				if(dutyCycleBlue<=0&&incrementing==0){
					isblue=0;
					iscyan=1;
					initialise();
				}
			}
			if(iscyan){
				fadeinoutcyan();
				if(dutyCycleBlue<=0&&incrementing==0){
					iscyan=0;
					isyellow=1;
					initialise();
				}
			}
			if(isyellow){
				fadeinoutyellow();
				if(dutyCycleRed<=0&&incrementing==0){
					isyellow=0;
					isgreen=1;
					initialise();
				}
			}
			if(isgreen){
				fadeinoutgreen();
				if(dutyCycleGreen<=0&&incrementing==0){
					isgreen=0;
					iswhite=1;
					initialise();
				}
			}
			if(iswhite){
				fadeinoutwhite();
				if(dutyCycleBlue<=0&&incrementing==0){
					iswhite=0;
					ismagenta=1;
					initialise();
				}
			}
			if(ismagenta){
				fadeinoutmagenta();
				if(dutyCycleBlue<=0&&incrementing==0){
					ismagenta=0;
					isred=1;
					initialise();
				}
			}
			if(isred){
				fadeinoutred();
				if(dutyCycleRed<=0&&incrementing==0){
					isred=0;
					isblue=1;
					initialise();
				}
			}
		}
		
		//check if button is pushed
// 		if(PINC && (1<<PINC5)){
// 			changeMode();
// 		}
		// this will pulse the LED
// 		if(mode==0){
// 			if(dutyCycle>=255){
// 				incrementing=0;
// 			}
// 			if(dutyCycle<=0){
// 				incrementing=1;
// 			}
// 			if(incrementing){
// 				incrementLED();
// 			}
// 			if(incrementing==0){
// 				decrementLED();
// 			}
// 		}
		// this will leave the LED on constant
// 		if(mode==1){
// 			dutyCycle=255;	
// 		}
// 		
// 		// this will make the colours change
// 		if(mode==2){
// 			
// 		}
	}
	return 0;
}

ISR(TIMER0_COMPA_vect){
	OCR0A=dutyCycleGreen;
}

ISR(TIMER0_COMPB_vect){
	OCR0B=dutyCycleRed;
}

ISR(TIMER1_COMPA_vect){
	OCR1A=dutyCycleBlue;
}

// ISR(TIMER0_OVF_vect){
// 	OCR0A = (dutyCycle/100.0)*255.0; // represents amount of time to be on
// }

// working using delays
// int main(void)
// {	
// 	DDRC=0xff;
//     while(1)
//     {
// 	 status_write();
//     }
// }
// 
// void status_write() {
// 	PORTC = 0xff;
// 	_delay_ms(500);
// 	PORTC=0x00;
// 	_delay_ms(500);
// }
// 
// void status_on() {
// 	PORTC = 0xff;
// }

