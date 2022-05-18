#include <stdio.h>

int main(int argc, char *argv[]) {
  char line[1000];
  fgets(line, sizeof(line), stdin);
  printf("%s", line);
  return 0;
}
