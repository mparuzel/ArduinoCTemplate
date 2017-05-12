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

#include "isr.h"

#include <avr/io.h>
#include <avr/interrupt.h>

/* ================================= MACROS ================================= */

/* Defines an ISR and forwards execution to a weak-defined function. */
#define DEFINE_ISR(isr, func) void __attribute__((weak)) func(void); \
                              inline ISR(isr) { func(); }

/* ======================= INTERRUPT SERVICE ROUTINES ======================= */

#if defined(__AVR_ATmega168__) ||  \
    defined(__AVR_ATmega168P__) || \
    defined(__AVR_ATmega328P__)

/* TODO: add support for other ATmega* chips. */
DEFINE_ISR(INT0_vect,           isr_int0);
DEFINE_ISR(INT1_vect,           isr_int1);
DEFINE_ISR(PCINT0_vect,         isr_pcint0);
DEFINE_ISR(PCINT1_vect,         isr_pcint1);
DEFINE_ISR(PCINT2_vect,         isr_pcint2);
DEFINE_ISR(WDT_vect,            isr_wdt);
DEFINE_ISR(TIMER2_COMPA_vect,   isr_timer2_comp_a);
DEFINE_ISR(TIMER2_COMPB_vect,   isr_timer2_comp_b);
DEFINE_ISR(TIMER2_OVF_vect,     isr_timer2_ovf);
DEFINE_ISR(TIMER1_CAPT_vect,    isr_timer1_event);
DEFINE_ISR(TIMER1_COMPA_vect,   isr_timer1_comp_a);
DEFINE_ISR(TIMER1_COMPB_vect,   isr_timer1_comp_b);
DEFINE_ISR(TIMER1_OVF_vect,     isr_timer1_ovf);
DEFINE_ISR(TIMER0_COMPA_vect,   isr_timer0_comp_a);
DEFINE_ISR(TIMER0_COMPB_vect,   isr_timer0_comp_b);
DEFINE_ISR(TIMER0_OVF_vect,     isr_timer0_ovf);
DEFINE_ISR(SPI_STC_vect,        isr_spi_stc);
DEFINE_ISR(USART_RX_vect,       isr_usart_rx);
DEFINE_ISR(USART_UDRE_vect,     isr_usart_udre);
DEFINE_ISR(USART_TX_vect,       isr_usart_tx);
DEFINE_ISR(ADC_vect,            isr_adc);
DEFINE_ISR(EE_READY_vect,       isr_ee_ready);
DEFINE_ISR(ANALOG_COMP_vect,    isr_analog_comp);
DEFINE_ISR(TWI_vect,            isr_twi);
DEFINE_ISR(SPM_READY_vect,      isr_spm_ready);

#endif
