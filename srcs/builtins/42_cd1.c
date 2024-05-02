/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_cd1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: watanabekoji <watanabekoji@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:08:49 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/01 13:07:36 by watanabekoj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_chdir_util(t_env *env)
{
	t_env	*home;

	home = getenv_node(env, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (-1);
	}
	else
	{
		if (chdir(home->value) == -1)
		{
			if (errno != ENOENT)
				perror("cd");
			return (-1);
		}
	}
	return (0);
}

static	int	ft_chdir(char *path, t_env *env)
{
	if (path != NULL)
	{
		if (chdir(path) == -1)
		{
			if (errno != ENOENT)
				perror("cd");
			return (-1);
		}
	}
	else
	{
		return (ft_chdir_util(env));
	}
	return (0);
}

static int	set_oldpwd(char *pwd_buff, t_env *env)
{
	t_env	*old;

	old = getenv_node(env, "OLDPWD");
	if (old == NULL)
		;
	else
	{
		free(old->value);
		old->value = ft_strdup(pwd_buff);
		if (old->value == NULL)
			return (1);
	}
	return (0);
}

int	ft_cd(char *av[], t_env *env)
{
	char	*pwd;

	pwd = x_getcwd();
	if (errno == ENOENT)
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", STDERR_FILENO);
	set_oldpwd(pwd, env);
	free(pwd);
	if (ft_chdir(av[0], env) == -1)
		return (1);
	else
		cd_change_env(env);
	return (0);
}
