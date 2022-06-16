/*
 * parse.h 2022@kotakato
 */

#ifndef PARSE_H
#define PARSE_H

// 一つのコマンド (リダイレクトなどは此方)
// argv: char*の配列 最後の要素はNULLになる
// argc: 最後のNULLを除いたargvの要素数
typedef struct {
  char **argv;
  int argc;
} SIMPLECMD;
SIMPLECMD *simplecmd_new();
void simplecmd_push_arg(SIMPLECMD *cmd, char *arg);
void simplecmd_free(SIMPLECMD *cmd);
void simplecmd_pp(SIMPLECMD *cmd);

// 現状pipeで繋がれたコマンド
// CMDの配列
typedef struct {
  SIMPLECMD **cmd;
  int size;
} CMDS;
CMDS *cmds_new();
void cmds_push_cmd(CMDS *cmds, SIMPLECMD *cmd);
void cmds_free(CMDS *cmds);
void cmds_pp(CMDS *cmds);

// 現状;で繋がれたコマンド
typedef struct {
  CMDS **cmds;
  int size;
} LINE;
LINE *line_new();
void line_push_cmds(LINE *line, CMDS *cmds);
void line_free(LINE *line);
void line_pp(LINE *line);

#endif
