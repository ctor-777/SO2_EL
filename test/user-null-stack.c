#include <libc.h>

char buff[24];

int pid;

unsigned long stack[100];

void thread_func(void* args) {
	char x[2];
	x[0] = ((struct event_t *)args)->scandcode;
	write(1,x,1);
	exit();
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	struct event_t ev;
	while(1) { 
		int x=pollEvent(&ev);
		if(x)
		{
			int i = clone(thread_func, (void *)&ev, 0);
			if (i < 0) {
				write(1, "\nclone failed: ", 15);
				perror();
			}
		}
	}
}
