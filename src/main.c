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
	if (signum == SIGQUIT)
		return ;
}

int	main(void)
{
	char	*prompt;
	char	*input;
	t_token	*tokens;
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);// CNTL + C
	sigaction(SIGQUIT, &sa, NULL);//CNTL + "\"
	prompt = "minish>> ";
	while (1)
	{
		input = readline(prompt);
		if (input == NULL)// CNTL + D
		{
			ft_printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = lexer(input);
		free(input);
		decide_type(tokens);
		check(tokens);
		//実行用のプログラムを入れる
		print_tokens(tokens); //debug用
	}
	free(tokens); //全然リーク
	return 0;
}
