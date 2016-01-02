/*
 * Author: Mark Paruzel <mark@markparuzel.com>
 * Date:  2015-12-31
 *
 * This file is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU Lesser General Public License as published by the 
 * Free Software Foundation; either version 2.1 of the License, or (at your 
 * option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this file; if not, see: <http://www.gnu.org/licenses/>.
 */

#include "spi.h"
#include "spi_internal.h"
#include "gpio.h"

/* =============================== STRUCTURES ============================== */

typedef struct {
    uint8_t map[4]; // Mapped to spi_pin_usage_t.
} pins_t;

typedef struct {
    volatile uint8_t *spcr;
    volatile uint8_t *spdr;
    volatile uint8_t *spsr;
} registers_t;

/* ================================ GLOBALS ================================ */

static registers_t _regs = { &SPCR, &SPDR, &SPSR };
static pins_t      _pins = { 0xFF, };

/* ========================== INTERRUPT HANDLERS =========================== */

// ISR SPI_STC_vect

/* ========================= LOCAL FUNCTIONALITY =========================== */

static uint8_t spi_exchange(uint8_t in)
{
    (void) *_regs.spsr; /* Flush previous SPIF. */
    
    /* Send byte and wait for completion. */
    *_regs.spdr = in;
    loop_until_bit_is_set(*_regs.spsr, SPIF);
    
    /* By reading SPDR, the SPIF flag is cleared. */
    return *_regs.spdr;
}

/* =========================== SPI FUNCTIONALITY =========================== */

int spi_init(uint32_t clock, spi_mode_t mode, spi_control_t ctl, spi_bit_order_t ord)
{
    const uint8_t MODE[]   = { [SPI_MODE_0] = _BV(CPHA),
                               [SPI_MODE_1] = _BV(CPOL),
                               [SPI_MODE_2] = _BV(CPOL) | _BV(CPHA),
                               [SPI_MODE_3] = 0 };
    const uint8_t CTL[]    = { [SPI_MASTER] = _BV(MSTR),
                               [SPI_SLAVE]  = 0 };
    const uint8_t BITORD[] = { [SPI_MSB]    = 0,
                               [SPI_LSB]    = _BV(DORD) };
    const uint8_t F_FLGS[] = { [0] /* 2 */  = _BV(SPE), /* SPI2X placeholder. */
                               [1] /* 4 */  = 0,
                               [2] /* 8 */  = _BV(SPR0) | _BV(SPE),
                               [3] /* 16 */ = _BV(SPR0),
                               [4] /* 32 */ = _BV(SPR1) | _BV(SPE),
                               [5] /* 64 */ = _BV(SPR0) | _BV(SPR1) | _BV(SPE),
                               [6] /* 128 */= _BV(SPR0) | _BV(SPR1) };
    const uint32_t F_DIV[] = { [0]          = F_CPU / 2,
                               [1]          = F_CPU / 4,
                               [2]          = F_CPU / 8,
                               [3]          = F_CPU / 16,
                               [4]          = F_CPU / 32,
                               [5]          = F_CPU / 64,
                               [6]          = F_CPU / 128 };
    
    uint8_t i = 0;
    
    /* Determine the flags that closly represent the clock speed. */
    while (i < 6 && clock >= F_DIV[i]) {
        ++i;
    }

    /* Set SPCR and SPSR (_BV(SPE) is used as placeholder for SPI2X flag). */
    *_regs.spsr = (F_FLGS[i] & _BV(SPE)) ? _BV(SPI2X) : 0;
    *_regs.spcr = _BV(SPE) | F_FLGS[i] | MODE[mode] | CTL[ctl] | BITORD[ord];

    return 0;
}

int spi_deinit(void)
{
    *_regs.spcr = 0;
    *_regs.spsr = 0;    
    _pins = (pins_t) { { 0xFF, } };
    
    return 0;
}

int spi_pin_setup(uint8_t pin, spi_pin_usage_t usage)
{
    /* PIN mode set for SPI slave (XOR will swap if MSTR is set). */
    const uint8_t PIN_MODE[] = { [SPI_PIN_MISO] = PIN_MODE_OUTPUT,
                                 [SPI_PIN_MOSI] = PIN_MODE_INPUT,
                                 [SPI_PIN_SCK]  = PIN_MODE_INPUT,
                                 [SPI_PIN_SS]   = PIN_MODE_INPUT };
    
    /* Invert the pin mode if the control register is set to slave mode. */
    const uint8_t is_mstr = (*_regs.spcr & _BV(MSTR)) >> MSTR;
    const pin_mode_t mode = (pin_mode_t) ((is_mstr ^ PIN_MODE[usage]) & 0x01);
    
    /* Normalize SS pin to deselected state. */
    if (usage == SPI_PIN_SS) {
        spi_deselect(pin);
    }
    
    /* Set the pin mode and save it for later use. */
    int rc = gpio_pin_mode(pin, mode);
    if (!rc) {
        _pins.map[usage] = pin;
    }
    
    return rc;
}

int spi_select(uint8_t ss_pin)
{
    /* Notify slave of incoming data. */
    return gpio_digital_write(ss_pin, 0);
}

int spi_deselect(uint8_t ss_pin)
{
    /* Release the slave to signal the end of data transfer. */
    return gpio_digital_write(ss_pin, 1);
}

int spi_read(void)
{
    return (int) spi_exchange(0xFF);
}

int spi_write(uint8_t byte)
{
    return (int) spi_exchange(byte);
}
