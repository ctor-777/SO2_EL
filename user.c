#include <libc.h>

char buff[24];

int pid;

void thread_func(void* param) {
	write(1, "in thread\n", 10);
	while(1){}
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */


	int i = clone(&thread_func, 0, (&i) - (10 * sizeof(unsigned long)));

	write(1, "returned from clone\n", 20);
	while(1) { }
}
