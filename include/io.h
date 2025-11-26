/*
 * io.h - Definició de l'entrada/sortida per pantalla en mode sistema
 */

#ifndef __IO_H__
#define __IO_H__

#include <types.h>

/** Screen functions **/
/**********************/

// ----------- seqences ------------
// change bg color: ESC -> 4 -> color(1-2 chars) -> m
// change fg color: ESC -> 3 -> color(1-2 chars) -> m
// change cursor: ESC -> x(1-2 chars) -> ; -> y(1-2 chars) -> H/f

typedef enum {
	NO_SEQ,
	INIT_SEQ,

	CHANGE_BG_COLOR_SEL,

	CHANGE_FG_COLOR_SEL,

	CHANGE_POS_X,
	CHANGE_POS_Y,
} seq_state;

typedef enum {
    /* Dark Colors (0x0 - 0x7) */
    VGA_COLOR_BLACK         = 0x0,
    VGA_COLOR_BLUE          = 0x1,
    VGA_COLOR_GREEN         = 0x2,
    VGA_COLOR_CYAN          = 0x3,
    VGA_COLOR_RED           = 0x4,
    VGA_COLOR_MAGENTA       = 0x5,
    VGA_COLOR_BROWN         = 0x6,
    VGA_COLOR_LIGHT_GRAY    = 0x7,

    /* Light/Bright Colors (0x8 - 0xF) */
    VGA_COLOR_DARK_GRAY     = 0x8,
    VGA_COLOR_LIGHT_BLUE    = 0x9,
    VGA_COLOR_LIGHT_GREEN   = 0xA,
    VGA_COLOR_LIGHT_CYAN    = 0xB,
    VGA_COLOR_LIGHT_RED     = 0xC,
    VGA_COLOR_LIGHT_MAGENTA = 0xD,
    VGA_COLOR_YELLOW        = 0xE,
    VGA_COLOR_WHITE         = 0xF
} vga_color;

#define is_num(x) ((x >= '0') && (x <= '9'))

Byte inb (unsigned short port);
void printc(char c);
void printc_xy(Byte x, Byte y, char c);
void printk(char *string);



// temporal
void change_bg_color(vga_color color);

void change_fg_color(vga_color color);

#endif  /* __IO_H__ */
