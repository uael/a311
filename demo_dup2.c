#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define ENTREE_STANDARD 0

int main() {
  int descr_group, resultat;
  char c;
  descr_group = open("/etc/passwd", O_RDONLY);
  resultat = dup2(descr_group, ENTREE_STANDARD);
  c = (char) getchar();
  while (c != EOF) {
    putchar(c);
    c = (char) getchar();
  }
}
