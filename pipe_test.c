#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define R (0)
#define W (1)

char *const cmd1[] = { "echo", "hoge", NULL };
char *const cmd2[] = { "rev", NULL };

int
main(int argc, char *argv[])
{
  // make pipe
  int pfd[2];
  pipe(pfd);

  // fork process
  pid_t pid = fork();

  if (pid == 0) {
    // child
    close(pfd[W]);
    dup2(pfd[R], R);
    close(pfd[R]);
    execvp(cmd2[0], cmd2);
  } else {
    // parent
    close(pfd[R]);
    dup2(pfd[W], W);
    close(pfd[W]);
    execvp(cmd1[0], cmd1);
  }

  return 0;
}
