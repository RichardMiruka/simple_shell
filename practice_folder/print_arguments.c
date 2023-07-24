#include <stdio.h>

int main(int argc, char **argv) {
    // Start with index 1 to skip the program name (av[0])
    int i = 1;

    // Loop through the av array until a NULL pointer is encountered
    while (argv[i] != NULL) {
        printf("%s\n", argv[i]);
        i++;
    }

    return 0;
}

//Write a program that prints all the arguments, without using ac.//
