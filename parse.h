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
CMDS *cmds_new();
void cmds_push_cmd(CMDS *cmds, CMD *cmd);
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
