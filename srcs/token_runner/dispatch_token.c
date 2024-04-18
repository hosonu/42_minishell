#include "../../includes/minishell.h"

extern t_ige sige;
int	get_sigint_flag(void);
int	set_sigint_flag(int i);

void    token_main_engine(t_token **list, t_fdgs *fdgs, t_status *status, t_env *env)
{
    if ((*list)->type > 0 && (*list)->type < 30)
    {
        status->is_file = 1;
        if((*list)->type == HEREDOC)
            execute_heredoc(fdgs->gfd, (*list), status->exit_code, env);
    }
    else if((*list)->type >= 30)
    {
        dispatch_token_help(list, fdgs, status, env);
        status->is_file = 0;
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
        token_main_engine(&list[i], &fdgs, &status, env);
        i++;
    }
    wait_childs(&status);
    sige.waiting_for_sige = 0;
    set_sigint_flag(0);
}
