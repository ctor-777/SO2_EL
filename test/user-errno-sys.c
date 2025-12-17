#include <libc.h>

char buff[24];

int pid;

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

	write(1,"\n", 1);
	if (write(2, "test", 5)) {
		perror();
	}
	write(1,"\n", 1);
	if (write(1, 0, 5)) {
		perror();
	}


	while(1) { 

	}
}
