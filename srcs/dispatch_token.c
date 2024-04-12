
#include "../includes/minishell.h"

extern int sige;

void    dispatch_token_help(t_token *list, t_fdgs *fdgs, t_status *status, t_env *env)
{
    int pid;
    char **tokens_splited;

    fdgs->original_stdin = x_dup(STDIN_FILENO);
    fdgs->original_stdout = x_dup(STDOUT_FILENO);
    manage_gfdin(fdgs->gfd, list);
    manage_pipein(fdgs->pp, list);
    tokens_splited = ft_split(list->token, ' ');//Are we handle ftfuntions error
    handle_token(tokens_splited, status->exit_code, env);
    //buildin comand execve && list->pipe false
    // if(list->pipeout == false && list->pipein == false)
    // {
    //     check_builtins(tokens_splited, env);//check jakunane!!

    // }
    pid = x_fork();
    if (pid == 0)
    {
        manage_gfdout(fdgs->gfd, list);
        manage_pipeout(fdgs->pp, list);
        execve_token(tokens_splited, env);
    }
    else if (pid > 0)
    {
        x_dup2(fdgs->original_stdin, STDIN_FILENO);
        x_dup2(fdgs->original_stdout, STDOUT_FILENO);
        x_close(fdgs->original_stdin);
        x_close(fdgs->original_stdout);
        if(list->type == HEREDOCCOMMAND || list->type == REOUTHEREDOCCOMMAND)
            x_unlink("/tmp/sh-thd-tekitou");
    }
}

void dispatch_token(t_token **list)
{
    int i;
    int cnt;
    static t_status status;
    t_fdgs fdgs;
    t_env *env;
    
    i = 0;
    cnt = 0;
    env = environ_init();
    while (list[i] != NULL)
    {
        if (list[i]->type > 0 && list[i]->type < 30)
            fcntl_token(&fdgs, list[i], status.exit_code, env);
        else if (list[i]->type >= 30)
        {
            dispatch_token_help(list[i], &fdgs, &status, env);
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
