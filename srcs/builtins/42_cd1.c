/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_cd1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:08:49 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 16:18:44 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_chdir_util(t_env *env)
{
	t_env	*home;

	home = getenv_node(env, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("HOME not set\n", STDERR_FILENO);
		return (-1);
	}
	else
	{
		if (chdir(home->value) == -1)
		{
			printf("No such file or directory\n");
			return (-1);
		}
	}
	return (0);
}

static	int	ft_chdir(char *path, t_env *env)
{
	t_env	*home;

	if (path != NULL)
	{
		if (chdir(path) == -1)
		{
			printf("No such file or directory\n");
			return (-1);
		}
	}
	else
	{
		return (ft_chdir_util(env));
	}
	return (0);
}

static int	set_oldpwd(char pwd_buff[PATH_MAX], t_env *env)
{
	t_env	*old;

	old = getenv_node(env, "OLDPWD");
	if (old == NULL)
		cd_export(env, "OLDPWD=", pwd_buff);
	else
	{
		free(old->value);
		old->value = ft_strdup(pwd_buff);
		if (old->value == NULL)
		{
			perror("malloc");
			return (1);
		}
	}
}

int	ft_cd(char *av[], t_env *env)
{
	char	pwd_buff[PATH_MAX];

	if (getcwd(pwd_buff, PATH_MAX) == NULL)
	{
		perror("cd");
		return (1);
	}
	set_oldpwd(pwd_buff, env);
	if (ft_chdir(av[0], env) == -1)
		return (1);
	else
		cd_change_env(env);
	return (0);
}
