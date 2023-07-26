#include "main_unique.h"

/**
 * handle_sigint - Signal handler for SIGINT (Ctrl+C)
 *
 * @sig: Signal number (unused)
 */
void handle_sigint(int sig)
{
    (void)sig; // Unused parameter, silence compiler warning.
    write(STDOUT_FILENO, "\n$ ", 3);
    fflush(stdout);
}

