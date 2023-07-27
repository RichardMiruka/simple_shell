#include "main.h"

/**
 * aux_help_env - Help information for the builtin env
 * Return: no return
 */
void aux_help_env(void)
{
    char *help = "env: env [option] [name=value] [command [args]]\n\t";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "Print the environment of the shell.\n";
    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_setenv - Help information for the builtin setenv
 * Return: no return
 */
void aux_help_setenv(void)
{
    char *help = "setenv: setenv (const char *name, const char *value, int replace)\n\t";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "Add a new definition to the environment\n";
    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_general - Entry point for help information for the help builtin
 * Return: no return
 */
void aux_help_general(void)
{
    char *help = "^-^ bash, version 1.0(1)-release\n";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "These commands are defined internally. Type 'help' to see the list";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "Type 'help name' to find out more about the function 'name'.\n\n ";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "alias: alias [name=['string']]\n";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "exit: exit [n]\n";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "env: env [option] [name=value] [command [args]]\n";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "setenv: setenv [variable] [value]\n";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "unsetenv: unsetenv [variable]\n";
    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_exit - Help information for the builtin exit
 * Return: no return
 */
void aux_help_exit(void)
{
    char *help = "exit: exit [n]\n Exit shell.\n";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "Exits the shell with a status of N. If N is omitted, the exit";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "status is that of the last command executed\n";
    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_unsetenv - Help information for the builtin unsetenv
 * Return: no return
 */
void aux_help_unsetenv(void)
{
    char *help = "unsetenv: unsetenv (const char *name)\n\t";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "Remove an entry completely from the environment\n";
    write(STDOUT_FILENO, help, _strlen(help));
}
