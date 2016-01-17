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

typedef enum {
    SPI_PIN_MISO,
    SPI_PIN_MOSI,
    SPI_PIN_SCK,
    SPI_PIN_SS
} spi_pin_usage_t;

/* ==================== SERIAL PERIPHERAL INTERFACE API ===================== */

int spi_init(uint32_t clock, spi_mode_t mode, spi_control_t ctl, spi_sbit_t sb);
int spi_init_pin(uint8_t pin, spi_pin_usage_t usage);
int spi_begin(void);
int spi_end(void);
int spi_select(uint8_t ss_pin);
int spi_deselect(uint8_t ss_pin);
int spi_exchange(uint8_t in);

#endif
