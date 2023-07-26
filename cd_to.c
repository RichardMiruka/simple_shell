#include "main_unique.h"

/**
 * cd_to - Change the working directory to the given directory.
 *
 * @datash: Pointer to the shell_data_t struct.
 * Return: No return value.
 */
void cd_to(shell_data_t *datash)
{
    char pwd[PATH_MAX];
    char *dir, *cp_pwd, *cp_dir;

    getcwd(pwd, sizeof(pwd));

    dir = datash->arguments[1];
    if (chdir(dir) == -1)
    {
        get_error(datash, 2); /* Display error message */
        return;
    }

    cp_pwd = _strdup(pwd);
    set_env("OLDPWD", cp_pwd, datash); /* Update OLDPWD */

    cp_dir = _strdup(dir);
    set_env("PWD", cp_dir, datash); /* Update PWD */

    free(cp_pwd);
    free(cp_dir);

    datash->last_status = 0; /* Update last status */

    getcwd(pwd, sizeof(pwd)); /* Update pwd to handle relative paths */
}

/**
 * cd_dot - Change the working directory to the parent directory.
 *
 * @datash: Pointer to the shell_data_t struct.
 * Return: No return value.
 */
void cd_dot(shell_data_t *datash)
{
    char pwd[PATH_MAX];
    char *dir, *cp_pwd, *cp_strtok_pwd;

    getcwd(pwd, sizeof(pwd));
    cp_pwd = _strdup(pwd);
    set_env("OLDPWD", cp_pwd, datash); /* Update OLDPWD */

    dir = datash->arguments[1];
    if (_strcmp(".", dir) == 0)
    {
        set_env("PWD", cp_pwd, datash); /* Update PWD if directory is "." */
        free(cp_pwd);
        return;
    }
    if (_strcmp("/", cp_pwd) == 0)
    {
        free(cp_pwd);
        return; /* Can't go to parent directory from root */
    }

    cp_strtok_pwd = cp_pwd;
    reverse_string(cp_strtok_pwd);
    cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
    if (cp_strtok_pwd != NULL)
    {
        cp_strtok_pwd = _strtok(NULL, "\0");

        if (cp_strtok_pwd != NULL)
            reverse_string(cp_strtok_pwd);
    }
    if (cp_strtok_pwd != NULL)
    {
        chdir(cp_strtok_pwd);
        set_env("PWD", cp_strtok_pwd, datash); /* Update PWD */
    }
    else
    {
        chdir("/");
        set_env("PWD", "/", datash); /* Update PWD to root */
    }

    free(cp_pwd);
    datash->last_status = 0; /* Update last status */

    getcwd(pwd, sizeof(pwd)); /* Update pwd to handle relative paths */
}

/**
 * cd_to_home - Change the working directory to the user's home directory.
 *
 * @datash: Pointer to the shell_data_t struct.
 * Return: No return value.
 */
void cd_to_home(shell_data_t *datash)
{
    char *p_pwd, *home;
    char pwd[PATH_MAX];

    getcwd(pwd, sizeof(pwd));
    p_pwd = _strdup(pwd);

    home = _getenv("HOME", datash->shell_env);
    if (home == NULL)
    {
        set_env("OLDPWD", p_pwd, datash); /* Update OLDPWD */
        free(p_pwd);
        return;
    }

    if (chdir(home) == -1)
    {
        get_error(datash, 2); /* Display error message */
        free(p_pwd);
        return;
    }

    set_env("OLDPWD", p_pwd, datash); /* Update OLDPWD */
    set_env("PWD", home, datash); /* Update PWD */

    free(p_pwd);
    datash->last_status = 0; /* Update last status */

    getcwd(pwd, sizeof(pwd)); /* Update pwd to handle relative paths */
}

/**
 * cd_previous - Change the working directory to the previous directory.
 *
 * @datash: Pointer to the shell_data_t struct.
 * Return: No return value.
 */
void cd_previous(shell_data_t *datash)
{
    char pwd[PATH_MAX];
    char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

    getcwd(pwd, sizeof(pwd));
    cp_pwd = _strdup(pwd);

    p_oldpwd = _getenv("OLDPWD", datash->shell_env);
    if (p_oldpwd == NULL)
        cp_oldpwd = cp_pwd;
    else
        cp_oldpwd = _strdup(p_oldpwd);

    set_env("OLDPWD", cp_pwd, datash); /* Update OLDPWD */

    if (chdir(cp_oldpwd) == -1)
        set_env("PWD", cp_pwd, datash);
    else
        set_env("PWD", cp_oldpwd, datash); /* Update PWD */

    p_pwd = _getenv("PWD", datash->shell_env);
    write(STDOUT_FILENO, p_pwd, _strlen(p_pwd)); /* Print PWD */
    write(STDOUT_FILENO, "\n", 1);

    free(cp_pwd);
    if (p_oldpwd)
        free(cp_oldpwd);

    datash->last_status = 0; /* Update last status */

    getcwd(pwd, sizeof(pwd)); /* Update pwd to handle relative paths */
}

