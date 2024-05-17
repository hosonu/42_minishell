/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_cd1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:08:49 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/09 16:47:13 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_chdir_util(t_env *env)
{
	t_env	*home;

	home = getenv_node(env, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("minish: cd: HOME not set\n", STDERR_FILENO);
		return (-1);
	}
	else
	{
		if (chdir(home->value) == -1)
		{
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
	if (errno == ENOENT && (perfectly_match(av[0], ".") == 1
			|| perfectly_match(av[0], "..") == 1))
	{
		ft_putstr_fd("cd: error retrieving current directory", STDERR_FILENO);
		ft_putstr_fd(": getcwd: cannot access parent directories:", 2);
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
	}
	set_oldpwd(pwd, env);
	free(pwd);
	if (ft_chdir(av[0], env) == -1)
		return (1);
	else
		cd_change_env(env);
	return (0);
}
