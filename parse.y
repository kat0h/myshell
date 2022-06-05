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
extern int yylex(void);
extern int yyerror(char const *str);

// コマンド単体
// char*の配列
typedef struct {
  char **arg;
} ARGS;

// 一つのコマンド (リダイレクトなどは此方)
typedef struct {
  ARGS args;
} CMD;

// 現状pipeで繋がれたコマンド
// CMDの配列
typedef struct {
  CMD **cmd;
} CMDS;

// 現状;で繋がれたコマンド
typedef struct {
  CMDS **cmds;
} LINE;

%}
%union {
  char* arg;
}
%token <arg> ARG
%token PIPE SEMICOLON CR
%type <arg> arg
%%
lines
  : line
  | line lines
  ;
line
  : cmds CR {
  }
  | cmds SEMICOLON line CR {
  }
  | CR
  ;
cmds
  : cmd {
  }
  | cmd PIPE cmds {
  }
  ;
cmd
  : args {
  }
  ;
args
  : arg {
  }
  | arg args {
  }
  ;
arg
  : ARG {
    $$ = yylval.arg;
    printf("%s\n", yylval.arg);
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
