#include "main.h"

/* custom_memcpy - Implementation of memcpy function */
void custom_memcpy(void *newptr, const void *ptr, unsigned int size)
{
    char *dest = newptr;
    const char *src = ptr;

    while (size--)
        *dest++ = *src++;
}

/* custom_realloc - Implementation of realloc function */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;
    unsigned int copy_size;

    if (new_size <= old_size)
        return ptr;

    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    copy_size = (old_size < new_size) ? old_size : new_size;
    custom_memcpy(new_ptr, ptr, copy_size);
    free(ptr);

    return new_ptr;
}

/* custom_reallocdp - Reallocate a double pointer */
char **custom_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
    char **new_ptr;
    unsigned int i;

    if (new_size <= old_size)
        return ptr;

    new_ptr = malloc(new_size * sizeof(char *));
    if (!new_ptr)
        return NULL;

    for (i = 0; i < old_size; i++)
        new_ptr[i] = ptr[i];

    free(ptr);
    return new_ptr;
}


