#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "macros.h"

#define DIR1 4,C
#define DIR2 5,C
#define DIR3 6,B

#define LED 7,B

#define MOD(a,b) (((a)%(b)) < 0 ? ((a)%(b)+(b)) : ((a)%(b)))

uint8_t half_step[] = {0b0001, 0b0011, 0b0010, 0b0110, 0b0100, 0b1100, 0b1000, 0b1001};
uint8_t c = 0;

void blink(uint8_t n) {
	int i;
	for(i=0;i<n;i++) {
		flip(LED);	
		_delay_ms(100);
		flip(LED);
		_delay_ms(100);
	}
}

int main(void)
{
	uint8_t s, new_s; // used to memorize step pins to detect raising front
	uint8_t rf=0; // raising front
	uint8_t m1=0, m2=0, m3=0; // temp storage for motor output
	uint8_t cpt=0;

	// B0 : step1, B1 : step2, B2 : step3, B6 : dir3, B7 : led
	DDRB = 0b10000000;
	// C0 C1 C2 C3 : motor 1, C4 : dir1, c5 : dir2
	DDRC = 0b00001111;
	// D0 D1 D2 D3 : motor 2, D4 D5 D6 D7 : motor 3
	DDRD = 0b11111111;

	blink(10);

	new_s = PINB;
	while(1) {
		s=new_s;
		new_s=PINB;
		rf = ~s&new_s;
		if(rf&1) { // raising front on B0
			cpt++;
			if(cpt>=100) {
				cpt=0;
				if(get(DIR1)) {
					c = MOD(c+1, 8);
				}
				else {
					c = MOD(c-1, 8);
				}
				m1 = half_step[c];
			}
		}
		PORTC = m1;
		PORTD = m2 | m3 << 4;
	}
	return 0;
}
