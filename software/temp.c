/* -*- c-basic-offset: 8 -*-
 * temp.c -- Temperature Meter
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

#include <stdio.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
//#include "uart.h"
#include "lcd.h"
#include "pin.h"

int main(int argc, char **argv)
{
	char buf[32];
	struct lcd lcd;

	//uart_init();
	//strcpy_P(buf, PSTR("Temperature\n"));
	//uart_puts((unsigned char *)buf);

	strcpy_P(buf, PSTR("Temperature"));
	lcd_init(&lcd, 7, 8, 9, 10, 11, 12);
	lcd_print(&lcd, buf);

	/* ADC */
	ADMUX = _BV(REFS0) | 0b0101; /* AVcc, Channel 5 */
	ADCSRA = _BV(ADEN); /* Enable ADC */

	for (;;) {
		unsigned char h, l;
		int r, t, d;

		ADCSRA = _BV(ADEN) | _BV(ADSC) | 4; /* Start conversion, clk/16 */
		loop_until_bit_is_clear(ADCSRA, ADSC);
		l = ADCL;
		h = ADCH;
		r = (h << 8) | l;
		// normal
		//t = (5 * r * 100L) / 1024L;
		// x5 OPAMP x10 for precision
		t = (r * 1000L) / 1024L;
		d = t % 10;
		t /= 10;
		//sprintf_P(buf, PSTR("%d -> %d.%d\n"), r, t, d);
		//uart_puts((unsigned char *)buf);
		sprintf_P(buf, PSTR("%2d.%1d"), t, d);
		lcd_cursor(&lcd, 0, 1);
		lcd_print(&lcd, buf);
		_delay_ms(1000);
	}

	return 0;
}
