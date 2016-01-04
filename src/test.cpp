#include "Arduino.h"
extern "C" {
#include "serial.h"
#include "spi.h"
}


void setup(void)
{
	serial_init(9600);
	
	//pinMode(13, OUTPUT);
	int rc = 0;
	
	rc = spi_init_pin(10, SPI_PIN_SS);
	if (rc == 1) serial_write("1",1); else serial_write("0", 1);
	rc = spi_init_pin(11, SPI_PIN_MOSI);
	if (rc == 1) serial_write("1",1); else serial_write("0", 1);
	rc = spi_init_pin(12, SPI_PIN_MISO);
	if (rc == 1) serial_write("1",1); else serial_write("0", 1);
	rc = spi_init_pin(13, SPI_PIN_SCK);
	if (rc == 1) serial_write("1",1); else serial_write("0", 1);
	
	
	serial_write(" ", 1);
	rc = spi_init(F_CPU/2, SPI_MODE_0, SPI_MASTER, SPI_MSB);
	if (rc & (1 << 0)) serial_write("1",1);
	if (rc & (1 << 1)) serial_write("2",1);
	if (rc & (1 << 2)) serial_write("3",1);
	if (rc & (1 << 3)) serial_write("4",1);
	if (rc & (1 << 4)) serial_write("5",1);
	if (rc & (1 << 5)) serial_write("6",1);
	if (rc & (1 << 6)) serial_write("7",1);
	if (rc & (1 << 7)) serial_write("8",1);
	
	serial_write(" ", 1);
	
	if (SPCR & (1 << 0)) serial_write("1",1);
	if (SPCR & (1 << 1)) serial_write("2",1);
	if (SPCR & (1 << 2)) serial_write("3",1);
	if (SPCR & (1 << 3)) serial_write("4",1);
	if (SPCR & (1 << 4)) serial_write("5",1);
	if (SPCR & (1 << 5)) serial_write("6",1);
	if (SPCR & (1 << 6)) serial_write("7",1);
	if (SPCR & (1 << 7)) serial_write("8",1);
	
	serial_write(" ", 1);
}

void loop(void)
{
	delay(1000);

	serial_write("<", 1);
	
	spi_begin();
	spi_select(13);
	
	serial_write(":", 1);

	int rc = spi_write(0xFF);
	if (rc != 0xff) {
		serial_write("rc ", 3);
	}
	
	serial_write(":", 1);

	rc = spi_read();
	if (rc != 0xFF) {
		serial_write("!FF ", 4);
	}
	
	serial_write(":", 1);

	spi_deselect(13);
	spi_end();

	
	serial_write(">", 1);
	
}
