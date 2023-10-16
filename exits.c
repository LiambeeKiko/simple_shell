#include "shell.h"

/**
 * copyStringWithLimit - Copies a string with a specified character limit.
 * @destination: The destination string to copy to.
 * @source: The source string to copy from.
 * @limit: The maximum number of characters to copy.
 *
 * Return: The concatenated string.
 */
char *copyStringWithLimit(char *destination, const char *source, int limit)
{
int i;
for (i = 0; source[i] != '\0' && i < limit - 1; i++)
{
destination[i] = source[i];
}
destination[i] = '\0';
return (destination);
}

/**
 * concatenateStringWithLimit - Concatenates two strings with a character limit.
 * @destination: The first string.
 * @source: The second string.
 * @limit: The maximum number of characters to use for concatenation.
 *
 * Return: The concatenated string.
 */
char *concatenateStringWithLimit(char *destination, const char *source, int limit)
{
int i, j;
for (i = 0; destination[i] != '\0'; i++)
{
}
for (j = 0; source[j] != '\0' && i < limit - 1; i++, j++)
{
destination[i] = source[j];
}
destination[i] = '\0';
return (destination);
}

/**
 * findCharacterInString - Locates a character in a string.
 * @str: The string to be parsed.
 * @character: The character to look for.
 *
 * Return: A pointer to the memory area containing the character.
 */
char *findCharacterInString(const char *str, char character)
{
while (*str != '\0')
{
if (*str == character)
{
return ((char *)str);
}
str++;
}
return (NULL);
}
