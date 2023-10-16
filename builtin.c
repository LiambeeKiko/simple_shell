#include "shell.h"

/**
 * exitShell - Exit the shell.
 * @info: Pointer to the info_t struct.
 *
 * Return: Exits with the specified exit status (0 if info->argv[0] is not "exit").
 */
int exitShell(info_t *info) {
    int exitStatus;

    if (info->argv[1]) {
        exitStatus = convert_number(info->argv[1], CONVERT_LOWERCASE | CONVERT_UNSIGNED);

        if (exitStatus == -1) {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return (1);
        }

        info->err_num = exitStatus;
        return (-2);
    }

    info->err_num = -1;
    return (-2);
}

/**
 * changeDirectory - Change the current directory of the process.
 * @info: Pointer to the info_t struct.
 *
 * Return: Always 0.
 */
int changeDirectory(info_t *info) {
    char *currentDir, *newDir, buffer[1024];
    int chdir_ret;

    currentDir = getcwd(buffer, 1024);

    if (!currentDir)
        _eputs("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1]) {
        newDir = _getenv(info, "HOME");
        if (!newDir)
            chdir_ret = _mychdir((newDir = _getenv(info, "PWD")) ? newDir : "/");
        else
            chdir_ret = _mychdir(newDir);
    } else if (_strcmp(info->argv[1], "-") == 0) {
        if (!_getenv(info, "OLDPWD")) {
            _puts(currentDir);
            _eputchar('\n');
            return (1);
        }

        _puts(_getenv(info, "OLDPWD"));
        _eputchar('\n');
        chdir_ret = _mychdir((newDir = _getenv(info, "OLDPWD")) ? newDir : "/");
    } else {
        chdir_ret = _mychdir(info->argv[1]);
    }

    if (chdir_ret == -1) {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    } else {
        _setenv(info, "OLDPWD", _getenv(info, "PWD"));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }

    return (0);
}

/**
 * showHelp - Display help information.
 * @info: Pointer to the info_t struct.
 *
 * Return: Always 0.
 */
int showHelp(info_t *info) {
    char **arg_array;

    arg_array = info->argv;
    _puts("help call works. Function not yet implemented\n");

    if (arg_array)
        _puts(*arg_array);

    return (0);
}
