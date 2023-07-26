#include "main.h"
/**
 * handle_inp - handles the inpu function
 * @buff: char pointer
 * @args: argument
 * Return: 0 on sucess
 */

int handle_inp(char **buff, char *args[])
{
	size_t get_len = 0;
	ssize_t read_inp;

	read_inp = getline(buff, &get_len, stdin);

	if (read_inp == -1 || (*buff)[read_inp - 1] != 10)
		return (-1);
	(*buff)[read_inp - 1] = '\0';
	args[0] = (*buff);
	args[1] = NULL;

	if (read_inp == 1)
	{
		return (1);
	}
	return (0);

}
