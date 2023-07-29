#include "dash.h"

/**
 * is_path - check if the given filename is a path
 * @data: the data struct pointer
 *
 * Return: (Success) - PASS if the filename is a path.
 *         (Fail)    - CRASH otherwise.
 */
int is_path(das_h *data)
{
	/* Check if the filename contains '/' */
	if (_strchr(data->args[0], '/') != 0)
	{
		/* If it contains '/', set the command to the filename. */
		data->cmd = _strdup(data->args[0]);
		return (PASS);
	}
	return (CRASH);
}

#define DELIMITER ":"

/**
 * is_short - check if the given filename is in short form
 * @data: the data struct pointer
 *
 * Return: (Success) - No explicit return value.
 *         (Fail)    - No explicit return value.
 **/
void is_short(das_h *data)
{
	char *path, *token, *_path;
	struct stat st;
	int exist_flag = 0;

	/* Get the value of the PATH environment variable */
	path = _getenv("PATH");
	_path = _strdup(path);

	/* Split the PATH using ':' as the delimiter and search for the executable*/
	token = strtok(_path, DELIMITER);
	while (token)
	{
		/* Concatenate the path with the filename to get the full command path. */
		data->cmd = _strcat(token, data->args[0]);

		/* Check if the file exists using stat function. */
		if (stat(data->cmd, &st) == 0)
		{
			exist_flag = 1;
			break;
		}

		/* Free the memory for the current path and prepare for the next iteration*/
		free(data->cmd);
		token = strtok(NULL, DELIMITER);
	}

	/* If the executable doesn't exist in any path, use the filename. */
	if (exist_flag == 0)
	{
		data->cmd = _strdup(data->args[0]);
	}

	/* Free the memory allocated for the PATH copy. */
	free(_path);
}

#undef DELIMITER

/**
 * is_in_built - check if the command is a built-in command
 * @data: a pointer to the data structure
 *
 * Return: (Success) - 0 is returned if the command is a built-in command.
 *         (Fail)    - A negative number is returned otherwise.
 */
int is_in_built(das_h *data)
{
	in_built blt[] = {
		{"exit", kill_program},
		{"cd", cd_dir},
		{"help", help_info},
		{NULL, NULL}
	};
	int i = 0;

	/* Loop through the list to check if the given cmd is one of them. */
	while ((blt + i)->cmd)
	{
		/* Compare the given command with the current built-in command. */
		if (_strcmp(data->args[0], (blt + i)->cmd) == 0)
			return (PASS);

		/* Move to the next built-in command. */
		i++;
	}

	return (OK);
}

