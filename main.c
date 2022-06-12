#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <strings.h>
#include <sysexits.h>
#include <sys/wait.h>
#include <err.h>

#include "parser.h"
#include "parse.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void prompt() {
  printf("$ ");
}

int read_line(char* line, int size) {
  char *result = fgets(line, size, stdin);
  printf("%lu", strlen(line));
  printf("u");
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
  char *line = "echo test | cat\n";
  // char line[1000];
  // if (read_line(line, 1000) == -1) {
  //   return 0;
  // };

  LINE *l = NULL;
  parse(l, line);

  // if (l != NULL) {
  //   // LINE
  //   puts("{");
  //   for (int i=0; i<(l->size); i++) {
  //     // CMDS
  //     CMDS *c = l->cmds[i];
  //     printf(" {\n  ");
  //     for (int j=0; j<(c->size); j++) {
  //       CMD *a = c->cmd[j];
  //       // 一つのコマンド
  //       printf("{");
  //       for (int k=0; k<(a->argc); k++) {
  //         printf(" '%s'", a->argv[k]);
  //       }
  //       printf(" } ");
  //       if (j+1<c->size)
  //         printf("'|' ");
  //     }
  //     puts("\n }");
  //   }
  //   puts("}");
  // 
  // }

  // line_free(l);
  return 1;
}

int main(int argc, char *argv[]) {
  int status = 0;
  while (status) {
    status = main_loop();
  }
  main_loop();

  return EXIT_SUCCESS;
}
