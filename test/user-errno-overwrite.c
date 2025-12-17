#include <libc.h>

char buff[24];

int pid;

void thread_func(void* args) {
	write(1, "setting errno to EFAULT(14) in thread\n", 39);
	write(1, 0, 5);
	write(1, "errno at thread: ", 17);
	perror();
	write(1, "\n", 1);
	exit();
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	write(1, "setting errno to EBADF(9)\n", 26);
	write(2, "irrelevant", 5);
	write(1, "errno at start: \n", 17);
	perror();

	struct event_t ev;
	while(1) { 
		int x=pollEvent(&ev);
		if(x)
		{
			int i = clone(thread_func, (void *)&ev, (&i) - (10 * sizeof(unsigned long)));

			write(1, "reading errno again: ", 22);
			perror();
			write(1, "\n", 1);
		}

	}
}
