#include "Arduino.h"
#include "HardwareSerial.h"

const int pin = 13;

void setup(void)
{
	Serial.begin(9600);
	pinMode(pin, OUTPUT);
}

void loop(void)
{
	digitalWrite(pin, HIGH);
	delay(100);
	Serial.print("Hello ");
	digitalWrite(pin, LOW);
	delay(100);
	Serial.print("world\n");
}
