#include "../../includes/minishell.h"

extern t_ige	sige;

int	set_sigint_flag(int i)
{
	static int	sigint_flag;

	if (i == 1)
		sigint_flag = 1;
	else if (i == 0)
		sigint_flag = 0;
	return sigint_flag;
}

int	get_sigint_flag(void)
{
	return (set_sigint_flag(-1));
}

void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
		set_sigint_flag(1);
}

int	heredoc_hook(void)
{
	if (get_sigint_flag() == 1)
	{
		rl_replace_line("", 0);
		rl_done = 1;
		return 1;
	}
	else
		return 0;
}

void execute_heredoc(int gfd[2], t_token *list, int exit_code, t_env *env)
{
    char *input;

    signal(SIGINT, signal_handler_heredoc);
    rl_event_hook = heredoc_hook;
    rl_catch_signals = 0;
    gfd[0] = open("/tmp/sh-thd-tekitou", O_TRUNC | O_RDWR | O_CREAT, 0644);
    while(gfd[0] != -1 && get_sigint_flag() == 0)
    {
        input = readline("> ");
        if(input == NULL || get_sigint_flag() == 1)
        {
            x_close(gfd[0]);
            free(input);
	        rl_event_hook = 0;
            break;
        }
        if(ft_strncmp(input, list->token, ft_strlen(list->token)) == 0
                && ft_strlen(input) == ft_strlen(list->token))
        {
            x_close(gfd[0]);
            free(input);
            break;
        }
        input = expand_variable(input, 1, exit_code, env);
        write(gfd[0], input, ft_strlen(input));
        write(gfd[0], "\n", 1);
        free(input);
    }
}

void   fcntl_token(t_fdgs *fdgs, t_token *list, int exit_code)
{
    if (list->type == TRUNCOUTFILE)
    {
        fdgs->gfd[1] = x_open(list->token, O_TRUNC | O_CREAT | O_RDWR, 0644);
    }
    else if (list->type == APNDOUTFILE)
    {
        fdgs->gfd[1] = x_open(list->token, O_APPEND | O_CREAT | O_RDWR, 0644);
    }
    else if (list->type == INFILE)
    {
        fdgs->gfd[0] = x_open(list->token, O_RDONLY, 0);
    }
}