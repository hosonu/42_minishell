/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:42:03 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/19 14:42:03 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	manage_gfdin(int gfd[2], t_token *list, bool gene)
{
	if (list->type == REINCOMMAND || list->type == REINOUTCOMMAND)
	{
		if (gene == 0)
			x_dup2(gfd[0], STDIN_FILENO);
		else if (gene == 1 && gfd[0] != -1)
			x_close(gfd[0]);
	}
	else if (list->type == HEREDOCCOMMAND || list->type == REOUTHEREDOCCOMMAND)
	{
		if (gfd[0] == -2)
			gfd[0] = x_open("/tmp/sh-thd-tekitou", O_RDONLY, 0);
		if (gene == 0)
			x_dup2(gfd[0], STDIN_FILENO);
		else if (gene == 1 && gfd[0] != -1)
			x_close(gfd[0]);
	}
}

void	manage_gfdout(int gfd[2], t_token *list, bool gene)
{
	if (list->type == REOUTCOMMAND || list->type == REINOUTCOMMAND
		|| list->type == REOUTHEREDOCCOMMAND)
	{
		if (gene == 0)
			x_dup2(gfd[1], STDOUT_FILENO);
		else if (gene == 1 && gfd[1] != -1)
			x_close(gfd[1]);
	}
}

void	manage_pipein(int pp[2], t_token *list)
{
	if (list->pipein == true)
	{
		if (list->type == COMMAND || list->type == REOUTCOMMAND)
		{
			x_dup2(pp[0], STDIN_FILENO);
		}
		x_close(pp[0]);
		x_close(pp[1]);
	}
	if (list->pipeout == true)
		x_pipe(pp);
}

void	manage_pipeout(int pp[2], t_token *list)
{
	if (list->pipeout == true)
	{
		if (list->type == COMMAND || list->type == REINCOMMAND
			|| list->type == HEREDOCCOMMAND)
		{
			x_dup2(pp[1], STDOUT_FILENO);
		}
		x_close(pp[0]);
		x_close(pp[1]);
	}
}
