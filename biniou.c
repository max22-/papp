#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "macros.h"

#define SPEAKER 4,C

int mute = 1;

void setup_timer(void)
{
	TCCR0B |= (1<<CS01);
	TCCR0A |= (1<<WGM01);
	TIMSK0 |= (1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
	flip(SPEAKER);
}

void play(int n)
{
	if(mute) {
		cli();
		setup_timer();
	}
	OCR0A = n;
	if(mute) {
		sei();
		mute=0;
	}
}

void silence(void)
{
	if(mute==1)
		return;
	cli();
	TCCR0A=0;
	TCCR0B=0;
	TIMSK0 &= ~(1<<OCIE0A);
	off(SPEAKER);
	sei();
	mute=1;
}

void debug(char d)
{
	PORTD = ~d;
}

// stepper motor

void circular_shift(volatile uint8_t *c)
{
	*c = ((*c<<1) & 0xF) | ( (*c & 0xF) >> 3);
}

void stepper(void)
{
	static uint16_t cpt=0;
	if (cpt>=1000) {
		circular_shift(&PORTD);
		cpt=0;
	}
	cpt++;

}
// #############
int main(void)
{
	DDRD = 0b1111;
	DDRB = 0;
	out(SPEAKER);

	debug((char)1);

	while(1) {
		stepper();
		switch(PINB) {
			case 0b01111111:  // la
				play(141); 
				break;
			case 0b01111110: // sib
				play(133);
				break;
			case 0b01111100: // do
				play(118);
				break;
			case 0b01111000: // re
				play(105);
				break;
			case 0b01110000: // mib
				play(99);
				break;
			case 0b01101000: // mi 
				play(94);
				break;
			case 0b01100000: // fa
				play(88);
				break;
			case 0b01000000: // sol
				play(79);
				break;
			case 0b00100000: // lab
				play(74);
				break;
			case 0b00000000: // la (octave)
				play(70);
				break;
			case 0b00111111: // sib (octave)
				play(66);
				break;
			case 0b00111100: //do (octave)
				play(59);
				break;
			default:
				silence();
		}
	}
	return 0;
}
