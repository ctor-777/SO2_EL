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
	write(1, "\n33m45mTEST1", 14);

	//TEST2: 
	//	mateixa comprovació que al pas anterior invertint els colors
	//
	//	auria d'apareixel la linea "TEST2" de color magenta amb fons cyan
	write(1, "\n35m43mTEST2", 14);

	//TEST3: 
	//	prova de cambiar de posició, y proba una posició en la que el primer 
	//	digit forma part de la sequencia de per cambiar el color de text, la miquna 
	//	de estats pasará primer per l'estat de cambi de color del text, y a la coma 
	//	transicionara al segon estat de cambi de posició
	//
	//	auria d'apareixer la linea "TEST3" a la linea de 
	//	sota de la anterior 3 columnes adelantada
	write(1, "3;3HTEST3", 10);

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
	write(1, "5;3H\x7F", 6);

	//TEST6: 
	//	comprovació d'un valor de y mes gran de la mida de la pantalla
	//
	//	auria d'apareixer la linea "TEST6" a la ultima fila de la pantalla.
	write(1, "15;3000HTEST6", 14);
	
	//TEST7: 
	//	comprovació d'un valor de x mes gran de la mida de la pantalla
	//
	//	auria d'apareixer la linea "TEST7" que comença a l'ultima columna (fara wrap a la linea anterior).
	write(1, "3000;7HTEST7", 13);

	//TEST8: 
	//	comprovació del cambit d'estat des de CHANGE_BG/FG a CHANGE_POS_Y en 
	//	cas d'una coordenada que comença per 3 o 4 (com als tests 3 i 4) per ambs dos digits
	//
	//	auria d'apareixer la linea "TEST8" a la columna 31 i a la fila 10
	write(1, "31;10HTEST8", 12);
	
	//TEST9: 
	//	comprovació d'un color de fons i de text no valid
	//
	//	auria de fer la marcara dels colors
	write(1, "\n3200m4500mTEST9", 18);
	
	//TEST10: 
	//	comprovació d'un color de fons i de text mes gran de 7 (bright colors)
	//
	//	auria de fer el cambi de color de text a blanc y fer la mascara de 9 (1 blau)
	write(1, "\n315m49mTEST10", 16);
	
	//TEST11: 
	//	comprovació del backspace.
	//
	//	auria de escriure TE11, ja que ha eliminat els characters ST.
	write(1, "\nTEST\b\b11", 9);
	
	//TEST12: 
	//	comprovació del backspace al final de la linea
	//
	//	auria de escriure TEST
	write(1, "\nTEST12\b\b", 9);

	//TEST13: 
	//	comprovació dels maxims valor per texte i fons
	//
	//	auria de escriure TEST13 amb text blanc i fons gris
	write(1, "\n315m47mTEST13", 16);
	//TEST6: 
	  while(1) { 

	}
}
