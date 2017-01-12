/********************************************************************/
/* IUT NICE-COTE D'AZUR - Departement INFORMATIQUE - R. CHIGNOLI    */
/* Module DUT M311                            Theme IPC S5 & POSIX  */
/********************************************************************/
// sem_Syst5.c : code des fonctions utilitaires M311

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "sem_Syst5.h"

void detruire_sem(int sem)
{ if (semctl(sem, 0, IPC_RMID, 0) != 0) {perror("detruire_sem"); exit(-1);}}

void changer_sem(int sem, int val)
{ struct sembuf sb[1];
  sb[0].sem_num = 0;  sb[0].sem_op = val;  sb[0].sem_flg = 0;
  if (semop(sem, sb, 1) != 0){ perror("changer_sem"); exit(-1);}
}

int creer_sem(key_t key, int mode)
{
  int sem,r;
  if (mode == CREATION) {
    sem = semget(key, 1, IPC_CREAT | IPC_EXCL  | 0666);
    if (sem < 0) { perror("Creer_sem"); exit(-1); }
    r = semctl(sem, 0, SETVAL, 1);      /* valeur initiale = 1 */
    if (r < 0) { perror("initialisation smaphore"); exit(-1); }
  }
  else
  {
    sem = semget(key, 1, 0666);
    if (sem < 0) { perror("Utiliser_sem"); exit(-1); }
  }
  
  printf ("\nSemaphore OK(%d) !\n\n", key);
  return sem;
}

void P(int sem){ changer_sem(sem, -1);}

void V(int sem){ changer_sem(sem, 1);}


