#include "shell.h"

/**
 * is_cmd - Checks if a file is an executable command.
 * @info: Pointer to the info struct (unused).
 * @path: Path to the file.
 *
 * Return: (1) if the file is an executable command, (0) otherwise.
 */
;
int is_cmd(info_t *info, char *path)
{
	struct stat st;
	if (!path || stat(path, &st) != 0)
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * find_path - Finds the full path of a command in the PATH string.
 * @info: Pointer to the info struct (unused).
 * @pathstr: The PATH string containing colon-separated directories.
 * @cmd: The command to find.
 *
 * Return: The full path of the command if found, or (NULL) if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	(void)info;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);

			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
