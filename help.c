#include "main_unique.h"

/**
 * unique_help - function that retrieves help messages according to the builtin
 *
 * @shell_data: data structure containing command line arguments and input
 * Return: Return 0
 */
int unique_help(shell_data_t *shell_data)
{
    if (shell_data->arguments[1] == NULL)
        auxiliary_help_general();
    else if (_strcmp(shell_data->arguments[1], "setenv") == 0)
        auxiliary_help_setenv();
    else if (_strcmp(shell_data->arguments[1], "env") == 0)
        auxiliary_help_env();
    else if (_strcmp(shell_data->arguments[1], "unsetenv") == 0)
        auxiliary_help_unsetenv();
    else if (_strcmp(shell_data->arguments[1], "help") == 0)
        auxiliary_help();
    else if (_strcmp(shell_data->arguments[1], "exit") == 0)
        auxiliary_help_exit();
    else if (_strcmp(shell_data->arguments[1], "cd") == 0)
        auxiliary_help_cd();
    else if (_strcmp(shell_data->arguments[1], "alias") == 0)
        auxiliary_help_alias();
    else
        write(STDERR_FILENO, shell_data->arguments[0], _strlen(shell_data->arguments[0]));

    shell_data->last_status = 0;
    return (1);
}
