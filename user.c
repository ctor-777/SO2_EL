#include <libc.h>

char buff[24];

int global;

char stack[1024];

void not_optimize() {
	write(1, "\nin no opt", 10);
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
		yield();
		write(1, "end global value", 18);
		itoa(global, buff);
		write(1, buff, 1);
		write(1, "\n", 1);
		while(1) {;}	
	}
	while(1) {;}
	exit();
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */
	write(1,"\n",1);
	
	struct event_t ev;
	
	//Test 1.1
	write(1, "\n\n\n\n\n\n\n\n\n\n\nTEST 1.1\n", 20);
	write(1,"Creating semaphore with value 0\n", 32);
	semCreate(0);
	
	//Test 1.2
	write(1, "\n\n\n\n\n\n\n\n\n\n\nTEST 1.2\n", 20);
	write(1,"Creating semaphore with value 1\n", 32);
	sem_t* sem = semCreate(1);
	
	//Test 1.3
	write(1, "\n\n\n\n\n\n\n\n\n\n\nTEST 1.3\n", 20);
	write(1,"In order to test it, we should uncomment 'sem->value++' and see how we get a page fault\n", 88);
	//sem->value++;
	
	
	sem_t* semAux;
	//Test 2
	write(1, "\n\n\n\n\n\n\n\n\n\n\nTEST 2\n", 18);
	write(1,"Creating semaphore when there are no free left\n", 47);
	int x = 2;
	while(x<8 && (semAux=semCreate(1))) x++;
	if(semCreate(1)<0) write(1,"Can't create, there are no free semaphores left\n", 48);
	else write(1,"Test failed\n", 12);
	
	
	
	
	
	
	
	
	
	
	//Test 12
	write(1, "\n\n\n\n\n\n\n\n\n\n\nTEST 12\n", 19);
	write(1,"Thread using semDestroy to try to destroy the semaphore that he created\n", 72);
	if(semDestroy(semAux)) write(1,"Semaphore destroyed\n", 20);
	else write(1, "Test failed\n", 12);

	global = 1;


	clone(thread_func, 0, stack);
	// thread_func(0);
	exit();

}






