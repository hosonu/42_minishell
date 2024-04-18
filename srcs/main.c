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

t_ige sige;
t_ige sige;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		sige.waiting_for_sige = signum;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

t_token	**prompt_handle(void)
{
	t_token	**list;
	t_token	*tokens;
	char	*input;

	input = readline("minish>> ");
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return NULL;
	}
	if (input[0] != '\0')
		add_history(input);
	if (quotation_validate(input) == -1)
	{
		free(input);
		//exit_status 258
		return NULL;
	}
	tokens = tokenize(input);
	free(input);
	list = token_list(tokens);
	return (list);
}

int	main(void)
{
	t_token	**list;

	while (1)
	{
		set_signal_handler();
		list = prompt_handle();
		if (list != NULL)
		{
			dispatch_token(list);
			free_linear_token_list(list);
		}
		else
			break ;
	}
	return 0;
}
