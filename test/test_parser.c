#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "../parser.h"

int main(int argc, char *argv[]) {
  // read stdin
  char input[1000];
  strncpy(input, argv[1], 1000);
  // parse input
  Args *args = Args_new();
  Args_parse(args, input);
  // print args
  for (int i=0; i < args->argc; i++) {
    printf("\"%s\"", args->argv[i]);
    if (i != args->argc - 1)
      printf(",");
  }
  printf("\n");
  if (!(args->argv[args->argc] == NULL)) {
    // error
    return 1;
  }
  // free memory
  Args_free(args);
}
