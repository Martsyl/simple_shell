#include "main.h"
/**
* main - Entry point
* Return: 0 on success
*/

int main(void)
{
	int get_status, keep_running = 1, get_input, get_num = 0;
	char *buff = NULL;
	pid_t pid;
	char *agc[20], *args;

	while (keep_running)
	{
		_puts("$ ");
		get_input = handle_inp(&buff, agc);
		if (get_input == -1 || get_input == 2)
			keep_running = 0;
		if (get_input != -1)
		{
			if (buff[0] == '\0')
				continue;
			args = strtok(buff, " ");
			while (args != NULL)
			{
				agc[get_num] = args;
				args = strtok(NULL, " ");
				get_num++;
			}
			agc[get_num] = NULL;
			pid = fork();
			if (pid == 0)
			{
				if (execve(agc[0], agc, environ) == -1)
					perror(agc[0]);
			}
			else if (pid == -1)
				keep_running = 0;
			else
			{
				wait(&get_status);
				if (!(WIFEXITED(get_status) && (WEXITSTATUS(get_status) == 0)))
					keep_running = 0;
			}
		}
	}
	free(buff);
	return (keep_running ? 0 : 1);
}
