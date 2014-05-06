CC=avr-gcc
DEVICE = atmega328p
PROGRAMMER = -c gpio -P gpio
OBJCOPY=avr-objcopy
TARGET=stepperdriver
CFLAGS=-g -mmcu=$(DEVICE) -Wall -Wstrict-prototypes -Os -mcall-prologues

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).out
	$(OBJCOPY) -R .eeprom -O ihex $(TARGET).out $(TARGET).hex

$(TARGET).out: $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET).out -Wl,-Map,$(TARGET).map $(TARGET).o

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

$(TARGET).s: $(TARGET).c
	$(CC) $(CFLAGS) -S $(TARGET).c

cpp:
	$(CC) $(CFLAGS) -E $(TARGET).c
clean:
	rm -f *.o *.map *.out *.hex *.s

install: all
	sudo avrdude -p $(DEVICE) $(PROGRAMMER) -U flash:w:$(TARGET).hex -F


	
