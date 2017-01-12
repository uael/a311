/********************************************************************/
/* IUT NICE-COTE D'AZUR - Departement INFORMATIQUE - R. CHIGNOLI    */
/* Module DUT M311                            Theme IPC S5 & POSIX  */
/********************************************************************/
// demo_sem.c : Demonstration d'utilisation d'un smaphore
// usage : commande [-creation]  cle                                                                             
// premier acces : utiliser l'option "-creation"                                              
// Utiliser la commande ipcs pour voir la situation systeme 
// Utiliser la commande iprm pour detruire une ressource systeme  

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "sem_Syst5.h"

int main(int argc, char *argv[])
{
  key_t key;
  char reponse;
  int sem, mode, encore = 1;
  
  if (argc < 3) { fprintf(stderr, "Usage: %s [-creation | -use ] cle\n", argv[0]); exit(1);}
  if ((argc == 3) && (strcmp (argv[1], "-creation") == 0))
   { mode = CREATION; printf ("Mode creation\n\n"); key = atoi(argv[2]); }
  else if ((argc == 3) && (strcmp (argv[1], "-use") == 0))
   { mode = UTILISATION; printf ("Mode utilisation\n\n"); key = atoi(argv[2]);  }
  else 
  { fprintf(stderr, "Usage: %s [-creation | -use ] cle\n", argv[0]); exit(2);}
   sem = creer_sem(key, mode);
  while (encore) {
    printf("P,V,X,Q ? "); reponse = getchar(); 
    __fpurge(stdin); // ... pour bonne gestion du buffer clavier ... 
    switch (reponse) {
    case 'P': P(sem); printf("... P OK.\n"); break;
    case 'V': V(sem); printf("... V OK.\n"); break;
    case 'X': detruire_sem(sem);
      printf("... Semaphore detruit\n"); encore = 0;
      break;
    case 'Q':
      encore = 0; break;
    default: printf("... Commande incorrecte\n");
    }
  }
  printf("... Bye\n");
}
