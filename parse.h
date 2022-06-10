#ifndef PARSE_H
#define PARSE_H

// 一つのコマンド (リダイレクトなどは此方)
// argv: char*の配列 最後の要素はNULLになる
// argc: 最後のNULLを除いたargvの要素数
typedef struct {
  char **argv;
  int argc;
} CMD;
CMD *cmd_new();
void cmd_push_arg(CMD *cmd, char *arg);
void cmd_free(CMD *cmd);
void cmd_pp(CMD *cmd);

// 現状pipeで繋がれたコマンド
// CMDの配列
typedef struct {
  CMD **cmd;
  int size;
} CMDS;

// 現状;で繋がれたコマンド
typedef struct {
  CMDS **cmds;
  int size;
} LINE;

#endif
