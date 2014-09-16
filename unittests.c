#include <stdio.h>
#include "minunit.h"
#include "3600sh.h" 

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

static char* all_tests() {
  mu_run_test(test_foo);
  mu_run_test(test_trimstr);
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
