#include "parsing.h"

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
  char* tmp = calloc(strlen(str), sizeof(char));  // allocate space for a temp string
  int prev_space = 1; // 1 if is a space, 0 if not. Set to 1 by default to get rid of leading spaces
  int i = 0; // counter for the inputted string
  int j = 0; // counter for the corrected copy
  int lastchar = strlen(str) - 1;  // counter for the last non-space char

  // decrement counter for last non-space char
  while (lastchar > 0) {
    if (isspace(str[lastchar])) {
      lastchar--;
    } else {
      break;
    }
  }

  while (str[i] != '\0' && i < lastchar + 1) {
    if (isspace(str[i])) {
        if (prev_space) {  // if the previous slot was a space
          i++;             // just increment str's counter
        } else {
          tmp[j] = str[i]; // copy it over
          prev_space = 1;  // let the next slot know the previous was a space
          i++;
          j++;
        } 
    } else { // if this slot is a alphanumeric character
      tmp[j] = str[i]; // copy value over
      prev_space = 0;  // let next slot know this is not a space
      j++;
      i++;
    }
  }

  tmp[j+1] = '\0'; // set null byte to the end of the string
  strcpy(str, tmp); // copy the corrected string back to the input
  free(tmp);  // free the tmp var
}

/*
 * This function takes a string, a pointer to an int, and
 * a char for a delimeter. It splits the given string into
 * an array of strings based on the given delimiter and 
 * changes the int to represent the number of strings in
 * the new array.
 *
 * Note that the given delim can have multiple delims. 
 * Each char supplied is a delim.
 * For example, given " \n\t", 
 *    this function will split "this is\ta\n sentence" into:
 *    "this" "is" "a" "sentence".
 */
char** splitstr(char* str, const char* delim, int* count) {
  char** result = NULL;  
  *count = 0;
  
  char* token;
  token = strtok(str, delim);
  
  // Iterates through the tokens delimited by ';'
  while(token != NULL) {
    (*count)++;

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
    result = realloc(result, *count * sizeof(char*));
    result[*count - 1] = calloc(strlen(token), sizeof(char));

    strcpy(result[*count - 1], token);
   
    // Move forward to the next token
    token = strtok(NULL, delim);
  }
  return result;
}

// Returns a copy of the array passed in, but without the
// specified index
char** remove_index(char** arr, int index, int size) {
  char** new_array = calloc(size, sizeof(char*));
  for (int i = 0; i < size; i++) {
    if (i != index) {
      if (i > index) { new_array[i - 1] = arr[i]; }
      else { new_array[i] = arr[i]; }
    }
  }
  // add a null terminator so our command can be read correctly
  new_array[size - 1] = NULL;
  return new_array;
}

/* 
 * This function takes a string and mutates it in place such that
 * all occurences of \{space} \& and \\ are replaced with \s 
 * \a and \b. The point of this being that we can then pass this
 * input to our parsing functions and have them exhibit correct
 * behavior for escape chars.
 *
 * e.g. for the input: cat foo\ bar
 * we would get the args [cat, foo\, bar]
 * but the input: cat foo\sbar
 * would correctly get the args [cat, foo\sbar]
 * which we can then replace with a space once all parsing has occurred.
 *
 * However, \a \s and \b are not actually valid escape chars so we need
 * to make sure to throw errors if we encounter them here, since our 
 * replacement function won't know the difference.
 */
int change_escape_chars(char* str) {
  int i = 0;
  while(str[i] != '\0') {
    if (str[i] == '\\') {
      if (str[i + 1] == ' ') {
        str[i + 1] = 's';
      }
      else if (str[i + 1] == '&') {
        str[i + 1] = 'a';
      }
      else if (str[i + 1] == '\\') {
        str[i + 1] = 'b';
      }

      // Return -1 for invalid chars
      else if (str[i + 1] == 'b' || str[i + 1] == 'a' || str[i + 1] == 's') {
        return -1; 
      }
    }
    i++;
  }
  return 0;
}

/* 
 * This function takes a string and mutates it in place such that
 * all occurences of \{space} \& and \\ are replaced with \s 
 * \a and \b. The point of this being that we can then pass this
 * input to our parsing functions and have them exhibit correct
 * behavior for escape chars.
 *
 * e.g. for the input: cat foo\ bar
 * we would get the args [cat, foo\, bar]
 * but the input: cat foo\sbar
 * would correctly get the args [cat, foo\sbar]
 * which we can then replace with a space once all parsing has occurred.
 *
 * However, \a \s and \b are not actually valid escape chars so we need
 * to make sure to throw errors if we encounter them here, since our 
 * replacement function won't know the difference.
 */
int revert_escape_chars(char* str) {
  int i = 0;
  while(str[i] != '\0') {
    if (str[i] == '\\') {
      if (str[i + 1] == 's') {
        str[i + 1] = ' ';
      }
      else if (str[i + 1] == 'a') {
        str[i + 1] = '&';
      }
      else if (str[i + 1] == 'b') {
        str[i + 1] = '\\';
      }

      // Return -1 for invalid chars
      else if (str[i + 1] == '\\' || str[i + 1] == '&' || str[i + 1] == ' ') {
        return -1; 
      }
    }
    i++;
  }
  return 0;
}
