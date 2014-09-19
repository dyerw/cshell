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
  char* tmp = (char*) calloc(strlen(str), sizeof(char));
  int prev_space = 1; // 1 if is a space, 0 if not
  int i = 0;
  int j = 0;
  while (str[i] != '\0') {
    if (isspace(str[i])) {
				if (prev_space) {
					i++;
				} else {
					tmp[j] = str[i];
					prev_space = 1;
					i++;
					j++;
				} 
    } else {
			tmp[j] = str[i];
			prev_space = 0;
			j++;
			i++;
		}
	}
  tmp[j+1] = '\0';
  strcpy(str, tmp);
  free(tmp);
}

/*
 * Return the size of the given array of strings.
 * i.e. 
 *   char** arry = {"1", "2", "3"}
 *   array_size(arry) = 3
 */
int array_size(char** strings) {
   int i;
   while (strings[i] != NULL) {
     i++;
   }
   return i;
}
