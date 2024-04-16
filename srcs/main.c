/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:06 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/16 16:14:10 by kojwatan         ###   ########.fr       */
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
		tokens = tokenize(input);
		free(input);
		list = token_list(tokens);
		dispatch_token(list);
		free_linear_token_list(list);
	}
	return 0;
}
