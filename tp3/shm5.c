/******************************************************************/
/* IUT NICE-COTE D'AZUR - Departement INFORMATIQUE - R. CHIGNOLI  */
/* Module DUT SYS-RX                              Theme 1 IPC S5  */
/******************************************************************/
/* shm2.c : Squelette pour les questions 2.X                      */
/******************************************************************/
#include <stdlib.h> 
#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/shm.h>

typedef struct _shared_memory_t {
  int count;
  int date;
} shared_memory_t;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "\nSyntaxe : %s num-cle\n\n", argv[0]);
    exit(1);
  }
  int memid, result, key = atoi(argv[1]);
  shared_memory_t *memory;

  memid = shmget(key, sizeof(shared_memory_t), 0777 | IPC_CREAT);
  if (memid == -1) {
    perror("shmget");
    exit(-1);
  }

  result = shmctl(memid, IPC_RMID, SHM_INFO);
  if (result == -1) {
    perror("shmctl");
    exit(-1);
  }

  printf("shmctl %d", result);
}

