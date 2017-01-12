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
#include <time.h>

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

  memid = shmget(key, sizeof(shared_memory_t), 0777 | IPC_EXCL);
  if (memid == -1) {
    perror("shmget");
    exit(-1);
  }

  memory = shmat(memid, NULL, 0);
  if (memory == (shared_memory_t *) -1) {
    perror("shmat");
    exit(-1);
  }

  printf("last access: %s", ctime((time_t *) &memory->date));

  result = shmdt(memory);
  if (result == -1) {
    perror("shmdt");
    exit(-1);
  }
}

