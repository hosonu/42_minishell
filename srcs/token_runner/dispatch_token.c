/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:50:56 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/24 20:51:51 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_sige;

void	token_main_engine(t_token **list, t_fdgs *fdgs, t_status *status,
		t_env *env)
{
	if ((*list)->type > 0 && (*list)->type < 30)
	{
		status->is_file += 1;
		if ((*list)->type == HEREDOC)
		{
			execute_heredoc(fdgs->gfd, (*list), status->exit_code, env);
		}
	}
	else if ((*list)->type >= 30)
	{
		dispatch_token_help(list, fdgs, status, env);
		status->is_file = 0;
	}
}

void	dispatch_token(t_token **list, t_env *env)
{
	int				i;
	t_fdgs			fdgs;
	static t_status	status;

	i = 0;
	if (g_sige == SIGINT)
		status.exit_code = 1;
	while (list[i] != NULL)
	{
		token_main_engine(&list[i], &fdgs, &status, env);
		i++;
	}
	wait_childs(&status);
	g_sige = 0;
	set_sigint_flag(0);
}
