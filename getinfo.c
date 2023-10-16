#include "shell.h"

/**
 * getHistoryFilePath - Returns the path to the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file path.
 */
char *getHistoryFilePath(info_t *info) {
    char *homeDir, *historyPath;

    homeDir = _getenv(info, "HOME");
    if (!homeDir)
        return (NULL);

    historyPath = malloc(sizeof(char) * (_strlen(homeDir) + _strlen(HIST_FILE) + 2));
    if (!historyPath)
        return (NULL);

    historyPath[0] = 0;
    _strcpy(historyPath, homeDir);
    _strcat(historyPath, "/");
    _strcat(historyPath, HIST_FILE);

    return (historyPath);
}

/**
 * writeHistoryToFile - Writes the history to a file.
 * @info: The parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int writeHistoryToFile(info_t *info) {
    int fd;
    char *filename = getHistoryFilePath(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return (-1);

    for (node = info->history; node; node = node->next) {
        _putsToFileDescriptor(node->str, fd);
        _putcharToFileDescriptor('\n', fd);
    }
    _putcharToFileDescriptor(BUF_FLUSH, fd);
    close(fd);

    return (1);
}

/**
 * readHistoryFromFile - Reads history from a file.
 * @info: The parameter struct.
 *
 * Return: The number of lines read from the history file on success, 0 on failure.
 */
int readHistoryFromFile(info_t *info) {
    int i, last = 0, lineCount = 0;
    int fd;
    ssize_t bytesRead, fileSize = 0;
    struct stat st;
    char *buffer = NULL, *filename = getHistoryFilePath(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return (0);

    if (!fstat(fd, &st))
        fileSize = st.st_size;

    if (fileSize < 2)
        return (0);

    buffer = malloc(sizeof(char) * (fileSize + 1));

    if (!buffer)
        return (0);

    bytesRead = read(fd, buffer, fileSize);
    buffer[fileSize] = 0;

    if (bytesRead <= 0) {
        free(buffer);
        close(fd);
        return (0);
    }

    close(fd);

    for (i = 0; i < fileSize; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = 0;
            buildHistoryList(info, buffer + last, lineCount++);
            last = i + 1;
        }
    }

    if (last != i)
        buildHistoryList(info, buffer + last, lineCount++);

    free(buffer);
    info->histCount = lineCount;

    while (info->histCount >= HIST_MAX)
        deleteNodeAtIndex(&(info->history), 0);

    renumberHistory(info);

    return (info->histCount);
}

/**
 * buildHistoryList - Adds an entry to the history linked list.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @lineCount: The history line count.
 *
 * Return: Always 0.
 */
int buildHistoryList(info_t *info, char *buf, int lineCount) {
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    addNodeEnd(&node, buf, lineCount);

    if (!info->history)
        info->history = node;

    return (0);
}

/**
 * renumberHistory - Renumbers the history linked list after changes.
 * @info: Parameter struct.
 *
 * Return: The new histCount.
 */
int renumberHistory(info_t *info) {
    list_t *node = info->history;
    int i = 0;

    while (node) {
        node->num = i++;
        node = node->next;
    }

    return (info->histCount = i);
}
