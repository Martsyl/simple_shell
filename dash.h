#ifndef DASH_H
#define DASH_H

/* header files */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

/* Global variable */
extern char **environ;

/* Macros */
#define PUT(c) (write(STDOUT_FILENO, c, _strlen(c)))
#define SETOWD(V) (V = _strdup(_getenv("OLDPWD")))
#define BUFSIZE 1024
#define TOKENSIZE 64
#define PROMPT "(^^) "
#define PASS (1)
#define CRASH (-1)
#define OK (0)

/* Struct */

/**
 * struct dash_data - Global data structure
 * @line: the line input
 * @args: the arguments token
 * @error_msg: the global path
 * @cmd: the parsed command
 * @index: the command index
 * @oldpwd: the old path visited
 * @env: the environnment
 *
 */
typedef struct dash_data
{
	char *line;
	char **args;
	char *cmd;
	char *error_msg;
	char *oldpwd;
	unsigned long int index;
	char *env;
} das_h;

/**
 * struct inbuilt - Manage the builtin functions
 * @cmd: the command line on string form
 * @f: the associated function
 *
 */
typedef struct inbuilt
{
	char *cmd;
	int (*f)(das_h *data);
} in_built;

/* *****aid.c and aid_2.c *******/
char *_getenv(char *path_name);
void inter_signal(int signo);
void *fill_array(void *a, int el, unsigned int len);
void rev_ar(char *arr, int len);
void index_cmd(das_h *data);
int len_digit(int num);
int error_info(das_h *data);
char *int_to_str(unsigned int n);
int _atoi(char *c);
int history_info(das_h *data);

/* ************ cache.c ************/
void *_realloc(void *ptr, unsigned int size_before, unsigned int size_after);
char *_memset(char *s, char byt, unsigned int n);
int free_data(das_h *data);
char *_memcpy(char *dest, char *src, unsigned int n);

/* ************function.c*************/
int is_path(das_h *data);
void is_short(das_h *data);
int is_in_built(das_h *data);


/********** dash.c **************/
int read_line(das_h *data);
int split_line(das_h *data);
int parse_line(das_h *data);
int process_cmd(das_h *data);

/* **********in_built.c *********/
int cd_dir(das_h *data);
int kill_program(das_h *data /* usused */);
int handle_builtin(das_h *data);
int help_info(das_h *data);

/********** mystring.c ***************/

char *_strcpy(char *dest, char *src);
int _isalpha(int c);
char *_strcat(char *first, char *second);
int _strlen(char *str);
int _strcmp(char *s1, char *s2);
char *_strchr(char *str, char c);
char *_strdup(char *str);

#endif /* DASH_H */
