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

#ifndef ANALOG_H
#define ANALOG_H

#include "board.h"

/* =============================== ANALOG API =============================== */


int analog_init(void);
int analog_stop_pwm(uint8_t timer);


static inline int analog_read(pin_t pin)
{
    // http://www.arduinoos.com/2011/09/pwm-part-2/
    // https://github.com/H2CO3/libavrutil/blob/master/src/analog.h
    return 0;
}

static inline void analog_write(pin_t pin, int val)
{


    return 0;
}


#endif
