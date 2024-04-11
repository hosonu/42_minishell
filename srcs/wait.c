
#include "../includes/minishell.h"

void    wait_process(int cnt, t_status *status)
{
    int exit_code;
    int exit_status
    int signal;
    while (cnt > 0 && x_wait(exit_status) > 0)
    {
        if (WIFEXITED(exit_status))
        {
            exit_code = WEXITSTATUS(exit_status);
            printf("Child process exited with code %d\n", exit_code);
        }
        else if (WIFSIGNALED(exit_status))
            signal = WTERMSIG(exit_status);
        cnt--;
    }
}
