#ifndef STR_H
#define STR_H
#include <stdio.h>
#include <stdlib.h>


typedef struct {
  char *s;
} Str;

Str *newStr();
void setStr(Str *s, char *i);
void addStr(Str *s, char *i);
void freeStr(Str *str);

#endif
