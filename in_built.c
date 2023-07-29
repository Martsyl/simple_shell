#include "dash.h"

/**
 * cd_dir - changes directory
 * @data: a pointer to the data structure
 *
 * Return: (Success) 0 is returned
 * ------- (Fail) negative number will returned
 */
int cd_dir(das_h *data)
{
	char *home;

	home = _getenv("HOME");
	if (data->args[1] == NULL)
	{
		/* Change to HOME directory and update OLDPWD */
		SETOWD(data->oldpwd);
		if (chdir(home) < 0)
			return (CRASH);
		return (PASS);
	}
	if (_strcmp(data->args[1], "-") == 0)
	{
		if (data->oldpwd == 0)
		{
			/* If OLDPWD is not set, change to HOME dir and update OLDPWD */
			SETOWD(data->oldpwd);
			if (chdir(home) < 0)
				return (CRASH);
		}
		else
		{
			/* Change to OLDPWD and update OLDPWD with the current directory */
			SETOWD(data->oldpwd);
			if (chdir(data->oldpwd) < 0)
				return (CRASH);
		}
	}
	else
	{
		/* Change to the specified directory and update OLDPWD */
		SETOWD(data->oldpwd);
		if (chdir(data->args[1]) < 0)
			return (CRASH);
	}
	return (PASS);
}

#undef GETCWD

/**
 * kill_program - exit the program
 * @data: a pointer to the data structure
 *
 * Return: (Success) 0 is returned
 * ------- (Fail) negative number will returned
 */
int kill_program(das_h *data /* usused */)
{
	int code, i = 0;

	if (data->args[1] == NULL)
	{
		/* If no argument provided, exit with the errno value */
		free_data(data);
		exit(errno);
	}

    /* Check if the argument is a valid integer (exit code) */
	while (data->args[1][i])
	{
		if (_isalpha(data->args[1][i++]) < 0)
		{
			data->error_msg = _strdup("Illegal number\n");
			return (CRASH);
		}
	}
	code = _atoi(data->args[1]);

    /* Free data and exit with the provided exit code */
	free_data(data);
	exit(code);
}

/**
 * handle_builtin - handle and manage the builtins cmd
 * @data: a pointer to the data structure
 *
 * Return: (Success) 0 is returned
 * ------- (Fail) negative number will returned
 */
int handle_builtin(das_h *data)
{
	/* Definition of the built-in commands and their corresponding functions */
	in_built blt[] = {
		{"exit", kill_program},
		{"cd", cd_dir},
		{"help", help_info},
		{NULL, NULL}
	};
	int i = 0;

	/* Loop through the built-in cmd and execute the corresponding function */
	while ((blt + i)->cmd)
	{
		if (_strcmp(data->args[0], (blt + i)->cmd) == 0)
			return ((blt + i)->f(data));
		i++;
	}

	/* If the command is not a built-in, return CRASH  */
	return (CRASH);
}

/**
 * help_info - display the help menu
 * @data: a pointer to the data structure
 *
 * Return: (Success) 0 is returned
 * ------- (Fail) negative number will returned
 */
int help_info(das_h *data)
{
	int fd, fw, rd = 1;
	char c;

	fd = open(data->args[1], O_RDONLY);
	if (fd < 0)
	{
		data->error_msg = _strdup("no help topics match\n");
		return (CRASH);
	}
	while (rd > 0)
	{
		rd = read(fd, &c, 1);
		fw = write(STDOUT_FILENO, &c, rd);
		if (fw < 0)
		{
			data->error_msg = _strdup("cannot write: permission denied\n");
			return (CRASH);
		}
	}
	PUT("\n");
	return (PASS);
}

