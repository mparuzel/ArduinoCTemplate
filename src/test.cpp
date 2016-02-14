#include "Arduino.h"
extern "C" {
#include "serial.h"
#include "spi.h"
#include "gpio.h"
}

extern "C" {
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
}



void setup(void)
{
	gpio_pin_mode(PIN_13, PIN_MODE_OUTPUT);

    serial_init(9600);
    serial_set_fdev();
}



void loop(void)
{

 while(1);

}
