/*
 * interrupt.h - Definició de les diferents rutines de tractament d'exepcions
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <types.h>

/*
 * We add the header libc.h to have access to the struct event_t in order to create the circular buffer that will store them.
*/
#include <libc.h>

#define IDT_ENTRIES 256
#define SIZE_CIRCULAR_BUFFER 4

extern Gate idt[IDT_ENTRIES];
extern Register idtR;

/*
 * We've made it global so we can have access to this variables and circular buffer from the syscall in sys.c
*/

extern int add_index;
extern int read_index;
extern int overr;

extern struct event_t keyboard_events[SIZE_CIRCULAR_BUFFER];

void setInterruptHandler(int vector, void (*handler)(), int maxAccessibleFromPL);
void setTrapHandler(int vector, void (*handler)(), int maxAccessibleFromPL);

void setIdt();

#endif  /* __INTERRUPT_H__ */
