/**
 * CS3600, Spring 2013
 * Project 1 Starter Code
 * (c) 2013 Alan Mislove
 *
 * You should use this (very simple) starter code as a basis for 
 * building your shell.  Please see the project handout for more
 * details.
 */

#include "3600sh.h"

#define USE(x) (x) = (x)

int main(int argc, char*argv[]) {
  // Code which sets stdout to be unbuffered
  // This is necessary for testing; do not change these lines
  USE(argc);
  USE(argv);
  setvbuf(stdout, NULL, _IONBF, 0); 
  
  // Main loop that reads a command and executes it
  while (1) {         
    // You should issue the prompt here
      
    // You should read in the command and execute it here
    
    // You should probably remove this; right now, it
    // just exits
    do_exit();
  }

  return 0;
}

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

}

// Function which exits, printing the necessary message
//
void do_exit() {
  printf("So long and thanks for all the fish!\n");

  // Wait for all children to exit, then exit
  while (wait(NULL) > 0) {}
  exit(0);
}
