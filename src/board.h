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
 *           PC6   1|    |28  PC5 (ADC5)
 *      (D0) PD0   2|    |27  PC4 (ADC4)
 *      (D1) PD1   3|    |26  PC3 (ADC3)
 *      (D2) PD2   4|    |25  PC2 (ADC2)
 * PWM+ (D3) PD3   5|    |24  PC1 (ADC1)
 *      (D4) PD4   6|    |23  PC0 (ADC0)
 *           VCC   7|    |22  GND
 *           GND   8|    |21  AREF
 *           PB6   9|    |20  AVCC
 *           PB7  10|    |19  PB5 (D13)
 * PWM+ (D5) PD5  11|    |18  PB4 (D12)
 * PWM+ (D6) PD6  12|    |17  PB3 (D11) PWM
 *      (D7) PD7  13|    |16  PB2 (D10) PWM
 *      (D8) PB0  14|    |15  PB1 (D9)  PWM
 *                  +----+
 *
 * (PWM+ indicates the additional PWM pins on the ATmega168.)
 */

/* Port B Pins. */
static const pin_t PIN_B0 = MAKE_PIN(B, 0); /* D8,   PCINT0,  CLKO,  ICP1     */
static const pin_t PIN_B1 = MAKE_PIN(B, 1); /* D9,   PCINT1,  OC1A            */
static const pin_t PIN_B2 = MAKE_PIN(B, 2); /* D10,  PCINT2,  OC1B,  SS       */
static const pin_t PIN_B3 = MAKE_PIN(B, 3); /* D11,  PCINT3,  OC2A,  MOSI     */
static const pin_t PIN_B4 = MAKE_PIN(B, 4); /* D12,  PCINT4,         MISO     */
static const pin_t PIN_B5 = MAKE_PIN(B, 5); /* D13,  PCINT5,         SCK      */
static const pin_t PIN_B6 = MAKE_PIN(B, 6); /*       PCINT6,  XTAL1, TOSC1    */
static const pin_t PIN_B7 = MAKE_PIN(B, 7); /*       PCINT7,  XTAL2, TOSC2    */

/* Port C Pins. */
static const pin_t PIN_C0 = MAKE_PIN(C, 0); /* ADC0, PCINT8,                  */
static const pin_t PIN_C1 = MAKE_PIN(C, 1); /* ADC1, PCINT9,                  */
static const pin_t PIN_C2 = MAKE_PIN(C, 2); /* ADC2, PCINT10,                 */
static const pin_t PIN_C3 = MAKE_PIN(C, 3); /* ADC3, PCINT11,                 */
static const pin_t PIN_C4 = MAKE_PIN(C, 4); /* ADC4, PCINT12, SDA             */
static const pin_t PIN_C5 = MAKE_PIN(C, 5); /* ADC5, PCINT13, SCL             */
static const pin_t PIN_C6 = MAKE_PIN(C, 6); /*       PCINT14, RESET           */

/* Port D Pins. */
static const pin_t PIN_D0 = MAKE_PIN(D, 0); /* D0,   PCINT16, RXD             */
static const pin_t PIN_D1 = MAKE_PIN(D, 1); /* D1,   PCINT17, TXD             */
static const pin_t PIN_D2 = MAKE_PIN(D, 2); /* D2,   PCINT18,        INT0     */
static const pin_t PIN_D3 = MAKE_PIN(D, 3); /* D3,   PCINT19, OC2B,  INT1     */
static const pin_t PIN_D4 = MAKE_PIN(D, 4); /* D4,   PCINT20, XCK,   T0       */
static const pin_t PIN_D5 = MAKE_PIN(D, 5); /* D5,   PCINT21, OC0B,  T1       */
static const pin_t PIN_D6 = MAKE_PIN(D, 6); /* D6,   PCINT22, OC0A,  AIN0     */
static const pin_t PIN_D7 = MAKE_PIN(D, 7); /* D7,   PCINT32,        AIN1     */

#else
#   error "Unsupported board; Please add pin constants."
#endif

#endif
