#include "main.h"

/**
 * read_line - Read input from stream (stdin).
 * @lineptr: Buffer that stores the input.
 * @n: Size of lineptr.
 * @stream: Stream to read from (stdin).
 * Return: The number of bytes read.
 */
ssize_t read_line(char **lineptr, size_t *n, FILE *stream)
{
    int i;
    static ssize_t input;
    ssize_t retval;
    char *buffer;
    char t = 'z';

    /* If input is 0, flush the stream. */
    if (input == 0)
        fflush(stream);
    else
        return (-1);

    input = 0;
    buffer = malloc(sizeof(char) * BUFFER_SIZE);

    if (buffer == NULL)
        return (-1);

    /* Read characters until a newline is encountered. */
    while (t != '\n')
    {
        i = read(STDIN_FILENO, &t, 1);

        if (i == -1 || (i == 0 && input == 0))
        {
            free(buffer);
            return (-1);
        }

        if (i == 0 && input != 0)
        {
            input++;
            break;
        }

        /* Reallocate buffer if input exceeds current size. */
        if (input >= BUFFER_SIZE)
            buffer = _realloc(buffer, input, input + 1);

        buffer[input] = t;
        input++;
    }

    buffer[input] = '\0';

    /* Assign the line to lineptr. */
    assign_line(lineptr, n, buffer, input);

    retval = input;

    if (i != 0)
        input = 0;

    return (retval);
}

/**
 * assign_line - Assigns the line variable for read_line.
 * @lineptr: Buffer that stores the input string.
 * @n: Size of line.
 * @buffer: String that is being assigned to line.
 * @j: Size of buffer.
 */
void assign_line(char **lineptr, size_t *n, char *buffer, size_t j)
{
    if (*lineptr == NULL || *n < j)
    {
        if (j > BUFFER_SIZE)
            *n = j;
        else
            *n = BUFFER_SIZE;

        free(*lineptr);
        *lineptr = buffer;
    }
    else
    {
        /* Copy the buffer to lineptr and free the buffer. */
        _strcpy(*lineptr, buffer);
        free(buffer);
    }
}

