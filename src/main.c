#include "../minishell.h"

void	print_tokens(t_token *top)
{
	while(top != NULL)
	{
		ft_printf("token %s\ttype %d\n", top->token, top->type);
		top = top->next;
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(void)
{
	char	*prompt;
	char	*input;
	t_token	*tokens;
/*	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
*/	prompt = "minish>> ";
	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = lexer(input);
		decide_type(tokens);
		print_tokens(tokens);
		free(input);
	}
	free(tokens);
	return 0;
}
