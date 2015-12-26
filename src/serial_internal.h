/*
 * Author: Mark Paruzel <mark@markparuzel.com>
 * Date:  2015-12-15
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

#ifndef SERIAL_INTERNAL_H
#define SERIAL_INTERNAL_H

#include <avr/io.h>
#include <avr/interrupt.h>

#if ((RAMEND - RAMSTART) < 1024)
#   define SERIAL_BUFFER_SIZE 16
#else
#   define SERIAL_BUFFER_SIZE 64
#endif

#if defined(UBRRH)
#   define SERIAL_REGS_INIT { &UBRRH, &UBRRH, &UCSRA, &UCSRB, &UCSRC, &UDR }
#elif defined(UBRR0H)
#   define SERIAL_REGS_INIT { &UBRR0H, &UBRR0L, &UCSR0A, &UCSR0B, &UCSR0C, &UDR0 }
#endif

#if !defined(UPE) && defined(PE)
#   define UPE      PE
#endif

#if !defined(TXC) && defined(TXC0)
#   define DOR      DOR0
#   define FE       FE0
#   define MPCM     MPCM0
#   define RXCIE    RXCIE0
#   define RXC      RXC0
#   define RXEN     RXEN0
#   define TXC      TXC0
#   define TXEN     TXEN0
#   define UCSZ0    UCSZ00
#   define UCSZ1    UCSZ01
#   define UDRIE    UDRIE0
#   define UDRE     UDRE0
#   define UPM0     UPM00
#   define U2X      U2X0
#   define UPM1     UPM01
#   define UPE      UPE0
#   define USBS     USBS0
#endif

/* Currently, only one serial port is supported. */
#if defined(USART0_RX_vect)
#   define RX_VECTOR USART0_RX_vect
#   define TX_VECTOR USART0_UDRE_vect
#elif defined(USART_RX_vect)
#   define RX_VECTOR USART_RX_vect
#   define TX_VECTOR USART_UDRE_vect
#elif defined(USART_RXC_vect)
#   define RX_VECTOR USART_RXC_vect
#   define TX_VECTOR USART_UDRE_vect
#endif

/* Forward declaration for interrupt handler function. */
#if defined(RX_VECTOR) && defined(TX_VECTOR)
    ISR(RX_VECTOR);
    ISR(TX_VECTOR);
#else
#   error "TX and RX vectors not defined for this platform."
#endif

#endif /* SERIAL_INTERNAL_H */