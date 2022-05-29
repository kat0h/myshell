#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sysexits.h>
#include <sys/wait.h>
#include <err.h>

#include "parser.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void prompt() {
  printf("$ ");
}

int read_line(char* line, int size) {
  char *result = fgets(line, size, stdin);
  line[strlen(line) - 1] = '\0';
  if (result != NULL)
    return 0;
  else
    return -1;
}

void run_ext_command(char *argv[]) {
  int e = execvp(argv[0], argv);
  if (e == -1) {
    err(EXIT_FAILURE, "exec failed");
  }
}

void wait_ext_command(pid_t pid) {
  int wstatus;
  if (waitpid(pid, &wstatus, 0) == -1) {
    err(EXIT_FAILURE, "waitpid");
  }
}

int main_loop() {
  // show prompt
  prompt();

  // read  line
  char line[1000];
  if (read_line(line, sizeof(line)) == -1) {
    return 0;
  };

  // parse arguments
  Args *args = Args_new();
  Args_parse(args, line);

  // fork process
  pid_t pid = fork();
  if (pid == -1) {
    err(EXIT_FAILURE, "fork failed");
  }

  // run command
  if (pid == 0) {
    run_ext_command(args->argv);
    Args_free(args);
  } else {
    // parent
    wait_ext_command(pid);
  }

  return 1;
}

int main(int argc, char *argv[]) {
  int status = 1;
  while (status) {
    status = main_loop();
  }

  return EXIT_SUCCESS;
}
