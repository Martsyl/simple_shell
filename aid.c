#include "dash.h"

/**
 * _getenv - Get the value of an environment variable.
 * @path_name: Pointer to the name of the environment variable.
 *
 * Return: On success
 */
char *_getenv(char *path_name)
{
	char **environ_cursor, *env_ptr, *name_ptr;

	environ_cursor = environ;
       /* Loop through the environment variables */

	while (*environ_cursor)
	{
		env_ptr = *environ_cursor;
		name_ptr = path_name;

		/* Compare the name of the environ variable with the requested name */
		while (*env_ptr == *name_ptr)
		{
			if (*env_ptr == '=')
				break;
			env_ptr++;
			name_ptr++;
		}

		/* If a match is found, return the value of the environment variable */
		if ((*env_ptr == '=') && (*name_ptr == '\0'))
			return (env_ptr + 1);
		environ_cursor++;
	}

	/* If the environment variable is not found, return NULL */
	return (NULL);
}

/**
 * inter_signal - Handle the process interrupt signal (SIGINT).
 * @signo: The signal identifier.
 *
 * Return: void
 */
void inter_signal(int signo)
{
	if (signo == SIGINT)
	{
		/* Print a newline and the prompt when a SIGINT signal is received */
		PUT("\n");
		PUT(PROMPT);
	}
}

/**
 * fill_array - Fill an array with a given element.
 * @a: Pointer to the array.
 * @el: The element to fill the array with.
 * @len: The length of the array.
 *
 * Return: Pointer to the filled array.
 */
void *fill_array(void *a, int el, unsigned int len)
{
	char *p = a;
	unsigned int i = 0;
	/* Loop through the array and fill it with the given element */
	while (i < len)
	{
		*p = el;
		p++;
		i++;
	}
	return (a);
}

/**
 * rev_ar - Reverse an array.
 * @arr: Pointer to the array to be reversed.
 * @len: The length of the array.
 *
 * Return: void
 */
void rev_ar(char *arr, int len)
{
	int i;
	char tmp;

    /* Loop through the array and swap elements to reverse it */
	for (i = 0; i < (len / 2); i++)
	{
		tmp = arr[i];
		arr[i] = arr[(len - 1) - i];
		arr[(len - 1) - i] = tmp;
	}
}

/**
 * index_cmd - Increment the index in the data structure.
 * @data: Pointer to the data structure (das_h).
 *
 * Return: void
 */
void index_cmd(das_h *data)
{
	/* Increment the index in the data structure */
	data->index += 1;
}

