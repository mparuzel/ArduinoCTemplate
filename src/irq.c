/*
 * Author: Mark Paruzel <mark@markparuzel.com>
 * Date:  2016-02-28
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

#include "irq.h"

#include <avr/io.h>
#include <avr/interrupt.h>

/* =========================== EXTERNAL INTERRUPT =========================== */

int irq_external_enable(uint8_t int_num, irq_mode_t mode)
{
    typedef struct {
        uint8_t bit;
        uint8_t shift;
    } regs_t;

    const regs_t REGS[] = { [0] = { .bit = _BV(INT0), .shift = ISC00 },
                            [1] = { .bit = _BV(INT1), .shift = ISC10 } };

    /* Check inputs. */
    if (int_num > sizeof(REGS) / sizeof(REGS[0])) {
        return -1;
    }

    /* Overwrite the control register. */
    EICRA &= 0x03 << REGS[int_num].shift;
    EICRA |= mode << REGS[int_num].shift;

    /* Enable interrupt. */
    EIMSK |= REGS[int_num].bit;
    sei();

    return 0;
}

int irq_external_disable(uint8_t int_num)
{
#if 0
    const regs_t REGS[] = { [0] = _BV(INT0),
                            [1] = _BV(INT1) };

    /* Check inputs. */
    if (int_num > sizeof(REGS) / sizeof(REGS[0])) {
        return -1;
    }

    /* Disable interrupt. */
    EIMSK &= ~_BV(int_num);
#endif
    return 0;
}

/* ========================== PIN CHANGE INTERRUPT ========================== */

int irq_pin_change_enable(uint8_t int_num)
{

}

int irq_pin_change_disable(uint8_t int_num)
{

}
