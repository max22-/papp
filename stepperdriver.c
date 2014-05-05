#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "macros.h"

#define LED 5,C

uint8_t half_step[] = {0b0001, 0b0011, 0b0010, 0b0110, 0b0100, 0b1100, 0b1000, 0b1001};

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
	uint8_t pb, new_pb; // used to memorize step pins to detect raising front
	uint8_t rf=0, dir=0, inc=0, dec=0; // raising front, ...
	uint8_t cpt=0;
	uint8_t c1=0, c2=0, c3=0; // step counter for each motor
	uint8_t m1=0, m2=0, m3=0; // temp storage for motor output

	// B0 : step1, B1 : step2, B2 : step3, B4 : dir1, B5 : dir2, B6 : dir3
	DDRB = 0b00000000;
	// C5 : LED
	DDRC = 0b00101111;
	// D0 D1 D2 D3 : motor 2, D4 D5 D6 D7 : motor 3
	DDRD = 0b11111111;

	blink(10);

	new_pb = PINB;
	while(1) {
		pb=new_pb;
		new_pb=PINB;
		rf = (~pb&new_pb)&0b111;
		dir = (new_pb >> 3) & 0b111;
		inc = rf & dir;
		dec = rf & (~dir);
		if(rf!=0) {
			flip(LED); // Debug
			cpt++;
			if(cpt>=100) {
				cpt=0;
				//flip(LED); //Debug !!

				c1 += inc & 0b001;
				c1 -= dec & 0b001;
				c2 += (inc & 0b010 )>>1;
				c2 += (dec & 0b010 )>>1;
				c3 += (inc & 0b100 )>>2;
				c3 += (dec & 0b100 )>>2;

				m1 = half_step[c1&0b111];
				m2 = half_step[c2&0b111];
				m3 = half_step[c3&0b111];


				PORTC = m1;
				PORTD = m2 | m3 << 4;
			}
		}

	}
	return 0;
}
