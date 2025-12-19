#include <libc.h>

char buff[24];

int pid;

struct event_t global;

void thread_func(void* args) {
	char x[2];
	x[0] = global.scandcode;
	write(1,x,1);
	while(1){;}
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	struct event_t ev;
	while(1) { 
		int x=pollEvent(&global);
		if(x)
		{
			int i = clone(thread_func, (void *)&ev, (&i) - (10 * sizeof(unsigned long)));
			exit();
		}
	}
}
