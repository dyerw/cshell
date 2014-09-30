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

  char hostname[128];
  char dirbuf[PATH_MAX];
  gethostname(hostname, sizeof(hostname));
  getcwd(dirbuf, PATH_MAX);
  
  // Main loop that reads a command and executes it
  while (!feof(stdin)) {         
    // You should issue the prompt here
    // Prints in form of:   [username]@[host]:[directory, full path]>[space] 
    fflush(stdin);
    fflush(stderr);
    fflush(stdout);    
    printf("%s@%s:%s> ", getpwuid(getuid())->pw_name, hostname, dirbuf);

    // You should read in the command and execute it here
    char* input = calloc(200, sizeof(char));
    fgets(input, 200, stdin); 
    
    int err = 0;
    // Escape all the chars that are going to mess w/ the parsing
    if (change_escape_chars(input) == -1) {
      puts("Error: Unrecognized escape sequence.");
      err = 1;
    }

    // Trim the spaces
    trimstr(input);    

    // Make sure unescaped & only found at end of string
    unsigned int k = 0;
    while (input[k] != '\0') {
      // If we find an ampersand and it's not the last char
      if (input[k] == '&' && k != strlen(input) - 1) {
        puts("Error: Invalid syntax.");
        err = 1;
      }
      k++;
    }
    
    if (!err) {
      // Break out every command into an array
      char** result = NULL;
      int* size = calloc(1, sizeof(int));
      result = splitstr(input, ";", size);

      for (int i = 0; i < *size; i++) {
        // For each command, split it into arguments
        int* nargc = calloc(1, sizeof(int));
        char** nargv = splitstr(result[i], " \t", nargc);
      
        // Add a null terminator to the list of args
        nargv = realloc(nargv, (*nargc + 1) * sizeof(char*));
        nargv[*nargc] = NULL;

         execute(*nargc, nargv);
      }
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
  char* syntax_err = "Error: Invalid syntax.";  

  // If the given command is exit, then exit
  if (strcmp(argv[0], "exit") == 0) { do_exit(); }
  if (strcmp(argv[0], "quit") == 0) { do_exit(); } 

  // Check if we're going to run this command in the background
  int background = 0;
  if (strcmp(argv[argc - 1], "&") == 0) {
    background = 1;
    char** tmp;
    tmp = remove_index(argv, argc - 1, argc);
    free(argv);
    argv = tmp;
    argc--;
  }
  
  // Handle I/O redirection
  FILE* fd = NULL;
  int new_stdin = -1;
  int new_stderr = -1;
  int new_stdout = -1;
  
  for (int i = 0; i < argc; i++) {
    // Check for input redirection
    if (strcmp(argv[i], "<") == 0) {

      // If there's no file to redirect, fail
      if (i == argc - 1 || is_redirect(argv[i + 1])) { puts(syntax_err); return; }
      // If the following argument after the file isn't < then fail
      if (i != argc - 2 && (strcmp(argv[i + 2], ">") != 0 && strcmp(argv[i + 2], "2>") != 0)) { puts(syntax_err); return; }

      // Open the file following the < symbol
      fd = fopen(argv[i + 1], "r");
      if (fd == NULL) { puts("Error: Unable to open redirection file."); return; }
      
      // Switch standard in with the file descriptor
      new_stdin = fileno(fd);

      // Delete these elements from the arguments array
      char** newArr;
      newArr = remove_index(argv, i, argc);
      argc--;
      newArr = remove_index(newArr, i, argc);
      argc--;
      free(argv);
      argv = newArr;
      i = 0;
    }
    
    // Check for output redirection
    if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], "2>") == 0) {

      if (i == argc - 1 || is_redirect(argv[i + 1])) { puts(syntax_err); return; }

      if (i != argc - 2 && (strcmp(argv[i + 2], "<") != 0 && strcmp(argv[i + 2], "2>") != 0)) { puts(syntax_err); return; }

      fd = fopen(argv[i + 1], "w"); 

      if (fd == NULL) { puts("Error: Unable to open redirection file."); return; }
      
      if (strcmp(argv[i], "2>") == 0) {
        new_stderr = fileno(fd);
      }
      else {
        new_stdout = fileno(fd);
      }

      char** newArr;
      newArr = remove_index(argv, i, argc);
      argc--;
      newArr = remove_index(newArr, i, argc);
      argc--;
      free(argv);
      argv = newArr;
      i = 0;
    }
  }

  // Substitute the correct escape chars for each argument
  for (int j = 0; j < argc; j++) {
    if (revert_escape_chars(argv[j]) == -1) {
      puts("Error: Unrecognized escape sequence.");
      return;    
    }
  }

  pid_t childpid;
  childpid = fork();

  // If we're in the child
  if (childpid == 0) {
    // Check to see if we need to switch I/O
    if ( new_stdin != -1 ) { dup2(new_stdin, 0); }
    if ( new_stdout != -1 ) { dup2(new_stdout, 1); }
    if ( new_stderr != -1 ) { dup2(new_stderr, 2); }

    // If the command isn't recognized
    if (execvp(argv[0], argv) == -1) {
      puts("Error: Command not found.");
      exit(1);
    }

  // If we're the parent
  } else {
    if (!background) {
      waitpid(childpid, NULL, 0);
    }
  }

  if (fd != NULL) { fclose(fd); }
  return;
}
