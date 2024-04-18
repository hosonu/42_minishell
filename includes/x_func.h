#ifndef X_FUNC_H
#define X_FUNC_H

#include "./minishell.h"

//x_func.c
pid_t x_fork(void);
void *x_malloc(size_t size);

//x_func_second.c
int x_execve(const char *filename, char *const argv[], char *const envp[]);
int x_access(const char *pathname, int mode);
int x_unlink(const char *pathname);
int x_open(const char *pathname, int flags, mode_t mode);

//x_func_third.c
int x_dup(int oldfd);
int x_dup2(int oldfd, int newfd);
int x_pipe(int pipefd[2]);
int x_close(int fd);

#endif
