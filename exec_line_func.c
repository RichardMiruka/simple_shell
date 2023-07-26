#include "main_unique.h"

/**
 * exec_line - Finds builtins and commands and executes them.
 *
 * @datash: Pointer to the shell_data_t struct (args).
 * Return: 1 on success, -1 on error.
 */
int exec_line(shell_data_t *datash)
{
    int (*builtin)(shell_data_t *datash);

    if (datash->arguments[0] == NULL)
        return 1;

    // Check if the command is a builtin
    builtin = get_builtin_command(datash->arguments[0]);

    if (builtin != NULL)
        return builtin(datash);

    // Execute the command as an external command
    return execute_command(datash);
}




