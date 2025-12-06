#include <libc.h>

char buff[24];

int pid;

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	//clear screen (no forma part del milestone)
	write(1, "J", 2);
	
	//TEST1: 
	//	comprovació basica de cambi de color de fons i de color de text, en 
	//	aquest cas text->cyan fons->magenta
	//
	//	auria d'apareixel la linea "TEST1" de color cyan amb fons magenta
	write(1, "\n33m45mTEST1", 15);

	//TEST2: 
	//	mateixa comprovació que al pas anterior invertint els colors
	//
	//	auria d'apareixel la linea "TEST2" de color magenta amb fons cyan
	write(1, "\n35m43mTEST2", 15);

	//TEST3: 
	//	prova de cambiar de posició, y proba una posició en la que el primer 
	//	digit forma part de la sequencia de per cambiar el color de text, la miquna 
	//	de estats pasará primer per l'estat de cambi de color del text, y a la coma 
	//	transicionara al segon estat de cambi de posició
	//
	//	auria d'apareixer la linea "TEST3" a la linea de 
	//	sota de la anterior 3 columnes adelantada
	write(1, "3;3HTEST3", 38);

	//TEST4: 
	//	la mateixa comprovació que a la linea anterior, pero pasant per cambi de 
	//	color de fons en lloc de text.
	//
	//	auria d'apareixer la linea "TEST4" a la linea de 
	//	sota de la anterior 4 columnes adelantada
	write(1, "4;4HTEST4", 10);

	//TEST5: 
	//	comprovació del character del, mou el cursor sobre la s del "TEST3" 
	//	del test 3 i l'esborra
	//
	//	auria de desapareizer el character S de la linea del test 3
	write(1, "5;3H\x7F", 7);

	//TEST6: 
	//	comprovació d'un valor de y mes gran de la mida de la pantalla
	//
	//	auria d'apareixer la linea "TEST5" a la ultima fila de la pantalla.
	write(1, "15;3000HTEST5", 14);

	//TEST6: 
	
	//TEST6: 
	
	//TEST6: 
	
	//TEST6: 
	
	//TEST6: 
	
	//TEST6: 
	  while(1) { 

	}
}
