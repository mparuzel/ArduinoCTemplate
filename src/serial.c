/*
 * Author: Mark Paruzel <mark@markparuzel.com>
 * Date:  2015-12-13
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

#include "serial.h"
#include "serial_internal.h"

/* =============================== STRUCTURES =============================== */

typedef struct {
    volatile uint8_t *ubrrh;
    volatile uint8_t *ubrrl;
    volatile uint8_t *ucsra;
    volatile uint8_t *ucsrb;
    volatile uint8_t *ucsrc;
    volatile uint8_t *udr;
} registers_t;

typedef struct {
    uint8_t buf[SERIAL_BUFFER_SIZE];
    volatile uint8_t head;
    volatile uint8_t tail;
} ring_buffer_t;

/* ================================ GLOBALS ================================= */

static registers_t _regs = SERIAL_REGS_INIT;
static ring_buffer_t _rx = { 0 };
static ring_buffer_t _tx = { 0 };
static FILE _serial_fp   = { 0 };

/* =========================== INTERRUPT HANDLERS =========================== */

void isr_usart_rx(void)
{
    /* If errors are detected, reset the interrupt. */
    if (*_regs.ucsra & (_BV(FE) | _BV(DOR) | _BV(UPE))) {
        *_regs.ucsrb &= ~(_BV(RXCIE) | _BV(RXEN));
        *_regs.ucsrb |=  (_BV(RXCIE) | _BV(RXEN));

        /* Discard byte. */
        *_regs.udr;

        return;
    }

    const uint8_t next_head = (_rx.head + 1) & (SERIAL_BUFFER_SIZE - 1);

    /* Add the new byte to the rx buffer, if space is available. */
    if (next_head != _rx.tail) {
        _rx.buf[_rx.head] = *_regs.udr;
        _rx.head = next_head;
    }
}

void isr_usart_udre(void)
{
    *_regs.udr = _tx.buf[_tx.tail];
    _tx.tail = (_tx.tail + 1) & (SERIAL_BUFFER_SIZE - 1);

    if (_tx.head == _tx.tail) {
        /* Disable interrupt due to lack of data to send. */
        *_regs.ucsrb &= ~(_BV(UDRIE));
    }
}

/* ========================== STDIO FUNCTIONAILIY =========================== */

static int serial_putc(char ch, FILE *fp)
{
    serial_write(&ch, 1);

    return 0;
}

static int serial_getc(FILE *fp)
{
    char c = 0;

    int num = serial_read(&c, 1);
    if (num) {
        return c;
    }

    /* Nothing to read. */
    return _FDEV_EOF;
}

/* ========================== SERIAL FUNCTIONALITY ========================== */

int serial_init(uint16_t baud)
{
    uint16_t baud_setting = (F_CPU / 4 / baud - 1) / 2;

    /* Determine the use of U2X mode. */
    if (baud_setting & 0xF000) {
        *_regs.ucsra = 0;
        baud_setting = (F_CPU / 8 / baud - 1) / 2;
    } else {
        *_regs.ucsra = _BV(U2X);
    }

    /* Set baud rate register. */
    *_regs.ubrrh = baud_setting >> 8;
    *_regs.ubrrl = baud_setting;

    /* Set 8-bit character sizes. */
    *_regs.ucsrc |= (_BV(UCSZ1) | _BV(UCSZ0));
#if defined(__AVR_ATmega8__)
    /* Some boards need two parity bits. */
    *_regs.ucsrc |= (_BV(USBS));
#endif

    /* Set up interrupts. */
    *_regs.ucsrb |=  (_BV(TXEN) | _BV(RXCIE) | _BV(RXEN));
    *_regs.ucsrb &= ~(_BV(UDRIE));

    return 0;
}

int serial_deinit(void)
{
    /* Disable RX and TX. */
    *_regs.ucsrb &= ~(_BV(UDRIE) | _BV(TXEN) | _BV(RXCIE) | _BV(RXEN));

    _rx.head = _rx.tail;
    _tx.head = _tx.tail;

    return 0;
}

int serial_peek(void)
{
    /* Return the next byte in the buffer. */
    if (_rx.head != _rx.tail) {
        return (int) _rx.buf[_rx.tail];
    }

    return -1;
}

int serial_read(void *buf, size_t sz)
{
    int written = 0;

    while (_rx.tail != _rx.head && written < (int) sz) {
        /* Write a byte at a time to the buffer provided. */
        *(uint8_t *) buf++ = _rx.buf[_rx.tail];

        written++;
        _rx.tail = (_rx.tail + 1) & (SERIAL_BUFFER_SIZE - 1);
    }

    return written;
}

int serial_write(const void *buf, size_t sz)
{
    for( ; sz != 0; --sz, ++buf) {
        const uint8_t next_head = (_tx.head + 1) & (SERIAL_BUFFER_SIZE - 1);

        /* Spin until space is available in the TX buffer. */
        while (next_head == _tx.tail) {
            *_regs.ucsrb |= _BV(UDRIE);
        };

        _tx.buf[_tx.head] = *(uint8_t *) buf;
        _tx.head = next_head;
    }

    /* Enable TX interrupt if it was disabled before. */
    *_regs.ucsrb |= _BV(UDRIE);

    return 0;
}

int serial_set_fdev(void)
{
    fdev_setup_stream(&_serial_fp, serial_putc, serial_getc, _FDEV_SETUP_RW);

    /* Override the standard io FILE streams. */
    stdout = &_serial_fp;
    stdin  = &_serial_fp;
    stderr = &_serial_fp;

    return 0;
}
