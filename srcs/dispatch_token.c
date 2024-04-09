
#include "../includes/minishell.h"

void    dispatch_token_help(t_token **list, t_fdgs *fdgs, int i)
{
    int pid;

    fdgs->original_stdin = x_dup(STDIN_FILENO);
    fdgs->original_stdout = x_dup(STDOUT_FILENO);
    manage_gfdin(fdgs->gfd, list[i]);
    manage_pipein(fdgs->pp, list[i]);
    pid = x_fork();
    if (pid == 0)
    {
        manage_gfdout(fdgs->gfd, list[i]);
        manage_pipeout(fdgs->pp, list[i]);
        execve_token(list[i]);
    }
    else if (pid > 0)
    {
        x_dup2(fdgs->original_stdin, STDIN_FILENO);
        x_dup2(fdgs->original_stdout, STDOUT_FILENO);
        x_close(fdgs->original_stdin);
        x_close(fdgs->original_stdout);
        if(list[i]->type == HEREDOCCOMMAND || list[i]->type == REOUTHEREDOCCOMMAND)
        {
            x_unlink("/tmp/sh-thd-tekitou");
        }
    }
}

void dispatch_token(t_token **list)
{
    int i;
    int cnt;
    int status = 0;
    t_fdgs fdgs;

    i = 0;
    cnt = 0;
    while (list[i] != NULL)
    {
        if (list[i]->type > 0 && list[i]->type < 30)
        {
            fcntl_token(&fdgs, list[i]);
        }
        else if (list[i]->type >= 30)
        {
            dispatch_token_help(list, &fdgs, i);
            cnt++;
        }
        i++;
    }
    while (cnt > 0 && x_wait(&status) > 0)
    {
        cnt--;
    }
}
