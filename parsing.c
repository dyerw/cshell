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
  int i, begin, end;
  begin = 0;			// The starting index of the inital string
  end = strlen(str) - 1;	// The ending index of the initial string

  // Change the starting pointer if there's whitespace at the start
  // WORKS
  while (isspace(*str)) {
    *(str++);
  }

  //------ METHOD 1 FOR REMOVING EXCESS SPACE IN MIDDLE OF STRING-------
  /* TODO: Not Working
  // For removing excess spaces in the middle of a word
  while (i < strlen(str)) {

    // if the char at current position and char at next position are spaces
    if (isspace(str[i]) && isspace(str[i+1])) {
      // Loop through and shift all values left
      for (i = i; i < (strlen(str)-1); i++) {
	str[i] = str[i+1];
      }
    }

    i++;
  }
  */
  //-------- END METHOD 1 MIDDLE EXCESS ---------
  

  // --------METHOD 1 FOR REMOVING TRAILING SPACES-----
  /*
  while ((end >= begin) && isspace(str[end])) {
    end--;
  }
  

  end = end - begin;
  i = begin;
  while (i < end+1) {
    str[i-begin] = str[i];
    i++;
  }
  str[end+1] = '\0';
  */
  // --------------END METHOD 1 TRAILING----------

  //Mehtod 1.5 for Removing Traling
  int n = strlen(str)-1;
  while(isspace(str[n]) && n > 0) {
    *(str + n) = 'Q';
    n--;
  }



  // ---------METHOD 2 FOR REMOVING TRAILING SPACES-------
  /*
  int n;
  for (n = strlen(str)-1; n > 0; n--) {
    if (!(isspace(str[n]))) {
      if (str[n+1] != '\0') {
        *(str + n + 1) = '\0';
        break;
      }
    }
  }
  */
  // ------------END METHOD 2 TRAILING---------------------


  // --------METHOD 3 FOR REMOVING TRAILING SPACES--------
  /*
  char* end = str;

  // Get a pointer to the end of the string, or to an instance of a comment
  while (*end != '\0' && *end != '#') {
    end++;
  }

  // Set the end pointer to the last non-space value
  if (isspace(*(end-1)) > 0) {
    while (isspace(*(end-1)) > 0) {
      end--;
    }

     Put in a terminating string at the end
    *end = '\0';  // Segfaulting here
  }
  */
  // ------------END METHOD 3 TRAILING ------------


  /* For the sake of debugging,
   * this will print out what the result turns out to be
   * but with "END" at the end so as to see if trailing spaces remain
   */  
  printf("Result: %sEND\n", str);
}


// Alternative method I found online that is supposed to handle it, but doesn't work
void trimstr2(char* str) {
  /*unsigned int i,x;
  for(i=x=1; str[i]; ++i) {
    if(!isspace(str[i]) || (i>0 && !isspace(str[i-1]))) {
      str[x++] = str[i];
    }
  }
  str[x] = '\0'; */
  int count = 0;
  for (unsigned int i=0; i < strlen(str); i++) {
    if (!(isspace(str[i]))) {
      str[i+1] = str[i];
      count = 0;
    } else if (isspace(str[i]) && count == 0) {
      str[i+1] = str[i];
      count = 1;
    }
  }
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
