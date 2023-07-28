#include "main.h"

/* custom_rev_string - Reverse a string in place */
void custom_rev_string(char *s)
{
    int len, i;
    char temp;

    len = custom_strlen(s);
    for (i = 0; i < len / 2; i++)
    {
        temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}
