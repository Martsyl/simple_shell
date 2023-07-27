#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
char *strn_cpy(char *str, char *qstr, int b);
int _putchar(char c);
void _puts(char *str);
char *str_cat(char *str, char *cat);
char *mem_cpy(char *str, char *mem, unsigned int b);
char *str_cpy(char *str, char *cpy);
char *str_dup(char *str);
char *str_cat(char *str, char *cat);
void free_line(char **line);
void exec_cmmd(char **inp, char *buff);
char *get_env(const char *inp);
char *get_cmd(char *cmmd);
extern char **environ;
int _putchar(char c);
void _puts(char *str);
size_t strlen(const char *str);

#endif
