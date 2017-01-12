/********************************************************************/
/* IUT NICE-COTE D'AZUR - Departement INFORMATIQUE - R. CHIGNOLI    */
/* Module DUT M311                            Theme IPC S5 & POSIX  */
/********************************************************************/
// sem51.c : affichage de / et * par un pere et un fils ...
// Pour sem52 : utiliser creer_sem(...), P (...), V(...) et detruire_sem(...)
//              (voir sem_Syst5.h et demo_sem.c)

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include "sem_Syst5.h"

typedef struct { int  nombre; char car;} struct_p;

void  imprimer (struct_p* param){   
   int i; 
   for (i=0 ; i < param->nombre; i++) printf ("%c", param->car); }

int main (int argc, char* argv[]) {
   int i, valeur, resultat; 
   struct_p x; 
   char tab[2] = {'/', '*'};

   assert (argc == 2);
   valeur = atoi (argv[1]);
   for (i=1; i<=2; i++) {
      if ((resultat = fork()) == -1){perror ("fork"); exit (1);}
      if (resultat == 0){ // Fils i
        x.nombre=valeur;  x.car=tab[i-1];
        printf ("FILS %d : affiche %d '%c'\n", i, x.nombre, tab[i-1]);
        imprimer (&x);
        exit (0);
      }
   }
}
        





