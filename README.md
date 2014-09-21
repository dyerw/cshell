cshell
======

a shell, written for cs3600


TODO
====
* ~~trimstr(Adam)~~
* ~~Parsing(Liam~~
  * ~~break input lines on semi-colons into an array~~
  * ~~break commands on spaces for args~~
* ~~display prompt correctly, read from prompt~~
* ~~fork and execute processes~~
* background processes
* I/O redirection
* Pass the Milestone tests


CS3600 C 
==============

* The Make File
  * To run the shell, run 'make'
  * To run the unit tests on the shell, run 'make utest'
  * To run the given tests, run 'make test'
  * To remove any executables, run 'make cleanall'
* What the shell supports
  * The shell supports commands found in PATH, I/O redirection, and background process
  * Any number of arguments or any length may be supplied
  * The escape characters '\ ', '\t', '\\', '\&'
  * To give multiple commands in one line, place an semi-colon after each command. Otherwise, an error will be thrown
  * Although unadvised, you may place extra spaces through the given command(s). They will simply be removed.
  * By default, commands will be run in the foreground. In order to change this for a particular command, place an ampersand(&) at the end of the command (before any semi-colons as well
  * In order to exit the shell, simply type 'exit' and hit enter
  * This shell support interrupts, and so should return to 3600sh when pressing Ctrl+C
  
