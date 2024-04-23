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

int	check_argc(char **str)
{
	int	cnt;

	cnt = 0;
	while (str[cnt] != NULL)
	{
		cnt++;
	}
	return (cnt);
}

int	check_builtins_parents(char **tokens_splited, t_env *env, int exit_code)
{
	int	is_builtins;

	is_builtins = -1;
	if (ft_strncmp("cd", tokens_splited[0], 2) == 0)
	{
		ft_cd(tokens_splited + 1, env);
		is_builtins = 0;
	}
	else if (ft_strncmp("export", tokens_splited[0], 5) == 0)
	{
		ft_export(tokens_splited + 1, env);
		is_builtins = 0;
	}
	else if (ft_strncmp("unset", tokens_splited[0], 5) == 0)
	{
		ft_unset(tokens_splited + 1, env);
		is_builtins = 0;
	}
	else if (ft_strncmp("exit", tokens_splited[0], 4) == 0)
	{
		ft_exit(tokens_splited, exit_code);
		is_builtins = 0;
	}
	return (is_builtins);
}

int	check_builtins_childs(char **tokens_splited, t_env *env)
{
	int	is_builtins;

	is_builtins = -1;
	if (ft_strncmp("echo", tokens_splited[0], 4) == 0)
		is_builtins = ft_echo(tokens_splited);
	else if (ft_strncmp("pwd", tokens_splited[0], 3) == 0)
		is_builtins = ft_pwd();
	else if (ft_strncmp("env", tokens_splited[0], 3) == 0)
		is_builtins = ft_env(env);
	else if (ft_strncmp("cd", tokens_splited[0], 2) == 0)
		is_builtins = 0;
	else if (ft_strncmp("export", tokens_splited[0], 5) == 0)
		is_builtins = 0;
	else if (ft_strncmp("unset", tokens_splited[0], 5) == 0)
		is_builtins = 0;
	else if (ft_strncmp("exit", tokens_splited[0], 4) == 0)
		is_builtins = 0;
	return (is_builtins);
}