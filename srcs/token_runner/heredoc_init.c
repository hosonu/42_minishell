/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcntl_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:44:00 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/19 14:44:00 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_sigint_flag(int i)
{
	static int	sigint_flag;

	if (i == 1)
		sigint_flag = 1;
	else if (i == 0)
		sigint_flag = 0;
	return (sigint_flag);
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
		return (1);
	}
	else
		return (0);
}

void	heredoc_init(int gfd[2])
{
	if (gfd[0] != -2)
		x_close(gfd[0]);
	signal(SIGINT, signal_handler_heredoc);
	rl_event_hook = heredoc_hook;
	rl_catch_signals = 0;
	gfd[0] = open("/tmp/sh-thd-tekitou", O_TRUNC | O_RDWR | O_CREAT, 0644);
}
