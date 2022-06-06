/*
 * header file for parse.y and parse.l
 * this is just included in parse.y & parse.l
 */

// コマンド単体
// char*の配列
// 最後の要素はNULLになる
// sizeはNULLを除いた要素の個数
typedef struct {
  char **argv;
  int argc;
} ARGS;

// 一つのコマンド (リダイレクトなどは此方)
typedef struct {
  ARGS *args;
} CMD;

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

