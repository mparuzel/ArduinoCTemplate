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
	PIN_MODE_INPUT = 0,
	PIN_MODE_OUTPUT = 1,
	PIN_MODE_INPUT_PULLUP = 2
} pin_mode_t;

/* ================================ GPIO API ================================ */

int gpio_pin_mode(uint8_t pin, pin_mode_t mode);
int gpio_get_pin_mode(uint8_t pin);

int gpio_digital_write(uint8_t pin, uint8_t val);
int gpio_digital_read(uint8_t pin);

int gpio_analog_write(uint8_t pin, uint16_t val);
int gpio_analog_read(uint8_t pin);

#endif
