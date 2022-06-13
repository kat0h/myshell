#include "exec.h"
#include <stdio.h>
#include <sysexits.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

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

void exec_command(LINE *line) {
  pid_t pid = fork();

  // forkが失敗したときのエラー処理
  if (pid == 0) {
    // child
    run_ext_command(line->cmds[0]->cmd[0]->argv);
  } else {
    // parent
    wait_ext_command(pid);
  }
}

