/********************/
/*  demo_pipe : ... */
/********************/
# include <stdio.h>
char string[] = "hello";
int main()
{ char buf[70];
  int  fds[2];
  pipe (fds);
  write(fds[1], string, 6);
  read (fds[0], buf, 6);
  printf ("Chaine provenant du pipe-line : %s \n", buf);
}
