/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:55:05 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/25 18:55:05 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_sige;

int	fcntl_engine(t_fdgs *fdgs, t_token **list, t_status *status, t_env *env)
{
	int	i;

	fdgs->gfd[0] = -2;
	fdgs->gfd[1] = -2;
	i = 0;
	while (list[i]->type != HEREDOC && status->is_file == 1
		&& list[i]->type < 30)
	{
		if (fcntl_token(fdgs, list[i], status, env) == -1)
			status->is_file = 0;
		i++;
		if (list[i] == NULL)
		{
			i--;
			break ;
		}
	}
	return (i);
}

void	dispatch_token(t_token **list, t_env *env, t_status *status)
{
	int		i;
	t_fdgs	fdgs;

	i = 0;
	status->is_file = 1;
	if (g_sige == SIGINT)
		status->exit_code = 1;
	while (list[i] != NULL)
	{
		i += fcntl_engine(&fdgs, &list[i], status, env);
		if (list[i] != NULL && list[i]->type == HEREDOC)
			execute_heredoc(fdgs.gfd, list[i], status->exit_code, env);
		else if (list[i] != NULL && list[i]->type >= 30)
		{
			if (dispatch_token_help(&list[i], &fdgs, status, env) == -1)
				break ;
			status->is_file = 1;
		}
		else if (list[i]->type == METAPIPE)
			status->is_file = 1;
		i++;
	}
	wait_childs(status);
	g_sige = 0;
	set_sigint_flag(0);
}
