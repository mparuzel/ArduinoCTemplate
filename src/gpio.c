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

#include "gpio.h"
#include "gpio_internal.h"

/* ================================= MACROS ================================= */

#define LIKELY(x)   __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

/* =========================== INTERRUPT HANDLERS ===========================

ISR(INT0_vect) {
    intFunc[EXTERNAL_INT_0]();
}
*/



/* =========================== GPIO FUNCTIONALITY =========================== */

/* TODO: remove dependency on this. */
#include "Arduino.h"

/* From arduino_pins.h */
#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))


int gpio_attach_irq(uint8_t pin, void (*func)(void), interrupt_mode_t mode)
{
    uint8_t intr = digitalPinToInterrupt(pin);
    if (intr == NOT_AN_INTERRUPT) {
        return -1;
    }

    attachInterrupt(intr, func, (int) mode);
    return (int) 0;
}

int gpio_detach_irq(uint8_t pin)
{
    detachInterrupt(pin);
    return 0;
}
