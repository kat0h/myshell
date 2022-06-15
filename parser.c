/*
 * parser.c 2022@kotakato
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "parser.h"
#include "parse.h"

int parse(LINE **l, char *input_line) {
  YY_BUFFER_STATE buffer = yy_scan_string(input_line);

  if (yyparse()) {
    fprintf(stderr, "Parser Error");
    // エラー時は1などを返して知らせる
    exit(1);
  }

  *l = line_tree;

  yy_delete_buffer(buffer);
  return 0;
}

// -DPARSER_MAIN
#ifdef PARSER_MAIN
int main() {
  char line[1000];
  while(1) {
    printf(">>> ");
    fgets(line, 1000, stdin);
    if (feof(stdin))
      break;
    LINE *l;
    parse(&l, line);
    line_pp(l);
    line_free(l);
  }
  return 0;
}
#endif
