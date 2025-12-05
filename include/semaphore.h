/*
 * sched.h - Estructures i macros pel tractament de processos
 */

#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <list.h>

#define NR_SEM 256

typedef struct semaphore {
    int value;
    struct list_head blocked_threads;
    struct list_head list;
    int active;
} sem_t;

extern sem_t semaphoresVector[NR_SEM];

extern struct list_head semFree;

void init_semFree();


#endif  /* __SEMAPHORE_H__ */
