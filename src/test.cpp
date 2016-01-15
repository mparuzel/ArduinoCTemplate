#include "Arduino.h"
extern "C" {
#include "serial.h"
#include "spi.h"
}
	const char hex[] = "0123456789ABCDEF--";

static void dump_hex(uint8_t d) 
{
	serial_write("0x", 2);
	serial_write(&hex[(d&0xF0) >> 4], 1);
	serial_write(&hex[d&0xF], 1);
}



void setup(void)
{
	serial_init(9600);
	
	//pinMode(13, OUTPUT);
	int rc = 0;
	
	rc = spi_init_pin(10, SPI_PIN_SS);
	rc = spi_init_pin(11, SPI_PIN_MOSI);
	rc = spi_init_pin(12, SPI_PIN_MISO);
	rc = spi_init_pin(13, SPI_PIN_SCK);
	
	rc = spi_init(F_CPU/2, SPI_MODE_0, SPI_MASTER, SPI_MSB);

}


void loop(void)
{
	delay(1000);

	serial_write("<", 1);
	
	int rc = spi_begin();
	if (rc == -1)
		serial_write("adf", 3);

	serial_write(" SPCR:", 6);
	dump_hex(SPCR);
	serial_write(" SPSR:", 6);
	dump_hex(SPSR);
	serial_write(">\n", 2);	

	
	
	

	for (byte regAddr = 1; regAddr <= 100; regAddr++)
	{
		spi_select(10);
		spi_exchange(0x3c & 0x7F);
		uint8_t b = spi_exchange(0);		
		spi_deselect(10);
		
		dump_hex(regAddr);
		serial_write(" -> ", 4);
		dump_hex(b);
		serial_write("\n", 1);

		delay(100);
	}
	
	
	spi_end();
	
	
	serial_write(">\n", 2);
	delay(5000);
	while (1) {};
}
