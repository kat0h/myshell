%{
#include <stdio.h>
#include "parse.tab.h"
%}

%%

\| {
  return PIPE;
}

; {
  return SEMICOLON;
}

[^ \n]* {
  yylval.arg = yytext;
  return ARG;
}

"\n" {
  return CR;
}

. ;

%%

int yywrap(void) {
  return 1;
}
