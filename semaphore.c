#include <semaphore.h>
#include <list.h>


sem_t semaphoresVector[NR_SEM];

struct list_head semFree;

void init_semFree()
{
  int i;

  INIT_LIST_HEAD(&semFree);

  /* Insert all semaphore structs in the semList */
  for (i=0; i<NR_SEM; i++)
    list_add_tail(&(semaphoresVector[i].list), &semFree);
}
