#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

Args* Args_new() {
  Args *args;
  args = (Args *)malloc(sizeof(Args));
  args->argv = NULL;
  args->argc = 0;
  return args;
}

void Args_free(Args *args) {
  for (int i = 0; i < args->argc; i++)
    free(args->argv[i]);
  free(args);
};

int Args_parse(Args *data, char *line) {
  return 0;
}
