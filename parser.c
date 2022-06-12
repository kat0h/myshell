#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "parser.h"
#include "parse.h"

int parse(LINE *line, char *input_line) {
  YY_BUFFER_STATE buffer = yy_scan_string(input_line);

  if (yyparse()) {
    fprintf(stderr, "Parser Error");
    exit(1);
  }

  line = line_tree;

  yy_delete_buffer(buffer);
  return 0;
}

// -DPARSER_MAIN
#ifdef PARSER_MAIN
int main() {
  LINE *l;
  parse(l, "echo unko\n");
  return 0;
}
#endif
