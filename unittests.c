#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "parsing.h"

int tests_run = 0;

char* str_actual = "cool beans";
char* str1 = "cool beans";
char* str_leading = "  cool beans";
char* str_trailing = "cool beans  ";
char* str_excess = "cool  beans";
char* str_combo = "  cool      beans    ";
static char* test_trimstr() {
  // test a correctly formatted string
  char* input0 = (char*) calloc(strlen(str1), sizeof(char));
  strcpy(input0, str1);
  trimstr(input0);
  mu_assert("ERROR: Leading white space exists",
	    strcmp(str_actual, input0) == 0);
  free(input0);
  tests_run++; 

  // test leading spaces
  char* input1 = (char*) calloc(strlen(str_leading), sizeof(char));
  strcpy(input1, str_leading);
  trimstr(input1);
  mu_assert("ERROR: Leading white space exists",
	    strcmp(str_actual, input1) == 0);
  free(input1);
  tests_run++;
  
  // test excess internal spaces
  char* input2 = (char*) calloc(strlen(str_excess), sizeof(char));
  strcpy(input2, str_excess);
  trimstr(input2);
  mu_assert("ERROR: excess white space exists between words", 
            strcmp(str_actual, input2) == 0);
  free(input2);
  tests_run++;
 
  // test trailing spaces
  char* input3 = (char*) calloc(strlen(str_trailing), sizeof(char));
  strcpy(input3, str_trailing);
  trimstr(input3);
  mu_assert("ERROR: Trailing whitespace exists", 
            strcmp(str_actual, input3) == 0);
  free(input3);
  tests_run++;
  
  // test a combination of extra spaces
  char* input4 = (char*) calloc(strlen(str_combo), sizeof(char));
  strcpy(input4, str_combo);
  trimstr(input4);
  mu_assert("ERROR: excess white space exists", 
            strcmp(str_actual, input4) == 0);
  free(input4);
  tests_run++;
  
  return 0;
}

static char* all_tests() {
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
