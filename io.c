/*
 * io.c - 
 */

#include "include/io.h"
#include <io.h>

#include <types.h>

/**************/
/** Screen  ***/
/**************/

#define NUM_COLUMNS 80
#define NUM_ROWS    25

#define TAB_WIDTH 8

Byte x, y=19;

Byte fg_color = VGA_COLOR_GREEN;
Byte bg_color = VGA_COLOR_BLACK;

/* Read a byte from 'port' */
Byte inb (unsigned short port)
{
  Byte v;

  __asm__ __volatile__ ("inb %w1,%0":"=a" (v):"Nd" (port));
  return v;
}

void change_bg_color(vga_color color) {
	bg_color = color;
}

void change_fg_color(vga_color color) {
	fg_color = color;
}

void change_pos(Byte new_x, Byte new_y) {
	x = new_x;
	y = new_y;
}

int pow(int base, int exponent) {
	int result = 1;
	for (int i = 0; i < exponent; i++) {
		result *= base;
	}
	return result; 
}

void erase_display() {
	Word *screen = (Word *)0xb8000;
	for(int y_i = 0; y_i < NUM_ROWS; y_i++) {
		for(int x_i = 0; x_i < NUM_COLUMNS; x_i++) {
			screen[(y_i * NUM_COLUMNS + x_i)] = 0;
		}
	}
	x = 0;
	y = 0;
}

void printc(char c)
{
	static seq_state state = NO_SEQ;

	static int param_counter = 0;
	static int tmp_x = 0;
	static int tmp_y = 0;
	static int tmp_color = 0;


		 __asm__ __volatile__ ( "movb %0, %%al; outb $0xe9" ::"a"(c)); /* Magic BOCHS debug: writes 'c' to port 0xe9 */


	switch(state) {
		case NO_SEQ:
			if (c=='\n') {
				x = 0;
				y=(y+1)%NUM_ROWS;
			} else if (c == 0x1b) { //ESC
				state = INIT_SEQ;
			} else if (c == 0x09) { //tab
				int diff = x % TAB_WIDTH;
				x += (TAB_WIDTH - diff);
				if( x >= NUM_COLUMNS) {
					x = 0;
					y = (y+1) % NUM_ROWS;
				}

			} else if (c == 0x08) { //backspace
				if (--x <= 0)
				{
					x = NUM_COLUMNS - 1;
					if (y == 0)
						y = NUM_ROWS - 1;
					else
						--y;
				}

				Word *screen = (Word *)0xb8000;
				screen[(y * NUM_COLUMNS + x)] = 0;

			} else if (c == 0x7f) { //del
				Word *screen = (Word *)0xb8000;
				screen[(y * NUM_COLUMNS + x)] = 0;
			} else {
				Word print_color = bg_color << 4 | fg_color;
				Word ch = (Word) (c & 0x00FF) | print_color << 8;
				Word *screen = (Word *)0xb8000;
				screen[(y * NUM_COLUMNS + x)] = ch;
				if (++x >= NUM_COLUMNS)
				{
					x = 0;
					y=(y+1)%NUM_ROWS;
				}
			}
			break;

		case INIT_SEQ:
			if (c == '3')
				state = CHANGE_FG_COLOR_SEL;
			else if (c == '4')
				state = CHANGE_BG_COLOR_SEL;
			else if ((c >= '0') && (c <='9')) {
				tmp_x = c - '0';
				state = CHANGE_POS_X;
			} else if (c == 'J') { //clear screen
				erase_display();
				state = NO_SEQ;
			} else
				state = NO_SEQ;
			break;

		case CHANGE_BG_COLOR_SEL:
			if (c == 'm' && param_counter != 0) {
				change_bg_color(tmp_color);

				param_counter = 0;
				tmp_color = 0;

				state = NO_SEQ;
			} else if (is_num(c)) {
				tmp_color *= 10;
				tmp_color += c - '0';
				param_counter++;
			} else if (c == ';') {
				tmp_x = tmp_color + (4 * pow(10, param_counter));
				state = CHANGE_POS_Y;
				param_counter = 0;
			} else
				state = NO_SEQ;
			break;

		case CHANGE_FG_COLOR_SEL:
			if (c == 'm' && param_counter != 0) {
				change_fg_color(tmp_color);
				
				param_counter = 0;
				tmp_color = 0;

				state = NO_SEQ;
			} else if (is_num(c)) {
				tmp_color *= 10;
				tmp_color += c - '0';
				param_counter++;
			} else if (c == ';') {
				tmp_x = tmp_color + (3 * pow(10, param_counter));
				param_counter = 0;
				tmp_color = 0;

				state = CHANGE_POS_Y;
			} else
				state = NO_SEQ;
			break;

		case CHANGE_POS_X:
			if (c == ';' && param_counter != 0) {
				state = CHANGE_POS_Y;
				param_counter = 0;
			} else if (is_num(c)) {
				tmp_x *= 10;
				tmp_x += c - '0';
				param_counter++;
			} else 
				state = NO_SEQ;
			
			break;
		case CHANGE_POS_Y:
			if (c == 'H' && param_counter != 0) {
				change_pos(tmp_x, tmp_y);

				tmp_x = 0;
				tmp_y = 0;
				param_counter = 0;

				state = NO_SEQ;
			} else if (is_num(c)) {
				tmp_y *= 10;
				tmp_y += c - '0';
				param_counter++;
			} else 
				state = NO_SEQ;
			break;
		default:
			state = NO_SEQ;
			break;
	}
}

void printc_xy(Byte mx, Byte my, char c)
{
  Byte cx, cy;
  cx=x;
  cy=y;
  x=mx;
  y=my;
  printc(c);
  x=cx;
  y=cy;
}

void printk(char *string)
{
  int i;
  for (i = 0; string[i]; i++)
    printc(string[i]);
}
