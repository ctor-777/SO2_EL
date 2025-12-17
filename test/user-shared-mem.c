#include <libc.h>

char buff[24];

int global;

void thread_func(void* args) {
	write(1, "global modificado\n", 18);
	global = 2;
	exit();
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	global = 1;

	struct event_t ev;
	while(1) { 
		int x=pollEvent(&ev);
		if(x)
		{
			write(1, "valor global: ", 14);
			itoa(global, buff);
			write(1, buff, strlen(buff));
			write(1, "\n", 1);
			int i = clone(thread_func, (void *)&ev, (&i) - (10 * sizeof(unsigned long)));
		}

	}
}
