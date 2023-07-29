#include "dash.h"

/**
 * main - the main function
 *
 * Return: (Success) 0 always
 * ------- (Fail) we drop out :)
 */
int main(void)
{
	das_h data;
	int pl;

	_memset((void *)&data, 0, sizeof(data));
	signal(SIGINT, inter_signal);


	while (1)
	{
		index_cmd(&data);
		if (read_line(&data) < 0)
		{
			if (isatty(STDIN_FILENO))
				PUT("\n");
			break;
		}
		if (split_line(&data) < 0)
		{
			free_data(&data);
			continue;
		}
		pl = parse_line(&data);

		if (pl == 0)
		{
			free_data(&data);
			continue;
		}
		if (pl < 0)
		{
			error_info(&data);
			continue;
		}
		if (process_cmd(&data) < 0)
		{
			error_info(&data);
			break;
		}
		free_data(&data);
	}

	free_data(&data);
	exit(EXIT_SUCCESS);
}

/**
 * read_line - read a line from the standard input
 * @data: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int read_line(das_h *data)
{
	char *csr_ptr, *end_ptr, c;
	size_t size = BUFSIZE, read_st, length, n_size;

	data->line = malloc(size * sizeof(char));

	if (data->line == NULL)
		return (CRASH);

	if (isatty(STDIN_FILENO))
		PUT(PROMPT);

	for (csr_ptr = data->line, end_ptr = data->line + size;;)
	{
		read_st = read(STDIN_FILENO, &c, 1);
		if (read_st == 0)
			return (CRASH);

		*csr_ptr++ = c;
		if (c == '\n')
		{
			*csr_ptr = '\0';
			return (PASS);
		}

		if (csr_ptr + 2 >= end_ptr)
		{
			n_size = size * 2;
			length = csr_ptr - data->line;
			data->line = _realloc(data->line, size * sizeof(char),
					n_size * sizeof(char));

			if (data->line == NULL)
				return (CRASH);
			size = n_size;
			end_ptr = data->line + size;
			csr_ptr = data->line + length;
		}
	}
}

#define DELIMITER " \n\t\r\a\v"

/**
 * split_line - splits line to tokens
 * @data: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int split_line(das_h *data)
{
	char *token;
	size_t size = TOKENSIZE, n_size, i = 0;

	if (_strcmp(data->line, "\n") == 0)
		return (CRASH);

	data->args = malloc(size * sizeof(char *));
	if (data->args == NULL)
		return (CRASH);

	token = strtok(data->line, DELIMITER);
	if (!token)
		return (CRASH);

	while (token)
	{
		data->args[i++] = token;
		if (i + 2 >= size)
		{
			n_size = size * 2;
			data->args = _realloc(data->args, size * sizeof(char *),
					n_size * sizeof(char *));

			if (data->args == NULL)
				return (CRASH);

			size = n_size;
		}

		token = strtok(NULL, DELIMITER);
	}

	data->args[i] = NULL;
	return (0);
}

#undef DELIMITER
#define DELIMITER ":"

/**
 * parse_line - parses arguments to a valid command
 * @data: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int parse_line(das_h *data)
{
	if (is_path(data) > 0)
		return (PASS);

	if (is_in_built(data) > 0)
	{
		if (handle_builtin(data) < 0)
			return (CRASH);

		return (OK);
	}
	is_short(data);
	return (PASS);
}

#undef DELIMITER

/**
 * process_cmd - process command and execute process
 * @data: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int process_cmd(das_h *data)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(data->cmd, data->args, environ) < 0)
		{
			data->error_msg = _strdup("not found\n");
			return (CRASH);
		}
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}

	return (0);
}

