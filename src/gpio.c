/*
 * Author: Mark Paruzel <mark@markparuzel.com>
 * Date:  2015-12-31
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

#include "gpio.h"
#include "gpio_internal.h"

#include "Arduino.h"

int gpio_pin_mode(uint8_t pin, pin_mode_t mode)
{
    pinMode(pin, mode);
    return 0;
}

int gpio_digital_write(uint8_t pin, uint8_t val)
{
    digitalWrite(pin, val);
    return 0;
}

int gpio_digital_read(uint8_t pin)
{
    return (int) digitalRead(pin);
}