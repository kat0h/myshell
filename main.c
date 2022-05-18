#include <stdio.h>

void prompt() {
  printf("$ ");
}

void read_line(char* line, int size) {
  fgets(line, size, stdin);
}

int main(int argc, char *argv[]) {
  prompt();

  char line[1000];
  read_line(line, sizeof(line));

  int c = 0;
  while(line[c] != '\0') {
    char chr = line[c];
    if (chr == ' ') {
      printf("\n");
    } else {
      printf("%c", chr);
    }
    c++;
  }

  return 0;
}
