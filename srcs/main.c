/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: watanabekoji <watanabekoji@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:06 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/01 02:13:01 by watanabekoj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_sige;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sige = signum;
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
	t_token			**list;
	t_env			*env;
	t_status		status;
	struct termios	oldt;

	tcgetattr(STDIN_FILENO, &oldt);
	status.is_file = 0;
	status.exit_status = 0;
	status.exit_code = 0;
	env = environ_init();
	while (1)
	{
		set_signal_handler();
		list = prompt_handle(env, &status);
		if (list != NULL)
		{
			dispatch_token(list, env, &status);
			if (access("/tmp/sh-thd-tekitou", F_OK) == 0)
				x_unlink("/tmp/sh-thd-tekitou");
			free_linear_token_list(list);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}
	free_env(env);
	return (0);
}
