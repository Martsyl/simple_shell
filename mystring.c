#include "dash.h"

/**
 * _strcat - Concatenates two strings in a path form.
 * @first: The first given destination.
 * @second: The second given source.
 *
 * Return: (Success) A newly allocated string containing the conc. outcome.
 * ------- (Fail) NULL if memory allocation fails.
 */
char *_strcat(char *first, char *second)
{
	int len1, len2, i = 0, j = 0;
	char *outcome;

	len1 = _strlen(first);
	len2 = _strlen(second);

    /* Allocate memory for the concatenated string */
	outcome = malloc((len1 + len2 + 2) * sizeof(char));
	if (!outcome)
		return (NULL);

	*outcome = '\0';

    /* Copy the first string into the outcome */
	while (first[j])
		outcome[i++] = first[j++];

    /* Add a path separator '/' */
	outcome[i++] = '/';

	j = 0;

    /* Append the second string to the outcome */
	while (second[j])
		outcome[i++] = second[j++];

    /* Null-terminate the outcome string */
	outcome[i] = '\0';

	return (outcome);
}

/**
 * _strlen - Finds the length of a given string.
 * @str: The given string.
 *
 * Return: (Success) The length of the string.
 * ------- (Fail) Returns a negative value.
 */
int _strlen(char *str)
{
	int len;

	for (len = 0; str[len]; len++)
		;
	return (len);
}

/**
 * _strcmp - Compare two strings.
 * @s1: The first given string.
 * @s2: The second given string.
 *
 * Return: (Success) A positive number if strings are different..
 */
int _strcmp(char *s1, char *s2)
{
	int cmp = 0, i;

    /* Check if either of the strings is NULL */
	if (s1 == NULL || s2 == NULL)
		return (1);

    /* Compare char until a diff is found or the end of one str is reached */
	for (i = 0; s1[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			cmp = s1[i] - s2[i];
				break;
		}
		else
			continue;
	}
	return (cmp);
}

/**
 * _strchr - Locates a character in a given string.
 * @str: The given string.
 * @c: The character to be found.
 *
 * Return: (Success) A pointer to the first occurrence of the char c in str.
 * ------- (Fail) Return a NULL pointer if the character is not found.
 */
char *_strchr(char *str, char c)
{
	char *ptr;

	if (!str)
		return (NULL);

    /* Iterate through the string until the character is found */

	for (ptr = str; *ptr; ptr++)
		if (*ptr == c)
			return (ptr);
	return (NULL);
}

/**
 * _strdup - Duplicates a string.
 * @str: The given string.
 *
 * Return: (Success) A pointer to the duplicated string.
 * ------- (Fail) Return a NULL pointer if memory allocation fails.
 */
char *_strdup(char *str)
{
	char *paired;

	if (!str)
		return (NULL);

    /* Allocate memory for the duplicate string */
	paired = malloc(_strlen(str) + 1);
	if (!paired)
		return (NULL);

    /* Copy the original string into the duplicate */
	_strcpy(paired, str);
	return (paired);
}

