#include "main.h"
/**
 * _strncpy - function that copies a string
 *
 * @str: string
 * @qstr: source srting
 * @b: integer that specify the max num of chars to be copied.
 * Return: str
 */
char *strn_cpy(char *str, char *qstr, int b)
{
	int i;

	for (i = 0; i < b && qstr[i] != '\0'; i++)
	{
		str[i] = qstr[i];
	}
	while (i < b)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 *  _puts - print string to stdout
 * @str: pointer to string.
 * Return: Always 0.
 */
void _puts(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
	_putchar('\n');
}
