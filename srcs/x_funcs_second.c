#include "../includes/minishell.h"

int x_execve(const char *filename, char *const argv[], char *const envp[])
{
    int result = execve(filename, argv, envp);
    if (result == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }
    return result;
}

int x_access(const char *pathname, int mode) 
{
    int result = access(pathname, mode);
    if (result == -1) {
        perror("access");
        exit(EXIT_FAILURE);
    }
    return result;
}

int x_unlink(const char *pathname)
{
    int result = unlink(pathname);
    if (result == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }
    return result;
}

int x_open(const char *pathname, int flags, mode_t mode)
{
    int result = open(pathname, flags, mode);
    if (result == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    return result;
}

int x_close(int fd)
{
    int result = close(fd);
    if (result == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
    return result;
}