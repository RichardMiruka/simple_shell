#include "main_unique.h"

/**
 * shell_loop - Main loop of the shell.
 *
 * @shell_data: Data relevant to the shell's runtime.
 * Return: No return.
 */
void shell_loop(shell_data_t *shell_data)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDOUT_FILENO, "^-^ ", 4);
		input = unique_read_line(&i_eof);
		if (i_eof != -1)
		{
			input = remove_comments(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(shell_data, input) == 1)
			{
				shell_data->last_status = 2;
				free(input);
				continue;
			}
			input = replace_variable(input, shell_data);
			loop = split_commands(shell_data, input);
			shell_data->line_counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

/**
 * remove_comments - Deletes comments from the input.
 *
 * @input: Input string.
 * Return: Input without comments.
 */
char *remove_comments(char *input)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		input = _realloc(input, i, up_to + 1);
		input[up_to] = '\0';
	}

	return (input);
}

