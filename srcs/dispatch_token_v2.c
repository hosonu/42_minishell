#include "../includes/minishell.h"

extern t_ige sige;
int	get_sigint_flag(void);
int	set_sigint_flag(int i);

void pre_manage_fd_parent(t_token *list, t_fdgs *fdgs)
{
    fdgs->original_stdin = x_dup(STDIN_FILENO);
    fdgs->original_stdout = x_dup(STDOUT_FILENO);
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

void    dispatch_token_help(t_token **list, t_fdgs *fdgs, t_status *status, t_env *env)
{
    int pid;
    char **tokens_splited;

    tokens_splited = ft_split((*list)->token, ' ');
    handle_token(tokens_splited, status->exit_code, env);
    if((*list)->pipeout != true &&  (*list)->pipein != true 
        && check_builtins_parents(tokens_splited, env) == 0)
        return ;
    else
    {
        pre_manage_fd_parent((*list), fdgs);
        pid = x_fork();
        if(pid == 0)
        {
            if (get_sigint_flag() == 1)
		        exit(EXIT_FAILURE);
            signal(SIGINT, SIG_DFL);
            if(status->is_file == 1)
            {
                fcntl_token(fdgs, list[-1], status->exit_code, env);
            }
            manage_gfdin(fdgs->gfd, (*list));
            manage_gfdout(fdgs->gfd, (*list));
            manage_pipeout(fdgs->pp, (*list));
            execve_token(tokens_splited, env);
        }
        else
        {
            signal(SIGINT, SIG_IGN);
            post_manage_fd_parent((*list), fdgs);
        }
    }
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
    if(sige.waiting_for_sige == SIGINT)
        status.exit_code = 130;
    while (list[i] != NULL)
    {
        if (list[i]->type > 0 && list[i]->type < 30)
        {
            status.is_file = 1;
            if(list[i]->type == HEREDOC)
            {
                fdgs.gfd[0] = x_open("/tmp/sh-thd-tekitou", O_TRUNC | O_RDWR | O_CREAT, 0644);
                execute_heredoc(fdgs.gfd, list[i], status.exit_code, env);
            }
        }
        else if(list[i]->type >= 30)
        {
            dispatch_token_help(&list[i], &fdgs, &status, env);
            status.is_file = 0;
        }
        i++;
    }
    while (wait(&status.exit_status) > 0 || errno != ECHILD)
    {
        if (WIFEXITED(status.exit_status))
        {
            status.exit_code = WEXITSTATUS(status.exit_status);
        }
        else if (WIFSIGNALED(status.exit_status) != 0)
        {
            if(WTERMSIG(status.exit_status) == SIGINT )
                write(1, "\n", 1);
            status.exit_code = WTERMSIG(status.exit_status) + 128;
        }
    }
    sige.ext_child = 0;
    sige.waiting_for_sige = 0;
    set_sigint_flag(0);
}
