#include "main.h"

/**
 * read_line - Reads a line of input from stdin.
 *
 * @i_eof: Pointer to an integer to store the return value of getline function.
 *
 * Return: The input string read from stdin.
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}


