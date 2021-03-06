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

#ifndef SPI_INTERNAL_H
#define SPI_INTERNAL_H

#include <avr/io.h>
#include <avr/interrupt.h>

#if defined(SPCR)
#   define SPI_REGS_INIT { &SPCR, &SPDR, &SPSR }
#elif defined(SPCR0)
#   define SPI_REGS_INIT { &SPCR0, &SPDR0, &SPSR0 }
#endif

#if !defined(SPE) && defined(SPE0)
#	define SPR0 	SPR00
#	define SPR1		SPR10
#	define CPHA		CPHA0
#	define CPOL		CPOL0
#	define MSTR		MSTR0
#	define DORD		DORD0
#	define SPE		SPE0
#	define SPIE		SPIE0
#endif

#endif
