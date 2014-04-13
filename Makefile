CC=avr-gcc
OBJCOPY=avr-objcopy
TARGET=plotterbot

CFLAGS=-g -mmcu=atmega328p -Wall -Wstrict-prototypes -Os -mcall-prologues

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).out
	$(OBJCOPY) -R .eeprom -O ihex $(TARGET).out $(TARGET).hex

$(TARGET).out: $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET).out -Wl,-Map,$(TARGET).map $(TARGET).o

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

clean:
	rm -f *.o *.map *.out *.hex

unpublish:
	rm -f ~/public_html/$(TARGET).tar.gz
publish: all unpublish
	rm -f ../$(TARGET).tar.gz
	tar cfvz ../$(TARGET).tar.gz .
	mv ../$(TARGET).tar.gz ~/public_html/


prog:
	sudo avrdude -p atmega328p -c gpio -P gpio -U flash:w:$(TARGET).hex

cprog: $(TARGET).hex prog

install_pkgs:
	sudo apt-get install gcc-avr binutils-avr avr-libc avrdude 

	
