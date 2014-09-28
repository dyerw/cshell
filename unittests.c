#include <stdio.h>
#include <string.h>
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

///////////////////
// TRIMSTR TESTS //
///////////////////
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

///////////////////
// SPLITSTR TEST //
///////////////////
static char* test_splitstr() {
  char* input = NULL;
  int* n = calloc(1, sizeof(n));
  char** result;

  // Tests that a command with no ; is 
  // returned as a singal element in an
  // array
  input = calloc(strlen("ls -al"), sizeof(char));
  strcpy(input, "ls -al");

  result = splitstr(input, ";", n);

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

  result = splitstr(input, ";", n);

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

  result = splitstr(input, ";", n);

  mu_assert("ERROR: separate_cmds ls -al; != ls -al",
            (strcmp(result[0], "ls -al") == 0));

  return 0;
}

//////////////////
// REMOVE_INDEX //
//////////////////
static char* test_remove_index() {
// takes an array of strings, and index, and an array size
// returns void
  char* strA = calloc(2, sizeof(char));
  strcpy(strA, "ls");
  char* strB = calloc(2, sizeof(char));
  strcpy(strB, "-a");
  char* strC = calloc(1, sizeof(char));
  strcpy(strC, "<");
  char* strD = calloc(8, sizeof(char));
  strcpy(strD, "test.txt");

  char** strArray = calloc(4, sizeof(char*)); 
  strArray[0] = strA;
  strArray[1] = strB;
  strArray[2] = strC;
  strArray[3] = strD;
  for(int i = 0; i < 4; i++) {
    printf("Pre-removal Element %d: %s\n", i, strArray[i]);
  }

  char** newArray;
  newArray = remove_index(strArray, 2, 4);
  free(strArray);
  strArray = newArray;
 
  newArray = remove_index(strArray, 2, 3);
  free(strArray);
  strArray = newArray;
  for(int j = 0; j < 3; j++) {
    printf("Post-removal Element %d: %s\n", j, strArray[j]);
  }
  mu_assert("ERROR: failed to remove item at index 2\n", strArray[2] == NULL);
  
  return 0;

}

/////////////////////////
// change_escape_chars //
/////////////////////////
static char* test_change_escape_chars() {
  char* strA = calloc(5, sizeof(char));
  strcpy(strA, "ls\\&");
  char* strB = calloc(5, sizeof(char));
  strcpy(strB, "ls\\ ");
  char* strC = calloc(5, sizeof(char));
  strcpy(strC, "ls\\\\");
  char* strD = calloc(5, sizeof(char));
  strcpy(strD, "ls\\t");
  char* strE = calloc(5, sizeof(char));
  strcpy(strE, "ls\\a");


  change_escape_chars(strA);
  change_escape_chars(strB);
  change_escape_chars(strC);
  change_escape_chars(strD);
  change_escape_chars(strE);

  mu_assert("ERROR: failed to change escape char for &\n", strcmp(strA, "ls\\a") == 0);
  mu_assert("ERROR: failed to change escape char for space\n", strcmp(strB, "ls\\s") == 0);
  mu_assert("ERROR: failed to change escape char for \\\n", strcmp(strC, "ls\\b") == 0);
  mu_assert("ERROR: failed to change escape char for \\t\n", strcmp(strD, "ls\\t") == 0);
  //mu_assert("ERROR: failed to change escape char for \&\n", strcmp(strE, "ls\\a") == 0);

  free(strA);
  free(strB);
  free(strC);
  free(strD);
  free(strE);

  return 0;
}

/////////////////////////
// revert_escape_chars //
/////////////////////////
static char* test_revert_escape_chars() {
  char* strA = calloc(5, sizeof(char));
  strcpy(strA, "ls\\a");
  char* strB = calloc(5, sizeof(char));
  strcpy(strB, "ls\\s");
  char* strC = calloc(5, sizeof(char));
  strcpy(strC, "ls\\b");
  char* strD = calloc(5, sizeof(char));
  strcpy(strD, "ls\\t");
  char* strE = calloc(9, sizeof(char));
  strcpy(strE, "ls\\a\\s\\t");

  revert_escape_chars(strA);
  revert_escape_chars(strB);
  revert_escape_chars(strC);
  revert_escape_chars(strD);
  revert_escape_chars(strE);

  printf("Actual, ampersand: \"%s\".   Expected: \"ls&\"\n", strA);
  printf("Actual, space: \"%s\".   Expected: \"ls \"\n", strB);
  printf("Actual, backslash: \"%s\".   Expected: \"ls\\\"\n", strC);
  printf("Actual, tab: \"%s\".   Expected: \"ls\t\"\n", strD);
  printf("Actual, combo: \"%s\".   Expected: \"ls& \t\"\n", strE);
  
  mu_assert("ERROR: failed to revert escape char for &\n", strcmp(strA, "ls&") == 0);
  mu_assert("ERROR: failed to revert escape char for space\n", strcmp(strB, "ls ") == 0);
  mu_assert("ERROR: failed to revert escape char for \\\n", strcmp(strC, "ls\\") == 0);
  mu_assert("ERROR: failed to revert escape char for \\t\n", strcmp(strD, "ls\t") == 0);
  mu_assert("ERROR: failed to revert escape chars for \\a\\s\\t\n", strcmp(strE, "ls& \t") == 0);

  free(strA);
  free(strB);
  free(strC);
  free(strD);
  free(strE);

  return 0;
}

// Runs all our test functions
static char* all_tests() {
  mu_run_test(test_trimstr);
  mu_run_test(test_splitstr);
  mu_run_test(test_remove_index);
  mu_run_test(test_change_escape_chars);
  mu_run_test(test_revert_escape_chars);
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
