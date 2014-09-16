/**
 * S3600, Spring 2013
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
  
  signal(SIGINT, interrupt_handler);
  
  // for printing out parts of the prompt
  char hostname[128];
  char dirbuf[128];
  gethostname(hostname, sizeof(hostname));
  getcwd(dirbuf, 128);
  
  // Main loop that reads a command and executes it
  while (1) {         
    // You should issue the prompt here
    // Format - [username]@[host]:[full dir path]>[space]
    printf("%s@%s:%s> ", getlogin(), hostname, dirbuf);
    // You should read in the command and execute it here
    
    // You should probably remove this; right now, it
    // just exits
    do_exit();
  }

  return 0;
}

void interrupt_handler(int signum) {
    pid_t childpid;
    if (!(childpid == 0) {
        printf("  The process has been stopped\n");
        kill(childpid, SIGINT);
    }
}

static void execute(int argc, char* argv[]) {
    pid_t childpid;
    
    childpid = fork();
    if (childpid == 0) {
        
        // will be needing to modify these error messages (and possibly conditions)
        if (execvp(argv[0], argv) == -1) {
            perror("execvp");
            printf("     (couldn't find command)\n");
        }
        exit(1);
    } else {
        waitpid(childpid, NULL, 0);
    return;
}

// Function which exits, printing the necessary message
//
void do_exit() {
  printf("So long and thanks for all the fish!\n");

  // Wait for all children to exit, then exit
  while (wait(NULL) > 0) {}
  exit(0);
}

