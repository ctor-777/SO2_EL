#include <libc.h>

char buff[24];

int pid;

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	write(1, "\n33m45mthis should be blue\n", 29);
	write(1, "35m43mthis should be magenta\n", 31);
	write(1, "3;3Hthis should be somewhere else", 35);
	  while(1) { 

	}
}
