#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "parser.h"
#include "parse.h"
#include "exec.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void prompt() {
  printf("$ ");
}

int read_line(char* line, int size) {
  char *result = fgets(line, size, stdin);
  if (result != NULL)
    return 0;
  else
    return -1;
}

int main_loop() {
  // show prompt
  prompt();

  // read  line
  // char *line = "echo test | cat\n";
  char line[1000];
  if (read_line(line, 1000) == -1) {
    return 0;
  };

  LINE *l = NULL;
  int i = 0;
  parse(&l, line);
  if (l != NULL) {
    // パーサーが作成した構造体からコマンドを実行：
    exec_command(l);

    // 入力で確保されたメモリーを解放する
    line_free(l);
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
