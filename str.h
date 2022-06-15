/*
 * str.h 2022@kotakato
 */

#ifndef STR_H
#define STR_H
#include <stdio.h>
#include <stdlib.h>


char *newStr();
void setStr(char *s, char *i);
void addStr(char *s, char *i);
void freeStr(char *str);

#endif
