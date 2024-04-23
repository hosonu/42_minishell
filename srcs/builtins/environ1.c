/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:19:17 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 09:17:20 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	key_cpy(char *dst, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var[i] != '=' && var[i] != '\0')
	{
		dst[j] = var[i];
		i++;
		j++;
	}
	dst[j] = '\0';
}

void	value_cpy(char *dst, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	if (var[i] != '\0')
		i++;
	while (var[i] != '\0')
	{
		dst[j] = var[i];
		j++;
		i++;
	}
	dst[j] = '\0';
}

t_env	*new_env(char *var)
{
	t_env	*new;
	char	**splited;

	if (ft_strchr(var, '=') == NULL)
		return (NULL);
	new = x_malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	splited = env_split(var);
	if (splited == NULL)
		return (NULL);
	new->key = splited[0];
	new->value = splited[1];
	new->next = NULL;
	return (new);
}

void	destroy_env(t_env *data)
{
	free(data->key);
	free(data->value);
	free(data);
}

void	delone_env(t_env *env, t_env *data)
{
	t_env	*tmp;

	if (env == NULL)
		return ;
	tmp = env;
	if (env->next == data)
		env->next = data->next;
	else
	{
		while (tmp != NULL)
		{
			if (tmp->next == data)
				tmp->next = data->next;
			tmp = tmp->next;
		}
	}
	destroy_env(data);
}