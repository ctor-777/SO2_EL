#include <libc.h>

char buff[24];

int pid;

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

  while(1) { 
  	
  	struct event_t ev;
  	int x = pollEvent(&ev);
    if(x==1) 
    {
    		char x[1];
    		x[0] = ev.scandcode;
    		write(1,"\n",1);
    		write(1,x,1);
    		write(1," ",1);
    		if(ev.pressed)
    			write(1,"PRESSED",8);
    		else
    			write(1,"RELEASED",9);
  	}
  	else if (x==-1)
  		write(1,"Acceso invalido\n",16);
  		

  
  }
}
