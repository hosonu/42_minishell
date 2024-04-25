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
	if (x_sstrncmp("cd", tokens_splited[0], 2) == 0)
	{
		status->exit_code = ft_cd(tokens_splited + 1, env);
		return (0);
	}
	else if (x_sstrncmp("export", tokens_splited[0], 6) == 0)
	{
		status->exit_code = ft_export(tokens_splited + 1, env);
		return (0);
	}
	else if (x_sstrncmp("unset", tokens_splited[0], 5) == 0)
	{
		status->exit_code = ft_unset(tokens_splited + 1, env);
		return (0);
	}
	else if (x_sstrncmp("exit", tokens_splited[0], 4) == 0)
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
	if (x_sstrncmp("echo", tokens_splited[0], 4) == 0)
		return (ft_echo(tokens_splited));
	else if (x_sstrncmp("pwd", tokens_splited[0], 3) == 0)
	{
		ft_pwd();
		return (0);
	}
	else if (x_sstrncmp("env", tokens_splited[0], 3) == 0)
		return (ft_env(env));
	else if (x_sstrncmp("export", tokens_splited[0], 6) == 0)
	{
		ft_export(tokens_splited + 1, env);
		return (0);
	}
	else if (x_sstrncmp("unset", tokens_splited[0], 5) == 0
		|| x_sstrncmp("cd", tokens_splited[0], 2) == 0)
		return (0);
	else if (x_sstrncmp("exit", tokens_splited[0], 4) == 0)
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
