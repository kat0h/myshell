/*
 * myshell.y 2022@kotakato
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "parse.h"
#include "str.h"

// flex
extern int yylex(void);
extern int yyerror(char const *str);

// parser.c
LINE *line_tree = NULL;

%}
%union {
  char *arg ;
  SIMPLECMD *simplecmd;
  CMDS *cmds;
  LINE *line;
}
%token PIPE SEMICOLON CR <arg> ARG
%type <arg>  arg
%type <simplecmd>  simplecmd
%type <cmds> cmds
%type <line> line
%%

l
  : line CR {
    // ポインタはparser.cで解放されます
    line_tree = $1;
  }
  | CR {
    line_tree = NULL;
  }
  ;
line
  : cmds {
    LINE *ptr = line_new();
    line_push_cmds(ptr, $1);
    $$ = ptr;
  }
  | line SEMICOLON cmds {
    line_push_cmds($1, $3);
    $$ = $1;
  }
  ;
cmds
  : simplecmd {
    CMDS *ptr = cmds_new();
    cmds_push_cmd(ptr, $1);
    $$ = ptr;
  }
  | cmds PIPE simplecmd {
    cmds_push_cmd($1, $3);
    $$ = $1;
  }
  ;
simplecmd
  : arg {
    SIMPLECMD *ptr = simplecmd_new();
    simplecmd_push_arg(ptr, $1);
    $$ = ptr;
  }
  | simplecmd arg {
    simplecmd_push_arg($1, $2);
    $$ = $1;
  }
  ;
arg
  : ARG {
    char *ptr = newStr();
    setStr(ptr, yylval.arg);
    // yylval.argを解放する
    free(yylval.arg);
    $$ = ptr;
  }
%%

int yyerror(char const *str) {
    extern char *yytext;
    fprintf(stderr, "parser error\n");
    return 0;
}
