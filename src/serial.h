/*
 * Author: Mark Paruzel <mark@markparuzel.com>
 * Date:  2015-12-13
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

#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/* Initializes USART.
 */
int serial_init(uint16_t baud);

/* Deinitializes serial operations.
 */
int serial_deinit(void);

/* Peeks into the input buffer and returns the number of bytes available.
 */
int serial_peek(void);

/* Reads a number of bytes from the input buffer.
 */
int serial_read(void *buf, size_t sz);

/* Writes a number of bytes to the output buffer. This is a blocking operation
 * while the output buffer is read by a client.
 */
int serial_write(const void *buf, size_t sz);

/* Associates the read/write serial operations with stdin/stdout/stderr. Be
 * warned, by using stdio functions, the file executable's file size will
 * increase by up to 2Kb.
 */
int serial_set_fdev(void);

#endif
