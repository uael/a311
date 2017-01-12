/******************************************************************/
/* IUT NICE-COTE D'AZUR - Departement INFORMATIQUE - R. CHIGNOLI  */
/* Module DUT SYS-RX                              Theme 1 IPC S5  */
/******************************************************************/
/* shm2.c : Squelette pour les questions 2.X                      */
/******************************************************************/
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h>

#include <sys/time.h>
#include <time.h>

int main(int argc, char * argv[]) { 
    if (argc != 2) {fprintf (stderr, "\nSyntaxe : %s num-cle\n\n", argv[0]); exit (1);}
    /* CLE : UTILISER ARGV[1] */
}

