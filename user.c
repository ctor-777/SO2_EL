#include <libc.h>

char buff[24];

int pid;

void thread_func(void* args) {
	struct event_t ev;
	if(semWait(args))
	{
		write(1,"Thread",6);
		write(1," in the lock\nNow he will read 1st key press envent: ", 52);
		while(!pollEvent(&ev));
		while(!pollEvent(&ev));
		char x[2];
		x[0] = ev.scandcode;
		write(1,x,1);
		semSignal(args);
		exit();
	}
	else
	{
		write(1,"Thread",6);
		write(1," got blocked and unblocked by creator\nNow he will read 2nd key press event: ", 77);
		while(!pollEvent(&ev));
		while(!pollEvent(&ev));
		char x[2];
		x[0] = ev.scandcode;
		write(1,x,1);
		semSignal(args);
		exit();
	}
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */
	write(1,"\n",1);
	struct event_t ev;
	void* sem= (void *)semCreate(1);
	int i = clone(thread_func, sem, (&i) - (10 * sizeof(unsigned long)));
	if(semWait(sem))
	{
		write(1,"Creator",7);
		write(1," in the lock\nNow he will read 1st key press envent: ", 52);
		while(!pollEvent(&ev));
		while(!pollEvent(&ev));
		char x[2];
		x[0] = ev.scandcode;
		write(1,x,1);
		write(1,"\n",1);
		semSignal(sem);
		exit();
	}
	else
	{
		write(1,"Creator",7);
		write(1," got blocked and unblocked by thread\nNow he will read 2nd key press event: ", 76);
		while(!pollEvent(&ev));
		while(!pollEvent(&ev));
		char x[2];
		x[0] = ev.scandcode;
		write(1,x,1);
		write(1,"\n",1);
		semSignal(sem);
		exit();
	}
}









