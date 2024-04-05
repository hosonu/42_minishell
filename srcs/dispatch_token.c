#include "../includes/minishell.h"

void    dispatch_token_help(t_token **list, t_fdgs *fdgs, int i)
{
    int pid;

    fdgs->original_stdin = dup(STDIN_FILENO);
    manage_gfdin(fdgs->gfd, list[i]);
    manage_pipein(fdgs->pp, list[i]);
    pid = fork();
    if (pid == 0)
    {
        manage_gfdout(fdgs->gfd, list[i]);
        manage_pipeout(fdgs->pp, list[i]);
        execve_token(list[i]);
    }
    else if (pid > 0)
    {
        wait(NULL);
        if(list[i]->type == HEREDOCCOMMAND || list[i]->type == REOUTHEREDOCCOMMAND)
        {
            dup2(fdgs->original_stdin, STDIN_FILENO);
            close(fdgs->original_stdin);
            unlink("/tmp/sh-thd-tekitou");
        }
    }
}

void dispatch_token(t_token **list)
{
    int i;
    int pid2;
    t_fdgs fdgs;

    i = 0;
    pid2 = fork();
    if (pid2 > 0)
    {
        wait(NULL);
    }
    else if (pid2 == 0)
    {
        while (list[i] != NULL)
        {
            if (list[i]->type > 0 && list[i]->type < 30)
               fctl_token(&fdgs, list[i]);
            else if (list[i]->type >= 30)
            {
                dispatch_token_help(list, &fdgs, i);
            }
            i++;
        }
        exit(0);
    }
}
