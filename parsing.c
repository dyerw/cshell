#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

    // Make sure the token doesn't have a space before or after
    // if it does, delete them
    if (isspace(token[0])) {
      //TODO: maybe break this out into a function and test it??
      memmove(&token[0], &token[1], strlen(token)); 
    }
    else if (isspace(token[strlen(token) - 1])) {
      memmove(&token[strlen(token) - 1], &token[strlen(token)], 1);
    }

    // Store this token in the next available index in our 
    // result array
    result = realloc(result, *num_cmds * sizeof(char*));
    result[*num_cmds - 1] = calloc(strlen(token), sizeof(char));

    strcpy(result[*num_cmds - 1], token);
   
    // Move forward to the next token
    token = strtok(NULL, delim);
  }
  return result;
}
