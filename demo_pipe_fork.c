
// demo_pipe_fork : ...
// - Demande de descripteurs de pipe line,
// - demande de fork,
// - PERE : lit des car. au clavier, ecrit dans le pipe-line
//          (apres fermeture du descr. inutile),
// - FILS : lit dans le pipe-line, ecrit les car. recus
//         (apres fermeture du descr. inutile),

#include <stdio.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main() {
  int pid, ok, tabpipe[2], i;
  FILE *stream;
  char c;
  char *type;
  ok = pipe(tabpipe);
  pid = fork();
  if (pid < 0) printf("ERREUR FORK");
  else if (pid == 0) {
    /******* FILS  : LIT DANS LE PIPE-LINE **********/
    type = "r";
    stream = fdopen(tabpipe[0], type);
    close(tabpipe[WRITE]);
    /* Lecture dans le pipe-line */
    c = (char) fgetc(stream);
    while (c != EOF) {
      printf("Car. recu : %c \n", c);
      fflush(stdout);
      c = (char) fgetc(stream);
    }
  } else {
    /******* PERE  : ECRIT DANS LE PIPE-LINE ********/
    printf("Message a envoyer (ctrl.D pour finir) : ");
    close(tabpipe[READ]);
    type = "w";
    stream = fdopen(tabpipe[1], type);
    /* Lecture au clavier, ecriture dans le pipe-line  */
    c = (char) getchar();
    while (c != EOF) {
      fputc(c, stream);
      fflush(stream);
      c = (char) getchar();
    }
    /* Production de la fin de fichier */
    fclose(stream);
  }
}
