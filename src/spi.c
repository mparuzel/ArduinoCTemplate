/*
 * Author: Mark Paruzel <mark@markparuzel.com>
 * Date:  2015-12-31
 *
 * This file is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this file; if not, see: <http://www.gnu.org/licenses/>.
 */

#include "spi.h"
#include "spi_internal.h"
#include "digital.h"

/* =============================== STRUCTURES =============================== */

typedef struct {
    uint8_t spcr;
    uint8_t spsr;
} config_t;

typedef struct {
    volatile uint8_t *spcr;
    volatile uint8_t *spdr;
    volatile uint8_t *spsr;
} registers_t;

/* ================================ GLOBALS ================================= */

static const registers_t _regs = SPI_REGS_INIT;
static config_t          _cfg  = { 0, };

/* =========================== INTERRUPT HANDLERS =========================== */

// ISR SPI_STC_vect

/* =========================== SPI FUNCTIONALITY ============================ */

int spi_init(uint32_t clk, spi_mode_t m, spi_control_t ctl, spi_sbit_t sb)
{
    const uint8_t MODE[]   = { [SPI_MODE_0] = _BV(CPHA),
                               [SPI_MODE_1] = _BV(CPOL),
                               [SPI_MODE_2] = _BV(CPOL) | _BV(CPHA),
                               [SPI_MODE_3] = 0 };
    const uint8_t CTL[]    = { [SPI_MASTER] = _BV(MSTR),
                               [SPI_SLAVE]  = 0 };
    const uint8_t SIGBIT[] = { [SPI_MSB]    = 0,
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
    uint32_t freq = 0;

    /* Determine the flags that closly represent the clock speed. */
    for (freq = F_CPU / 2; i < 6 && clk < freq; freq >>= 1) {
        ++i;
    }

    /* Setup SPCR and SPSR (_BV(SPE) in F_FLGS is a placeholder for SPI2X). */
    _cfg.spsr = (F_FLGS[i] & _BV(SPE)) ? _BV(SPI2X) : 0;
    _cfg.spcr = _BV(SPE) | F_FLGS[i] | MODE[m] | CTL[ctl] | SIGBIT[sb];

    return 0;
}

int spi_begin(pin_t ss_pin)
{
    /* If the MSTR flag is set, this value will determine if the pin mode is
     * flipped to an opposite value. */
    const uint8_t is_mstr = (_cfg.spcr & _BV(MSTR)) >> MSTR;
    const pin_mode_t mode = is_mstr ^ PIN_MODE_INPUT;

    /* If acting as master, set SS to HIGH to enable pull-up resistor. */
    digital_write(ss_pin, is_mstr);
    digital_pin_mode(ss_pin, mode);

    /* Apply settings. */
    *_regs.spcr = _cfg.spcr;
    *_regs.spsr = _cfg.spsr;

    /* Setting the pins here avoids accidentally clocking in a single bit in
     * some cases. */
    digital_pin_mode(PIN_MOSI, mode);
    digital_pin_mode(PIN_SCK, mode);

    return 0;
}

void spi_end(void)
{
    *_regs.spcr = 0;
    *_regs.spsr = 0;
}


int spi_exchange(uint8_t in)
{
    /* Queue byte for transfer. */
    *_regs.spdr = in;

    /* Apparently, this NOP introduces a small delay before loop is started
     * which allows the SPDR register to be read. Such a delay yields an extra
     * 10% speed boost. Don't as why; I read it in the Arduino SPI code. */
    __asm__ __volatile__ ("nop");
    loop_until_bit_is_set(*_regs.spsr, SPIF);

    /* By reading SPDR, the SPIF flag is cleared. */
    return *_regs.spdr;
}
