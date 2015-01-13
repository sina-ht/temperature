/* -*- c-basic-offset: 8 -*-
 * pin.c -- Pin control
 * Copyright (C) 2014 Hiroshi Takekawa
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * ATTENTION: GPL version 2 only. You cannot apply any later version.
 * This situation may change in the future.
 */

#include <avr/io.h>
#include "pin.h"

void set_direction(int pin, int d)
{
	if (pin >= 0 && pin < 8) {
		if (d)
			DDRD |= (1 << pin);
		else
			DDRD &= ~(1 << pin);
	} else if (pin >= 8 && pin <= 13) {
		pin -= 8;
		if (d)
			DDRB |= (1 << pin);
		else
			DDRB &= ~(1 << pin);
	}
}

void set_port(int pin, int d)
{
	if (pin >= 0 && pin < 8) {
		if (d)
			PORTD |= (1 << pin);
		else
			PORTD &= ~(1 << pin);
	} else if (pin >= 8 && pin <= 13) {
		pin -= 8;
		if (d)
			PORTB |= (1 << pin);
		else
			PORTB &= ~(1 << pin);
	}
		
}
