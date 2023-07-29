#include "dash.h"

/**
 * len_digit - Determine the number of digits in an integer
 * @num: The given number
 *
 * Return: The length of the integer
 */
int len_digit(int num)
{
	int len = 1;

	while (num >= 10) /* Continue until the number becomes single-digit */
	{
		len++;
		num /= 10;
	}
	return (len);
}

/**
 * error_info - Print error message to standard output
 * @data: The data structure pointer
 *
 * Return: Always returns 0
 */
int error_info(das_h *data)
{
	char *idx = int_to_str(data->index);

	PUT("hsh: ");
	PUT(idx);
	PUT(": ");
	PUT(data->args[0]);
	PUT(": ");
	PUT(data->error_msg);

	free(idx);
	return (0);
}

/**
 * int_to_str - Convert an integer to a string
 * @n: The given number
 *
 * Return: A pointer to the null-terminated string
 */
char *int_to_str(unsigned int n)
{
	int len = 0;
	char *s;

	len = len_digit(n);
	s = malloc(len + 1);
	if (!s)
		return (NULL);

	s[len] = '\0'; /* Null-terminate the string */
	while (n != 0)
	{
		s[--len] = (n % 10) + '0'; /* Convert the last digit to a character */
		n /= 10;
	}

	return (s);
}

/**
 * _atoi - Convert a string to an integer
 * @c: The given character
 *
 * Return: An integer
 */
int _atoi(char *c)
{
	unsigned int val = 0;
	int sign = 1;

	if (!c)
		return (0);

	if (*c == '-') /* Check for negative sign */
	{
		sign = -1;
		c++;
	}

	while (*c)
	{
		val = (val * 10) + (*c - '0'); /* Convert the character to integer digit */
		c++;
	}

	return (sign * val);
}

/**
 * history_info - Write a line of history to a file
 * @data: The data structure pointer (Unused in this implementation)
 *
 * Return: 1 on success, -1 on failure
 */
int history_info(das_h *data)
{
	(void) data;
	char *filename = "history";
	char *line_of_history = "this is a line of history";
	ssize_t fd, w;
	int len = 0;

	if (!filename)
		return (-1);
	fd = open(filename, O_RDWR | O_APPEND);
	if (fd < 0)
		return (-1);

	if (line_of_history)
	{
		while (line_of_history[len])
			len++;
		w = write(fd, line_of_history, len);
		if (w < 0)
			return (-1);
	}

	return (1);
}
