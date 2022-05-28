#include <stdio.h>
#include <unistd.h>

#include <sysexits.h>
#include <err.h>

#include "parser.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void prompt() {
  printf("$ ");
}

void lntrim(char *str) {
  int i = 0;
  while(1) {
    if(str[i] == '\n') {
      str[i] = '\0';
      break;
    }
    i++;
  }
}

void read_line(char* line, int size) {
  fgets(line, size, stdin);
  lntrim(line);
}

int main(int argc, char *argv[]) {
  prompt();

  char line[1000];
  read_line(line, sizeof(line));
  Args *args = Args_new();
  Args_parse(args, line);

  pid_t pid = fork();

  if (pid == -1) {
    err(EXIT_FAILURE, "fork failed");
  }

  if (pid == 0) {
    // parent
    return 0;
  } else {
    int e = execv(args->argv[0], args->argv);
    if (e == -1) {
      err(EXIT_FAILURE, "exec failed");
    }
    Args_free(args);
  }

  return EXIT_SUCCESS;
}
