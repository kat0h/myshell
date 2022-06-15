%{
#include <stdio.h>
#include "parse.h"
#include "myshell.tab.h"
#include "str.h"

char *string_buffer = NULL;

// TODO
// * 引数のパースについて
//   * echo ""hoge"" は'hoge'と解釈される
//   * 現状 ""hoge"" は' hoge'と解釈される
%}

%x STRING

%%


; {
  return SEMICOLON;
}

\" {
  string_buffer = newStr();
  BEGIN STRING;
}

[^ \n;\"]* {
  char *arg = newStr();
  setStr(arg, yytext);
  yylval.arg = arg;
  return ARG;
}

"\n" {
  return CR;
}

. {}

<STRING>\\\" {
  // エスケープされた二重引用符
  addStr(string_buffer, "\"");
}

<STRING>\" {
  // argはyacc側で解放されます
  char *arg = newStr();
  setStr(arg, string_buffer);

  // string_bufferを解放する
  free(string_buffer);
  string_buffer = NULL;

  yylval.arg = arg;
  BEGIN INITIAL;
  return ARG;
}

<STRING>. {
  addStr(string_buffer, yytext);
}

%%

int yywrap(void) {
  return 1;
}
