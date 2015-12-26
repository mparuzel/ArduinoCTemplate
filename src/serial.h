/*
 * Author: Mark Paruzel <mark@markparuzel.com>
 * Date:  2015-12-13
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

#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stddef.h>

/* Initializes UART. 
 */
int serial_init(uint16_t baud);
int serial_deinit(void);
int serial_peek(void);
int serial_read(const void *buf, size_t sz);
int serial_write(const void *buf, size_t sz);

#endif