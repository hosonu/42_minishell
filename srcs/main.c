/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:06 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/18 21:05:54 by kojwatan         ###   ########.fr       */
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
	}
	return 0;
}
