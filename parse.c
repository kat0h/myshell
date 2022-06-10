#include <stdlib.h>
#include <stdio.h>
#include "./parse.h"

CMD *cmd_new() {
  CMD *cmd = malloc(sizeof(CMD));
  char **argv = malloc(sizeof(char *));
  cmd->argv = argv;
  cmd->argv[0] = NULL;
  cmd->argc = 0;
  return cmd;
}

// cmd_push_arg()
// cmd->argcをインクリメントし、cmd->argvに渡されたargのポインターをそのまま代入します。
void cmd_push_arg(CMD *cmd, char *arg) {
  cmd->argv = realloc(cmd->argv, sizeof(char *) * (cmd->argc + 2));
  cmd->argv[cmd->argc] = arg;
  cmd->argv[cmd->argc+1] = NULL;
  cmd->argc++;
}

// cmd_free()
// 渡されたcmdとargvの各要素を全て解放します
void cmd_free(CMD *cmd) {
  for (int i = 0; i <= cmd->argc; i++) {
    free(cmd->argv[i]);
  }
  free(cmd->argv);
  free(cmd);
}

void cmd_pp(CMD *cmd) {
  printf("argc: %d\n", cmd->argc);
  puts("argv: {");
  for (int i=0; i<(cmd->argc); i++) {
    printf("  \"%s\"\n", cmd->argv[i]);
  }
  puts("}\n");
}

int main(void) {
  CMD *cmd = cmd_new();
  cmd_push_arg(cmd, "echo");
  cmd_push_arg(cmd, "test");
  cmd_pp(cmd);
  cmd_free(cmd);
}
