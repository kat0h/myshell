#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "parser.h"
#include "str.h"

Args* Args_new() {
  Args *args;
  args = (Args *)malloc(sizeof(Args));
  args->argv = NULL;
  args->argc = 0;
  return args;
}

void Args_free(Args *args) {
  // TODO

};

#define STR_LIT 1
typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yylex();
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern char *yytext;
extern char *yybuffer;

int Args_parse(Args *args, char *line) {
  YY_BUFFER_STATE buffer = yy_scan_string(line);
  yybuffer = newStr();

  int token = yylex();
  while (token) {
    switch (token) {
      case STR_LIT:
        args->argc++;
        // resize argv
        args->argv = realloc(args->argv, sizeof(char *) * args->argc);
        char *ptr = newStr();
        setStr(ptr, yybuffer);
        args->argv[args->argc-1] = ptr;
    }
    setStr(yybuffer, "");
    token = yylex();
  }
  // set last pointer to NULL
  args->argv = realloc(args->argv, sizeof(char *) * (args->argc + 1));
  args->argv[args->argc] = NULL;

  freeStr(yybuffer);
  yy_delete_buffer(buffer);

  return 0;
}
