#include "Arduino.h"
extern "C" {
#include "serial.h"
#include "spi.h"
}


void setup(void)
{
	serial_init(9600);
	
	spi_init(8E6, SPI_MODE_0, SPI_MASTER, SPI_MSB);
	spi_pin_setup(10, SPI_PIN_SS);
	spi_pin_setup(11, SPI_PIN_MOSI);
	spi_pin_setup(12, SPI_PIN_MISO);
	spi_pin_setup(13, SPI_PIN_SCK);

	//pinMode(pin, OUTPUT);
}

void loop(void)
{
	//digitalWrite(pin, HIGH);
	delay(1000);
	
	serial_write(" | ", 3);
	
	//digitalWrite(pin, LOW);
	//delay(1000);
	
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
