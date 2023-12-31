#include "dash.h"

/**
 * aux_help_alias - Provides help information for the builtin alias command.
 * Return: No return value.
 */
void aux_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	PUT(help);
	help = "\tDefine or display aliases.\n";
	PUT(help);
}

/**
 * change_cd_help - Provides help information for the builtin cd command.
 * Return: No return value.
 */
void change_cd_help(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	PUT(help);
	help = "\tChange the shell working directory.\n";
	PUT(help);
}

/**
 * rev_string - Reverses a string.
 * @s: Input string.
 * Return: No return value.
 */
void rev_string(char *s)
{
	int length = 0;
	char *start = s;
	char *end = s;
	char temp;

	if (s == NULL)
		return;

	/* Find the end of the string */
	while (*end != '\0')
	{
		length++;
		end++;
	}

	end--; /* Set 'end' to the last character before the null terminator */

	/* Swap characters from both ends */
	while (start < end)
	{
		temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
}
