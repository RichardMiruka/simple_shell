#include "main.h"

/**
 * error_handler - Handles and displays errors based on the given evaluation value
 *
 * @shell_data: Pointer to the shell data structure
 * @evaluation: Error value to determine the error type
 * Return: The evaluation value
 */
int error_handler(shell_data_t *shell_data, int evaluation)
{
	char *error_message = NULL;

	switch (evaluation)
	{
	case -1:
		error_message = error_environment_variable(shell_data);
		break;
	case 126:
		error_message = error_permission(shell_data->arguments[0]);
		break;
	case 127:
		error_message = error_command_not_found(shell_data);
		break;
	case 2:
		if (_strcmp("exit", shell_data->arguments[0]) == 0)
			error_message = error_exit_shell(shell_data);
		else if (_strcmp("cd", shell_data->arguments[0]) == 0)
			error_message = error_get_cd(shell_data);
		break;
	default:
		break;
	}

	if (error_message)
	{
		write(STDERR_FILENO, error_message, _strlen(error_message));
		free(error_message);
	}

	shell_data->last_status = evaluation;
	return (evaluation);
}

