#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minunit.h"
#include "parsing.h"

int tests_run = 0;

// Example test
int foo = 7;
static char* test_foo() {
  mu_assert("error, foo != 7", foo == 7);
  return 0;
}

static char* test_trimstr() {
  // Tests that a string with no spaces is not 
  // modified
  char* str1 = "cool";
  char* str1cpy = "cool";
  trimstr(str1);
  mu_assert("ERROR: trimstr(\"cool\") != \"cool\"", 
            strcmp(str1, str1cpy) == 0);

  return 0;
}

static char* test_separate_cmds() {
  char* input = NULL;
  int* n = calloc(1, sizeof(n));
  char** result;

  // Tests that a command with no ; is 
  // returned as a singal element in an
  // array
  input = calloc(strlen("ls -al"), sizeof(char));
  strcpy(input, "ls -al");

  result = separate_cmds(input, n);

  mu_assert("ERROR: cmd w/ no ; is not returned as the same string",
            strcmp(result[0], input) == 0);
  mu_assert("ERROR: cmd w/ no ; is not of length 1",
            (*n == 1));
  free(n);
  free(result);
  free(input);

  // Tests that a command with a single ;
  // is broken into two commands
  n = calloc(1, sizeof(int));
  input = calloc(strlen("ls -al; cat foo.txt"), sizeof(char));
  strcpy(input, "ls -al; cat foo.txt");

  result = separate_cmds(input, n);

  mu_assert("ERROR: separate_cmds(\"ls -al; cat foot.txt\")[0]",
            strcmp(result[0], "ls -al") == 0);
  mu_assert("ERROR: separate_cmds(\"ls -al; cat foot.txt\")[1]",
            strcmp(result[1], "cat foo.txt") == 0);
  mu_assert("ERROR: \"ls -al; cat foo.txt\" length != 2",
            (*n == 2));
  free(n);
  free(result);
  free(input);

  // Tests that a command with a ; at the end
  // doesn't affect the result
  n = calloc(1, sizeof(int));
  input = calloc(strlen("ls -al;"), sizeof(int));
  strcpy(input, "ls -al;");

  result = separate_cmds(input, n);

  mu_assert("ERROR: separate_cmds ls -al; != ls -al",
            (strcmp(result[0], "ls -al") == 0));

  return 0;
}

static char* all_tests() {
  mu_run_test(test_foo);
  mu_run_test(test_trimstr);
  mu_run_test(test_separate_cmds);
  return 0;
}

int main(int argc, char** argv) {
  char* result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  }
  else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
