#include <stdio.h>
#include <unistd.h>

#include <err.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

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

  pid_t pid = fork();

  if (pid == -1) {
    err(EXIT_FAILURE, "fork failed");
  }

  if (pid == 0) {
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
  } else {
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
  }



  return EXIT_SUCCESS;
}
