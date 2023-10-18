#include "shell.h"

/**
 * getListLength - Determines the length of a linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t getListLength(const list_t *head)
{
size_t size = 0;
while (head)
{
head = head->next;
size++;
}
return (size);
}

/**
 * listToStringArray - Returns an array of strings from the list->str.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **listToStringArray(list_t *head)
{
list_t *node = head;
size_t size = getListLength(head);
char **strArray;
char *str;
size_t i, j;
if (!head || !size)
return (NULL);
strArray = malloc(sizeof(char *) * (size + 1));
if (!strArray)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strArray[j]);
free(strArray);
return (NULL);
}
_strcpy(str, node->str);
strArray[i] = str;
}
strArray[i] = NULL;
return (strArray);
}

/**
* printListWithNumbers .
* @head: Pointer to the first node.
*
* Return: Size of the list.
*/
size_t printListWithNumbers(const list_t *head)
{
size_t size = 0;
while (head)
{
_puts(convertNumberToString(head->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(head->str ? head->str : "(nil)");
_puts("\n");
head = head->next;
size++;
}
return (size);
}

/**
* findNodeWithPrefix - Returns the node whose string starts with a prefix.
* @head: Pointer to list head.
* @prefix: String to match.
* @nextChar: The next character after the prefix to match.
*
* Return: Matching node or NULL.
*/
list_t *findNodeWithPrefix(list_t *head, char *prefix, char nextChar)
{
char *p = NULL;
while (head)
{
p = startsWith(head->str, prefix);
if (p && ((nextChar == -1) || (*p == nextChar)))
return (head);
head = head->next;
}
return (NULL);
}

/**
* getNodeIndex - Gets the index of a node.
* @head: Pointer to list head.
* @node: Pointer to the node.
*
* Return: Index of the node or -1.
*/
ssize_t getNodeIndex(list_t *head, list_t *node)
{
size_t index = 0;
while (head)
{
if (head == node)
return (index);
head = head->next;
index++;
}
return (-1);
}
