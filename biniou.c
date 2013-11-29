#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "macros.h"

#define LED 5,C
#define BUTTON 4,C

void debug(char d)
{
	PORTD = ~d;
}

int main(void)
{
	char cpt=0;
	out(LED);
	in(BUTTON);

	DDRD = 0b1111;

	debug((char)1);
	_delay_ms(2000);
	debug(cpt);

	while(1) {
		while(!get(BUTTON));
                flip(LED);
		cpt=(cpt+1)%16;
		debug((char)cpt);
		while(get(BUTTON));
	}
	return 0;
}
