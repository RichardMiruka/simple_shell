#include "main_unique.h"

/**
 * print_env - prints the environment variables
 *
 * @shell_data: data relevant.
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
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @environment: environment variable
 *
 * Return: value of the environment variable if found.
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
 * cmp_env_name - compares environment variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
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

