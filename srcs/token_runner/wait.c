/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:42:16 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/23 22:28:41 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_childs(t_status *status)
{
	while (wait(&status->exit_status) > 0 || errno != ECHILD)
	{
		if (WIFEXITED(status->exit_status))
		{
			status->exit_code = WEXITSTATUS(status->exit_status);
		}
		else if (WIFSIGNALED(status->exit_status) != 0)
		{
			if (WTERMSIG(status->exit_status) == SIGINT || WTERMSIG(status->exit_status) == SIGQUIT)
				write(1, "\n", 1);
			status->exit_code = WTERMSIG(status->exit_status) + 128;
		}
	}
}
