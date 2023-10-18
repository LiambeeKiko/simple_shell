#include "shell.h"

/**
 * convertStringToInt - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted integer. If there are no numbers in the string
 *         or an error occurs, it returns -1.
 */
int convertStringToInt(const char *s)
{
int i = 0;
int result = 0;
int sign = 1;
if (s == NULL)
return (-1);
if (s[0] == '-')
{
sign = -1;
i++;
}
else if (s[0] == '+')
{
i++;
}
for (; s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result = result * 10 + (s[i] - '0');
if (result < 0)
return (-1);
}
else
{
return (-1);
}
}
return (result *sign);
}

/**
 * printErrorMessage - Print an error message to standard error.
 * @info: The parameter and return info struct.
 * @errorType: String containing the specified error type.
 *
 * Return: None.
 */
void printErrorMessage(info_t *info, const char *errorType)
{
_eputs(info->fname);
_eputs(": ");
printDecimal(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(errorType);
}

/**
 * printDecimal - Print a decimal (integer) number to a given file descriptor.
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int printDecimal(int input, int fd)
{
int (*printChar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
int i, count = 0;
unsigned int absoluteValue, current;
if (input < 0)
{
absoluteValue = -input;
printChar('-');
count++;
}
else
{
absoluteValue = input;
}
current = absoluteValue;
for (i = 1000000000; i > 1; i /= 10)
{
if (absoluteValue / i)
{
printChar('0' + current / i);
count++;
}
current %= i;
}
printChar('0' + current);
count++;
return (count);
}

/**
 * convertNumberToString - Convert a number to a string.
 * @num: The number to convert.
 * @base: The base of the number system (e.g., 10 for decimal).
 * @flags: Argument flags.
 *
 * Return: The string representation of the number.
 */
char *convertNumberToString(long int num, int base, int flags)
{
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;
if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}
char *digits = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';
do {
*--ptr = digits[n % base];
n /= base;
} while (n != 0);
if (sign)
*--ptr = sign;
return (ptr);
}

/**
 * removeComments - Replace the first instance of '#' with '\0'.
 * @buf: The address of the string to modify.
 *
 * Return: None.
 */
void removeComments(char *buf)
{
int i;
for (i = 0; buf[i] != '\0'; i++)
{
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
}
