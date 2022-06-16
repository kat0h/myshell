/*
 * ecec.c 2022@kotakato
 */

#include "exec.h"
#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <sysexits.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>
#include <string.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void run_ext_command(char *argv[]) {
  // システムコマンドを実行
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
  // セミコロンで区切られたコマンドを実行
  // 現状パイプで繋れたコマンドなどは処理できない
  for (int i = 0; i < line->size; i++) {
    SIMPLECMD *cmd = line->cmds[i]->cmd[0];

    // ビルトインコマンドを実行
    if (strcmp(cmd->argv[0], "cd") == 0) {
      // 引数個数チェック
      if (cmd->argc <= 1) {
        fprintf(stderr, "ERR: Too few argment\n");
        return;
      }
      int err = chdir(cmd->argv[1]);
      if (err == -1) {
        fprintf(stderr, "ERR: Directory not found\n");
      }
      return;
    }

    // default
    pid_t pid = fork();
    if (pid == 0) {
      // child
      // cmd[0]は固定
      run_ext_command(cmd->argv);
    } else {
      // parent
      wait_ext_command(pid);
    }
  }
}

