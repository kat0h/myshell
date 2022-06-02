#ifndef PARSER_H
#define PARSER_H

#include "str.h"

typedef struct {
  char **argv;
  int argc;
} Args;

Args* Args_new();
void Args_free(Args *args);
int Args_parse(Args *args, char *line);

// $ "echo" hoge
typedef struct {
  int type;
  char *str;
} Arg;

// $ Args2
typedef struct {
  Arg *args;
  int argc;
} Args2;

// $ Args2 | Args2
typedef struct {
  Args2 *args;
} Commands;

#endif
