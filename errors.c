#include "shell.h"

/**
 * printToStderr - Prints a string to the standard error stream.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void printToStderr(const char *str)
{
if (!str)
return;
while (*str != '\0')
{
writeCharToStderr(*str++);
}
}

/**
 * writeCharToStderr - Writes a character to the standard error stream.
 * @c: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int writeCharToStderr(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
 * writeCharToFileDescriptor - Writes a character to a given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int writeCharToFileDescriptor(char c, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
 * printStringToFileDescriptor - Prints a string to a given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int printStringToFileDescriptor(const char *str, int fd)
{
int i = 0;
if (!str)
return (0);
while (*str)
{
i += writeCharToFileDescriptor(*str++, fd);
}
return (i);
}
