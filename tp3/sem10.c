#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/sem.h>
#include <string.h>
#include "sem_Syst5.h"

typedef struct _my_struct_t {
  char chars[7];
} my_struct_t;

void print(my_struct_t *param) {
  int i;
  for (i = 0; i < 7; i++) printf("%c", param->chars[i]);
}

int main(int argc, char *argv[]) {
  int value, resultat, sem;
  my_struct_t x;

  assert (argc == 2);
  value = atoi(argv[1]);

  if ((resultat = fork()) == -1) {
    perror("fork");
    exit(1);
  }

  sem = sem_create(value, CREATION);
  if (resultat == 0) {
    P(sem);
    print(&x);
  } else {
    sem = sem_create(value, USE);
    strcpy(x.chars, "BONJOUR");
    V(sem);
  }

  return 0;
}
        





