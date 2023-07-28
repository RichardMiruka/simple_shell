#include "main.h"

/* custom_repeated_char - Check for repeated character in a string */
int custom_repeated_char(char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i] == ';' || input[i] == '&' || input[i] == '|')
		return 1;
	return 0;
}

/* custom_error_sep_op - Check for syntax error in separators */
int custom_error_sep_op(char *input, int i, char last)
{
	if (input[i] == ';' || input[i] == '&' || input[i] == '|')
	{
		if (input[i + 1] == last)
		{
			write(STDERR_FILENO, "Syntax error near unexpected token `", 36);
			write(STDERR_FILENO, &input[i], 1);
			write(STDERR_FILENO, "'\n", 2);
			return 1;
		}
	}
	return 0;
}

/* custom_first_char - Check for the first non-space character in input */
int custom_first_char(char *input, int *i)
{
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
	if (input[*i] == '\0')
		return 1;
	return 0;
}

/* custom_print_syntax_error - Print syntax error message */
void custom_print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	char *counter_str;

	if (bool == 1)
	{
		write(STDERR_FILENO, datash->av[0], custom_strlen(datash->av[0]));
		write(STDERR_FILENO, ": ", 2);
		custom_print_number(datash->counter);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, input, custom_strlen(input));
		write(STDERR_FILENO, ": Syntax error: end of file unexpected\n", 39);
	}
	else
	{
		counter_str = custom_itoa(datash->counter);
		write(STDERR_FILENO, datash->av[0], custom_strlen(datash->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, counter_str, custom_strlen(counter_str));
		free(counter_str);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, input, custom_strlen(input));
		write(STDERR_FILENO, ": Syntax error: ", 16);
		write(STDERR_FILENO, "newline unexpected\n", 19);
	}
}

/* check_syntax_error - Check for syntax errors in the input */
int check_syntax_error(data_shell *datash, char *input)
{
	int i, nlen;

	if (input == NULL || input[0] == '\0')
		return 1;

	nlen = custom_strlen(input);
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#' && i == 0)
		{
			free(input);
			return 1;
		}
		if (input[i] == '\n' && custom_repeated_char(input, i + 1))
		{
			free(input);
			return 1;
		}
		if (input[i] == '\n' && input[i + 1] == '\n')
		{
			custom_print_syntax_error(datash, input, i, 0);
			free(input);
			return 1;
		}
		if (input[i] == '\n' && (input[i + 1] == ';' || input[i + 1] == '&' || input[i + 1] == '|'))
		{
			custom_print_syntax_error(datash, input, i, 0);
			free(input);
			return 1;
		}
		if (input[i] == ';' && custom_error_sep_op(input, i, ';'))
		{
			free(input);
			return 1;
		}
		if (input[i] == '&' && custom_error_sep_op(input, i, '&'))
		{
			free(input);
			return 1;
		}
		if (input[i] == '|' && custom_error_sep_op(input, i, '|'))
		{
			free(input);
			return 1;
		}
	}
	if (input[nlen - 1] == ';' || input[nlen - 1] == '&' || input[nlen - 1] == '|')
	{
		custom_print_syntax_error(datash, input, nlen - 1, 1);
		free(input);
		return 1;
	}

	return 0;
}
