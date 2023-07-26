#include "main_unique.h"

/**
 * _setenv_command - sets an environment variable
 *
 * @shell_data: data relevant (env name and env value)
 * Return: 1 on success.
 */
int _setenv_command(shell_data_t *shell_data)
{
	if (shell_data->arguments[1] == NULL || shell_data->arguments[2] == NULL)
	{
		get_error(shell_data, -1);
		return (1);
	}

	set_environment_variable(shell_data->arguments[1], shell_data->arguments[2], shell_data);

	return (1);
}

/**
 * copy_information - copies information to create
 * a new environment variable or alias
 * @name: name (environment variable or alias)
 * @value: value (environment variable or alias)
 *
 * Return: new environment variable or alias.
 */
char *copy_information(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = string_length(name);
	len_value = string_length(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	if (!new)
	{
		return (NULL);
	}
	concatenate_strings(new, name);
	concatenate_strings(new, "=");
	concatenate_strings(new, value);

	return (new);
}

/**
 * set_environment_variable - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @shell_data: data structure (environment variables)
 * Return: no return
 */
void set_environment_variable(char *name, char *value, shell_data_t *shell_data)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; my_environ[i]; i++)
	{
		var_env = string_duplicate(my_environ[i]);
		name_env = strtok(var_env, "=");
		if (compare_strings(name_env, name) == 0)
		{
			free(my_environ[i]);
			my_environ[i] = copy_information(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	my_environ = custom_reallocate_double_pointer(my_environ, i, i + 2);
	if (!my_environ)
	{
		return;
	}
	my_environ[i] = copy_information(name, value);
	my_environ[i + 1] = NULL;
}

/**
 * _unsetenv_command - deletes an environment variable
 *
 * @shell_data: data relevant (environment variable name)
 *
 * Return: 1 on success.
 */
int _unsetenv_command(shell_data_t *shell_data)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (shell_data->arguments[1] == NULL)
	{
		get_error(shell_data, -1);
		return (1);
	}
	k = -1;
	for (i = 0; my_environ[i]; i++)
	{
		var_env = string_duplicate(my_environ[i]);
		name_env = strtok(var_env, "=");
		if (compare_strings(name_env, shell_data->arguments[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(shell_data, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	if (!realloc_environ)
	{
		return (1);
	}
	for (i = j = 0; my_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = my_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(my_environ[k]);
	free(my_environ);
	my_environ = realloc_environ;
	return (1);
}
