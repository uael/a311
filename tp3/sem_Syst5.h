#define CREATION 1
#define USE 0

int sem_create(key_t key, int mode);
void P(int sem);
void V(int sem);
void sem_remove(int sem);


