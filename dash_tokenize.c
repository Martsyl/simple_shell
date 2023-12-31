#include "dash.h"

/**
 * add_nodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void add_nodes(dash_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = swap_char(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_div_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_div_node_end(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * next_cmd - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @shdata: data structure
 * Return: no return
 */
void next_cmd(dash_list **list_s, line_list **list_l, dash_data *shdata)
{
	int loop_sep;
	dash_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (shdata->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * div_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @shdata: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int div_commands(dash_data *shdata, char *input)
{
	dash_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l)
	{
		shdata->input = list_l->line;
		shdata->args = tokenize_line(shdata->input);
		loop = exec_line(shdata);
		free(shdata->args);

		if (loop == 0)
			break;

		next_cmd(&list_s, &list_l, shdata);

		if (list_l)
			list_l = list_l->next;
	}

	free_div_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * tokenize_line - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **tokenize_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOKENSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (!tokens)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, DELIMETER);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOKENSIZE;
			tokens = _realloc_ptr(tokens, i, sizeof(char *) * bsize);
			if (!tokens)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, DELIMETER);
		tokens[i] = token;
	}

	return (tokens);
}

/**
 * swap_char - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swap_char(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}
