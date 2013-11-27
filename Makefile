CC=avr-gcc
OBJCOPY=avr-objcopy
PARPORT=/dev/parport0
TARGET=biniou

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


prog_erase:
	sudo uisp -dlpt=$(PARPORT) --erase -dprog=dapa

prog_burn:
	sudo uisp -dlpt=$(PARPORT) --upload if=$(TARGET).hex -dprog=dapa -dno-poll -v

prog_verif:
	sudo uisp -dlpt=$(PARPORT) --verify if=$(TARGET).hex -dprog=dapa -dno-poll -v

prog: prog_erase prog_burn prog_verif

cprog: $(TARGET).hex prog_erase prog_burn prog_verif

install_pkgs:
	sudo apt-get install gcc-avr binutils-avr avr-libc uisp

