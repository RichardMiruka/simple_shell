#include "main.h"

/* custom_strdup - Implementation of strdup function */
char *custom_strdup(const char *s)
{
    char *duplicate;
    int len, i;

    len = _strlen(s);
    duplicate = malloc(len + 1);
    if (!duplicate)
        return NULL;

    for (i = 0; i < len; i++)
        duplicate[i] = s[i];
    duplicate[len] = '\0';

    return duplicate;
}

/* custom_strlen - Implementation of strlen function */
int custom_strlen(const char *s)
{
    int len = 0;

    while (*s != '\0')
    {
        s++;
        len++;
    }

    return len;
}

/* custom_cmp_chars - Compare characters in a string with a delimiter */
int custom_cmp_chars(char str[], const char *delim)
{
    int i, j;

    for (i = 0; str[i]; i++)
    {
        for (j = 0; delim[j]; j++)
        {
            if (str[i] == delim[j])
                return 1;
        }
    }

    return 0;
}

/* custom_strtok - Implementation of strtok function */
char *custom_strtok(char str[], const char *delim)
{
    static char *ptr;
    int i, j, start, end;

    if (str)
        ptr = str;

    if (*ptr == '\0')
        return NULL;

    while (custom_cmp_chars(ptr, delim))
        ptr++;

    start = 0;
    while (ptr[start])
    {
        for (i = 0; delim[i]; i++)
        {
            if (ptr[start] == delim[i])
                break;
        }
        if (!delim[i])
            break;
        start++;
    }

    end = start;
    while (ptr[end])
    {
        for (j = 0; delim[j]; j++)
        {
            if (ptr[end] == delim[j])
                break;
        }
        if (delim[j])
            break;
        end++;
    }

    if (ptr[start] == '\0')
        return NULL;

    ptr[end] = '\0';
    return ptr + start;
}

/* custom_isdigit - Check if a string represents a valid integer */
int custom_isdigit(const char *s)
{
    int i = 0;

    if (s[i] == '-' || s[i] == '+')
        i++;

    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return 0;
        i++;
    }

    return 1;
}
