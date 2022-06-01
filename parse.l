%{
#include <stdio.h>
#define STR_LIT 1
extern void yy_input(char*, int*, int);
#define yy_input(buf, count, max) yy_input(buf, &count, max)
// TODO: "ls" "."を解釈できるようにする
%}

%start STR_LIT

%%

<INITIAL>[ \n\t];
<INITIAL>\" {
  BEGIN STR_LIT;
}
<INITIAL>[^ \n\t]* {
  return STR_LIT;
};

<INITIAL>. ;

<STR_LIT>[^\"]* {
  return STR_LIT;
}
<STR_LIT>\" {
  BEGIN INITIAL;
}


%%

int yywrap(void) {
  return 1;
}
