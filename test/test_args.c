#include <stdio.h>
#include <stdlib.h>
#include "../parser.h"

int fail, success;
void assert_equal(int want, int got) {
  if (want == got) {
    printf("OK: want %d, got %d\n", want, got);
    success++;
  } else {
    printf("NG: want %d, got %d\n", want, got);
    fail++;
  }
}

void test_new_free() {
  Args *args = Args_new();

  Args_parse(args, "test hello world");
  printf("input: %s\n", "test hello world");
  printf("argc: %d\n", args->argc);
  printf("argv: [");
  for (int i=0; i < args->argc; i++)
    printf("\"%s\", ", args->argv[i]);
  printf("]\n");

  if (!(args->argv[args->argc] == NULL)) {
    fail++;
  }
  Args_free(args);
}

int main() {
  test_new_free();

  if (fail != 0) {
    printf("FAILED: %d/%d tests failed\n", fail, fail + success);
    return EXIT_FAILURE;
  }
  printf("PASSED: All tests finished succesfully\n");
  return EXIT_SUCCESS;
}
