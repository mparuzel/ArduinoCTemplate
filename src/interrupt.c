/*
 * Author: Mark Paruzel <mark@markparuzel.com>
 * Date:  2016-02-13
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

#include "interrupt.h"


#include <avr/io.h>

#include <avr/interrupt.h>
#include <stdio.h>
int aaaa = 0;

//void isr_timer0(void)

//void isr_timer0(void)  __attribute__ ((weak));

void __attribute__((weak)) isr_timer0(void)  ;
inline ISR(TIMER1_OVF_vect) { isr_timer0(); }
