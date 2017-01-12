#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "sem_Syst5.h"

int main(int argc, char *argv[]) {
  key_t key;
  char response;
  int sem, mode, encore = 1;

  if (argc < 3) {
    fprintf(stderr, "Usage: %s [-c|-u] key\n", argv[0]);
    exit(1);
  }
  if ((argc == 3) && (strcmp(argv[1], "-c") == 0)) {
    mode = CREATION;
    printf("Mode c\n\n");
    key = atoi(argv[2]);
  } else if ((argc == 3) && (strcmp(argv[1], "-u") == 0)) {
    mode = USE;
    printf("Mode u\n\n");
    key = atoi(argv[2]);
  } else {
    fprintf(stderr, "Usage: %s [-c|-u] key\n", argv[0]);
    exit(2);
  }
  sem = sem_create(key, mode);
  while (encore) {
    printf("P,V,X,Q ? ");
    response = (char) getchar();
    __fpurge(stdin);
    switch (response) {
      case 'P':
        P(sem);
        printf("... P OK.\n");
        break;
      case 'V':
        V(sem);
        printf("... V OK.\n");
        break;
      case 'X':
        sem_remove(sem);
        printf("... Semaphore destroyed\n");
        encore = 0;
        break;
      case 'Q':
        encore = 0;
        break;
      default:
        printf("... Invalid command: %c\n", response);
    }
  }
  printf("... Bye\n");
}
