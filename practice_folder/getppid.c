#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t parent_pid = getppid();
    pid_t current_pid = getpid();

    printf("Parent PID: %d\n", parent_pid);
    printf("Current PID: %d\n", current_pid);

    return 0;
}

/**
 *Write a program that prints the PID of the parent process.
*Run your program several times within the same shell.
*It should be the same.
*Does echo $$ print the same value? Why?
 */
