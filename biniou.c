#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "macros.h"

#define LED 5,C
#define BUTTON1 4,C
#define BUTTON2 3,C

void debug(char d)
{
	PORTD = ~d;
}

int main(void)
{
	char cpt=0;
	out(LED);
	in(BUTTON1);
	in(BUTTON2);

	DDRD = 0b1111;

	debug((char)1);
	_delay_ms(2000);
	debug(cpt);

	while(1) {
		if(!get(BUTTON1) && !get(BUTTON2))
			on(LED);
		else
			off(LED);
	}
	return 0;
}
