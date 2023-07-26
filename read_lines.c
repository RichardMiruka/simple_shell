#include "main_unique.h"

/**
 * unique_read_line - Reads the input string from stdin using getline.
 *
 * @i_eof: Pointer to store the return value of getline function (EOF status).
 * Return: Input string.
 */
char *unique_read_line(int *i_eof)
{
    char *input = NULL;
    size_t bufsize = 0;

    *i_eof = getline(&input, &bufsize, stdin);

    return (input);
}


