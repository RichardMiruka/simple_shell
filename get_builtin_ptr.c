#include "main_unique.h"

/**
 * get_builtin_command - finds and returns a pointer to the builtin function
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin_command(char *cmd))(shell_data_t *)
{
    builtin_command_t builtin[] = {
        { "env", env_command },
        { "exit", shell_exit },
        { "setenv", setenv_command },
        { "unsetenv", unsetenv_command },
        { "cd", change_directory },
        { "help", get_help },
        { NULL, NULL }
    };
    int i;

    for (i = 0; builtin[i].name; i++)
    {
        if (_strcmp(builtin[i].name, cmd) == 0)
            break;
    }

    return (builtin[i].function);
}

