#include "main_unique.h"

/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @shell_data: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other cases
 */
int check_syntax_error(shell_data_t *shell_data, char *input)
{
	int begin = 0;
	int first_char_result = 0;
	int error_sep_op_result = 0;
	int i = 0;

	first_char_result = first_char(input, &begin);
	if (first_char_result == -1)
	{
		print_syntax_error(shell_data, input, begin, 0);
		return 1;
	}

	error_sep_op_result = error_sep_op(input + begin, 0, *(input + begin));
	if (error_sep_op_result != 0)
	{
		print_syntax_error(shell_data, input, begin + error_sep_op_result, 1);
		return 1;
	}

	return 0;
}

/**
 * print_syntax_error - prints when a syntax error is found
 *
 * @shell_data: data structure
 * @input: input string
 * @index: index of the error
 * @is_separator: flag to control error message
 * Return: no return
 */
void print_syntax_error(shell_data_t *shell_data, char *input, int index, int is_separator)
{
	char *error_msg, *error, *counter;
	int length;

	if (input[index] == ';')
	{
		if (is_separator == 0)
			error_msg = (input[index + 1] == ';' ? ";;" : ";");
		else
			error_msg = (input[index - 1] == ';' ? ";;" : ";");
	}

	if (input[index] == '|')
		error_msg = (input[index + 1] == '|' ? "||" : "|");

	if (input[index] == '&')
		error_msg = (input[index + 1] == '&' ? "&&" : "&");

	const char *error_msg2 = ": Syntax error: \"";
	const char *error_msg3 = "\" unexpected\n";
	counter = integer_to_string(shell_data->line_counter);
	length = string_length(shell_data->arguments[0]) + string_length(counter);
	length += string_length(error_msg) + string_length(error_msg2) + string_length(error_msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(counter);
		return;
	}

	concatenate_strings(error, shell_data->arguments[0]);
	concatenate_strings(error, ": ");
	concatenate_strings(error, counter);
	concatenate_strings(error, error_msg2);
	concatenate_strings(error, error_msg);
	concatenate_strings(error, error_msg3);

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * @index: index
 * Return: repetitions
 */
int repeated_char(char *input, int index)
{
	if (*(input - 1) == *input)
		return repeated_char(input - 1, index + 1);

	return index;
}

/**
 * error_sep_op - finds syntax errors
 *
 * @input: input string
 * @index: index
 * @last: last char read
 * Return: index of error. 0 when there are no errors
 */
int error_sep_op(char *input, int index, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return 0;

	if (*input == ' ' || *input == '\t')
		return error_sep_op(input + 1, index + 1, last);

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return index;

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return index;

		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return index;
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return index;

		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return index;
		}
	}

	return error_sep_op(input + 1, index + 1, *input);
}

/**
 * first_char - finds index of the first char
 *
 * @input: input string
 * @index: index
 * Return: 1 if there is an error. 0 in other cases.
 */
int first_char(char *input, int *index)
{
	for (*index = 0; input[*index]; *index += 1)
	{
		if (input[*index] == ' ' || input[*index] == '\t')
			continue;

		if (input[*index] == ';' || input[*index] == '|' || input[*index] == '&')
			return -1;

		break;
	}

	return 0;
}
