/********************************************************************/
/* IUT NICE-COTE D'AZUR - Departement INFORMATIQUE - R. CHIGNOLI    */
/* Module DUT M311                            Theme IPC S5 & POSIX  */
/********************************************************************/
// sem51.c : affichage de / et * par un pere et un fils ...
// Pour sem52 : utiliser sem_create(...), P (...), V(...) et sem_remove(...)
//              (voir sem_Syst5.h et demo_sem.c)

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include "sem_Syst5.h"

typedef struct _my_struct_t {
  int number;
  char car;
} my_struct_t;

void print(my_struct_t *param) {
  int i;
  for (i = 0; i < param->number; i++) printf("%c", param->car);
}

int main(int argc, char *argv[]) {
  int i, value, resultat;
  my_struct_t x;
  char tab[2] = {'/', '*'};

  assert (argc == 2);
  value = atoi(argv[1]);
  for (i = 0; i < 2; i++) {
    if ((resultat = fork()) == -1) {
      perror("fork");
      exit(1);
    }
    if (resultat == 0) {
      x.number = value;
      x.car = tab[i];
      printf("Child %d : print %d '%c'\n", i+1, x.number, tab[i]);
      print(&x);
      exit(0);
    }
  }
}
        





