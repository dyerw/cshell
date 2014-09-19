#include <stdlib.h>
#include <string.h>

/*
 * This function takes a pointer to a string and returns
 * the same pointer with excess spaces removed from the
 * string. Excess spaces being any back to back spaces,
 * as well as leading and trailing spaces.
 * EX:
 *   "a  a" -> "a a"
 *   " abc" -> "abc"
 *   "abc " -> "abc"
 *   "wow this  is   so    cool" -> "wow this is so cool"
 */
void trimstr(char* str) {
  str = str;
}

/* 
 * This function takes a string and returns
 * an array of strings where each new string
 * is a substring and the substrings are divided
 * based on the occurence of ; in the original 
 * string, num_cmds lets the return function 
 * know the length of the returned array
 */
char** separate_cmds(char* str, int* num_cmds) {
  char** result = NULL;  
  *num_cmds = 0;
  
  char* token;
  const char delim[2] = ";";
  token = strtok(str, delim);
  
  // Iterates through the tokens delimited by ';'
  while(token != NULL) {
    (*num_cmds)++;
    result = realloc(result, *num_cmds * sizeof(char*));
    result[*num_cmds - 1] = calloc(strlen(token), sizeof(char));

    strcpy(result[*num_cmds - 1], token);
   
    token = strtok(NULL, delim);
  }
  return result;
}
