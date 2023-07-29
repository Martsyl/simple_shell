#ifndef _DASH_H_
#define _DASH_H_

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libgen.h>
#include <signal.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

/******** macros ********/
#define PUT_PWD(cp_pwd) write(STDOUT_FILENO, cp_pwd, _strlen(cp_pwd))
#define PUT(help) write(STDOUT_FILENO, help, _strlen(help))
#define PUT_ELEN(erro, length) write(STDERR_FILENO, error, length)
#define PUT_ERR(error) write(STDERR_FILENO, error, _strlen(error))
#define DELIMETER " \t\r\n\a"
#define TOKENSIZE 128
#define BUFSIZE 1024

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;

/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} dash_data;

/**
 * struct div - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct div
{
	char separator;
	struct div *next;
} dash_list;

/**
 * struct cmd_line_list - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct cmd_line_list
{
	char *line;
	struct cmd_line_list *next;
} line_list;

/**
 * struct store_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct store_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct store_var_list *next;
} store_var;

/**
 * struct inbuilt - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct inbuilt
{
	char *name;
	int (*f)(dash_data *shdata);
} in_built;

/*change_dir.c*/
int cd_dir(dash_data *shdata);
void cd_per(dash_data *shdata);
void cd_goto(dash_data *shdata);
void cd_go_back(dash_data *shdata);
void cd_home(dash_data *shdata);

/*check_input.c*/
void check_env_var(store_var **h, char *in, dash_data *data);
int check_var_typed(store_var **h, char *in, char *st, dash_data *data);
char *replace_str_var(store_var **head,
		char *input, char *new_input, int nlen);
char *rep_str_var(char *input, dash_data *shdata);

/*conver_string.c*/
int get_len(int n);
char *int_to_string(int n);
int _atoi(char *s);
char *without_comment(char *in);
void cmd_help(void);
void aux_help_alias(void);
void change_cd_help(void);
void rev_string(char *s);

/*dash_list.c*/
store_var *add_store_var_node(store_var **head,
		int var_length, char *value, int value_length);
void free_store_var_list(store_var **head);
dash_list *add_div_node_end(dash_list **head, char sep);
void free_div_list(dash_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/*environ.c*/
char *copy_info(char *name, char *value);
void set_env_var(char *name, char *value, dash_data *shdata);
int _setenv(dash_data *shdata);
int _delenv(dash_data *shdata);
int cmp_env_name(const char *nenv, const char *name);
char *_getenv(const char *name, char **_environ);
int _env(dash_data *shdata);

/*error_code.c*/
int error_code(dash_data *shdata, int eval);
int (*get_builtin(char *cmd))(dash_data *);

/*error_msg.c*/
char *strcat_error_msg(dash_data *shdata,
		char *msg, char *error, char *var_str);
char *error_env(dash_data *shdata);
char *error_path_126(dash_data *shdata);
char *error_message(dash_data *shdata);
char *cmd_not_found(dash_data *shdata);
char *msg_exit_shell(dash_data *shdata);

/*error_syntax.c*/
int count_char(char *input, int i);
int find_sy_error(char *input, int i, char last);
int first_char_input(char *input, int *i);
void syntax_error_info(dash_data *shdata, char *input, int i, int bool);
int check_syntax_error(dash_data *shdata, char *input);

/*help_info.c*/
void _help_info_env(void);
void _help_info_setenv(void);
void _help_info_unsetenv(void);
void _help_info_exit(void);
int get_help(dash_data *shdata);

/*read_input.c*/
void assign_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
char *_get_line(int *i_eof);

/*realloc_ptr.c*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_realloc_ptr(char **ptr, unsigned int old_size, unsigned int new_size);
void _memcpy(void *dest, const void *src, unsigned int size);

/*shs_execve*/
int is_current_dir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_execve(dash_data *shdata);
int check_cmd_error(char *dir, dash_data *shdata);
int cmd_execve(dash_data *shdata);

/*shs_tokenize.c*/
void add_nodes(dash_list **head_s, line_list **head_l, char *input);
void next_cmd(dash_list **list_s, line_list **list_l, dash_data *shdata);
int div_commands(dash_data *shdata, char *input);
char **tokenize_line(char *input);
char *swap_char(char *input, int bool);

/*dash.c*/
void free_data(dash_data *shdata);
void set_data(dash_data *shdata, char **av);
void shell_prompt(dash_data *shdata);
void get_signal(int s);
void _help_info(void);

/*start_exit.c*/
int exec_line(dash_data *shdata);
int exit_shell(dash_data *shdata);

/*strings.c*/
char *_strdup(const char *s);
size_t _strlen(const char *s);
int comp_chars(const char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strchr(const char *s, int c);
size_t _strspn(const char *s, const char *accept);



#endif /* dash.h */
