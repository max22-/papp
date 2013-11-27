#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "macros.h"

#define LED 3,C
#define BUTTON 4,C
#define SEND 5,C 


int capsense(void)
{
	int t=0;
	on(SEND);
	_delay_ms(1);
	off(SEND);
	for(t=0;t<=65535;t++) {
		if(!get(BUTTON))
			break;
	}
	return t;
}

void debug(char d)
{
	PORTD = ~d;
}

int main(void)
{
	int thresh=0;
	int t=0;

	out(LED);
	in(BUTTON);
	out(SEND);

	DDRD = 0b1111;

	thresh = 125 * capsense() / 100;

	debug((char)(thresh/(255*16)));
	_delay_ms(2000);
	debug((char)(thresh % 256));

	while(1) {
		debug((char)2);
		do {
			t = capsense();
		} while (t < thresh);
		flip(LED);
		debug((char)3);
		do {
			t = capsense();
		} while (t >= thresh);

	}
	return 0;
}
