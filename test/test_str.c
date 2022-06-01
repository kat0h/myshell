#include <stdio.h>
#include <stdlib.h>
#include "../str.h"

int main(void) {
  Str *s = newStr();
  setStr(s, "hage");
  printf("data: %s\n", s->s);
  addStr(s, " hoge");
  printf("data: %s\n", s->s);
  freeStr(s);
  return 0;
}

