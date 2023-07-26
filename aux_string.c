#include "main_unique.h"

/**
 * _strchr - locates a character in a string.
 * @s: The string to search.
 * @c: The character to find.
 *
 * Return: A pointer to the first occurrence of the character c in the string s,
 *         or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
    unsigned int i = 0;

    for (; *(s + i) != '\0'; i++)
    {
        if (*(s + i) == c)
            return (s + i);
    }

    if (*(s + i) == c)
        return (s + i);

    return ('\0');
}

/**
 * _strspn - gets the length of a prefix substring.
 * @s: The initial segment.
 * @accept: The accepted bytes.
 *
 * Return: The number of accepted bytes at the beginning of s.
 */
int _strspn(char *s, char *accept)
{
    int i, j, bool;

    for (i = 0; *(s + i) != '\0'; i++)
    {
        bool = 1;
        for (j = 0; *(accept + j) != '\0'; j++)
        {
            if (*(s + i) == *(accept + j))
            {
                bool = 0;
                break;
            }
        }

        if (bool == 1)
            break;
    }

    return (i);
}

/**
 * _strcmp - compares two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: 0 if the strings are equal, a negative value if s1 is less than s2,
 *         and a positive value if s1 is greater than s2.
 */
int _strcmp(char *s1, char *s2)
{
    int i;

    for (i = 0; s1[i] == s2[i] && s1[i]; i++)
        ;

    if (s1[i] > s2[i])
        return (1);
    if (s1[i] < s2[i])
        return (-1);

    return (0);
}

/**
 * _strcat - concatenates two strings.
 * @dest: The destination buffer to store the result.
 * @src: The source string to be appended to the destination.
 *
 * Return: A pointer to the destination string (dest).
 */
char *_strcat(char *dest, const char *src)
{
    int i;
    int j;

    for (i = 0; dest[i] != '\0'; i++)
        ;

    for (j = 0; src[j] != '\0'; j++)
    {
        dest[i] = src[j];
        i++;
    }

    dest[i] = '\0';
    return (dest);
}

/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: The destination buffer to store the copied string.
 * @src: The source string to be copied.
 *
 * Return: A pointer to the destination string (dest).
 */
char *_strcpy(char *dest, char *src)
{
    size_t a;

    for (a = 0; src[a] != '\0'; a++)
    {
        dest[a] = src[a];
    }

    dest[a] = '\0';

    return (dest);
}

