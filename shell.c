#include "main.h"

/**
 * main - Entry point
 *
 * Return: Always 0
 */

int main(void)
{
	bool keep_running = true;
	char *buff = NULL, *buff_cpy = NULL;
	const char *get_delim = " \t\n";
	size_t get_buffsize = 0, gettk_len;
	int count;
	ssize_t rn;
	char *tkns[100] = {0}, *tkn = NULL;

	while (keep_running)
	{
		if (isatty(STDIN_FILENO))
			write(1, "#cisfun$ ", 9);
		else
			keep_running = false;
		rn = getline(&buff, &get_buffsize, stdin);
		if (rn == -1)
		{
			if (!isatty(STDIN_FILENO))
			{
				free(buff);
				break;
			}
			perror("getline");
			free(buff);
			exit(EXIT_FAILURE);
		}
		if (*buff == '\n' || (*buff == ' ' || *buff == '\t'))
			continue;
		buff_cpy = str_dup(buff);
		tkn = strtok(buff_cpy, get_delim);
		for (count = 0; tkn; count++)
		{
			gettk_len = _strlen(tkns);
			tkns[count] = malloc(sizeof(char *) * gettk_len);
			strn_cpy(tkns[count], tkn, gettk_len + 1);
			tkn = strtok(NULL, get_delim);
		}
		free(buff_cpy);
		exec_cmmd(tkns, buff);
		free_line(tkns);
		free(buff);
		buff = NULL;
		get_buffsize = 0;
	}
	free(buff);
	return (0);
}
