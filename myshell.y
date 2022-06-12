/*
  TODO:
    <args> ::= <arg> | <arg> <args>
    <cmd>  ::= <args>
    <cmds> ::= <cmd> | <cmd> '|' <cmds>
    <line> ::= <cmds> | <cmds> ';' <line>
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
LINE *line_tree;

%}
%union {
  char *arg ;
  CMD  *cmd ;
  CMDS *cmds;
  LINE *line;
}
%token PIPE SEMICOLON CR <arg> ARG
%type <arg>  arg
%type <cmd>  cmd
%type <cmds> cmds
%type <line> line
%%

l
  : line CR {
    // ポインタはparser.cで解放されます
    line_pp($1);
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
  : cmd {
    CMDS *ptr = cmds_new();
    cmds_push_cmd(ptr, $1);
    $$ = ptr;
  }
  | cmds PIPE cmd {
    cmds_push_cmd($1, $3);
    $$ = $1;
  }
  ;
cmd
  : arg {
    CMD *ptr = cmd_new();
    cmd_push_arg(ptr, $1);
    $$ = ptr;
  }
  | cmd arg {
    cmd_push_arg($1, $2);
    $$ = $1;
  }
  ;
arg
  : ARG {
    char *ptr = newStr();
    setStr(ptr, yylval.arg);
    $$ = ptr;
  }
%%

int yyerror(char const *str) {
    extern char *yytext;
    fprintf(stderr, "parser error\n");
    return 0;
}
