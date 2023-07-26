#include "main_unique.h"

/**
 * handle_sigint - Handles the SIGINT signal (Ctrl + C) in the shell prompt.
 *
 * @sig: The signal number (unused in this function).
 */
void handle_sigint(int sig)
{
    (void)sig; // Unused parameter, silence compiler warning.
    write(STDOUT_FILENO, "\n^-^ ", 5); // Display a custom message when Ctrl + C is pressed.
}
