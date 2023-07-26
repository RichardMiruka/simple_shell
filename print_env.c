#include "main_unique.h"

/**
 * print_env - Prints the environment variables.
 *
 * @shell_data: Pointer to the shell_data_t struct
 * Return: 1 on success.
 */
int print_env(shell_data_t *shell_data)
{
    int i, j;

    for (i = 0; shell_data->shell_env[i]; i++)
    {
        for (j = 0; shell_data->shell_env[i][j]; j++)
            ;

        write(STDOUT_FILENO, shell_data->shell_env[i], j);
        write(STDOUT_FILENO, "\n", 1);
    }

    shell_data->last_status = 0;
    return (1);
}

/**
 * _getenv - Get an environment variable.
 * @name: Name of the environment variable.
 * @environment: Environment variable.
 *
 * Return: Value of the environment variable if found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **environment)
{
    char *ptr_env;
    int i, mov;

    /* Initialize ptr_env value */
    ptr_env = NULL;
    mov = 0;

    /* Compare all environment variables */
    /* environ is declared in the header file */
    for (i = 0; environment[i]; i++)
    {
        /* If name and env are equal */
        mov = cmp_env_name(environment[i], name);
        if (mov)
        {
            ptr_env = environment[i];
            break;
        }
    }

    return (ptr_env + mov);
}

/**
 * cmp_env_name - Compares environment variables names
 * with the name passed.
 * @nenv: Name of the environment variable.
 * @name: Name passed.
 *
 * Return: 0 if they are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
    int i;

    for (i = 0; nenv[i] != '='; i++)
    {
        if (nenv[i] != name[i])
        {
            return (0);
        }
    }

    return (i + 1);
}

