#include "../../includes/minishell.h"

void    wait_childs(t_status *status)
{
    while (wait(&status->exit_status) > 0 || errno != ECHILD)
    {
        if (WIFEXITED(status->exit_status))
        {
            status->exit_code = WEXITSTATUS(status->exit_status);
        }
        else if (WIFSIGNALED(status->exit_status) != 0)
        {
            if(WTERMSIG(status->exit_status) == SIGINT )
                write(1, "\n", 1);
            status->exit_code = WTERMSIG(status->exit_status) + 128;
        }
    }
}
