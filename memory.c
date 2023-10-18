#include "shell.h"

/**
 * bfree - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 *
 * This function frees the memory pointed to by 'ptr' and then sets the pointer
 * itself to NULL to avoid any dangling references.
 *
 * Return: 1 if memory was freed, 0 if 'ptr' was already NULL.
 */
int free_and_null(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
