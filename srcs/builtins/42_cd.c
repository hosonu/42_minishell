/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:32:17 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 09:10:48 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_export(t_env *env, char *arg, char buff[PATH_MAX])
{
	char	*av[2];

	arg = ft_strjoin(arg, buff);
	if (arg == NULL)
	{
		perror("malloc");
		return (1);
	}
	av[0] = arg;
	av[1] = NULL;
	ft_export(av, env);
	free(arg);
	return (0);
}

void	cd_change_env(t_env *env)
{
	t_env	*pwd;
	char	pwd_buff[PATH_MAX];

	if (getcwd(pwd_buff, PATH_MAX) == NULL)
		perror("cd");
	pwd = getenv_node(env, "PWD");
	if (pwd == NULL)
		cd_export(env, "PWD=", pwd_buff);
	else
	{
		free(pwd->value);
		pwd->value = ft_strdup(pwd_buff);
		if (pwd->value == NULL)
			perror("malloc");
	}
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
	}
	return (0);
}

int	ft_cd(char *av[], t_env *env)
{
	t_env	*old;
	char	pwd_buff[PATH_MAX];

	if (getcwd(pwd_buff, PATH_MAX) == NULL)
	{
		perror("cd");
		return (1);
	}
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
	if (ft_chdir(av[0], env) == -1)
		return (1);
	else
		cd_change_env(env);
	return (0);
}
