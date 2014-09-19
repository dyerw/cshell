#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void trimstr(char* str);
char** separate_cmds(char* str, int* num_cmds);
