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

#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stddef.h>

#include <avr/io.h>

/* ================================= MACROS ================================= */

#define MAKE_PIN(p, b) { .regs = { &DDR##p, &PIN##p, &PORT##p, _BV(b) } };

/* =============================== STRUCTURES =============================== */

typedef union {
    struct {
        volatile uint8_t *ddr;
        volatile uint8_t *pin;
        volatile uint8_t *port;
        uint8_t bit;
    } regs;
    uint32_t raw;
} pin_t;

/* =============================== PIN LAYOUT =============================== */

#if defined(__AVR_ATmega168__) ||  \
    defined(__AVR_ATmega168P__) || \
    defined(__AVR_ATmega328P__)

/* ATmega168/168P/328P Pin Setup:
 *
 *                  +-\/-+
 *            PC6  1|    |28  PC5 (AI 5)
 *      (D 0) PD0  2|    |27  PC4 (AI 4)
 *      (D 1) PD1  3|    |26  PC3 (AI 3)
 *      (D 2) PD2  4|    |25  PC2 (AI 2)
 * PWM+ (D 3) PD3  5|    |24  PC1 (AI 1)
 *      (D 4) PD4  6|    |23  PC0 (AI 0)
 *            VCC  7|    |22  GND
 *            GND  8|    |21  AREF
 *            PB6  9|    |20  AVCC
 *            PB7 10|    |19  PB5 (D 13)
 * PWM+ (D 5) PD5 11|    |18  PB4 (D 12)
 * PWM+ (D 6) PD6 12|    |17  PB3 (D 11) PWM
 *      (D 7) PD7 13|    |16  PB2 (D 10) PWM
 *      (D 8) PB0 14|    |15  PB1 (D 9) PWM
 *                  +----+
 *
 * (PWM+ indicates the additional PWM pins on the ATmega168.)
 */

/* Digital pins. */
static const pin_t PIN_0  = MAKE_PIN(D, 0);
static const pin_t PIN_1  = MAKE_PIN(D, 1);
static const pin_t PIN_2  = MAKE_PIN(D, 2);
static const pin_t PIN_3  = MAKE_PIN(D, 3);
static const pin_t PIN_4  = MAKE_PIN(D, 4);
static const pin_t PIN_5  = MAKE_PIN(D, 5);
static const pin_t PIN_6  = MAKE_PIN(D, 6);
static const pin_t PIN_7  = MAKE_PIN(D, 7);
static const pin_t PIN_8  = MAKE_PIN(B, 0);
static const pin_t PIN_9  = MAKE_PIN(B, 1);
static const pin_t PIN_10 = MAKE_PIN(B, 2);
static const pin_t PIN_11 = MAKE_PIN(B, 3);
static const pin_t PIN_12 = MAKE_PIN(B, 4);
static const pin_t PIN_13 = MAKE_PIN(B, 5);

/* Analog pins. */
static const pin_t PIN_14 = MAKE_PIN(C, 0);
static const pin_t PIN_15 = MAKE_PIN(C, 1);
static const pin_t PIN_16 = MAKE_PIN(C, 2);
static const pin_t PIN_17 = MAKE_PIN(C, 3);
static const pin_t PIN_18 = MAKE_PIN(C, 4);
static const pin_t PIN_19 = MAKE_PIN(C, 5);

#else
#   error "Unsupported board; Please add pin constants."
#endif

#endif
