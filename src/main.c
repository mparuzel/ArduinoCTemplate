#include "Arduino.h"

#include "serial.h"
#include "spi.h"
#include "digital.h"



#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/wdt.h>
#include "isr.h"

int main(void)
{
	init();
    serial_init(9600);
    serial_set_fdev();

    printf("Setup.\n");
	digital_pin_mode(PIN_B5, PIN_MODE_OUTPUT);

	for (;;) {
        digital_write(PIN_B5, 1);
        delay(1000);
        digital_write(PIN_B5, 0);
        delay(1000);
        printf("asdf\n");
	}

	return 0;
}
