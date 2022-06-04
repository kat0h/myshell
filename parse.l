%{
#include <stdio.h>
#include "../str.h"

#define STR_LIT 1
#define PIPE 2

extern void yy_input(char*, int*, int);
#define yy_input(buf, count, max) yy_input(buf, &count, max)

char *yybuffer = NULL;
%}

%x STR_LIT

%%

<INITIAL>[ \n\t];
<INITIAL>\| {
  return PIPE;
};
<INITIAL>[^ \n\t]* {
  setStr(yybuffer, yytext);
  return STR_LIT;
};
<INITIAL>. ;


%%

int yywrap(void) {
  return 1;
}
