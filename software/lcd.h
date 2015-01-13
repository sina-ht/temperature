/* -*- c-basic-offset: 8 -*-
 * lcd.h -- LCD driver header
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

#ifndef __LCD_H__
#define __LCD_H__

struct lcd {
	int pin_e;
	int pin_rs;
	int pin_d4;
	int pin_d5;
	int pin_d6;
	int pin_d7;
};

void lcd_on(struct lcd *l);
void lcd_off(struct lcd *l);
void lcd_cursor(struct lcd *l, int x, int y);
void lcd_clear(struct lcd *l);
void lcd_cursor_home(struct lcd *l);
void lcd_display_shift(struct lcd *l, int r);
void lcd_init(struct lcd *l, int rs, int e, int d4, int d5, int d6, int d7);
void lcd_print(struct lcd *l, char *p);

#endif
