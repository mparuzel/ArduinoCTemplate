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

#ifndef GPIO_H
#define GPIO_H

#include "board.h"

#include <stdint.h>
#include <stddef.h>

/* =============================== STRUCTURES =============================== */

typedef enum {
	PIN_MODE_OUTPUT         = 0,
	PIN_MODE_INPUT          = 1,
	PIN_MODE_INPUT_PULLUP   = 2
} pin_mode_t;

typedef enum {
    IRQ_CHANGE  = 1,
    IRQ_FALLING = 2,
    IRQ_RISING  = 3
} interrupt_mode_t;

/* ================================ GPIO API ================================ */

static inline int gpio_pin_mode(pin_t pin, pin_mode_t mode)
{
    if (mode == PIN_MODE_OUTPUT) {
        *pin.regs.ddr |= pin.regs.bit;
    } else {
        *pin.regs.ddr &= ~pin.regs.bit;

        if (mode == PIN_MODE_INPUT_PULLUP) {
            *pin.regs.port |= pin.regs.bit;
        } else {
            *pin.regs.port &= ~pin.regs.bit;
        }
    }
}

static inline pin_mode_t gpio_get_pin_mode(pin_t pin)
{
    if (*pin.regs.ddr & pin.regs.bit) {
        return PIN_MODE_OUTPUT;
    } else {
        if (*pin.regs.port & pin.regs.bit) {
            return PIN_MODE_INPUT_PULLUP;
        }

        return PIN_MODE_INPUT;
    }
}

static inline void gpio_digital_write(pin_t pin, uint8_t val)
{
    if (!val)
    {
        *pin.regs.port &= ~pin.regs.bit;
    } else {
        *pin.regs.port |= pin.regs.bit;
    }
}

static inline int gpio_digital_read(pin_t pin)
{
    return (*pin.regs.port & pin.regs.bit) ? 1 : 0;
}

/* TODO analog */


int gpio_attach_irq(uint8_t pin, void (*func)(void), interrupt_mode_t mode);
int gpio_detach_irq(uint8_t pin);

#endif
