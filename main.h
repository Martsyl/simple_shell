#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
extern char **environ;
int handle_inp(char **buff, char *args[]);
int _putchar(char c);
void _puts(char *str);
#endif
