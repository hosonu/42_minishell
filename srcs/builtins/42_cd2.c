/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:32:17 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 16:09:24 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_export(t_env *env, char *arg, char buff[PATH_MAX])
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