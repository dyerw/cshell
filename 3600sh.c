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

  //signal(SIGINT, interrupt_handler);
  // Adam: Code for getting the necessary prompt sections
  char hostname[128]; // Need to choose a non-arbitrary number
  char dirbuf[PATH_MAX];   // same thing
  gethostname(hostname, sizeof(hostname));
  getcwd(dirbuf, 128); // non-arbitrary num needed
  
  // Main loop that reads a command and executes it
  while (!feof(stdin)) {         
    // You should issue the prompt here
    // Prints in form of:   [username]@[host]:[directory, full path]>[space] 
    printf("%s@%s:%s> ", getpwuid(getuid())->pw_name, hostname, dirbuf);

    // You should read in the command and execute it here
    char* input = calloc(200, sizeof(char));
    fgets(input, 200, stdin); 
    
    // Trim the spaces
    trimstr(input);
    
    // Break out every command into an array
    char** result = NULL;
    int* size = calloc(1, sizeof(int));
    result = splitstr(input, ";", size);

    for (int i = 0; i < *size; i++) {
      // For each command, split it into arguments
      char** nargv = NULL;
      int* nargc = calloc(1, sizeof(int));
      nargv = splitstr(result[i], " ", nargc);
      
      // Add a null terminator to the list of args
      nargv = realloc(nargv, (*nargc + 1) * sizeof(char*));
      nargv[*nargc] = NULL;

      execute(*nargc, nargv);
    }
  }
  do_exit();
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

/*
 * execute takes a count of args and an array of strings
 * for the args. It forks itself, then transforms the child
 * process into the command to be executed, waits for
 * it to finish and then returns.
 */
void execute(int argc, char* argv[]) {
  
  // If the given command is exit, then exit
  if (strcmp(argv[0], "exit") == 0) { do_exit(); }

  // Handle I/O redirection
  // TODO: break out into a function???
  // FIXME: This is not DRY at all
  FILE* fd = NULL;
  for (int i = 0; i < argc; i++) {
    // Check for input redirection
    if (strcmp(argv[i], "<") == 0) {
      // Open the file following the < symbol
      fd = fopen(argv[i + 1], "r");
      
      // Switch standard in with the file descriptor
      dup2(0, fileno(fd));

      // Delete these elements from the arguments array
      remove_index(argv, i, argc);
      argc--;
      remove_index(argv, i, argc);
      argc--;
      i = 0;
    }
    
    // Check for output redirection
    if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], "2>") == 0) {
      fd = fopen(argv[i + 1], "w"); 

      int stream;
      if (strcmp(argv[i], "2>") == 0) {
        stream = 2;
      }
      else {
        stream = 1;
      }

      dup2(stream, fileno(fd));

      remove_index(argv, i, argc);
      argc--;
      remove_index(argv, i, argc);
      argc--; 
      i = 0;
    }
  }
  pid_t childpid;
  childpid = fork();

  // If we're in the child
  if (childpid == 0) {

    // If the command isn't recognized
    if (execvp(argv[0], argv) == -1) {
      puts("Error: Command not found.");
      exit(1);
    }

  // If we're the parent
  } else {
    //TODO: handle &
    waitpid(childpid, NULL, 0);
  }

  if (fd != NULL) { fclose(fd); }
  return;
}
 
/*
void interrupt_handler(int signum) {
    pid_t childpid;
    if (!(childpid == 0)) {
        printf("  The process has been stopped\n");
        kill(childpid, SIGINT);
    }
}
*/
