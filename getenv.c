#include "shell.h"

/**
 * copyEnvironToCharArray - Returns a copy of the environment variables as an array of strings.
 * @info: Parameter struct.
 *
 * Return: Array of strings representing the environment variables.
 */
char **copyEnvironToCharArray(info_t *info) {
    if (!info->environ || info->env_changed) {
        info->environ = list_to_array(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * unsetEnvironmentVariable - Remove an environment variable.
 * @info: Parameter struct.
 * @variable: The environment variable to remove.
 *
 * Return: 1 on successful removal, 0 otherwise.
 */
int unsetEnvironmentVariable(info_t *info, const char *variable) {
    list_t *node = info->env;
    unsigned int index = 0;
    const char *p;

    if (!node || !variable)
        return (0);

    while (node) {
        p = starts_with(node->str, variable);
        if (p && *p == '=') {
            info->env_changed = delete_node_at_index(&(info->env), index);
            index = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        index++;
    }

    return (info->env_changed);
}

/**
 * setEnvironmentVariable - Initialize a new environment variable or modify an existing one.
 * @info: Parameter struct.
 * @variable: The environment variable property.
 * @value: The environment variable value.
 *
 * Return: 0 on success, 1 on failure.
 */
int setEnvironmentVariable(info_t *info, char *variable, char *value) {
    char *buffer = NULL;
    list_t *node;
    char *p;

    if (!variable || !value)
        return (1);

    buffer = malloc(_strlen(variable) + _strlen(value) + 2);
    if (!buffer)
        return (1);

    _strcpy(buffer, variable);
    _strcat(buffer, "=");
    _strcat(buffer, value);

    node = info->env;
    while (node) {
        p = starts_with(node->str, variable);
        if (p && *p == '=') {
            free(node->str);
            node->str = buffer;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }

    add_nodeint_end(&(info->env), 0);
    info->env_changed = 1;
    return (0);
}
