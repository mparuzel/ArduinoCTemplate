/*
 * Author: Mark Paruzel <mark@markparuzel.com>
 * Date:  2016-02-28
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

#ifndef IRQ_H
#define IRQ_H

#include "board.h"

/* =============================== STRUCTURES =============================== */

typedef enum {
    IRQ_CHANGE  = 1,
    IRQ_FALLING = 2,
    IRQ_RISING  = 3
} irq_mode_t;

/* ========================= EXTERNAL INTERRUPT API ========================= */

/* Enables an external interrupt. Once enabled, the interrupt handler isr_int*()
 * will fire when a signal is detected on the pin.
 */
int irq_external_enable(uint8_t int_num, irq_mode_t mode);

/* Disables external interrupt.
 */
int irq_external_disable(uint8_t int_num);

/* ======================== PIN CHANGE INTERRUPT API ======================== */

/* Enables an pin change interrupt. A pin change ISR handles a change on pins
 * marked as PCINT##.
 */
int irq_pin_change_enable(uint8_t pcint_num);

/* Disables the a pin change trigger.
 */
int irq_pin_change_disable(uint8_t pcint_num);

#endif
