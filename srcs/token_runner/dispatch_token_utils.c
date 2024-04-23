/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:59:03 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/24 02:21:00 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pre_manage_fd_parent(t_token *list, t_fdgs *fdgs)
{
	fdgs->original_stdin = x_dup(STDIN_FILENO);
	fdgs->original_stdout = x_dup(STDOUT_FILENO);
	manage_pipein(fdgs->pp, list);
}

void	post_manage_fd_parent(t_fdgs *fdgs)
{
	x_dup2(fdgs->original_stdin, STDIN_FILENO);
	x_dup2(fdgs->original_stdout, STDOUT_FILENO);
	x_close(fdgs->original_stdin);
	x_close(fdgs->original_stdout);
}

void	mange_fd_child(t_token **list, t_fdgs *fdgs, t_status *status)
{
	if (status->is_file == 1)
		fcntl_token(fdgs, list[-1]);
	manage_gfdin(fdgs->gfd, (*list));
	manage_gfdout(fdgs->gfd, (*list));
	manage_pipeout(fdgs->pp, (*list));
}

void	dispatch_token_help(t_token **list, t_fdgs *fdgs, t_status *status,
		t_env *env)
{
	int		pid;
	char	**tokens_splited;

	tokens_splited = minish_split((*list)->token, ' ');
	if (tokens_splited == NULL)
		return ;
	handle_token(tokens_splited, status->exit_code, env);
	if ((*list)->pipeout != true && (*list)->pipein != true
		&& check_builtins_parents(tokens_splited, env, status->exit_code) == 0)
		return ;
	pre_manage_fd_parent((*list), fdgs);
	pid = x_fork();
	if (pid == 0)
	{
		if (get_sigint_flag() == 1)
			exit(EXIT_FAILURE);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		mange_fd_child(list, fdgs, status);
		execve_token(tokens_splited, env);
	}
	
	int	i = 0;
	while (tokens_splited[i] != NULL)
	{
		free(tokens_splited[i]);
		i++;
	}
	free(tokens_splited);

	signal(SIGINT, SIG_IGN);
	post_manage_fd_parent(fdgs);
}
