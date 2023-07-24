#include <stdio.h>
#include <stdlib.h>

int main() {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t characters_read;

    while (1) {
        printf("$ ");
        fflush(stdout);

        // Read the user's command
        characters_read = getline(&line, &bufsize, stdin);

        // Check if the user entered EOF (Ctrl+D)
        if (characters_read == EOF) {
            printf("\n");
            break;
        }

        // Print the entered command
        printf("%s", line);
    }

    // Free the allocated memory for the line
    free(line);

    return 0;
}

/**
 *Write a program that prints "$ ",
 * wait for the user to enter a command,
 * prints it on the next line.
 */
