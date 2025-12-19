/*
 * sched.h - Estructures i macros pel tractament de processos
 */

#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <list.h>

typedef struct semaphore {
    int value;
    struct list_head blocked_threads;
    struct list_head list;
    int active;
} sem_t;


#endif  /* __SEMAPHORE_H__ */
