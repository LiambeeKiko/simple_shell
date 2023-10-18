#include "shell.h"

/**
 * displayEnvironment - Display the current environment variables.
 * @info: Pointer to the info_t struct containing the environment list.
 *
 * Return: Always 0.
 */
int displayEnvironment(const info_t *info)
{
print_list(info->env);
return (0);
}

/**
 * getenvValue - Get the value of an environment variable by name.
 * @info: Pointer to the info_t struct containing the environment list.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *getenvValue(const info_t *info, const char *name)
{
list_t *node = info->env;
char *p;
while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
 * setEnvironmentVariable - Initialize a new environment variable or modify an existing one.
 * @info: Pointer to the info_t struct containing potential arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int setEnvironmentVariable(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguments\n");
return (1);
}
if (_setenv(info, info->argv[1], info->argv[2]) == 0)
return (0);
return (1);
}

/**
 * unsetEnvironmentVariable - Remove an environment variable.
 * @info: Pointer to the info_t struct containing potential arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int unsetEnvironmentVariable(info_t *info)
{
int i;
if (info->argc == 1)
{
_eputs("Too few arguments.\n");
return (1);
}
for (i = 1; i < info->argc; i++)
_unsetenv(info, info->argv[i]);
return (0);
}

/**
 * populateEnvironmentList - Populate the environment linked list.
 * @info: Pointer to the info_t struct containing potential arguments.
 *
 * Return: Always 0.
 */
int populateEnvironmentList(info_t *info)
{
list_t *node = NULL;
size_t i;
for (i = 0; environ[i]; i++)
add_nodeint_end(&node, environ[i], 0);
info->env = node;
return (0);
}
