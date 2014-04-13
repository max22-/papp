#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "macros.h"

#define DEBOUNCE 1
#define STEP 0,B
#define DIRECTION 1,B

#define MOD(a,b) (((a)%(b)) < 0 ? ((a)%(b)+(b)) : ((a)%(b)))

uint8_t half_step[] = {0b1110, 0b1100, 0b1101, 0b1001, 0b1011, 0b0011, 0b0111, 0b0110};
uint8_t c = 0;

void forward(volatile uint8_t *p)
{
	*p = ((*p<<1) & 0xF) | ( (*p & 0xF) >> 3);
}

void backward(volatile uint8_t *p)
{
	*p = ((*p>>1) & 0xF) | ( (*p & 0xF) << 3);
}

void blink(uint8_t n) {
	int i;
	for(i=0;i<n;i++) {
		PORTD = 0b1110;
		_delay_ms(100);
		PORTD = 0b1111;
		_delay_ms(100);
	}
}

ISR(PCINT0_vect) {
	if((PINB & (1 << PINB0)) == 0) 
		return;
	if(DEBOUNCE) {
		_delay_ms(100);
	}
	if(get(DIRECTION)) {
		c = MOD(c+1, 8);
	}
	else {
		c = MOD(c-1, 8);
	}
	PORTD=half_step[c];
	//blink(10);
}




int main(void)
{
	DDRD = 0b1111;
	DDRB = 0;

	PCICR |= (1 <<PCIE0);
	PCMSK0 |= (1 << PCINT0);
	sei();

	blink(10);

	while(1) {

	}
	return 0;
}
