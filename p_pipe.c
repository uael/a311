/***********************************************************************/
/*                                                                     */
/* p_pipe      : - Demande de descripteurs de pipe-line,               */
/*               - Demande de fork,                                    */
/*               - PERE : execute la commande wc-l depuis le pipe-line */
/*                        (apres avoir ferme le descripteur inutile),  */
/*               - FILS : execute la commande ls -ls vers le pipe-line */
/*                        (apres avoir ferme le descripteur inutile).  */
/*                                                                     */
/***********************************************************************/
/*  - dup2 : remplacement d'un descripteur par un autre (BAS NIVEAU).  */
/*                                                                     */
/*           int dup2 (desc_1, desc_2)                                 */
/*           int desc_1, desc_2;                                       */
/*                                                                     */
/*   Duplication du descripteur desc_1 "dans" le descripteur desc_2.   */
/*                                                                     */
/*   S'il etait ouvert, le fichier decrit par desc_2 est ferme.        */
/*                                                                     */
/*   Donc, apres dup2, les E/S destinees a desc_2 se passent sur desc_1*/
/*                                                                     */
/***********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>*

#define READ 0
#define WRITE 1

int main() {
  int tabpipe[2], tabpipe2[2];

  pipe(tabpipe);
  if (fork() == 0) {
    dup2(tabpipe[WRITE], WRITE);
    char *argv[] = {"ls", "-l", NULL};
    execvp("ls", argv);
  }
  else {
    pipe(tabpipe2);
    close(tabpipe[WRITE]);
    if (fork() == 0) {
      dup2(tabpipe[READ], READ);
      dup2(tabpipe2[WRITE], WRITE);
      char *argv[] = {"grep", "pipe", NULL};
      execvp("grep", argv);
    }
    else {
      close(tabpipe2[WRITE]);
      dup2(tabpipe2[READ], READ);
      char *argv[] = {"wc", "-l", NULL};
      execvp("wc", argv);
    }
  }

  return 0;
}