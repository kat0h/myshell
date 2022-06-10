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
extern int yylex(void);
extern int yyerror(char const *str);
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

lines
  : l
  | lines l
  ;
l
  : line CR {
    // preview nodes
    LINE *l = $1;
    // LINE
    puts("{");
    for (int i=0; i<(l->size); i++) {
      // CMDS
      CMDS *c = l->cmds[i];
      printf(" {\n  ");
      for (int j=0; j<(c->size); j++) {
        CMD *a = c->cmd[j];
        // 一つのコマンド
        printf("{");
        for (int k=0; k<(a->argc); k++) {
          printf(" '%s'", a->argv[k]);
        }
        printf(" } ");
        if (j+1<c->size)
          printf("'|' ");
      }
      puts("\n }");
    }
    puts("}");
  }
  | CR
  ;
line
  : cmds {
    LINE *ptr = malloc(sizeof(LINE));
    CMDS **p  = malloc(sizeof(CMD *) * 2);
    ptr->size = 1;
    ptr->cmds = p;
    ptr->cmds[0] = $1;
    ptr->cmds[1] = NULL;
    $$ = ptr;
  }
  | line SEMICOLON cmds {
    $1->size++;
    $1->cmds = realloc($1->cmds, sizeof(CMDS *) * ($1->size + 1));
    $1->cmds[$1->size-1] = $3;
    $1->cmds[$1->size] = NULL;
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
    fprintf(stderr, "parser error near %s\n", yytext);
    return 0;
}

int main(void) {
    extern int yyparse(void);
    extern FILE *yyin;

    yyin = stdin;
    if (yyparse()) {
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }
}
