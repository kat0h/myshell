#include <stdio.h>
#include <stdlib.h>
#include "../str.h"

int main(void) {
  char *s = newStr();
  setStr(s, "hage");
  printf("data: %s\n", s);
  addStr(s, " hoge");
  printf("data: %s\n", s);
  freeStr(s);
  return 0;
}

