/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:59:03 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/24 21:26:36 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pre_manage_fd_parent(t_token *list, t_fdgs *fdgs)
{
	fdgs->original_stdin = x_dup(STDIN_FILENO);
	fdgs->original_stdout = x_dup(STDOUT_FILENO);
	manage_pipein(fdgs->pp, list);
}

void	post_manage_fd_parent(t_fdgs *fdgs, char **tokens_splited,
		t_token **list)
{
	dup2(fdgs->original_stdin, STDIN_FILENO);
	dup2(fdgs->original_stdout, STDOUT_FILENO);
	x_close(fdgs->original_stdin);
	x_close(fdgs->original_stdout);
	manage_gfdin(fdgs->gfd, (*list), 1);
	manage_gfdout(fdgs->gfd, (*list), 1);
	double_free(tokens_splited);
}

void	mange_fd_child(t_token **list, t_fdgs *fdgs)
{
	manage_gfdin(fdgs->gfd, (*list), 0);
	manage_gfdout(fdgs->gfd, (*list), 0);
	manage_pipeout(fdgs->pp, (*list));
}

void	child_help(char **tokens_splited, t_env *env)
{
	if (get_sigint_flag() == 1)
		exit(EXIT_FAILURE);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve_token(tokens_splited, env);
}

int	dispatch_token_help(t_token **list, t_fdgs *fdgs, t_status *status,
		t_env *env)
{
	int		pid;
	char	**tokens_splited;

	tokens_splited = minish_split((*list)->token, ' ');
	if (tokens_splited == NULL)
		return (double_free(tokens_splited));
	tokens_splited = handle_token(tokens_splited, status->exit_code, env);
	if ((*list)->pipeout != true && (*list)->pipein != true
		&& check_builtins_parents(tokens_splited, env, status) == 0)
		return (double_free(tokens_splited));
	pre_manage_fd_parent((*list), fdgs);
	pid = x_fork(status);
	if (pid == 0)
	{
		mange_fd_child(list, fdgs);
		child_help(tokens_splited, env);
	}
	signal(SIGINT, SIG_IGN);
	post_manage_fd_parent(fdgs, tokens_splited, list);
	if (pid == -1)
		return (just_close_pipe(fdgs->pp));
	return (0);
}
