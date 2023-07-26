#include "main_unique.h"

/**
 * check_error_cmd - verifies if the user has permissions to access
 *
 * @dir: destination directory
 * @shell_data: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_error_cmd(char *dir, shell_data_t *shell_data)
{
    if (dir == NULL)
    {
        get_error(shell_data, 127);
        return (1);
    }

    if (_strcmp(shell_data->arguments[0], dir) != 0)
    {
        if (access(dir, X_OK) == -1)
        {
            get_error(shell_data, 126);
            free(dir);
            return (1);
        }
        free(dir);
    }
    else
    {
        if (access(shell_data->arguments[0], X_OK) == -1)
        {
            get_error(shell_data, 126);
            return (1);
        }
    }

    return (0);
}

/**
 * is_executable - determines if it is an executable
 *
 * @shell_data: data structure
 * Return: 0 if it is not an executable, other number if it is
 */
int is_executable(shell_data_t *shell_data)
{
    struct stat st;
    int i;
    char *input;

    input = shell_data->arguments[0];
    for (i = 0; input[i]; i++)
    {
        if (input[i] == '.')
        {
            if (input[i + 1] == '.')
                return (0);
            if (input[i + 1] == '/')
                continue;
            else
                break;
        }
        else if (input[i] == '/' && i != 0)
        {
            if (input[i + 1] == '.')
                continue;
            i++;
            break;
        }
        else
            break;
    }
    if (i == 0)
        return (0);

    if (stat(input + i, &st) == 0)
    {
        return (i);
    }
    get_error(shell_data, 127);
    return (-1);
}

/**
 * is_cdir - checks ":" if it is in the current directory.
 * @path: type char pointer to char.
 * @i: type int pointer to index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir(char *path, int *i)
{
    if (path[*i] == ':')
        return (1);

    while (path[*i] != ':' && path[*i])
    {
        *i += 1;
    }

    if (path[*i])
        *i += 1;

    return (0);
}

/**
 * _which - locates a command
 *
 * @cmd: command name
 * @shell_data: data structure
 * Return: location of the command.
 */
char *_which(char *cmd, shell_data_t *shell_data)
{
    char *path, *ptr_path, *token_path, *dir;
    int len_dir, len_cmd, i;
    struct stat st;

    path = get_environment_variable("PATH", shell_data->shell_env);
    if (path)
    {
        ptr_path = string_duplicate(path);
        len_cmd = string_length(cmd);
        token_path = strtok(ptr_path, ":");
        i = 0;
        while (token_path != NULL)
        {
            if (is_cdir(path, &i))
                if (stat(cmd, &st) == 0)
                    return (cmd);
            len_dir = string_length(token_path);
            dir = malloc(len_dir + len_cmd + 2);
            concatenate_strings(dir, token_path);
            concatenate_strings(dir, "/");
            concatenate_strings(dir, cmd);
            if (stat(dir, &st) == 0)
            {
                free(ptr_path);
                return (dir);
            }
            free(dir);
            token_path = strtok(NULL, ":");
        }
        free(ptr_path);
        if (stat(cmd, &st) == 0)
            return (cmd);
        return (NULL);
    }
    if (cmd[0] == '/')
        if (stat(cmd, &st) == 0)
            return (cmd);
    return (NULL);
}

/**
 * cmd_exec - executes command lines
 *
 * @shell_data: data relevant (arguments and command line)
 * Return: 1 on success.
 */
int cmd_exec(shell_data_t *shell_data)
{
    pid_t pd;
    pid_t wpd;
    int state;
    int exec;
    char *dir;
    (void)wpd;

    exec = is_executable(shell_data);
    if (exec == -1)
        return (1);
    if (exec == 0)
    {
        dir = _which(shell_data->arguments[0], shell_data);
        if (check_error_cmd(dir, shell_data) == 1)
            return (1);
    }

    pd = fork();
    if (pd == 0)
    {
        if (exec == 0)
            dir = _which(shell_data->arguments[0], shell_data);
        else
            dir = shell_data->arguments[0];
        execve(dir + exec, shell_data->arguments, shell_data->shell_env);
    }
    else if (pd < 0)
    {
        perror(shell_data->arguments[0]);
        return (1);
    }
    else
    {
        do
        {
            wpd = waitpid(pd, &state, WUNTRACED);
        } while (!WIFEXITED(state) && !WIFSIGNALED(state));
    }

    shell_data->last_status = state / 256;
    return (1);
}
