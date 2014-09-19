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
#include "parsing.h"

#define USE(x) (x) = (x)

int main(int argc, char*argv[]) {
  // Code which sets stdout to be unbuffered
  // This is necessary for testing; do not change these lines
  USE(argc);
  USE(argv);
  setvbuf(stdout, NULL, _IONBF, 0); 

  // Adam: Code for getting the necessary prompt sections
  char hostname[128] // Need to choose a non-arbitrary number
  char dirbuf[128]   // same thing
  gethostname(hostname, sizeof(hostname));
  getcwd(dirbuf, 128); // non-arbitrary num needed
  
  // Main loop that reads a command and executes it
  while (1) {         
    // You should issue the prompt here
    // Prints in form of:   [username]@[host]:[directory, full path]>[space] 
    printf("%s@%s:%s> ", getlogin(), hostname, dirbuf);

    // You should read in the command and execute it here
    //TODO: something to read in input
    
    //TODO: execute
    
    // You should probably remove this; right now, it
    // just exits
    do_exit();
  }

  return 0;
}

// Function which exits, printing the necessary message
//
void do_exit() {
  printf("So long and thanks for all the fish!\n");

  // Wait for all children to exit, then exit
  while (wait(NULL) > 0) {}
  exit(0);
}

/* Currently just some pseudo-code */
void execute(int argc, char* argv[]) {
  
	// If the given command is exit, then exit
	if (strcmp(argv[0], "exit")) {
     do_exit();

	// Otherwise, execute the code
  } else {
    pid_t childpid;
    childpid = fork();

		// If we're in the child
		if (childpid == 0) {

			// If the command isn't recognized
			if (execvp(argv[0], argv) == -1) {
				perror("execvp: Couldn't find the specified command\n");
			}
			exit(1);

			// Handle & here?

		// If we're the parent
   	} else {
			waitpid(childpid, NULL, 0);
		}
		return;
  }
}
