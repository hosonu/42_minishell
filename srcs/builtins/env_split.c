/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:39:59 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/24 00:24:16 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**env_split_alloc(char **split, char *var)
{
	int	count;

	count = key_strlen(var);
	split[0] = x_malloc(count + 1);
	if (split[0] == NULL)
		return (NULL);
	count = value_strlen(var);
	if (ft_strchr(var, '=') == NULL)
		split[1] = NULL;
	else if (count == 0)
		split[1] = ft_strdup("");
	else
	{
		split[1] = x_malloc(value_strlen(var) + 1);
		if (split[1] == NULL)
		{
			free(split[0]);
			return (NULL);
		}
		ft_memset(split[1], 1, value_strlen(var));
	}
	return (split);
}

static void	env_split_cpy(char **split, char *var)
{
	key_cpy(split[0], var);
	if (split[1] != NULL && split[1][0] != '\0')
		value_cpy(split[1], var);
}

char	**env_split(char *var)
{
	char	**split;

	split = x_malloc(sizeof(char *) * 2);
	if (split == NULL)
		return (NULL);
	split[1] = NULL;
	split = env_split_alloc(split, var);
	if (split == NULL)
	{
		free(split);
		return (NULL);
	}
	env_split_cpy(split, var);
	return (split);
}
