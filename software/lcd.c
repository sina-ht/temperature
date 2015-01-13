/* -*- c-basic-offset: 8 -*-
 * lcd.c -- LCD driver
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
#include <string.h>
#include <util/delay.h>
#include "lcd.h"
#include "pin.h"

#define LCD_CMD_RAW_WAIT 1
#define LCD_CMD_NORMAL_WAIT 40
#define LCD_CMD_LONG_WAIT 1640

static void lcd_cmd_raw(struct lcd *l, unsigned char val, int rs)
{
	set_port(l->pin_d4,  val & 1);
	set_port(l->pin_d5, (val >> 1) & 1);
	set_port(l->pin_d6, (val >> 2) & 1);
	set_port(l->pin_d7, (val >> 3) & 1);
	set_port(l->pin_rs, rs);
	set_port(l->pin_e, 1);
	_delay_us(LCD_CMD_RAW_WAIT);
	set_port(l->pin_e, 0);
}

static void lcd_cmd(struct lcd *l, unsigned char cmd)
{
	lcd_cmd_raw(l, (cmd >> 4) & 0xf, 0);
	lcd_cmd_raw(l,  cmd       & 0xf, 0);
}

void lcd_on(struct lcd *l)
{
        lcd_cmd(l, 0xe); /* Display On, Cursor On */
        _delay_us(LCD_CMD_NORMAL_WAIT);
}

void lcd_off(struct lcd *l)
{
        lcd_cmd(l, 0x8); /* Display Off, Cursor Off */
        _delay_us(LCD_CMD_NORMAL_WAIT);
}

void lcd_cursor(struct lcd *l, int x, int y)
{
	if (x >= 0 && x < 32 && y >= 0 && y < 2) {
		unsigned char addr = 0x40 * y + x;

		lcd_cmd(l, addr | 0x80); /* Set DDRAM address */
		_delay_us(LCD_CMD_NORMAL_WAIT);
	}
}

void lcd_clear(struct lcd *l)
{
        lcd_cmd(l, 0x1);
	_delay_us(LCD_CMD_LONG_WAIT);
}

void lcd_cursor_home(struct lcd *l)
{
        lcd_cmd(l, 0x2);
	_delay_us(LCD_CMD_LONG_WAIT);
}

void lcd_display_shift(struct lcd *l, int r)
{
	if (r <= 16 && r >= -16) {
		int i, j, d;
		j = (r > 0) ? r : -r;
		d = (r > 0) ? 0 : 1;

		for (i = 0; i < j; i++) {
			lcd_cmd(l, 0x18 | (d << 2));
			_delay_us(LCD_CMD_NORMAL_WAIT);
		}
	}
}

void lcd_init(struct lcd *l, int rs, int e, int d4, int d5, int d6, int d7)
{
	set_direction(rs, 1);
	set_direction(e, 1);
	set_direction(d4, 1);
	set_direction(d5, 1);
	set_direction(d6, 1);
	set_direction(d7, 1);
	set_port(rs, 0);
	set_port(e, 0);

	l->pin_rs = rs;
	l->pin_e = e;
	l->pin_d4 = d4;
	l->pin_d5 = d5;
	l->pin_d6 = d6;
	l->pin_d7 = d7;

	// wait more than 15 ms
        _delay_ms(15);
        lcd_cmd_raw(l, 0x3, 0);

	// wait more than 4.1 ms
        _delay_ms(5);
        lcd_cmd_raw(l, 0x3, 0);

	// wait more than 100 usec
        _delay_us(100);
        lcd_cmd_raw(l, 0x3, 0);

	// function set
        lcd_cmd_raw(l, 0x2, 0);
        lcd_cmd(l, 0x28); /* Data length = 4bit, 2line display, 5x7 font */

        lcd_off(l);
        lcd_clear(l);
        lcd_on(l);

	// entry mode set
        lcd_cmd(l, 0x6); /* Increament cursor, without shift */
}

void lcd_print(struct lcd *l, char *p)
{
        int i;

        for (i = 0; i < strlen(p); i++) {
		lcd_cmd_raw(l, (p[i] >> 4) & 0xf, 1);
		lcd_cmd_raw(l,  p[i]       & 0xf, 1);
		_delay_us(LCD_CMD_NORMAL_WAIT);
        }
} 
