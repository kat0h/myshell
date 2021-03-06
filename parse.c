/*
 * parse.c 2022@kotakato
 */

#include <stdlib.h>
#include <stdio.h>
#include "./parse.h"
#include "./str.h"

int DEBUG_INDENT = 0;
#define INDENT() for(int indent=0;indent<DEBUG_INDENT;indent++)printf("  ")

SIMPLECMD *simplecmd_new() {
  SIMPLECMD *cmd = malloc(sizeof(SIMPLECMD));
  char **argv = malloc(sizeof(char *));
  cmd->argv = argv;
  cmd->argv[0] = NULL;
  cmd->argc = 0;
  return cmd;
}

// simplecmd_push_arg()
// cmd->argcをインクリメントし、cmd->argvに渡されたargのポインターをそのまま代入します。
void simplecmd_push_arg(SIMPLECMD *cmd, char *arg) {
  cmd->argv = realloc(cmd->argv, sizeof(char *) * (cmd->argc + 2));
  cmd->argv[cmd->argc] = arg;
  cmd->argv[cmd->argc+1] = NULL;
  cmd->argc++;
}

// simplecmd_free()
// 渡されたcmdとargvの各要素を全て解放します
void simplecmd_free(SIMPLECMD *cmd) {
  for (int i = 0; i < cmd->argc; i++) {
    free(cmd->argv[i]);
  }
  free(cmd->argv);
  free(cmd);
}

// simplecmd_pp()
// cmdの内容を表示します. デバグ用
void simplecmd_pp(SIMPLECMD *cmd) {
  INDENT();
  printf("argc: %d\n", cmd->argc);
  INDENT();
  puts("argv: {");
  for (int i=0; i<(cmd->argc); i++) {
    INDENT();
    printf("  \"%s\"\n", cmd->argv[i]);
  }
  INDENT();
  puts("}");
}

CMDS *cmds_new() {
  CMDS *cmds = malloc(sizeof(CMDS));
  SIMPLECMD **c = malloc(sizeof(SIMPLECMD *));
  cmds->cmd = c;
  // set initial value
  cmds->size = 0;
  cmds->cmd[0] = NULL;
  return cmds;
}

void cmds_push_cmd(CMDS *cmds, SIMPLECMD *cmd) {
  cmds->size++;
  cmds->cmd = realloc(cmds->cmd, sizeof(SIMPLECMD *) * (cmds->size + 1));
  cmds->cmd[cmds->size-1] = cmd;
  cmds->cmd[cmds->size] = NULL;
}

void cmds_free(CMDS *cmds) {
  for (int i = 0; i < cmds->size; i++) {
    simplecmd_free(cmds->cmd[i]);
  }
  free(cmds->cmd);
  free(cmds);
}

void cmds_pp(CMDS *cmds) {
  INDENT();
  printf("size: %d\n", cmds->size);
  INDENT();
  puts("cmd: {");
  DEBUG_INDENT++;
  for (int i=0; i<(cmds->size); i++) {
    simplecmd_pp(cmds->cmd[i]);
  }
  DEBUG_INDENT--;
  INDENT();
  puts("}");
}

LINE *line_new() {
  LINE *line = malloc(sizeof(LINE));
  CMDS **c = malloc(sizeof(CMDS *));
  line->cmds = c;
  line->cmds[0] = NULL;
  line->size = 0;
  return line;
}

void line_push_cmds(LINE *line, CMDS *cmds) {
  line->size++;
  line->cmds = realloc(line->cmds, sizeof(CMDS *) * (line->size + 1));
  line->cmds[line->size-1] = cmds;
  line->cmds[line->size] = NULL;
}

void line_free(LINE *line) {
  for (int i = 0; i < line->size; i++) {
    cmds_free(line->cmds[i]);
  }
  free(line->cmds);
  free(line);
}

void line_pp(LINE *line) {
  INDENT();
  printf("size: %d\n", line->size);
  INDENT();
  puts("cmds: {");
  DEBUG_INDENT++;
  for (int i=0; i<(line->size); i++) {
    cmds_pp(line->cmds[i]);
  }
  DEBUG_INDENT--;
  INDENT();
  puts("}");
}

// -DPARSE_MAIN
#ifdef PARSE_MAIN
int main(void) {
  SIMPLECMD  *cmd  = cmd_new();
  CMDS *cmds = cmds_new();
  LINE *line = line_new();

  char *i = newStr();
  char *j = newStr();
  i = setStr(i, "echo");
  j = setStr(j, "test");

  cmd_push_arg(cmd, i);
  cmd_push_arg(cmd, j);
  cmds_push_cmd(cmds, cmd);
  line_push_cmds(line, cmds);

  line_pp(line);

  line_free(line);
}
#endif
