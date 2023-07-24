/**
 *Write a function that splits a string and returns an array of each word of the string.

man strtok

#advanced: Write the function without strtok

*To split a string into words and return an array of each word, you can use the strtok function from the C standard library. However *please note that the strtok function modifies the original input string.
* If you want to preserve the original string, you can create a copy and work on that.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split_string_with_strtok(const char* input_string, const char* delimiter, int* num_words) {
    char* input_copy = strdup(input_string); // Create a copy to avoid modifying the original
    if (!input_copy) {
        perror("Error allocating memory");
        return NULL;
    }

    char* token = strtok(input_copy, delimiter);
    int max_words = 10; // You can adjust this value as needed
    char** words = malloc(max_words * sizeof(char*));
    int count = 0;

    while (token != NULL) {
        words[count] = strdup(token);
        count++;
        token = strtok(NULL, delimiter);

        if (count >= max_words) {
            max_words *= 2;
            words = realloc(words, max_words * sizeof(char*));
            if (!words) {
                perror("Error reallocating memory");
                return NULL;
            }
        }
    }

    free(input_copy);
    *num_words = count;
    return words;
}

// Function to free the memory allocated for the word array
void free_words(char** words, int num_words) {
    for (int i = 0; i < num_words; i++) {
        free(words[i]);
    }
    free(words);
}

int main() {
    const char* input_string = "Hello, world! This is a test.";
    const char* delimiter = " ,.!"; // Words are split based on these delimiters
    int num_words;

    char** words = split_string_with_strtok(input_string, delimiter, &num_words);

    if (words) {
        printf("Number of words: %d\n", num_words);
        for (int i = 0; i < num_words; i++) {
            printf("%s\n", words[i]);
        }
        free_words(words, num_words);
    }

    return 0;
}

