#include "Arduino.h"
extern "C" {
#include "serial.h"
#include "spi.h"
#include "digital.h"
}

extern "C" {
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/wdt.h>
#include "isr.h"
}

void setup(void)
{

	digital_pin_mode(PIN_B5, PIN_MODE_OUTPUT);

    serial_init(9600);
    serial_set_fdev();

    printf("Setup.\n");
}

void loop(void)
{

    unsigned long ms = micros();
    unsigned long now = 0;
    uint8_t g = 1;

    for (uint8_t i = 0; i < 255; ++i) { //116
        digital_write(PIN_B5, 1);
        digital_write(PIN_B5, 0);
    }

      now = micros();
    printf("Took: %d ms\n", now - ms);



    while (1) {};
}
