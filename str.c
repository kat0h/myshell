/*
 * Utility library
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

char *newStr() {
  char *s = (char *) malloc(sizeof(char *));
  s = (char *) malloc(1 * sizeof(char));

  s[0] = '\0';
  return s;
}

void setStr(char *s, char *i) {
  int len = strlen(i);
  s = realloc(s, sizeof(char) * (len + 1));
  strncpy(s, i, len);
  s[len] = '\0';
}

void addStr(char *s, char *i) {
  int len = strlen(i);
  s = realloc(s, sizeof(char) * (strlen(s) + len));
  strcat(s, i);
}

void freeStr(char *s) {
  free(s);
}
