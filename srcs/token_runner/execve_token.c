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
	tmp = path;
	path = ft_strjoin(path, command);
	free(tmp);
	if (path == NULL)
		error_and_exit("malloc", 1, 0);
	return (path);
}

char	*find_executable(char *command, char **path)
{
	int		j;
	char	*full_path;

	j = 0;
	while (path[j] != NULL)
	{
		full_path = join_path(command, path[j]);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		j++;
	}
	return (NULL);
}

char	*path_lookup(char *command, char **envi)
{
	int		i;
	char	*result;
	char	**path;

	i = 0;
	path = NULL;
	if (envi == NULL || command == NULL)
		return (NULL);
	while (envi[i] != NULL)
	{
		if (ft_strncmp(envi[i], "PATH=", 5) == 0)
		{
			path = ft_split(envi[i] + 5, ':');
			result = find_executable(command, path);
			free(path);
			return (result);
		}
		i++;
	}
	return (NULL);
}

void	execve_token(char **tokens_splited, t_env *env)
{
	char	**environ;
	char	*command;

	if (check_builtins_childs(tokens_splited, env) == 0)
		exit (0);
	environ = env_int_str(env);
	free_env(env);
	if (tokens_splited[0] == NULL)
		exit(0);
	if (tokens_splited[0][0] == '.' || tokens_splited[0][0] == '/'
		|| (tokens_splited[0][0] == '~' && tokens_splited[0][1] == '/'))
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
