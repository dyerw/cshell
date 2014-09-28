#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>

void trimstr(char* str);
char** splitstr(char* str, const char* delim, int* count);
char** remove_index(char** arr, int index, int size);
int change_escape_chars(char* str);
int revert_escape_chars(char* str);
