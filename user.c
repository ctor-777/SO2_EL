#include "include/libc.h"
#include <libc.h>

char buff[24];

int global;

char stack[1024];

struct position {
	int x;
	int y;
};

enum orientation {
	RIGHT,
	LEFT,
	UP,
	DOWN,
};

struct s_player {
	struct position pos;
	enum orientation ori;
	int health;
};

struct s_player player;

struct s_player enemies[3];

char map[23][80];

void change_pos(int x, int y) {
	if( x > 80 || x < 0 || y < 0 || y > 25)
		return;
	char buff[5];
	write(1, "\e", 1);
	itoa(x, buff);
	write(1, buff, strlen(buff));
	write(1, ";", 1);
	itoa(y, buff);
	write(1, buff, strlen(buff));
	write(1, "H", 1);
}

void create_map() {
	write(1, "\x1bJ", 2);

	write(1, "\e46m", 4);
	change_pos(0, 5);
	for(int y = 5; y < 25; y++) {
		for(int x = 0; x < 80; x++) {
			write(1, " ", 1);
			map[y][x] = 'g';
		}
	}
}

void print_player(struct s_player* player) {
	change_pos(player->pos.x, player->pos.y);

	write(1, "\e32m\e40m", 8);
	switch (player->ori) {
		case RIGHT:
			write(1, "}", 1);
			break;
		case LEFT:
			write(1, "{", 1);
			break;
		case UP:
			write(1, "^", 1);
			break;
		case DOWN:
			write(1, "v", 1);
			break;
	}

}

void clear_player(struct s_player* player) {
	change_pos(player->pos.x, player->pos.y);
	write(1, "\x7f", 1);
}

void clear_map() {
	for(int x = 0; x < 80; x++) {
		for(int y = 0; y < 25; y++) {
			map[y][x] = ' ';
		}
	}
}

void keyboard_thread(void* param) {
	struct event_t ev;
	int x;
	while(1) {
		x = pollEvent(&ev);
		while(!x) {
			x = pollEvent(&ev);
		}
		if (ev.pressed) {
			// clear_player(&player);
			switch (ev.scandcode) {
				case 'w':
					player.pos.y--;
					if (player.pos.y < 2)
						player.pos.y = 2;
					player.ori = UP;
					break;
				case 'd':
					player.pos.x++;
					if (player.pos.x > 80)
						player.pos.x = 80;

					player.ori = RIGHT;
					break;
				case 's':
					player.pos.y++;
					if (player.pos.y > 25)
						player.pos.y = 25;
					player.ori = DOWN;
					break;
				case 'a':
					player.pos.x--;
					if (player.pos.x < 0)
						player.pos.x = 0;
					player.ori = LEFT;
					break;
				default:
					break;
			}
			print_player(&player);
		}
	}
		
	yield();
}

void placement_thread(void* param) {
}

void score_thread(void* param) {
}



int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	player.pos.x = 40;
	player.pos.y = 4;
	player.ori = DOWN;
	clear_map();
	create_map();
	print_player(&player);
	keyboard_thread(0);
	while(1) {;}

}






