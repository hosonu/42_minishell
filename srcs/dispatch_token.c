
#include "../includes/minishell.h"

void    dispatch_token_help(t_token **list, t_fdgs *fdgs, int i, t_status *status)
{
    int pid;
    char **tokens_splited;

    fdgs->original_stdin = x_dup(STDIN_FILENO);
    fdgs->original_stdout = x_dup(STDOUT_FILENO);
    manage_gfdin(fdgs->gfd, list[i]);
    manage_pipein(fdgs->pp, list[i]);
    tokens_splited = ft_split(list[i]->token, ' ');//Are we handle ftfuntions error
    handle_token(tokens_splited, status->exit_code);
    //buildin comand execve && list[i]->pipe false
    pid = x_fork();
    if (pid == 0)
    {
        manage_gfdout(fdgs->gfd, list[i]);
        manage_pipeout(fdgs->pp, list[i]);
        execve_token(tokens_splited);
    }
    else if (pid > 0)
    {
        x_dup2(fdgs->original_stdin, STDIN_FILENO);
        x_dup2(fdgs->original_stdout, STDOUT_FILENO);
        x_close(fdgs->original_stdin);
        x_close(fdgs->original_stdout);
        if(list[i]->type == HEREDOCCOMMAND || list[i]->type == REOUTHEREDOCCOMMAND)
            x_unlink("/tmp/sh-thd-tekitou");
    }
}

void dispatch_token(t_token **list)
{
    int i;
    int cnt;
    static t_status status;
    t_fdgs fdgs;
    
    i = 0;
    cnt = 0;
    while (list[i] != NULL)
    {
        if (list[i]->type > 0 && list[i]->type < 30)
            fcntl_token(&fdgs, list[i], status.exit_code);
        else if (list[i]->type >= 30)
        {
            dispatch_token_help(list, &fdgs, i, &status);
            cnt++;
        }
        i++;
    }   
    while (cnt > 0 && x_wait(&status.exit_status) > 0)
    {
        if (WIFEXITED(status.exit_status))
            status.exit_code = WEXITSTATUS(status.exit_status);
        else if (WIFSIGNALED(status.exit_status))
            status.exit_code = WTERMSIG(status.exit_status) + 128;
        cnt--;
    }
}
