#include <libc.h>

char buff[24];

int global;

unsigned long stack[1024];

void not_optimize(unsigned int x) {
    __asm__ volatile("" : : "r"(x) : "memory");
}

void thread_func(void* args) {
	write(1, "\nin thread\n", 11);

	write(1, "start global value", 18);
	itoa(global, buff);
	write(1, buff, 1);
	write(1, "\n", 1);
	
	int i = 1;
	int pid = fork();
	if (pid != 0) {
		write(1, "fork ", 5);
		itoa(i, buff);
		write(1, buff, strlen(buff));
		write(1, " output: ", 9);
		itoa(pid, buff);
		write(1, buff, strlen(buff));
		write(1, "\n", 1);
	}
	while(pid > 0) {
		i++;
		pid = fork();
		if (pid != 0) {
			write(1, "fork ", 5);
			itoa(i, buff);
			write(1, buff, strlen(buff));
			write(1, " output: ", 9);
			if (pid < 0) {
				write(1, "error: ", 7);
				perror();
			} else {
				itoa(pid, buff);
				write(1, buff, strlen(buff));
				write(1, "\n", 1);
			}
		}
	}
	if (pid == 0) {
		global = 2;

		write(1, "fork global value", 18);
		itoa(global, buff);
		write(1, buff, 1);
		write(1, "\n", 1);

		while(1) {;}
	}
	if (pid < 0) {
		while(1) {
			write(1, "end global value", 18);
			itoa(global, buff);
			write(1, buff, 1);
			write(1, "\n", 1);
		};	
	}
	while(1) {;}
	exit();
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	global = 1;


	clone(thread_func, 0, stack);
	// thread_func(0);
	exit();

}
