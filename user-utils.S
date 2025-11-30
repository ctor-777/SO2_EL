#include <asm.h>

ENTRY(syscall_sysenter)
	push %ecx
	push %edx
	push $SYSENTER_RETURN
	push %ebp
	mov %esp, %ebp
	sysenter
ENTRY(SYSENTER_RETURN)
	pop %ebp
	pop %edx
	pop %edx
	pop %ecx
	ret

/* int write(int fd, char *buffer, int size) */
ENTRY(write)
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx;  // Save EBX, ESI and EDI if modified
	movl $4, %eax
	movl 0x8(%ebp), %ebx;	//fd
	movl 0xC(%ebp), %ecx;	//buffer
	movl 0x10(%ebp), %edx;	//size
	call syscall_sysenter
	popl %ebx
	test %eax, %eax
	js nok	// if (eax < 0) -> 
	popl %ebp
	ret

/* Common code for negative return */
nok:
	neg %eax
	mov %eax, errno
	mov $-1, %eax
	popl %ebp
	ret

/* int gettime() */
ENTRY(gettime)
	pushl %ebp
	movl %esp, %ebp
	movl $10, %eax
	call syscall_sysenter
	popl %ebp
	ret

/* int getpid() */
ENTRY(getpid)
	pushl %ebp
	movl %esp, %ebp
	movl $20, %eax
	call syscall_sysenter
	popl %ebp
	ret

/* int fork() */
ENTRY(fork)
	pushl %ebp
	movl %esp, %ebp
	movl $2, %eax
	call syscall_sysenter
	test %eax, %eax
	js nok	// if (eax < 0) -->
	popl %ebp
	ret

/* void exit() */
ENTRY(exit)
	pushl %ebp
	movl %esp, %ebp
	movl $1, %eax
	call syscall_sysenter
	popl %ebp
	ret

/* int yield() */
ENTRY(yield)
	pushl %ebp
	movl %esp, %ebp
	movl $13, %eax
	call syscall_sysenter
	popl %ebp
	ret

/* int get_stats(int pid, struct stats *st) */
ENTRY(get_stats)
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx;  // Save EBX, ESI and EDI if modified
	movl $35, %eax
	movl 0x8(%ebp), %ebx;	//pid
	movl 0xC(%ebp), %ecx;	//st
	call syscall_sysenter
	popl %ebx
	test %eax, %eax
	js nok	// if (eax < 0) -->
	popl %ebp
	ret

/*
  * int pollEvent(struct event_t *ev) 
  * We create this wrapper for the system call pollEvent to allow the user-mode code to invoke it without privileges.
  *
  * The wrapper consists of manually creating a dynamic link to the user code because in assembly, the compiler does not do it for you. 
  * 
  * Then save the registers that will be modified (%ebx to store the parameter, *ev, of the syscall), 
  * move to the register %eax the number asociated to the syscall in the sys_call_table.S, in this case 5. 
  * 
  * Afterward call the syscall sysenter which will save %ecx, %edx registers, create a dynamic link, and enter the system mode, pushing part of the HW context and calling the sys_call_handler.
  * 
  * After we've done the syscall, we restore the %ebx, check if we've had any error during the syscall, whose error number will be stored in the %eax register, if it's the case, we will jump to the 
  * funcion nok storing the error code in the errno variable and overwritte the %eax register with -1.
  * 
  * Finally, we undo the dynamic link and return to the user code with the result in the %eax register.
*/
ENTRY(pollEvent)
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx;
	movl $5, %eax
	movl 0x8(%ebp), %ebx;	//&ev
	call syscall_sysenter
	popl %ebx
	test %eax, %eax
	js nok
	popl %ebp
	ret
