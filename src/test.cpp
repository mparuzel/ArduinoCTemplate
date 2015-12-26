#include "Arduino.h"
extern "C" {
#include "serial.h"
}
const int pin = 13;

void setup(void)
{
	serial_init(9600);

	pinMode(pin, OUTPUT);
}

void loop(void)
{
	digitalWrite(pin, HIGH);
	delay(1000);
	
	serial_write(" | ", 3);
	
	digitalWrite(pin, LOW);
	delay(1000);
	
	if (serial_peek() >= 0) {
		char foo[64];
		
		int n = serial_read(foo, 64);
		serial_write(foo, n);
		
		delay(1000);
		serial_deinit();
		delay(1000);
		
		serial_init(9600);
		
		serial_write("reinit", 7);
	}
	
	//serial_write("world\n", 7);
}
