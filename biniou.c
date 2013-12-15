#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "macros.h"

#define SPEAKER 0,B

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
	DDRC = 0;
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
		switch(PORTC) {
			case 0b111111:
				sib();	
				break;
			case 0b111110:
				ut();
				break;
			case 0b111100:
				re();
				break;
			case 0b111000:
				mib();	
				break;
			case 0b110100:
				mi();
				break;
			case 0b110000:
				fa();
				break;
			case 0b100000:
				sol();
				break;
			case 0b010000:
				la();
				break;
			case 0b000000:
				la();
				break;
			case 0b011111:
				sib2();
				break;
			case 0b011110:
				ut2();
				break;
			default:
				silence();
		}
	}
	return 0;
}
