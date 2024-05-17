/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:41:45 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/25 03:47:02 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_builtins(char **tokens_splited, t_env *env, t_status *status)
{
	if (perfectly_match("cd", tokens_splited[0]) == 1)
	{
		status->exit_code = ft_cd(tokens_splited + 1, env);
		return (0);
	}
	else if (perfectly_match("export", tokens_splited[0]) == 1)
	{
		status->exit_code = ft_export(tokens_splited + 1, env);
		return (0);
	}
	else if (perfectly_match("unset", tokens_splited[0]) == 1)
	{
		status->exit_code = ft_unset(tokens_splited + 1, env);
		return (0);
	}
	else if (perfectly_match("exit", tokens_splited[0]) == 1)
	{
		ft_exit(tokens_splited, status->exit_code, 1, env);
		status->exit_code = 1;
		return (0);
	}
	return (-1);
}

int	check_builtins_parents(char **tokens_splited, t_env *env, t_status *status)
{
	int	is_builtins;

	is_builtins = exec_builtins(tokens_splited, env, status);
	return (is_builtins);
}

static int	exec_builtins_chld(char **tokens_splited, t_env *env)
{
	if (tokens_splited[0] == NULL)
		return (-1);
	if (perfectly_match("echo", tokens_splited[0]) == 1)
		return (ft_echo(tokens_splited));
	else if (perfectly_match("pwd", tokens_splited[0]) == 1)
	{
		ft_pwd();
		return (0);
	}
	else if (perfectly_match("env", tokens_splited[0]) == 1)
		return (ft_env(env));
	else if (perfectly_match("export", tokens_splited[0]) == 1)
	{
		ft_export(tokens_splited + 1, env);
		return (0);
	}
	else if (perfectly_match("unset", tokens_splited[0]) == 1
		|| perfectly_match("cd", tokens_splited[0]) == 1)
		return (0);
	else if (perfectly_match("exit", tokens_splited[0]) == 1)
	{
		ft_exit(tokens_splited, 0, 0, env);
		exit(1);
	}
	return (-1);
}

int	check_builtins_childs(char **tokens_splited, t_env *env)
{
	int	is_builtins;

	is_builtins = exec_builtins_chld(tokens_splited, env);
	if (is_builtins == 0)
		free_env(env);
	return (is_builtins);
}
