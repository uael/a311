/***********************************************************************/
/*                                                                     */
/* p_pipe_arg  : - Demande de descripteurs de pipe-line,               */
/*               - Demande de fork,                                    */
/*               - PERE : recupere le deuxieme parametre qui correspond*/
/*                        a la commande qui doit s'executer depuis le  */
/*                        pipe-line.                                   */
/*               - FILS : recupere le premier parametre qui correspond */
/*                        a la commande qui doit s'executer vers le    */
/*                        pipe-line.                                   */
/*                                                                     */
/* EXEMPLE     : p_pipe_arg who wc  <====> who | wc                    */
/*                                                                     */
/*                                                                     */
/***********************************************************************/

#include <stdio.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
  int tabpipe[2];

  if (argc != 3) {
    fprintf(stderr, "SYNTAXE: %s command1 command2\n", argv[0]);
  }

  pipe(tabpipe);
  if (fork()) {
    dup2(tabpipe[WRITE], WRITE);
    char *args[] = {argv[1], NULL};
    execvp(argv[1], args);
  }
  else {
    close(tabpipe[WRITE]);
    dup2(tabpipe[READ], READ);
    char *args[] = {argv[2], NULL};
    execvp(argv[2], args);
  }

  return 0;
}
