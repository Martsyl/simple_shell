#include "dash.h"

/**
 * _strcpy - Copies a string from source to destination.
 * @src: The string source.
 * @dest: The string destination.
 *
 * Return: The pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0'; /* Null-terminate the destination string */
	return (dest);
}

/**
 * _isalpha - Checks if the input is a letter.
 * @c: The character to be checked.
 *
 * Return: 1 if letter, else 0.
 */
int _isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (PASS);
	}
	return (CRASH);
}

