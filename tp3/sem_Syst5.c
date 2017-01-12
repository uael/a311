#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "sem_Syst5.h"

void sem_remove(int sem) {
  if (semctl(sem, 0, IPC_RMID, 0) != 0) {
    perror("sem_remove");
    exit(-1);
  }
}

void sem_change(int sem, int val) {
  struct sembuf sb[1];
  sb[0].sem_num = 0;
  sb[0].sem_op = (short) val;
  sb[0].sem_flg = 0;
  if (semop(sem, sb, 1) != 0) {
    perror("sem_change");
    exit(-1);
  }
}

int sem_create(key_t key, int mode) {
  int sem, r;
  if (mode == CREATION) {
    sem = semget(key, 1, IPC_CREAT | 0666);
    if (sem < 0) {
      perror("sem_create");
      exit(-1);
    }
    r = semctl(sem, 0, SETVAL, 1);
    if (r < 0) {
      perror("sem_create");
      exit(-1);
    }
  } else {
    sem = semget(key, 1, 0666);
    if (sem < 0) {
      perror("sem_use");
      exit(-1);
    }
  }
  return sem;
}

void P(int sem) { sem_change(sem, -1); }

void V(int sem) { sem_change(sem, 1); }


