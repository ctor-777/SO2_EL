/*
 * libc.h - macros per fer els traps amb diferents arguments
 *          definició de les crides a sistema
 */
 
#ifndef __LIBC_H__
#define __LIBC_H__

#include <stats.h>

extern int errno;

/*
 * We declare the struct event_t in libc.h because it's a user-mode header where we can access it from the user code and also from the system code.
 * If it was declared in a system-privileged header, we could not have access to the struct, including the event information we'd store.
*/

struct event_t {
    int pressed;
    char scandcode;
};

int write(int fd, char *buffer, int size);

void itoa(int a, char *b);
void itoa_hex(int a, char* b);

int strlen(char *a);

void perror();

int getpid();

int fork();

void exit();

int yield();

int get_stats(int pid, struct stats *st);

/*
 * We declare the wrapper header for the syscall
*/

int pollEvent(struct event_t *ev);

char* getSlot(int num_bytes);

int delSlot(char* s);

#endif  /* __LIBC_H__ */
