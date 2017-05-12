/*
 * Author: Mark Paruzel <mark@markparuzel.com>
 * Date:  2016-02-13
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

#ifndef ISR_H
#define ISR_H

#include <stdint.h>
#include <stddef.h>

/* ======================= INTERRUPT SERVICE ROUTINES ======================= */

/* The following functions are defined as weak; meaning their implementation
 * can be overridden by strongly defined functions. This list does not contain
 * ISRs for all ATMega* platforms; that is a task for a later time.
 */

/* External Interrupt Request 0. */
void isr_int0(void);

/* External Interrupt Request 1. */
void isr_int1(void);

/* Pin Change Interrupt Request 0. */
void isr_pcint0(void);

/* Pin Change Interrupt Request 1. */
void isr_pcint1(void);

/* Pin Change Interrupt Request 2. */
void isr_pcint2(void);

/* Watchdog Time-out Interrupt. */
void isr_wdt(void);

/* Timer/Counter 2 Compare Match A. */
void isr_timer2_comp_a(void);

/* Timer/Counter 2 Compare Match B. */
void isr_timer2_comp_b(void);

/* Timer/Counter 2 Overflow. */
void isr_timer2_ovf(void);

/* Timer/Counter 1 Capture Event. */
void isr_rimer1_event(void);

/* Timer/Counter 1 Compare Match A. */
void isr_timer1_comp_a(void);

/* Timer/Counter 1 Compare Match B. */
void isr_timer1_comp_b(void);

/* Timer/Counter 1 Overflow. */
void isr_timer1_ovf(void);

/* Timer/Counter 0 Compare Match A. */
void isr_timer0_comp_a(void);

/* Timer/Counter 0 Compare Match B. */
void isr_timer0_comp_b(void);

/* Timer/Couner 0 Overflow. */
void isr_timer0_ovf(void);

/* SPI Serial Transfer Complete. */
void isr_spi_stc(void);

/* USART Rx Complete (used in serial.c). */
void isr_usart_rx(void);

/* USART, Data Register Empty (used in serial.c). */
void isr_usart_udre(void);

/* USART Tx Complete (used in serial.c). */
void isr_usart_tx(void);

/* ADC Conversion Complete. */
void isr_adc(void);

/* EEPROM Ready. */
void isr_ee_ready(void);

/* Analog Comparator. */
void isr_analog_comp(void);

/* Two-wire Serial Interface. */
void isr_twi(void);

/* Store Program Memory Read. */
void isr_spm_ready(void);

#endif
