#include <libc.h>

char buff[24];

int pid;

struct event_t global;

void thread_func(void* args) {
	write(1, "\nexiting thread 2\n", 17);
	exit();
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
			write(1, "\nexiting thread 1\n", 17);
			exit();
		}
	}
}
