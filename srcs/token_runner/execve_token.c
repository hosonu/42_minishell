/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:43:43 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/24 02:36:11 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_path(char *command, char *path)
{
	path = ft_strjoin(path, "/");
	if (path == NULL)
		error_and_exit("malloc");
	path = ft_strjoin(path, command);
	if (path == NULL)
		error_and_exit("malloc");
	return (path);
}

char	*path_lookup(char *command, char **envi)
{
	int		i;
	char	**path;

	i = 0;
	while (envi[i] != NULL)
	{
		if (ft_strncmp(envi[i], "PATH=", 5) == 0)
		{
			path = ft_split(envi[i] + 5, ':');
			i = 0;
			while (path[i] != NULL)
			{
				path[i] = join_path(command, path[i]);
				if (access(path[i], X_OK) == 0)
					return (path[i]);
				free(path[i]);
				i++;
			}
		}
		i++;
	}
	return (NULL);
}

void	execve_token(char **tokens_splited, t_env *env)
{
	char	**environ;
	char	*command;
	int		i;

	i = 0;
	if (check_builtins_childs(tokens_splited, env) == 0)
		exit(0);
	environ = env_int_str(env);
	while (tokens_splited[i] != NULL)
	{
		if (access(tokens_splited[i], X_OK) == 0)
			x_execve(tokens_splited[i], tokens_splited, environ);
		else
		{
			command = path_lookup(tokens_splited[i], environ);
			x_execve(command, tokens_splited, environ);
		}
		i++;
	}
}
