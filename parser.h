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

#endif
