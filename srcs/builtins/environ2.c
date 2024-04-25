/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:24:10 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 23:30:39 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	addlast_env(t_env *env, t_env *new)
{
	t_env	*node;

	node = env;
	while (node->next != NULL)
		node = node->next;
	node->next = new;
}

t_env	*environ_init(void)
{
	extern char	**environ;
	t_env		*env;
	t_env		*new;
	int			i;

	i = 0;
	env = x_malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
	while (environ[i] != NULL)
	{
		new = new_env(environ[i]);
		if (new == NULL)
		{
			free_env(env);
			return (NULL);
		}
		addlast_env(env, new);
		i++;
	}
	return (env);
}

char	*ft_getenv(t_env *env, char *key)
{
	char	*value;

	value = NULL;
	if (key == NULL)
		return (NULL);
	env = env->next;
	while (env != NULL)
	{
		if (ft_strncmp(key, env->key, ft_strlen(key)) == 0)
		{
			if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
			{
				value = ft_strdup(env->value);
				if (value == NULL)
				{
					perror("malloc");
					return (NULL);
				}
			}
		}
		env = env->next;
	}
	return (value);
}

t_env	*getenv_node(t_env *env, char *key)
{
	env = env->next;
	while (env != NULL)
	{
		if (ft_strncmp(key, env->key, ft_strlen(key)) == 0)
		{
			if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
				return (env);
		}
		env = env->next;
	}
	return (NULL);
}

char	**env_int_str(t_env *env)
{
	char	**str;
	char	*line;
	char	*tmp;

	line = NULL;
	env = env->next;
	while (env != NULL)
	{
		tmp = line;
		line = ft_strjoin(line, env->key);
		free(tmp);
		tmp = line;
		line = ft_strjoin(line, "=");
		free(tmp);
		tmp = line;
		line = ft_strjoin(line, env->value);
		free(tmp);
		tmp = line;
		line = ft_strjoin(line, "\n");
		free(tmp);
		env = env->next;
	}
	str = ft_split(line, '\n');
	free(line);
	return (str);
}
