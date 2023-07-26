#ifndef _MAIN_UNIQUE_H_
#define _MAIN_UNIQUE_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

/* Define unique constants and macros */

#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 128
#define TOKEN_DELIMITER " \t\r\n\a"

/* Points to an array of pointers to strings representing environment variables */
extern char **my_environ;

/* Structure to store command lines in a singly linked list */

typedef struct command_line_list
{
    char *line;
    struct command_line_list *next;
} command_line_list_t;

/* Structure to hold data relevant to the shell's runtime */

/* Function declarations */
char *unique_read_line(int *i_eof);

typedef struct shell_data
{
    char **arguments;   /* Tokenized command line arguments */
    char *command_line; /* Command line entered by the user */
    int last_status;    /* Last status of the shell */
    int line_counter;   /* Lines counter */
    char **shell_env;   /* Environment variable */
    char *shell_pid;    /* Process ID of the shell */
} shell_data_t;

/* Structure to store variables in a singly linked list */

typedef struct replace_var_list
{
    int variable_length;
    char *variable;
    int value_length;
    struct replace_var_list *next;
} replace_var_list_t;

/* Structure for built-in commands */

typedef struct builtin_command
{
    char *name;
    int (*function)(shell_data_t *shell_data);
} builtin_command_t;

/* get_help.c */
int get_help(shell_data_t *shell_data);

/* aux_help2.c */
void auxiliary_help(void);
void auxiliary_help_alias(void);
void auxiliary_help_cd(void);

/* aux_help.c */
void auxiliary_help_env(void);
void auxiliary_help_setenv(void);
void auxiliary_help_unsetenv(void);
void auxiliary_help_general(void);
void auxiliary_help_exit(void);

/* get_sigint.c */
void get_sigint_handler(int sig);

/* get_error.c */
int get_error(shell_data_t *shell_data, int evaluation);

/* aux_error2.c */
char *error_get_alias_name(char **arguments);
char *error_environment_variable(shell_data_t *shell_data);
char *error_syntax(char **arguments);
char *error_permission(char **arguments);
char *error_command_not_found(shell_data_t *shell_data);

/* aux_error1.c */
char *concatenate_paths(shell_data_t *shell_data, char *path1, char *path2, char *path3);
char *error_get_current_directory(shell_data_t *shell_data);
char *error_invalid_command(shell_data_t *shell_data);
char *error_exit_shell(shell_data_t *shell_data);

/* aux_stdlib.c */
int get_number_length(int number);
char *integer_to_string(int number);
int string_to_integer(char *string);

/* _exit.c */
int shell_exit(shell_data_t *shell_data);

/* get_builtin */
int (*get_builtin_command(char *command))(shell_data_t *shell_data);

/* cd_shell.c */
int change_directory(shell_data_t *shell_data);

/* cd.c */
void change_to_current_directory(shell_data_t *shell_data);
void change_to_directory(shell_data_t *shell_data);
void change_to_previous_directory(shell_data_t *shell_data);
void change_to_home_directory(shell_data_t *shell_data);

/* env2.c */
char *copy_information(char *name, char *value);
void set_environment_variable(char *name, char *value, shell_data_t *shell_data);
int setenv_command(shell_data_t *shell_data);
int unsetenv_command(shell_data_t *shell_data);

/* env1.c */
char *get_environment_variable(const char *name, char **environment);
int env_command(shell_data_t *shell_data);

/* cmd_exec.c */
int is_current_directory(char *path, int *index);
char *find_executable(char *command, char **environment);
int is_executable_command(shell_data_t *shell_data);
int check_command_error(char *directory, shell_data_t *shell_data);
int execute_command(shell_data_t *shell_data);

/* exec_line */
int execute_line(shell_data_t *shell_data);

/* get_line.c */
void extract_line(char **line_pointer, size_t *length, char *buffer, size_t buffer_length);
ssize_t get_line(char **line_pointer, size_t *length, FILE *stream);

/* replace_var.c */
void check_environment_variable(replace_var_list_t **head, char *input, shell_data_t *shell_data);
int check_variables(replace_var_list_t **head, char *input, char *start, shell_data_t *shell_data);
char *replace_input(replace_var_list_t **head, char *input, char *new_input, int new_length);
char *replace_variable(char *input, shell_data_t *shell_data);

/* split.c */
char *swap_characters(char *input, int should_swap);
void add_nodes(command_line_list_t **separators_list, command_line_list_t **lines_list, char *input);
void go_to_next(command_line_list_t **separators_list, command_line_list_t **lines_list, shell_data_t *shell_data);
int split_commands(shell_data_t *shell_data, char *input);
char **split_line(char *input);

/* check_syntax_error.c */
int has_repeated_characters(char *input, int index);
int has_syntax_error_in_separator(char *input, int index, char last_separator);
int find_first_character(char *input, int *index);
void print_syntax_error(shell_data_t *shell_data, char *input, int index, int is_redirection);
int check_syntax_error(shell_data_t *shell_data, char *input);

/* read_line.c */
char *read_input_line(int *is_end_of_file);

/* shell_loop.c */
char *remove_comments(char *input);
void run_shell_loop(shell_data_t *shell_data);

/* aux_memory.c */
void custom_memcpy(void *new_pointer, const void *pointer, unsigned int size);
void *custom_realloc(void *pointer, unsigned int old_size, unsigned int new_size);
char **custom_reallocate_double_pointer(char **pointer, unsigned int old_size, unsigned int new_size);

/* aux_string3.c */
void reverse_string(char *string);

/* aux_lists2.c */
replace_var_list_t *add_replace_variable_node(replace_var_list_t **head, int variable_length, char *variable, int value_length);
void free_replace_variable_list(replace_var_list_t **head);

/* aux_lists.c */
command_line_list_t *add_separator_node_end(command_line_list_t **head, char separator);
void free_separator_list(command_line_list_t **head);
command_line_list_t *add_line_node_end(command_line_list_t **head, char *line);
void free_line_list(command_line_list_t **head);

/* aux_string.c */
char *concatenate_strings(char *destination, const char *source);
char *copy_string(char *destination, char *source);
int compare_strings(char *string1, char *string2);
char *find_character(char *string, char character);
int is_digit(const char *string);

/* aux_string2.c */
char *string_duplicate(const char *string);
int string_length(const char *string);
char *find_character(char *string, char character);
int string_span(char *string, char *characters);

#endif
