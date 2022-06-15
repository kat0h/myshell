/*
 * str.c 2022@kotakato
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

char *newStr() {
  char *s = malloc(1 * sizeof(char));

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
  // メモリ領域の拡張
  int len = strlen(i);
  s = realloc(s, sizeof(char) * (strlen(s) + len));
  // コピー用領領域を確保
  char* c = newStr();
  setStr(c, i);
  // コピー
  strcat(s, c);
  // コピー用領領域を解放
  free(c);
}

void freeStr(char *s) {
  free(s);
}
