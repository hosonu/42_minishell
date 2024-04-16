#include "../includes/minishell.h"

extern t_ige sige;

void pre_manage_fd_parent(t_token *list, t_fdgs *fdgs)
{
    fdgs->original_stdin = x_dup(STDIN_FILENO);
    fdgs->original_stdout = x_dup(STDOUT_FILENO);
    manage_gfdin(fdgs->gfd, list);
    manage_pipein(fdgs->pp, list);
}

void    post_manage_fd_parent(t_token *list, t_fdgs *fdgs)
{
    x_dup2(fdgs->original_stdin, STDIN_FILENO);
    x_dup2(fdgs->original_stdout, STDOUT_FILENO);
    x_close(fdgs->original_stdin);
    x_close(fdgs->original_stdout);
    if(list->type == HEREDOCCOMMAND || list->type == REOUTHEREDOCCOMMAND)
        x_unlink("/tmp/sh-thd-tekitou");
}

void    dispatch_token_help(t_token *list, t_fdgs *fdgs, t_status *status, t_env *env)
{
    int pid;
    char **tokens_splited;

    pre_manage_fd_parent(list, fdgs);
    tokens_splited = ft_split(list->token, ' ');
    handle_token(tokens_splited, status->exit_code, env);
    if(list->pipeout != true &&  list->pipein != true && check_builtins_parents(tokens_splited, env) == 0)
        status->is_wait = 0;
    else
    {
        pid = x_fork();
        sige.ext_child = 1;
        if (pid == 0)
        {
            manage_gfdout(fdgs->gfd, list);
            manage_pipeout(fdgs->pp, list);
            execve_token(tokens_splited, env);
        }
    }
    post_manage_fd_parent(list, fdgs);
}

void dispatch_token(t_token **list)
{
    int i;
    int cnt;
    static t_status status;
    t_fdgs fdgs;
    static t_env *env;
    
    i = 0;
    cnt = 0;
    if(env == NULL)
        env = environ_init();
    status.is_wait = 1;
    sige.ext_child = 0;
    fdgs.gfd[0] = -2;
    if(sige.waiting_for_sige == SIGINT)
        status.exit_code = 130;
    while (list[i] != NULL)
    {
        if (list[i]->type > 0 && list[i]->type < 30)
        {
            fcntl_token(&fdgs, list[i], status.exit_code, env);
        }
        else if (list[i]->type >= 30 && fdgs.gfd[0] != -1)
        {
            dispatch_token_help(list[i], &fdgs, &status, env);
            if(status.is_wait == 1)
                cnt++;
        }
        else if(list[i]->type >= 30 && list[i]->pipeout == true)
        {
            x_pipe(fdgs.pp);
            fdgs.gfd[0] = -2;
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
    sige.ext_child = 0;
    sige.waiting_for_sige = 0;
}
