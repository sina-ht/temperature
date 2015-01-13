/* -*- c-basic-offset: 8 -*-
 * uart.c -- UART driver
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
#include "uart.h"

unsigned char uart_getc(void)
{
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}

void uart_putc(unsigned char c)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}

void uart_puts(unsigned char *p)
{
	unsigned char c;

	while ((c = *p++) != '\0') {
		uart_putc(c);
		if (c == '\n')
			uart_putc('\r');
	}
}

void uart_init(void)
{
	unsigned int ubrr;

	ubrr = (F_CPU / (16UL * BAUD_RATE)) - 1;
	UBRR0H = (ubrr >> 8);
	UBRR0L = (ubrr & 0xff);
	UCSR0B = _BV(TXEN0) | _BV(RXEN0); /* Enable TX/RX */
}
