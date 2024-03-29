#include "../minishell.h"

void	print_tokens(t_token *top)
{
	while(top != NULL)
	{
		ft_printf("DEBUG before sort: token [%s]\ttype %d\n", top->token, top->type);
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
	char	*input_trimed;
	t_token	*tokens;
	t_token	**list;
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
		input_trimed = ft_strtrim(input, " ");
		free(input);
		tokens = lexer(input_trimed);
		free(input_trimed);
		decide_type(tokens);
		//print_tokens(tokens); //debug用
		token_revise(tokens);
		list = linear_token_list(tokens);
		sort_token(list);
		token_type_revise(list);
		//実行用のプログラムを入れる
		//print_tokens(tokens); //debug用
		print_to(list);
	}
	free(tokens); //全然リーク
	return 0;
}
