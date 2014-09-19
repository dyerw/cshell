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
  char* tmp = (char*) calloc(strlen(str), sizeof(char));  // allocate space for a temp string
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
					i++;						 // just increment str's counter
				} else {
					tmp[j] = str[i]; // copy it over
					prev_space = 1;	 // let the next slot know the previous was a space
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
