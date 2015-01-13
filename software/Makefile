TARGET := temp
CC := avr-gcc
OBJCOPY := avr-objcopy
CFLAGS := -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p
#LDFLAGS := -Wl,-u,vfprintf -lprintf_flt -lm
AVRDUDE ?= avrdude
PROGRAMMER ?= arduino

all: $(TARGET).hex
$(TARGET).hex: $(TARGET)
	$(OBJCOPY) -O ihex -R .eeprom $< $@
$(TARGET): $(TARGET).o pin.o lcd.o uart.o
	$(CC) $(LDFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: install
install: $(TARGET).hex
	if test "$(PROGRAMMER)" = "arduino"; then \
	  $(AVRDUDE) -c $(PROGRAMMER) -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$(TARGET).hex; \
	else \
	  $(AVRDUDE) -c $(PROGRAMMER) -p ATMEGA328P -b 115200 -U flash:w:$(TARGET).hex; \
	fi

.PHONY: clean
clean:
	rm -f $(TARGET).hex $(TARGET) *.o *~
