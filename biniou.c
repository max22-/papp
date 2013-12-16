#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "macros.h"

#define SPEAKER 4,C

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

void la(void)
{
	cli();
	setup_timer();
	OCR0A = 141;
	sei();
}


void sib(void)
{
	cli();
	setup_timer();
	OCR0A = 133;
	sei();
}

void ut(void)
{
	cli();
	setup_timer();
	OCR0A = 118;
	sei();
}

void re(void)
{
	cli();
	setup_timer();
	OCR0A = 105;
	sei();
}

void mib(void)
{
	cli();
	setup_timer();
	OCR0A = 99;
	sei();
}

void mi(void)
{
	cli();
	setup_timer();
	OCR0A = 94;
	sei();
}


void fa(void)
{
	cli();
	setup_timer();
	OCR0A = 88;
	sei();
}

void sol(void)
{
	cli();
	setup_timer();
	OCR0A = 79;
	sei();
}

void lab(void)
{
	cli();
	setup_timer();
	OCR0A = 74;
	sei();
}

void la2(void)
{
	cli();
	setup_timer();
	OCR0A = 70;
	sei();
}

void sib2(void)
{
	cli();
	setup_timer();
	OCR0A = 66;
	sei();
}

void ut2(void)
{
	cli();
	setup_timer();
	OCR0A = 59;
	sei();
}

void silence(void)
{
	cli();
	TCCR0A=0;
	TCCR0B=0;
	TIMSK0 &= ~(1<<OCIE0A);
	off(SPEAKER);
	sei();
}

void debug(char d)
{
	PORTD = ~d;
}

int main(void)
{
	DDRD = 0b1111;
	DDRB = 0;
	out(SPEAKER);

	debug((char)1);
	_delay_ms(2000);
	debug(0);

	while(1) {
		switch(PINB) {
			case 0b01111111:
				la();	
				break;
			case 0b01111110:
				sib();	
				break;
			case 0b01111100:
				ut();
				break;
			case 0b01111000:
				re();
				break;
			case 0b01110000:
				mib();	
				break;
			case 0b01101000:
				mi();
				break;
			case 0b01100000:
				fa();
				break;
			case 0b01000000:
				sol();
				break;
			case 0b00100000:
				lab();
				break;
			case 0b00000000:
				la2();
				break;
			case 0b00111111:
				sib2();
				break;
			case 0b00111100:
				ut2();
				break;
			default:
				silence();
		}
	}
	return 0;
}
