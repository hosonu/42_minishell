/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:43:43 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/25 02:43:19 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_path(char *command, char *path)
{
	char	*tmp;

	tmp = path;
	path = ft_strjoin(path, "/");
	free(tmp);
	if (path == NULL)
		error_and_exit("malloc", 1, 0);
	path = ft_strjoin(path, command);
	if (path == NULL)
		error_and_exit("malloc", 1, 0);
	return (path);
}

char	*path_lookup(char *command, char **envi)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
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
	free(path);
	return (NULL);
}

void	execve_token(char **tokens_splited, t_env *env)
{
	char	**environ;
	char	*command;

	if (check_builtins_childs(tokens_splited, env) == 0)
		exit (0);
	environ = env_int_str(env);
	if (tokens_splited[0] == NULL)
		exit(0);
	if (tokens_splited[0][0] == '.' || tokens_splited[0][0] == '/')
	{
		if (access(tokens_splited[0], X_OK) == 0)
		{
			if (execve(tokens_splited[0], tokens_splited, environ) == -1)
				error_and_exit(tokens_splited[0], 126, 1);
		}
		else if (errno == EACCES)
			error_and_exit(tokens_splited[0], 126, 0);
		else
			error_and_exit(tokens_splited[0], 127, 0);
	}
	command = path_lookup(tokens_splited[0], environ);
	if (x_execve(command, tokens_splited, environ) == -1)
		exit (127);
}
