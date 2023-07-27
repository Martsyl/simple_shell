#include "main.h"
/**
 * free_line - free the tokens
 *
 * @line: tokens
 */                           

void free_line(char **line)
{
	int i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
}
/**
 * exec_cmmd - exeutes dommands
 *@inp: tokens
 * @buff: buffer
 * Return: eexit
 */

void exec_cmmd(char **inp, char *buff)
{
	int status;
	pid_t pid;
	char *cmmd = NULL;
	cmmd = get_cmd(inp[0]);
	if (!cmmd)
	{
		printf("%s: cmmd not found\n", inp[0]);
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(cmmd, inp, environ) == -1)
		{
			perror("execve");
			free_line(inp);
			free(buff);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
	if (strcmp(cmmd, inp[0]) != 0)
		free(cmmd);


}
/**
 * get_env - get the env
 * @inp: name of the env
 * Return: ptr
 */
char *get_env(const char *inp)
{
	int i = 0;
	char *  get_name;
	for (i = 0; environ[i]; i++)
	{
		get_name = strtok(environ[i + 1], "=");
		if (strcmp( get_name, inp) == 0)
			return (strtok(NULL, "="));
	}
	return (NULL);
}

/**
 * get_cmd - fun that look for cmd
 * @cmmd: cmd
 * Return: char
 */
char *get_cmd(char *cmmd)
{
	char *path, *copy_path, *pth_tkn, *file_path;
	int cmmd_length, dir_len;
	struct stat buffer;
	path = getenv("PATH");

	if (path)
	{
		copy_path = str_dup(path);
		cmmd_length = _strlen(cmmd);
		pth_tkn = strtok(copy_path, ":");

		while (pth_tkn)
		{
			dir_len = _strlen(pth_tkn);
			file_path = malloc(cmmd_length + dir_len + 2);
			str_cpy(file_path, pth_tkn);
			str_cat(file_path, "/");
			str_cat(file_path, cmmd);
			str_cat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(copy_path);
				return (file_path);
			}
			else
			{
				free(file_path); /* free bushe ntchekiw li morah*/
				pth_tkn = strtok(NULL, ":");
			}
		}
		free(copy_path);
		if (stat(cmmd, &buffer) == 0) /* ila kant cmd brasha path .. wa mat3rf*/
		{
			return (cmmd);
		}
		return (NULL);
	}

	return (NULL);
}
