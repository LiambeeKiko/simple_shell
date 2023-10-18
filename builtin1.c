#include "shell.h"

/**
 * displayHistory - Display the history list with line numbers.
 * @info: Pointer to the info_t struct containing the history list.
 *
 * Return: Always 0.
 */
int displayHistory(info_t *info)
{
print_list(info->history);
return (0);
}

/**
 * unsetAlias - Unset an alias by removing it from the alias list.
 * @info: Pointer to the info_t struct containing the alias list.
 * @str: The string alias to unset.
 *
 * Return: 0 on success, 1 on error.
 */
int unsetAlias(info_t *info, char *str)
{
char *p, c;
int ret;
p = _strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = delete_node_at_index(&(info->alias), find_node_with_str(info->alias, str));
*p = c;
return (ret);
}

/**
 * setAlias - Set an alias to a string.
 * @info: Pointer to the info_t struct containing the alias list.
 * @str: The string alias to set.
 *
 * Return: 0 on success, 1 on error.
 */
int setAlias(info_t *info, char *str)
{
char *p;
p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unsetAlias(info, str));
unsetAlias(info, str);
return (add_nodeint_end(&(info->alias), str) == NULL);
}

/**
 * printAlias - Print an alias string.
 * @node: Pointer to the alias list node.
 *
 * Return: 0 on success, 1 on error.
 */
int printAlias(const list_t *node)
{
char *p = NULL, *a = NULL;
if (node)
{
p = _strchr(node->str, '=');
for (a = node->str; a <= p; a++)
_putchar(*a);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
 * aliasCommand - Implement the alias command to set or print aliases.
 * @info: Pointer to the info_t struct containing arguments and alias list.
 *
 * Return: Always 0.
 */
int aliasCommand(info_t *info)
{
int i = 0;
char *p = NULL;
const list_t *node = NULL;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
printAlias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
p = _strchr(info->argv[i], '=');
if (p)
setAlias(info, info->argv[i]);
else
printAlias(find_node_with_str(info->alias, info->argv[i]));
}
return (0);
}
