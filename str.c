/*
 * str.c 2022@kotakato
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

char *newStr() {
  char *s = malloc(1024 * sizeof(char));

  s[0] = '\0';
  return s;
}

char *setStr(char *s, char *i) {
  int len = strlen(i);
  char *ptr = realloc(s, sizeof(char) * (len + 1));
  strncpy(ptr, i, len);
  ptr[len] = '\0';
  return ptr;
}

char *addStr(char *s, char *i) {
  char *ptr = realloc(s, sizeof(char) * (strlen(i) + strlen(s) + 1));
  strcat(ptr, i);
  ptr[strlen(i) + strlen(s)] = '\0';
  return ptr;
}

