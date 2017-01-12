/********************************************************************/
/* IUT NICE-COTE D'AZUR - Departement INFORMATIQUE - R. CHIGNOLI    */
/* Module DUT M311                            Theme IPC S5 & POSIX  */
/********************************************************************/
// sem_Syst5.h : specification des fonctions utilitaires M311

#define CREATION 1
#define UTILISATION 0

int creer_sem(key_t key, int mode); 

void P(int sem); 

void V(int sem); 

void detruire_sem(int sem); 


