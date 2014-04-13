#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "macros.h"

#define SIZE 100
#define DELAY 100

void forward(volatile uint8_t *p)
{
	*p = ((*p<<1) & 0xF) | ( (*p & 0xF) >> 3);
}

void backward(volatile uint8_t *p)
{
	*p = ((*p>>1) & 0xF) | ( (*p & 0xF) << 3);
}

int main(void)
{
	int i;
	DDRD = 0b1111;
	DDRC = 0b1111;

	PORTC = 0b1110;
	PORTD = 0b1110;

	while(1) {
		for(i=0;i<SIZE;i++) {
			forward(&PORTC);
			_delay_ms(DELAY);
		}	
		for(i=0;i<SIZE;i++) {
			forward(&PORTD);
			_delay_ms(DELAY);
		}	
		for(i=0;i<SIZE;i++) {
			backward(&PORTC);
			_delay_ms(DELAY);
		}	
		for(i=0;i<SIZE;i++) {
			backward(&PORTD);
			_delay_ms(DELAY);
		}	

	}
	return 0;
}
