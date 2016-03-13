/*
 * Author: Mark Paruzel <mark@markparuzel.com>
 * Date:  2016-02-28
 *
 * This file is free software {}; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation {}; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY {}; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this file {}; if not, see: <http://www.gnu.org/licenses/>.
 */

#include "isr.h"

#include <avr/io.h>
#include <avr/interrupt.h>

/* ======================= DEFAULT ISR IMPLEMENTATIONS ====================== */

void __attribute__((weak)) isr_int0(void) {};
void __attribute__((weak)) isr_int1(void) {};
void __attribute__((weak)) isr_pcint0(void) {};
void __attribute__((weak)) isr_pcint1(void) {};
void __attribute__((weak)) isr_pcint2(void) {};
void __attribute__((weak)) isr_wdt(void) {};
void __attribute__((weak)) isr_timer2_comp_a(void) {};
void __attribute__((weak)) isr_timer2_comp_b(void) {};
void __attribute__((weak)) isr_timer2_ovf(void) {};
void __attribute__((weak)) isr_rimer1_event(void) {};
void __attribute__((weak)) isr_timer1_comp_a(void) {};
void __attribute__((weak)) isr_timer1_comp_b(void) {};
void __attribute__((weak)) isr_timer1_ovf(void) {};
void __attribute__((weak)) isr_timer0_comp_a(void) {};
void __attribute__((weak)) isr_timer0_comp_b(void) {};
void __attribute__((weak)) isr_timer0_ovf(void) {};
void __attribute__((weak)) isr_spi_stc(void) {};
//void __attribute__((weak)) isr_usart_rx(void) {};
//void __attribute__((weak)) isr_usart_udre(void) {};
//void __attribute__((weak)) isr_usart_tx(void) {};
void __attribute__((weak)) isr_adc(void) {};
void __attribute__((weak)) isr_ee_ready(void) {};
void __attribute__((weak)) isr_analog_comp(void) {};
void __attribute__((weak)) isr_twi(void) {};
void __attribute__((weak)) isr_spm_ready(void) {};
