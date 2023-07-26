#include "main_unique.h"

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
    shell_data_t datash;
    (void)ac; // Unused parameter warning.

    signal(SIGINT, get_sigint_handler);
    set_shell_data(&datash, av);
    shell_loop(&datash);
    free_shell_data(&datash);

    if (datash.last_status < 0)
        return 255;

    return datash.last_status;
}

/**
 * free_shell_data - frees shell_data structure
 *
 * @datash: shell_data structure
 * Return: no return
 */
void free_shell_data(shell_data_t *datash)
{
    unsigned int i;

    for (i = 0; datash->shell_env[i]; i++)
    {
        free(datash->shell_env[i]);
    }

    free(datash->shell_env);
    free(datash->shell_pid);
}

/**
 * set_shell_data - Initializes the shell_data structure
 *
 * @datash: shell_data structure
 * @av: argument vector
 *
 * Return: no return
 */
void set_shell_data(shell_data_t *datash, char **av)
{
    unsigned int i;

    datash->av = av;
    datash->command_line = NULL;
    datash->arguments = NULL;
    datash->last_status = 0;
    datash->line_counter = 1;

    for (i = 0; my_environ[i]; i++)
        ;

    datash->shell_env = malloc(sizeof(char *) * (i + 1));

    for (i = 0; my_environ[i]; i++)
    {
        datash->shell_env[i] = string_duplicate(my_environ[i]);
    }

    datash->shell_env[i] = NULL;
    datash->shell_pid = integer_to_string(getpid());
}

