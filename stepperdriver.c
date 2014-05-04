#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "macros.h"

#define LED 7,B

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
	uint8_t s, new_s; // used to memorize step pins to detect raising front
	uint8_t rf=0; // raising front
	uint8_t cpt[3] = {0, 0, 0};
	uint8_t c[3] = {0, 0, 0}; // step counter for each motor
	uint8_t m[3] = {0, 0, 0}; // temp storage for motor output
	uint8_t i;
	// Direction pins : C4, C5, B6
	uint8_t dir_bit[3] = {4, 5, 6};
	volatile uint8_t *dir_port[3] = {&PINC, &PINC, &PINB};

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

		for(i=0;i<1;i++) { //debug !!!!!!!!!!!!!!!
			if(rf&(1<<i)) { // raising front on B0 (i=0), B1 (i=1), B2 (i=2)
				flip(LED);
				cpt[i]++;
				if(cpt[i]>=100) {
					cpt[i]=0;	
					if(*dir_port[i]&(1<<dir_bit[i]))
						c[i]++;
					else 
						c[i]--;
					m[i] = half_step[c[i]&0b111];
				}	
			}
		}

		PORTC = m[0];
		PORTD = m[1] | m[2] << 4;
	}
	return 0;
}
