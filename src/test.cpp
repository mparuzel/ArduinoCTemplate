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
#include <avr/wdt.h>
#include "interrupt.h"

extern int aaaa;
/*
void isr_timer0(void)
{
    aaaa=10;
}
*/

}

//initialize watchdog
void WDT_Init(void)
{
//disable interrupts
cli();
TIMSK1 |= (1<<TOIE0);                        // Overflow Interrupt enable
TCCR1A |= ((1<<CS00) | (1<<CS02));            // Prescaler 128
TCNT1 = 0;
   //Enable Global Interrupts
   sei();

}

void setup(void)
{
    	// Disable all interrupts
	WDT_Init();


	gpio_pin_mode(PIN_13, PIN_MODE_OUTPUT);

    serial_init(9600);
    serial_set_fdev();
}



void loop(void)
{

 while(1) {
          gpio_digital_write(PIN_13, 1);
     _delay_ms(1000);
     gpio_digital_write(PIN_13, 0);
     _delay_ms(1000);
     printf("%d\n", aaaa);
 }

}
