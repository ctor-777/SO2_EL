#include "include/libc.h"
#include <libc.h>

char buff[24];

int pid;

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	char* addr = getSlot(10);
	char* addr2 = getSlot(10);
	char buffer[10];
	itoa_hex((int)addr, addr);
	write(1, "\n", 1);
	write(1, addr, strlen(addr));

	itoa_hex((int)addr2, addr2);
	write(1, "\n", 1);
	write(1, addr2, strlen(addr2));
	// itoa_hex((int)addr, buffer);
	// write(1, buffer, strlen(buffer));


	*addr = 'a';
	*(addr + 1) = 'b';
	*(addr + 2) = 0;

	write(1, "\naddr value: ", 13);
	itoa(*addr, buffer);
	write(1, buffer, strlen(buffer));

	int i = delSlot(addr);
	itoa(i, buffer);
	write(1, "\ndelSlot output: ", 17);
	write(1, buffer, strlen(buffer));

	i = delSlot(addr);
	itoa(i, buffer);
	write(1, "\ndelSlot output: ", 17);
	write(1, buffer, strlen(buffer));

	*addr2 = 't';
	// *addr = 't';

	delSlot(addr2);

	*addr2 = 't';
	while(1) { 
	}
}
