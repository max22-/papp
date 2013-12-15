#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "macros.h"

#define SPEAKER 4,C

ISR(TIMER0_COMPA_vect)
{
	flip(SPEAKER);
}

void sib(void)
{
	cli();
	OCR0A = 133;
	TIMSK0 |= (1<<OCIE0A);
	sei();
}

void ut(void)
{
	cli();
	OCR0A = 118;
	TIMSK0 |= (1<<OCIE0A);
	sei();
}

void re(void)
{
	cli();
	OCR0A = 105;
	TIMSK0 |= (1<<OCIE0A);
	sei();
}

void mib(void)
{
	cli();
	OCR0A = 99;
	TIMSK0 |= (1<<OCIE0A);
	sei();
}

void mi(void)
{
	cli();
	OCR0A = 94;
	TIMSK0 |= (1<<OCIE0A);
	sei();
}


void fa(void)
{
	cli();
	OCR0A = 88;
	TIMSK0 |= (1<<OCIE0A);
	sei();
}

void sol(void)
{
	cli();
	OCR0A = 79;
	TIMSK0 |= (1<<OCIE0A);
	sei();
}

void lab(void)
{
	cli();
	OCR0A = 74;
	TIMSK0 |= (1<<OCIE0A);
	sei();
}

void la(void)
{
	cli();
	OCR0A = 70;
	TIMSK0 |= (1<<OCIE0A);
	sei();
}

void sib2(void)
{
	cli();
	OCR0A = 66;
	TIMSK0 |= (1<<OCIE0A);
	sei();
}

void ut2(void)
{
	cli();
	OCR0A = 59;
	TIMSK0 |= (1<<OCIE0A);
	sei();
}

void silence(void)
{
	cli();
	TIMSK0 |= (0<<OCIE0A);
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

	cli();
	TCCR0B |= (1<<CS01);
	TCCR0A |= (1<<WGM01);
	OCR0A = 133;
	TIMSK0 |= (1<<OCIE0A);
	sei();


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
				la();
				break;
			case 0b00000000:
				la();
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
