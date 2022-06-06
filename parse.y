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
extern int yylex(void);
extern int yyerror(char const *str);
%}
%union {
  char *arg ;
  ARGS *args;
  CMD  *cmd ;
  CMDS *cmds;
  LINE *line;
}
%token PIPE SEMICOLON CR <arg> ARG
%type <arg>  arg
%type <args> args
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
        ARGS *a = c->cmd[j]->args;
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
    CMDS *cs = malloc(sizeof(CMDS));
    CMD **c = malloc(sizeof(CMD *) * 2);
    cs->size = 1;
    cs->cmd = c;
    cs->cmd[0] = $1;
    cs->cmd[1] = NULL;
    $$ = cs;
  }
  | cmds PIPE cmd {
    $1->size++;
    $1->cmd = realloc($1->cmd, sizeof(CMD *) * ($1->size + 1));
    $1->cmd[$1->size-1] = $3;
    $1->cmd[$1->size] = NULL;
    $$ = $1;
  }
  ;
cmd
  : args {
    CMD *ptr = malloc(sizeof(CMD));
    ptr->args = $1;
    $$ = ptr;
  }
  ;
args
  : arg {
    // ARGSを生成
    ARGS *pa = malloc(sizeof(ARGS));
    char **ps = malloc(sizeof(char *) * 2);
    ps[0] = $1;
    ps[1] = NULL;
    pa->argv = ps;
    pa->argc = 1;
    $$ = pa;
  }
  | args arg {
    $1->argc++;
    $1->argv = realloc($1->argv, sizeof(char *) * ($1->argc + 1));
    $1->argv[$1->argc-1] = $2;
    $1->argv[$1->argc] = NULL;
    $$ = $1;
  }
  ;
arg
  : ARG {
    // 必ずポインタを解放する
    unsigned long len = strlen(yylval.arg);
    char *ptr = malloc(sizeof(char) * (len + 1));
    strncpy(ptr, yylval.arg, len);
    ptr[len] = '\0';
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
