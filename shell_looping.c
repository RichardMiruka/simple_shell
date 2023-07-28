#include "main.h"

/**
 * shell_loop - Main loop of the shell program.
 *
 * @datash: Pointer to the data structure containing relevant data (av, input, args).
 *
 * Return: No return value.
 */
void shell_loop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4); /* Print the prompt symbol to stdout */
		input = read_line(&i_eof); /* Read a line of input from stdin */
		if (i_eof != -1)
		{
			input = without_comment(input); /* Remove comments from the input */
			if (input == NULL)
				continue; /* Continue the loop if the input is empty after removing comments */

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2; /* Set the status to 2 if there is a syntax error */
				free(input);
				continue; /* Continue the loop to read the next input */
			}
			input = rep_var(input, datash); /* Replace variables in the input */
			loop = split_commands(datash, input); /* Split and execute commands from the input */
			datash->counter += 1; /* Increment the line counter */
			free(input); /* Free the memory allocated for the input */
		}
		else
		{
			loop = 0; /* Exit the loop if the end-of-file is reached (i_eof = -1) */
			free(input); /* Free the memory allocated for the input */
		}
	}
}

/**
 * without_comment - Remove comments from the input.
 *
 * @in: Input string containing a command line.
 * Return: Input string without comments.
 */
char *without_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#') /* If a comment symbol '#' is found */
		{
			if (i == 0)
			{
				free(in);
				return (NULL); /* If '#' is the first character, the entire input is a comment */
			}

			/* If '#' is preceded by a space, tab, or semicolon, consider it as a valid comment */
			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i; /* Store the index up to which the input is valid (excluding the comment) */
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1); /* Reallocate memory to remove the comment from the input */
		in[up_to] = '\0'; /* Null-terminate the input at the end of the valid characters */
	}

	return (in); /* Return the input string without comments */
}

