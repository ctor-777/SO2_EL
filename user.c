#include <libc.h>

char buff[24];

void thread_func(sem_t* args) {

	//Test 7, 10
	write(1,"Unblocking the creator thread from the new thread, actual value -1\n", 67);
	if(semSignal(args)<0) write(1, "Test failed\n", 12);
	
	//Test 5, 6
	write(1,"Using semWait on new thread to get blocked, actual value 0\n", 59);
	if(semWait(args)) write(1, "Test failed\n", 12);
	else
	{
		//Test 8
		write(1,"Thread got unblocked by creator\n", 32);
	
	}
	


	//Test 11
	write(1, "\n\n\n\n\n\n\n\n\n\n\nTEST 11\n", 19);
	write(1,"Thread using semDestroy to try to destroy the semaphore that he did not create\n", 79);
	if(!semDestroy(args)) write(1,"Can't destroy a semaphore that you did not create\n", 50);
	else write(1, "Test failed\n", 12);
	
	//Test 16
	write(1, "\n\n\n\n\n\n\n\n\n\n\nTEST 16\n", 19);
	write(1,"Thread using semWait to get blocked and destroying the semaphore from the thread creator to check if the child thread woke up and return errno error code corresponding to ESEMDESTROYED\n", 185);
	semSignal(args);
	semWait(args);
	if(errno == 130) write(1,"Thread returned correct error code\n", 35);
	else write(1, "Test failed\n", 12);
	
	//END of TESTS
	write(1, "\n\n\n\n\n\n\n\n\n\n\nEND OF TESTS\n", 24);

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

	//Test 13
	write(1, "\n\n\n\n\n\n\n\n\n\n\nTEST 13\n", 19);
	write(1,"Thread using semDestroy to try to destroy a semaphore that's already free\n", 74);
	if(semDestroy(semAux)<0) write(1,"Can't destroy a semaphore that's already free\n", 46);
	else write(1, "Test failed\n", 12);
	
	
	//Test 14
	write(1, "\n\n\n\n\n\n\n\n\n\n\nTEST 14\n", 19);
	write(1,"Thread using semWait on unactive semaphore\n", 43);
	if(semWait(semAux)<0) write(1,"Can't use semWait on unactive semaphore\n", 40);
	else write(1, "Test failed\n", 12);
	
	//Test 15
	write(1, "\n\n\n\n\n\n\n\n\n\n\nTEST 15\n", 19);
	write(1,"Thread using semSignal on unactive semaphore\n", 45);
	if(semWait(semAux)<0) write(1,"Can't use semSignal on unactive semaphore\n", 42);
	else write(1, "Test failed\n", 12);
	
	
	
	
	
	
	
	
	

	//Test 3, 4
	write(1, "\n\n\n\n\n\n\n\n\n\n\nTEST 3, 4, 5, 6, 7, 8, 10\n", 37);
	write(1,"Using semWait, actual value 1\n", 30);
	if(semWait(sem)) 
	{
		write(1,"We did not get blocked\n", 23);
		int i = clone(thread_func, sem, (&i) - (10 * sizeof(unsigned long)));
		write(1,"Using semWait again to block the actual thread, actual value 0\n", 63);
		if(!semWait(sem)) 
		{
			//Test 7, 8
			write(1,"Unblocked by the new thread\nUnblocking the new thread, current value -1\n", 73);
			semSignal(sem);
		}
		else write(1, "Test failed\n", 12);
		
	}
	else write(1,"Test failed\n", 12);
	
	//Test 9
	write(1, "\n\n\n\n\n\n\n\n\n\n\nTEST 9\n", 18);
	write(1,"Using semSignal when the current value is 0\n", 44);
	if(semSignal(sem)<0) write(1, "Test failed\n", 12);
	
	//Test 16
	semWait(sem);
	semWait(sem);
	semDestroy(sem);
	
	while(1);
	exit();
}






