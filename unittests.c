#include <stdio.h>
#include "minunit.h"
#include "parsing.h"

int tests_run = 0;

// Example test
int foo = 7;
static char* test_foo() {
  mu_assert("error, foo != 7", foo == 7);
  return 0;
}

char* str_actual = "cool beans";
char* str1 = "cool beans";
char* str_leading = "  cool beans";
char* str_trailing = "cool beans  ";
char* str_excess = "cool  beans";
char* str_combo = "  cool      beans    ";
static char* test_trimstr() {
  //trimstr2(str1);  // Tests a correctly-formatted string
  trimstr(str_leading);  // Trims a string with leading whtie space
  trimstr(str_trailing); // Trims a string with trailing white space
  //trimstr2(str_excess);   // Trims a string with excess middle white space
  //trimstr2(str_combo);    // Trims a string with a mix of all three
  //mu_assert("ERROR: the string was modified from its correct form", 
  //          strcmp(str_actual, str1) == 0);
  mu_assert("ERROR: Leading white space exists",
	    strcmp(str_actual, str_leading) == 0);
  printf("Test Leading: %sEND\n", str_leading);
  mu_assert("ERROR: trailing white space exists", 
            strcmp(str_actual, str_trailing) == 0);
  printf("Test Trailing: %sEND\n", str_trailing);
  //mu_assert("ERROR: excess white space exists between words", 
  //          strcmp(str_actual, str_excess) == 0);
  //printf("Test Excess: %sEND\n", str_excess);
  //mu_assert("ERROR: the combo string was not trimmed", 
  //          strcmp(str_actual, str_combo) == 0);
  
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
