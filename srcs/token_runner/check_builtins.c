/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:41:45 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/19 14:41:45 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtins_parents(char **tokens_splited, t_env *env, t_status *status)
{
	int	is_builtins;

	is_builtins = -1;
	if (tokens_splited[0] == NULL)
		return (is_builtins);
	if (x_sstrncmp("cd", tokens_splited[0], 2) == 0)
	{
		status->exit_code = ft_cd(tokens_splited + 1, env);
		is_builtins = 0;
	}
	else if (x_sstrncmp("export", tokens_splited[0], 6) == 0)
	{
		status->exit_code = ft_export(tokens_splited + 1, env);
		is_builtins = 0;
	}
	else if (x_sstrncmp("unset", tokens_splited[0], 5) == 0)
	{
		status->exit_code = ft_unset(tokens_splited + 1, env);
		is_builtins = 0;
	}
	else if (x_sstrncmp("exit", tokens_splited[0], 4) == 0)
		ft_exit(tokens_splited, status->exit_code, 1, env);
	return (is_builtins);
}

int	check_builtins_childs(char **tokens_splited, t_env *env)
{
	int	is_builtins;

	is_builtins = -1;
	if (tokens_splited[0] == NULL)
		return (is_builtins);
	if (x_sstrncmp("echo", tokens_splited[0], 4) == 0)
		is_builtins = ft_echo(tokens_splited);
	else if (x_sstrncmp("pwd", tokens_splited[0], 3) == 0)
	{
		ft_pwd();
		is_builtins = 0;
	}
	else if (x_sstrncmp("env", tokens_splited[0], 3) == 0)
		is_builtins = ft_env(env);
	else if (x_sstrncmp("export", tokens_splited[0], 6) == 0)
	{
		ft_export(tokens_splited + 1, env);
		is_builtins = 0;
	}
	else if (x_sstrncmp("unset", tokens_splited[0], 5) == 0
		|| x_sstrncmp("cd", tokens_splited[0], 2) == 0)
		is_builtins = 0;
	else if (x_sstrncmp("exit", tokens_splited[0], 4) == 0)
		ft_exit(tokens_splited, 0, 0, env);
	return (is_builtins);
}
