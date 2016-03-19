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

#ifndef SPI_H
#define SPI_H

#include "board.h"

#include <stdint.h>
#include <stddef.h>

/* =============================== STRUCTURES =============================== */

typedef enum {
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3
} spi_mode_t;

typedef enum {
    SPI_MASTER,
    SPI_SLAVE
} spi_control_t;

typedef enum {
    SPI_MSB,
    SPI_LSB
} spi_sbit_t;

/* ==================== SERIAL PERIPHERAL INTERFACE API ===================== */

#include "digital.h"

int spi_init(uint32_t clock, spi_mode_t mode, spi_control_t ctl, spi_sbit_t sb);
int spi_begin(pin_t ss_pin);
void spi_end(void);

static inline void spi_select(pin_t ss_pin)
{
    /* Notify slave of incoming data. */
    digital_write(ss_pin, 0);
}

static inline void spi_deselect(pin_t ss_pin)
{
    /* Release the slave to signal the end of data transfer. */
    digital_write(ss_pin, 1);
}
int spi_exchange(uint8_t in);

#endif
