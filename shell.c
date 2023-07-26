#include "main.h"
/**
 * main - the main func
 * Return: 0
 */
int main(void)
{
	int get_status, keep_running = 1;
	char *buff = NULL; 
	char *agc[2];
	pid_t pid;

	while (keep_running)
	{
		printf("#cisfun$ ");
		if (handle_inp(&buff, agc) == -1)
			keep_running = 0;
		else
		{
			if (buff[0] == '\0')
				continue;
			pid = fork();
			if (pid == 0)
			{
				if (execve(agc[0], agc, environ) == -1)
					perror("./shell");

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
	if (keep_running == 0)
		return (-1);
	return (0);
}
