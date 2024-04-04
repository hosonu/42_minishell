#include "../includes/minishell.h"

void dispatch_token(t_token **list)
{
    int i;
    int pp[2];
    int pid;
    int pid2;
    int gfd[2];
    int original_stdin;

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
               fctl_token(gfd, list[i]);
            else if (list[i]->type >= 30)
            {
                original_stdin = dup(STDIN_FILENO);
                manage_gfdin(gfd, list[i]);
                manage_pipein(pp, list[i]);
                pid = fork();
                if (pid == 0)
                {
                    manage_gfdout(gfd, list[i]);
                    manage_pipeout(pp, list[i]);
                    execve_token(list[i]);
                }
                else if (pid > 0)
                {
                    wait(NULL);
                    if(list[i]->type == HEREDOCCOMMAND || list[i]->type == REOUTHEREDOCCOMMAND)
                    {
                        dup2(original_stdin, STDIN_FILENO);
                        close(original_stdin);
                        unlink("/tmp/sh-thd-tekitou");
                    }

                }
            }
            i++;
        }
        exit(0);
    }
}
