/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:06 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/04 02:47:58 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


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
	while (1)
	{
		input = readline("minish>> ");
		if (input == NULL)// CNTL + D
		{
			ft_printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (prompt_validate(input) == -1)
		{
			free(input);
			continue ;
		}
		input_trimed = ft_strtrim(input, " ");
		free(input);
		tokens = lexer(input_trimed);
		free(input_trimed);
		//print_chain_tokens(tokens); //debug用
		decide_type(tokens);
		token_revise(tokens);
		sort_token(&tokens);
		//print_chain_tokens(tokens); //debug用
		token_revise(tokens);
		//free_chain_token_list(tokens); //線形リストにデータを移しているのでfreeはしちゃだめ
		list = linear_token_list(tokens);
		token_type_revise(list);
		//実行用のプログラムを入れる
		dispatch_token(list);
		//print_linear_tokens(tokens); //debug用
		// print_linear_tokens(list);
		free_linear_token_list(list);
	}
	return 0;
}
