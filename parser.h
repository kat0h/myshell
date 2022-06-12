#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "parse.h"

int parse();

// flex
typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

// bison
extern int yyparse(void);
extern FILE *yyin;

extern LINE *line_tree;


#endif
