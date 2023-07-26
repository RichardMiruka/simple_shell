#include "main_unique.h"
#include <stdlib.h>

/**
 * _realloc_unique - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc_unique(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *newptr;

    if (ptr == NULL)
        return (malloc(new_size));

    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }

    if (new_size == old_size)
        return (ptr);

    newptr = malloc(new_size);
    if (newptr == NULL)
        return (NULL);

    if (new_size < old_size)
        custom_memcpy(newptr, ptr, new_size);
    else
        custom_memcpy(newptr, ptr, old_size);

    free(ptr);
    return (newptr);
}

/**
 * _reallocdp_unique - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdp_unique(char **ptr, unsigned int old_size, unsigned int new_size)
{
    char **newptr;
    unsigned int i;

    if (ptr == NULL)
        return (malloc(sizeof(char *) * new_size));

    if (new_size == old_size)
        return (ptr);

    newptr = malloc(sizeof(char *) * new_size);
    if (newptr == NULL)
        return (NULL);

    for (i = 0; i < old_size; i++)
        newptr[i] = ptr[i];

    free(ptr);

    return (newptr);
}

/**
 * custom_memcpy - copies information between void pointers.
 * @new_pointer: destination pointer.
 * @pointer: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void custom_memcpy(void *new_pointer, const void *pointer, unsigned int size)
{
    char *char_pointer = (char *)pointer;
    char *char_new_pointer = (char *)new_pointer;
    unsigned int i;

    for (i = 0; i < size; i++)
        char_new_pointer[i] = char_pointer[i];
}

