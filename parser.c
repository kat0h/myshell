#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "parser.h"

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

int Args_parse(Args *args, char *line) {
  int c = 0;
  int sc = 1;
  // TODO: if line is "                      " then clash
  // スペースをヌル文字に変える

  // count spaces
  while(line[c] != '\0') {
    if (line[c] == ' ')
      sc++;
    c++;
  }
  args->argc = sc;
  // +2 is for NULL
  args->argv = (char **) malloc((sc + 2) * sizeof(char *));


  int i = 0;
  c = 0;
  for (i = 0; i < sc; i++) {
    int wc = 0;
    int start = c;
    while(line[c] != ' ' && line[c] != '\0') {
      wc++;
      c++;
    }
    char *arg = (char *) malloc((wc+1) * sizeof(char));
    strncpy(arg, &line[start], wc);
    arg[wc] = '\0';

    args->argv[i] = arg;

    if (line[c] == '\0')
      break;
    else
      c++;

  }

  args->argv[args->argc] = NULL;

  return 0;
}
