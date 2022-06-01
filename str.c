#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

Str *newStr() {
  Str *s = (Str *) malloc(sizeof(Str));
  s->s = (char *) malloc(1 * sizeof(char));

  s->s[0] = '\0';
  return s;
}

void setStr(Str *s, char *i) {
  int len = strlen(i);
  s->s = realloc(s->s, sizeof(char) * (len + 1));
  strncpy(s->s, i, len);
  s->s[len] = '\0';
}

void addStr(Str *s, char *i) {
  int len = strlen(i);
  s->s = realloc(s->s, sizeof(char) * (strlen(s->s) + len));
  strcat(s->s, i);
}

void freeStr(Str *str) {
  free(str->s);
  free(str);
}
