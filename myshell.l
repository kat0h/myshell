%{
#include <stdio.h>
#include "parse.h"
#include "myshell.tab.h"
%}

%%

; {
  return SEMICOLON;
}

[^ \n;]* {
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
