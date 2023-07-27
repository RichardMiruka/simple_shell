#include "main.h"

/**
 * error_path_126 - error message for path and failure denied permission.
 * @datash: Pointer to the shell_data_t struct.
 *
 * Return: The error string.
 */
char *error_path_126(shell_data_t *datash)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(datash->line_counter);
	length = _strlen(datash->arguments[0]) + _strlen(ver_str) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datash->arguments[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->arguments[0]);
	_strcat(error, ": Permission denied\n");
	free(ver_str);
	return (error);
}

/**
 * error_env - error message for env in get_env.
 * @datash: Pointer to the shell_data_t struct.
 * Return: The error message.
 */
char *error_env(shell_data_t *datash)
{
	int length;
	char *error;
	char *ver_str;
	const char *msg = ": Unable to add/remove from environment\n";

	ver_str = aux_itoa(datash->line_counter);
	length = _strlen(datash->arguments[0]) + _strlen(ver_str) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, datash->arguments[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->arguments[0]);
	_strcat(error, msg);
	free(ver_str);

	return (error);
}
